   { -----------------
      zakladnie fcie
     -----------------
   }
    function   alloc_FDRrte   (var rte: POBxys; const src: POBxys; bodov: int): bool;
    procedure  dealloc_FDRrte (var rte: POBxys; var bodov: int);

    procedure  new_FDR_data (FDR1, FDR2: PFDR); far;
    procedure  new_FDR   (FDR1, FDR2: PFDR); far;
    function   new_FDR_  (FDR1: PFDR; var FDR2: PFDR): PFDR; far;
    procedure  disp_FDR  (FDR: PFDR); far;
    procedure  disp_FDR_ (var FDR: PFDR); far;

    function   eq_FDR  (FDR1, FDR2: PFDR): bool; far;
    function   chg_FDR (FDR1, FDR2: PFDR): bool; far;

    function   idn_FDR  (FDR: PFDR): string; far;
    function   ssr_FDR  (FDR: PFDR): string; far;
    function   ssr0_FDR (FDR: PFDR): string; far;


   { ------------
      kodovanie
     ------------
   }
    procedure  decodeDB_FDR  (buff: PDB_buff; FDR: PFDR; head: PDB_head); far;
    function   codekey_FDR   (FDR: PFDR): string; far;
    procedure  decodekey_FDR (s: string; FDR: PFDR); far;

    procedure  code_FPL4data_to_FDR  (const FPL: DFPL4; var FDR: DFDR);
    procedure  code_FDRdata_to_FPL4  (const FDR: DFDR;  var FPL: DFPL4);

    function   code_FDRrte_s (FDR: PFDR; _fpl: bool): string;
    function   code_FDR_s    (FDR: PFDR): string;


   { ------------
      read/save
     ------------
   }


   { ------------
      vypocty
     ------------
   }
    function  eet_FDR (FDR: PFDR): real;
    function  stav_FDR (FDR: PFDR; cas: real; var zmena: bool): Tpoz; far;

    procedure update_FDR_date (FDR: PFDR; date: TDate);


   { ---------------------
      dekodovanie/vypocty
     ---------------------
   }
    function  _decode_FPL4_7a (var FPL: DFPL4; var FDR: DFDR; check_en: bool; var res: string): int;

    function  _decode_FPL4_DATA  (var FPL: DFPL4; var FDR: DFDR;
                                  var dd: TFDR_decoded_data;
                                  var res: string
                                 ): int;

    function  _decode_FPL4_DATE  (var  FPL : DFPL4; var FDR : DFDR;
                                  f18_ : pchar;
                                  var  dd : TFDR_decoded_data;
                                  var  res: string
                                 ): int;

    function  _decode_FPL4_15 (FPL: DFPL4; var FDR: DFDR; var dd: TFDR_decoded_data; var res: string): int;

    function  _decode_FPL4 (var FPL: DFPL4; check_en: bool; var res: string): int;

    function  _urc_trat_FPLC (var _OBs: TOBxys; var _bodov: int; _exclude_uknown_points: bool): bool;
    procedure _napln_trat_FPLC_ (var rte: POBxys; var bodov: int; var FPL: DFPLC; _exclude_uknown_points: bool);

    {function  _item_FPL4_22   (_22: pchar; var _item: string; var pres: pchar): pchar;}
    function  _decode_FPL4_22 (var FPL: DFPL4; var res: string): bool;



   { ------------
      zobrazenie
     ------------
   }
    const  dx_FDR_item  = (kod_7a+1+kod_NDB+kod_TIME) shl 3 + 4;
           dy_FDR_item  = 8;

           _dx_FDR_plan =    kod_7a+1
                           + kod_9b+1+kod_9c+2
                           + (kod_AP+kod_TIME+1)*2+2
                           + (kod_NDB+kod_TIME+1)*2+3
                           + 1+altS_+1
                           + 4+fplsrcs+1
                           + 4
                          ;

           {_dx_FDR_plan =    kod_7a+1
                           + kod_9b+1+kod_9c+2
                           + (kod_AP+kod_TIME+1)*2
                           + (kod_NDB+kod_TIME+1)*2
                           + 1+altS_+1
                           + fplsrcs+1
                           + 4
                          ;}

           dx_FDR_plan  = _dx_FDR_plan shl 3;
           dy_FDR_plan  = 8;


    procedure  plan_FDR (FDR: PFDR; x,y: int; b: bool);
    function   info_FDR (FDR: PFDR; title: string): bool;

    {$IFDEF PRN}
     function  print_FDR  (FDR: PFDR): bool;
     procedure print_FDRs (FDRs: PFDRs; top: pint; title: string);
    {$ENDIF}

