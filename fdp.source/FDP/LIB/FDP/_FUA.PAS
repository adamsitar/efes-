(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 3.9                                              *)
(* (c) Ales Kosice 1993,99  (ab)                                     *)
(* Priestory                                                         *)
(*-------------------------------------------------------------------*)

{$I comp.h}
{$I comp_fdp.h}

{ spracovanie sprav o planovanom vyuziti vzdusneho priestoru
  na nasledujuci 24 hodinovy casovy interval
}

unit _FUA;


interface


    uses  TypeDef, DB,
          AStream,
          {$I unit_gr.h},
          {$I unit_oop.h}, Lists,
          {$I unit_net.h},
          {$I unit_map.h},
          _L4_def, _MTK_2, _L4_func, _FDP_def, _FPL_def,
          FDP_edit,
          _PLAN, _STRIP;


    {
    ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
    €                             €
    € PRIESTORY                   €
    €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
    }

    { IFDEF PRS}

     {$IFDEF FUA}
      { I _FUA_cnst.h}
      { I _FUA_err.h}
      {$I _FUA_title.h}
      {$I _FUA_mnu.h}
      {$I _FUA_plan.h}
      {$I _FUA_functions.h}

      function  _handle_event_FUA (var _Event: TEvent; O: PObject; FUA: pointer): bool;
     {$ENDIF}

    { ENDIF}


implementation

uses  BIOS, _Check, DOS, IO,
      keyb, mouse, str0, sets, mess, utime, math, sort, prnt, msg, mem,
      Vypocty, Archiv,
      FIR_def, Body,
      FDP_scrl, FDP_msg, form_SYS,
      FDP_func, FDP_fun2,
      _NOTAM {$IFDEF PRS}, _PRS {$ENDIF}
      {$IFDEF ARCHIVE_DAR},     DAR_arch  {$ENDIF}
      {$IFDEF STATISTIKA} ,     STA_def   {$ENDIF}
      ;


{ IFDEF PRS}
{$IFDEF FUA}

  {$I _FUA_.inc}       { niektore priestory nemusia byt schvalovane }

  {$IFDEF FUA_DATA}
   {$I _FUA_plan.inc}  { spracovanie sprav AUP, UUP }
  {$ENDIF}

  {$IFDEF PROCESS_FUA}
   const AUP_kod  = pathAUP+key_aup+ext_kod;
         UUP_kod  = pathUUP+key_uup+ext_kod;

   {$I _FUA_frm.h}
   {$I _FUA.frm}
  {$ENDIF}

  {$IFDEF FUA_DATA}
   {$I _FUA2.inc}
   {$I _FUA4.inc}
   {$I _FUA_net.inc}
  {$ENDIF}


 {$I _FUA_handle.inc}


var  SaveExit : pointer;

procedure done_FUA;
    begin
      ExitProc:= SaveExit;
      done_FUA_;
    end;

procedure init_FUA;
    begin
      SaveExit:= ExitProc;
      ExitProc:= @done_FUA;

      write('Initialize FUA... ');
      init_FUA_;
      writeln('Done.');
    end;

begin
 init_FUA;
{$ENDIF}
{ ENDIF}
end.