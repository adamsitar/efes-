(*-------------------------------------------------------------------*)
(* LETVIS FDP - EDD 3.0                                              *)
(* (c) Ales Kosice 1994  (ab)                                        *)
(* Supervisor                                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}


unit FDP_ap;


interface


    uses  TypeDef,
          {$I unit_gr.h},
          {$I unit_oop.h}, Lists, Report,
          {$I unit_net.h};


    const EN_GRAPH_MODE_SWITCH : bool = true;
          APP_ETHERNET_ADR : TEthernetAdr = (0,0,$C0,$3C,$CC,$DF);


    type  PFDPapp = ^TFDPapp;
          TFDPapp = object(TApp)

            data_initialized: bool;
            {reinitialize_gm: bool;}

            constructor Init(_Owner: PGroup; _BarMenu,_LOGO: pointer; _VER,_CR: string);

            procedure   InitMMI(_Owner: PGroup; _BarMenu,_LOGO: pointer; _VER,_CR: string); virtual;
            procedure   InitData; virtual;

            procedure   InitNET; virtual;
            procedure   InitEXT_drivers; virtual;
            procedure   InitEXT; virtual;

            procedure   InitApp; virtual;
            procedure   InitApp2; virtual;

            procedure   DoneEXT; virtual;
            destructor  Done; virtual;


            function    ReadProgramCfg (cfg_fn: string; _dialog: bool): bool; virtual;
            procedure   SaveProgramCfg (cfg_fn: string); virtual;

            function    ReadUserCfg (_Event: TEvent): bool;
            procedure   SaveUserCfg;


            procedure   distribute_app_config; virtual;
            procedure   get_app_config (typ : Tnd_typ; sw : Tnd_sw; nd : Tnd_nd;
                                        var data: pchars; var size: word
                                       ); virtual;
            procedure   set_app_config (const data: pchars; size: word); virtual;


            procedure   HandleEvent(var _Event: TEvent); virtual;

            function    change_gm(_gm: TGraphMode; _init,_draw: bool): bool; virtual;
          end;



    {$I ..\lib\mnu\_cfg.h}

    function CFG_READ_menu_init (title: string): PSubMenu;
    function CFG_SAVE_menu_init (title: string): PSubMenu;



implementation


uses DOS, BIOS, IO, DB, _Check,
     ovr, mem, math, keyb, str0, mess, utime, prnt, crt, sort, sets,
     AStream,

     {$IFDEF IPX} _IPX, {$ENDIF}
     {$IFDEF PCTCP} PCTCPdef, PCTCP, {$ENDIF}
     NET_utc,

     Vypocty, Body,
     Msg, FDP_msg,

     {$I unit_map.h},

     _L4_def, _MTK_2, _FDP_def, _FPL_def,
     _PLAN, {$I unit_fdp.h}
     {$I unit_fdf.h} _FDP, FDP_NET, FDP_fun2, EDD_func, _SSR,
     {$IFDEF TRENAZER} trnzr, {$ENDIF}
     {$IFDEF ARCHIVE_DAR} DAR_def, DAR_arch, {$ENDIF}

     {$I unit_ext.h},
     {$I unit_ap.h} menu, GUI,

     Sector;


{$I fdp_about.inc}
{$I fdp_password.inc}
{$I fdp_object.inc}

{$I cfg_fdp.inc}
{$I cfg_app.inc}
{$I ..\lib\mnu\_cfg.mnu}

{$I fdp_handle.inc}

end. { Ap_FDP }