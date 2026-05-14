(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 1.0                                              *)
(* (c) Ales Kosice 1993  (ab)                                        *)
(* Priestory                                                         *)
(*-------------------------------------------------------------------*)

{$I comp.h}
{$I comp_fdp.h}

{ Pretoze plan moze presahovat do nasledujuceho dna
  (len na 24 hodin...),
  pri inicializacii sa musi prezriet i predchadzajuci den
}


unit _PRZ;


interface


    uses  TypeDef, DB,
          {$I unit_oop.h},
          {$I unit_net.h},
          _MTK_2, _L4_def, _FDP_def,
          _PLAN, _STRIP,
          _NOTAM;


    {
    ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
    €                             €
    € ZIADOSTI O PRIESTORY        €
    €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
    }

    {$IFDEF PRZ}
      {$I _PRZ_title.h}
      {$I _PRZ_func.h}    { ziadosti pre VLIS o pridelenie vzdusneho priestoru }

      {$I _PRN_title.h}
      {$I _PRN_func.h}    { notamy VLIS o prideleni vzdusneho priestoru }

      function  _handle_event_PRZ (var _Event: TEvent; O: PObject; PRZ: pointer): bool;
    {$ENDIF}


implementation

uses  BIOS, _Check, IO,
      keyb, mouse, str0, sets, mess, utime, math, sort, prnt, msg,
      {$I unit_gr.h},
      Lists, Vypocty, Archiv,
      FIR_def, {$I unit_map.h},
      Body, FDP_func,
      form_SYS, FDP_msg, FDP_scrl, FDP_edit
      {$IFDEF STATISTIKA},  STA_def   {$ENDIF}
      {$IFDEF ARCHIVE_DAR}, DAR_arch  {$ENDIF}
      ;


{$IFDEF PRZ}

{ -------------------------------------------------------
   Ziadosti pre VLIS o pridelenie vzdusneho priestoru
  -------------------------------------------------------
}
 const     p_prz_dbscroller : PScrollDB_FDP = nil;
 procedure format_PRZ (PRZ: PPRZ); far; forward;

 {$I _PRZ_ziadost.cod}
 {$I _PRZ_ziadost.inc}
 {$I _PRZ_ziadost.drw}
 {$I _PRZ_ziadost.prn}

 {$I _PRZ2.inc}

 {$IFDEF PRZ_REQUEST}
   {$I _PRZ_ziadost.frm}

   {$I _PRZ3.inc}
 {$ENDIF}

 {$I _PRZ4a.inc}           { handlery pre spracovanie v prehlade }
 {$I _PRZ4.inc}            { prehlad }

 {$I _PRZ_send.inc}        { odoslanie }
 {$I _PRZ_functions.inc}


{ -------------------------------------------------------
   NOTAMY VLIS o pridelenom vzdusnom priestore
  -------------------------------------------------------
}
 {$I _PRN_notam.cod}
 {$I _PRN_notam.inc}

 {$I _PRN2.inc}
 {$I _PRN4a.inc}            { handlery pre spracovanie v prehlade }
 {$I _PRN4.inc}             { prehlad }

 {$I _PRN_send.inc}         { odoslanie }
 {$I _VLIS_rec.inc}


 {$I _PRZ_handle.inc}


begin
  write('Initialize PRZ... ');
  {$IFDEF PRZ_REQUEST}
   clear_form(@frm_PRZ,SIZE_frm_PRZ,nil);
  {$ENDIF}
  writeln('Done.')
{$ENDIF}
end.