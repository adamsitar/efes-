{ ------------------------------------------------------------ }
{  TView                                                       }
{ ------------------------------------------------------------ }

constructor TView.Init(_Owner: PGroup; x,y,dx,dy: int);
      begin
        inherited Init(_Owner);
        ObjectType := obj_view;

        XY(x,y,dx,dy);
        cmXXXX := cmNil; hlpXXX := nil;
        EventMask := evMouseClick + evKeyDown + evCommand;
        MCursor := MYS;

        active  := false;
        visible := true;
        istview := true;

        bk0   := 0;
        Local := nil;

        S_run := false;
        R_err := false;
      end;

procedure TView.XY(x,y,dx,dy: int);
    begin
      x0:= x; y0:= y; x1:= x0+dx; y1:= y0+dy
    end;

procedure TView.Reinit(x,y,dx,dy: int);
    begin
    end;


procedure TView.Run(var _Event: TEvent);   { hlavny cyklus }
    begin
      kb_clear;
      m_clear;
      repeat {writeStr(100,100, inttostr(maxavail,1,1), white, black);}
        if (_Event.What <> evNothing) then ClearEvent(_Event);
        if not S_run then
           begin
             S_run:= true;
             if @Local<>nil then Local;
             LocalMain(_Event);
             if (_Event.What = evNothing)  then GetEvent(_Event);
              if (_Event.What <> evNothing) then HandleEvent(_Event);
             S_run:= false
           end;
        CheckProcesses
      until EndState(_Event);
      {if (_Event.Command = cmXXXX) then}  {Make;}
      {if (_Event.Command <> cmQuit) then ClearEvent(_Event);}
    end; { TView.Run }


procedure TView.RunLocalFunc(var _Event: TEvent; Info: PChar);   { hlavny cyklus }
    var   _WinReg : PWinReg;
          bp : bool; xl,yl : int;
    begin
      _WinReg:= nil;
      with bar_mnuXY do
        if not SaveWin(x0,y0,GetMaxXM,y1, _WinReg) then
           begin
             if not s_nem then
                begin
                  s_nem:= true;
                  mess.BeepErr;
                  _write_err_log('Not enough memory ('+inttostr(maxavail,6,0)+').');
                  s_nem:= false
                end;
             Exit
           end;
      m_off(bp, xl,yl);
      with bar_mnuXY do WriteInfo(x0,y0,GetMaxXM,y1,StrPas(Info));
      m_on(bp, xl,yl);
      Run(_Event);
      RestWin(_WinReg, true,true);
      kb_clear
    end; { TView.Run }


function TView.EndState(var _Event: TEvent): bool;
   begin
     EndState:=       ((_Event.What and evMessage) <> 0)
                  and (   (_Event.Command = cmXXXX)
                       or (_Event.Command = cmCancel)
                       or (_Event.Command = cmClose)
                       or (_Event.Command = cmQuit)
                      )
                  and (not R_err)
   end;


procedure TView.Draw;
    begin
    end;


procedure TView.Image;
    begin
    end;


procedure TView.Mail (_Whom: PObject; _Command: Word; _ForAll: TNumber;
                      _mail: pointer; _size: word
                     );
    var   xl,yl: int;
    begin
      xl:= mouse_status.stat.x; yl:= mouse_status.stat.y;
      inherited Mail(_Whom,_Command,_ForAll,_mail,_size);
      mouse.set_xy(xl,yl)
    end;

procedure TView.MailE (var _Event: TEvent;
                       _Whom: PObject; _Command: Word; _ForAll: TNumber;
                       _mail: pointer; _size: word
                      );
    var   xl,yl: int;
    begin
      xl:= mouse_status.stat.x; yl:= mouse_status.stat.y;
      inherited MailE(_Event,_Whom,_Command,_ForAll,_mail,_size);
      mouse.set_xy(xl,yl)
    end;


procedure TView.show;
    begin
      visible:= true;
      Draw
    end;

procedure TView.hide;
    var   bp : bool; xl,yl : int;
    begin
      m_off(bp, xl,yl);
      ClrWin (x0,y0,x1,y1, bk0);
      m_on(bp, xl,yl);
      visible:= false
    end;

procedure TView.visibility(is_visible: bool);
    begin
      if visible<>is_visible then
         begin
           visible:= is_visible;
           if visible then show
           else hide
         end
    end;

procedure TView.MoveRel(dx,dy: int);
    begin
      Inc(x0,dx);
      Inc(y0,dy);
      Inc(x1,dx);
      Inc(y1,dy)
    end;

procedure TView.Resize(dx,dy: int);
    begin
      Inc(x1,dx);
      Inc(y1,dy)
    end;

{
nastavenie tvaru kurzora mysi - nastavi odvodena trieda,
pripadne zmenit na parameter namiesto procedury
}
procedure TView.m_shape;
    begin
      m_cursor(MCursor)
    end;


function TView.inView(x,y: int): bool;
   begin
     inView:= visible and inRectangle(x,y, x0,y0,x1,y1)
   end;

function TView.isClicked(_Event: TEvent): bool;
   begin
     with _Event do isClicked:=
            ( (What = evMouseClick) or (What = evMouseDouble) )
        and (     inView(M.x+(-Moff[M.curs].x),M.y+(-Moff[M.curs].y))
              and bool(M.bt and mbLeftButton)
            )
   end;


{
 dotatocna akcia
}
procedure TView.Idle(var _Event: TEvent);
    begin
      check_display
    end;


function  TView.HelpDisplayed(var _Event: TEvent): bool;
    begin
      if isKey(_Event,kbF1) and (hlpXXX<>nil) and (@p_hlp<>nil) then
         begin
           ClearEvent(_Event);
           p_hlp(hlpXXX);
           HelpDisplayed:= true
         end
      else HelpDisplayed:= false
    end;

procedure TView.HandleEvent(var _Event: TEvent);
    begin
      inherited HandleEvent(_Event);
      HelpDisplayed(_Event);
    end;


{
 zapne pohlad, ze vstup smeruje najprv k nemu
}
procedure TView.ActiveOn;  { inline v C++ }
    begin
      Active:= true
    end; { TView.On }

procedure TView.ActiveOff; { inline v C++ }
    begin
      Active:= false;
    end; { TView.Off }


{
 zistitenie najvacsich rozmerov v skupine
}
procedure TView.get_reg_size(S: PRegionSize);
    var   size: long;
    begin
      size:= (x1-x0);
      size:= size * (y1-y0);
      if (size < S^.Size) then Exit;
    { S^.Region.x0:= x0; S^.Region.y0:= y0; S^.Region.x1:= x1; S^.Region.y1:= y1; }
      Move(x0, S^.Region.x0,4*SizeOf(int));
      S^.Size:= size
    end; { TView.Size }
