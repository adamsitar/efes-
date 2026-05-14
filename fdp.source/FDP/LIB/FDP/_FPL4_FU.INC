 function  formular_FPL4_ (FPL: PFPL4; tit: string; novy: bool): bool;
    begin
      if p_form_fpl4<>nil then formular_FPL4_:= func_fpl4_form (p_form_FPL4) (FPL,tit,novy)
      else formular_FPL4_:= false
    end;


{ kontroly na jednoznacnost spracovania
}
 function existuje_FPL4(FPL: PFPL4; _zobraz: bool): bool;
    begin
      existuje_FPL4:=
              (find_FPL4(FPL,nil)<>-1)
        and   (    (not _zobraz)
                or ( Ask2(msgWARNING,
                        inf_plan+' '+decode_l4_7a(FPL^._7)+'-'+decode_l4_13a(FPL^._13)
                        + ' '+inf_na_den+' '+DateToStr2(FPL^.date.d,FPL^.date.m,0)
                        + ' '+inf_exist+' '+ask_prepisat,
                        '',White,clBUTTON_COLOR,waitASK*18
                        ) <> ansAno
                   )
              )
    end;


 function zmeneny_FPL4(FPL: PFPL4; _zobraz: bool): bool;
    var   FPLn: DFPL4;
          bres: bool;
    begin
      if read_FPL4(codekey_FPL4(FPL),@FPLn)>=0 then
         begin
           bres:= chg_FPL4(FPL,@FPLn);
           if bres and _zobraz then
              begin
                info_FPL4(@FPLn, tit_zmeneny_plan);
                bres:= not (Ask2(msgWARNING, tit_zmeneny_plan+' '+ask_prepisat,'',White,clBUTTON_COLOR,waitASK*18)=ansAno)
              end;
           zmeneny_FPL4:= bres;
           disp_FPL4(@FPLn)
         end
      else zmeneny_FPL4:= false
    end;



  procedure _zaradenie_FPL4 (FPL: PFPL4;
                             var check_par: word; _stat: string; _src: fdp_src;
                             var res: string; var ires: int;
                             dbind: pint                      { index v db ! }
                            );                 { smie sa pouzit vo volani "zarad" ! }
      var   i,ind: int;
            is_ind: bool;
      begin
        if (check_par=0) and (FPL^.data<>nil) then check_par:= FPL^.data^.cmnd;

       { vypocet premennych pre fpld, najma datumu a casu preletu eet
       } _format_FPL4new (FPL,check_par,res,i,is_ind,ind);

       { dalsie spracovanie ->
         - zaradenie FDR do zoznamu dennych planov
         - zaradenie FPLC, ak je let aktivovany alebo zrusene
         - zaradenie FPLC do statistiky
         - odoslanie FLI...
         vykonavaju zretazene funkcie
       }
        if p_zarad_FPL4<>nil then proc_zarad_FPL4(p_zarad_FPL4)(FPL,check_par,_stat,_src,res,ires,dbind);

       { ulozenie
       } if check_par and cm_zarad_FPL4 <> 0 then
            begin
              if is_ind then dbind:= @ind;
              save_FPL4_(FPL,dbind);
            end;

       { rozoslanie
       } if check_par and cm_rozosli_FPL4 <> 0 then distribute_FPL4(FPL,[],[]);
         if check_par and cm_rozosli_FPL4_EXT <> 0 then { AFTN };
     end;


 function _zarad_FPL4 (FPL: PFPL4; check_par: word; _stat: string; _send: bool; _src: fdp_src): bool;
    var   res: string;
          ires: int;
          dbind: pint;
    begin
      if _stat<>'' then
         begin
           FPL^._3:= _stat;
           FPL^.stat:= _stat;
         end;

     ires:= -1; dbind:= nil;
     {$IFDEF FPL4_ACT}
      if (FPL^.data<>nil) and (FPL^.data^.cmnd<>0) then check_par:= FPL^.data^.cmnd
      else if (check_par=0) then check_par:= cm_zarad_FPL4 or cm_rozosli_FPL4;
      _zaradenie_FPL4 (FPL,check_par,_stat,_src,res,ires,dbind);
     {$ELSE}
      save_FPL4_(FPL,nil);
      if _send then distribute_FPL4(FPL,[],[]);
     {$ENDIF}

     if (p_fpl4_dbscroller<>nil) then p_fpl4_dbscroller^.data_update(FPL);

      _zarad_FPL4:= true;
    end;


 function zarad_FPL4 (FPL: PFPL4; _stat: string; _send: bool; _src: fdp_src): bool;
    begin
      zarad_FPL4:= _zarad_FPL4 (FPL, 0,_stat,_send,_src);
    end;
