(*-------------------------------------------------------------------*)
(* App 1.0                                                           *)
(* 1993                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$X+,I-,S-,P-}

unit App;


interface


    uses   Ovr, TypeDef, IO,
           Events, Objects, Views, Scroll,
           NET_def, FIR_def;


    const  APP_CFG      = exe+ext_kod;

           ext_usa      = '.usa';
           APP_USER_CFG = exe+ext_usa;
           USER_CFG     : string = exe+ext_usa;

           EXIT_PASSWORD_LENGTH = 20;

           EXIT_PASSWORD_FDP   : string[20] = '';
           EXIT_PASSWORD_ALES  = {$IFDEF KIEV} 'Nick';
                                 {$ELSE}       'ales007';
                                 {$ENDIF}
           EXIT_PASSWORD_INST  = FIR_adr;

           saveCFG       : bool = true;
           complMESS     : bool = false;

           IS_REFRESH    : bool = false;
           APP_GUI_INIT  : bool = false;


           {$I app_cfg.h}


    type   PApp = ^TApp;

         { --------------------------------------------- }
         { TLocalApp                                     }
         { --------------------------------------------- }
           PAppGui = ^TAppGui;
           TAppGui = object(TGroup)

             AppScroll   : POScrollStream;
             StatusLine  : PGroup; { STATUS }
             last_active : PView;  { posledne aktivne okno }

             constructor Init(_Owner: PApp; x,y,dx,dy: int);
             procedure   ReInit(x,y,dx,dy: int); virtual;

             procedure   Idle(var _Event: TEvent); virtual;
             procedure   HandleEvent(var _Event: TEvent); virtual;

             function    next_active(P: PView): PView; virtual;
             function    prev_active(P: PView): PView; virtual;
             function    set_active (P: PView): bool;  virtual;
           end;


         { --------------------------------------------- }
         { TApp                                          }
         { --------------------------------------------- }
           TApp = object(TGroup)

             {$IFDEF EXIT_PASSWORD}
               exit_password : pchar;
             {$ENDIF}

             AppGui : PAppGui;
             riadok : int;

             constructor Init(_Owner: PGroup; _BarMenu,_LOGO: pointer; _VER,_CR: string);
             procedure   InitApp; virtual;
             destructor  Done; virtual;

             procedure   Idle(var _Event: TEvent); virtual;
             procedure   HandleEvent(var _Event: TEvent); virtual;
             procedure   Run(var _Event: TEvent); virtual;

             procedure   init_LOGO(_LOGO: pointer); virtual;
             procedure   done_LOGO; virtual;

             procedure   ReInit(x,y,dx,dy: int); virtual;
             procedure   Refresh; virtual;

             {$IFDEF EXIT_PASSWORD}
               procedure   set_password(pswd: string);
             {$ENDIF}
             function    confirm_exit: bool;

             procedure   set_btmdXY (dx0,dy0,dx1,dy1: int);

             procedure   writeln  (s: string; cl: byte; ident: string; is_utc: bool);
             procedure   writeln_ (pb: pbytes; size: int; cl: byte; ident: string; is_utc, is_NL: bool); virtual;

             {protected}
             function    EndState (var _Event: TEvent): bool; virtual;


             function    ReadProgramCfg (cfg_fn: string; _dialog: bool): bool; virtual;
             procedure   SaveProgramCfg (cfg_fn: string); virtual;

             procedure   get_app_config (typ : Tnd_typ; sw : Tnd_sw; nd : Tnd_nd;
                                         var data: pchars; var size: word
                                        ); virtual;
             procedure   set_app_config (const data: pchars; size: word); virtual;
             procedure   distribute_app_config; virtual;
           end;


    type   proc_handle_object_event   = function (var _Event: TEvent; O: PObject; FPL: pointer): bool;
           p_proc_handle_object_event = ^proc_handle_object_event;

    const  MainApp   : PApp = nil;
           appGui    : PGroup = nil;

    var    MainEvent : TEvent;



implementation

uses  BIOS, DOS, _Check,
      mouse, keyb, mess, math, str0, utime, sets, sort,
      {$I unit_gr.h},
      AStream, Edit, Menus, Dialog, Lists, help_def, Help,
      CMs, Msg, Kody;


{$I AppGui.inc}

{$I App_.inc}
{$I App_handle.inc}
{$I App_archive.inc}
{$I App_cfg.inc}

begin
  MainAppPtr:= @MainApp
end.