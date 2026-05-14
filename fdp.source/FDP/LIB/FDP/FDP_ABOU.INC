procedure _about(x0,y0,x1,y1: int; p: pointer); far;
    var   x,y : int;
          di  : SearchRec;
          dt  : DateTime;
          s   : string;
          b   : bool;
    begin
      x:= x0 + (x1-x0) div 2;
      bgigraph.button(x0,y0,x1,y1,clBUTTON_COLOR+2,btSmall,btOFF);

      _lineh(x0+5,x1-5,y0+60,clBUTTON_COLOR);
      inc(x,dx_ed); inc(y0,dy_ed);

      {$IFDEF SPEA}SetBkColor(clBUTTON_COLOR+2);{$ENDIF}
      SetColor(clGRd);
      OutTextXY(x-length(titFDP+', '+titFOR)*4,y0+22,titFDP+', '+titFOR);
      s:= 'node: '+strpas(NODEname);
      OutTextXY(x-length(s)*4,y0+41,s);

      FindFirst(path_E+exe+'.exe',Archive,di);
      b:= DosError=0;
      ResetIOError;

      SetColor(clGRb);
      y0:= y0+80; if b then dec(y0,8);
      OutTextXY(x-length(titCR)*4,y0,titCR);

      y:= 20;
      {$IFNDEF CZ}
       OutTextXY(x-length(titTLFSK)*4, y0+y,   titTLFSK);
       OutTextXY(x-length(titEMLSK)*4, y0+y+10,titEMLSK);
       OutTextXY(x-length(titWWWSK)*4, y0+y+20,titWWWSK);
       inc(y,35);
      {$ENDIF}
      {$IFNDEF SK}
       OutTextXY(x-length(titTLFCZ)*4, y0+y,   titTLFCZ);
       OutTextXY(x-length(titEMLCZ)*4, y0+y+10,titEMLCZ);
       OutTextXY(x-length(titWWWCZ)*4, y0+y+20,titWWWCZ);
       inc(y,35);
      {$ENDIF}

      inc(y,5);

      if b then
         begin
           UnpackTime(di.Time,dt);
          {with dt do s:= DateToStr2(Day,Month,Year)+' '+TimeToStr(hour,min,':');}
           with dt do s:= DateToStr(Day,Month,Year,0,'')+' '+TimeToStr(hour,min,'');
          {$IFNDEF SPEA}
           SetTextStyle(SmallFont, HorizDir,4);
          {$ENDIF}
           OutTextXY(x-(length(s)+6)*2,y0+y,s);
          {$IFNDEF SPEA}
           SetTextStyle(DefaultFont, HorizDir,0)
          {$ENDIF}
         end;
    end;
