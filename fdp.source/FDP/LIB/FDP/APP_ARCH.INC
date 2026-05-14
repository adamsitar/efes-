procedure TApp.ReInit(x,y,dx,dy: int);
    begin
      XY(0,0,MaxX,MaxY);
      if BarMenu<>nil then BarMenu^.Reinit(0,0,MaxX,MaxY);
      set_btmdXY(btmdXY.x0,btmdXY.y0,btmdXY.x1,btmdXY.y1);
      if AppGUI<>nil then AppGUI^.Reinit(0,0,MaxX,MaxY);
    end;


procedure TApp.Refresh;
    begin
      set_RGBpallete;
      m_reinit_shape;
      ClearDevice;
      if BarMenu<>nil then BarMenu^.Draw; { umyselna redundancia, menu sa vykresli prve }
      Draw;
    end;



procedure TApp.init_LOGO(_LOGO: pointer);
    var   GM: TGraphMode;
          _MaxX,_MaxY: int;
    begin
     {$IFNDEF DEBUG}
      if _LOGO<>nil then
         begin
           {$IFDEF BGI}
             _MaxX:= MaxX; _MaxY:= MaxY; GM:= GraphMode;
             TProc(_LOGO);
             GraphMode:= GM; MaxX:= _MaxX; MaxY:= _MaxY
           {$ENDIF}
         end
     {$ENDIF}
    end;

procedure TApp.done_LOGO;
    begin
     {$IFNDEF DEBUG} {$IFDEF BGI}
        set_GrMode(GraphMode);
       {BarMenu^.reinit}
     {$ENDIF} {$ENDIF}
    end;



procedure TApp.set_btmdXY(dx0,dy0,dx1,dy1: int);
    begin
      set_region(dx0,dy0,dx1,dy1, btmdXY);
      if (BarMenu<>nil) and (btmdXY.y0=0) then btmdXY.y0:= BarMenu^.y1+3
    end;


procedure TApp.writeln (s: string; cl: byte; ident: string; is_utc: bool);
    begin
      writeln_(@s[1], length(s), cl, ident, is_utc, false)
    end;


procedure TApp.writeln_(pb: pbytes; size: int; cl: byte; ident: string; is_utc, is_NL: bool);
    const dx = 5;
          dy = 5;
    var   rdk,poc, riadkov, stlpcov, medzera, x,y, i,j,k : int;
          textik,utc : string;
    begin
     { vypis do okna s rozmermi x0,y0,x1,y1 - btmdXY }
      if (OpenWins>0) or (not WRITELN_FLOW) then Exit;

      medzera := 3;
      stlpcov := (x1 - btmdXY.x1 - x0 - btmdXY.x0 - 2*dx) div Maximum(1,TextWidth('W'));
      riadkov := (y1 - btmdXY.y1 - y0 - btmdXY.y0 - dy) div (Maximum(1,TextHeight('H'))+medzera);

      if is_utc then utc:= TimeToStr2(hour,min,sec,':','ú')+' ' else utc:= '';

      x:= x0+btmdXY.x0 + dx;
      i:= 0; rdk:= 1; poc:= get_str_items(pchars(pb),size,[#13,#10]);
      while (i<size) and (rdk<=poc) do
        begin
          if is_NL then
             begin
               textik:= get_str(pchars(pb),size,rdk,[#13,#10],sizeof(textik)-1);
               if rdk=1 then textik:= utc+ident+textik
               else textik:= InsChar('',length(utc), ' ',0) + InsChar('',length(ident), ' ',0) + textik;
               inc(rdk)
             end
          else begin
                 k:= N(Minimum(Minimum(sizeof(textik)-1,stlpcov)-Length(utc+ident),size-i));
                 textik[0]:= chr(k);
                 Move(pb^[i],textik[1],k);
                 if i=0 then textik:= utc+ident+textik
                 else textik:= InsChar('',length(utc), ' ',0) + InsChar('',length(ident), ' ',0) + textik;
                 textik:= copy(textik,1,stlpcov);
                 k:= length(textik)-length(utc+ident);
                 inc(i,k)
               end;
          inc(riadok);
          if riadok > riadkov then
             begin
               ClrWin(x0+btmdXY.x0+dx,y0+btmdXY.y0+dy, x1-btmdXY.x1-dx,y1-btmdXY.y1, black);
               riadok:= 1
             end;
          y:= y0+btmdXY.y0 + dx + (TextHeight('H')+medzera)*(riadok-1);
          Write_(x,y,textik, cl)
        end
    end;
