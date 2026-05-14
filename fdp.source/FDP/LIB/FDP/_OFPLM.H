    {
    ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
    €                                                          €
    € vojensky letovy plan                                     €
    €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
    }

    type  PmFPL = ^OmFPL;
          OmFPL = object(O_FPL)

            {$IFDEF OPL}
             p_pre_i, p_pre_iot,
             p_pro_i, p_pro_iot,
             p_coo_i, p_coo_iot,
                      p_act_iot,

             p_prop_day, p_cnl_day : pbool;

             pre_i, pre_iot,
             pro_i, pro_iot,
             coo_i, coo_iot,

             act_iot,

             prop_day,
             cnl_day   : bool;
            {$ENDIF}


             constructor Init(_items  : word;
                              _en_net : bool;

                              var _p_PRN   : bool;

                              {$IFDEF EDD}
                               _accepted : bool;
                               _adrBOARD : PPObject;
                               _cmADD,_cmCHG,_cmDEL,_cmCLR : word;
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


            procedure plan_added (p: pointer); virtual;   { bol zaradeny plan }
            procedure plan_deleted; virtual;              { opak }

            procedure format_data_variables (p: pointer); virtual;

            {$IFDEF OPL}
             function  sort: bool; virtual;

             function  test_na (na: bool): bool;
             function  zmenene_parametre_platnosti: bool; virtual;
             function  cas_pre_preaktivaciu_planov: bool; virtual;
            {$ENDIF}


            function  urc_platnost(p: pointer; var zmena: bool; kresli: bool): Tpoz; virtual;
            function  is_plan (p: pointer): bool; virtual;


            function  get_poz (p: pointer): Tpoz; virtual;
            procedure set_cor (p: pointer; cor: int); virtual;
            function  get_cor (p: pointer): int; virtual;
            procedure cl_cor  (p: pointer); virtual;
            {$IFDEF NET}
             function  get_rec(p: pointer): Pplan_rec; virtual;
            {$ENDIF}


            {$IFDEF MAPY}
             {protected}
             procedure get_sur(p: pointer; var sur: Tsur); virtual;
             procedure set_sur(p: pointer; sur: Tsur); virtual;

             function  _target_coordinates(p: pointer; cas: real; var sur: Tsur): Tpoz; virtual;

             public
             function  get_mapa(p: pointer): PMapData; virtual;
             procedure set_mapa(p: pointer; mapa: PMapData); virtual;
             procedure get_mapa_par(p: pointer;
                                    var Trat: POBxys; var bodov: int;
                                    var Trat_: POBxys; var bodov_: int;
                                    var MapNaz: string
                                   ); virtual;
            {$ENDIF}


            {$IFDEF EDD}
             public
             function  zarad (ind: int; is: TSpecGroups): string; virtual;
             function  smer  (ind: int): Ts_dir; virtual;

             function  ETO   (ind: int): real;   virtual;
             function  ETD   (ind: int): real;   virtual;
             function  ETA   (ind: int): real;   virtual;
             function  FL    (ind: int): real;   virtual;
            {$ENDIF}


            {$IFDEF RDP_ACCEPT}
             function  get_accept(p: pointer; var ACPT: TTRG_stat; var RDP: TRTRadr): TTRG_stat; virtual;
             procedure set_accept(p: pointer; TRG: TTRG_stat; RDP: TRTRadr); virtual;
            {$ENDIF}
          end;
