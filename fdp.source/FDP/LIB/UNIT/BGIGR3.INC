{ ----------------
  ikony
  ---------------- }
{
nakresli kvacku
}
procedure icYes_(x,y: int; cl: byte);
    { const arYes: array[0..1,0..17] of int =
          ((1,6, 2,7, 3,8, 4,8, 5,8, 6,7, 7,6, 8,4, 8,1),
           (2,7, 2,6, 3,7, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0)); }
    const arYes: array[0..29] of int =
          (1,5, 1,6,  2,6, 2,7, 3,7, 3,8, 4,8, 5,7, 5,6, 6,5, 6,4, 7,3, 7,2, 8,1, 8,0);
    begin
      _drawpoly(x,y,cl,@arYes[0],15);
      {
      _drawpoly(x,y,cl,@arYes[0,0],9);
      _drawpoly(x,y,cl,@arYes[1,0],3)
      }
     end; { icYes }

{
nakresli kvacku
}
procedure icYes(x,y: int);
    begin
      icYes_(x,y, cyan)
    end; { icYes }

procedure icNo_(x,y: int; cl: byte);
    const arNo: array[0..1,0..15] of int =
          (( 5,5, 5,6, 6,7, 6,8, 7,9, 8,10, 9,11, 11,11),
           ( 4,10, 5,11, 6,10, 7,9, 8,8, 10,4, 10,3, 0,0));
    begin
      _drawpoly(x,y,cl,@arNo[0,0],8);
      _drawpoly(x,y,cl,@arNo[1,0],7)
    end; { icNo }

{
nakresli krizik
}
procedure icNo(x,y: int);
    begin
      icNo_(x,y, red);
    end; { icNo }

{
nakresli sipku
}
procedure icMove(x,y: int);
    const arMove: array[0..19] of int =
          ( 4,5, 6,3, 6,7, 4,5, 8,5, 9,6, 10,7, 10,9, 9,10, 7,11{, 3,11});
    begin
      _drawpoly(x,y,cyan,@arMove,10);
    end; { icNo }


procedure icList(x,y: int);
    const ar: array[0..7] of int = (2,5, 2,7, 2,5, 2,6);
    var   i: int;
    begin
      ClrWin(x,y,x+10,y+10,clGRe);
      setcolor(clGR5); rectangle(x,y,x+10,y+10);
      setcolor(clGR2); i:= 0;
      while i<7 do begin
         line(x+ar[i],y+2+i,x+ar[i+1],y+2+i);
         inc(i,2)
      end;
     end; { icList }

{
nakresli sipku
}
procedure icArrowUp(x,y: int; on: TbtStat);
    const arUp: array[1..8] of int =  (4,1, 0,-3, -4,1, 4,1); {5,11}
          dx =   3;
          dy =   3;
    var   sh : array[0..1] of byte;
          i  : int;
    begin
      Dec(y,2);         { aby spodna hrana bola na urcenej rovine y }
      setcolor(clARR_COLOR);
      sh[0]:= clARR_DARK;
      sh[1]:= clARR_LIGHT;
      _fillpoly(x,y,clARR_COLOR, @arUp,4);
      setcolor(sh[ord(on)]);
      line(x-dx-4,y+2,x+dx+4,y+2);
      for i:= 1 to 2 do line(x+dx+ i shl 1,y+i,x,y-dy-i);
      setcolor(sh[ord(not bool(on))]);
      for i:= 1 to 2 do line(x-dx- i shl 1,y+i,x,y-dy-i)
    end;

procedure icArrowDown(x,y: int; on: TbtStat);
    const arDown: array[1..8] of int = (4,-1, 0,3, -4,-1, 4,-1);
          dx =   3;
          dy =   3;
    var   sh  : array[0..1] of byte;
          i   : int;
    begin
      Inc(y,2);         { aby spodna hrana bola na urcenej rovine y }
      setcolor(clARR_COLOR);
      sh[1]:= clARR_DARK;
      sh[0]:= clARR_LIGHT;
      _fillpoly(x,y,clARR_COLOR, @arDown,4);
      setcolor(sh[ord(on)]);
      line(x-dx-4,y-2,x+dx+4,y-2);
      setcolor(sh[ord(not bool(on))]);
      for i:= 1 to 2 do line(x+dx+ i shl 1,y-i,x,y+dy+i);
      for i:= 1 to 2 do line(x-dx- i shl 1,y-i,x,y+dy+i)
    end;

