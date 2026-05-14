(*-------------------------------------------------------------------*)
(* Arrays  - polia                                                   *)
(* (c) Ales Kosice 1993  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h} { D-}

{
  ak nie je miesto pre ulozenie premennej, Add vrati -1;
  osetri si to odvodena trieda podla svojej filozofie
}

{ polia sa pouzivaju v intrrupt procedurach }

{$X+,I-,S-,P-,F+,O-}
{$C FIXED PRELOAD PERMANENT}


unit Arrays;


interface


     uses  TypeDef,
           _Check,
           str0, DB,
           AStream;


     {$I arr_def.h}
     {$I arr2_def.h}
     {$I buff_def.h}
     {$I arr_ems.h}

     procedure set_chg_ticks (var Tchg: tick_counter);


implementation

uses  Mem, BIOS, BGIgraph, Msg, Mess;

{$I arr.inc}

{$I arr_1.inc}   { TStatic, TDynamic }
{$I arr_2.inc}   { TDynamic2         }
{ I arr_3.inc}   { TArray            }
{$I arr_4.inc}   { TBuffer           }

{$I arr_ems.inc}

end.