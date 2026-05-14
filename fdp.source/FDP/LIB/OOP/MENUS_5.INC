{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TOptMenu                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
procedure TOptMenu.init_buttons;
    begin
      btOK    := New(PbtOK,    Init(nil,x0+10,y1-dbtHEIGHT-10, kbCtrlEnter)); { kvoli set_size je pred init }
      btCancel:= New(PbtCancel,Init(nil,x1-dbtWIDTH-10,y1-dbtHEIGHT-10));
      btCancel^.cmXXXX:= cmCancel;
    end;

constructor TOptMenu.Init(_title: string; _hlpXXX: Pchar; _cmXXXX: word; _FirstItem: PItem);
      begin
        x0:= initX; x1:= initX; y0:= initY; y1:= initY;
        btOK:= nil; btCancel:= nil;
        init_buttons;
        inherited Init(_title,_hlpXXX, _FirstItem);
        btTitle^.kbHot := kbEnter; btTitle^.cmXXXX:= cmOK;
        cmXXXX:= _cmXXXX;
        if btOK<>nil then begin PushObject(btOK); btOK^.visible:= false end;
        if btCancel<>nil then begin PushObject(btCancel); btCancel^.visible:= false end;
        if (btOK<>nil) and (btCancel<>nil) then
           begin
             btOK^.visible:= true;
             btCancel^.visible:= true;
             XY(initX,initY,get_width,15+dbtHEIGHT+10);
             set_size
           end;
      end;

procedure TOptMenu.HandleEvent(var _Event: TEvent);
    begin
      inherited HandleEvent(_Event);
      if isCommand(_Event,cmOK) then
         begin
           SetCommand(_Event,cmXXXX);
           _Event.Whom:= MainAppPtr^
         end
    end;

function TOptMenu.get_width: word;
   begin
     get_width:= Maximum( StrLen(btTitle^.title) + dx_ch + 28*2, dbtWIDTH*2 + 35);
   end;

procedure TOptMenu.set_size;
    begin
      inherited set_size;
      if (btOK<>nil) and (btCancel<>nil) then
         begin
           y1:= y1 + dbtHEIGHT + 10;
           btOK^.XY    (x0+10,y1-dbtHEIGHT-12,dbtWIDTH,dbtHEIGHT);
           btCancel^.XY(x1-dbtWIDTH-10,y1-dbtHEIGHT-12,dbtWIDTH,dbtHEIGHT);
           set_region(10,winHEIGHT-5,-10,-dbtHEIGHT-20, r)
         end;
    end; { set_size }



{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TOptMenu_S                                               €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TOptMenu_S.Init(_title: string; _hlpXXX: Pchar; _cmXXXX: word; _page: byte; _FirstItem: PItem);
      begin
        page:= _page; lo:= 0; hi:= _page-1; top:= -1; pos:= 0;
        sb:= nil;
        inherited Init(_title,_hlpXXX, _cmXXXX,_FirstItem)  { urobi set_size }
      end;


procedure TOptMenu_S.set_size;
    var   Item  : PItem;
          dx,dy : int;
    begin
      inherited set_size;

    { uuprava premennyych pre priipad meniaceho sa menu
      - spocitanie
      - uprava horucich klaves na ' '
    }
      Item:= FirstItem; top:= -1;
      while (Item <> nil) do
        begin
          Item:= Item^.Next;
          inc(top)
        end;

      lo:= 0; hi:= minimum(page-1,top);
      if (sb=nil) and (hi<top) then sb:= New(PScrollBar,Init(@Self, x1, y0, 0, true{pos_en},false{stranka},true{sam}));

      if sb<>nil then
         begin
           sb^.lo:= lo; sb^.hi:= hi; sb^.top:= top; sb^.pos:= pos;
           dx:= MEDZERA__SCROLLER__SCROLL_BAR + SCROLL_BAR__SIRKA
         end
      else dx:= 0;

      set_Item_dy;
      if (btOK<>nil) and (btCancel<>nil) then dy:= dbtHEIGHT+10 else dy:= 0;
      XY(x0,y0,x1-x0+dx,winHEIGHT+15+dy + vyska*(hi-lo+1));

      if (btOK=nil) and (btCancel=nil) then dy:= dbtHEIGHT+10 else dy:= 0;
      if sb<>nil then sb^.reinit(x1-dx-5,y0 + winHEIGHT-5, dx,y1-(y0+dbtHEIGHT+20-dy+winHEIGHT-5));
      set_region(10,winHEIGHT-5,-10-dx,-dbtHEIGHT-20+dy, r);

      btTitle^.XY(x0+28,y0+10,x1-x0-56,btHEIGHT);
      btEsc^.XY(x1-24,y0+10,btHEIGHT,btHEIGHT);

      if (btOK<>nil)     then btOK^.XY    (x0+10,y1-dbtHEIGHT-12,dbtWIDTH,dbtHEIGHT);
      if (btCancel<>nil) then btCancel^.XY(x1-dbtWIDTH-10,y1-dbtHEIGHT-12,dbtWIDTH,dbtHEIGHT)
    end; { set_size }


procedure TOptMenu_S.HandleEvent(var _Event: TEvent);
    var   p   : PItem;
          nlo,nhi,ntop,npos: int;
    label L;
    begin
      L: TWindow.HandleEvent(_Event);

      if (_Event.What=evKeyDown) or (mnu_mouse_scroll and ((_Event.What and evMouse)<>0)) then
         begin
           if mnu_mouse_scroll and ((_Event.What and evMouse)<>0) then SetKeyEvent(_Event,@Self,m_to_kb(_Event.M));
           case _Event.Key of
              kbEnter, kbUp,kbDown,kbPgUp,kbPgDn,kbHome,kbEnd :
                begin
                  case _Event.Key of
                    kbEnter : if ActItem<>nil then
                                 begin
                                   _Event.Key:= ActItem^.kbAct;
                                   goto L
                                 end;
                    kbUp   : SetActItem(ScrollItem(-1));
                    kbDown : SetActItem(ScrollItem(+1));
                    kbPgUp : SetActItem(ScrollItem(-(hi-lo+1)));
                    kbPgDn : SetActItem(ScrollItem(hi-lo+1));
                    kbHome : SetActItem(NextItem(LastItem){FirstItem});
                    kbEnd  : SetActItem(PrevItem(FirstItem){LastItem})
                  end;
                  ClearEvent(_Event)
                end;
              kbLeft  : SetCommand(_Event,cmLeftMenu);
              kbRight : SetCommand(_Event,cmRightMenu);

              else if (BarMenu<>nil) and (BarMenu^.inBarMenuKeys(GetAltChar(_Event.Key))) then
                      begin
                        Pending.What:= evKeyDown;
                        Pending.Key := GetAltChar(_Event.Key);
                        SetCommand(_Event,cmAltMenu)
                      end
           end
         end

      else if (_Event.What and evMessage <> 0) then
         case _Event.Command of
         { udalost od polozky menu
         }
           cmChangeActItem    : begin
                                  Move(MailBox^,p,SizeOf(pointer));
                                  SetActItem(p);
                                  ClearEvent(_Event)
                                end;

           cmScrollBarClicked : begin
                                  receive__scroll_mail(nlo,nhi,ntop,npos);
                                  SetActItem(ScrollItem(npos-pos))
                                end;

           cmOK : begin
                    SetCommand(_Event,cmXXXX);
                    _Event.Whom:= MainAppPtr^
                  end
         end

    end; { HandleEvent }


{
  vrati poziciu pos Item v zozname
}
function  TOptMenu_S.get_pos(Item: PItem): int;
    var   Item_: PItem;
          pos_ : int;
    begin
      Item_:= FirstItem; pos_:= 0;
      while (Item_<>nil) and (Item_<>Item) do
        begin
          Item_:= Item_^.Next;
          inc(pos_)
        end;
      get_pos:= pos_
    end;

{
  vrati Item zo zoznamu na pozicii pos_
}
function  TOptMenu_S.get_Item(pos_: int): PItem;
    var   Item  : PItem;
          i     : int;
    begin
      Item:= FirstItem; i:= 0;
      while (Item<>nil) and (i<>pos_) do
        begin
          Item:= Item^.Next;
          inc(i)
        end;
      get_Item:= Item
    end;


procedure TOptMenu_S.set_Item_dy;
    var   Item : PItem;
          i,dx,item_x,item_y : int;
    begin

    { vyypocet poloh ITEM vzhladom ku ich relatiivnej polohe voci lo
    }
      item_x:= x0 + dx_ITEM; dx:= sirka-40+56;
      item_y:= y0 + dy_ITEM;

      i:= lo;
      Item:= get_Item(lo);
      while (i<=hi) and (Item<>nil) do
        begin
          Item^.InitXY(item_x,item_y,dx);
          inc(item_y,vyska);
          Item:= Item^.Next;
          inc(i)
        end;

    { nastavenie visible
    }
      Item:= FirstItem; i:= 0;
      while (Item <> nil) do
        begin
          Item^.visible:= (i>=lo) and (i<=hi);
          Item:= Item^.Next;
          inc(i)
        end;

      if sb<>nil then begin sb^.lo:= lo; sb^.hi:= hi; sb^.top:= top end;

    end;


function  TOptMenu_S.ScrollItem(di: int): PItem;
    var   Item : PItem;
          npos : int;
    label L;
    begin
    { najde polozku na pozicii pos+di); }
      npos:= Limit(pos+di,0,top, 0);
      L: Item:= get_Item(npos);
         if (Item^.title=nil) or (not Item^.isEnabled) then
            begin
              if (npos=0) then di:= 1
              else if (npos=top) then di:= -1;
              npos:= Limit(npos+di,0,top, 0);
              goto L
            end;
      ScrollItem:= get_Item(npos)
   end;


procedure TOptMenu_S.SetActItem(_next: PItem);
   var    prev_lo,prev_hi,temp,i : int;
          Item : PItem;
   begin
     prev_lo:= lo; prev_hi:= hi; temp:= pos;
     pos:= get_pos(_next);                              { urcenie novej aktualnej pozicie pos }
     set__scroll_pos(lo,hi, temp, top,pos, true,false); { urcenie novych suradnic lo, hi }
     if (prev_lo<>lo) or (prev_hi<>hi) then
        begin
          set_Item_dy;                                  { prepocet poloh buttonov a ich visible }
          Image;
          i:= lo;
          Item:= get_Item(lo);
          while (i<=hi) and (Item<>nil) do
            begin
              Item^.Draw;
              Item:= Item^.Next;
              inc(i)
            end
        end;
     inherited SetActItem(_next);
     if sb<>nil then Mail(sb, cmScrollerChanged, One, @lo,4*SizeOf(int)) { len upravit sb }
   end;


procedure TOptMenu_S.DoneItems;
    begin
      inherited DoneItems;
      sb:= nil
    end; { DoneItems }

