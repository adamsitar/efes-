procedure show_cursor(x,y, dx,dy, dy_c0,dy_c1, indx,indy : int; ch: char; ins: bool; c,b: byte);
    var   bp : bool; xl,yl : int;
    begin
      m_off(bp, xl,yl);
      inc(x, indx*dx-1);
      inc(y, indy*dy);
      if ins then
         begin
           SetColor(c);
         { SetLineStyle(DottedLn, 0, NormWidth); }
           Line(x,y-dy_c0,   x+dx-1,y-dy_c0);
           Line(x,y+dy+dy_c1,x+dx-1,y+dy+dy_c1);
         end
      else begin
             FillWin(x,y-dy_c0,x+dx-1,y+dy+dy_c1, c);
             {$IFDEF SPEA}SetBkColor(c);{$ENDIF} SetColor(b);
             OutTextXY(x+1+dx_ed,y+dy_ed,ch)
           end;
      m_on(bp, xl,yl);
    end; { cursor }

procedure hide_cursor(x,y, dx,dy, dy_c0,dy_c1, indx,indy : int; ch: char; c,b: byte);
    var   bp : bool; xl,yl : int;
    begin
      m_off(bp, xl,yl);
      inc(x, indx*dx-1);
      inc(y, indy*dy);
      FillWin(x,y-dy_c0,x+dx-1,y+dy+dy_c1, b);
      {$IFDEF SPEA}SetBkColor(b);{$ENDIF} SetColor(c);
      OutTextXY(x+1+dx_ed,y+dy_ed,ch);
      m_on(bp, xl,yl);
    end; { cursor }

{
prepocet riadku a stlpca na graficke suradnice
}
function SetX(X: int): int;
   begin
     SetX:= (X-1)*dx_ch
   end; { SetX }

function SetY(Y: int): int;
   begin
     SetY:= (Y-1)*(dx_ch+2)
   end; { SetY }


procedure ClearStr (x,y: int; len: int; bg: byte);
    begin
      {$IFDEF BGI} FillWin(x-1,y,x+len*8,y+TextHeight('H'), bg); {$ENDIF}
    end;

procedure Write_ (x,y: int; S: string; cl: byte);
    begin
      SetColor(cl);
      OutTextXY(x,y,S)
    end; { Write }

procedure WriteStr(x,y: int; S: string; cl,bg: byte);
    begin
      SetTextJustify(LeftText,TopText);
      {$IFDEF BGI} FillWin(x-1,y,x+TextWidth(S)-1,y+TextHeight('H'), bg); {$ENDIF}
      {$IFDEF SPEA} SetBkColor(bg); {$ENDIF}
      SetColor(cl); OutTextXY(x,y,S)
    end; { WriteStr }


procedure WriteStrF (x,y: int; s: string; size: byte; cl,bg: byte);
    begin
      FillWin(x-1,y-1,x+(size shl 3)+1,y+(1 shl 3), bg);
      {$IFDEF SPEA} SetBkColor(bg); {$ENDIF} SetColor(cl);
      OutTextXY(x,y,s)
    end; { WriteStrF }



procedure WriteDStr(x,y: int; S: string; cl,sh,bg: byte);
    begin
      SetTextJustify(LeftText,TopText);
      {$IFDEF BGI} FillWin(x-2,y-2,x+TextWidth(S)+2,y+TextHeight('H')+3, bg); {$ENDIF}
      {$IFDEF SPEA} SetBkColor(bg); {$ENDIF}
      {$IFDEF BGI} Write_(x+1,y+4,S,sh); {$ENDIF}
      Write_(x,y+3,S,sh)
    end; { SGStr }

procedure WriteCentr(x0,x1,y0,y1: int; S: string; cl: byte);
    begin
      SetColor(cl);
     { SetTextStyle(DefaultFont, HorizDir, 1);
      SetTextJustify(LeftText,CenterText); }
      OutTextXY(x0+Centruj(x1-x0,Length(S) * dx_ch) + 1,(y1+y0+dy_bt) shr 1,S);
     { SetTextJustify(LeftText,TopText) }
    end; { WriteCentr }

procedure WriteInfo(x0,y0,x1,y1: int; info: string);
    var   s,s_ : string;
          dx,i: int;
          c: byte;
    begin
      if pos('~',info)<>0 then c:= cyan else c:= clINFO;
      {$IFDEF SPEA} c:= clGRe; {$ENDIF}   { kym nevyriesim zapis po znakoch }
      s_:= get_s_(info, '~',[]);
      info:= DelChar(info,['~']);
      dx  := {Min(Length(info) * dx_ch + 16,}MaxX-10-x0{)};
      if dx<Length(info) * dx_ch then
         begin
           info:= Copy(info,1,dx shr 3 - 4)+'...';
           s_  := Copy(s_  ,1,dx shr 3 - 4)
         end;
      button(x0,y0,x0+dx,y1, clBUTTON_COLOR , btSmall,btOFF);
      button(x0+dx+2,y0,MaxX,y1, clBUTTON_COLOR , btNorm,btOFF);
      SetTextJustify(LeftText,TopText);
      {$IFDEF SPEA} SetBkColor(clBUTTON_COLOR); {$ENDIF}
      Write_(x0+dx_ch,y0{$IFDEF BGI}+4{$ELSE}+11{$ENDIF}, info, c);
      {$IFDEF BGI}
        Write_(x0+dx_ch,y0{$IFDEF BGI}+4{$ELSE}+11{$ENDIF}, s_,   yellow)
      {$ENDIF}
    end;


function cut_text(s: string): string;
   var   t: string;
   begin
     t:= copy(s,1,(MaxX-btcdXY.x1-btcdXY.x0-50) div 10);
     if length(t)<length(s) then t:= t+'...';
     cut_text:= t
   end;


{
  clipping textu
}
 procedure WriteClippedText(x1,y1: int; s: string);
    {$IFDEF BGI}
      var   VP : ViewPortType;
            dx, x2,y2,p,k : int;
    {$ENDIF}
     begin
       {$IFDEF BGI}
         GetViewSettings(VP);
         x2:= x1+TextWidth (s);
         y2:= y1+TextHeight(s);
         dx:= TextWidth('W');
         if (y1<=0) or (y2>=VP.y2-VP.y1) then Exit;
         if (x1<=0) then
            begin
              p:= Abs(x1) div Maximum(1,dx);
              k:= N(length(s)-p);
              s:= Copy(s,p,k);
              x1:= x1+p*dx
            end;
         if (x2>=VP.x2-Vp.x1) then
            begin
              p:= (x2-(VP.x2-Vp.x1)) div Maximum(1,TextWidth('W'));
              s:= Copy(s,1,N(length(s)-p-1))
            end;
       {$ENDIF}
       if (x1>0) and (s<>'') then OutTextXY(x1,y1, s)
       {rectangle(x1,y1,x2,y2);}
     end;

