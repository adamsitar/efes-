(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 3.0                                              *)
(* (c) Ales Kosice 1993,5  (ab)                                      *)
(* Diverzie                                                          *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_fdp.h}

{ Pod "end." je uvedene pouzivanie konstant stavu }


unit _DVZ;


interface


    uses   TypeDef, sets, DB,
           {$I unit_net.h},
           {$I unit_oop.h},
           Body,
           _L4_def, _FDP_def, _FPL_def, FDP_edit;

    {
    ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
    Û                             Û
    Û DIVERZIE                    Û
    ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
    }

    {$IFDEF DVZ}
     { I _DVZ_cnst.h}  { docasne v _FDP_def }
     {$I _DVZ_title.h}
     {$I _DVZ_plan.h}
     {$I _DVZ_func.h}

     function _handle_event_DVZ (var _Event: TEvent; O: PObject; DVZ: pointer): bool;
    {$ENDIF}


implementation

uses  BIOS, _Check, IO, DOS,
      keyb, mouse, str0, mess, utime, math, sort, prnt,
      {$I unit_gr.h},
      Msg, _MTK_2,
      Vypocty, Archiv, Status,
      _PLAN, _STRIP,
      form_SYS, FDP_msg, FDP_scrl, FDP_func
      {$IFDEF STATISTIKA}, STA_def {$ENDIF}
      ;


{$IFDEF DVZ}

  const      p_dvz_dbscroller : PScrollDB_FDP = nil;
  procedure  add_DVZ(DVZ: PDVZ); far; forward;

  {
    Pouzivane cnst stavu:  -disk,
                           -prop,
                           -acc,    - schvalena
                           -active  - vyhlasena
                           -finish, - cancel.

                           -server -> sprava nebola potvrdena serverom
                           -let    -> sprava nebola potvrdena letiskom
                           -warn   -> varovanie pred zrusenim


    Kombinacie konstant    -prop             -> ziadost o diverziu
                           -read+prop+cancel -> zamietnuta ziadost o diverziu
                           -read+acc         -> schvalena

                           -prop+active        -> odoslanie na diverziu
                           -read+active+cancel -> zamietnutie odoslania na diverziu
                           -read+active        -> schvalenie

                           -read+warn        -> waruuuj
                           -read+cancel      -> zrusenie


  const  dvz_neschvalena = cnst_read+cnst_prop+cnst_cnl;
         dvz_schvalena   = cnst_read+cnst_prop+cnst_cnl;

  }

  const cnst_dvz_req = cnst_prop;
        cnst_dvz_dec = cnst_dec+cnst_cnl;  { zamietnutie ziadosti o div }
        cnst_dvz_acc = cnst_acc;           { schvalenie ziadosti o div  }

        cnst_dvz_zac = cnst_active;
        cnst_dvz_zaa = cnst_dvz_zac+cnst_dvz_acc;
        cnst_dvz_zad = cnst_dvz_zac+cnst_dvz_dec;
        cnst_dvz_kon = cnst_stat_arr;
        cnst_dvz_alr = cnst_warn;
        cnst_dvz_acn = cnst_warn+{cnst_dvz_acc+cnst_dvz_zac+}cnst_cnl;  { zrusenie drzanej diverzie ineho letiska }


  { ----------------- }
  { DVZ               }
  { ----------------- }

  {$I _DVZ_plan.cod}
  {$I _DVZ_proc.inc}
  {$I _DVZ_plan.inc}
  {$I _DVZ_plan.drw}
  {$I _DVZ_plan.prn}

  {$I _DVZ2.inc}

  {$IFDEF PROCESS_DVZ}
    {$I _DVZ_plan.frm}     { poziadavka na diverziu }
    {$I _DVZ_req.frm}      { spracovanie prichodivsich i pozdrzanych ziadosti, vystraha pred zrusenim }
    {$I _DVZ_req.inc}      { spracovanie prichodivsich i pozdrzanych ziadosti, vystraha pred zrusenim }

    {$I _DVZ3.inc}
  {$ENDIF}

  {$I _DVZ4a.inc}
  {$I _DVZ4.inc}

  {$I _DVZ_send.inc}
  {$I _DVZ_rec.inc}

  {$I _DVZ_functions.inc}
  {$I _DVZ_handle.inc}
  { I _DVZ_archiv.inc}


begin
 {$IFDEF PROCESS_DVZ}
   write('Initialize DVZ... ');
   clear_form(@Form_DVZ,SIZE_frm_DVZ,nil);
   pozri_ziadosti_o_DVZ(nil);
   writeln('Done.');
 {$ENDIF}
 {kontrola_archivu;}
{$ENDIF}
end.
