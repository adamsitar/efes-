{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TItem                                                    €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TItem.Init(_title: string; _cmXXXX: word; _Next: PItem);
      begin
        inherited Init(nil, {dx}0,{dy}0, 0 {StrLen(_title) shl 3},dbtHEIGHT, kbNoKey, _cmXXXX, _title, 1, clKey,clItem);
        mnu:= _item;
        centr_txt:= false; kbAct:= kbEnter;
        PMenu:= nil; PMenu_init:= nil; PMenu_done:= nil;
        en_func:= nil; en_bool:= true; is_func:= false;
        Next:= _Next
      end;

procedure TItem.HandleEvent(var _Event: TEvent);
    begin
      if not (isEnabled and visible) then Exit;
      if     (    isKey(_Event,kbHot)
               or (Active and isKey(_Event,kbAct))
             )
          or isClicked(_Event) then
            begin
              isActive;
              OnOff(TbtStat(not bool(stat))); {Beep(300,10);}
              SetCommand(_Event,cmXXXX);
              _Event.Whom:= MainAppPtr^;
              if bool(click) then
                 begin
                   OnOff(btOFF); {Beep(300,10)}
                 end
            end
    end;

procedure TItem.Draw;
    var   bp : bool; xl,yl, x,y : int;
          bk : byte;
    begin
      if not visible then Exit;

      m_off(bp, xl,yl);
      ct:= _ct_(active,isEnabled);
      ck:= _ck_(active,isEnabled);
      bk:= _bk_(active,isEnabled);
      if centr_txt then x:= x0+Centruj(x1-x0,StrLen(title) * dx_ch) else x:= x0+dx_ch;
      y:= (y1+y0+dy_bt) shr 1;
      Button;
      FillWin(x0+2,y0+2,x1-2,y1-2, bk);
      {$IFDEF SPEA} {if stat=btON then} SetBkColor(bk); {grBUTTON_COLOR[btON]) else SetBkColor(clBUTTON_COLOR);} {$ENDIF}
      SetColor(ct); OutTextXY(x,y, StrPas(title));
      if (stat=btOFF) and (xk<>0) then begin SetColor(ck); OutTextXY(x+((xk-1)*dx_ch),y, key) end;
      m_on(bp, xl,yl)
    end;

{
 pripravi stav spinaca pred prvym vykreslenim
}
procedure TItem.init_for_draw;
    begin
    end;

{
volany len pri inicializacii !
}
function TItem.get_width: int;
   begin
     get_width:= StrLen(title) * dx_ch
   end;

function TItem.get_height: int;
   begin
     get_height:= {y1 } btHEIGHT + MEDZERA_ITEM
   end;

{
 volany len pri inicializacii !
}
procedure TItem.InitXY(x,y, dx: int);
    begin
      XY(x,y,dx,btHEIGHT);
    end;

procedure TItem.DoneItems;
    begin
    end;


procedure TItem.Text(_ct,_ck: byte);
    var   bp : bool;
          x,y, xl,yl : int;
          bk : byte;
    begin
      m_off(bp, xl,yl);
      ct:= _ct_(active,isEnabled);
      ck:= _ck_(active,isEnabled);
      bk:= _bk_(active,isEnabled);
      if centr_txt then x:= x0+Centruj(x1-x0,StrLen(title)*dx_ch)
      else x:= x0+dx_ch;
      y:= (y1+y0+dy_bt) shr 1;
      FillWin(x0+2,y0+2,x1-2,y1-2, bk);
      {$IFDEF SPEA} {if stat=btON then} SetBkColor(bk);{grBUTTON_COLOR[btON]) else SetBkColor(clBUTTON_COLOR);} {$ENDIF}
      SetColor(ct); OutTextXY(x,y, StrPas(title));
      if xk <> 0 then begin SetColor(ck); OutTextXY(x+((xk-1)*dx_ch),y, key) end;
      m_on(bp, xl,yl)
    end;


procedure TItem.ActiveOn;
    var   c: word;
    begin
      inherited ActiveOn;
      if x0<>0 then Text(ct,ck)
    end;

procedure TItem.ActiveOff;
    var   c: word;
    begin
      inherited ActiveOff;
      if x0<>0 then Text(ct,ck)
    end;

procedure TItem.isActive;
    var   p: pointer;
    begin
      if Active then Exit;
      p:= @Self;
      Mail(Owner,cmChangeActItem, One,@p,SizeOf(pointer))
    end;


function TItem.isEnabled: bool;
   begin
     isEnabled:=     (en_func=nil)
                 or  (   ((not is_func) and ((en_bool and bool(en_func^)) or ((not en_bool) and (not bool(en_func^)))) )
                      or (     is_func  and ((en_func<>nil) and TBFunc(en_func)))
                     )
   end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TItem2                                                   €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TItem2.Init(_title: string; _kbHot: char; _cmXXXX: word; _Next: PItem);
      begin
        inherited Init(_title,_cmXXXX,_Next);
        kbHot:= _kbHot
      end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TLine                                                    €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TLine.Init(_Next: PItem);
    begin
      sirka:= 2;
      inherited Init('',cmNil,_Next);
      mnu:= _line; kbAct:= #0;
    end;

