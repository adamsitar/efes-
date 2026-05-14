   { -----------------
      zakladnie fcie
     -----------------
   }
    procedure new_RTZ (RTZ1, RTZ2: PRTZ); far;
    procedure disp_RTZ(RTZ : PRTZ);       far;
    procedure copy_RTZ(RTZ1, RTZ2: PRTZ); far;

    function  chg_RTZ (RTZ1, RTZ2: PRTZ): bool; far;
    function  eq_RTZ  (RTZ1, RTZ2: PRTZ): bool; far;

    procedure format_RTZ(RTZ: PRTZ); far;


   { ------------
      kodovanie
     ------------
   }
    function  codekey_RTZ    (RTZ: PRTZ): string; far;
    procedure decodekey_RTZ  (key: string; RTZ: PRTZ); far;

    procedure code_RTZ      (RTZ: PRTZ; var pkt: TNETpkt); far;
    procedure decode_RTZ    (const pkt: TNETpkt; RTZ: PRTZ); far;

    procedure codeDB_RTZ    (RTZ: PRTZ; buff: PDB_buff; desc: PDB_head); far;
    procedure decodeDB_RTZ  (buff: PDB_buff; RTZ: PRTZ; desc: PDB_head); far;


   { ------------
      read/save
     ------------
   }
    function  get_dbRTZfn: string; far;
    function  read_RTZ (key: string; RTZ: PRTZ): int; far;
    procedure save_RTZ (_RTZ: PRTZ); far;


   { ------------
      send
     ------------
   }
    function  send_RTZ (RTZ: PRTZ; adr: TNETadr; wait: bool): bool; far;
    function  distribute_RTZ(RTZ: PRTZ; sw: Tnd_sw_set; nd: Tnd_nd_set): bool; far;
    procedure odosli_RTZ (RTZ: PRTZ); far;


   { ------------
      vypocty
     ------------
   }


   { ------------
      zobrazenie
     ------------
   }
    function  print_RTZ  (RTZ: PRTZ): bool; far;
    function  info_RTZ   (RTZ: PRTZ; title: string): bool; far;
    function  report_RTZ (RTZ: PRTZ; title: string): bool; far;


   { ------------
      PLAN
     ------------
   }
    function  zarad_RTZ(RTZ: PRTZ; _stat: string; _send: bool; _src: fdp_src): bool; far;


   { ------------
      NET
     ------------
   }
    procedure _pkt_RTZ (RTZ: PRTZ); far;
    procedure _ack_RTZ(key: string; rec: Tplan_rec; fdp: bool; nd: int); far;
