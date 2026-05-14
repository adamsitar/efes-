{ Sprava AUP,UUP sa spacovava ucelene, v pripade odosielania do siete
  AFTN ju odosielajuca stanica rozbije do sprav s maximalnou povolenou
  dlzkou a indikuje poradovym cislom spravy.

  [Alternativnym riesenim je priprava casti sprav AUP,UUP a ich ulozenie
   v suboroch dd-mm-rr.00i namiesto dd-mm-rr.typ. Bol som vo velkom pokuseni
   pouzit toto riesenie, lebo neviem, ake su presne postupy pri tvorbe postupov sprav
   AUP, UUP v praxi, ci je mozne spravu opakovane vytvorit, alebo opravou
   prepisat povodnu..., neviem, ci na vsetky smery posielaju identicku
   spravu AUP, neviem kolko odosielaju sprav UUP
  ]

  LAM o spracovani spravy sa nevyhodnocuje.
}

{ nacitanie/kontrola spravnosti uvedenia poloziek hlavicky,
  predpokladom je, ze editor dovoli zapisovat len velkymi
  pismenami, pretoze sprava je urcena do AFTN
}
 function _up_head (fn  : string;
                    buf : PTxtFileBuffer;

                    var _up : string;   { typ spravy   }
                    var cis : string;   { cislo spravy }
                    var ref : string;   { odkazovana sprava }

                    var adr : string;   { adresati spravy }
                    var zac : TDatum;   { datum zaciatku platnosti spravy }
                    var kon : TDatum;   { datum konca platnosti spravy }

                    var val : TDate;

                    check_all : bool;
                    typ     : string;   { ocakavany tup spravy }

                    var res : string
                   ): bool;             { true, ak subor existuje }

    var   _adr,s,t : string;
          cislo : long;
          i,j,al,ires : int;
          isbuf,isb : bool;

    label X;

    begin
      _up_head:= false;
      res:= ''; ires:= -1;
      _up:= ''; cis:= ''; ref:= ''; adr:= '';
      fillchar (zac,sizeof(zac),0);
      fillchar (kon,sizeof(kon),0);
      fillchar (val,sizeof(val),0);


     { otestovanie naplnenia spravy
     }
      isbuf:= buf<>nil;
      if (not isbuf) then
         begin
           if FExists(fn)<>0 then
              begin
                ires:= l4_err(a_FUA,'',0,err_FUA_sprava_not_found, res);
                Exit;
              end;
           buf:= new(PTxtFileBuffer,Init(fn));
           buf^.ReadFile;
         end;


     { vyhladanie a otestovanie typu spravy "TYPE"
     }
      i:= 0; while (i<buf^.items) do
        begin
          s:= cut_(buf^.read(i));
          inc(i);
          if pos(key_fua_type+' ',s)=1 then
             begin
               _up:= getstr(s,2,[icao_NXIT]);
               break
             end;
        end;

      if (_up='') then ires:= l4_err(a_FUA,'',0,err_FUA_typ, res);
      if (ires=-1) and (typ<>'') and (typ<>_up) then ires:= l4_err(a_FUA,'',0,err_FUA_typ, res);
      if check_all and (ires<>-1) then goto X
      else ires:= -1;


     { vyhladanie, spracovanie a otestovanie poloziek pre "REF DATA"
     }
      _adr:= '';
      while (i<buf^.items) do
        begin
          s:= cut_(buf^.read(i));
          inc(i);
          j:= pos(key_fua_ref_data+' ',s);
          if j=1 then
             begin
               s:= cut_(copy(s,j+length(key_fua_ref_data),length(s)-length(key_fua_ref_data)+1));
               break
             end;
        end;

     { kontrola zadania spravnosti vlastnej adresy
     }
      if (s='') then ires:= l4_err(a_FUA,'',0,err_FUA_ods, res);
      if (ires=-1) then
         begin
           al:= 0;
           ires:= _check_mtk_adr (s,_adr,al,true,0,res);
         end;
      {$IFDEF CONNECT_TO_AFTN}
       if (ires=-1) and (ADR_O_THIS<>_adr) then ires:= l4_err(a_FUA,'',0,err_FUA_ods, res);
      {$ENDIF}
      if check_all and (ires<>-1) then goto X
      else ires:= -1;


     { nacitania adries adresatov
     }
      adr:= ''; al:= 0;
      while (i<buf^.items) and (ires=-1) do
         begin
           s:= cut_(buf^.read(i));
           inc(i);
           if   { dalsi (iny ako adresa) text ? }
                 (length(s) = kod_MTK_2_MOD_CISLA_SPRAVY)
              or (pos(key_fua_msg_ref,s)=1)
              or (pos(key_fua_fil_time,s)=1)
              or (pos(key_fua_val_period,s)=1)
                 then break;
           ires:= _check_mtk_adr (s, adr,al,false,0,res);
         end;
      if adr<>'' then ires:= _check_mtk_adr ('', adr,al,true,0,res)
      else ires:= l4_err(a_FUA,'',0,err_FUA_adr, res);
      if check_all and (ires<>-1) then goto X
      else ires:= -1;


     { vyhladanie cisla spravy, ak za adresami nenasleduje cislo spravy,
       je to chyba. Cislo musi byt zadane vzdy.
     }
      if    (length(s)<>kod_MTK_2_MOD_CISLA_SPRAVY)
         or (not is_scish_(s,cislo,false))
         then ires:= l4_err(a_FUA,'',0,err_FUA_cis, res)
      else cis:= s;
      if ires<>-1 then goto X;
      if i<buf^.items then
         begin
           s:= cut_(buf^.read(i));
           inc(i);
         end;


     { vyhladanie cisla opravovanej spravy v "MSG REF",
       ak je to sprava UUP
     }
      if (_up=key_UUP) or (typ=key_UUP) then
         begin
         { najdenie casti "MSG REF" a jej posledneho riadku
           obsahujuceho cislo opravovanej spravy
         }
           if (pos(key_fua_msg_ref,s)<>1) and (i<buf^.items) then
              begin
                s:= cut_(buf^.read(i));
                inc(i);
              end;
           j:= pos(key_fua_msg_ref,s);
           if j=1 then
              begin
                s:= cut_(copy(s,j+length(key_fua_msg_ref),length(s)-length(key_fua_msg_ref)+1));
                isb:= false;
                while (not isb) and (ires=-1) and (i<buf^.items) do
                  begin
                    t:= copy(s,length(key_AUP)+1,kod_MTK_2_MOD_CISLA_SPRAVY);
                    isb:=     (length(s)=length(key_AUP) + kod_MTK_2_MOD_CISLA_SPRAVY)
                          and (is_scish_(t,cislo,false));
                    if not isb then
                       begin
                         s:= cut_(buf^.read(i));
                         inc(i);
                       end;
                  end;
                if not isb then ires:= l4_err(a_FUA,'',0,err_FUA_ref, res)
                else ref:= t
              end
           else ires:= l4_err(a_FUA,'',0,err_FUA_ref, res);
           if check_all and (ires<>-1) then goto X
           else ires:= -1;
         end;


     { vyhladanie zaciatku a konca platnosti spravy
     }
      isb:= false;
      while (i<buf^.items) and (ires=-1) do
         begin
           isb:= pos(key_fua_val_period,s)=1;
           if isb then break;
           s:= cut_(buf^.read(i));
           inc(i);
         end;

      if not isb then
         begin
           ires:= l4_err(a_FUA,'',0,err_FUA_val, res);
           goto X
         end
      else t:= cut_(copy(s,length(key_fua_val_period)+1,N(length(s)-length(key_fua_val_period))));

      if    (not decode_l4_datum (getstr(t,1,[icao_NXIT]),zac))
         or (DateToSec(year,month,day) > DatumToSec(zac))
            then
         begin
           ires:= l4_err(a_FUA,'',0,err_FUA_zac, res);
           goto X
         end;

     if check_all then
        begin
          if     (not decode_l4_datum (getstr(t,2,[icao_NXIT]),kon))
              or (DatumToSec(zac) >= DatumToSec(kon))
                then
              begin
                ires:= l4_err(a_FUA,'',0,err_FUA_kon, res);
                goto X
              end;

           if   (DatumToSec(zac)+secDAY < DatumToSec(kon))
             or (TimeToSec(zac.h,zac.m,0) < TimeToSec(cas_PRS_zac,0,0))
             or ((zac.den<>kon.den) and (TimeToSec(kon.h,kon.m,0) >  TimeToSec(cas_PRS_zac,0,0)))
             then
              begin
                ires:= l4_err(a_FUA,'',0,err_FUA_dlz, res);
                goto X
              end;
        end;

     { urcenie platnosti spravy
     }
      init_date (val, zac.rok,zac.mes,zac.den);


      X: if not isbuf then
            begin
              buf^.Done;
              dispose(buf{,Done});
            end;

      _up_head:= ires=-1;
    end;


 function _up_check (fn  : string;
                     buf : PTxtFileBuffer;

                     typ : string;        { ocakavany typ spravy }

                     var _up  : string;   { zapisany typ spravy  }

                     var cis  : string;   { cislo spravy }
                     var ref  : string;   { odkazovana sprava }

                     var adr  : string;   { adresati spravy      }
                     var zac  : TDatum;   { datum zaciatku platnosti spravy }
                     var kon  : TDatum;   { datum konca platnosti spravy    }

                     var val  : TDate;

                     check_all : bool;
                     _typ      : string;  { ocakavany tup spravy }

                     var res   : string
                    ): bool;              { true, ak subor existuje         }


    begin
      _up_check:= false;
      if not _up_head (fn,buf, _up,cis,ref, adr,zac,kon, val, check_all,_typ,res) then Exit;
      _up_check:= res='';
    end;


 procedure _up_fil_time (fn: string; val: string);
     var   buf1,buf2 : PTxtFileBuffer;
           i,j,z,k : int;
           b1,b2 : bool;
           s : string;
     begin
       if FExists(fn)<>0 then Exit;

       buf1:= new(PTxtFileBuffer,Init(fn));
       buf2:= new(PTxtFileBuffer,Init(fn));
       buf1^.ReadFile;

      { vyhladanie zaciatku a konca platnosti spravy
      }
       i:= 0; while (i<buf1^.items) do
         begin
           s:= cut_(buf1^.read(i));
           b1:= pos(key_fua_fil_time,s)=1;
           b2:= pos(key_fua_val_period+' ',s)=1;
           if b1 or b2 then break;
           inc(i)
         end;

       if i<buf1^.items then
          begin

           { vytvorenie kopie a vlozenie udajov do nich
           }
            for j:= 0 to i-1 do buf2^.add(buf1^.read(j));
            buf2^.add(key_fua_fil_time+'   '+val);
            if b1 then z:= i+1 else z:= i;
            for j:= z to buf1^.items-1 do buf2^.add(buf1^.read(j));

           { ulozenie subora
           }
            buf2^.SaveFile;
          end;

       dispose(buf2,Done);
       dispose(buf1,Done);
     end;


