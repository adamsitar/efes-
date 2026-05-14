function TApp.EndState(var _Event: TEvent): bool;
   begin
     EndState:= isCommand(_Event,cmQuit)
   end;


procedure TApp.Idle(var _Event: TEvent);
    begin
      if AppGui<>nil then AppGui^.Idle(_Event);
      {if Stack<>nil then ForEach(@_prekreslit,Stack,nil); -> o to sa stara AppGui }
    end;


procedure TApp.Run(var _Event: TEvent);
    begin
      done_LOGO;
      inherited Run(_Event)
    end;


procedure TApp.HandleEvent(var _Event: TEvent);
    begin
      inherited HandleEvent(_Event);

      case _Event.What of
        evCommand,evBroadcast :
          case _Event.Command of
            cmQUIT               : if confirm_exit then Exit
                                   else ClearEvent(_Event);

            cmConfigChanged      : begin
                                     distribute_app_config;
                                     Refresh;
                                     ClearEvent(_Event)
                                   end;

            cmRefresh            : begin
                                     IS_REFRESH:= true;
                                     Refresh;
                                     IS_REFRESH:= false;
                                     ClearEvent(_Event)
                                   end;

            cmMainMenuRedraw     : begin
                                     BarMenu^.Draw;
                                     ClearEvent(_Event)
                                   end;

            cmSERVER_STATUS      : begin
                                     SetCommand(_Event,cmMenuRedraw);
                                     inherited HandleEvent(_Event);
                                     ClearEvent(_Event)
                                   end
          end;

        evKeyDown :
          case _Event.Key of
            kbAltX               : SetCommand(Pending,cmQuit);
          end;

        evMouseClick :
          if bool (_Event.M.bt and mbRightButton) then SetCommand(_Event,cmCancel)

      end; { case }

    end;


{$IFDEF EXIT_PASSWORD}
  procedure TApp.set_password(pswd: string);
      begin
        StrDispose(exit_password);
        exit_password:= StrPasNew(pswd)
      end;
{$ENDIF}

function TApp.confirm_exit: bool;
   var   s : string;
   begin
     confirm_exit:= true;
     {$IFNDEF DEBUG}
       if (maxavail>minWinHeap) then
          {$IFDEF EXIT_PASSWORD}
            if formular_s(s,EXIT_PASSWORD_LENGTH,
                          'Enter an exit password : ',
                          nil,1,@setABCcs_,nil, 0,nil, true,false,false,nil
                         ) then
               confirm_exit:=    (s=strpas(exit_password))
                              or (s=EXIT_PASSWORD_ALES)
                              or (s=EXIT_PASSWORD_INST)
            else confirm_exit:= false
          {$ELSE}
            confirm_exit:= Ask2(msgWARNING,msgEXIT,'',White,clBUTTON_COLOR,waitASK)=ansAno
          {$ENDIF}
     {$ENDIF}
   end;



