{ -----------------
   Stvorcova siet
  -----------------
}
procedure TStSiet.readGrOb(var _InF: file);
    var   Zs,Zd : TZdZs;
          res   : word;
    begin
      inherited readGrOb(_InF);
      BlockRead(_InF,Zd,Sizeof(TZdZs),res);
      BlockRead(_InF,Zs,Sizeof(TZdZs),res);
      BlockRead(_InF,delX,SizeOf(word),res);
      BlockRead(_InF,nX,SizeOf(word),res);
      BlockRead(_InF,delY,SizeOf(word),res);
      BlockRead(_InF,nY,SizeOf(word),res);
      ZdZs_xy(Zd,Zs, ldr.X,ldr.Y)
    end;

{$IFDEF DRAW}
   procedure TStSiet.Draw;
       var   PB    : TGBod;
             dX,dY : real;
             X,Y   : long;
             poc   : int;
       begin
         dX:= ldr.X + (nX*delX)*20.3819;
         for poc:= 0 to nY do
           begin
             PB.X:= ldr.X;
             PB.Y:= ldr.Y +(poc*delY)*30.69444;
             BodXY(@PB, X,Y);
             MoveTo(X,Y);
             PB.X:= dX;
             BodXY(@PB, X,Y);
             LineTo(X,Y)
           end;

         dY:= ldr.Y + (nY*delY)*30.69444;
         for poc:= 0 to nX do
           begin
             PB.X:= ldr.X +(poc*delX)*20.3819;
             PB.Y:= ldr.Y;
             BodXY(@PB, X,Y);
             MoveTo(X,Y);
             PB.Y:= dY;
             BodXY(@PB, X,Y);
             LineTo(X,Y)
           end
     end;
{$ENDIF}