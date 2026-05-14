     { -----------------
        zakladnie fcie
       -----------------
     }
      procedure format_cFPL (FPL: PDcFPL); far;

      function  eq_cFPL   (FPL1, FPL2: PDcFPL): bool; far;
      function  chg_cFPL  (FPL1, FPL2: PDcFPL): bool; far;
      function  idn_cFPL  (FPL: PDcFPL): string; far;
      function  ssr_cFPL  (FPL: PDcFPL): string; far;
      function  ssr0_cFPL (FPL: PDcFPL): string; far;


     { ------------
        kodovanie
       ------------
     }
      function  code_l4_FPLC_   (FPL: PDcFPL; cislo: string): pchar; far;
      function  decode_l4_FPLC_ (data: pchars; size: TNETdlz; FPL: PDcFPL): string; far;

      procedure codeDB_FPLC   (FPL: PDcFPL; buff: PDB_buff; head: PDB_head); far;
      procedure decodeDB_FPLC (buff: PDB_buff; FPL: PDcFPL; head: PDB_head); far;

      procedure code_FPLC     (FPL: PDcFPL; var pkt: TNETpkt);   far;
      procedure decode_FPLC   (const pkt: TNETpkt; FPL: PDcFPL); far;
      procedure code_FPLC_mess   (FPL: PDcFPL; var pkt: TNETpkt); far;
      procedure decode_FPLC_mess (const pkt: TNETpkt; FPL: PDcFPL); far;

      {$IFDEF DATA_BIN}
       procedure decode0_cFPL (const pkt: TNETpkt; FPL: PDcFPL); far;
       {$IFDEF RDP}
         procedure code0_cFPL_RDP (FPL: PDcFPL; var pkt: TNETpkt); far;
        {$IFDEF TRENAZER}
         procedure decode0_cFPL_RDP (const pkt: TNETpkt; FPL: PDcFPL); far;
        {$ENDIF}
       {$ENDIF}
      {$ENDIF}

      function  codekey_FPLC   (FPL: PDcFPL): string;    far;
      procedure decodekey_FPLC (s: string; FPL: PDcFPL); far;
      {procedure init_key_cFPL  (const FPL: DcFPL; var FPLi: DcFPL);}


     { ------------
        read/save
       ------------
     }
      function  _arch_fn_cFPL(p: pointer; i: int): string; far;
      procedure save_cFPL(_FPL: PDcFPL); far;

      {function  find_cFPL(key: string; var FPL: PFPLC): bool;}
      function  _find_FPLCa (key: string; var p: PFPLC; var o: P_OFPL): int;
      function  find_FPLCa (key: string): PFPLC;


     { ------------
        vypocty
       ------------
     }
      procedure datum_cFPL(var FPLc: DcFPL);
      function  prepocet_trate_FPLc (FPL: PDcFPL; cmXXXX: word; bod: int): string;
      procedure oprava_casu_pristatia_cFPL(FPL: PDcFPL);
      procedure pristatie_cFPL(FPL: PDcFPL);

      function  decode_c_trat(_start,_prist: TAP; _trat: Tc_trat; _bodov: int;
                              var Trat: TOBxys; var bodov: int
                             ): string;

      function  stav_cFPL      (FPL: PDcFPL; cas: real; var zmena: bool): Tpoz; far;
      function  est_cFPL       (FPL: PDcFPL): bool; far;
      function  suradnice_cFPL (FPL: PDcFPL; cas: real; var sur: Tsur): Tpoz; far;

      {$IFDEF SECTORS} function  sektor_FPLc    (FPL: PDcFPL): bool;
      {$ENDIF}

      function  zmenena_trat_FPLc(FPLp,FPL: PDcFPL; var od_bodu: int): bool;
      function  zmenene_udaje_FPLc(FPLp,FPL: PDcFPL; dep_arr, v_sektore: bool): bool;


     { ------------
        zobrazenie
       ------------
     }

      const  dx_cFPLp  = 645;
             dy_cFPLp  = {$IFNDEF EDD_20} 35 {$ELSE} 42 {$ENDIF};

      function dxi_cFPL: int; far;
      function dyi_cFPL: int; far;

      procedure prop_strip_cFPL (FPL: PDcFPL; x,y: int; b: bool); far;
      procedure strip_cFPL(FPL: PDcFPL; x,y: int; b: bool); far;
      procedure plan_cFPL (FPL: PDcFPL; x,y: int; b: bool); far;

      {$IFDEF MAPY}
        procedure draw_cFPLtrgt(p: pointer; x,y: int; var sur: Tsur; maz: bool);
        procedure zobraz_trat_cFPL(FPL: PDcFPL); far;
      {$ENDIF}

      {$IFDEF PRN}
        function  print_cFPL(FPL: PDcFPL): bool; far;
      {$ENDIF}
      {$IFDEF MPU}
        function  print_cFPL_MPU(FPL: PDcFPL; nd: int; adr: byte): bool; far;
        {$IFDEF DEBUG}
          procedure test_print_cFPL;
        {$ENDIF}
      {$ENDIF}

      {$IFNDEF EDD}
        procedure sc_cFPL(FPL: PDcFPL; x,y: int; b: bool); far;
        function  dx_sc_cFPL: int; far;
        function  dy_sc_cFPL: int; far;
      {$ENDIF}

      function   info_cFPL(FPL: pointer; title: string): bool; far;
      const      p_info_FPLc : TBFunc_ps = info_cFPL;

      function   comp_idn_cFPL(FPL1,FPL2: PDcFPL): bool; far;


     { ------------
        NET
       ------------
     }
      function  send_cFPL       (FPL: PDcFPL; adr: TNETadr; wait: bool): bool; far;
      function  distribute_cFPL (FPL: PDcFPL; sw: Tnd_sw_set; nd: Tnd_nd_set): bool; far;
      function  distribute_rdp_cFPL (FPL: PDcFPL; add: pbool): bool; far;
      procedure message_cFPL    (FPL: PDcFPL; kod: word; adr: TNETadr); far;

      procedure coordinate_FPLC (FPL: PDcFPL;
                                 src: fdp_src; dst: set_fdp_src;
                                 zmena, zmeneny: bool
                                ); far;


      function  _pkt_FPLC_(ods: TNETadr; FPL: PFPLC): bool; far;
      procedure _ack_FPLC (key: string; rec: Tplan_rec; fdp: bool; nd: int); far;


     { ------------
        PLAN
       ------------
     }
      type    Tadd_FPLc  = procedure (FPL: PDcFPL);

      {$IFDEF EDD}
       procedure add_prop_FPLc (FPL: PDcFPL); far;
      {$ENDIF}

      procedure add_FPLc (FPL: PDcFPL); far;
      const     p_add_FPLc : Tadd_FPLc = add_FPLc;

      function  _zarad_FPLc(FPL: PDcFPL; _stat: string;

                            _send: bool; _nd: Tnd_nd_set;
                            _src: fdp_src;
                            _src_adr : TNETadr;
                            _ssr,               { kontrola duplicity _ssr    }
                            _fpl4,              { aktivacia _fpl4            }
                            _prop: bool;        { zaradenie medzi navrhovane }

                            FPLp: PDcFPL;
                            _hladany : bool
                           ): bool;

      function  zarad_FPLc (FPL: PDcFPL; _stat: string; _send: bool; _src: fdp_src): bool; far;


      const   p_zarad_FPLC_FPL4 : pproc_p = nil;
              p_form_FPLC       : pBFunc_ps = nil;



     {$IFDEF SSR_MANAGEMENT}
      function  _zarad_FPLCssr(FPL : PFPLC;
                               zaradit : bool;
                               var res : string;
                               err : pstring;
                               FPLp : PDcFPL;
                               _hladany : bool
                              ): int;
     {$ENDIF}

     {$IFDEF FLI_COORDINATION}
      type      Tform_cFPL = function(FPL: PDcFPL): bool;
      function  _formular_FLI(FPL: PDcFPL): bool;
      const     p_formular_FLI : Tform_cFPL = _formular_FLI;

      function  _code_l4_fli(FPL: PDcFPL): string;
      procedure _decode_l4_fli(_19: string; FPL: PDcFPL);
      procedure _nastav_przn_fli(FPL: PDcFPL; bod: string);
      function  _nastaveny_przn_fli(OB: TOB): bool;
      procedure _odoslane_FLI(FPL : PDcFPL; nastav,dalsi,zarad: bool);
     {$ENDIF}
