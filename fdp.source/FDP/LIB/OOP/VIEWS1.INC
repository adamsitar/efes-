{ ------------------------------------------------------------ }
{  TGroup                                                      }
{ ------------------------------------------------------------ }

constructor TGroup.Init(_Owner: PGroup; x,y,dx,dy: int);
      begin
        inherited Init(_Owner, x,y,dx,dy);
        istview := false;

        slow_done_app:= false;
        check_idle_all:= false;

        MouseSave:= true;
        ScreenSave:= true;
        ScreenDesc:= -1;

        on_board:= false;
        in_frame:= true;

        PIS:= true;
        PREPIS:= 0;
        PREPISANE:= absTime;
        s_prekreslit:= false
      end;


function TGroup.is_to_be_Run: bool;
   begin
     is_to_be_Run:= true
   end;

procedure TGroup.InitApp;
    begin
    end;

procedure TGroup.InitApp2;
    begin
    end;

procedure TGroup.DoneApp;
    begin
    end;

procedure TGroup.DoneApp2;
    begin
    end;


function TGroup.InitRun(var _Event: TEvent; var xl,yl: int; var isapp,isrun: bool): bool;
   begin
     kb_clear;
     xl:= mouse_status.stat.x; yl:= mouse_status.stat.y;
     mouse.set_xy(x0 + (x1-x0) div 2,y0 + (y1-y0) div 2);

     Push(Application,@Self);

     isapp:= true;
     isrun:= true;

     if ScreenSave then
        begin
          ScreenDesc:= PushScreen;
          isapp:= ScreenDesc>-1;
          if (not isapp) and (not s_nem) then
             begin
               s_nem:= true;
               mess.BeepErr;
               _write_err_log('Not enough memory ('+inttostr(maxavail,6,0)+').');
               s_nem:= false
             end;
         end;

     if isapp then
        begin
          InitApp;
          isrun:= is_to_be_Run;
          if isrun then
             begin
               if ScreenSave then with ScreenPtr do
                  begin
                    FillWin(Region.x0+Xtien,Region.y0+Ytien,
                            Region.x1+Xtien,Region.y1+Ytien,
                            Black)
                  end;
               Draw;
               on_board:= true;
               InitApp2
             end
        end;

     InitRun:= isapp and isrun
   end;

procedure  TGroup.DoneRun(var _Event: TEvent; xl,yl: int; isapp,isrun: bool);
    begin
      if isapp then
         begin
           on_board:= false;
           if isrun then DoneApp2;
           if ScreenSave then PopScreen;
           DoneApp;
         end;
      Pop(Application);
      if MouseSave then mouse.set_xy(xl,yl);
      kb_clear
    end;

procedure TGroup.Run(var _Event: TEvent);
    var   xl,yl: int;
          isapp,isrun: bool;
    begin
      if InitRun(_Event, xl,yl, isapp,isrun) then inherited Run(_Event);
      DoneRun(_Event, xl,yl, isapp,isrun);
    end;


{procedure TGroup.Run(var _Event: TEvent);
    var   xl,yl: int;
          bres : bool;
    begin
      xl:= mouse_status.stat.x; yl:= mouse_status.stat.y;
      mouse.set_xy(x0 + (x1-x0) div 2,y0 + (y1-y0) div 2);

      Push(Application,@Self);

      bres:= true;
      if ScreenSave then
         begin
           ScreenDesc:= PushScreen;
           if ScreenDesc=-1 then
              begin
                if not s_nem then
                   begin
                     s_nem:= true;
                     mess.BeepErr;
                     _write_err_log('Not enough memory ('+inttostr(maxavail,6,0)+').');
                     s_nem:= false
                   end;
                bres:= false;
              end
          end;

       if bres then
          begin
            InitApp;
            if is_to_be_Run then
               begin
                 if ScreenSave then with ScreenPtr do
                    FillWin(Region.x0+Xtien,Region.y0+Ytien,Region.x1+Xtien,Region.y1+Ytien, Black);
                 Draw;
                 InitApp2;
                 inherited Run(_Event);
                 DoneApp2;
              end;
            if ScreenSave then PopScreen;
            DoneApp;
          end;

      Pop(Application);

      if MouseSave then mouse.set_xy(xl,yl);
      kb_clear
    end;  TGroup.Run }


{
  zvacsenie, len pre pohlady neodpamatavajuce si podklad
}
procedure _idle(O: PObject; E: PEvent); far;
    begin
      O^.Idle(E^)
    end;

procedure TGroup.Idle(var _Event: TEvent);
    begin
      if check_idle_all then ForEach(@_idle,Stack,@_Event);
      inherited Idle(_Event);
      Prekreslit
    end;


