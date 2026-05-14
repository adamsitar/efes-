(*-------------------------------------------------------------------*)
(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL_func                                             *)
(* (c) Ales Kosice 1995  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}

unit FDP_fun3;


interface

    uses   TypeDef,
           FIR_def, Bod_def, Body, ZemSur, LDM,
           NET_def, _L4_def, _MTK_2, _FDP_def, _FPL_def,
           _FPL4;


    {$IFDEF FPL4}
      function _decode_15 (dep: TAP; dep_: TCas;
                           arr: TAP;

                           eet: TCas;
                           dat: TDate;

                           var typ  : string;                   { vstupne hodnoty }
                           var rych : single; var rych_: char;  { mozu byt priradene }
                           var vys  : word;   var vys_: char;   { ak nie su inicializovane }

                           strat : string;                      { priradena trat }
                           trat  : string;

                           var rte   : POBxys;                  { dekodovana trat       }
                           var bodov : int;                     { pocet bodov trate     }

                           var res: string
                          ): bool;


      function  _prirad_trat_FPL4 (bd0,bdl: string;
                                   var ntrat,trat: string;
                                   fT: PText
                                  ): bool;

      function  prirad_trat_FPL4 (x,y   : int;

                                  _1,_n : string;      { vstupny bod           }
                                  FPL   : PDcFPL;

                                  var rte   : POBxys;  { dekodovana trat       }
                                  var bodov : int;     { pocet bodov trate     }

                                  var res   : string
                                 ): string;
    {$ENDIF}


implementation

uses  bios, sets, keyb, str0, io, utime,
      {$I unit_oop.h}, Lists,
     _L4_func, FDP_msg, Form_sys;

 {$IFDEF FPL4}
  {$I trat_FPL4.inc}
 {$ENDIF}

end.
