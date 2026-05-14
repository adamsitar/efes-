         { ------------------- }
         { TFPL                }
         { ------------------- }
    type    P_OFPL = ^O_FPL;
            O_FPL = object (O_STRIP)

              p_plan_handler : pointer;
              p_ssr,p_ssr0   : pointer;
              p_typ          : pointer;

              {$IFDEF EDD}
                accepted  : bool;    { je to pole "accepted" stripov ? }
              {$ENDIF}

              {$IFDEF SECTORS}
                semaphorS : bool;
                updateS   : real;
                dayS      : byte;
                monthS    : byte;
                yearS     : word;
                hourS     : byte;
                minS      : byte;
                secS      : byte;
              {$ENDIF}

              {$IFDEF MAPY}
                draw_trgt : pointer; { TProc_piib -> vykreslenie planu }
                ciele_en  : pointer; { adresa na bool povolujucu imitaciu  }
                cl_ciel   : byte;
              {$ENDIF}


              constructor  Init(_items,_data_size : word;

                                _new_item,
                                _format_item,
                                _disp_item : pointer;

                                _eq,
                                _id,
                                _ssr,
                                _chg,
                                _poz,
                                _est : pointer;

                                _distribute : pointer;  { TNET_distribute_rdp_pkt  }
                                _send       : pointer;  { TNET_send_pkt }
                                _en_net     : bool;

                                _item_list  : pointer;
                                _item_dx,_item_dy : int;
                                _get_item_dx,_get_item_dy : pointer;
                                _p_viewer : PScrollInd;

                                {$IFDEF MAPY}
                                 _p_kresli  : pointer;
                                 _draw_trgt : pointer;    { TProc_piib -> vykreslenie planu }
                                 _ciele_en  : pointer;
                                 _cl_ciel,
                                 _cl_trat   : byte;
                                {$ENDIF}

                                {$IFDEF EDD}
                                 _accepted : bool;
                                 _adrBOARD : PPObject;
                                 _cmADD,_cmCHG,_cmDEL,_cmCLR: word;

                                 _strip   : pointer;
                                 _skupina : string;
                                {$ENDIF}

                                var _p_PRN  : bool;
                                _p_print    : pointer;

                                _save       : pointer;
                                _zobraz     : pointer;
                                _formular   : pointer;
                                _p_comp     : pointer;  { @TBfunc_p2: bool; pre porovnanie  }
                                _p_handler  : pointer;

                                _p_nameDB, _p_decodeDB : pointer;
                                _riadkovDB : byte;
                                _p_codekey : pointer;

                                _limit_add, _limit_cnl, _limit_del : pint;
                                _nacitanie : bool;

                                _hlpXXX    : Pchar
                               );

              function  Eq(ind: int; p: pointer): bool; virtual;


             { --------------------
                spracovanie planov
               --------------------
             }
              function  nastavenie_platnosti(zmena: bool): bool; virtual;

              procedure format_data_variables (p: pointer); virtual;

              function  get_ssr    (p: pointer): string;
              function  is_ssr     (ind: int; ssr: string): bool;
              function  ssr_in_use (idn,ssr: string): string;

              function  get_typ    (p: pointer): string;


              {$IFDEF PRN}
                function  is_to_addP (p: pointer): bool; virtual;
              {$ENDIF}


              {$IFDEF SECTORS}
                function  urc_platnostS  (p: pointer): bool; virtual;

                function  _is_to_addS    (p: pointer; _S_IN_THROUGH: bool; _S_EST_LIMIT: real): bool; virtual;
                function  is_to_addS     (p: pointer): bool; virtual;

                function  let_cez_sektor (p: pointer): bool; virtual;
                function  let_v_sektore  (p: pointer; _limit: real): bool; virtual;
                function  platnost_letu_v_sektore (p: pointer; zmena_sektorizacie: bool): bool; virtual;
                {function let_zo_sektora (p: pointer; _limit: real): bool; virtual;}

                function  nastavenie_platnosti_v_sektore: bool;
              {$ENDIF}


              {$IFDEF MAPY} { ciel, historia }
                {protected}
       {A}      function  sur_eq   (p,ip: pointer): bool; virtual;
       {A}      procedure get_sur  (p: pointer; var sur: Tsur); virtual;
       {A}      procedure set_sur  (p: pointer; sur: Tsur); virtual;
                procedure init_sur (p: pointer; clear: bool);

                public
                procedure targets (mapa_init: bool);
                procedure init_targets;
                procedure hide_targets;
                procedure show_targets;

                function  handle_target (var _Event: TEvent): bool;

                {protected}
                procedure _target_history     (p: pointer; var sur: Tsur);
                function  _target_coordinates (p: pointer; cas: real; var sur: Tsur): Tpoz; virtual;
                procedure _target             (p,ip: pointer; mapa_init: bool);

                function  _handle_target(var _Event: TEvent; p: pointer): bool;


               { TRAT LETU      }
                procedure zobraz_plan_na_mape (p: pointer); virtual;
                procedure zmaz_plan_na_mape   (p: pointer; _del: bool); virtual;

       {A}      function  get_mapa (p: pointer): PMapData;       virtual;
       {A}      procedure set_mapa (p: pointer; mapa: PMapData); virtual;
       {A}      procedure get_mapa_par (p: pointer;
                                        var Trat: POBxys; var bodov: int;
                                        var Trat_: POBxys; var bodov_: int;
                                        var MapNaz: string
                                       ); virtual;

                procedure put_mapa  (M: PMapData);
                procedure draw_mapa (M: PMapData);   { vykresli mapu trate do Mapa }
                procedure hide_mapa (M: PMapData);

                procedure add_mapa (p: pointer);     { prida mapu trate do Mapa }
                procedure del_mapa (p: pointer);
              {$ENDIF}


              {$IFDEF RDP}
                procedure message_to_RDP_sector(p: pointer; kod: word);

               {$IFDEF RDP_ACCEPT}
                 function  is_rdp_sector(RDP: TRTRadr): int;

                 function  get_accept(p: pointer; var ACPT: TTRG_stat; var RDP: TRTRadr): TTRG_stat; virtual;
                 procedure set_accept(p: pointer; TRG: TTRG_stat; RDP: TRTRadr); virtual;

                 procedure RDP_accept(idn: string; TRG: TTRG_stat; RDP: TRTRadr; send: bool);
                 procedure EDD_accept(p: pointer;  TRG: TTRG_stat; RDP: TRTRadr; send: bool);

                 procedure FL_accept    (idn: string; RDP: TRTRadr); virtual;
                 procedure FL_unaccept  (idn: string; RDP: TRTRadr); virtual;
                 procedure FL_handover  (idn: string; RDP: TRTRadr); virtual;
                 procedure FL_unhandover(idn: string; RDP: TRTRadr); virtual;

                 procedure FPL_accept   (p: pointer); virtual;
                 procedure FPL_unaccept (p: pointer); virtual;
               {$ENDIF}
              {$ENDIF}


              { Pri novej verzii FDP zvazit model roznych koordinacnych sprav
              }

              {$IFDEF ABI_COORDINATION}
                procedure set_ABI (p: pointer); virtual;
                procedure coordinate_ABI (p: pointer); virtual;
              {$ENDIF}
            end;


  {$IFDEF RDP_ACCEPT}
    procedure init_RDP_SECTOR;
  {$ENDIF}