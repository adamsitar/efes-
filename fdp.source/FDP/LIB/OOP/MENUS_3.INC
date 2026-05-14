{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TRadioItem                                               €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TRadioItem.Init(_title: string; _Next: PItem);
      begin
        inherited Init(_title, nil, _Next);
        cmXXXX:= cmSwitchPressed; mnu:= _radioitem
      end;

procedure TRadioItem.HandleEvent(var _Event: TEvent);
    begin
      if isEnabled and visible then
         if    isClicked(_Event)
            or isKey(_Event,kbHot)
            or (Active and (_Event.What=evKeyDown) and isKey(_Event,kbAct)) then
               begin
                 if stat = btOFF then
                    begin
                      stat:= btON;
                      Draw;
                      SetCommand(_Event,cmXXXX) { sprava len pre RadioItem }
                    end
                 else ClearEvent(_Event)
               end
    end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TRadio                                                   €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
const rdOFF = btHEIGHT-4;

constructor TRadio.Init(_title: string; _check_adr: pointer; _val_off: int; _FirstItem: PSwitch2; _Next: PSwitch2);
      var   Item : PItem;
            max_x,max_y, pocet_item, item_x,item_y, item_dx, dx,dy : int;
      begin
        inherited Init(_title, cmNil, _Next);
        mnu:= _radio;
        Switches:= New(PGroup,Init(nil, 0,0,0,0));
        Switches^.MCursor:= SIPKA;
        check_adr:= _check_adr;
        val_off  := _val_off;
        swON := byte(check_adr^) - _val_off;
        sw   := 0;
        max_x:= 0; max_y:= 0;
        FirstItem:= _FirstItem; ActItem:= _FirstItem; LastItem:= _FirstItem;
        Item:= _FirstItem;
        while (Item <> nil) do
         begin
           LastItem:= Item;
           Item^.PushToStack(Switches);
           max_x:= Maximum(max_x,Item^.get_width);
           Inc(max_y,Item^.get_height);
           if sw=swON then Item^.stat:= btON;
           Item:= Item^.Next;
           Inc(sw);
         end;
        Dec(sw)
      end;

procedure radio_width(V: PView; var dx: int); far;
    begin
      dx:= Maximum(PItem(V)^.get_width,dx);
    end;

function TRadio.get_width: int;
   var   dx  : int;
   begin
     dx:= 0;
     ForEach(@radio_width,Switches^.Stack,@dx);
     get_width:= dx + btHEIGHT;
   end;

procedure radio_height(V: PView; var dy: int); far;
    begin
      Inc(dy, PItem(V)^.get_height);
    end;

function TRadio.get_height: int;
   var   dy  : int;
   begin
     dy:= rdOFF;
     ForEach(@radio_height,Switches^.Stack,@dy);
     Inc(dy,rdOFF);
     get_height:= dy
   end;


procedure init_xy(V: PView; xy: PRegion); far;
    begin
      PItem(V)^.InitXY(xy^.x0,xy^.y0,xy^.x1);
      Dec(xy^.y0,PItem(V)^.get_height)
    end;

procedure TRadio.InitXY(x,y, dx: int);
    var   y_r,x_s : int;
          _xy     : TRegion;
    begin
      XY(x, y + rdOFF div 2 - 2, dx, get_height - trunc(1.5*rdOFF+0.5) + 4);
      Switches^.XY(x0,y0,x1-x0,y1-y0);
      _xy.x0:= x0 + btHEIGHT div 2;
      _xy.y0:= y1 - rdOFF - 10;
      _xy.x1:= dx - btHEIGHT;
      ForEach(@init_xy,Switches^.Stack,@_xy);
    end;

destructor TRadio.Done;
     begin
       Switches^.Done;
       Dispose(Switches);
       inherited Done;
     end;

procedure TRadio.SwitchesDraw;
    var   bp: bool; xl,yl : int;
    begin
      m_off(bp, xl,yl);
      on_off(x0,y0,x1,y1,clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT,btSmall,btON);
      Switches^.Draw;
      m_on(bp, xl,yl);
    end;

procedure TRadio.Draw;
    var   Item : PItem;
    begin
      sw   := 0;
      swON := byte(check_adr^) - val_off;
      Item := FirstItem;
      while (Item <> nil) do
        begin
          if sw=swON then Item^.stat:= btON
          else Item^.stat:= btOFF;
          Item:= Item^.Next;
          Inc(sw);
        end;
      Dec(sw);
      SwitchesDraw
    end;

procedure TRadio.m_shape;
    begin
      Switches^.m_shape
    end;


procedure TRadio.HandleEvent(var _Event: TEvent);
    var   S: PObjectReg;
          t: int;
    begin
      Switches^.HandleEvent(_Event);
      if (_Event.What and evMessage <> 0) then
         case _Event.Command of
           cmSwitchPressed :
                  begin
                    t:= sw; S:= Switches^.Stack;
                    while (t<>swON) do
                      begin
                        S:= Switches^.PrevObjectReg(S);
                        Dec(t)
                      end;
                    with PRadioItem(S^.ObjectPtr)^ do
                      begin
                        stat:= btOFF;
                        Draw
                      end;
                    t:= sw; S:= Switches^.Stack;
                    while (PRadioItem(S^.ObjectPtr)^.stat <> btON) do
                      begin
                        S:= Switches^.PrevObjectReg(S);
                        Dec(t)
                      end;
                    swON:= t;
                    ClearEvent(_Event)
                  end;
           cmOK : byte(check_adr^):= swON + val_off
         end;
    end;

procedure TRadio.MoveRel(dx,dy: int);
    begin
      inherited MoveRel(dx,dy);
      Switches^.MoveRel(dx,dy)
    end;


procedure TRadio.ActiveOn;
    begin
      {nastavit priznak aktivity}
    end;

procedure TRadio.ActiveOff;
    begin
    end;

(*
function  TRadio.PrevItem(P: PItem): PItem;
   begin
     if P<>FirstItem then P:= PItem( GetView( PrevViewReg(GetViewReg(P)) ))
     else P:= LastItem;
     if P^.title= nil then P:= PrevItem(P);
     PrevItem:= P
   end;

function  TWinMenu.NextItem(P: PItem): PItem;
   begin
     if P<>LastItem then P:= PItem( GetView( NextViewReg(GetViewReg(P)) ))
     else P:= FirstItem;
     if P^.title= nil then P:= NextItem(P);
     NextItem:= P
   end;

procedure TWinMenu.SetActItem(_next: PItem);
   begin
     ActItem^.ActiveOff;
     ActItem:= _next;
     ActItem^.ActiveOn
   end;
*)


