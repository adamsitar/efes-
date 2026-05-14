(*-------------------------------------------------------------------*)
(* Event 1.0                                                         *)
(* 1993                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$DEFINE ZHASNI_MYS}


unit Events;


interface


    uses    TypeDef, mouse;


    const { Event codes }
            evMouseClick  = $0001;   { stlacenie buttonu na mysi }
            evMouseDouble = $0002;   { dvojite stlacenie buttonu }
            evMouseDrag   = $0004;   { stlacene a tahane         }
            evMouseMove   = $0008;   { len tahane                }
            evKeyDown     = $0010;
            evCommand     = $0100;
            evBroadcast   = $0200;

          { Event masks }
            evNothing     = $0000;
            evMouse       = $000F;
            evKeyboard    = $0010;
            evMessage     = $FF00;

          { Event masks }
            PositionalEvents : Word = evMouse;
            FocusedEvents    : Word = evKeyboard + evCommand;


    const   ev_mx : int = 0;
            ev_my : int = 0;

    const   TimeOutDouble = 1000;

    const   MouseMotionEvents: bool = false;

    type    TEvCmnd = word;

    type  { Event record }
            PEvent = ^TEvent;
            TEvent = record
              case What: Word of
                evNothing: ();
                evMouse  : (M  : TMouseChar);
                evKeyDown: (Key: char);
                evMessage: (Command: TEvCmnd;     { prikaz           }
                            From   : pointer;  { odkial           }
                            Whom   : pointer;  { komu             }
                            Box    : pointer;  { schranka         }
                            Size   : word;     { velkost schranky }
                            ForAll : bool;     { pre viacerych    }
                            isMail : bool
                           )
              end;


    type    TProc_vE = procedure(var _Event: TEvent);


    procedure GetKeyEvent  (var _Event: TEvent);
    procedure GetMouseEvent(var _Event: TEvent);

    procedure ClearEvent   (var _Event: TEvent; self_adr: pointer);
    procedure SetCommand   (var _Event: TEvent; self_adr: pointer; Command: word);
    procedure SetKeyEvent  (var _Event: TEvent; self_adr: pointer; key: char);

    function  isCommand (_Event: TEvent; cmXXXX: word): bool;
    function  isKey  (_Event: TEvent; kbHot: char): bool;
    function  inKeys (_Event: TEvent; kbHots: TCharSet): bool;



implementation

uses  BIOS,
      math, keyb,keyb_int, str0;


procedure GetKeyEvent(var _Event: TEvent);
    var   ch: char;
    begin
      if kbhit then
         begin
           _Event.What:= evKeyDown;
           ch:= GetKey;
           if ch=kbEsc then kb_clear;
           _Event.Key:= ch
         end
    end;

procedure GetMouseEvent(var _Event: TEvent);
    var   m1,m0 : TMouseChar;
          i1,i0 : int;
          cit, zap : int;
    begin
      if m_hit then
         begin
           cit:= mcit; zap:= mzap; mcit:= mzap;
           i0:= Prev(zap,maxMouseBuff);
           i1:= Prev(i0,maxMouseBuff);
           m0:= mbuffer[i0];
           m1:= mbuffer[i1];
           if (i0<>cit) and (m0.bt=m1.bt) and not(TimeOut(m1.bt, m0.bt, TimeOutDouble)) then
               if ((m0.x=m1.x) and (m0.y=m1.y)) then _Event.What:= evMouseDouble
               else _Event.What:= evMouseDrag
           else if m0.bt<>0 then _Event.What:= evMouseClick;
           _Event.M:= m0 { zapisanie poslednej hodnoty mysi do Eventu }
          {
           if (Next(cit,maxMouseBuff) = zap) then
             if ((m1.x=m2.x) and (m1.y=m2.y) and (m1.bt=m2.bt)) then _Event.What:= evMouseDouble
             else _Event.What:= evMouseClick
           else _Event.What:= evMouseDrag;
           }
         end
      else if     MouseMotionEvents
              and ((mouse_status.stat.x<>0) and (mouse_status.stat.y<>0))
              and ((ev_mx<>mouse_status.stat.x) or (ev_my<>mouse_status.stat.y) ) then
                 begin
                   ev_mx:= mouse_status.stat.x; ev_my:= mouse_status.stat.y;
                   _Event.What:= evMouseMove;
                   _Event.M:= mouse_status.stat
                 end;
          {else check_mouse}
    end;


procedure ClearEvent(var _Event: TEvent; self_adr: pointer);
    begin
      FillChar(_Event,SizeOf(TEvent),0);
      _Event.What:= evNothing;
      _Event.From:= self_adr
    end;

procedure SetCommand(var _Event: TEvent; self_adr: pointer; Command: word);
    begin
      ClearEvent(_Event, self_adr);
      _Event.What    := evCommand;
      _Event.Command := Command;
      _Event.From    := self_adr
    end; { SetCommand }


procedure SetKeyEvent(var _Event: TEvent; self_adr: pointer; key: char);
    begin
      _Event.What := evKeyDown;
      _Event.Key  := key;
      _Event.From := self_adr;
      kb_clear
    end;


function isCommand(_Event: TEvent; cmXXXX: word): bool;
   begin
     isCommand:= ((_Event.What and evMessage) <> 0) and (_Event.Command = cmXXXX)
   end;

function isKey(_Event: TEvent; kbHot: char): bool;
   begin
     isKey:= (_Event.What = evKeyDown) and (upcase(_Event.Key) = kbHot)
   end;


function inKeys(_Event: TEvent; kbHots: TCharSet): bool;
   begin
     inKeys:= (_Event.What = evKeyDown) and (UpCase(_Event.Key) in kbHots)
   end;

end. { Events }