function TGroup.GetView(P: PObjectReg): PView;
   begin
     if (P<>nil) and (P^.ObjectPtr^.ObjectType >= obj_view)
        then GetView:= PView(P^.ObjectPtr) { TGroup by mal obsahovat len objekty typu PView }
        else GetView:= nil
   end; { GetView }



{ --------------------------
  uchovanie obrazovky:
  --------------------------}

const Xtien = 5;
      Ytien = 5;

function  TGroup.SaveScreen: int;
    var   dis: int;
    begin
      with ScreenPtr do
        begin
          if (Region.x1 + Xtien + btmdXY.x1 > GetMaxXM) then
             begin
               dis:= GetMaxXM - (Region.x1 + Xtien + btmdXY.x1);
               MoveRel(dis,0);
               Inc(Region.x0,dis); Inc(Region.x1,dis);
             end;
          if (Region.y1 + Ytien + btmdXY.y1 > GetMaxY) then
             begin
               dis:= GetMaxY - (Region.y1 + Ytien + btmdXY.y1);
               MoveRel(0,dis);
               Inc(Region.y0,dis); Inc(Region.y1,dis);
             end;
          Region.x0:= maximum(0,Region.x0); Region.y0:= maximum(0,Region.y0);
          SaveScreen:= OpenWin(Region.x0,Region.y0,Region.x1,Region.y1, Xtien,Ytien, false);
        end
    end; { TGroup.SaveScreen }


procedure view_size(V: PObject; S: PRegionSize); far;
    begin
      if (V^.ObjectType>=obj_view) then PView(V)^.get_reg_size(S)
    end; { view_size }

procedure TGroup.get_reg_size(S: PRegionSize);
    begin
      ForEach(@view_size,Stack,S);
      inherited get_reg_size(S)
    end; { TGroup.get_reg_size }


function  TGroup.PushScreen: int;
    begin
      {if not ScreenSave then Exit;}
      ScreenPtr.Size:= 0;
      get_reg_size(@ScreenPtr);
      PushScreen:= SaveScreen
    end;  { TGroup.PushScreen }


procedure TGroup.RestoreScreen;
    begin
      CloseWin
    end; { TGroup.RestoreScreen }

procedure TGroup.PopScreen;
    begin
      {if not ScreenSave then Exit;}
      RestoreScreen
    end;  { TGroup.PopScreen }



function TGroup.ma_sa_prekreslit: bool;
   begin
     if PREPISANE > absTime then PREPISANE:= absTime;
     ma_sa_prekreslit:= PREPIS > PREPISANE;
   end;

procedure TGroup.Prekreslenie;
    begin
      if ma_sa_prekreslit then
         begin
           Draw;
           PREPIS:= 0;
           PREPISANE:= absTime;
         end;
    end;


procedure _prekreslit(V: PObject; p: pointer); far;
    begin
      if     (V^.ObjectType>=obj_view)
         and (not PView(V)^.istview)
         and PGroup(V)^.ma_sa_prekreslit
         then PGroup(V)^.Prekreslit
    end;

procedure TGroup.Prekreslit;
    var   s1,s2: string;
    begin
      if ma_sa_prekreslit then
         begin
           {Str(prepis,s1); Str(prepisane,s2); write_err_log(s1+','+s2);}
           if (not s_prekreslit) and (not OverlapWin(x0,y0,x1,y1, ScreenDesc)) then
              begin
                s_prekreslit:= true;
                Prekreslenie;
                s_prekreslit:= false
              end
           else if check_idle_all then
                begin
                  ForEach(@_prekreslit,Stack,nil);
                end;
           {Str(prepis,s1); Str(prepisane,s2); write_err_log(s1+','+s2);}
         end
    end;  { TGroup.Prekreslenie }


{ presun vsetkych pohladov skupin skupiny
}
procedure move_view(V: PObject; P: PPoint); far;
    begin
      if (V^.ObjectType>=obj_view) then PView(V)^.MoveRel(P^.x,P^.y)
    end; { move_to__view }

procedure TGroup.MoveRel(dx,dy: int);
    var   P: PPoint;
    begin
      New(P);
      P^.x:= dx;
      P^.y:= dy;
      ForEach(@move_view,Stack,P);
      inherited MoveRel(dx,dy);
      Dispose(P);
    end; { TGroup.MoveRel }

{
  zvacsenie, len pre pohlady neodpamatavajuce si podklad
}
procedure resize_view(V: PObject; P: PPoint); far;
    begin
      if (V^.ObjectType>=obj_view) then PView(V)^.Resize(P^.x,P^.y)
    end; { move_to__view }

