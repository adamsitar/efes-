{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TBarMenu                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
const dxITEMS = 17;

function TBarmenu.inView(x,y: int): bool;
   begin
     inView:= inRectangle(x,y, x0,y0,x1,y1)
   end;

constructor TBarMenu.Init(_title: string; _FirstItem: PItem);
      var   Item : PItem;
            mnu_x0, mnu_dx, dx: int;
      begin
        inherited Init(nil, 0,0,MaxX,btHEIGHT);
        ScreenSave:= false; MouseSave:= false;
        FirstItem := _FirstItem;

      { vypocet velkosti mnu }
        mnu_x0:= 0;
        if Length(_title)<>0 then mnu_x0:= length(_title)+dx_ch+dxITEMS;

        Item:= _FirstItem;
        mnu_dx:= mnu_x0 + 1;
        while (Item <> nil) do
          begin
            inc(mnu_dx,Item^.get_width+dxITEMS);
            Item:= Item^.Next;
          end;
        if (MaxX < mnu_dx+10) then mnu_x0:= maximum(mnu_x0+mnu_dx+10-MaxX,0);

        bar_mnuXY.x0:= mnu_x0;
        if (FirstItem<>nil) and (FirstItem^.cmXXXX=cmAbout) then inc(bar_mnuXY.x0,FirstItem^.get_width+dxITEMS);

      { nastavenie hlavnych poloziek menu }
        init_menus:= true;
        dx:= mnu_x0;
        Item:= _FirstItem;
        while (Item <> nil) do with Item^ do
          begin
            PushToStack(@Self);
           {if (kbHot<>kbNoKey) then kbHot:= GetAltCode(kbHot);}
            InitXY(dx,0,get_width+dxITEMS);
            if (PMenu<>nil) then PMenu^.MoveRel(dx-initX, btHEIGHT+5 - initY);
            inc(dx,get_width+dxITEMS);
            Item:= Item^.Next;
          end;

        bar_mnuXY.x1:= mnu_dx;
        bar_mnuXY.y0:= 0;
        bar_mnuXY.y1:= btHEIGHT;

      { 2x nefunkcny button }
        if _title<>'' then
            btTit:= New(PButton,Init(@Self, 0,0,maximum(bar_mnuXY.x0-1,0),btHEIGHT,kbNoKey,cmNil,_title,0,LightCyan,Yellow))
        else btTit:= nil;
        btEmp:= New(PButton,Init(@Self, mnu_dx,0,maximum(mnu_dx,MaxX-mnu_dx),btHEIGHT,kbNoKey,cmNil,'',0,LightCyan,Yellow));
        init_menus:= false
      end;


procedure TBarMenu.ReInit(x,y,dx,dy: int);
    var   Item : PItem;
          mnu_x0, mnu_dx, _dx : int;
    begin
      XY(0,0,MaxX,btHEIGHT);

      if btTit<>nil then mnu_x0:= strlen(btTit^.title)+dx_ch+dxITEMS
      else mnu_x0:= 0;
      Item:= FirstItem;
      mnu_dx:= mnu_x0 + 1;
      while (Item <> nil) do
        begin
          inc(mnu_dx,Item^.get_width+dxITEMS);
          Item:= Item^.Next;
        end;
      if (MaxX < mnu_dx+10) then mnu_x0:= maximum(mnu_x0+mnu_dx+10-MaxX,0);

      bar_mnuXY.x0:= mnu_x0;
      if (FirstItem<>nil) and (FirstItem^.cmXXXX=cmAbout) then inc(bar_mnuXY.x0,FirstItem^.get_width+dxITEMS);

      Item:= FirstItem;
      init_menus:= true;
      _dx:= mnu_x0;
      while (Item <> nil) do with Item^ do
        begin
          if PMenu<>nil then with PMenu^ do MoveRel(_dx-x0, btHEIGHT+5 - y0);
          if StrLen(title)>0 then inc(_dx,get_width+dxITEMS);
          Item:= Item^.Next;
        end;
      btEmp^.x1:= MaxX;

      if btTit<>nil then btTit^.XY(0,0,maximum(bar_mnuXY.x0-1,0),btHEIGHT);
      btEmp^.XY(mnu_dx,0,maximum(mnu_dx,MaxX-mnu_dx),btHEIGHT);

      init_menus:= false
    end; { ReInit }


function isSubMenu(V: PView): bool; far;
   begin
     isSubMenu:=     {(PButton(V)^.cmXXXX<>cmNil)   vylucenie buttonov }
                     (PItem(V)^.mnu=_submenu)     { vylucenie jednoduchych spinacov }
                 and (PItem(V)^.PMenu<>nil)       { vylucenie jednoduchych spinacov }
                 and (PItem(V)^.isEnabled)
   end;


var PV: PView;

function last_menu(V: PView): bool; far;
   var   m : Tshift_menu;
   begin
     Move(MailBox^,m,sizeof(m));
     if     (V=m.p) and (PSubMenu(V)^.kbHot=m.c)
        and isSubMenu(V) { vylucenie buttonov a jednoduchych spinacov }
        then begin
               last_menu:= true;
               PV:= V
             end
        else last_menu:= false
   end;

procedure TBarMenu.HandleEvent(var _Event: TEvent);
    var   VR : PObjectReg;
          I  : PItem;
    begin
      inherited HandleEvent(_Event);

      with _Event do
        if (What=evCommand) and ((Command=cmLeftMenu) or (Command=cmRightMenu)) then
           begin
             { najst ktore menu inicializuje char(MailBox^) }
             PV:= nil;
             FirstThat(@last_menu,Stack);
             if PV=nil then Exit;
             VR:= GetObjectReg(PV); {ii:= VR;}
             case Command of
               cmLeftMenu : repeat VR:= PrevObjectReg(VR) until isSubMenu(PView(VR^.ObjectPtr));
               cmRightMenu: repeat VR:= NextObjectReg(VR) until isSubMenu(PView(VR^.ObjectPtr))
             end;
             ClearEvent(_Event);
             Pending.What:= evKeyDown;
             Pending.Key:= PItem(VR^.ObjectPtr)^.kbHot
           end

        else if isCommand(_Event,cmChangeActItem) then ClearEvent(_Event)
             else if (_Event.What=evKeyDown) and (_Event.key in [#139..#173,#243..#252]) then
                     begin
                       { prepnutie menu cez Alt... }
                     end

        else if isCommand(_Event,cmMenuRedraw) then
                begin
                  if activeMenu<>nil then
                     begin
                       activeMenu^.ReInitDraw;
                       activeMenu^.ClearEvent(_Event);
                     end
                  {I:= FirstItem;
                  while (I <> nil) do with I^ do
                    begin
                      if (PMenu<>nil) and PMenu^.is_active then with PMenu^ do
                         begin
                           Draw;
                           ClearEvent(_Event);
                           break
                         end;
                      I:= I^.Next
                    end;}
                end
    end;

function TBarMenu.inBarMenuKeys(key: char): bool;
   begin
     Move(key,MailBox^,SizeOf(char));
     PV:= nil;
     FirstThat(@last_menu,Stack);
     inBarMenuKeys:= PV<>nil
   end;

