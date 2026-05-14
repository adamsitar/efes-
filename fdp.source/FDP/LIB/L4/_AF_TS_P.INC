{$IFDEF PLN}


{ -------------------------------------------------------------
   Spracovanie sprav PLN o povolenych letoch
  -------------------------------------------------------------
}

{ Urcenie, ci je to sprava PLN a ci ma prislusne nalezitosti ?
}
 function O_AFTN_TSGA._is_PLN (data: pchars; size: word;
                               var riadkov,riadok: int;
                               var date: TDate;
                               var res: string
                              ): bool;

    var   i,p,j,k, ires : int;
          soh1,soh2,eoh, s0,s1,s2 : string;
          is,isd : bool;

    label X;

    begin
      riadkov:= 0; riadok:= 0;
      _is_PLN:= false;

     { Je to PLN ?
     }
      soh1:= delchar(soh1_PLN,[icao_NXIT]);
      soh2:= delchar(soh2_PLN,[icao_NXIT]);
      i:= 1; is:= false; p:= get_str_items(data,size, setNL);
      while (i<p) and (not is) do
        begin
          s0:= get_str(data,size, i, setNL, sizeof(s0)-1);
          s1:= delchar(s0,[icao_NXIT]);
          s2:= get_str(data,size, i+1, setNL, sizeof(string)-1);
          s2:= delchar(s2,[icao_NXIT]);
          is:= (soh1=copy(s1,1,length(soh1))) and (soh2=s2);
          inc(i)
        end;
      if is then begin riadkov:= p; riadok:= i+1 end
      else Exit;


      _is_PLN:= true;
      InfoCakaj(msgWAITING,tit_PLN_CHECK);

     { PLN urceny pre dane pracovisko ?
     }
      if pln_ADR then
         begin
           soh1:= copy(s0,length(soh1_PLN)+1,length(s0)-length(soh1_PLN));
           i:= 1; is:= false; p:= getstritems(adr_PLN,[icao_NXIT]);
           while (i<=p) and (not is) do
             begin
               is:= pos(icao_NXIT+getstr(adr_PLN,i,[icao_NXIT])+icao_NXIT,soh1)>0;
               inc(i)
             end;
           if not is then
              begin
                l4_err(a_PLN,'',0,err_pln_other_adress,res);
                goto X
              end
         end;

     { Spravny datum platnosti ?
     }
      fillchar(date,sizeof(date),0);
      isd:= false; j:= 1; k:= getstritems(s0,[icao_NXIT]);
      while (j<=k) and (not isd) do
        begin
          s1:= getstr(s0,j,[icao_NXIT]);
          isd:= GetDateStr_(date.r,date.m,date.d, s1, false, ['.','/']);
          inc(j)
        end;
      if (res='') and (not isd) then
         begin
           l4_err(a_PLN,'',0,err_pln_unknown_date,res);
           goto X
         end;

      if (res='') and (DateToSec(year,month,day) > DateToSec(date.r,date.m,date.d)) then
         begin
          {$IFDEF DEBUG}
           init_date (date, year,month,day);    { Ladit treba }
          {$ELSE}
           l4_err(a_PLN,'',0,err_pln_validity,res);
           goto X
          {$ENDIF}
         end;

      X: InfoCakaj_zatvor;
    end;


{ Funkcia pre zaradenie PLN ako planov FPL4 na dany den :
  - postupne sa spracovavaju vsetky polozky zoznamu
  - z kazdej sa vytvori FPL4 a ulozi sa (nenaplnene udaje sa doplnia na zaklade cfg)
  - kontrola spravnosti planu sa vykona pri aktivovani planu
}

 const PLNkod = 'PLN'+ext_kod;

 procedure save_last_pln (date: TDate; size,riadok: int; data: string);
     var   t: text;
     begin
       assign(t,PLNkod); rewrite(t);
       writeln(t,code_l4_date(date));
       writeln(t,cstr(size,5));
       writeln(t,cstr(riadok,2));
       writeln(t,data);
       close(t);
     end;

 function read_last_pln (var date: TDate; var size,riadok: int; var data: string): bool;
    var   t: text;
          i: int;
    begin
      read_last_pln:= false;
      if Exists(PLNkod)<>0 then Exit;

      assign(t,PLNkod); reset(t);
      readln(t,data); decode_l4_date(data,date);
      readln(t,data); val(data,size,i);
      readln(t,data); val(data,riadok,i);
      readln(t,data);
      close(t);

      read_last_pln:= true
    end;


 type  p_pln_data = ^type_pln_data;
       type_pln_data = record

        { odkazy
        }
         aftn : P_AFTN_TSGA;

        { data
        }
         data : pchars;
         size : word;
         date : TDate;

         eoh  : string;
         res  : pstring;

         riadkov,
         riadok : int;

       end;


 function _spracuj_PLN (data: p_pln_data; {riadok: pint; riadkov: int;} i: PProcess): bool;
    var   PLN : DPLN;
          s   : string;
          is  : bool;
    begin
      is:= true;
      s:= cut_(get_str(data^.data,data^.size, data^.riadok,setNL,sizeof(s)-1));
      if (s<>MTK_2_EOT) and (data^.riadok < data^.riadkov) then
         begin
           if (data^.eoh<>copy(s,1,length(data^.eoh))) then
              begin
                if i<>nil then i^.new_item(s);
                save_last_pln (data^.date, data^.size,data^.riadok,s);
                is:= decode_PLN_aftn_tsga (s,data^.date,PLN,pln_FPL,data^.res^);
                if is then
                   begin
                     zarad_PLN(@PLN,'',true,aftn);
                     inc(data^.riadok);
                   end;
                disp_PLN(@PLN);
              end
           else data^.riadok:= data^.riadkov;
         end;
      _spracuj_PLN:= (s=MTK_2_EOT) or (data^.riadok >= data^.riadkov) or (not is {data^.res<>''})
    end;


 function O_AFTN_TSGA._decode_PLN (data: pchars; size: word;
                                   riadkov,riadok: int;
                                   date: TDate;
                                   var res: string
                                  ): bool;
    var   d : type_pln_data;
          ldate : TDate;
          lsize,lriadok : int;
          ldata : string;
          b : bool;
    begin
      _decode_PLN := false;

     { naplnenie udajov pre spracovanie
       a volanie ext fcie spracovania
       (dekodovanie a zaradenie)
     }
      d.aftn:= @self;
      d.data:= data;
      d.size:= size;
      d.date:= date;
      d.eoh := delchar(eoh_PLN,[icao_NXIT]);
      d.res := @res;
      d.riadkov:= riadkov;
      d.riadok := riadok;


     { mozem vyhladat poslednu spracovavanu poziciu,
       ak bolo spracovanie prerusene, aby sa znova
       neradili uz spracovane plany
     }
       if     read_last_pln (ldate,lsize,lriadok,ldata)
          and eq_date(ldate,date)
          and (lsize=size)
          then
            begin
              d.riadok := lriadok + 1;
            end;


     { fcia pre spracovanie, dovoluje ho prerusit
     }
      b:= __INFO_DB; __INFO_DB:= false;
      if InfoProcess (tit_PLN_ITEM+':',titDLA,'',cut_(get_str(data,size, d.riadok,setNL,sizeof(string)-1)),
                      @_spracuj_PLN, @d{,
                      riadkov,@riadok}
                     )
         then
           begin
             DelFile(PLNkod)
           end;
      __INFO_DB:= true;

      _decode_PLN:= (res='') and (d.riadkov<=d.riadok)
    end;


