(*-------------------------------------------------------------------*)
(* LETVIS FDP - ZAMESTNANIA                                          *)
(* (c) Ales Kosice 1993,95  (ab)                                     *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_fdp.h}



unit _ZAM;


interface


    uses   TypeDef,
           DB,
           {$I unit_net.h},
           {$I unit_oopt.h},
           FIR_def, _L4_def, Bod_def, _FDP_def,
           _PLAN, _STRIP,
           FDP_func, FDP_fun2;


    {
    ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
    €                             €
    € ZAMESTNANIA                 €
    €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
    }

    {$IFDEF ZAM}
      { I _ZAM_cnst.h}
      {$I _ZAM_title.h}
      {$I _ZAM_plan.h}
      {$I _ZAM_func.h}

      {$I _oZAM.h}

      function _handle_event_ZAM (var _Event: TEvent; O: PObject; ZAM: pointer): bool;
    {$ENDIF}


implementation


uses  DOS, BIOS, _Check, IO,
      keyb, mouse, str0, sets, mess, utime, math, sort, prnt, msg,
      {$I unit_gr.h},
      Lists,
      Vypocty, Archiv,

      _MTK_2,
      Body, {$I unit_map.h},
      FDP_scrl, FDP_msg, FDP_edit, form_SYS

      {$IFDEF ARCHIVE_DAR}, DAR_arch  {$ENDIF}
      {$IFDEF STATISTIKA} , sta_def, sta_obj    {$ENDIF}
      ;


{$IFDEF ZAM}

  const    p_zam_dbscroller : PScrollDB_FDP = nil;
  procedure  add_ZAM (ZAM: PZAM); far; forward;

  {$I _ZAM_plan.cod}
  {$I _ZAM_plan.vyp}
  {$I _ZAM_plan.inc}     { save, send           }
  {$I _ZAM_plan.drw}
  {$I _ZAM_plan.prn}

  {$I _ZAM2.inc}         { zakladne spracovanie }

  {$IFDEF PROCESS_ZAM}
   {$I _ZAM_frm.h}
   {$I _ZAM_plan.frm}

   {$I _ZAM3.inc}        { spracovanie dat      }
   {$I _ZAM_RPL.inc}     { prehlady RPL         }
  {$ENDIF}

  {$I _ZAM4a.inc}        { handlery             }
  {$I _ZAM4.inc}         { prehlad              }

  {$I _ZAM5.inc}         { objekt...            }
  {$I _ZAM10.inc}


  {$I _ZAM_send.inc}     { odoslanie }
  {$I _ZAM_rec.inc}
  {$I _ZAM_functions.inc}
  {$I _ZAM_handle.inc}
  { I _ZAM_archiv.inc}


begin
  write('Initialize ZAM... ');
  {$IFDEF MAPY}
    polomer_ZAM:= Limit(read_cfg_word(SYSTEMcfg,cfg_polomer_ZAM,polomer_ZAM),3,30, 0);
  {$ENDIF}
  {$IFDEF PROCESS_ZAM}
    clear_form(@frm_ZAM,SIZE_frm_ZAM,nil);
  {$ENDIF}
  {kontrola_archivu;}
  writeln('Done.')
{$ENDIF}
end.