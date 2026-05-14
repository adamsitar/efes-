(*-------------------------------------------------------------------*)
(* LETVIS FDP                                                        *)
(* (c) Ales Kosice 1993,95 (ab)                                      *)
(* Vypocty                                                           *)
(*-------------------------------------------------------------------*)

{$I comp.h}

{$X+,I-,S-,P-}

unit Vypocty;


interface


    uses  TypeDef,
          _L4_def;

    function   get_poloha (x1,y1,t1: real; x2,y2,t2: real;
                           _abstime: real;
                           rych: single; rych_: char;
                           vys : word; vys_ : char;
                           var xp,yp: real
                          ): bool;


implementation

uses  math,str0, IO, sets;

{$I vypocty.inc}

end.
