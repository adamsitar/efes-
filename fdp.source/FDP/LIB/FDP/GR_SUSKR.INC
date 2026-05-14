{ -----------------
   Sustava kruznic
  -----------------
}

procedure TSusKruz.readGrOb(var _InF: file);
    var   Zs,Zd : TZdZs;
          res   : word;
    begin
      inherited readGrOb(_InF);
      BlockRead(_InF,Zd,Sizeof(TZdZs),res);
      BlockRead(_InF,Zs,Sizeof(TZdZs),res);
      BlockRead(_InF,delR,Sizeof(longint),res);
      BlockRead(_InF,N,Sizeof(word),res);
      ZdZs_xy(Zd,Zs, stred.X,stred.Y)
    end;


{$IFDEF DRAW}
   procedure TSusKruz.Draw;
       var   Xs,Ys,Xr,Yr : long;
             _poc : int;
             PB   : TGBod;
       begin
         BodXY(@stred, Xs,Ys);
         for _poc := 1 to N do
           begin
             PB.X:= delR*_poc;
             PB.Y:= PB.X;
             PB.X:= PB.X + stred.X;
             PB.Y:= PB.Y + stred.y;
             BodXY(@PB, Xr,Yr);
             Xr:= abs(Xr-Xs);
             Yr:= abs(Yr-Ys);
             Ellipse(Xs,Ys,0,360,Xr,Yr)
           end;
       end;
{$ENDIF}
