 constructor O_Smmi.Init(_Owner: PApp
                           {$IFDEF DATA_WRITTEN_IN_APP}
                             ; AppDataObject : PPObject
                             ; _cl_SEND,_cl_REC: byte
                           {$ENDIF}
                          );
       begin
         inherited Init(_Owner, 0,btHEIGHT+3, MaxX, MaxY);

         {$IFDEF DATA_WRITTEN_IN_APP}
           AppScroll:= New(POScrollStream,Init(@Self,
                           AppDataObject, '',
                           0,btmdXY.y0,MaxX,
                           2,2,4,0,
                           -1,
                           false,false,
                           0,0, nil,nil,nil,
                           _cl_SEND,_cl_REC,
                           false,true,
                           nil)
                          );
         {$ENDIF}

         HODINY_init(_Owner, 0,0);
         {$IFDEF STATUS} STATUS_init(_Owner {$IFDEF DATA_WRITTEN_IN_APP},@Self{$ENDIF}); {$ENDIF}
         set_region(0,btmdXY.y0,0,Clock^.y1-Clock^.y0+5,btmdXY);
         sc_dy:= 50;
         hlpXXX:= hlp_GUI;

         check_idle_all:= true;
         MAPS_DATA:= true;
       end;


{ prepocet vysky scrollocich zoznamov pre prelety;
  poloha je zatial staticka;
}
 procedure O_Smmi.ReInit(x,y,dx,dy: int);
     begin
       if (not NET_ENABLED) then Exit;
       inherited ReInit(x,y,dx,dy);
       Clock^.reinit(0,0,MaxX,MaxY);
       {$IFDEF STATUS} STATUS_reinit; {$ENDIF}
       {$IFDEF DATA_WRITTEN_IN_APP}
         if AppScroll<>nil then
            begin
              AppScroll^.hide;
              AppScroll^.ReInit(0,btmdXY.y0+1,dx-3,dy-(btmdXY.y0+btmdXY.y1+3));
              AppScroll^.visible:= true;
              set_active(AppScroll)
            end;
       {$ENDIF}
     end;


 procedure O_Smmi.Draw;
     var   bp: bool;
           xl,yl: int;
     begin
       if (not NET_ENABLED) then Exit;
       m_off(bp, xl,yl);
       ReInit(0,0,MaxX,MaxY);
       inherited Draw;
       m_on(bp, xl,yl)
     end;


 procedure O_Smmi.HandleEvent(var _Event: TEvent);
     begin
       inherited HandleEvent(_Event);
       if (_Event.What=evCommand) or (_Event.What=evBroadcast) then
          case _Event.Command of
            cmDefault : ;
            {$IFDEF DATA_WRITTEN_IN_APP}
              cmScrollEnable: if (AppScroll<>nil) then AppScroll^.set_scrollable
            {$ENDIF}
          end
     end;
