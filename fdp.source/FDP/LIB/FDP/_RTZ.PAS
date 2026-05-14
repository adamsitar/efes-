(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 3.0                                              *)
(* (c) Ales Kosice 1993,95  (ab)                                     *)
(* Schopnosti                                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_fdp.h}


{ skratka QGO nezodpoveda schopnostiam, ale je najvystiznejsia pre kod }


unit _RTZ;


interface


    uses   TypeDef,
           {$I unit_gr.h}, DB,
           {$I unit_oop.h}, Report,
           {$I unit_net.h},
           _L4_def, Body, _FDP_def;

    {
    ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
    €                             €
    € SCHOPNOSTI                  €
    €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
    }

    {$IFDEF RTZ}

      { I _RTZ_cnst.h}  { docasne v _FDP_def }
      {$I _RTZ_title.h}
      {$I _RTZ_plan.h}
      {$I _RTZ_func.h}

      function _handle_event_RTZ (var _Event: TEvent; O: PObject; RTZ: pointer): bool;

    {$ENDIF}


implementation


uses  BIOS, _Check, DOS, IO,
      mem, keyb, mouse, str0, sets, mess, utime, math, sort, prnt,
      Lists,
      Msg, Vypocty, Archiv,
      _MTK_2,
      FDP_scrl, FDP_msg, FDP_func,
      FDP_edit, form_SYS
      ;

{$IFDEF RTZ}

  procedure  add_RTZ(RTZ: PRTZ); far; forward;


  { ----------------- }
  { RTZ               }
  { ----------------- }
  {$I _RTZ_plan.cod}
  {$I _RTZ_plan.inc}     { save, send    }
  {$I _RTZ_plan.drw}
  {$I _RTZ_plan.prn}

  {$I _RTZ2.inc}         { spracovanie   }

  {$IFDEF PROCESS_RTZ}
    { I _RTZ_plan.frm}
    { I _RTZ3.inc}       { spracovanie   }
    { I _RTZ_RPL.inc}    { prehlady RPL }
  {$ENDIF}

  {$I _RTZ4a.inc}        { menu          }
  {$I _RTZ4.inc}         { prehlad       }

  {$I _RTZ_handle.inc}
  { I _RTZ_archiv.inc}

  {$I _RTZ_send.inc}     { save, send    }
  {$I _RTZ_rec.inc}
  {$I _RTZ_functions.inc}


begin
  write('Initialize RTZ... ');
  {$IFDEF PROCESS_RTZ}
   clear_form(@Form_RTZ,SIZE_frm_RTZ,nil);
  {$ENDIF}
  writeln('Done.')
{$ENDIF}
end.
