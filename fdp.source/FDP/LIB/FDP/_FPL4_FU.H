   { -----------------
      zakladnie fcie
     -----------------
   }

    procedure  new_FPL4     (FPL1, FPL2: PFPL4); far;
    function   new_FPL4_    (FPL1: PFPL4; var FPL2: PFPL4): PFPL4; far;
    procedure  disp_FPL4    (FPL: PFPL4); far;
    procedure  disp_FPL4_   (var FPL: PFPL4); far;

    function   eq_FPL4      (FPL1, FPL2: PFPL4): bool; far;
    function   chg_FPL4     (FPL1, FPL2: PFPL4): bool; far;

    function   _FPL4act (FPL: PFPL4): bool;

    function   fpl_approved  (src: byte; cond: bool): bool;

    procedure  fplsrc_clear  (var data: pchar);
    function   fplsrc_idn    (src: byte): string;
    procedure  fplsrc_decode (data: pchar; var src : Tfplsrc);
    procedure  fplsrci_update(FPL: PFPL4; ITEM,DATA: string);
    procedure  fplsrci_check (FPLi,FPL: PFPL4; ITEM: string);
    procedure  fplsrc_check  (FPLi,FPL: PFPL4);

    procedure  format_FPL4_ (FPL: PFPL4); far;
    procedure  format_FPL4  (FPL: PFPL4); far;

    function   idn_FPL4     (FPL: PFPL4): string; far;
    function   ssr_FPL4     (FPL: PFPL4): string; far;

    function   is_FPL4M     (FPL: PFPL4): bool; far;
    function   is_FPL4O     (FPL: PFPL4): bool; far;
    function   is_FPL4MIL   (FPL: PFPL4): bool; far;


   { ------------
      kodovanie
     ------------
   }
    function   codekey_FPL4   (FPL: PFPL4): string; far;
    procedure  decodekey_FPL4 (s: string; FPL: PFPL4); far;

    function   code_l4_FPL4_   (FPL: PFPL4): pchar; far;
    function   decode_l4_FPL4_ (data: pchars; size: TNETdlz; FPL: PFPL4): string; far;

    procedure  _codeDBB_FPL4   (FPL: PFPL4; buff: PDB_buff; head: PDB_head); far;
    procedure  _decodeDBB_FPL4 (buff: PDB_buff; FPL: PFPL4; head: PDB_head); far;
    procedure  codeDB_FPL4    (FPL: PFPL4; buff: PDB_buff; head: PDB_head); far;
    procedure  decodeDB_FPL4  (buff: PDB_buff; FPL: PFPL4; head: PDB_head); far;

    {$IFDEF DATA_BIN}
      procedure decode0_FPL4  (const pkt: TNETpkt; FPL: PFPL4); far;
    {$ENDIF}

    procedure  decode_FPL4    (const pkt: TNETpkt; FPL: PFPL4); far;
    procedure  code_FPL4      (FPL: PFPL4; var pkt: TNETpkt); far;


   { ------------
      vypocty
     ------------
   }
    {function   _item_FPL4_22    (_22: pchar; var _item: string; var pres: pchar): pchar;
    function   _decode_FPL4_22  (var FPL: DFPL4; var res: string): bool;
    }
    procedure  _format_FPL4new(FPL: PFPL4; check_par: word;
                               var res: string; var ires: int;
                               var is_ind: bool; var ind: int
                              );


   { ------------
      read/save
     ------------
   }
    function   get_fn_FPL4: string;
    function   get_fn_FPL4_RPL: string;

    function   find_FPL4  (FPL: PFPL4; _if: pointer): int; far;
    function   read_FPL4  (key: string; FPL: PFPL4): int; far;
    procedure  save_FPL4  (FPL: PFPL4); far;

    procedure  save_FPL4_RPL_ (_FPL: PFPL4; prepisat: bool); far;
    procedure  save_FPL4_RPL  (_FPL: PFPL4); far;


   { ------------
      zobrazenie
     ------------
   }
    const  dxm_FPL4  = 562;
           dxf_FPL4  = 562;
           dym_FPL4  =  44;
           dyf_FPL4  = 178;

    const  p_fpl4_dbscroller : PScrollDB_FDP = nil;


    function   dxi_FPL4: int;
    function   dyi_FPL4: int;

    function   _lat_FPL4 (s: string): string;
    procedure  plan_FPL4 (FPL: PFPL4; x,y: int; b: bool);
    function   info_FPL4 (FPL: PFPL4; title: string): bool;

    {$IFDEF MAPY}
     procedure zobraz_trat_FPL4(FPL: PFPL4); far;
    {$ENDIF}

    {$IFDEF PRN}
     function  print_FPL4(FPL: PFPL4): bool; far;
     procedure print_FPL4s(FPL4s: PFPL4s; top: pint; title: string); far;
    {$ENDIF}


   { ------------
      NET
     ------------
   }
    function   send_FPL4       (FPL: PFPL4; adr: TNETadr; wait: bool): bool; far;
    function   distribute_FPL4 (FPL: PFPL4; sw: Tnd_sw_set; nd: Tnd_nd_set): bool; far;

    procedure  _pkt_FPL4 (FPL: PFPL4); far;
    procedure  _ack_FPL4 (key: string; rec: Tplan_rec; fdp: bool; nd: int); far;

    {function   spracovanie_FPL4_EXT (przn : TFPL4_spracovanie): TFPL4_spracovanie;}



   { ------------
      PLAN
     ------------
   }
    function  existuje_FPL4 (FPL: PFPL4; _zobraz: bool): bool; far;
    function  zmeneny_FPL4  (FPL: PFPL4; _zobraz: bool): bool; far;


    type  func_fpl4_form   = function (FPL: PFPL4; tit: string; novy: bool): bool;
          p_func_fpl4_form = ^func_fpl4_form;

    const p_form_FPL4 : p_func_fpl4_form = nil;

    function  formular_FPL4_ (FPL: PFPL4; tit: string; novy: bool): bool;


    function _zarad_FPL4 (FPL: PFPL4; check_par: word; _stat: string; _send: bool; _src: fdp_src): bool;
    function zarad_FPL4  (FPL: PFPL4; _stat: string; _send: bool; _src: fdp_src): bool;


   { zaradenie noveho (editovaneho, prijateho) FPL4 do spracovania
   }
    type   proc_zarad_FPL4  = procedure (FPL: PFPL4;
                                         var check_par: word; _stat: string; _src: fdp_src;
                                         var res: string; var ires: int;
                                         dbind: pint
                                        );
           pproc_zarad_FPL4 = ^proc_zarad_FPL4;


    const  p_zarad_FPL4 : pproc_zarad_FPL4 = nil;

    procedure _zaradenie_FPL4 (FPL: PFPL4;
                               var check_par: word; _stat: string; _src: fdp_src;
                               var res: string;
                               var ires: int;
                               dbind: pint
                              );

