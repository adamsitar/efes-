{ ----------------
  okna
  ----------------
}

{
zmazanie okna, bez nastavenia prechadzajuceho vyplnoveho vzoru
}
procedure FillWin(x0,y0,x1,y1: int; bg: byte);
    begin
      SetFillStyle(SolidFill,bg);
      Bar(x0,y0,x1,y1);
    end; { FillWin }

{
zmazanie okna, nastavenie prechadzajuceho vypnoveho vzoru
}
procedure ClrWin(x0,y0,x1,y1: int; bg: byte);
    var   FillInfo: FillSettingsType;
    begin
     {$IFDEF BGI}
       GetFillSettings(FillInfo);
       SetFillStyle(SolidFill,bg);
     {$ENDIF}
     {$IFDEF SPEA}
      SPcolor(bg);
     {$ENDIF}
      Bar(x0,y0,x1,y1);
     {$IFDEF BGI}
       SetFillStyle(FillInfo.Pattern,FillInfo.Color)
     {$ENDIF}
    end; { ClrWin }

{
vyfarbi okno ako Norton 7.0
}
procedure window(Xl,Yl,Xh,Yh: int; shdx,shdy, RectOff, Bg,Ph: byte);
    begin
      FillWin(Xl,Yl,Xh,Yh,Bg);
      SetColor(Ph);
      Rectangle(Xl+RectOff,Yl+RectOff,Xh-RectOff,Yh-RectOff);
    end; { window }


{ ----------------
  buttony
  ---------------- }
{
  farby sa zadavaju ako pre OFF
}
procedure on_off(x0,y0,x1,y1: int; b1,b2, thick: byte; on: TbtStat);
    var   b: byte;
    begin
     {$IFDEF EGAVGA}
       b1:= black; b2:= lightgray;
     {$ENDIF}
      if bool(ord(on)) then begin b:= b1; b1:= b2; b2:= b end;
      SetColor(b1);
      Line(x0,y1,x1,y1);
      Line(x1,y0,x1,y1);
      if (thick <> btSmall) then begin
         Line(x0+1,y1-1,x1-1,y1-1);
         Line(x1-1,y0+1,x1-1,y1-1);
         if (thick = btLarge) then begin
            Line(x0+2,y1-2,x1-2,y1-2);
            Line(x1-2,y0+2,x1-2,y1-2)
         end
      end;
      SetColor(b2);
      Line(x0,y0,x1,y0);
      Line(x0,y0,x0,y1);
      if (thick <> btSmall) then begin
         Line(x0+1,y0+1,x1-1,y0+1);
         Line(x0+1,y0+1,x0+1,y1-1);
         if (thick = btLarge) then begin
            Line(x0+2,y0+2,x1-2,y0+2);
            Line(x0+2,y0+2,x0+2,y1-2)
        end
      end
    end; { on_off }


procedure button(x0,y0,x1,y1: int; bk, thick: byte; on: TbtStat);
    begin
     {$IFDEF EGAVGA}
       FillWin(x0+1,y0+1,x1-1,y1-1,darkgray);
       if bk+clBUTTON_DARK<0 then bk:= clBUTTON_COLOR;
       on_off(x0,y0,x1,y1,black,lightgray,thick,on)
     {$ELSE}
       FillWin(x0+1,y0+1,x1-1,y1-1,bk);
       if bk+clBUTTON_DARK<0 then bk:= clBUTTON_COLOR;
       on_off(x0,y0,x1,y1,bk+clBUTTON_DARK,bk+clBUTTON_LIGHT,thick,on)
     {$ENDIF}
    end; { Button }


{
  najsamvacsi button
}
const BWposun = 5;
      bwDLZKA = 11;
      bwSIRKA = 7;

