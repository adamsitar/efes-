{ ----------------------------------------------------
   Nizkourovnove funkcie AFTN pre odoslanie dat
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   Zostavenie spravy
  ...........................
}
(*
 type  pole_adries = array[0.._MTK_ADR_LINEs-1] of string;

 procedure naplnenie_adries (adr,prty: string; var adresy: pole_adries; var adries: int);
     var   i,j,pocet : int;
           s,a : string;
     begin
       pocet:= getstritems(adr,[icao_NXIT]);
       i:= 1; adries:= 0;
       while ((adries*_MTK_ADR_hi_pocet)+i<=pocet) and (adries<_MTK_ADR_LINEs) do
         begin
           adresy[adries]:= '';
           j:= 1; a:= '';
           while (j<=_MTK_ADR_hi_pocet) and ((adries*_MTK_ADR_hi_pocet)+i<=pocet) do
             begin
               s:= getstr(adr,i,[icao_NXIT]);
               if j>1 then s:= MTK_2_SPACE + s;
               a:= a + s;
               inc(j);
               inc(i)
             end;
           adresy[adries]:= MTK_2_NL_+prty+MTK_2_SPACE+a+MTK_2_NL_;
           inc(adries)
         end
     end;


 function odoslanie_spravy (prty,adr, CHNL_O,ADR_O: string;
                            data: pchars; size: word;
                            ibits,icom: byte;
                            is_odata: bool; var odata: pchars; var osize: word
                           ): string;

    var   hlavicka  : string;
          adresy    : pole_adries;
          adries    : int;
          adresa    : string;
          odoslal   : string;
          koniec    : string;

          bsize,asize : word;
          bdata,adata : pchars;

          res,pom : string;
          c,i,l,k : int;

    begin

    { odstranenie bielych znakov
    }
      for i:= 0 to size-1 do
       begin
         if data^[i] in MTK_2_CONTROL+[' '] then data^[i]:= ' '
         else begin
                l:= 0; k:= 0;
                while (l<max_MTK_2_abc) and (MTK_2[l,k]<>data^[i]) do
                  begin
                    k:= 0; while (k<max_MTK_2_znk) and (MTK_2[l,k]<>data^[i]) do inc(k);
                    if (k>=max_MTK_2_znk) then inc(l)
                  end;
                if l>=max_MTK_2_abc then data^[i]:= ' '
              end
       end;

      res:= '';
      bdata:= nil; bsize:= 0;
      adata:= nil; asize:= 0;

      INC_CISLO_SPRAVY(CISLO_SPRAVY, AFTN_kod);

    { naplnenie poloziek telegramu
    }
      hlavicka :=   MTK_2_LATIN+MTK_2_SOT+MTK_2_SPACE
                  + CHNL_O+inttostr(CISLO_SPRAVY,3,0)+MTK_2_SPACE
                  + code_l4_utc(hour,min)
                  + MTK_2_INT_                  { obsahuje MTK_2_LATIN }
                  ;

      {adresy  }   naplnenie_adries (adr,prty, adresy,adries);
      adresa   := ''; for i:= 0 to adries-1 do adresa:= adresa+adresy[i];

      if adresa<>'' then
         odoslal  :=   MTK_2_DIGITS+inttostr(day,2,0)+code_l4_utc(hour,min)
                     + MTK_2_LATIN +MTK_2_SPACE + ADR_O
                     + MTK_2_NL_
      else odoslal  := MTK_2_NL_;

      koniec   := MTK_2_EOT_;

      bsize    :=   length(hlavicka)
                  + length(adresa)
                  + length(odoslal)
                  + size
                  + length(koniec);

      getmem(bdata,bsize); fillchar(bdata^,bsize,0); c:= 0;

      move(hlavicka[1], bdata^[c], length(hlavicka)); inc(c,length(hlavicka));
      move(adresa[1],   bdata^[c], length(adresa));   inc(c,length(adresa));
      move(odoslal[1],  bdata^[c], length(odoslal));  inc(c,length(odoslal));
      move(data^[0],    bdata^[c], size);             inc(c,size);
      move(koniec[1],   bdata^[c], length(koniec));   inc(c,length(koniec));

      ascii_to_mtk2bin (bdata,bsize, false {v hlavicke je M2L}, pbytes(adata),asize, true,ibits);

      {IFDEF DEBUG
        getmem(ddata,bsize); move(adata^,ddata^,bsize);
        mtk2bin_to_ascii(pchars(ddata),bsize, ibits);
        freemem(ddata,bsize);
        ENDIF}

      if not SendCOMib(icom,pbytes(adata),asize, true) then res:= 'Error while sending...';

      if is_odata then
         begin
           mtk2bin_to_ascii(adata, asize, ibits);
           osize:= asize; odata:= adata
         end
      else freemem(adata,asize);
      freemem(bdata,bsize);

      odoslanie_spravy:= res
    end;
*)
{$IFDEF DEBUG}
 {$I _ITA2_pkt.inc} { modul z _MTK_2}
{$ENDIF}

 function odoslanie_spravy (prty,adr, CHNL_O,ADR_O: string;
                            data: pchars; size: word;
                            ibits,icom: byte;
                            is_odata: bool; var odata: pchars; var osize: word
                           ): string;

    var   bsize,asize : word;
          bdata,adata : pchars;
          adresati    : pchar;
          res : string;
    begin
      res:= '';
      if cut_(adr)<>'' then
         begin
           adr:= adr+NULL;
           adresati:= @adr[1]
         end
      else adresati:= nil;
      with DEV_AFTN^ do INC_CISLO_SPRAVY (CISLO_SPRAVY, CISLO_SPRAVYcfg);
      if code_ITA2_pkt (CHNL_O,DEV_AFTN^.CISLO_SPRAVY,prty,adresati,ADR_O,
                        data,size,
                        adata,asize,
                        true,ibits,
                        bdata, bsize
                       )
           then
         begin
           if not SendCOMib(icom,pbytes(bdata),bsize, true) then res:= 'Error while sending...';
           if is_odata then
              begin
                mtk2bin_to_ascii(bdata,bsize, ibits);
                osize:= bsize; odata:= bdata
              end
           else freemem(bdata,bsize);
           freemem(adata,asize);
         end
      else res:= 'Error while coding message...';
      odoslanie_spravy:= res
    end;


 function send_to_AFTN (prty,adr,head: string; data: pchars; size: word): string; far;
    begin
      if DEV_AFTN<>nil then send_to_AFTN:= DEV_AFTN^.send_TLG (prty,adr,head, data,size)
      else send_to_AFTN:= ''
    end;


