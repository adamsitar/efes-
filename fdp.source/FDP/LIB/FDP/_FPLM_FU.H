   { -----------------
      zakladnie fcie
     -----------------
   }
    procedure new_mFPL  (FPL1, FPL2: PDmFPL); far;
    procedure disp_mFPL (FPL : PDmFPL);       far;
    procedure copy_mFPL (FPL1, FPL2: PDmFPL); far;

    function  eq_mFPL  (FPL1, FPL2: PDmFPL): bool; far;
    function  eq_KRL   (FPL1, FPL2: PDmFPL): bool; far;
    function  chg_mFPL (FPL1, FPL2: PDmFPL): bool; far;

    procedure format_mFPL_(FPL: PDmFPL); far;
    procedure format_mFPL (FPL: PDmFPL); far;
    function  format_mFPL_trat (FPL: PDmFPL): string; far;

    function  idn_mFPL (FPL: PDmFPL): string; far;
    function  ssr_mFPL (FPL: PDmFPL): string; far;

    function  _8b_FPLM (FPL: PDmFPL): char;

    function  kod_typu_lietadla           (typ: string): string;
    function  vojensky_kod_typu_lietadla  (typ: string): bool;
    function  iny_kod_typu_lietadla       (typ: string): bool;

    function  is_KRL  (FPL: PDmFPL): bool; far;
    function  is_mFPL (FPL: PDmFPL): bool; far;
    function  is_oFPL (FPL: PDmFPL): bool; far;

    function  is_VFR_FL_FPLM (FPL: PDmFPL): bool; far;
    function  is_VFR_FPLM    (FPL: PDmFPL): bool; far;

    function  __plan_pre_pracovisko (FPL: PDmFPL; aktivne: bool): bool;
    function  _plan_pre_pracovisko  (FPL: PDmFPL): bool; far;

    function  comp_idn_mFPL (FPL1,FPL2: PDmFPL): bool; far;
    {$IFDEF OPL}
     function triedenie_mFPLs (const mFPLs: PmFPLs; top: int): bool;
    {$ENDIF}


   { ------------
      kodovanie
     ------------
   }
    {function  code_FPLM_AP    (kod: string): string;}
    function  code_FPLM_7a     (FPL: PDmFPL): string;

    function  code_l4_FPLM_    (FPL: PDmFPL; cislo: string): pchar; far;
    function  decode_l4_FPLM_  (data: pchars; size: TNETdlz; FPL: PDmFPL): string; far;

    function  codekey_FPLM     (FPL: PDmFPL): string;    far;
    procedure decodekey_FPLM   (s: string; FPL: PDmFPL); far;
    {$IFDEF KRL}
      function  codekey_KRL    (FPL: PDmFPL): string; far;
      procedure decodekey_KRL  (s: string; FPL: PDmFPL); far;
    {$ENDIF}

    procedure code_FPLM        (FPL: PDmFPL; var pkt: TNETpkt); far;
    procedure decode_FPLM      (const pkt: TNETpkt; FPL: PDmFPL); far;
    procedure code_FPLM_mess   (FPL: PDmFPL; var pkt: TNETpkt); far;
    procedure decode_FPLM_mess (const pkt: TNETpkt; FPL: PDmFPL); far;

    {$IFDEF DATA_BIN}
      procedure decode0_mFPL   (const pkt: TNETpkt; FPL: PDmFPL); far;
     {$IFDEF RDP}
      procedure code0_mFPL_RDP (FPL: PDmFPL; var pkt: TNETpkt); far;
      {$IFDEF TRENAZER}
        procedure decode0_mFPL_RDP (const pkt: TNETpkt; FPL: PDmFPL); far;
      {$ENDIF}
     {$ENDIF}
    {$ENDIF}

    procedure codeDB_FPLM   (FPL: PDmFPL; buff: PDB_buff; head: PDB_head); far;
    procedure decodeDB_FPLM (buff: PDB_buff; FPL: PDmFPL; head: PDB_head); far;

    procedure init_key_mFPL  (const FPL: DmFPL; var FPLi: DmFPL);


   { ------------
      vypocty
     ------------
   }
    function  _identifikacia_mimoletiskoveho_letu (FPL: PDmFPL): bool;
    function  _identifikacia_letu_do_tsa (FPL: PDmFPL): bool;
    function  _prirad_dalsie_cislo_letu_do_tsa (FPL: PDmFPL): char;

    {const _dekoduj_uplnu_trat : bool = true;}
    function  syntax_mFPL (FPL,FPLp: PDmFPL;
                           KRIDLO, vlastne, prist_prepocet : bool;
                           var res: string; var ires: int;
                           form: PFDP_AForm
                          ): bool;


    function  decode_trat_FPLM (FPL : PDmFPL;
                                var trat: POBxys; var bodov: int;
                                err_exit       : bool;   { ukonci pri chybe                    }
                                uplna_trat     : bool;   { i so startom a pristatim            }
                                prist_prepocet : bool    { prepocet casu pristatia podla trate }
                               ): string;

    procedure zrus_trat_FPLM (var trat: POBxys; var bodov: int);

    function  stav_mFPL (FPL: PDmFPL; cas: real; var zmena: bool): Tpoz; far;
    function  est_mFPL  (FPL: PDmFPL): bool; far;
    function  est_oFPL  (FPL: PDmFPL): bool; far;
    function  suradnice_mFPL (FPL: PDmFPL; cas: real; var sur: Tsur)  : Tpoz; far;

    function  _let_do_priestoru (FPL: PDmFPL): bool;
    function  _cinnost_v_priestore (FPL: PDmFPL): string;
    function  _let_do_TSA (FPL: PDmFPL): bool;
    function  zmenena_trat_FPLm (FPLp,FPL: PDmFPL; cas_dep,cas_arr,vyska: bool): bool;


   { ------------
      read/save
     ------------
   }
    function  get_fn_mFPL_let: string;
    function  get_fn_mFPL_RPL_let: string;

    function  read_mFPL     (key: string; FPL: PDmFPL): int; far; { predpoklada, ze FPL je neinicalizovana struktura ! }
    procedure save_mFPL     (_FPL: PDmFPL); far;
    procedure save_mFPL_RPL_(_FPL: PDmFPL; prepisat: bool);
    procedure save_mFPL_RPL (_FPL: PDmFPL); far;

    function  _find_FPLM (FPL: PDmFPL; _if: pointer; fn,ext: string): int;
    function  find_FPLM  (FPL: PDmFPL; _if: pointer): int;  far;
    {$IFDEF KRL}
     function  find_KRL (FPL: PDmFPL; _if: pointer): int; far;
    {$ENDIF}
    function  find_FPLMa (key: string): PFPLM;


   { ------------
      zobrazenie
     ------------
   }
    {$IFDEF FPLM_L} const  dx_mFPL  = 500;
                           dym_mFPL = 35;
                           dyr_mFPL = 5;
                           dyf_mFPL =   dym_mFPL
                                      + dyr_mFPL+max_mFPL_15_r_hi*10+dyr_mFPL
                                      + dyr_mFPL+max_mFPL_18_r_hi*10+dyr_mFPL;
    {$ELSE}         const  dx_mFPL  = 500;
                           dyf_mFPL = 88;
    {$ENDIF}

    const p_fplm_dbscroller : PScrollDB_FDP = nil;


    function dxi_mFPL: int; far;
    function dyi_mFPL: int; far;

    {$IFDEF FPLM_L}
      procedure _plan_mFPL(x0,y0,x1,y1: int; bk: int; r15,r18: byte);
    {$ELSE}
      procedure _plan_mFPL(x0,y0,x1,y1: int; bk: int; sm: byte);
    {$ENDIF}
    procedure plan_mFPL (FPL: PDmFPL; x,y: int; b: bool); far;
    procedure planf_mFPL(FPL: PDmFPL; x,y: int; b: bool);

    {$IFNDEF EDD}
     procedure sc_mFPL(FPL: PDmFPL; x,y: int; b: bool); far;
     function  dx_sc_mFPL: int; far;
     function  dy_sc_mFPL: int; far;
    {$ENDIF}

    function  info_mFPL(FPL: PDmFPL; title: string): bool; far;

    procedure strip_mFPL(FPL: PDmFPL; x,y: int; b: bool); far;
    procedure prop_strip_mFPL (FPL: PDmFPL; x,y: int; b: bool); far;

    {$IFDEF MAPY}
      procedure draw_mFPLtrgt(p: pointer; x,y: int; var sur: Tsur; maz: bool);
      procedure zobraz_trat_mFPL(FPL: PDmFPL); far;
    {$ENDIF}

    {$IFDEF PRN}
      function  print_mFPL(FPL: PDmFPL): bool; far;
      procedure print_mFPLs(FPLs: Pptrs; top: pointer; title: string); far;
     {$IFDEF KRL}
       procedure print_KRLs (FPLs: Pptrs; top: pointer; title: string); far;
     {$ENDIF}
    {$ENDIF}

    {$IFDEF MPU}
      function  print_mFPL_MPU(FPL: PDmFPL; nd: int; adr: byte): bool;
      {$IFDEF DEBUG}
        procedure test_print_mFPL;
      {$ENDIF}
    {$ENDIF}


   { ------------
      OPL
     ------------
   }
    {$IFDEF PROCESS_FPLM} {$IFDEF OPL}
      {$IFDEF AIRBASE}
        function _spracovanie_na_ACC(p, FPL: PDmFPL): bool; far;
      {$ENDIF}

      {$IFDEF MACC}
        function _ziadost_o_pripomienku (p, FPL: PDmFPL): bool; far;
        function _odlozena_ziadost_o_pripomienku (p, FPL: PDmFPL): bool; far;
      {$ENDIF}

      procedure pozri_pripomienky_na_FPLM (FPL: PDmFPL);
    {$ENDIF} {$ENDIF}


     function  _prelet_cez_LSRLP (FPL: PDmFPL; LSRLP: string): bool;
     function  _ma_prelet_cez_LSRLP (FPL: PDmFPL; LSRLP: string): bool; far;

     function  _ma_MZP (trat: pchar): byte;
     function  _ma_MZP_na_LSRLP (FPL: PDmFPL; LSRLP: string): bool; far;


    {$IFDEF REPORT_FPLM_ARW}
     function  _is_FPLM_ARW (FPL: PDmFPL; s: Pstring): bool; far;
     procedure pozri_nevydane_spravy_FPLM_ARR (zmena: bool);
    {$ENDIF}



   { ------------
      NET
     ------------
   }
    function  send2node_mFPL (FPL: PDmFPL; nd: int): bool; far;
    {$IFDEF KRL} function  send2node_KRL (FPL: PDmFPL; nd: int): bool; far;
    {$ENDIF}

    function  send_mFPL        (FPL: PDmFPL; adr: TNETadr; wait: bool): bool; far;
    function  distribute_mFPL  (FPL: PDmFPL; sw: Tnd_sw_set; nd: Tnd_nd_set): bool; far;
    function  distribute_rdp_mFPL (FPL: PDmFPL; add: pbool): bool; far;
    procedure message_mFPL     (FPL: PDmFPL; kod: word; adr: TNETadr); far;

    procedure coordinate_FPLM  (FPL: PDmFPL;
                                src: fdp_src; dst: set_fdp_src;
                                zmena, zmeneny: bool
                               ); far;


    function  _odosli_mFPL_ (FPL: PDmFPL): bool;
    function  _odosli_mFPL  (FPL: PDmFPL; _src: fdp_src): bool; far;
    procedure odosli_mFPL   (FPL: PDmFPL); far;

    {$IFDEF KRL} function _odosli_KRL (FPL: PDmFPL): bool;
    {$ENDIF}

    function  _accept_FPLm (ods: TNETadr; FPL: PDmFPL): bool; far;
    procedure _pkt_FPLM (FPL: PDmFPL); far;
    procedure _ack_FPLM (key: string; rec: Tplan_rec; fdp: bool; nd: int); far;


   { ------------
      PLAN
     ------------
   }
    {$IFDEF EDD}
     procedure add_prop_FPLm (FPL: PDmFPL); far;
    {$ENDIF}
    procedure  add_FPLm  (FPL: PDmFPL); far;

    function  najdi_FPLM (FPL: DmFPL; var FPLp: DmFPL): bool;

    function  existuje_mFPL (FPL: PDmFPL; _zobraz: bool): bool; far;
    function  zmeneny_mFPL  (FPL: PDmFPL; _zobraz: bool): bool; far;

    function  zarad_FPLm (FPL: PDmFPL; _stat: string; _send: bool; _src: fdp_src): bool; far;

