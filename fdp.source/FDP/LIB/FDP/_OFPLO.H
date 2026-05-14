    {
    ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
    €                                                          €
    € inie letovie plany                                       €
    €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
    }

   {$IFDEF FPLO}
    type  PaFPL = ^OaFPL;
          OaFPL = object(OmFPL)

            constructor Init(_items : word;
                             _en_net: bool;

                             var _p_PRN   : bool;

                             {$IFDEF EDD}
                              _accepted : bool;
                              _adrBOARD : PPObject;
                              _cmADD,_cmCHG,_cmDEL,_cmCLR: word;
                             {$ENDIF}

                             {$IFDEF OPL}
                              _p_pre_i, _p_pre_iot,
                              _p_pro_i, _p_pro_iot,
                              _p_coo_i, _p_coo_iot,
                                        _p_act_iot,

                              _p_prop_day, _p_cnl_day : pbool;
                             {$ENDIF}

                             _p_formular : pointer;
                             _p_handler  : pointer
                            );

            function  is_plan(p: pointer): bool; virtual;

            {$IFDEF EDD}
             function  zarad (ind: int; is: TSpecGroups): string; virtual;
             function  smer(ind: int): Ts_dir; virtual;
            {$ENDIF}
          end;
   {$ENDIF}