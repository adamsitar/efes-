{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                                          Û
Û TAppGui                                                  Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ

 Abstraktny objekt, udrziava inormacie
 o permamentych objektoch na obrazovke

}

constructor TAppGui.Init(_Owner: PApp; x,y,dx,dy: int);
      begin
       {$IFDEF DATA_WRITTEN_IN_APP}
        EMS_test;
       {$ENDIF}
        inherited Init(_Owner, x,y,dx,dy);
        AppScroll:= nil;
        StatusLine:= nil;
        last_active:= nil;
        check_idle_all:= true
      end;


procedure TAppGUI.ReInit(x,y,dx,dy: int);
    begin
      XY(0,0,MaxX,MaxY);
      inherited ReInit(0,0,MaxX,MaxY);
    end;


procedure TAppGui.Idle(var _Event: TEvent);
    begin
      inherited Idle(_Event)
    end;


procedure TAppGui.HandleEvent(var _Event: TEvent);
    var   O: PObject;
    begin
      inherited HandleEvent(_Event);

      case _Event.What of

        evCommand, evBroadcast:
          case _Event.Command of

            cmSetActive : if InObject(_Event.From,O) and (O^.ObjectType>=obj_view) then set_active(PView(O));

            else Exit
          end;

        evKeyDown:
          case _Event.Key of

            kbTab      : last_active:= next_active (last_active);
            kbShiftTab : last_active:= prev_active (last_active)

            else Exit
          end

        else Exit
      end; { case }
      ClearEvent(_Event)
    end;


function TAppGui.next_active(P: PView): PView;
   begin
     if P<>nil then
        begin
          P:= GetView( NextObjectReg(GetObjectReg(P)) );
          if not set_active(P) then P:= next_active(P);  { ! rekurzia }
        end;
     next_active:= P
   end;

function TAppGui.prev_active(P: PView): PView;
   begin
     if P<>nil then
        begin
          P:= GetView( PrevObjectReg(GetObjectReg(P)) );
          if not set_active(P) then P:= prev_active(P);  { ! rekurzia }
        end;
     prev_active:= P
   end;

function TAppGui.set_active(P: PView): bool;
   var   is_activable: bool;
   begin
     if P<>nil then
        begin
          is_activable:= P^.visible and (P^.ObjectType>=obj_view_active);
          set_active:= is_activable;
          if (is_activable) then
             begin
               {if last_active=P then P:= _4okno;}
               if last_active<>nil then last_active^.ActiveOff;
               P^.ActiveOn;
               last_active:= P
             end
        end
     else set_active:= true { proti zacykleniu }
   end;
