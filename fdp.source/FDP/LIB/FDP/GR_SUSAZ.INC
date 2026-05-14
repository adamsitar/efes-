{ ------------------
   Sustava azimutov
  ------------------
}

procedure TSusAzim.readGrOb(var _InF: file);
    var   Zs,Zd : TZdZs;
          res   : word;
    begin
      inherited readGrOb(_InF);
      BlockRead(_InF,Zd,Sizeof(TZdZs),res);
      BlockRead(_InF,Zs,Sizeof(TZdZs),res);
      BlockRead(_InF,R,Sizeof(longint),res);
      BlockRead(_InF,delA,Sizeof(word),res);
      ZdZs_xy(Zd,Zs, stred.X,stred.Y)
    end; { Init }


{$IFDEF DRAW}
   procedure TSusAzim.Draw;
       var   uhol, pom1, pom2 : real;
             Xs,Ys,Xr,Yr : long;
             PB : TGBod;
       begin
         uhol := 0;
         pom1 := delA*Pi/180;
         pom2 := 2*Pi;
         BodXY(@stred, Xs,Ys);
         repeat
           MoveTo(Xs,Ys);
           PB.X := stred.X + R*sin(uhol);
           PB.Y := stred.Y + R*cos(uhol);
           BodXY(@PB, Xr,Yr);
           LineTo(Xr,Yr);
           uhol := uhol + pom1
         until uhol > pom2
       end;
{$ENDIF}
