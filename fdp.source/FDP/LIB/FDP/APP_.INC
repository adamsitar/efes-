constructor TApp.Init(_Owner: PGroup; _BarMenu,_LOGO: pointer; _VER,_CR: string);
      begin
        instal_LOGO(_VER,_CR, _LOGO=nil);
        InitBGI;
        {$IFDEF _MOUSE} InitMouse; {$ENDIF}
        m_cl;
        init_LOGO(_LOGO);
        inherited Init(_Owner, 0,0,MaxX,MaxY);
        ScreenSave:= false;

        if _BarMenu<>nil then
           begin
             BarMenu:= FBarMenu(_BarMenu);
             PushObject(Barmenu)
           end;
        riadok:= 0;
        set_btmdXY(btmdXY.x0,btmdXY.y0,btmdXY.x1,btmdXY.y1);

        MainApp:= @Self;
        AppGUI:= nil;
        {$IFDEF EXIT_PASSWORD}
          exit_password:= nil;
          {$IFNDEF DEBUG} set_password(EXIT_PASSWORD_FDP); {$ENDIF}
        {$ENDIF}
      end;

procedure TApp.InitApp;
    var   x,y: int;
    begin
      m_st;
      MainEnabled:= true
    end;

destructor TApp.Done;
     begin
       if @ACheckProcesses0<>nil then ACheckProcesses0:= nil;
       if @ACheckProcessesA<>nil then ACheckProcessesA:= nil;
       inherited Done;
       {$IFDEF EXIT_PASSWORD}
        strdispose(exit_password);
       {$ENDIF}
     end;
