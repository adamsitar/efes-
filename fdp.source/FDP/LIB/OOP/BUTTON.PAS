(*-------------------------------------------------------------------*)
(* Button 2.0                                                        *)
(* 1993,4                                                            *)
(*-------------------------------------------------------------------*)
{$I comp.h}

unit Button;


interface

    uses  TypeDef, keyb,
          graph_h, {$IFDEF BGI} Graph {$ELSE} Graphs {$ENDIF}, SVGA, BGIgraph,
          Events, Objects, Views;


    const cnst_HotKey = '~';

          dbtWIDTH   = 74;   { sirka TDialogButton }
          dbtDXoff   = 10;
          dbtDX      = 4;

          dbtHEIGHT  = 18;   { vyska     -//-      }
          dbtDYoff   = 10;
          dbtDY      = 10;

          btHEIGHT   = 14;   { vyska  ostatnych    }
          icWIDTH    = 14;

          winHEIGHT  = btHEIGHT + 20;
          winDXoff   = 10;
          winDX      = 28*2 + winDXoff;


          icKey  = white;   { vysvietena klavesa na dialogovom buttone }
          {$IFDEF SPEA}
            icText = clGRa; { text }
          {$ELSE}
            icText = clGRa;
          {$ENDIF}


    const kbMOVE   = {$IFDEF DEBUG} kbCtrlF5 {$ELSE} kbAltM {$ENDIF};
          clMOVE   = cyan;


    const grBUTTON_COLOR: array[btOFF..btON] of byte = (clBUTTON_COLOR,clBUTTON_COLOR-1);


          { --------------------------------------------- }
          { TButton                                       }
          { --------------------------------------------- }
    type  { Typ Tlacidlo - Ok: odvodit Enter a Esc        }
          PButton = ^TButton;
          TButton = object(TView)
          { protected }
            local_ev : bool;  { lokalny event - vysiela sa cez mail, inak sa don len zapise cmXXXX }

            stat     : TbtStat;
            btSize   : byte;
            click    : byte;  { impulzny spinac, zostane v polohe           }

            kbHot    : char;  { znak po stlaceni ktoreho sa aktivuje button }
            kbAltHot : char;  { -- // -- ;  nie je povinnoxt inicializovat  }
            kbAct    : char;

            key      : string[5];
            title    : Pchar;
            centr_txt: bool;
            xk       : int;
            ct,ck    : byte;  { farba textu a klavesy }

            public
            constructor Init(_Owner: PGroup; x,y, dx,dy: int;
                             _kbHot: char; _cmXXXX: word; _title: string;
                             _click, _ck,_ct: byte
                            );
            destructor  Done; virtual;
            procedure   HandleEvent(var _Event: TEvent); virtual;

            function    inView(x,y: int): bool; virtual;
            procedure   Draw; virtual;

            procedure   Text(_ct,_ck: byte); virtual;
            procedure   Button;

            procedure   new_title(_title: string; _draw: bool);
            procedure   new_title_key(_title: string; _draw: bool);
            procedure   _do_it(var _Event: TEvent); virtual;

            procedure   OnOff(_stat: TbtStat);

            procedure   check; virtual;
          end;


          PFButton = ^TFButton;
          TFButton = object(TButton)
            bk : byte;

            constructor Init(_Owner: PGroup; x,y, dx,dy: int;
                             _kbHot: char; _cmXXXX: word; _title: string;
                             _click, _ck,_ct, _bk: byte
                            );

            procedure   Draw; virtual;
          end;


          { --------------------------------------------- }
          { TDialogButton                                 }
          { typ Windows tlacidla                          }
          { --------------------------------------------- }
    type  PDialogButton = ^TDialogButton;
          TDialogButton = object(TButton)
            constructor Init(_Owner: PGroup; x,y: int; _kbHot: char; _cmXXXX: word; _title: string; _ck,_ct: byte);
          end;


          { --------------------------------------------- }
          { TIcon                                         }
          { Tlacidlo len so symbolom                      }
          { --------------------------------------------- }
    type  PIcon = ^TIcon;
          TIcon = object(TButton)
            private
            icon: pointer;

            public
            constructor Init(_Owner: PGroup; x,y, size: int; _kbHot: char; _cmXXXX: word; _icon: pointer);
            procedure   Draw; virtual;
          end;


          { --------------------------------------------- }
          { TTextIcon                                     }
          { Tlacidlo s popisom a symbolom                 }
          { --------------------------------------------- }
    type  PTextIcon = ^TTextIcon;
          TTextIcon = object(TIcon)
            xi,yi: int;

            constructor Init(_Owner: PGroup; x,y: int; _xi,_yi: int;
                             _kbHot: char; _cmXXXX: word;
                             _title: string; _icon: pointer
                            );
            procedure   Draw; virtual;
          end;


          { --------------------------------------------- }
          { TbtList                                       }
          { --------------------------------------------- }
    type  PbtList = ^TbtList;
          TbtList = object(TTextIcon)
            constructor Init(_Owner: PGroup; x,y: int);
          end;


          { -------------------------- }
          { Tlacidlo - Ok pre Windows  }
    type  { -------------------------- }
          PbtOk = ^TbtOk;
          TbtOk = object(TTextIcon)
             constructor Init(_Owner: PGroup; x,y: int; _kbHot: char);
          end;


          { --------------------------- }
          { TbtEsc                      }
          { --------------------------- }
    type  PbtEsc = ^TbtEsc;
          TbtEsc = object(TIcon)
             constructor Init(_Owner: PGroup; x,y: int);
             procedure   HandleEvent(var _Event: TEvent); virtual;
          end;


          { --------------------------- }
          { Tlacidlo - Cancel           }
    type  { --------------------------- }
          PbtTCancel = ^TbtTCancel;
          TbtTCancel = object(TTextIcon)
            constructor Init(_Owner: PGroup; x,y, dx: int; _cmXXXX: word; _title: string);
          end;


          { --------------------------- }
          { Tlacidlo - Esc pre Windows  }
    type  { --------------------------- }
          PbtCancel = ^TbtCancel;
          TbtCancel = object(TbtTCancel)
            constructor Init(_Owner: PGroup; x,y: int);
          end;


          { --------------------------- }
          { TbtMove                     }
          { --------------------------- }
    procedure _set_rectangle(x0m,y0m,x1m,y1m: int; xm,ym: int);
    procedure _move_rectangle(var x0m,y0m,x1m,y1m: int; dx,dy: int);
    procedure _restore_rectangle(x0m,y0m,x1m,y1m: int);
    function  _move_by_key(var x0m,y0m,x1m,y1m: int): bool;
    function  _move_by_drag(var x0m,y0m,x1m,y1m: int): bool;

    type  PbtMove = ^TbtMove;
          TbtMove = object(TIcon)
            MainOwner : PGroup;

            public
            constructor Init(_Owner, _MainOwner: PGroup; x,y: int);
            procedure   HandleEvent(var _Event: TEvent); virtual;
          end;


          { --------------------------------------------- }
          { TWindow                                       }
          { --------------------------------------------- }

    function  GetWindowSize(_title: string): word; { navrhne velkost okna vzhaladom na hlavicku }
    procedure get_win_btXY(P: PView; pod: byte; pos: int; var _x0,_y0: int);

    const    dx_Window_text = 10;
             dy_Window_text = 35;

    type  { Okno a la Kaco                                }
          PWindow = ^TWindow;
          TWindow = object(TGroup)
            {protected}
            btNil   : PIcon;
            btMove  : PbtMove;
            btEsc   : PbtEsc;
            btTitle : PButton;
            btSize  : byte;

            text    : pointer; { procedura pre vypis informacie Tproc_iiiip }
            text_p  : pointer; { parametre pre proceduru text }
            xp,yp   : pointer;
            own_img : bool;


            public
            constructor Init (_Owner: PGroup; x,y, dx,dy: int;
                              _kbHot: char; _cmXXXX: word;
                              _title: string; _move: bool
                             );
            procedure   MoveWin (var _x,_y: int; var _mode: int);
            destructor  Done; virtual;

            procedure   Draw;   virtual;
            procedure   Draw_;  virtual;
            procedure   Centre; virtual;
            procedure   Image;  virtual;

            procedure   set_text(_text,_text_p: pointer);
            function    get_width: word; virtual;
            procedure   get_btXY(pod: byte; pos: int; var _x0,_y0: int); virtual;
          end;


          { --------------------------------------------- }
          { TWindows                                      }
          { --------------------------------------------- }
    type  { Okno a la Kaco                                }
          PWindows = ^TWindows;
          TWindows = object(TWindow)
          { buttony }
            btOk    : PbtOk;
            btCancel: PbtTCancel;
            pocet   : byte;      { pocet bez Ok a Cancel            }

            constructor Init(_Owner: PGroup; x,y, dx,dy: int; _kbHot: char;
                             _cmXXXX: word; _title: string; _text: string;
                             _move: bool; _dole, _pocet: byte; _altk : bool
                             );
          end;


implementation

uses str0, BIOS, _Check,
     math, mouse, Msg,
     CMs;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TButton                                                  €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TButton.Init(_Owner: PGroup; x,y, dx,dy: int;
                         _kbHot: char; _cmXXXX: word; _title: string;
                         _click, _ck,_ct: byte
                        );
      begin
        inherited Init(_Owner, x,y, dx,dy); MCursor:= RUKA;
        cmXXXX := _cmXXXX; local_ev:= true;
        stat:= btOFF; click:= _click; btSize:= btNorm;
        ct:= _ct; ck:= _ck; bk0:= clBUTTON_COLOR;
        title:= nil; centr_txt:= true;
        kbHot:= _kbHot; kbAltHot:= kbHot; kbAct:= kbHot;
        new_title(_title,false)
      end; { TButton.Init }

destructor TButton.Done;
     begin
      { inherited Done; -> nepredpoklada sa, ze je to skupina }
       StrDispose(title)
     end;

procedure TButton._do_it(var _Event: TEvent);
    begin
      OnOff(TbtStat(not bool(stat)));
      ClearEvent(_Event);
      if local_ev then MailE(_Event, Owner, cmXXXX, One, nil,0)
      else SetCommand(_Event, cmXXXX);
      if bool(click) then
         begin
           Wait(1,nil);
           OnOff(TbtStat(not bool(stat)))
         end;
    end;

procedure TButton.HandleEvent(var _Event: TEvent);
    begin
      if not visible then Exit;
      if      (cmXXXX<>cmNil) and (not isCommand(_Event,cmXXXX)) {kbHot <> kbNoKey) }
         and  (      isClicked(_Event)
               or  (     (_Event.What=evKeyDown)
                     and (    (_Event.key in[kbHot,kbAltHot])
                           or (upcase(_Event.key) in[kbHot,kbAltHot])
                           or (     Active
                                and (   (_Event.key=kbAct)
                                     or (upcase(_Event.key)=kbAct)
                                    )
                              )
                         )
                   )
             ) then _do_it(_Event)
    end;


function TButton.inView(x,y: int): bool;
   begin
     inView:= visible and inRectangle(x,y, x0,y0,x1,y1)
   end;


procedure TButton.Draw;
    var   bp : bool; x,y, xl,yl : int;
    begin
      if not visible then Exit;
      m_off(bp, xl,yl);
      Button;
      {$IFDEF SPEA} if stat=btON then SetBkColor(grBUTTON_COLOR[btON]) else SetBkColor(clBUTTON_COLOR); {$ENDIF}
      if centr_txt then x:= x0+Centruj(x1-x0,StrLen(title) * dx_ch)
      else x:= x0+dx_ch;
      y:= (y1+y0+dy_bt) shr 1;
      SetColor(ct); OutTextXy(x,y, StrPas(title));
      if (stat=btOFF) and (xk <> 0) then
         begin
           SetColor(ck); OutTextXY(x+((xk-1)*dx_ch),y, key);
        end;
      m_on(bp, xl,yl)
    end;  { TButton.Draw }


procedure TButton.Text(_ct,_ck: byte);
    var   bp : bool; x,y, xl,yl : int;
    begin
      m_off(bp, xl,yl);
      ct:= _ct; ck:= _ck;
      if centr_txt then x:= x0+Centruj(x1-x0,StrLen(title)*dx_ch)
      else x:= x0+dx_ch;
      y:= (y1+y0+dy_bt) shr 1;
      SetColor(ct); OutTextXY(x,y, StrPas(title));
      if xk <> 0 then
        begin
          SetColor(ck); OutTextXY(x+((xk-1)*dx_ch),y, key)
        end;
      m_on(bp, xl,yl)
    end;

{
 pri stlacenom butone je pozadie tmavsie
}
procedure TButton.Button;
    begin
      BGIgraph.Button(x0,y0,x1,y1, grBUTTON_COLOR[stat], btSize,stat)
    end; { Button }

procedure TButton.OnOff(_stat: TbtStat);
    begin
      stat:= _stat;
      Draw
    end; { TButton.OnOff }


procedure TButton.new_title(_title: string; _draw: bool);
    begin
      StrDispose(title);
      if _draw then if x1-x0 < (length(_title){+1}) shl 3 then _title:= copy(_title,1,(x1-x0) shr 3 - 4)+'...';
      key:= GetStr(_title,Limit(Pos(cnst_HotKey,_title), 1,2, 0),[cnst_HotKey]);
      xk:= Pos(cnst_HotKey,_title);
      if (kbHot = kbNoKey) and (key <> '') then get_HotKey(kbHot,_title);
      title:= StrPasNew(DelChar(_title,[cnst_HotKey]));
      if _draw then Draw
    end;

procedure TButton.new_title_key(_title: string; _draw: bool);
    begin
      new_title(_title,_draw);
      get_HotKey(kbHot,_title);
    end;


procedure TButton.Check;
    begin
    end;



{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TFButton                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

constructor TFButton.Init(_Owner: PGroup; x,y, dx,dy: int;
                          _kbHot: char; _cmXXXX: word; _title: string;
                          _click, _ck,_ct,_bk: byte
                         );
      begin
        inherited Init(_Owner, x,y, dx,dy, _kbHot,_cmXXXX,_title,_click, _ck,_ct);
        bk:= _bk
      end;

procedure TFButton.Draw;
    var   bp: bool; xl,yl : int;
    begin
      if not visible then Exit;
      m_off(bp, xl,yl);
      BGIgraph.Button(x0,y0,x1,y1,clBUTTON_COLOR,btSize,stat);
      fillwin(x0+2,y0+2,x1-2,y1-2,bk);
      WriteCentr(x0,x1,y0+2,y1, StrPas(title), ct);
      if (stat=btOFF) and (xk <> 0) then
         begin
           SetColor(ck);
           OutTextXY(x0+Centruj(x1-x0,StrLen(title) * dx_ch)+1+((xk-1) * dx_ch), (y1+y0+dy_bt+2) shr 1, key);
        end;
      m_on(bp, xl,yl);
    end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TDialogButton                                            €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TDialogButton.Init(_Owner: PGroup; x,y: int; _kbHot: char;
                               _cmXXXX: word; _title: string; _ck,_ct: byte
                              );
      var   l1,l2: byte;
      begin
        l1:= length(delchar(_title,['~']));
        l2:= dbtWIDTH shr 3;
        if inRange (l1,l2-1,l2+1) then {centr_txt:= true}
        else _title:= inschar(cut_(_title), l2{-1},' ',1);
        inherited Init(_Owner, x,y, dbtWIDTH,dbtHEIGHT, _kbHot, _cmXXXX, _title, 1,_ck,_ct);
      end;  { TDialogButton.Init }


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TIcon                                                    €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TIcon.Init(_Owner: PGroup; x,y, size: int; _kbHot: char; _cmXXXX: word; _icon: pointer);
      begin
        inherited Init(_Owner, x,y,size,size, _kbHot,_cmXXXX,'', 1,0,0);
        icon:= _icon
      end;  { TIcon.Init }

procedure TIcon.Draw;
    var   bp: bool; xl,yl : int;
    type  Tprocii = procedure(x,y: int);
    begin
      if not visible then Exit;
      m_off(bp, xl,yl);
      Button;
      if icon<>nil then Tprocii(icon)(x0,y0);
      m_on(bp, xl,yl);
    end;  { TIcon.Draw }


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TTextIcon                                                €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TTextIcon.Init(_Owner: PGroup; x,y: int; _xi,_yi: int;
                           _kbHot: char; _cmXXXX: word;
                           _title: string; _icon: pointer);
      begin
        TButton.Init(_Owner, x,y,dbtWIDTH,dbtHEIGHT, _kbHot,_cmXXXX, _title,1, icKey,icText);
        xi:= _xi; yi:= _yi;
        icon:= _icon;
        if key<>'' then kbAltHot:= GetAltCode(key[1]);
      end;  { TTextIcon.Init }

procedure TTextIcon.Draw;
    type  Tprocii = procedure(x,y: int);
    var   bp: bool; xl,yl : int;
    begin
      if not visible then Exit;
      TButton.Draw;
      if icon<>nil then
         begin
           m_off(bp, xl,yl);
           Tprocii(icon)(x0+xi,y0+yi);
           m_on(bp, xl,yl)
         end;
    end;  { TIcon.Draw }


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TbtList                                                  €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TbtList.Init(_Owner: PGroup; x,y: int);
      begin
        inherited Init(_Owner, x,y,60,4, kbCtrlF1, cmList, 'Inde~x~  ',@icList)
      end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TbtOk                                                    €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TbtOk.Init(_Owner: PGroup; x,y: int; _kbHot: char);
      begin
        inherited Init(_Owner, x,y, 60,5, _kbHot, cmOk,titOK,@icYes)
      end;

constructor TbtEsc.Init(_Owner: PGroup; x,y: int);
      begin
        inherited Init(_Owner, x,y,btHEIGHT, kbEsc,cmCancel, @icNo);
      end;

procedure TbtEsc.HandleEvent(var _Event: TEvent);
    begin
      if not visible then Exit;
      if ((_Event.What = evMouseClick) and (_Event.M.bt and mbRightButton <> 0)) then _do_it(_Event)
      else inherited HandleEvent(_Event)
    end; { TbtEsc.HandleEvent }


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TbtTCancel, TbtCancel                                    €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TbtTCancel.Init(_Owner: PGroup; x,y, dx: int; _cmXXXX: word; _title: string);
      begin
        kbHot:= GetAltCode(get_HotKey(kbHot,_title));
        inherited Init(_Owner, x,y, dx,2, kbHot, _cmXXXX, _title,@icNo);
        kbAltHot:= kbHot
      end;

constructor TbtCancel.Init(_Owner: PGroup; x,y: int);
      begin
        inherited Init(_Owner,x,y,58, cmClose, titCANCEL)
      end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TbtMove                                                  €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TbtMove.Init(_Owner, _MainOwner: PGroup; x,y: int);
      begin
        inherited Init(_Owner, x,y, btHEIGHT, kbMOVE, cmMoveWindow, @icMove);
        MainOwner:= _MainOwner
      end;


{
 presun okna na poziciu
}
var xmove,ymove: int;

procedure _set_rectangle(x0m,y0m,x1m,y1m: int; xm,ym: int);
    var   bp: bool; xl,yl: int;
    begin
      m_off(bp, xl,yl);
      SetWriteMode(XORput);
      SetColor(clMOVE);
      Rectangle(x0m-1,y0m-1,x1m+1,y1m+1);
      SetWriteMode(0);
      m_on(bp, xl,yl);
      xmove:= xm; ymove:= ym;
      set_xy(xmove,ymove);
      m_set_shape(RUKA);
    end;

procedure _move_rectangle(var x0m,y0m,x1m,y1m: int; dx,dy: int);
    var   xi,yi: int;
          bp: bool; xl,yl : int;
    begin
      m_off(bp, xl,yl);
      SetWriteMode(XORput);
      SetColor(clMOVE);
      Rectangle(x0m-1,y0m-1,x1m+1,y1m+1);
      xi:= x0m; yi:= y0m;
      move_reg (x0m,y0m, x1m,y1m, dx,dy);
      dx:= x0m-xi; dy:= y0m-yi;
      Rectangle(x0m-1,y0m-1,x1m+1,y1m+1);
      SetWriteMode(0);
      m_on(bp, xl,yl);
      inc(xmove,dx); inc(ymove,dy);
      set_xy(xmove,ymove)
    end;

procedure _restore_rectangle(x0m,y0m,x1m,y1m: int);
    var   bp: bool; xl,yl : int;
    begin
      m_restore_shape;
      m_off(bp, xl,yl);
      SetWriteMode(XORput);
      SetColor(clMOVE);
      Rectangle(x0m-1,y0m-1,x1m+1,y1m+1);
      SetWriteMode(0);
      m_on(bp, xl,yl);
    end;


function _move_by_key(var x0m,y0m,x1m,y1m: int): bool;
   var   kb : char;
   begin
     _move_by_key:= true;
     kb:= kbNoKey;
     repeat
       CheckProcesses;
       if kbhit then
          begin
            kb:= GetKey;
            case kb of
              kbUp    : _move_rectangle(x0m,y0m,x1m,y1m, 0,-5);
              kbDown  : _move_rectangle(x0m,y0m,x1m,y1m, 0,+5);
              kbLeft  : _move_rectangle(x0m,y0m,x1m,y1m, -5,0);
              kbRight : _move_rectangle(x0m,y0m,x1m,y1m, +5,0);
              kbEsc   : _move_by_key:= false
            end
          end
     until kb in[kbEsc,kbEnter]
   end;

function _move_by_drag(var x0m,y0m,x1m,y1m: int): bool;
   var   bt,btt : byte;
   begin
     _move_by_drag:= mouse_status.stat.bt = 1;
     with mouse_status.stat do
       begin
         btt:= 1;
         while (bt=1) and not((btt<>1) and TimeOut(tick,GetTicks,5)) do
           begin
             get_bt(btt);
             if (x<>xmove) or (y<>ymove) then _move_rectangle(x0m,y0m,x1m,y1m, x-xmove,y-ymove);
             CheckProcesses
           end
       end
   end;


procedure TbtMove.HandleEvent(var _Event: TEvent);
    var   x0m,y0m,x1m,y1m : int;
          Pxy    : TPoint;
          res    : bool;
    begin
      if isClicked(_Event) or isKey(_Event,kbHot) then
         begin
           { nastavenie ramceka }
           OnOff(btON); Wait(5,CheckProcesses);
           get_region(MainOwner^.ScreenPtr.Region, x0m,y0m,x1m,y1m);
           _set_rectangle(x0m,y0m,x1m,y1m, x0m,y0m);

           { hladaj polohu }
           res:= true;
           if isKey(_Event,kbHot) then res:= _move_by_key(x0m,y0m,x1m,y1m)
           else _move_by_drag(x0m,y0m,x1m,y1m);

           { zmazanie ramceka }
            _restore_rectangle(x0m,y0m,x1m,y1m);

           { premiestnenie (?) }
            if res then
                begin
                  Pxy.x:= x0m; Pxy.y:= y0m;
                  Mail(MainOwner,cmMoveWindow,One,@Pxy,SizeOf(Pxy))
                end;

            {set_xy(x0,y0);}
            Wait(3,CheckProcesses);
            OnOff(btOFF);
            {set_xy(x0m-1,y0m-1);}

            ClearEvent(_Event);
            m_clear;
            ev_mx:= mouse_status.stat.x; ev_my:= mouse_status.stat.y
          end
    end; { TbtMove.HandleEvent }


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TWindow                                                  €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
function GetWindowSize(_title: string): word;
   begin
     GetWindowSize:= (Length(_title) * dx_ch) + winDX
   end;


constructor TWindow.Init(_Owner: PGroup; x,y, dx,dy: int;
                         _kbHot: char; _cmXXXX: word; _title: string;
                         _move: bool
                        );
      begin
        dx:= Maximum(dx,GetWindowSize(_title));
        inherited Init(_Owner, x,y, dx,dy+winHEIGHT);
        cmXXXX:= _cmXXXX; MCursor:= SIPKA; btSize:= btLarge;
        text:= nil; text_p:= nil;
        xp:= nil; yp:= nil;
        own_img:= false;
        if _move then
           begin
             if _Owner=nil then _Owner:= @Self;
             btMove := New(PbtMove,Init(@Self, _Owner, x+10,y+10));
             btNil  := btMove
           end
        else begin
               btNil:= New(PIcon,Init(@Self, x+10,y+10, btHEIGHT, kbNoKey, cmNil, nil));
               ScreenSave:= false
             end;
        _title:= CenterStr(cut_(_title),(x1-x-64) shr 3);
        btTitle:= New(PButton,Init(@Self, x+28,y+10,x1-x-56,btHEIGHT, _kbHot,_cmXXXX, _title, 1, icKey,icText));
        btEsc  := New(PbtEsc, Init(@Self, x1-24,y+10));
        btTitle^.stat:= btON
      end; { TWindow.Init }


procedure TWindow.MoveWin(var _x,_y: int; var _mode: int);
      begin
        if ( TGraphMode(N(_mode)) <> GraphMode ) or (_x=-1) or (_y=-1) then
           begin
             _x:= InitX; _y:= initY;
             {if (_mode<>-1) then} _mode:= ord(GraphMode)
           end;
        xp:= @_x; yp:= @_y;
        Centre
      end;


destructor TWindow.Done;
     begin
       if xp<>nil then begin int(xp^):= x0; int(yp^):= y0 end;
       inherited Done
     end;

procedure TWindow.Draw;
    var   bp: bool; xl,yl : int;
    begin
      m_off(bp, xl,yl);
      ButtonWindow(x0,y0,x1,y1,clBUTTON_COLOR,btSize);
      Image;
      if (Owner<>nil) and (Owner^.ObjectType>=obj_view) and (own_img) then PView(Owner)^.Image;
      inherited Draw;
      Draw_;
      m_on(bp, xl,yl)
    end; { Draw }

procedure TWindow.Draw_;
    begin
      if text<>nil then TProc_i4p(text)(x0+dx_Window_text,y0+dy_Window_text,x1-dx_Window_text,y1-dy_Window_text, text_p);
    end; { Draw }

procedure TWindow.Image;
    begin
    end; { Image }


procedure TWindow.Centre;
    var   x,y, dx : int;
    begin
      if (xp=nil) or ((int(xp^)=initX) and (int(yp^)=initY)) then
         begin
           dx:= GetMaxXM-btcdXY.x1-btcdXY.x0;
           if x1-x0 < dx then x:= btcdXY.x0 + Math.Centruj(GetMaxXM-btcdXY.x1-btcdXY.x0,(x1 - x0))
           else x:= Math.Centruj(GetMaxXM,(x1 - x0));
           y:= btcdXY.y0 + Math.Centruj(GetMaxY-btcdXY.y1-btcdXY.y0,(y1 - y0));
           MoveRel(x - x0,y - y0)
         end
      else begin
             x:= int(xp^); y:= int(yp^);
             if move_reg(x,y, x,y, x0-x,y0-y)=2 then MoveRel(x0-x,y0-y)
           end
    end;


procedure TWindow.set_text(_text,_text_p: pointer);
    begin
      text:= _text; text_p:= _text_p
    end;


function TWindow.get_width: word;
   begin
     get_width:= GetWindowSize(StrPas(btTitle^.title))
   end;


procedure get_win_btXY(P: PView; pod: byte; pos: int; var _x0,_y0: int);
    var   dx: int;
    begin
      if P<>nil then
         begin
           if pod=1 then begin _x0:= P^.x0; _y0:= P^.y1 end
           else begin _x0:= P^.x1; _y0:= P^.y0 end;
         end
      else begin
             _x0:= 0;
             _y0:= 0
           end;
      if pod=1 then
           begin
             inc(_x0, dbtDXoff + (dbtWIDTH+dbtDX)*(pos));
             inc(_y0, - dbtDYoff - dbtHEIGHT)
           end
      else begin
             inc(_x0, - dbtWIDTH  - dbtDXoff);
             inc(_y0, + dbtHEIGHT + 5+dbtDYoff + (btHEIGHT+dbtDY)*(pos))
           end;
    end;

procedure TWindow.get_btXY(pod: byte; pos: int; var _x0,_y0: int);
    begin
      get_win_btXY(@Self,pod,pos,_x0,_y0)
    end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TWindows                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
{
 _pod    -> spinace Ok a Cancel su na spodku okna;
 _pocet  -> max.pocet spinacov, v tom pripade Ok a Cancel
}
constructor TWindows.Init(_Owner: PGroup; x,y, dx,dy: int;
                          _kbHot: char; _cmXXXX: word; _title: string; _text: string;
                          _move : bool; _dole, _pocet: byte; _altk : bool
                         );
      var   x0Ok,y0Ok, x0Cancel,y0Cancel: int;
      begin
        pocet:= _pocet;
      { vypocet velkosti okna }
        if _dole=1 then
             begin
               x0Ok:= Maximum(GetWindowSize(_title),(dbtWIDTH + 5)*(pocet+2) + 30);
               if (dx < x0Ok) then dx:= x0Ok else Inc(dx,28);
               Inc(dy,btHEIGHT+10)
             end
        else begin
               dx:= Maximum(GetWindowSize(_title),dx + dbtWIDTH + 30);
{!}            dy:= Maximum(dy, (btHEIGHT + 5)*(pocet+2) + 20)
             end;
        inherited Init(_Owner, x,y, dx, dy, _kbHot,_cmXXXX, _title, _move);
      { vypocet umiestnenia buttonov }
        if pocet=0 then { vycentrovanie buttonov Ok a Cancel }
           if _dole=1 then
              begin
                 dx:= ((x1-x0) - (dbtWIDTH shl 1)) div 3;
                 x0Ok    := x0 + dx;
                 x0Cancel:= x0 + dx shl 1 + dbtWIDTH;
                 y0Ok    := y1-dbtHEIGHT-10;
                 y0Cancel:= y0Ok
              end
           else begin
                 { vycentrovanie buttonov Ok a Cancel }
                  dy:= ((y1-y0-winHEIGHT+10) - (dbtHEIGHT shl 1)) div 3;
                  y0Ok    := y0+winHEIGHT-10 + dy;    {btHEIGHT + 17}
                  y0Cancel:= y0Ok + dy + btHEIGHT;    {btHEIGHT + 8}
                  x0Ok:= x1 - dbtWIDTH-10;
                  x0Cancel:= x0Ok;
                end
        else begin
               get_btXY(_dole, 0, x0OK,y0OK);
               get_btXY(_dole, 1, x0Cancel,y0Cancel)
             end;

        btOk:= New(PbtOk,Init(@Self,x0Ok,y0Ok, _kbHot)); btOk^.cmXXXX:= _cmXXXX;
        if not _altk then btOk^.kbAltHot:= GetAltChar(btOk^.kbAltHot);
        if _text='' then _text:= titCANCEL;
        btCancel:= New(PbtTCancel,Init(@Self,x0Cancel,y0Cancel,2+7*length(_text), cmClose, _text)); { musi byt posledny ! }
        if not _altk then btCancel^.kbAltHot:= GetAltChar(btCancel^.kbAltHot)
      end; { TWindows.Init }


end.  { Button }