   { -----------------
      zakladnie fcie
     -----------------
   }
    procedure new_PRS  (PRS1, PRS2: PPRS); far;
    procedure copy_PRS (PRS1, PRS2: PPRS); far;
    procedure disp_PRS (PRS:  PPRS); far;

    function  test_PRS (PRS: PPRS): bool;
    function  chg_PRS  (PRS1,PRS2 : PPRS): bool; far;
    function  eq_PRS   (PRS1, PRS2: PPRS): bool; far;

    procedure format_PRS (PRS: PPRS); far;

    function  idn_PRS   (PRS: PPRS): string; far;
    function  nazov_PRS (PRS: PPRS): string; far;

    function  typ_PRS   (PRS: PPRS): string; far;
    function  is_strelnica (PRS: PPRS): bool;

    function  _TSA_kod (kod: string): string;
    function  in_TSA   (kod1,kod2: string): bool;


   { ------------
      kodovanie
     ------------
   }
    function  code_l4_PRS__  (PRS: PPRS; _hd: bool; _cislo: string; _18,_19: bool): pchar;
    function  code_l4_PRS_   (PRS: PPRS; _cislo: string): pchar; far;
    function  decode_l4_PRS_ (data: pchars; size: TNETdlz; PRS: PPRS): string; far;

    function  codekey_PRS    (PRS: PPRS): string; far;
    procedure decodekey_PRS  (key: string; PRS: PPRS); far;

    procedure code_PRS       (PRS: PPRS; var pkt: TNETpkt); far;
    procedure decode_PRS     (const pkt: TNETpkt; PRS: PPRS); far;
    {$IFDEF DATA_BIN}
     procedure decode0_PRS   (const pkt: TNETpkt; PRS: PPRS); far;
     procedure decode0NX_PRS (const pkt: TNETpkt; PRS: PPRS); far;
    {$ENDIF}

    procedure codeDB_PRS     (PRS: PPRS; buff: PDB_buff; desc: PDB_head); far;
    procedure decodeDB_PRS   (buff: PDB_buff; PRS: PPRS; desc: PDB_head); far;


   { ------------
      read/save
     ------------
   }
    function  get_dbPRSifn (PRS: PPRS): string;
    function  get_dbPRSdfn (das: TDate): string;
    function  get_dbPRSfn: string; far;
    function  get_dbPRS_RPLfn: string; far;

    {$IFDEF AIRBASE}
     {function  read_this_PRS (PRS: PPRS; FN: string): int; far;}
    {$ENDIF}
    function  read_PRS (key: string; PRS: PPRS): int; far;

    procedure save_PRS     (PRS: PPRS); far;
    procedure save_PRS_RPL (PRS: PPRS); far;


   { ------------
      zobrazenie
     ------------
   }
    procedure strip_PRS (PRS: PPRS; x,y: int; b: bool); far;
    function  print_PRS (PRS: PPRS): bool; far;
    function  info_PRS  (PRS: PPRS; title: string): bool; far;


   { ------------
      vypocty
     ------------
   }
    procedure _datum_schvalenia_PRS (zac: TDatum; var das: TDate);
    procedure datum_schvalenia_PRS (PRS: PPRS);

    function  stav_PRS (PRS: PPRS; cas: real; var zmena: bool): TPoz; far;
    function  est_PRS  (PRS: PPRS): bool; far;

    function  syntax_PRS (PRS,PRSp: PPRS;
                          var res: string; var ires: int;
                          kontrola_rozsahov: bool;
                          form: PFDP_AForm
                         ): bool; far;


   { ------------
      NET
     ------------
   }
    function  send_PRS       (PRS: PPRS; adr: TNETadr; wait: bool): bool; far;
    function  distribute_PRS (PRS: PPRS; sw: Tnd_sw_set; nd: Tnd_nd_set): bool; far;
    function  distribute_rdp_PRS (PRS: PPRS; add: pbool): bool; far;
    procedure message_PRS    (PRS: PPRS; kod: word; adr: TNETadr);

    {procedure coordinate_PRS (PRS: PPRS;
                              src: fdp_src; dst: set_fdp_src;
                              zmena, zmeneny: bool
                             ); far;

    function  _odosli_PRS    (PRS: PPRS; _src: fdp_src): bool; far;
    procedure odosli_PRS     (PRS: PPRS); far;}


    procedure _pkt_PRS (PRS: PPRS); far;
    procedure _ack_PRS (key: string; rec: Tplan_rec; fdp: bool; nd: int); far;



   { ------------
      PLAN
     ------------
   }
    function  exists_PRS   (PRS: TPRS; var PRSp: TPRS): bool; far;
    function  existuje_PRS (PRS: PPRS; _zobraz: bool): bool; far;
    function  zmeneny_PRS  (PRS: PPRS; _zobraz: bool): bool; far;

    function  zarad_PRS (PRS: PPRS; _stat: string; _send: bool; _src: fdp_src): bool; far;

    {function  _add_PRS (PRS: PPRS): bool; far;
    procedure add_PRS  (PRS: PPRS); far;}
