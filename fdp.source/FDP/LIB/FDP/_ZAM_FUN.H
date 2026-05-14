   { -----------------
      zakladnie fcie
     -----------------
   }
     procedure new_ZAM (ZAM1,ZAM2 : PZAM); far;
     procedure disp_ZAM(ZAM : PZAM); far;
     procedure format_ZAM(ZAM: PZAM); far;

     function  chg_ZAM (ZAM1,ZAM2: PZAM): bool; far;  { nezmenene }
     function  eq_ZAM  (ZAM1,ZAM2: PZAM): bool; far;  { to iste   }

     function  idn_ZAM (ZAM: PZAM): string; far;


   { ------------
      kodovanie
     ------------
   }
     function  code_l4_ZAM_   (ZAM: PZAM; cislo: string): pchar; far;
     function  decode_l4_ZAM_ (data: pchars; size: TNETdlz; ZAM: PZAM): string; far;

     function  codekey_ZAM   (ZAM: PZAM): string; far;
     procedure decodekey_ZAM (key: string; ZAM: PZAM); far;

     procedure code_ZAM      (ZAM: PZAM; var pkt: TNETpkt); far;
     procedure decode_ZAM    (const pkt: TNETpkt; ZAM: PZAM); far;
     {$IFDEF DATA_BIN}
      procedure decode0_ZAM  (const pkt: TNETpkt; ZAM: PZAM); far;
     {$ENDIF}

     procedure code_ZAM_mess   (ZAM: PZAM; var pkt: TNETpkt);   far;
     procedure decode_ZAM_mess (const pkt: TNETpkt; ZAM: PZAM); far;

     procedure codeDB_ZAM    (ZAM: PZAM; buff: PDB_buff; desc: PDB_head); far;
     procedure decodeDB_ZAM  (buff: PDB_buff; ZAM: PZAM; desc: PDB_head); far;


   { ------------
      read/save
     ------------
   }
     function  get_dbZAMfn: string; far;
     function  get_dbZAM_RPLfn: string; far;

     function  read_ZAM (key: string; ZAM: PZAM): int; far;
     procedure save_ZAM (_ZAM: PZAM); far;
     procedure save_ZAM_RPL (_ZAM: PZAM); far;


   { ------------
      vypocty
     ------------
   }
     function  stav_ZAM(ZAM: PZAM; cas: real; var zmena: bool): TPoz; far;
     function  est_ZAM(ZAM: PZAM): bool; far;


   { ------------
      zobrazenie
     ------------
   }
     procedure strip_ZAM  (ZAM: PZAM; x,y: int; b: bool); far;
     function  print_ZAM  (ZAM: PZAM): bool; far;
     function  info_ZAM   (ZAM: PZAM; title: string): bool; far;
     function  report_ZAM (ZAM: PZAM; title: string): bool; far;


   { ------------
      NET
     ------------
   }
    function  send_ZAM       (ZAM: PZAM; adr: TNETadr; wait: bool): bool; far;
    function  distribute_ZAM (ZAM: PZAM; sw: Tnd_sw_set; nd: Tnd_nd_set): bool; far;
    function  distribute_rdp_ZAM (ZAM: PZAM; add: pbool): bool; far;
    procedure message_ZAM    (ZAM: PZAM; kod: word; adr: TNETadr);

    procedure coordinate_ZAM (ZAM: PZAM;
                              src: fdp_src; dst: set_fdp_src;
                              zmena, zmeneny: bool
                             ); far;

    function  _odosli_ZAM    (ZAM: PZAM; _src: fdp_src): bool; far;
    procedure odosli_ZAM     (ZAM: PZAM); far;


    procedure _pkt_ZAM (ZAM: PZAM); far;
    procedure _ack_ZAM (key: string; rec: Tplan_rec; fdp: bool; nd: int); far;


   { ------------
      PLAN
     ------------
   }
    function  zarad_ZAM (ZAM: PZAM; _stat: string; _send: bool; _src: fdp_src): bool; far;

    {function  _add_ZAM (ZAM: PZAM): bool; far;
    procedure add_ZAM  (ZAM: PZAM); far;}



