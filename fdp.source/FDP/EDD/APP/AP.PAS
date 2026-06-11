(*-------------------------------------------------------------------*)
(* LETVIS FDP - EDD 3.0                                              *)
(* (c) Ales Kosice 1994  (ab)                                        *)
(* Supervisor                                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$D+,L+}    { local debug info so TD can source-step this module }

{$DEFINE EDD}


unit Ap;


interface


    uses  TypeDef,
          {$I unit_gr.h},
          {$I unit_oop.h},
          {$I unit_net.h},
          FDP_ap;


    type  PEDDapp = ^TEDDapp;
          TEDDapp = object(TFDPapp)
            constructor Init;

            procedure   HandleEvent(var _Event: TEvent); virtual;
            procedure   InitEXT_drivers; virtual;

            {$IFDEF MAPY}
              procedure  Draw; virtual;
              procedure  switch_TABLET;
            {$ENDIF}
          end;



implementation

uses DOS, BIOS, IO, DB, _Check,
     math, keyb, str0, mess, msg, utime, mouse,
     AStream,

     _L4_def, _MTK_2, _FDP_def, _FPL_def,
     _PLAN, {$I unit_fdp.h}
     {$I unit_ext.h},
     {$I unit_ap.h}
     EDD_func, FDP_msg, Sector,
     GUI, Menu;

 {$I ap.inc}
 {$I ap_handle.inc}

end. { Ap }

