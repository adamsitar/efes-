    const db_PRN_RIADKOV  = db_NTM_RIADKOV;           { kodovanie je natvrdo }
          dbchg_PRN       : bool = false;

    type  PPRN = ^TPRN;
          TPRN =  TNTM;

    const {$IFDEF DEBUG} max_PRN = 100;
          {$ELSE}        max_PRN = 500;
          {$ENDIF}


    const ispath_VLIS = false;
          isext_VLIS  = false;


   { -----------------
      zakladnie fcie
     -----------------
   }
    procedure new_PRN  (PRN1, PRN2: PPRN); far;
    procedure disp_PRN (PRN: PPRN); far;

    function  eq_PRN   (PRN1,PRN2: PPRN): bool; far;
    function  chg_PRN  (PRN1,PRN2: PPRN): bool; far;


    function  codekey_PRN    (PRN: PPRN): string; far;
    procedure decodekey_PRN  (key: string; PRN: PPRN); far;

    procedure code0_PRN      (PRN: PPRN; var pkt: TNETpkt); far;
    procedure decode0_PRN    (const pkt: TNETpkt; PRN: PPRN); far;
    procedure code_PRN       (PRN: PPRN; var pkt: TNETpkt); far;
    procedure decode_PRN     (const pkt: TNETpkt; PRN: PPRN); far;

    procedure codeDB_PRN     (PRN: PPRN; buff: PDB_buff; desc: PDB_head); far;
    procedure decodeDB_PRN   (buff: PDB_buff; PRN: PPRN; desc: PDB_head); far;


    function  read_PRN (key: string; PRN: PPRN): int; far;
    procedure save_PRN (PRN: PPRN); far;

    procedure _pkt_PRN (PRN: PPRN); far;
    procedure _ack_PRN (key: string; rec: Tplan_rec; fdp: bool; nd: int); far;


    function  send_PRN (PRN: PPRN; adr: TNETadr; wait: bool): bool; far;
    function  distribute_PRN (PRN: PPRN; sw: Tnd_sw_set; nd: Tnd_nd_set): bool; far;


   { ------------
      nariadenie
     ------------

    function  _send_NTM (NTM: PNTM; adr: TNETadr; wait: bool; typ: TNETtyp; info : string): bool;
    function  _distribute_NTM (NTM: PNTM; sw: Tnd_sw_set; nd: Tnd_nd_set; typ: TNETtyp; info : string): bool;
   }

    {function   NTM_fn   (fn: string): string; far;}
    procedure  _pkt_VLIS (var pkt: TNETpkt); far;
    procedure  _ack_VLIS (key: string; rec: Tplan_rec; fdp: bool; nd: int); far;