procedure ButtonWindow(x0,y0,x1,y1: int; bk, thick: byte);
    var   l,d: byte;
    begin
      button(x0,y0,x1,y1, bk, thick, btOFF);
     {$IFDEF EGAVGA}
      bk:= darkgray;
      d:= black;
      l:= lightgray;
     {$ELSE}
      d:= bk+clBUTTON_DARK;
      l:= bk+clBUTTON_LIGHT;
     {$ENDIF}
      { UPPER LEFT }
      _angle(x0+bwPOSUN,y0+bwDLZKA,x0+bwSIRKA,y0+bwDLZKA,x0+bwSIRKA,y0+bwSIRKA,d);
      _angle(x0+bwSIRKA,y0+bwSIRKA,x0+bwDLZKA,y0+bwSIRKA,x0+bwDLZKA,y0+bwPOSUN,d);
      _angle(x0+bwPOSUN,y0+bwDLZKA,x0+bwPOSUN,y0+bwPOSUN,x0+bwDLZKA,y0+bwPOSUN,l);
      { BOTTOM LEFT }
      _angle(x0+bwPOSUN,y1-bwPOSUN,x0+bwDLZKA,y1-bwPOSUN,x0+bwDLZKA,y1-bwSIRKA,d);
      line(x0+bwSIRKA,y1-bwSIRKA,x0+bwSIRKA,y1-bwDLZKA);
      _angle(x0+bwPOSUN,y1-bwPOSUN,x0+bwPOSUN,y1-bwDLZKA,x0+bwSIRKA,y1-bwDLZKA,l);
      line(x0+bwSIRKA,y1-bwSIRKA,x0+bwDLZKA,y1-bwSIRKA);
      { BOTTOM RIGHT }
      _angle(x1-bwDLZKA,y1-bwPOSUN,x1-bwPOSUN,y1-bwPOSUN,x1-bwPOSUN,y1-bwDLZKA,d);
      _angle(x1-bwPOSUN,y1-bwDLZKA,x1-bwSIRKA,y1-bwDLZKA,x1-bwSIRKA,y1-bwSIRKA,l);
      _angle(x1-bwSIRKA,y1-bwSIRKA,x1-bwDLZKA,y1-bwSIRKA,x1-bwDLZKA,y1-6,l);
      { UPPER RIGHT  }
      _angle(x1-bwPOSUN,y0+bwPOSUN,x1-bwPOSUN,y0+bwDLZKA,x1-bwSIRKA,y0+bwDLZKA,d);
      line(x1-bwSIRKA,y0+bwSIRKA,x1-bwDLZKA,y0+bwSIRKA);
      _angle(x1-bwPOSUN,y0+bwPOSUN,x1-bwDLZKA,y0+bwPOSUN,x1-bwDLZKA,y0+bwSIRKA,l);
      line(x1-bwSIRKA,y0+bwSIRKA,x1-bwSIRKA,y0+bwDLZKA);
    end; { ButtonWindow }


procedure InfoWin(nadpis,veta: string; dyv1,dyv2: int; cl,bk: byte);
    var   mdx, dx,dy, dxt, x0,y0, x1,y1 : int;
          bp : bool; xl,yl : int;
    begin
      m_off(bp, xl,yl);

      mdx:= MaxX-btcdXY.x1-btcdXY.x0;
      dx := Minimum(15 + length(veta) * dx_ch + 15,mdx);
      dy := 27 + dyv1 + 10 + dyv2 + 10;
      x0 := btcdXY.x0 + Math.Centruj(mdx,dx);
      y0 := btcdXY.y0 + Math.Centruj(MaxY-btcdXY.y1-btcdXY.y0,dy);
      x1 := x0+dx;
      y1 := y0+dy;
      dxt:= abs(x1-x0-(20 + (length(nadpis) * dx_ch))) div 2;
      OpenWin(x0,y0,x1,y1, Xtien,Ytien, true);
      ButtonWindow(x0,y0,x1,y1, bk, btNorm);
      Button(x0+dxt,y0+6,x1-dxt,y0+18, clBUTTON_COLOR-1, btSmall,btON);
      SetTextStyle(DefaultFont, HorizDir, 1);
      WriteStr(x0+dxt+10+dx_ed,y0+9+dy_ed,nadpis, clGRd,clBUTTON_COLOR-1);
      setcolor(cl);
      WriteStr(x0+15+dx_ed,y0+27+dyv1+dy_ed,veta, cl,bk);

      m_on(bp, xl,yl);

      {$IFDEF ARCHIVE_PROGRAM_ERR}
       _write_err_log(veta);
      {$ENDIF}
    end;


procedure InfoCakaj(nadpis,veta: string);
    begin
      if InGraphMode then
         begin
          {m_set_shape(HODINY);}
          InfoWin(nadpis,veta, 0,0, clGRe,clBUTTON_COLOR)
         end
      {else write(veta)}
    end;

procedure InfoCakaj_zatvor;
    begin
      if InGraphMode then
         begin
           CloseWin;
           {m_restore_shape}
         end
      {else writeln(' Done.')}
    end;

