 function  formular_RPL_ (RPL: PRPL; tit: string; novy: bool): bool;
    begin
     {$IFDEF PROCESS_RPL}
      if p_form_RPL<>nil then formular_RPL_:= func_rpl_form (p_form_RPL) (RPL,tit,novy)
      else
     {$ENDIF}
      formular_RPL_:= false
    end;


(*{ kontroly na jednoznacnost spracovania
}
 function existuje_RPL(RPL: PRPL; _zobraz: bool): bool;
    begin
      existuje_RPL:=
              (find_RPL(RPL,nil)<>-1)
        and   (    (not _zobraz)
                or ( Ask2(msgWARNING,
                        inf_plan+' '+RPL^._7a+'-'+RPL^._13a
                        + ' '+inf_exist+' '+ask_prepisat,
                        '',White,clBUTTON_COLOR,waitASK*18
                        ) <> ansAno
                   )
              )
    end;


 function zmeneny_RPL(RPL: PRPL; _zobraz: bool): bool;
    var   RPLn: DRPL;
          bres: bool;
    begin
      if read_RPL(codekey_RPL(RPL),@RPLn)>=0 then
         begin
           bres:= chg_RPL(RPL,@RPLn);
           if bres and _zobraz then
              begin
                info_RPL(@RPLn, tit_zmeneny_plan);
                bres:= not (Ask2(msgWARNING, tit_zmeneny_plan+' '+ask_prepisat,'',White,clBUTTON_COLOR,waitASK*18)=ansAno)
              end;
           zmeneny_RPL:= bres;
           disp_RPL(@RPLn)
         end
      else zmeneny_RPL:= false
    end;

*)

 function _zarad_RPLF (RPL: PRPLF;
                       check_par: word; _send: bool; _src: fdp_src;
                       var res: string; var ires: int
                      ): bool;
    var   dbres : int;
          _7x : string;
    begin
      _zarad_RPLF:= false;
      res:= ''; ires:= -1;

     { nacitanie povodneho
      dbres:= DB_najdi (RPLF, get_RPLfn(RPL),db_RPLF_RIADKOV,@decodeDB_RPLF,@codekey_RPLF,true,@disp_RPLF);
      disp_RPL (@RPLF.rpl);
      new_RPL (RPL,@RPLF.rpl);
      if (dbres<0) or (check_par and cm_decode_RPL_FPL4 <> 0) then
         begin
           disp_RPL (@RPLF.fpl);
           code_RPL_to_FPL4_ (RPL,RPLF.fpl,nil);
           format_FPL4new(@RPLF.fpl);
         end;
      DB_zapis(RPLF,dbres
               get_RPLfn(@RPL^.rpl),
               db_RPLF_RIADKOV,@codeDB_RPLF,@codekey_RPLF,
               @dbchg_RPLF, dbattr_RPLF
              );
      }
      if (check_par and cm_decode_RPL_FPL4 <> 0) or (RPL^.fpl._7='') then
         begin
           disp_FPL4(@RPL^.fpl);
           ires:= code_RPL_to_FPL4_FDR_ (RPL^.rpl,RPL^.fpl,rpl_ERR,res);
         end;

      if (res='') or (not rpl_ERR) then
         begin
           if (check_par and cm_check_RPL_KEY <> 0) or (RPL^.rpl._7x=' ') or (RPL^.rpl._7x='') then
              begin
                _7x:= read_RPLx (RPL^.rpl._7a);
                {if _7x<>'' then}
                   if cut_(_7x)='' then RPL^.rpl._7x:= 'A'
                   else RPL^.rpl._7x:= succ(_7x[1])
              end;

           DB_oprav(RPL,
                 get_RPLfn(@RPL^.rpl),
                 db_RPLF_RIADKOV,@codeDB_RPLF,@codekey_RPLF,
                 @dbchg_RPLF, dbattr_RPLF
                );

           if (p_rpl_dbscroller<>nil) then p_rpl_dbscroller^.data_update(@RPL^.rpl);
         end;
      _zarad_RPLF:= res=''
    end;


 function _zarad_RPL (RPL: PRPL;
                      check_par: word; _send: bool; _src: fdp_src;
                      var res: string; var ires: int
                     ): bool;
    var   RPLF : DRPLF;
    begin
      fillchar (RPLF,sizeof(RPLF),0);
      new_RPL (RPL,@RPLF.rpl);
      _zarad_RPL:= _zarad_RPLF (@RPLF, check_par {cm_zarad_RPL or cm_decode_RPL_FPL4},_send,_src, res,ires);
      disp_RPLF (@RPLF);
    end;


{ function zarad_RPL (RPL: PRPL; _stat: string; _send: bool; _src: fdp_src): bool;
    begin
      zarad_RPL:= _zarad_RPL (RPL, 0,_stat,_send,_src);
    end;
}