      function  _handle_event_FPL (var _Event: TEvent; O: PObject; FPL: pointer): bool; far;


      procedure spracuj_cFPL(_FN: string;
                             _find_and_process_data : bool;
                             _FNfunc: pointer; _FNfunc_p: pointer;
                             _data_filter : pointer; _filter : pointer;
                             _handler : pointer; _handler_type: TScrollAct_handler_type;
                             _title: string; _info: pchar; _hlpXXX : Pchar
                            );

      function  _handle_plan_FPLC (var Ev: TEvent;
                                   FPLi: PDcFPL; oFPL: P_OFPL;
                                   sc: PScrollInd; dx,dy: int;
                                   _plan,_vis: bool
                                  ): bool;
      function  handle_strip_FPLC (var Ev: TEvent; sc: PScrollInd; FPLi: PDcFPL; oFPL: P_OFPL): bool; far;
      function  handle_plan_FPLC  (var Ev: TEvent; sc: PScrollInd; FPLi: PDcFPL): bool; far;

      function  handle__spracuj_ukoncene_cFPL (FPL: PDcFPL): bool; far;


      {$IFNDEF FPLM_DISABLED}
       procedure spracuj_mFPL(_find_and_process_data,_find_cnl_data,
                             _ppl,_arch,_rpl,_fpl : bool;

                             _data_filter : string; _filter : pointer;
                             _handler : pointer; _handler_type : TScrollAct_handler_type;

                             _print,_send : bool;
                             _title: string; _info: pchar; _hlpXXX : Pchar
                            ); far;

       procedure load_mFPL (FN: string; pm,po: P_OFPL);


       {$IFDEF PROCESS_FPLM} {$IFDEF OPL}
         procedure spracuj_pripomienky_ku_FPLM;
       {$ENDIF} {$ENDIF}


       function  _handle_plan_FPLM (var Ev: TEvent; FPLi: PDmFPL; oFPL: P_OFPL; sc: PScrollInd; dx,dy: int; _plan: bool): bool;
       function  handle_strip_FPLM (var Ev: TEvent; sc: PScrollInd; FPLi: PDmFPL; oFPL: P_OFPL): bool; far;
       function  handle_plan_FPLM  (var Ev: TEvent; sc: PScrollInd; FPLi: PDmFPL): bool; far;


       function  handle__spracuj_ukoncene_mFPL (FPL: PDmFPL): bool; far;
      {$ENDIF}


      {$IFDEF RDP_ACCEPT}
        procedure FL_ACCEPT     (idn: string; RDP: word);
        procedure FL_UNACCEPT   (idn: string; RDP: word);
        procedure FL_A_HANDOVER (idn: string; RDP: word);
        procedure FL_U_HANDOVER (idn: string; RDP: word);
      {$ENDIF}
