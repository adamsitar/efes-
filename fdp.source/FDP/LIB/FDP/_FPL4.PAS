{ -------------------------------------
   Definicia FPL4 podla ICAO (L4444)
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

  תתתתתתתתתתתתתתתתתתתתתתתתתת
   (c) ALES 1996,99 Kosice,
  תתתתתתתתתתתתתתתתתתתתתתתתתת

  - velkosti poloziek su definovane
    natvrdo podla predpisu...
}

{$I comp.h}
{$I comp_FP4.h}

unit _FPL4;


interface

    uses   typedef,
           db, sets,
           {$I unit_gr.h},
           {$I unit_net.h},
           {$I unit_oop.h}, Lists,
           _L4_def, _MTK_2,
           FIR_def, ZemSur, Bod_def, Body,
           {$I unit_map.h},
           _FDP_def, _FPL_def, FDP_msg, FDP_scrl;


    {$I _FPL4_doc.h}

    {$I _FPLC_plan.h}          { definicia stripu so spracovanymi udajmi L4FPL  }
    {$I _FPL4_title.h}         { definicia FPL podla ICAO }
    {$I _FPL4_mnu.h}

    {$IFDEF FPL4}
     {$I _FDR_plan.h}

     {$I _FPL4_plan.h}         { definicia FPL podla ICAO }
     { I _FPL4_cnst.h}         { v _FDP_def : nastavenie spracovania planov }
     { I _FPL4_arrays.h}       { v _L4_def  : slovny popis poli L4FPL }
     {$I _FPL4_fr.h}

     {$I _FDR_functions.h}
     {$I _FPL4_functions.h}
    {$ENDIF}


implementation

uses  dos,bios,_check,keyb,math,mem,io,str0,mouse,utime,mess,msg,sort,prnt,
      Archiv, Vypocty,
      _L4_func,
      FDP_func,
      _SSR, Sector;

{$I _FPLc_0p.inc}
{$I _FPLc_0p.vyp}

{$IFDEF FPL4}

 {$I _FPL4_plan.cod}
 {$I _FPL4_proc.inc}
 {$I _FPL4_plan.inc}  { new,save... }

 {$I _FPL4_0.vyp}     { format }
 { I _FPL4_1.vyp}     { stav planu }
 { I _FPL4_2.vyp}     { naplnenie/priradenie identifikacie }
 { I _FPL4_5.vyp}     { syntax }
 {$I _FPL4_22.dec}

 {$I _FPL4_plan.drw}
 {$I _FPL4_plan.prn}

 {$I _FPL4_functions.inc}
 {$I _FPL4_send.inc}
 {$I _FPL4_net.inc}
 { I _FPL4_archiv.inc}
 {$I _FPL4.ini}


 {$I _FDR_plan.cod}   { obsahuje konverzie medzi zakladnym FPL4 a FDR }
 {$I _FDR_plan.inc}
 {$I _FDR_plan.vyp}
 {$I _FDR_plan.drw}
 {$I _FDR_plan.prn}


 {$I _FP4_10.dec}     { identifikacia a vyhladanie znamych bodov trate }
 {$I _FP4_11.dec}     { dekodovanie bodu a zmien rychlosti, vysky,...  }
 {$I _FP4_12.dec}     { vyhladanie najblizsich bodov ku tratiam, priesecnikov trati... }
 {$I _FP4_13.dec}     { najdenie vstupnych/vystupnych bodov trate cez riadenu oblast }
 {$I _FP4_14.dec}     { cas a vyska na vstupnom bode, dekodovanie alebo pridelenie tratovej rychlosti a vysky }
 {$I _FP4_15body.dec}
 {$I _FP4_15casy.dec}
 {$I _FP4_18.dec}
 {$I _FP4_plan.dec}

begin
  initializacia;
{$ENDIF}
end.