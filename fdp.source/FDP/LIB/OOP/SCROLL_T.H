    type    TBFunc_vEpi = function (var E: TEvent; p: pointer; i: int): bool;

            TBFunc_p    = function (p: pointer): bool;
            TBFunc_p2   = function (sc: PScroller; item_adr: pointer): bool;
            TBFunc_vEp2 = function (var E: TEvent; sc: PScroller; item_adr: pointer): bool;

            TBFunc_p3   = function (sc: PScroller; item_adr: pointer; par_adr: pointer): bool;
            TBFunc_vEp3 = function (var E: TEvent; sc: PScroller; item_adr: pointer; par_adr: pointer): bool;

            TScrollAct_handler_type = (_TNull,
                                       _TBFunc_i,_TBFunc_pi,_TBFunc_vEpi,
                                       _TBFunc_p,_TBFunc_p2,_TBFunc_vEp2,
                                       _TBFunc_vEp3,
                                       _TIFunc_s
                                      );
