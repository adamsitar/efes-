(*-------------------------------------------------------------------*)
(* LETVIS FDP/EDD                                                    *)
(* (c) Ales Kosice 1992,94 (ab)                                      *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-}

unit GUI;

interface


    uses  TypeDef,
          Events, Views, Button;

    const dMapaY0 = btHEIGHT + 3;
          dMapaY1 = btHEIGHT + 8;


    type  P_GUI = ^T_GUI;
          T_GUI = object(TGroup)

            private
            last_active : PView;   { posledne aktivne okno   }

            public
            constructor Init(_Owner: PGroup);

            procedure   HandleEvent(var _Event: TEvent); virtual;
            procedure   Draw; virtual;

            procedure   edd_status;
            procedure   prekreslenie; virtual;

          end;


    var   EDDgui: P_GUI;


implementation

uses _check, mouse, bios, keyb, str0, math, utime, io,
     {$I unit_gr.h},
     Scroll, App, help_def, Help, CM,
     Hodiny,
     _L4_def, FDP_ap, _FDP_def, NET_def,
     {$IFDEF SECTORS}
       Sector,
     {$ENDIF}
     {$IFDEF FPL0}
      _FPL_def, _FPL, _FPLc, _FPLm,
     {$ENDIF}
     {$IFDEF MAPY}
       MapyDef, Mapy,
     {$ENDIF}
      _FDP, _PLAN, PROP, ACC_ini, ACC;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TGUI                                                     €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

{$I gui_title.h}
{$I gui_obj.inc}
{$I gui_info.inc}

{$I gui_handle.inc}

var  SaveMain : TProc;

procedure check_GUI; far;
    begin
      if @SaveMain<>nil then SaveMain;

      {$IFDEF SECTORS}
      {$ENDIF}

      if (not PLANZET_MAPA) or ZMENIL_SA_CAS_SPAT then
         begin
           ZMENIL_SA_CAS_SPAT:= false;

           winPROP^.Prekreslit;
           winACC^.Prekreslit;
           EDDgui^.Prekreslit;
         end;

      winPROP^.check
    end;

begin
  SaveMain:= ACheckProcessesA;
  ACheckProcessesA:= check_GUI
end. { GUI }