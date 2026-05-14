{ Skontroluje, ci
  LSRLP - ziadost o vydanie pripomienky k letu
  MACC  - spracovanie ziadosti o vydanie pripomienky k letu
}
 procedure spracuj_pripomienky_ku_FPLM;
     const semaphor : bool = false;
     begin
       if (not semaphor) then
          begin
            semaphor:= true;
            {$IFDEF AIRBASE}
             spracuj_pripomienky_ku_FPL;
            {$ENDIF}
            {$IFDEF MACC}
             spracuj_ziadosti_o_pripomienky_ku_FPL;
            {$ENDIF}
            semaphor:= false
          end;
     end;


 function _is_REQ(FPL: PDmFPL; s: Pstring): bool; far;
    var   cond : string;
    begin
     _is_REQ:=    _FPLM.__plan_pre_pracovisko(FPL,false)
               and (_is_stat(FPL^.stat,cnst_disk+cnst_sended+cnst_FPL_REQ,false));
    end;

 function _is_REQ2(FPL: PDmFPL; s: Pstring): bool; far;
    var   cond : string;
    begin
     _is_REQ2:= _FPLM._plan_pre_pracovisko(FPL) and (_is_stat(FPL^.stat,cnst_dec+cnst_acc,false));
    end;

 function _REQ_FPL(sc: PScroller; FPL: PDmFPL): bool; far;
    begin
     {$IFDEF AIRBASE}
      formular_pre_vyziadanie_pripomienky_ku_FPLM (FPL);
     {$ENDIF}
     {$IFDEF MACC}
      formular_pre_vydanie_pripomienky_ku_FPLM (FPL,false);
     {$ENDIF}
      _REQ_FPL:= false
    end;


 procedure mFPL_REQ;
     begin
       spracuj_mFPL(find_and_process_FPLM,false,
                    false,false,false,true,
                    '', @_is_REQ,
                    @_REQ_FPL,_TBFunc_p2,
                    true,false,
                    msg_FPL_REQ, nil,hlp_mFPL_REQ
                   )
     end;


 function _REQ2_FPL(sc: PScroller; FPL: PDmFPL): bool; far;
    begin
      _REQ2_FPL:= _REQ2_FPL(sc,FPL)
    end;

 procedure mFPL_REQ2;
     begin
       spracuj_mFPL(find_and_process_FPLM,false,
                    false,false,false,true,
                    '', @_is_REQ2,
                    @_REQ_FPL,_TBFunc_p2,
                    true,false,
                    msg_FPL_REQ, nil,hlp_mFPL_REQ
                   )
     end;
