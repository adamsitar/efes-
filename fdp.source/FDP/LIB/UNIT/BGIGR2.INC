{ ------------------------------------------------
  rozsirenie zakladnych procedur Graphu
  ------------------------------------------------ }
{
  zvisla ciara s tienom
}
procedure _linev(x,y0,y1: int; bk: byte);
    begin
      setcolor({$IFDEF EGAVGA}black{$ELSE}bk+clBUTTON_DARK{$ENDIF});
      line(x,  y0,x  ,y1);
      setcolor({$IFDEF EGAVGA}lightgray{$ELSE}bk+clBUTTON_LIGHT{$ENDIF});
      line(x+1,y0,x+1,y1)
    end;

{
  vodorovna ciara s tienom
}
procedure _lineh(x0,x1,y: int; bk: byte);
    begin
      setcolor({$IFDEF EGAVGA}black{$ELSE}bk+clBUTTON_DARK{$ENDIF});
      line(x0,y,  x1,y);
      setcolor({$IFDEF EGAVGA}lightgray{$ELSE}bk+clBUTTON_LIGHT{$ENDIF});
      line(x0,y+1,x1,y+1)
    end;

{
  zvisla ciara s tienom
}
procedure _linevo(x,y0,y1: int; bk: byte);
    begin
      setcolor({$IFDEF EGAVGA}black{$ELSE}bk+clBUTTON_DARK{$ENDIF});
      line(x+1,y0,x+1,y1);
      setcolor({$IFDEF EGAVGA}lightgray{$ELSE}bk+clBUTTON_LIGHT{$ENDIF});
      line(x  ,y0,x  ,y1)
    end;

{
  vodorovna ciara s tienom
}
procedure _lineho(x0,x1,y: int; bk: byte);
    begin
      setcolor({$IFDEF EGAVGA}black{$ELSE}bk+clBUTTON_DARK{$ENDIF});
      line(x0,y+1,x1,y+1);
      setcolor({$IFDEF EGAVGA}lightgray{$ELSE}bk+clBUTTON_LIGHT{$ENDIF});
      line(x0,y  ,x1,y  )
    end;


{
  pravouholnik
}
procedure _angle(x0,y0,x1,y1,x2,y2: int; cl: byte);
    var   p: array[0..5] of int;
    begin
      p[0]:= x0; p[1]:= y0; p[2]:= x1; p[3]:= y1; p[4]:= x2; p[5]:= y2;
      SetColor(cl);
      DrawPoly(3,p)
    end;

{
  vykreslenie mnohouholnika relativne k suradniciam x,y
}
procedure _drawpoly(x,y: int; cl: byte; p: Pints; nmb: byte);
    var   pline  : array[0..maxPOLY-1] of int;
          i      : byte;
    begin
      i:= 0;
      while i<minimum(nmb*2-1,maxPOLY-2) do
        begin
          pline[i]  := p^[i]   + x;
          pline[i+1]:= p^[i+1] + y;
          Inc(i,2)
        end;
      SetColor(cl);
      DrawPoly(nmb,pline)
    end; { _drawpoly }

{
  vyplnenie mnohouholnika relativne k suradniciam x,y
}
procedure _fillpoly(x,y: int; bg: byte; p: Pints; nmb: byte);
    var   pline  : array[0..maxPOLY-1] of int;
          i      : byte;
    begin
      i:= 0;
      while i<minimum(nmb*2-1,maxPOLY-2) do
        begin
          pline[i]  := p^[i]   + x;
          pline[i+1]:= p^[i+1] + y;
          Inc(i,2)
        end;
      SetFillStyle(SolidFill,bg);
      FillPoly(nmb,pline)
    end; { _fillpoly }


procedure _set_typciary(_typ : byte ; _hr: byte);
    const ciara: array[0..8] of word = ($FFFF,$5555,$0101,$3333,$0F0F,$F00F,$6F6F,$E4E4,$F18F);
    begin
      SetLineStyle(UserBitLn, ciara[_typ], _hr);
    end;

