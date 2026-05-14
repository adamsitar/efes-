    {
    ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
    €                                                          €
    € civilny letovy plan                                      €
    €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
    }

    type { ------------------------- }
         { civilny FPL               }
         { ------------------------- }
           PcFPL = ^OcFPL;
           OcFPL = object(O_FPL)

             is_FPLC_CPL: bool;

             constructor Init(_items  : word;
                              _en_net : bool;
                              var _p_PRN : bool;

                              {$IFDEF EDD}
                               _accepted : bool;
                               _adrBOARD : PPObject;
                               _cmADD,_cmCHG,_cmDEL,_cmCLR : word;
                              {$ENDIF}

                              _p_formular : pointer;
                              _p_handler  : pointer
                             );


             function  is_plan(p: pointer): bool; virtual;
             procedure format_data_variables(p: pointer); virtual;
             function  Eq(ind: int; p: pointer): bool; virtual;

             function  zmenene_parametre_platnosti: bool; virtual;

             procedure set_cor(p: pointer; cor: int); virtual;
             function  get_cor(p: pointer): int; virtual;
             procedure cl_cor (p: pointer); virtual;

             function  get_priznak (p: pointer): byte; virtual;
             procedure set_priznak (p: pointer; przn: byte; save: bool); virtual;

             function  is_to_chg(p1,p2: pointer): bool; virtual;

             {protected}
             function  get_poz(p: pointer): Tpoz; virtual;
             function  urc_platnost(p: pointer; var zmena: bool; kresli: bool): Tpoz; virtual;

             procedure plan(p: pointer); virtual;

             {$IFDEF NET}
               function  get_rec(p: pointer): Pplan_rec; virtual;
             {$ENDIF}

             {$IFDEF OPL}
               function  sort: bool; virtual;
             {$ENDIF}


             {$IFDEF SECTORS}
               function  get_on_sector  (p: pointer): bool; virtual;
               procedure set_on_sector  (p: pointer; _on_sector: bool); virtual;

              {$IFDEF PRN}
               function  get_printed    (p: pointer): bool; virtual;
               procedure set_printed    (p: pointer; was: bool); virtual;
              {$ENDIF}

               function  urc_platnostS  (p: pointer): bool; virtual;
               function  let_cez_sektor (p: pointer): bool; virtual;
               function  let_v_sektore  (p: pointer; _limit: real): bool; virtual;
               function  platnost_letu_v_sektore (p: pointer; zmena_sektorizacie: bool): bool; virtual;
             {$ENDIF}


             {$IFDEF MAPY}
               {protected}
               procedure get_sur(p: pointer; var sur: Tsur); virtual;
               procedure set_sur(p: pointer; sur: Tsur);     virtual;

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
               function  zarad_inde(ind: int; is: TSpecGroups; res: string): string; virtual;
               function  smer  (ind: int): Ts_dir; virtual;

               function  NDB   (ind: int): string; virtual;
               function  ETO   (ind: int): real;   virtual;
               function  ETD   (ind: int): real;   virtual;
               function  ETA   (ind: int): real;   virtual;
               function  FL    (ind: int): real;   virtual;
             {$ENDIF}

             {$IFDEF RDP_ACCEPT}
               function  get_accept (p: pointer; var ACPT: TTRG_stat; var RDP: TRTRadr): TTRG_stat; virtual;
               procedure set_accept (p: pointer; TRG: TTRG_stat; RDP: TRTRadr); virtual;
             {$ENDIF}

             {$IFDEF FLI_COORDINATION}
               function  coordinate_FLI: bool;
               function  coordinate_FLI_ERR (var display_FLI_ERR: bool): bool; virtual;
             {$ENDIF}

             procedure  plan_zruseny (p: pointer); virtual;
           end;


    {const  _MAX_cFPLs = MAX_PTRs;

    type   PcFPLs = ^TcFPLs;
           TcFPLs = array[0.._MAX_cFPLs-1] of PDcFPL;}


    const {$IFDEF FDP_OPL}
            {$IFDEF DEBUG} max_cFPLs      = 50;
            {$ELSE}        max_cFPLs      = 500;
            {$ENDIF}
          {$ELSE}
            {$IFDEF DEBUG}
             {$IFDEF EDD}  max_PROP_cFPLs = 30;
             {$ENDIF}      max_cFPLs      = 50;
            {$ELSE}
             {$IFDEF EDD}  max_PROP_cFPLs = 300;
             {$ENDIF}      max_cFPLs      = 500;
            {$ENDIF}
          {$ENDIF}

          {$IFDEF EDD}     PROP_cFPL : PcFPL = nil;
          {$ENDIF}         cFPL      : PcFPL = nil;

