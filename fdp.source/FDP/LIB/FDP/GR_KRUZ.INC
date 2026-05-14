{ -----------------
   Kruznica
  -----------------
}

procedure TKruz.readGrOb(var _InF: file);
    var   Zs,Zd : TZdZs;
          res   : word;
    begin
      inherited readGrOb(_InF);
      BlockRead(_InF,Zd,Sizeof(TZdZs),res);
      BlockRead(_InF,Zs,Sizeof(TZdZs),res);
      BlockRead(_InF,R,Sizeof(longint),res);
      ZdZs_xy(Zd,Zs, stred.X,stred.Y)
    end; { Init }


procedure TKruz.DefineGrOb(p: pointer);
    begin
      prior:= PUserKruz(p)^.prior;
      farba:= PUserKruz(p)^.farba;
      typc := PUserKruz(p)^.typc;

      Stred.X:= PUserKruz(p)^.X;
      Stred.Y:= PUserKruz(p)^.Y;
      R      := PUserKruz(p)^.R
    end;


function  TKruz.is_in(_zd,_zs: TZdZs): bool;
  var     B : TGBod;
  begin
    ZdZs_xy(_zd,_zs, B.X,B.Y);
    is_in:= vzdialenost (B.x,B.y,stred.x,stred.y)<=r
  end;

{ vrati true, ak su oba body vo vnutri, alebo ich spojnica pretina kruznicu
}
function  TKruz.is_cut(zdA,zsA,zdB,zsB: TZdZs;
                       var in1,in2, is1,is2: bool;
                       var zd1,zs1, zd2,zs2: TZdZs
                      ): bool;

   var    A,B,_1,_2: TGBod;
          isp1,isp2 : bool;
          bres: bool;
   begin
     is_cut:= TGrOb.is_cut(zdA,zsA,zdB,zsB, in1,in2,is1,is2, zd1,zs1,zd2,zs2);
     zdzs_xy(zdA,zsA, A.x,A.y);
     zdzs_xy(zdB,zsB, B.x,B.y);

     bres:= priesecnik_usecky_s_kruznicou
             (A.x,A.y, B.x,B.y,
              stred.x,stred.y,r,
              in1,in2,isp1,isp2,
              _1.x,_1.y, _2.x,_2.y
             );

     if bres then
        begin
          xy_zdzs(_1.x,_1.y, zd1,zs1);
          xy_zdzs(_2.x,_2.y, zd2,zs2);
        end
     else TGrOb.is_cut(zdA,zsA,zdB,zsB, in1,in2,is1,is2, zd1,zs1,zd2,zs2);

     is_cut:= bres;
   end;


{$IFDEF DRAW}
   procedure TKruz.mapa_draw;
      var    Xs,Xr,Ys,Yr : long;
      begin
        _set_KrVys_par(stred,r, Xs,Ys,Xr,Yr);
        Ellipse(Xs,Ys,0,360,Xr,Yr)
      end;

  procedure TKruz.mapa_fill;
     var    Xs,Xr,Ys,Yr : long;
     begin
       _set_KrVys_par(stred,r, Xs,Ys,Xr,Yr);
       PieSlice(Xs,Ys,0,360,Xr)
     end;
{$ENDIF}



{ -----------------
   Kruznica fill
  -----------------
}

procedure TFillKruz.readGrOb(var _InF: file);
    begin
      inherited readGrOb(_InF);
      fill:= _fill_
    end;
