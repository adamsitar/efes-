(*-------------------------------------------------------------------*)
(* LETVIS FDP - Dalsie spracovanie FPL                               *)
(* (c) Ales Kosice 1993,98  (ab)                                     *)
(* Spracovanie planov                                                *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_fdp.h}


unit _FDP;


interface


    uses  TypeDef,
          {$I unit_gr.h},
          {$I unit_net.h},
          {$I unit_oop.h},
          _L4_def, _FDP_def;


    {$I _fdp_func.h}

    function _handle_event_FDP (var _Event: TEvent; O: PObject; p: pointer): bool;


implementation

uses  _check, BIOS, IO, DB, prnt, mouse, math, utime,

      Msg, FDP_msg,
      
      {$I unit_map.h},
      {$I unit_ap.h}
      _PLAN, {$I unit_fdp.h} frm_FPL,
      {$I unit_ext.h},

      ParStr;


var  SaveMainA : TProc;
     SaveMainD : TProc;

procedure checkA_FDP; forward;
procedure checkD_FDP; forward;


{$I _FDP_vykreslenie.inc}
{$I _FDP_spracovanie.inc}
{$I _FDP_koordinacia.inc}


procedure checkA_FDP;
    begin
      if @SaveMainA<>nil then SaveMainA;

      pozri_spracovanie_planov_;

      {$IFDEF MAPY}
       pozri_vykreslenie;
      {$ENDIF}

      pozri_koordinaciu;

      {$IFDEF STATUS}
       pozri_indikatory_STATUS;
      {$ENDIF}

      ZMENIL_SA_CAS:= false;
    end;

procedure checkD_FDP;
    begin
      if @SaveMainD<>nil then SaveMainD;
      pozri_spracovanie_planov_so_semaformi;
    end;

{$I _FDP_inicializacia_struktur.inc}
{$I _FDP_handle_event.inc}


begin
 {$IFDEF MAPY}
  p_show_targets:= _FDP.show_targets;
  p_hide_targets:= _FDP.hide_targets;
 {$ENDIF}

  fdp_co_ordinate_procedure:= _FDP._fdp_co_ordinate_procedure
end. { _FDP }