{ -------------------
   DB - ulozenie
  -------------------
}

 function _get_db_up_dfn (val: TDate; path,cis: string): string;
    begin
      _get_db_up_dfn:= get_DBfn_(val.d,val.m,val.r, path,cis)
    end;

 procedure _up_save (tmp,fn: string);
     begin
       if tmp<>fn then {if FExists(tmp)=0 then} copyfile(tmp,fn)
     end;

 (*procedure _up_save_tmp (tmp: string; val: TDate; path,head: string);
     begin
       {if FExists(tmp)=0 then} _up_save (tmp,_get_db_up_dfn(val,path,head))
     end;*)



{ -------------------
   NET - distribucia
  -------------------
}

 function  _up_send (fn: string; adr: TNETadr; typ: TNETtyp): bool;
    begin
      _up_send:= NETres(NETsend_file (adr,typ,fn,inf_FUA,net_flag_SEND,false,true,true,true,true))
    end;


 function _up_distribute (fn: string; typ: TNETtyp; sw: Tnd_sw_set; nd: Tnd_nd_set): bool;
    begin
      _up_distribute:= NETdistribute_file ([FDP,FDP0NX],sw,nd,typ,fn,inf_FUA,net_flag_SEND,ispath__UP,isext__UP,true,true,true)
    end;


