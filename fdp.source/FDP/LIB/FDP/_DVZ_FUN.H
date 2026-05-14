   { -----------------
      zakladnie fcie
     -----------------
   }
    procedure new_DVZ  (DVZ1, DVZ2: PDVZ); far;
    procedure disp_DVZ (DVZ : PDVZ);       far;
    procedure copy_DVZ (DVZ1, DVZ2: PDVZ); far;
    function  eq_DVZ   (DVZ1, DVZ2: PDVZ): bool; far;
    function  chg_DVZ  (DVZ1, DVZ2: PDVZ): bool; far;


   { ------------
      kodovanie
     ------------
   }
    function  code_l4_DVZ_   (DVZ: PDVZ; cislo: string): pchar; far;
    function  decode_l4_DVZ_ (data: pchars; size: TNETdlz; DVZ: PDVZ): string; far;

    function  codekey_DVZ   (DVZ: PDVZ): string; far;
    procedure decodekey_DVZ (key: string; DVZ: PDVZ); far;

    procedure code_DVZ      (DVZ: PDVZ; var pkt: TNETpkt); far;
    procedure decode_DVZ    (const pkt: TNETpkt; DVZ: PDVZ); far;
    {$IFDEF DATA_BIN}
     procedure decode0_DVZ  (const pkt: TNETpkt; DVZ: PDVZ); far;
    {$ENDIF}

    procedure codeDB_DVZ    (DVZ: PDVZ; buff: PDB_buff; desc: PDB_head); far;
    procedure decodeDB_DVZ  (buff: PDB_buff; DVZ: PDVZ; desc: PDB_head); far;


   { ------------
      read/save
     ------------
   }
    function  get_dbDVZfn: string; far;
    {function  get_dbDVZ_RPLfn: string; far;}

    {$IFDEF AIRBASE}
      {function  read_this_DVZ(DVZ: PDVZ; FN: string): int; far;}
    {$ENDIF}
    function  read_DVZ (key: string; DVZ: PDVZ): int; far;

    procedure save_DVZ (_DVZ: PDVZ); far;
    {procedure save_DVZ_RPL (_DVZ: PDVZ); far;}

    function  find_DVZ(DVZ: PDVZ; _if: pointer): int; far;


   { ------------
      send
     ------------
   }
    function  send_DVZ (DVZ: PDVZ; adr: TNETadr; wait: bool): bool; far;
    function  distribute_DVZ(DVZ: PDVZ; sw: Tnd_sw_set; nd: Tnd_nd_set): bool; far;
    {procedure odosli_DVZ (DVZ: PDVZ); far;}



   { ------------
      vypocty
     ------------
   }

    {$IFDEF PROCESS_DVZ}
      procedure spracuj_ziadosti_o_DVZ;
      procedure pozri_ziadosti_o_DVZ(DVZ: PDVZ);
    {$ENDIF}


   { ------------
      zobrazenie
     ------------
   }
    procedure plan_DVZ (DVZ: PDVZ; x,y: int; b: bool); far;
    function  info_DVZ (DVZ: PDVZ; title: string): bool; far;
    function  report_DVZ (DVZ: PDVZ; title: string): bool; far;

    {$IFDEF PRN}
      function  print_DVZ(DVZ: PDVZ): bool; far;
    {$ENDIF}


   { ------------
      PLAN
     ------------
   }

    function zarad_DVZ(DVZ: PDVZ; _stat: string; _send: bool; _src: fdp_src): bool; far;


   { ------------
      NET
     ------------
   }
    procedure _pkt_DVZ (DVZ: PDVZ); far;
    procedure _ack_DVZ (key: string; rec: Tplan_rec; fdp: bool; nd: int); far;
