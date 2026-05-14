    const db_PRZ_RIADKOV  = db_NTM_RIADKOV;           { kodovanie je natvrdo }
          dbchg_PRZ       : bool = false;

    type  PPRZ = ^TPRZ;
          TPRZ =  TNTM;

    const {$IFDEF DEBUG} max_PRZ = 100;
          {$ELSE}        max_PRZ = 500;
          {$ENDIF}


   { -----------------
      zakladnie fcie
     -----------------
   }
    procedure new_PRZ  (PRZ1, PRZ2: PPRZ); far;
    procedure disp_PRZ (PRZ: PPRZ); far;

    function  eq_PRZ   (PRZ1,PRZ2: PPRZ): bool; far;
    function  chg_PRZ  (PRZ1,PRZ2: PPRZ): bool; far;


    function  codekey_PRZ    (PRZ: PPRZ): string; far;
    procedure decodekey_PRZ  (key: string; PRZ: PPRZ); far;

    procedure code0_PRZ      (PRZ: PPRZ; var pkt: TNETpkt);
    procedure decode0_PRZ    (const pkt: TNETpkt; PRZ: PPRZ);
    procedure code_PRZ       (PRZ: PPRZ; var pkt: TNETpkt); far;
    procedure decode_PRZ     (const pkt: TNETpkt; PRZ: PPRZ); far;

    procedure codeDB_PRZ     (PRZ: PPRZ; buff: PDB_buff; desc: PDB_head); far;
    procedure decodeDB_PRZ   (buff: PDB_buff; PRZ: PPRZ; desc: PDB_head); far;


    function  read_PRZ (key: string; PRZ: PPRZ): int; far;
    procedure save_PRZ (PRZ: PPRZ); far;

    function  send_PRZ (PRZ: PPRZ; adr: TNETadr; wait: bool): bool; far;
    function  distribute_PRZ (PRZ: PPRZ; sw: Tnd_sw_set; nd: Tnd_nd_set): bool; far;

    procedure _pkt_PRZ (PRZ: PPRZ); far;
    procedure _ack_PRZ (key: string; rec: Tplan_rec; fdp: bool; nd: int); far;


    function  _zarad_PRZ (PRZ: PPRZ; _stat: string; _save,_send: bool; _src: fdp_src): bool; far;
    function  zarad_PRZ  (PRZ: PPRZ; _stat: string; _send: bool; _src: fdp_src): bool; far;
