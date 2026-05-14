   { -----------------
      zakladnie fcie
     -----------------
   }
    procedure new_SYN  (SYN1,SYN2: PSYN); far;
    procedure disp_SYN (SYN: PSYN); far;
    function  eq_SYN   (SYN1,SYN2: PSYN): bool; far;


   { ------------
      kodovanie
     ------------
   }
    {function  code_l4_ZAM_   (ZAM: PZAM; cislo: string): pchar; far;
     function  decode_l4_ZAM_ (data: pchars; size: TNETdlz; ZAM: PZAM): string; far;
    }
    procedure decode_SYN   (const pkt: TNETpkt; SYN: PSYN); far;
    procedure codeDB_SYN   (SYN: PSYN; buff: PDB_buff; desc: PDB_head); far;
    procedure decodeDB_SYN (buff: PDB_buff; SYN: PSYN; desc: PDB_head); far;
    function  codekey_SYN  (SYN: PSYN): string; far;


   { ------------
      read/save
     ------------
   }
    function  get_dbSYNfn: string;
    function  read_SYN(key: string; SYN: PSYN): int; far;
    procedure save_SYN(_SYN: PSYN);


   { ------------
      send
     ------------
   }
    function  send_SYN(SYN: PSYN; adr: TNETadr; wait: bool): bool; far;
    function  distribute_SYN(SYN: PSYN; sw: Tnd_sw_set; nd: Tnd_nd_set): bool; far;


   { ------------
      zobrazenie
     ------------
   }
    procedure plan_SYN(SYN: PSYN; x,y: int; b: bool); far;
    function  print_SYN(SYN: PSYN): bool; far;
    function  info_SYN(SYN: PSYN; title: string): bool; far;

   { ------------
      NET
     ------------
   }

    procedure _pkt_SYN (SYN: PSYN); far;
    procedure _ack_SYN (key: string; rec: Tplan_rec; fdp: bool; nd: int); far;

    {$IFDEF MET_RLI}
     procedure _pkt_MRL (pkt: TNETpkt); far;
     procedure initialize_MRL (nd: int);
    {$ENDIF}


    (*
    function  eq_MET  (MET1,MET2: PMET): bool;  far;
    procedure new_MET (MET1,MET2: PMET); far;
    procedure disp_MET(MET: PMET); far;

    procedure code_MET  (MET: PMET; pkt: PNETpacket);  far;
    procedure decode_MET(pkt: PNETpacket; MET: PMET);  far;
    procedure codeDB_MET  (MET: PMET; buff: PDB_buff; desc: PDB_head); far;
    procedure decodeDB_MET(buff: PDB_buff; MET: PMET; desc: PDB_head); far;
    function  codekey_MET (MET: PMET): string; far;

    function  get_dbMETfn: string;

    function  read_MET(key: string; MET: PMET): int; far;
    procedure save_MET(MET: PMET);

    function  send_MET(MET: PMET; adr: TNETadr; wait: bool): bool; far;
    function  distribute_MET(MET: PMET; sw: Tnd_sw_set; wp: Tnd_wp_set): bool; far;
    function  print_MET(MET: PMET): bool; far;
    *)
