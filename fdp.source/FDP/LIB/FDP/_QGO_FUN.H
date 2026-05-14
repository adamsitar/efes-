   { -----------------
      zakladnie fcie
     -----------------
   }
    procedure new_QGO (QGO1, QGO2: PQGO); far;
    procedure disp_QGO(QGO : PQGO);       far;
    procedure copy_QGO(QGO1, QGO2: PQGO); far;

    function  chg_QGO (QGO1, QGO2: PQGO): bool; far;
    function  eq_QGO  (QGO1, QGO2: PQGO): bool; far;

    procedure format_QGO(QGO: PQGO); far;


   { ------------
      kodovanie
     ------------
   }
    function  code_l4_QGO_   (QGO: PQGO; cislo: string): pchar; far;
    function  decode_l4_QGO_ (data: pchars; size: TNETdlz; QGO: PQGO): string; far;

    function  codekey_QGO    (QGO: PQGO): string; far;
    procedure decodekey_QGO  (key: string; QGO: PQGO); far;

    procedure code_QGO      (QGO: PQGO; var pkt: TNETpkt); far;
    procedure decode_QGO    (const pkt: TNETpkt; QGO: PQGO); far;
    {$IFDEF DATA_BIN}
     procedure decode0_QGO  (const pkt: TNETpkt; QGO: PQGO); far;
    {$ENDIF}

    procedure codeDB_QGO    (QGO: PQGO; buff: PDB_buff; desc: PDB_head); far;
    procedure decodeDB_QGO  (buff: PDB_buff; QGO: PQGO; desc: PDB_head); far;


   { ------------
      read/save
     ------------
   }
    function  get_dbQGOfn: string; far;
    function  get_dbQGO_RPLfn: string; far;

    {$IFDEF AIRBASE}
     function  read_this_QGO(QGO: PQGO; FN: string): int; far;
    {$ENDIF}
    function  read_QGO (key: string; QGO: PQGO): int; far;

    procedure save_QGO (_QGO: PQGO); far;
    procedure save_QGO_RPL (_QGO: PQGO); far;


   { ------------
      send
     ------------
   }
    function  send_QGO (QGO: PQGO; adr: TNETadr; wait: bool): bool; far;
    function  distribute_QGO(QGO: PQGO; sw: Tnd_sw_set; nd: Tnd_nd_set): bool; far;
    procedure odosli_QGO (QGO: PQGO); far;


   { ------------
      vypocty
     ------------
   }
    procedure spracuj_hlasenia_o_QGO;


   { ------------
      zobrazenie
     ------------
   }
    function  print_QGO  (QGO: PQGO): bool; far;
    function  info_QGO   (QGO: PQGO; title: string): bool; far;
    function  report_QGO (QGO: PQGO; title: string): bool; far;


   { ------------
      PLAN
     ------------
   }
    function  zarad_QGO(QGO: PQGO; _stat: string; _send: bool; _src: fdp_src): bool; far;


   { ------------
      NET
     ------------
   }
    procedure _pkt_QGO (QGO: PQGO); far;
    procedure _ack_QGO (key: string; rec: Tplan_rec; fdp: bool; nd: int); far;
