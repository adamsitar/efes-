{ תתתתתתתתתתתתתתתתתתתתתתתתת
   (c) ALES 1996,99 Kosice,
  תתתתתתתתתתתתתתתתתתתתתתתתת

 ---------------------------------------------------------------
  Zoznam schvalenych FPL na dany den
 תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

{$I comp.h}


unit _PLN;


interface


    uses   TypeDef,
           DB, NET_def,
           {$I unit_gr.h},
           {$I unit_oop.h},
           FIR_def, _L4_def, _MTK_2, _FDP_def,
           Bod_def, Body,
           _FPL4;


    {$IFDEF PLN}
     {$I TSGA_PLN.h}
     { I _PLN_cnst.h}
     {$I _PLN_title.h}
     {$I _PLN_plan.h}
     {$I _PLN_functions.h}

     function _handle_event_PLN (var _Event: TEvent; O: PObject; PLN: PPLN): bool;
    {$ENDIF}


implementation

uses  _check, dos, bios, math, mem, io, str0, utime, sets, mess, msg, keyb, sort, prnt,
      Kody, _NET,
      Archiv,
      FDP_msg, _FPL_def, FDP_scrl, FDP_fun3,
      {$IFDEF STATUS} Status, {$ENDIF}
      _L4_func;


{$IFDEF PLN}

 const    p_pln_dbscroller : PScrollDB_FDP = nil;


 {$I TSGA_PLN.cod}   { ext driver pre dekodovanie PLN }

 {$I _PLN_plan.cod}
 {$I _PLN_plan.vyp}  { obsahuje konverzie medzi PLN a FPL4 }
 {$I _PLN_plan.inc}
 {$I _PLN_send.inc}
 {$I _PLN_plan.drw}
 {$I _PLN_plan.prn}

 {$I _PLN_functions.inc}
 {$I _PLN_net.inc}

 {$I _PLNs_spracovanie.inc}
 { I _PLNs_process.inc}
 {$I _PLNs_handle.inc}

begin
  calibrate_ipln(soh1_PLN,soh2_PLN);
{$ENDIF}
end.
