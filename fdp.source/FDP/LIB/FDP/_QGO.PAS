(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 3.0                                              *)
(* (c) Ales Kosice 1993,95  (ab)                                     *)
(* Schopnosti                                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_fdp.h}


{ skratka QGO nezodpoveda schopnostiam, ale je najvystiznejsia pre kod }


unit _QGO;


interface


    uses   TypeDef,
           DB,
           {$I unit_oop.h}, Report,
           {$I unit_net.h},
           _L4_def, Body, _FDP_def, _PLAN;

    {
    ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
    €                             €
    € SCHOPNOSTI                  €
    €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
    }

    {$IFDEF QGO}

      { I _QGO_cnst.h}  { docasne v _FDP_def }
      {$I _QGO_title.h}
      {$I _QGO_plan.h}
      {$I _QGO_func.h}

      function _handle_event_QGO (var _Event: TEvent; O: PObject; QGO: pointer): bool;

    {$ENDIF}


implementation


uses  BIOS, _Check, DOS, IO,
      mem, keyb, mouse, str0, sets, mess, utime, math, sort,
      {$I unit_gr.h},
      Lists,
      Msg, Vypocty, Archiv,
      {$IFDEF PRN} prnt, {$ENDIF}
      _MTK_2,
      FDP_scrl, FDP_msg, FDP_func,
      FDP_edit, form_SYS
      {$IFDEF STATISTIKA} , STA_def  {$ENDIF}
      {$IFDEF ARCHIVE_DAR}, DAR_arch {$ENDIF}
      ;

{$IFDEF QGO}

  const      p_qgo_dbscroller : PScrollDB_FDP = nil;
  procedure  add_QGO(QGO: PQGO); far; forward;


  { ----------------- }
  { QGO               }
  { ----------------- }
  {$I _QGO_plan.cod}
  {$I _QGO_plan.inc}     { save, send    }
  {$I _QGO_plan.drw}
  {$I _QGO_plan.prn}

  {$I _QGO2.inc}         { spracovanie   }

  {$IFDEF PROCESS_QGO}
    {$I _QGO_plan.frm}
    {$I _QGO3.inc}       { spracovanie   }
    {$I _QGO_RPL.inc}    { prehlady RPL }
  {$ENDIF}

  {$I _QGO4a.inc}        { menu          }
  {$I _QGO4.inc}         { prehlad       }

  {$I _QGO_handle.inc}
  { I _QGO_archiv.inc}

  {$I _QGO_send.inc}     { save, send    }
  {$I _QGO_rec.inc}
  {$I _QGO_functions.inc}


begin
  write('Initialize QGO... ');
  {$IFDEF PROCESS_QGO}
   clear_form(@Form_QGO,SIZE_frm_QGO,nil);
  {$ENDIF}
  {kontrola_archivu;}
  writeln('Done.')
{$ENDIF}
end.
