{ -------------------------------------
   Definicia FPL4 podla ICAO (L4444)
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

  תתתתתתתתתתתתתתתתתתתתתתתתתת
   (c) ALES 1996,99 Kosice,
  תתתתתתתתתתתתתתתתתתתתתתתתתת

}

{$I comp.h}

{$I comp_FDP.h}
{$I comp_OPL.h}
{$I comp_FP4.h}


unit _FPL4s;

interface

    uses   TypeDef,
           {$I unit_oop.h}, Lists,
           {$I unit_gr.h},
           {$I unit_net.h},
           {$I unit_map.h},
           _L4_def, _MTK_2,
           _FDP_def, _FPL_def, FDP_edit,
           _PLAN, _FPL, _FPL4, _FPLc;


    {$IFDEF FPL4}
      {$I _FDR_obj.h}
      function  _handle_event_FPL4 (var _Event: TEvent; O: PObject; FPL: PFPL4): bool;
    {$ENDIF}


implementation

uses  bios, keyb, math, mem, io, str0, mouse, utime, sets, db, mess, msg, sort, prnt,
      Bod_def, Body, ZemSur, Vypocty,
      Archiv,
      FDP_msg, FDP_scrl,
      {$IFDEF RPL} _RPL,    {$ENDIF}
      {$IFDEF PLN} _PLN,    {$ENDIF}
      {$IFDEF TLG} frm_TLG, {$ENDIF}
      form_SYS, frm_FPL, frm_FPL4;


{$IFDEF FPL4}

 const  p_fdr_dbscroller  : PScrollDB_FDP = nil;

 function _handle_event_FPL4_sc (var _Event: TEvent; O: PObject;
                                 FPL: PFPL4;
                                 sc: PScroller
                                ): bool; far; forward;

 function handle_plan_FDR (var Ev: TEvent; sc: PScroller;
                           FDR: PFDR
                          ): bool; far; forward;

 {$I _oFDR5.inc}

 {$I _FPL4s_spracovanie.inc}
 {$I _FDRs_spracovanie.inc}


 {$IFDEF PROCESS_FPL4}
  {$I _FPL4_icao.inc}
  {$I _FPL4_tlg.inc}

 {$ENDIF}

 {$IFDEF FPL4_ACT}
  {$I _FPL4_act.inc}
 {$ENDIF}

 {$I _FPL4s_ihandle.inc}
 {$I _FPL4s_prehlad.inc}
 {$I _FPL4s_handle.inc}


 {$IFDEF FPL4_ACT}
  {$I _FPL4s_functions.inc}

 begin
   initialize_FPLs;
 {$ENDIF}

{$ENDIF}
end.

{$I _FPL4s_func.h}
