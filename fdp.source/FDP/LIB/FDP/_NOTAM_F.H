   { -----------------
      zakladnie fcie
     -----------------
   }
    procedure new_NTM  (NTM1, NTM2: PNTM); far;
    procedure disp_NTM (NTM: PNTM); far;

    function  chg_NTM  (NTM1,NTM2: PNTM): bool; far;
    function  eq_NTM   (NTM1,NTM2: PNTM): bool; far;

    function  key_NTM_ (NTM: string): string; far;
    function  key_NTM  (NTM: PNTM): string; far;
    {function  rok_NTM  (NTM: PNTM): word; far;}

    function  cislo_NTM (NTM: PNTM): string; far;
    function  stary_NTM (_NTM: string): string;

    procedure format_NTM_ (NTM: PNTM {; path,ext: string; riadkov: byte});
    function  modify_head_NOTAM (NTM: PNTM; _stat: string): bool;


   { ------------
      vypocty
     ------------
   }


   { ------------
      kodovanie
     ------------
   }
    function  code_l4_NTM_   (NTM: PNTM; cislo: string): pchar; far;
    function  decode_l4_NTM_ (data: pchars; size: TNETdlz; NTM: PNTM): string; far;

    function  codekey_NTM_   (cislo: string; dav: TDate): string;
    function  codekey_NTM    (NTM: PNTM): string; far;
    procedure decodekey_NTM  (key: string; NTM: PNTM); far;

    procedure code0_NTM      (NTM: PNTM; var pkt: TNETpkt); far;
    procedure decode0_NTM    (const pkt: TNETpkt; NTM: PNTM); far;
    procedure code_NTM       (NTM: PNTM; var pkt: TNETpkt); far;
    procedure decode_NTM     (const pkt: TNETpkt; NTM: PNTM); far;

    procedure codeDB_NTM     (NTM: PNTM; buff: PDB_buff; desc: PDB_head); far;
    procedure decodeDB_NTM   (buff: PDB_buff; NTM: PNTM; desc: PDB_head); far;



   { ------------
      read/save
     ------------
   }
   {function  _read_NTM (key: string; NTM: PNTM; path,ext: string): int;}
    procedure _save_NTM (NTM: PNTM; path,ext: string; var dbchg: bool);



   { ------------
      zobrazenie
     ------------
   }
    function  dxi_NTM: int; far;
    function  dyi_NTM_pozn(rp: int): int;
    function  dyi_NTM_sur(rs: int): int;
    function  dyi_NTM: int; far;

    procedure _plan_NTM(x0,y0,x1,y1: int; bk: int; rp,rs: byte; form: bool);
    procedure plani_NTM(NTM: PNTM; x,y: int; b,mini: bool);
    procedure plan_NTM(NTM: PNTM; x,y: int; b: bool); far;

    procedure _info_NTM(x0,y0,x1,y1: int; NTM: PNTM); far;
    function  info_NTM (NTM: PNTM; title: string): bool; far;


    function  print_NTM(NTM: PNTM): bool; far;
    procedure print_NTMs(NTMs: Pptrs; top: pointer; title: string); far;


    function  _check_NTM(NTM,NTMp: PNTM; var res: string; var ires: int; form: pointer): bool;
