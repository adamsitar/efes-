{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TSwitch0                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TSwitch0.Init(_title: string; _cmXXXX: word; _check_adr: pointer; _Next: PItem);
      begin
        inherited Init(_title, _cmXXXX, _Next); {kbAct:= ' ';} click:= 0;
        mnu:= _switch0;
        Inc(x0, btHEIGHT);
        check_adr:= _check_adr;
        read_check_adr {;if (check_adr<>nil) then stat:= TbtStat(bool(check_adr^))}
      end;

procedure TSwitch0.read_check_adr;
    begin
      if (check_adr<>nil) then stat:= TbtStat(bool(check_adr^))
    end;

procedure TSwitch0.writeto_check_adr;
    begin
      if (check_adr<>nil) then byte(check_adr^):= ord(stat)
    end;


procedure TSwitch0.HandleEvent(var _Event: TEvent);
    begin
      inherited HandleEvent(_Event);
      if isCommand(_Event,cmXXXX) and (_Event.Command<>cmNil) then
         begin
           writeto_check_adr;
           Beep(400,20)
         end
    end;

procedure TSwitch0.Draw;
    var   bp : bool;
          xl,yl : int;
          bk : byte;
    begin
      m_off(bp, xl,yl);
      Button;
      {$IFDEF SPEA} if stat=btON then SetBkColor(grBUTTON_COLOR[btON]) else SetBkColor(clBUTTON_COLOR); {$ENDIF}
      WriteCentr(x0,x1,y0,y1, StrPas(title),_ct_(active,isEnabled));
      if (xk <> 0) then
         begin
           SetColor(_ck_(active,isEnabled));
           OutTextXY(x0+Centruj(x1-x0,StrLen(title) * dx_ch)+1+((xk-1) * dx_ch), (y1+y0+dy_bt) shr 1, key);
         end;
      m_on(bp, xl,yl);
    end;

{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TSwitch1                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TSwitch1.Init(_title: string; _cmXXXX: word; _check_adr: pointer; _Next: PItem);
      begin
        inherited Init(_title, _cmXXXX, _Next);
        mnu:= _switch1; {kbAct:= ' ';} click:= 0;
        Inc(x0, btHEIGHT);
        check_adr:= _check_adr;
        read_check_adr                  { if (check_adr<>nil) then stat:= TbtStat(bool(check_adr^))}
      end;

procedure TSwitch1.HandleEvent(var _Event: TEvent);
    begin
     {if not visible then Exit;}
      if visible then inherited HandleEvent(_Event);
      if isCommand(_Event,cmXXXX) and (_Event.Command<>cmNil) then
         begin
           writeto_check_adr;           { byte(check_adr^):= ord(stat); }
           if visible then Beep(400,20)
         end
    end;


procedure TSwitch1.read_check_adr;
    begin
      if (check_adr<>nil) then stat:= TbtStat(bool(check_adr^))
    end;

procedure TSwitch1.writeto_check_adr;
    begin
      if (check_adr<>nil) then byte(check_adr^):= ord(stat)
    end;

procedure TSwitch1.init_for_draw;
    begin
      read_check_adr;  {if (check_adr<>nil) then stat:= TbtStat(bool(check_adr^))}
    end;


procedure TSwitch1.draw_switch;
    var   bp : bool; xl,yl : int;
    begin
      m_off(bp, xl,yl);
      Button;
      if stat=btON then icYes_(x0+14,y0+3, LightGreen)
      else icNo_ (x0+11,y0, Green);
      m_on(bp, xl,yl);
    end;

procedure TSwitch1.text_switch;
    begin
    end;

procedure TSwitch1.Draw;
    var   y  : int;
          bp : bool;
          xl,yl : int;
          bk : byte;
    begin
      if not visible then Exit;
      m_off(bp, xl,yl);
      draw_switch;
      y:= (y1+y0+dy_bt) shr 1;
      bk:= _bk_(active,isEnabled);
      _text_bk(bk);
      {$IFDEF SPEA} SetBkColor(bk{clBUTTON_COLOR}); {$ENDIF}
      SetColor(_ct_(active,isEnabled)); OutTextXY(x1-xt,y, StrPas(title));
      if (xk<>0) then begin SetColor(_ck_(active,isEnabled)); OutTextXY(x1-xt + ((xk-1) * dx_ch), y, key) end;
      text_switch;
      m_on(bp, xl,yl);
    end;


procedure TSwitch1._text_bk(bk: byte);
    begin
      FillWin(x1-xt-5,y0+2,x0-5,y1-2, bk);
    end;

procedure TSwitch1.Text(_ct,_ck: byte);
    var   bp : bool;
          x,y, xl,yl : int;
          bk : byte;
    begin
      m_off(bp, xl,yl);
      bk:= _bk_(active,isEnabled);
      _text_bk(bk);
      {$IFDEF SPEA} SetBkColor(bk{clBUTTON_COLOR}); {$ENDIF}
      y:= (y1+y0+dy_bt) shr 1;
      SetColor(_ct_(active,isEnabled)); OutTextXY(x1-xt,y, StrPas(title));
      if (xk<>0) then begin SetColor(_ck_(active,isEnabled)); OutTextXY(x1-xt + ((xk-1) * dx_ch), y, key) end;
      text_switch;
      m_on(bp, xl,yl)
    end;


function TSwitch1.get_width: int;
   begin
     get_width:= inherited get_width + 2*btHEIGHT + dx_ch;
   end;

procedure TSwitch1.InitXY(x,y, dx: int);
    begin
      xt:= dx;
      XY(x + dx - 2*btHEIGHT - dx_ch, y, 2*btHEIGHT + dx_ch, btHEIGHT)
    end;

function TSwitch1.inView(x,y: int): bool;
   begin
     inView:= inRectangle(x,y, x1-xt,y0,x1-xt + StrLen(title) * dx_ch,y1) or inRectangle(x,y, x0,y0,x1,y1)
   end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TSwitch2                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TSwitch2.Init(_title: string; _check_adr: pointer; _Next: PItem);
      begin
        inherited Init(_title, cmNil, _check_adr, _Next);
        mnu:= _switch2; kbAct:= ' '
      end;


procedure TSwitch2.HandleEvent(var _Event: TEvent);
    begin
      if isEnabled then
         if isCommand(_Event,cmOK) then
            begin
              writeto_check_adr {if (check_adr<>nil) then byte(check_adr^):= ord(stat)}
            end
         else if isCommand(_Event,cmCancel) then
            begin
              read_check_adr {stat:= TbtStat(bool(check_adr^))}
            end
         else if    {(kbHot <> kbNoKey)}
                     visible
                and (     isClicked(_Event)
                       or  isKey(_Event,kbHot)
                       or (Active and (_Event.What=evKeyDown) and isKey(_Event,kbAct))
                     ) then begin
                              ClearEvent(_Event);
                              isActive; { lepsia by bola funkcia Handle...: bool -> if Handle... }
                              OnOff(TbtStat(not bool(stat)));
                              Beep(400,20)
                            end;
    end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TSwitchI                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
const dx_si = 5;
      dy_si = 3;

procedure switchI_init_form(ifrm: PBox; I: PSwitchI); far;
   begin
     with ifrm^,I^ do StrPICopy(itemd^[0].item, cstr(ivar,flen), strlen(itemd^[0].item))
   end;

function switchI_check_func(ifrm: PBox; I: PSwitchI): bool; far;
   var   ival : int;
         bres : bool;
   begin
     ival:= getint(strpas(ifrm^.itemd^[0].item),1,setNil);
     bres:= (ival>=I^.imin) and (ival<=I^.imax);
     if bres then I^.ivar:= ival;
     switchI_check_func:= bres
   end;


procedure TSwitchI.read_check_adr;
    begin
      {if (check_adr<>nil) then stat:= TbtStat(bool(check_adr^))}
    end;

procedure TSwitchI.writeto_check_adr;
    begin
      {if (check_adr<>nil) then byte(check_adr^):= ord(stat)}
    end;

procedure TSwitchI.init_for_draw;
    begin
      if iadr<>nil then ivar:= iadr^ else ivar:= 0
    end;


function TSwitchI.get_width: int;
   begin
     get_width:= TItem.get_width + (box^.x1-box^.x0)+dx_ch;
   end;


procedure TSwitchI.InitXY(x,y, dx: int);
    var   dy: int;
    begin
      inherited InitXY(x,y, dx);
      if box<>nil then with box^ do
         begin
           dy:= y1-y0;
           box^.XY(x0,y+dy_si,x1-x0,dy)
         end;
    end;

procedure TSwitchI.MoveRel(dx,dy: int); { tieto dve misia by, lebo je to len TView }
    begin
      inherited MoveRel(dx,dy);
      if box<>nil then box^.MoveRel(x1-box^.x1-dx_si,y1-box^.y1-dy_si);
    end;


constructor TSwitchI.Init(_title: string; _check_adr: pint; _unt: string; _imin,_imax: int; _Next: PItem);
      var   O: PObject;
            s: string;
      begin
        if _imin>0 then s:= +cstr(_imin,1)+'-'+cstr(_imax,1)
        else s:= {$IFNDEF A36YKA}'Û'{$ELSE}'<'{$ENDIF}+cstr(_imax,1);
        if _unt<>'' then s:= s+' '+_unt;
        s:= '['+s+']';
        unt:= strpasnew(s);
        inherited Init(_title+' '+rightchar('',length(s),' '),nil,{_check_adr,}_Next);

        iadr:= _check_adr;
        if iadr<>nil then ivar:= iadr^ else ivar:= 0;
        imin:= _imin; imax:= _imax;

        flen:= 0;
        repeat
          inc(flen);
          _imax:= _imax div 10
        until _imax=0;
        new(ifrm); fillchar(ifrm^,sizeof(ifrm^),0);
        ifrm^.legal:= @setCisl;
        getmem(ifrm^.item,flen+1); fillchar(ifrm^.item^,flen,' '); ifrm^.item[flen]:= NULL;

        box:= nil;
        box:= New(PBox,Init(nil,
                  x0,y0, TextWidth(StrPas(ifrm^.item)),TextHeight('H'),
                  kbEnter, cmXXXX,
                  PForms(ifrm),1, clBUTTON_COLOR,clGRe,
                  @Self, @switchI_init_form,@switchI_check_func,nil,
                  false,true, true,false
                 ));
        box^.active:= false
      end;

destructor TSwitchI.Done;
     begin
       inherited Done;
       strdispose(unt);
       dispose(box,Done);
       freemem(ifrm^.item,flen+1);
       dispose(ifrm)
     end;


procedure TSwitchI.draw_switch_(_active: bool);
    var   bp : bool; xl,yl : int;
          st : TbtStat;
    begin
      m_off(bp, xl,yl);
      if box<>nil then
         begin
           switchI_init_form(box,@Self);
           if _active then st:= btON else st:= btOFF;
           with box^ do BGIgraph.Button(x0-dx_si,y0-dy_si,x1+dx_si,y1+dy_si, grBUTTON_COLOR[st],btSmall,st);
           box^.active:= _active;
           box^.Draw; { nemozem sa spoliehat na group, lebo my dedime od view... }
         end;
      m_on(bp, xl,yl);
    end;


procedure TSwitchI.draw_switch;
    begin
      draw_switch_(false)
    end;

procedure TSwitchI.text_switch;
    begin
      SetColor(_ct_(active,isEnabled));
      OutTextXY(x0-dx_si-strlen(unt)*dx_ch,(y1+y0+dy_bt) shr 1,strpas(unt));
    end;

procedure TSwitchI._text_bk(bk: byte);
    begin
      FillWin(x1-xt-5,y0+2,box^.x0-10,y1-2, bk);
    end;


procedure TSwitchI.HandleEvent(var _Event: TEvent);
    begin
      if isEnabled then
         begin
           if isCommand(_Event,cmOK) then
              begin
                if (iadr<>nil) and (imin<=ivar) and (ivar<=imax) then iadr^:= ivar
              end
           else if isCommand(_Event,cmCancel) then
                   begin
                     if (iadr<>nil) then ivar:= iadr^ else ivar:= 0
                   end
           else if     visible
                  and (     isClicked(_Event)
                         or  isKey(_Event,kbHot)
                         or (Active and (_Event.What=evKeyDown) and (_Event.Key=kbAct))
                       ) then begin
                                if active then
                                   begin
                                     if box<>nil then
                                        begin
                                          draw_switch_(true);
                                          box^.Run(_Event);
                                          draw_switch_(false)
                                        end
                                   end
                                else begin
                                       isActive; { lepsia by bola funkcia Handle...: bool -> if Handle... }
                                       OnOff(TbtStat(not bool(stat)));
                                       Beep(400,20)
                                     end;
                                ClearEvent(_Event)
                              end
         end;
    end;