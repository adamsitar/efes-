      {$IFDEF FDP_OPL}
        function  handle_strip_FPLc_BvEp3 (var Ev: TEvent; sc: PScrollInd; FPL:  PDcFPL; iFPL: P_OFPL): bool;

        function  _handle_plan_FPLm (var Ev: TEvent; sc: PScrollInd; dx,dy: int; FPLi: PDmFPL; iFPL: P_OFPL): bool;

        function  handle_strip_FPLm (var Ev: TEvent; sc: PScrollInd; FPLi: PDmFPL; iFPL: P_OFPL): bool;
      {$ENDIF}

      procedure spracuj_cFPL(_FN: string;
                             _find_and_process_data : bool;
                             _FNfunc: pointer; _FNfunc_p: pointer;
                             _data_filter : pointer; _filter : pointer;
                             _handler : pointer; _handler_type: TScrollAct_handler_type;
                             _title: string; _info: pchar; _hlpXXX : Pchar
                            );

      procedure spracuj_mFPL(_FN : string; _dbchg: pointer; {_FNfunc: pointer; _FNfunc_p: pointer;}
                             _find_and_process_data : bool;
                             _data_filter : string; _filter : pointer;
                             _handler : pointer; _handler_type : TScrollAct_handler_type;
                             _print, _send, _fpl : bool;
                             _title: string; _info: pchar; _hlpXXX : Pchar
                            ); far;

      function  handle__spracuj_ukoncene_cFPL(FPL: PDcFPL): bool; far;
      function  handle__spracuj_ukoncene_mFPL(FPL: PDmFPL): bool; far;

      function  _handle_event_FPL (var _Event: TEvent; O: PObject; FPL: pointer): bool; far;
