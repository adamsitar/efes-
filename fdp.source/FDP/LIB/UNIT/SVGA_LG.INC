const  VER: pchar = nil;
       CR : pchar = nil;

procedure write_LOGO;
    var   x,ta: byte;
    begin
      writeln;
      ta:= textattr;
      if not (whereX in[0,1]) then writeln;
      x:= (80-(strlen(VER)+2+strlen(CR))) div 2;
      gotoxy(1,WhereY);
      textattr:= white; write(strpas(VER)+'   ');
      gotoxy(1+strlen(VER)+3,WhereY); textattr:= lightgray; writeln(strpas(CR));
      textattr:= ta;
      writeln;
     {$IFNDEF DEBUG} Delay(1000) {$ENDIF}
    end;

procedure instal_LOGO(_VER,_CR: string; _statup: bool);
    begin
      writeln;
      VER:= StrPasNew(_VER);
      CR := StrPasNew(_CR);
      {$IFDEF SPEA}
        write_LOGO
      {$ENDIF}
    end;

procedure uninstal_LOGO;
    begin
     {$IFNDEF SPEA}
       if not ((ErrorAddr<>nil) or ProgramError) then write_LOGO;
     {$ENDIF}
      StrDispose(VER);
      StrDispose(CR);
    end;