{ -------------------------------------------------------------
   Spracovanie sprav PLN
  -------------------------------------------------------------
}
 procedure O_AFTN_TSGA._save_PLN(data: pchars; size: word; tit,fn: string; from: TNETadr);
     var   D : DirStr;
           N : NameStr;
           E : ExtStr;
     begin
       if fn='' then
          begin
            fn:= _fn_data(data,size);
            FSplit(fn,D,N,E);
            fn:= pathTLG+N+'.'+extPLN
          end;
       if tit<>'' then
          begin
            if tit[length(tit)]='.' then tit:= copy(tit,1,length(tit)-1);
            tit:= ' ('+tit+')';
          end;
       tit:= tit_PLN_PENDED+tit+'.';
       _save_txt_file (fn,tit, data,size, true);
       {$IFDEF SYNCHRONIZE_EXT}
       { posle na backup stanice,
         pretoze ta ma zakazene spracovavat pakety z externej sete
       } if is_distribute_pkt then distribute_pkt (data,size, tit,fn, spr_AFTN_PLN,from, true);
       {$ENDIF}
       is_PLN:= true;
     end;

 procedure  O_AFTN_TSGA._read_PLN;
     begin
       semaphor_pln:= true;
       _read_TLG(extPLN,@check_pln_editor,@init_pln_editor,@handle_pln_editor,0);
       is_PLN:= najstarsi_subor(pathTLG,'*.'+extPLN)<>'';
       semaphor_pln:= false;
     end;


{ spracovanie v prijimacom dekoderi "process_TLG"
}
 function O_AFTN_TSGA._process_PLN (src: TPKT_SRC; data: pchars; size: word; var res: string): bool;
    var   riadkov,riadok: int;
          prty: string;
          dat: TDate;
          is: bool;
    begin
      res:= '';
      _process_PLN:= false;
      if not _is_PLN (data,size, riadkov,riadok,dat, res) then Exit;

      _process_PLN:= true;

      {$IFDEF BACKUP}
        if SERVERstatus and (src in [src_ext,src_net]) then
           begin
             res:= '';
             Exit
           end;
      {$ENDIF}

      if (src in [src_ext,src_net]) then
         begin
           if pln_PND then
              begin
                _save_PLN (data,size, res,'', '');
                res:= '';
                Exit
              end;
         end;

      if res='' then _process_PLN:= _decode_PLN (data,size, riadkov,riadok, dat, res);

      if (res<>'') and (src in [src_ext,src_net]) then
         begin
           if pln_ERR then process_ERR_DATA(src, data,size,res,src=src_ext,src=src_ext,src=src_ext)
           else begin
                  prty:= is_prty(data,size,res);
                  _process_TLG (data,size,prty,true)
                end;
           res:= ''
         end
    end;


{ automaticke prinutenie ku spracovaniu odlozenych/nespracovanych
  sprav PLN
}
 procedure O_AFTN_TSGA.manage_PLN;
     const h : byte = 24;
           d : byte = 0;
     begin
       if (h<>hour) or (d<>day) then
           begin
             {if d=0 then is_pend_PLN:= najstarsi_subor(pathTLG,'*.'+extPLN)<>'';}
             {if (hour>=23) or ((d<>0) and (day>=d)) then _read_PLN (true);}
             is_PLN:= najstarsi_subor(pathTLG,'*.'+extPLN)<>'';
             h:= hour; d:= day;
           end;
       if (not semaphor_pln) and is_PLN and (h>=23) {or ((d<>0) and (day>=d))} then _read_PLN;
     end;

{$ENDIF}