{ -------------------
   EXT - koordinacia
  -------------------
}
 procedure _up_coordinate (fn : string;
                           head: string; typ: TNETtyp;
                           src: fdp_src; dst: set_fdp_src
                          );
     begin
      {$IFDEF EXTERNAL_NET}
       fdp_co_ordinate_procedure (src,dst, typ,head, true,fn);
      {$ENDIF}
     end;


{ --------------
   NET+EXT
  --------------
}
 function __up_odosli (fn: string;
                       head: string; typ: TNETtyp;
                       _src: fdp_src
                      ): bool;
    begin
      {$IFDEF PROCESS_FUA}
        {if __is_stat(PRS^.stat,cnst_disk) then
           begin
             stat:= cnst_sended;
             save_PRS(PRS);
           end;
        }
      {$ENDIF}

      __up_odosli:= _up_distribute (fn,typ, [],[]);
      _up_coordinate (fn,head,typ,_src,dst__UP)
    end;

 procedure _up_odosli (fn: string; head: string; typ: TNETtyp);
     begin
       __up_odosli (fn,head,typ,letvis)
     end;


{ --------------
   Funkcie
  --------------
}
 function _up_zarad (tmp,fn: string; head: string; typ: TNETtyp; _send: bool; _src: fdp_src): bool;
    begin
      _up_zarad:= true;

      { ulozenie subora }
      _up_save (tmp,fn);

      { zmazenie potvrdenia, ak existuje }
      file_rec (-1,fn,true,no_ack,true);

      { rozoslanie }
      if _send then __up_odosli (fn,head,typ,_src);

      {$IFDEF STATISTIKA_SERVER}
        {if p_save_STA_PRS<>nil then TProc_p(p_save_STA_PRS)(PRS);}
      {$ENDIF}

      {if (p_prs_dbscroller<>nil) then p_prs_dbscroller^.data_update(PRS);}
    end;
