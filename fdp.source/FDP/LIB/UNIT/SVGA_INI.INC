var SaveExit: pointer;

const crt_win = 'crt.win';

procedure DoneBGI;
    var   p : pointer;
          f : file;
          size : word;
          res  : int;
          OrigMode: int;
          X,Y : byte;
    begin
      CloseGraph;
      {$IFDEF BGI}
       uninstal_FONT;
      {$ENDIF}

      if FExists(crt_win)=0 then
         begin
           Assign(f,crt_win);
           Reset(f,1);
           BlockRead(f,OrigMode,sizeof(OrigMode), res);
           BlockRead(f,X,sizeof(X), res);
           BlockRead(f,Y,sizeof(Y), res);
           BlockRead(f,size,sizeof(size), res);
           GetMem(p,size);
           BlockRead(f,p^,size, res);
           TextMode(OrigMode);
           GotoXY(X,Y);
           WriteWin(p^);
           FreeMem(p,size);
           Close(f);
           DelFile(crt_win);
         end;

      if ExitMessage<>'' then writeln(ExitMessage);

      uninstal_LOGO;
      NormVideo;
      ExitProc:= SaveExit { Restore exit procedure address }
    end; { DoneBGI }


procedure InitBGI;
   var    GD,GM, EC : int;
          p : pointer;
          f : file;
          size : word;
          res,OrigMode : int;
          X,Y : byte;
   begin
     OrigMode:= LastMode;      { Remember original mode }
     X:= WhereX; Y:= WhereY;
     size:= WinSize;
     GetMem(p,size);
     ReadWin(p^);
     Assign(f,crt_win);
     Rewrite(f,1);
     BlockWrite(f,OrigMode,sizeof(OrigMode), res);
     BlockWrite(f,X,sizeof(X), res);
     BlockWrite(f,Y,sizeof(Y), res);
     BlockWrite(f,size,sizeof(size), res);
     BlockWrite(f,p^,size, res);
     Close(f);
     FreeMem(p,size);

    {$IFDEF BGI}
     instal_FONT;
    {$ENDIF}

    {$IFDEF EGAVGA}
     GD:= Detect;
     InitGraph(GD,GM, ' ');
     EC:= GraphResult;
     MaxX:= GetMaxXM; MaxY:= GetMaxY;
     set_RGBpallete;
    {$ELSE}
     {$IFDEF BGI}
       GD:= InstallUserDriver('BGI256', nil);
       EC:= GraphResult;
       if EC<>grOK then RunError('Graphics error: '+GraphErrorMsg(EC));
       GM:= ord(GraphMode);
     {$ENDIF}
     InitGraph(GD,GM,PathToDriver);
     init_RGB_FDP(ord(JAS));
     set_GrMode(GraphMode);
     set_RGBpallete;
    {$ENDIF}

     SetViewPort(0,0,MaxX,MaxY,true);
     SetTextJustify(LeftText,TopText);
     SetTextStyle(0, HorizDir, 1);

     SaveExit:= ExitProc;
     ExitProc:= @DoneBGI;

     Mouse.p_rozsviet := Rozsviet;
     Mouse.p_zhasni   := Zhasni;
     ROZSVIETENE:= set_absTime
   end; { InitBGI }
