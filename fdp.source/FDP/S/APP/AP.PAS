(*-------------------------------------------------------------------*)
(* LETVIS FDP/S 3.0                                                  *)
(* (c) Ales Kosice 1993,95  (ab)                                     *)
(* Supervisor                                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}

unit Ap;


interface


    uses  TypeDef,
          {$I unit_gr.h},
          {$I unit_oop.h},
          {$I unit_net.h},
          FDP_ap;



         { --------------------------------------------- }
         { Hlavna aplikacia OPL                          }
         { --------------------------------------------- }
    type  PSERVERapp = ^TSERVERapp;
          TSERVERapp = object(TFDPapp)

            constructor Init;

            procedure   InitMMI(_Owner: PGroup; _BarMenu,_LOGO: pointer; _VER,_CR: string); virtual;
            procedure   InitEXT_drivers; virtual;
            procedure   DoneEXT; virtual;

            procedure   HandleEvent(var _Event: TEvent); virtual;

            procedure   writeln_(pb: pbytes; size: int; cl: byte; ident: string; is_utc, is_NL: bool); virtual;

            {procedure   get_app_config (typ : Tnd_typ; sw : Tnd_sw; nd : Tnd_nd;
                                        var data: pchars; var size: word
                                       ); virtual;
            procedure   set_app_config (const data: pchars; size: word); virtual;}
          end;



implementation

uses DOS, BIOS, IO, DB, _Check,
     math, keyb, str0, mess, utime,
     AStream,

     _L4_def, _MTK_2, _FDP_def, _FPL_def, FDP_net,
     _PLAN, {$I unit_fdp.h}
     {$I unit_ext.h},
     {$IFDEF STATISTIKA_OPL} sta_OPL, {$ENDIF}
     {$I unit_ap.h}
     GUI, Menu;


{ I ap_ncfg.inc}

{ I ap.inc}
{$I ap_ini.inc}
{$I ap_scroll.inc}
{$I ap_handle.inc}


end. { Ap }