procedure TGroup.Resize(dx,dy: int);
    var   P: PPoint;
    begin
      New(P);
      P^.x:= dx;
      P^.y:= dy;
      ForEach(@resize_view,Stack,P);
      inherited Resize(dx,dy);
      Dispose(P);
    end; { TGroup.MoveRel }


procedure TGroup.Centre;
    begin
    end;

{
  vykreslenie vsetkych pohladov skupiny
}
procedure draw_view(V: PObject; P: pointer); far;
    begin
      if (V^.ObjectType>=obj_view) then PView(V)^.Draw
    end; { draw_view }

procedure TGroup.Draw;
    var   bp: bool; xl,yl: int;
    begin
      m_off(bp, xl,yl);
      ForEach(@draw_view,Stack,nil);
      PREPIS:= 0;
      PREPISANE:= absTime;
      m_on(bp, xl,yl)
    end; { TGroup.Draw }


function in_view(V: PView): bool; far;
   begin
     in_view:= V^.inView(mouse_status.stat.x,mouse_status.stat.y)
   end;

function TGroup.inView(x,y: int): bool;
   var   r: bool;
   begin
     r:= false;
     if visible then
        begin
          if not in_frame then r:= FirstThat(@in_view,Stack)<>nil;
          if not r then r:= inherited inView(x,y)
        end;
     inView:= r
   end;

{
  nastavenie tvaru kurzora mysi nad patricnym pohladom,
}
function find_view(V: PObject): bool; far;
   begin
     if     (V^.ObjectType>=obj_view)
        and (PView(V)^.visible)
        and (PView(V)^.inView(mouse_status.stat.x,mouse_status.stat.y)) then
            begin
              find_view:= true;
             {PView(V)^.m_shape}
            end
     else find_view:= false
   end;

{
  najde vlastnika najmensej plochy
}
procedure TGroup.m_shape;
    var   S,R  : PObjectReg;
          P,Pi, l1,l2 : long;
    label F;
    begin
      S:= Stack; R:= nil; P:= High(long);
      F: S:= FirstThat(@find_view,S);
      if S<>nil then
         begin
           with PView(S^.ObjectPtr)^ do
             begin
               l1:= x1-x0; l2:= y1-y0;
               Pi:= Abs(l1*l2)
             end;
           if Pi<P then
              begin
                P:= Pi;
                R:= S
              end;
           S:= S^.PrevReg;
           goto F
         end;
      if (R<>nil) then PView(R^.ObjectPtr)^.m_shape
      else if inView(mouse_status.stat.x,mouse_status.stat.y) then m_cursor(MCursor)
           else m_cursor(MYS)
    end;


procedure TGroup.HandleEvent(var _Event: TEvent);
    var   Pxy  : TPoint;
          p    : PGroup;
          {$IFDEF DEBUG_WIN}
            TempWinReg: PWinReg;
          {$ENDIF}

    begin
      inherited HandleEvent(_Event);

      if (_Event.What=evNothing) then Exit;

      case _Event.What of
        evCommand,evBroadcast :
          begin
            case _Event.Command of
              cmMoveWindow     : if (_Event.Whom=@Self) then
                                    begin
                                      Move(MailBox^,Pxy,SizeOf(Pxy));
                                      PopScreen;
                                      MoveRel(Pxy.x-ScreenPtr.Region.x0, Pxy.y-ScreenPtr.Region.y0);
                                      PushScreen;
                                      Draw
                                     end
                                 else Exit;
              cmProgramStatus  : if @p_dlg<>nil then p_dlg(msgSYSINFO,@_text,nil,250,110,nil,0);
              else Exit
            end;
            ClearEvent(_Event)
          end;

        evKeyDown :
          case _Event.Key of
            {
            kbCentre             : begin
                                     if Owner<>nil then p:= PGroup(Owner) else p:= @Self;
                                     p^.Centre;
                                     p^.Draw;
                                     ClearEvent(_Event)
                                   end;
            }
            kbCtrlPrScr,kbCtrlBS : SetCommand(Pending,cmRefresh);
            {kbCtrlF12,}#255     : SetCommand(Pending,cmProgramStatus);

           {$IFDEF WRITELN_NET}
             kbAltF11            : WRITELN_FLOW:= true;
             kbCtrlF11           : WRITELN_FLOW:= false;
           {$ENDIF}

           {$IFDEF DEBUG}
             ' '                 : SetTimem(hour,min,59);
           {$ENDIF}

          end

      end; { case }

      { dalej pre ladenie, netreba si vsimat... }
    end; { TGroup.HandleEvent }
