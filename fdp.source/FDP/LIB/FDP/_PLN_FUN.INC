
 function _zarad_PLN (PLN: PPLN; _send: bool; _src: fdp_src; _fpl4: bool): bool;
    var   ires : int;
          bres : bool;
          PLNi : DPLN;
    begin
      _zarad_PLN:= false;
      ires:= read_PLN(codekey_PLN(PLN),@PLNi);
      if (ires>-1) then
         begin
           bres:= chg_PLN (PLN,@PLNi);
           disp_PLN (@PLNi);
           if not bres then Exit
         end;
      DB_zapis(PLN,ires,get_DBfn(PLN^.date, pathFPL,extPLN), db_PLN_RIADKOV,@codeDB_PLN,@codekey_PLN, @dbchg_PLN, dbattr_PLN);

      { IFDEF PROCESS_FPL4}
       if _fpl4 and (p_zarad_PLN_FPL4<>nil) then TProc_p(p_zarad_PLN_FPL4)(PLN);
      { ENDIF}

      if _send then _odosli_PLN(PLN,_src);

      if (p_pln_dbscroller<>nil) then p_pln_dbscroller^.data_update(PLN);
    end;

 function zarad_PLN(PLN: PPLN; _stat: string; _send: bool; _src: fdp_src): bool;
    begin
      zarad_PLN:= _zarad_PLN(PLN,_send,_src,true)
    end;


 {procedure _add_PLN (PLN: PPLN; check_par: word; var res: string; var ires: int);
     begin
       res:= ''; ires:= 0;
       save_PLN (PLN);
       distribute_PLN(PLN,[],[])
     end;

  procedure add_sPLN (spln: string; dat: TDate);
     begin
       save_sPLN (spln,dat)
     end;
 }