{ ----------------------------------------------------
   Vyssie funkcie EXT pre odoslanie dat
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 function  O_AFTN._send_pkt (typ: byte; adr: string; data: pchars; size: word): bool;
     var   res,prty,tit : string;
           odata : pchars;
           osize : word;
     begin
        _send_pkt:= false;
       if (COMsemaphor[asyncCOM]) then Exit;
       indicate_ext(1);
       {if _scroller_enabled then}
       tit:= get_str(data,size,1,[icao_STD,icao_ARR]+setNL+setNL_,20)+'...';
       InfoCakaj(msgWAITING,msgSEND+': '+tit);
       {---}
       odata:= nil; osize:= 0;
       if typ<max_MTK_2_PRTY then prty:= MTK_2_PRTY[typ] else prty:= '';
       res:= odoslanie_spravy (prty,adr, CHNL_O,ADR_O, data,size, ASYNCbits,ASYNCcom, true, odata,osize);
       if (osize<>0) and (odata<>nil) then
          begin
            writeln_pkt(odata,osize,arch_PKT_SEND,'',cl_s,false,true);
            freemem(odata,osize)
          end
       else writeln_pkt(data,size,arch_PKT_SEND,'',cl_s,false,true);
       {----}
       Ts_:= AbsTime;
       {if _scroller_enabled then}
       InfoCakaj_zatvor;
       indicate_ext(-1);
       _send_pkt:= res=''
     end;


 function O_AFTN.is_pkt_to_ext_line: bool;
    begin
     {$IFDEF BACKUP}
       is_pkt_to_ext_line:= aftn_DUAL_LINE or (not aftn_MASTER_LINE) or is_distribute_pkt;
     {$ELSE}
       is_pkt_to_ext_line:= aftn_DUAL_LINE or (aftn_MASTER_LINE);
     {$ENDIF}
    end;

 function O_AFTN.send_pkt(typ: byte; adr: string; data: pchars; size: word): bool;
    begin
      if is_pkt_to_ext_line then send_pkt:= _send_pkt(typ,adr,data,size)
      else send_pkt:= _send_npkt(typ,adr,data,size)
    end;


{ ‡–‡– †‹€516 2121     Ù–• ‹ ‹†€000Ù
}
 procedure O_AFTN._send_HeartBeat;
     var   s: string;
     begin
       last_HeartBeat:= min;
       if (HeartBeat_ID='') or (not is_pkt_to_ext_line) then Exit;
       s:= HeartBeat_ID+icao_NXIT+CHNL_I+inttostr(0,3,0);
       _send_pkt($FF,'',@s[1],length(s));
       save_last_HeartBeat(last_HeartBeat)
     end;


{ Predpokladame jednu linku na master a backup server;
  nazvy poloziek v hlavicke uplne nesuhlasia s tym, co bude pouzite,
  ale musi sa dodrzat ich poradie a typ dany virtualnou fciou
}

 procedure O_AFTN.send_data (adr: string;

                             head,                    { head }
                             cislo,                   { prty }
                             header_data: string;     { head/typ }

                             data: pchars; size: word;
                             key: string;
                             typ: TNETtyp
                            );
     var   prty,res,s : string;
           adata : pchars; c,asize : word;
           ind : int;
           ishead: bool;
     begin
       prty:= cislo;
       ishead:= (head<>'') and (header_data<>'') and (header_data<>hd_TLG);

       if (head=get_str(data,size,1,[icao_ARR],sizeof(string)-1)) then
          begin
            data:= @data^[length(head+icao_ARR)];
            dec(size,length(head+icao_ARR))
          end;
       asize:= size{+1}{=#0};

       if ishead then inc(asize,3{'(-)'}+length(head));
       getmem(adata,asize); fillchar(adata^,asize,0);
       if ishead then
          begin
            s:= icao_STD+head+icao_ARR;
            move(s[1],adata^[0],length(s));
            c:= length(s)
          end
       else c:= 0;
       move(data^[0],adata^[c],size); inc(c,size);
       if ishead  then
          begin
            s:= icao_END;
            move(s[1],adata^[c],length(s))
          end;

      { priority,... nedokonale prepojenie fcii poplatne navrhu bez aftn;
        pri prepise je potrebne uvazovat z parametrom navyse pre send_data a _send_data
        : head...
        : prty...
      }
       ind:= is_mtkprtyi(prty);
       if ind>=0 then typ:= ind
       else begin
              prty:= mtk_tlg_fdp (typ);
              ind:= is_mtkprtyi(prty);
              if ind>=0 then typ:= ind
              else typ:= high(MTK_2_PRTY);
            end;

       {sended_data:= head;}
       _send_data (typ, adr,'', adata,asize, '',0{AFTN nepotvrdzuje});
       {sended_data:= '';}
       freemem(adata,asize)
     end;


 function O_AFTN.send_TLG (prty,adr,head: string; data: pchars; size: word): string;
    begin
      send_data (adr, head,prty,head, data,size,'',0);
      send_TLG:= ''
    end;


 procedure O_AFTN.send_LAM(data: pchars; size: word; head: string);
     begin
      { AFTN nepotvrdzuje
      }
     end;
