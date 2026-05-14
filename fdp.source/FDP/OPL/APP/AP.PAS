(*-------------------------------------------------------------------*)
(* LETVIS FDP - OPL 1.0                                              *)
(* (c) Ales Kosice 1993  (ab)                                        *)
(* Supervisor                                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_fdp.h}


unit Ap;


interface


    uses  TypeDef,
          {$I unit_gr.h},
          {$I unit_oop.h}, Lists,
          {$I unit_net.h},
          FDP_ap, GUI;


    const  AMC_coor_info = inf_FUA;


         { --------------------------------------------- }
         { Hlavna aplikacia OPL                          }
         { --------------------------------------------- }
    type  POPLapp = ^TOPLapp;
          TOPLapp = object(TFDPapp)

            OPLgui : P_GUI;

            constructor Init;
            procedure   HandleEvent(var _Event: TEvent); virtual;

            procedure   InitEXT_drivers; virtual;
            procedure   InitApp; virtual;

            function    change_gm(gm: TGraphMode; _init,_draw: bool): bool; virtual;
          end;


    var   OPLapp : POPLapp;


implementation


uses DOS, BIOS, IO, DB, _check, keyb, str0, mess, utime, prnt,
     Vypocty, Body, Msg, FDP_msg,
     _L4_def, _FDP_def, _PLAN,
     {$I unit_map.h},
     {$I unit_fdp.h}
     {$I unit_fdf.h}
     {$IFDEF STATISTIKA_OPL} sta_OPL, {$ENDIF}
     {$I unit_ap.h} Menu,
     {$I unit_ext.h},
     _FDP, FDP_func, FDP_fun2, FDP_net;


{$I ap.inc}
{$I ap_handle.inc}  { handle...}


{var SaveMain : TProc;

procedure check_MMI; far;
    begin
      if @SaveMain<>nil then SaveMain;
      if (OPLapp<>nil) and (OPLapp^.OPLgui<>nil) then OPLapp^.OPLgui^.Prekreslit
    end;

begin
  SaveMain:= ACheck;
  ACheck:= check_MMI}

end. { Ap }