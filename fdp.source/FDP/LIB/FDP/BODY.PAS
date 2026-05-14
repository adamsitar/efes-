(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 1.0                                              *)
(* (c) Ales Kosice 1993,99  (ab)                                     *)
(* Body na trati                                                     *)
(*-------------------------------------------------------------------*)

{$I comp.h}
{$I comp_FP4.h}

{$X+,I-,S-,P-}

{ Pre vojenske planovanie sa vypocitavaju
  z cfg suborov podriadene letiska a vlastne trate,
  aby mohli byt ponuknute pri zapise
}


unit Body;


interface


     uses  TypeDef,
           Arrays,
           Lists,
           FIR_def, _L4_def, NET_def,
           Bod_def;


           {$I body_cnst.h}
           {$I body_lst.h}            { definicia nazvov suborov obsahujucich popis FIR }
           {$I body_bod.h}
           {$I body_rte.h}
           {$I body_area.h}
           {$I body_err.h}


     const LK      : PaBody = nil;    { civilne letiska  }
           LK_m    : PaBody = nil;    { vojenske letiska }

           OB      : PaBody = nil;    { FIR NDB,OB,...       }
           OB_m    : PaBody = nil;    { vojenske otocne body }


           OBs_io  : int = 0;
           OB_io   : PIOBODy = nil;

           RTEs    : int = 0;
           RTE     : PRTEs = nil;     { trate LPS }

           RTEs_m  : int = 0;
           RTE_m   : PRTEs = nil;     { vojenske trate }


           AREA    : PaArea = nil;    { zoznam priestorov }



     const  airbase : string[KOD_AP] = '';


   { letiska, prislusnost
   }
     function   this_airbase: string;
     function   eq_airbase   (let1,let2: string): bool;

     function   adr_airbase  (let: string): TNETadr;
     function   aftn_airbase (let: string): string;

     function   _mairbase    (let: string): string;
     function   _cairbase    (let: string): string;

     function   civilne_letisko  (let: string): bool;
     function   vojenske_letisko (kod: string): bool;
     function   ine_letisko      (kod: string): bool;

     function   _letisko (kod,letisko: string): bool;

     function   toto_letisko  (kod: string): bool;
     function   podriadene_letisko (kod: string): bool;

     function   _is_RT (kod: string; var ind: int): bool;
     function   _is_PT (kod: string; var ind: int; var let,tsa: string): bool;
     function   vlastna_trat (s: string): bool;

     function   _LKmind (kod: string): int;


   { body
   }
     function   _OBind_  (kod: string; B: PaBody; var Bi: TsBod): int;
     function   _OBind   (kod: string; B: PaBody): int;
     function   _OBindBi (ind: int; B: PaBody; var Bi: TsBod): bool;

     function   _AREAind_ (kod: string; A: PaArea; var Ai: TpArea): int;

     function   _RTEind     (kod: string; R: PRTEs; max: int): int;
     function   _RTEbod_ind (bod: string; R: TRTE): int;

     procedure  AP_to_OB_   (APi: TAP;    var OB: TOB_);
     procedure  AP_to_OBxy  (APi: TAP;    var OBxy: TOBxy);
     procedure  BOD_to_OBxy (OBi: TsBod;  var OBxy: TOBxy);

     procedure  OB_to_OB_   (OB: TOB;  var OBi: TOB_);
     procedure  OB_to_OBxy  (OBi: TOB; var OBxy: TOBxy);

     procedure  OB__to_OBxy (OBi: TOB_; var OBxy: TOBxy);

     procedure  OBxy_to_OB  (OBxy: TOBxy; var OBi: TOB);
     procedure  OBxy_to_OB_ (OBxy: TOBxy; var OBi: TOB_);
     procedure  OBxy_to_AP_ (OBxy: TOBxy; var APi: TAP_);


    { vyhladanie suradnic otocnych bodov a letisk
    }
     function   is_NDB_eq  (kod_X, kod: string): bool;

     function   is_OB_eq   (kod_X,kod: string): bool; { tieto dve zrusit }
     function   is_OBind   (kod: string): bool;

     function   get_OB_XY  (kod: string; var B: TOBxy) : bool;
     function   get_OB_XYM (kod: string; var B: TOBxy) : bool;


     function   is_OB      (kod: string; var B: TsBod; vsetky: bool): bool;
     function   is_VOR     (kod: string; var x,y: real): bool;
     function   is_VOR_or_ZS (kod: string; var B: TsBod): bool;
     function   is_RTE     (kod: string; var R: TRTE): bool;

     function   is_iobod   (bod: string): int; far;

     function   is_iobod_dir             (bod,let: string; var dir: string): bool; far;
     type       Tis_iobod_dir = function (bod,let: string; var dir: string): bool;
                Pis_iobod_dir = ^Tis_iobod_dir;


   { kontrola na pretecenie suradnic
   }
     function   xy_in_range(x,y: real): bool;


   { inicializacia suradnic
   }
     procedure cas_suradnice_a_vyska_tratOBxy (trat: POBxys; bodov,bod: int; var cas,x,y: real; var vys: word);
     procedure suradnice_a_vyska_tratOBxy (trat: POBxys; bodov,bod: int; var x,y: real; var vys: word);
     procedure suradnice_a_vyska_tratBOD  (trat: PTrat;  bodov,bod: int; var x,y: real; var vys: word);


     function  get_items_OB (fn: string;
                             top,max: int;
                             skip: TCharSet;
                             err: bool;
                             var _err: bool
                            ): word;

     procedure read_OBs (fn: string;
                         B: PaBody; _0,_top: int;
                         p_ine: PP_init_OBine;
                         _exit: bool;
                         var _err: bool
                        );


     {
     function  nacitanie_oblasti_riadenia(s: string): pointer;
     procedure odalokovanie_oblasti_riadenia(var p_ine: pointer);

     const  p_nacitanie_oblasti_riadenia    : TPFunc_s = nacitanie_oblasti_riadenia;
            p_odalokovanie_oblasti_riadenia : TProc_vp = odalokovanie_oblasti_riadenia;
     }


implementation

uses  crt, bios, io, sets, str0, mess, math, parstr, sort, keyb,
      ZemSur, LDM, Vypocty,
      FDP_msg, Kody,
      _MTK_2;


 const   zd_max : real = 0;  { orezanie systemovej roviny, aby nepretiekli suradnice }
         zd_min : real = 0;
         zs_max : real = 0;
         zs_min : real = 0;

 function xy_in_range(x,y: real): bool;
    begin
      xy_in_range:= (zd_min<=x) and (x<=zd_max) and (zs_min<=y) and (y<=zs_max)
    end;

 procedure error_max (s,fn: string; poc,max: int; var nl: bool);
     begin
       if s='' then s:= err_B_vela_;
       MessError(kbNL + fn + s + ' ('+cstr(poc,1)+')'+err_B_maximum+cstr(max,1)+'.',true,nl)
     end;

 {$I body_code.inc}  { konverzie medzi roznymi strukturami }

 {$I body_ob.inc}    { fcie pre vyhladanie bodov        }
 {$I body_is.inc}    { doplnenie pre civilne body       }
 {$I body_ap.inc}    { -//-  letisk                     }
 {$I body_rte.inc}   { fcie pre trate                   }
 {$I body_area.inc}  { fcie pre priestory               }

 {$I body_ats.ini}
 {$I body_mil.ini}
 {$I body_ob.ini}    { inicializacia                    }
 {$I body_rte.ini}
 {$I body_area.ini}

 {$I body.ini}

 {$I body_xy.inc}    { konverzie datovych typov }

begin
 BODY_init
end.