    function  eq_NTM   (NTM1,NTM2: PNTM): bool; far;
    procedure new_NTM  (NTM1, NTM2: PNTM); far;
    procedure disp_NTM (NTM: PNTM); far;
    function  idn_NTM  (NTM: PNTM): string; far;

    procedure format_NTM (NTM: PNTM); far;

    function  code_NTM_data   (NTM: PNTM): string; far;
    procedure decode_NTM_data (s: string; NTM: PNTM); far;

    procedure codeDB_NTM      (NTM: PNTM; buff: PDB_buff; desc: PDB_desc); far;
    procedure decodeDB_NTM    (buff: PDB_buff; NTM: PNTM; desc: PDB_desc); far;

    procedure code_NTM        (NTM: PNTM; var pkt: TNETpkt); far;
    procedure decode_NTM      (const pkt: TNETpkt; NTM: PNTM); far;

    function  codekey_NTM     (NTM: PNTM): string;    far;
    procedure decodekey_NTM   (s: string; NTM: PNTM); far;

    function  _read_NTM (key: string; NTM: PNTM; path,ext: string): int;
    procedure _save_NTM (NTM: PNTM; path,ext: string; var dbchg: bool);

    function  _send_NTM (NTM: PNTM; adr: TNETadr; wait: bool; code: TNETtyp; info : string): bool;
    function  _distribute_NTM (NTM: PNTM; sw: Tnd_sw_set; wp: Tnd_wp_set; code: TNETtyp; info : string): bool;


    {$IFDEF PRN}
     function  print_NTM(NTM: PNTM): bool; far;
     procedure print_NTMs(NTMs: Pptrs; top: pointer; title: string); far;
    {$ENDIF}

     function  dxi_NTM: int; far;
     function  dyi_NTM_pozn(rp: int): int;
     function  dyi_NTM_sur(rs: int): int;
     function  dyi_NTM: int; far;

     procedure _plan_NTM(x0,y0,x1,y1: int; bk: int; rp,rs: byte; form: bool);
     procedure plani_NTM(NTM: PNTM; x,y: int; b,mini: bool);
     procedure plan_NTM(NTM: PNTM; x,y: int; b: bool); far;
     procedure _info_NTM(x0,y0,x1,y1: int; NTM: PNTM); far;
     function  info_NTM (NTM: PNTM; title: string): bool; far;
