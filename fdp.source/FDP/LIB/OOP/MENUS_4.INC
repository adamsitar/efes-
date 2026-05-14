{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TWinMenu                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TWinMenu.Init(_title: string; _hlpXXX: Pchar; _FirstItem: PItem);
      var   Item: PItem;
      begin
        inherited Init(@Self, initX,initY,0,0, kbNoKey, cmNil,delchar(_title,[cnst_HotKey]), true);
        hlpXXX:= _hlpXXX;
        FirstItem:= _FirstItem; ActItem:= _FirstItem; LastItem:= _FirstItem;
       { zaradenie do stacku  v poradi vypisu }
        Item:= _FirstItem;
        while (Item <> nil) do
          begin
            LastItem:= Item;
            Item^.PushToStack(@Self);  { zaradi polozku menu do zasobnika menu }
            Item:= Item^.Next
          end;
        initialized:= false;
        PConfirmed:= nil;
       { vypocet velkosti menu  }
        XY(initX,initY,get_width,15);
        set_size
      end;


procedure TWinMenu.AddItem(_Item: PItem);
    var   Item: PItem;
    begin
    { zaradenie do stacku  }
      if FirstItem=nil then FirstItem:= _Item;
      if ActItem=nil   then ActItem:= FirstItem;
      if LastItem<>nil then LastItem^.Next:= _Item;
      LastItem:= _Item;
      LastItem^.PushToStack(@Self);
    { uprava velkosti menu }
      set_size
    end; { AddItem }


procedure TWinMenu.DoneItems;
    begin
    { zaradenie do stacku  }
      if FirstItem=nil then Exit;

      while (Stack^.ObjectPtr<>pointer(FirstItem)) do
        begin
          Dispose(Stack^.ObjectPtr,Done);
          Pop(Stack)
        end;
      Dispose(Stack^.ObjectPtr,Done);
      Pop(Stack);
      FirstItem:= nil;
      ActItem:= nil;
      LastItem:= nil
    end; { DoneItems }


{
  vypocet velkosti menu, nekontrolujem na prekrocenie rozsahu MaxX a MaxY !
}
procedure TWinMenu.set_size;
    var   Item : PItem;
          max_x, max_y, item_x,item_y, dx,dy: int;
          s : string;
    begin
      max_x:= 0; max_y:= 0; dy:= winHEIGHT + 15;

      Item:= FirstItem;
      while (Item <> nil) do
        begin
          max_x:= Maximum(max_x,Item^.get_width);
          max_y:= Maximum(max_y,Item^.get_height);
          inc(dy,Item^.get_height);
          Item:= Item^.Next
        end;
      sirka:= Maximum(max_x+50,get_width);
      vyska:= max_y;
      x1:= x0 + sirka;
      y1:= y0 + dy;

      btNil^.XY(x0+10,y0+10,btHEIGHT,btHEIGHT);
      btTitle^.XY(x0+28,y0+10,x1-x0-56,btHEIGHT);
      btEsc^.XY(x1-24,y0+10,btHEIGHT,btHEIGHT);

      Item:= FirstItem;
      dx:= sirka-40;
      item_x :=  x0 + dx_ITEM;
      item_y :=  y0 + dy_ITEM;
      while (Item <> nil) do
        begin
          Item^.InitXY(item_x,item_y,dx);
          inc(item_y,Item^.get_height);
          Item:= Item^.Next
        end;

      set_region(10,winHEIGHT-5,-10,-10, r);
      with btTitle^ do sirka:= x1-x0;
    end; { set_size }

{
 Predchadzajuca polozka menu.
 Musim sa zastavit na FirstItem, lebo pred je uz samotne okno.
}
function  TWinMenu.PrevItem(P: PItem): PItem;
   var    P0,_P: PItem;
   label  L;
   begin
     P0:= P; _P:= P;
     L: if _P<>FirstItem then _P:= PItem( GetView( PrevObjectReg(GetObjectReg(_P)) ))
        else _P:= LastItem;
        if (_P=nil) or (P0=_P) then _P:= LastItem
        else if (_P^.title= nil) or (not _P^.isEnabled) then goto L;
     PrevItem:= _P
   end;

{
 nasledujuca polozka menu
}
function  TWinMenu.NextItem(P: PItem): PItem;
   var    P0,_P: PItem;
   label  L;
   begin
     P0:= P; _P:= P;
     L : if _P<>LastItem then _P:= PItem( GetView( NextObjectReg(GetObjectReg(_P)) ))
         else _P:= FirstItem;
         if (_P=nil) or (P0=_P) then _P:= FirstItem
         else if (_P^.title=nil) or (not _P^.isEnabled) then goto L;
     NextItem:= _P
   end;

{
 nastavi novu ActItem a prekresli
}
procedure TWinMenu.SetActItem(_next: PItem);
   begin
     if ActItem=nil then Exit;
     ActItem^.ActiveOff;
     ActItem:= _next;
     ActItem^.ActiveOn
   end;


procedure TWinMenu.HandleEvent(var _Event: TEvent);
    var   p : PItem;
    label L;
    begin
      L: inherited HandleEvent(_Event);

      if (_Event.What=evKeyDown) or (mnu_mouse_scroll and ((_Event.What and evMouse)<>0)) then
         begin
           if mnu_mouse_scroll and ((_Event.What and evMouse)<>0) then SetKeyEvent(_Event,@Self,m_to_kb(_Event.M));
           case _Event.Key of
              kbEnter, kbUp,kbDown,kbHome,kbEnd :
                begin
                  case _Event.Key of
                    kbEnter : if (ActItem<>nil) and (ActItem^.isEnabled) then
                                 begin
                                   _Event.Key:= ActItem^.kbAct; {SetCommand(_Event,cmRunSubMenu);}
                                   goto L
                                 end;
                    kbUp    : SetActItem(PrevItem(ActItem));
                    kbDown  : SetActItem(NextItem(ActItem));
                    kbHome  : SetActItem(NextItem(LastItem){FirstItem});
                    kbEnd   : SetActItem(PrevItem(FirstItem){LastItem})
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

      else if isCommand(_Event,cmChangeActItem) then
              begin
                Move(MailBox^,p,SizeOf(pointer));
                SetActItem(p);
                ClearEvent(_Event)
              end
    end;


procedure TWinMenu.Draw;
    var   Item: PItem;
          bp: bool;
          xl,yl, dx : int;
          s: string;
    begin
      if not initialized then
         begin
           Item:= FirstItem;
           while (Item <> nil) do
             begin
               Item^.init_for_draw;
               Item:= Item^.Next
             end;

           with btTitle^ do
             begin
               {sirka:= x1-x0;}
               dx:= (x1-x0) shr 3; s:= strpas(title);
               if dx < length(s) then new_title(copy(s,1,N(dx-length(titLARGE)))+titLARGE,false)
             end;
           initialized:= true
         end;

      m_off(bp, xl,yl);
      inherited Draw;
      SetActItem(NextItem(LastItem));
      {FirstItem^.Draw;}
      m_on(bp, xl,yl);
      if mnu_mouse_scroll then begin ev_mx:= mouse_status.stat.x; ev_my:= mouse_status.stat.y end
    end;



procedure TWinMenu.ReInitDraw;
    begin
      initialized:= false;
      Draw
    end;


function TWinMenu.EndState(var _Event: TEvent): bool;
   var   b : bool;
         m : Tshift_menu;
   begin
     if isCommand(_Event,cmNil) then ClearEvent(_Event)
     else if isCommand(_Event,cmXXXX) then
       if PConfirmed<>nil then TProc(PConfirmed);
     b:=      inherited EndState(_Event)
         or  (    (_Event.What and evMessage) <> 0)
               and (   (_Event.Whom    = MainAppPtr^)  {(_Event.Command = cmXXXX)}
                    or (_Event.Command = cmLeftMenu)
                    or (_Event.Command = cmRightMenu)
                    or (_Event.Command = cmAltMenu )
             );
     EndState:= b;
     if b then
        begin
          initialized:= false;
          if isCommand(_Event,cmCancel) then ClearEvent(_Event);
          if isCommand(_Event,cmLeftMenu) or isCommand(_Event,cmRightMenu) then
             begin
               m.c:= PSubMenu(Owner)^.kbHot;
               m.p:= Owner;
               Move(m,MailBox^,sizeof(m))
             end;
        end
   end;

procedure TWinMenu.Image;
    var   bp: bool; xl,yl : int;
    begin
      m_off(bp, xl,yl);
      BGIgraph.Button(x0+r.x0,y0+r.y0,x1+r.x1,y1+r.y1, clBUTTON_COLOR, btSmall, btON);
      m_on(bp, xl,yl);
    end; { Image }


procedure TWinMenu_S.init_buttons;
    begin
      { Zamerne prazdne, zostane nastavenie :
        btOK:= nil; btCancel:= nil;
      }
    end;

function TWinMenu_S.get_width: word;
   begin
     get_width:= TWinMenu.get_width
   end;