procedure TLine.Draw;
    var   bp: bool; x,y,xl,yl: int; bk: byte;
    begin
      if (not visible) or (sirka=$FF) then Exit;

      m_off(bp, xl,yl);
      SetColor({$IFDEF EGAVGA}lightgray{$ELSE}clBUTTON_COLOR+clBUTTON_LIGHT{$ENDIF});
      Line(x0+1,y0-1,x1-1,y0-1);
     { Line(x0+2,y0-2,x1-2,y0-2);}
      FillWin(x0,y0,x1,y1,clBUTTON_COLOR);
      SetColor({$IFDEF EGAVGA}black{$ELSE}clBUTTON_COLOR+clBUTTON_DARK{$ENDIF});
      Line(x0+1,y1+1,x1-1,y1+1);
     { Line(x0+2,y1+2,x1-2,y1+2);}
      m_on(bp, xl,yl);
    end;

procedure TLine.InitXY(x,y, dx: int);
    var   dy: int;
    begin
      if sirka>btHEIGHT then dy:= btHEIGHT else dy:= sirka;
      XY(x-10, y+ btHEIGHT shr 1 - dy shr 1, dx+20, dy)
    end;

{function TLine.isEnabled: bool;
   begin
     isEnabled:= false
   end;
}

{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TTextLine                                                €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

constructor TTextLine.Init(_title: string; _Next: PItem);
    begin
      inherited Init(_Next);
      sirka:= $FF;
      xk:= Pos(cnst_HotKey,_title);
      Tkey:= GetStr(_title,Limit(Pos(cnst_HotKey,_title), 1,2, 0),[cnst_HotKey]);
      Ttitle:= strpasnew(DelChar(_title,[cnst_HotKey]))
    end;

destructor TTextLine.Done;
     begin
       strdispose(Ttitle);
       inherited Done
     end;

procedure TTextLine.Draw;
    var   bp: bool; x,y,xl,yl: int;
    begin
      if (not visible) then Exit;

      m_off(bp, xl,yl);
      if centr_txt then x:= x0+Centruj(x1-x0,StrLen(Ttitle) * dx_ch)
      else x:= x0+dx_ch;
      y:= (y1+y0+dy_bt) shr 1;
      FillWin(x0+2,y0+2,x1-2,y1-2, _bk_(false,true));
      {$IFDEF SPEA} SetBkColor(bk_Item[mnu_palette,false]); {$ENDIF}
      SetColor(_ct_(false,true)); OutTextXY(x,y, StrPas(Ttitle));
      if (xk<>0) then begin SetColor(_ck_(false,true)); OutTextXY(x+((xk-1)*dx_ch),y, Tkey) end;
      m_on(bp, xl,yl)
    end;

procedure TTextLine.ActiveOn;
    begin
      Draw
    end;

procedure TTextLine.ActiveOff;
    begin
      Draw
    end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TSubMenu                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TSubMenu.Init(_title: string; _PMenu: PWinMenu; _Next: PItem);
      begin
        inherited Init(_title, cmRunSubMenu, _Next);
        click:= 0; mnu:= _submenu;
        PMenu:= _PMenu;
        if PMenu<>nil then PMenu^.Owner:= @Self
        {
        inherited Init(_title, cmNil, _Next);
        mnu:= _submenu; click:= 0;
        PMenu:= _PMenu;
        PMenu^.Owner:= @Self;
        if PMenu<>nil then cmXXXX:= PMenu^.cmXXXX
        }
      end;

destructor TSubMenu.Done;
     begin
       if PMenu<>nil then Dispose(PMenu,Done);
       PMenu:= nil;
       inherited Done
     end;


procedure TSubMenu.HandleEvent(var _Event: TEvent);
    begin
      inherited HandleEvent(_Event);
      if {(isEnabled) and} (isCommand(_Event,cmRunSubMenu{XXXX})) then
         begin
           if (PMenu <> nil) then
              begin
                if (PMenu_init <> nil) then
                   begin
                     Tproc_p(PMenu_Init)(@Self);
                     PMenu^.MoveRel(x0-PMenu^.x0{-btHEIGHT},y0-PMenu^.y0+btHEIGHT+6);
                     {PMenu^.MoveRel(btHEIGHT,btHEIGHT+10)}
                   end;
                if (PMenu^.FirstItem<>nil) then
                   begin
                     RunMenu(PMenu, _Event);
                     if ((_Event.What and evMessage)<>0) then PView(Owner)^.cmXXXX:= _Event.Command
                   end
                else ClearEvent(_Event);
                if (PMenu_done <> nil) then Tproc_p_vE(PMenu_done)(@Self,_Event);
                if (PMenu_init <> nil) then PMenu^.DoneItems
              end
           else ClearEvent(_Event);
           OnOff(btOFF)
         end
    end;

procedure TSubMenu.MoveRel(dx,dy: int);
    begin
      inherited MoveRel(dx,dy);
      if {init_menus and} (PMenu <> nil) then PMenu^.MoveRel(x1-PMenu^.x0-btHEIGHT,y1-PMenu^.y0-btHEIGHT-10)
    end;
