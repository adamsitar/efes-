(*-------------------------------------------------------------------*)
(* Views 1.0                                                         *)
(* 1993,94                                                           *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$DEFINE MYS_VO_VRCHNOM}  { iba posledna aplikacia je aktivna,
                            tvar mysi sa nastavuje len v nej.  }

{$X+,I-,S-,P-}

unit Views;

interface


    uses    TypeDef,
            mouse, keyb,
            {$I unit_gr.h},
            Events, Objects;


    type    cl_view_set = array[false..true,false..true] of byte;
                                {palette,acvive}

    const   clItem     = Cyan;
            clKey      = Yellow;
            clActItem  = LightCyan;
            clActKey   = White;

            cl_Item    : cl_view_set = ((clItem,clActItem),(clItem,clGRf));
            cl_Key     : cl_view_set = ((clKey,clActKey),  (clKey, clGRf));
            bk_Item    : cl_view_set = ((clBUTTON_COLOR,clBUTTON_COLOR),
                                        (clBUTTON_COLOR,{$IFDEF EGAVGA}blue{$ELSE}52{45{green}{$ENDIF})
                                       );


           {$I views.h}


          { --------------------------------------------- }
          { TView                                         }
          { --------------------------------------------- }
    type    PView  = ^TView;
            PGroup = ^TGroup;


          { Abstraktna trieda Pohlad pre odvodenie objektu na obrazovke }
            TView = object(TObject)

               x0,y0,x1,y1 : int;   { pozicia }

               cmXXXX  : word;
               hlpXXX  : PChar;

               visible : bool;
               active  : bool;      { pohlad je aktivny - pouzivatelsky vstup smeruje najprv k nemu }
               istview : bool;

               Local   : TProc;
               S_run   : bool;
               R_err   : bool;      { chyba pocas fungovania objektu }

               MCursor : TMCursor;
               bk0     : byte;

               public
               constructor Init(_Owner: PGroup; x,y,dx,dy: int);

               procedure   Run(var _Event: TEvent); virtual;
               procedure   RunLocalFunc(var _Event: TEvent; Info: PChar); virtual;

             { metody predefinovavane odovodenymi triedami }
               function    HelpDisplayed (var _Event: TEvent): bool; virtual;
               function    EndState (var _Event: TEvent): bool; virtual;
               procedure   HandleEvent(var _Event: TEvent); virtual;
               procedure   Draw; virtual;     { vykresli obrazovku programu   }
               procedure   Image; virtual;

               procedure   Mail (_Whom: PObject; _Command: Word; _ForAll: TNumber;
                                 _mail: pointer; _size: word
                                ); virtual;
               procedure   MailE(var _Event: TEvent;
                                 _Whom: PObject; _Command: Word; _ForAll: TNumber;
                                 _mail: pointer; _size: word
                                ); virtual;

               procedure   show; virtual;
               procedure   hide; virtual;
               procedure   visibility(is_visible: bool);

             { }
               procedure   XY(x,y,dx,dy: int);
               procedure   MoveRel(dx,dy: int); virtual;
               procedure   ReSize(dx,dy: int); virtual;
               procedure   ReInit(x,y,dx,dy: int); virtual;

               function    inView(x,y: int): bool; virtual;
               function    isClicked(_Event: TEvent): bool;
               procedure   get_reg_size(S: PRegionSize); virtual;

               procedure   m_shape; virtual;  { nastavenie tvaru kurzora mysi }

               public
             { udalosti }
               procedure   Idle(var _Event: TEvent); virtual;  { dotatocna kontrola pre GetEvent }

             { protected }
               procedure   ActiveOn; virtual;
               procedure   ActiveOff; virtual;
            end;


          { --------------------------------------------- }
          { TGroup                                        }
          { --------------------------------------------- }
          { Abstraktna trieda Skupina pre zoskupenie
            viacerych pohladov na jednom }
            TGroup = object(TView)

              MouseSave  : bool;
              ScreenSave : bool;    { = false-> zakladny objekt, neda sa presuvat }
              ScreenDesc : int;
              ScreenPtr  : TRegionSize;

              check_idle_all : bool;
              slow_done_app  : bool;
              on_board : bool;

              in_frame : bool;    { = true, ak vsetky objekty TGroup su v jej hraniciach }

              PIS          : bool;  { nad winACC nie je otvorene ziadne ine okno }
              PREPIS       : real;  { winACC bola aktualizovana a PIS bolo false }
              PREPISANE    : real;  { posledny prepis }
              s_prekreslit : bool;

              public
            { predefinovanie zdedenych procedur }
              constructor Init(_Owner: PGroup; x,y,dx,dy: int);

              procedure   Draw; virtual;                     { vykresli obrazovku programu       }

              procedure   Run(var _Event: TEvent); virtual;
              procedure   Idle(var _Event: TEvent); virtual;
              procedure   HandleEvent(var _Event: TEvent); virtual;

              procedure   MoveRel(dx,dy: int); virtual;
              procedure   ReSize(dx,dy: int); virtual;
              function    inView(x,y: int): bool; virtual;

              procedure   get_reg_size(S: PRegionSize); virtual;
              procedure   m_shape; virtual;          { nastavenie tvaru kurzora mysi     }

            { nove procedury }
              function    GetView(P: PObjectReg): PView;

              function    is_to_be_Run: bool; virtual;
              procedure   InitApp; virtual;
              procedure   InitApp2; virtual;
              procedure   DoneApp2; virtual;
              procedure   DoneApp; virtual;

              function    InitRun(var _Event: TEvent; var xl,yl: int; var isapp,isrun: bool): bool;
              procedure   DoneRun(var _Event: TEvent; xl,yl: int; isapp,isrun: bool);

              procedure   Centre; virtual;

              function    SaveScreen: int; virtual;
              function    PushScreen: int;

              procedure   RestoreScreen; virtual;
              procedure   PopScreen;

              function    ma_sa_prekreslit: bool; virtual;
              procedure   Prekreslit; virtual;
              procedure   Prekreslenie; virtual;
            end;


implementation

uses  BIOS, DOS, IO, _Check,
      keyb_int, mem, math, mess, str0,
      CMs, Msg;

const s_nem: bool = false; { semaphor not enough memory }


{$I progstat.inc}  { prachsprosty vypis }

{$I views0.inc}    { TView  }
{$I views1.inc}    { TGroup }
{$I view_shp.inc}  { prepinanie kurzorov mysi }


begin
  mouse.m_shape:= m_shape;
  {SaveMain:= Check
  MainProgram:= check_views}
end. { Views }