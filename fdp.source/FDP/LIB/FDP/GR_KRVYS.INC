{ -----------------
   Kruhovy vysek
  -----------------
}

procedure TKrVys.readGrOb(var _InF: file);
    var   Zs,Zd : TZdZs;
          res   : word;
    begin
      inherited readGrOb(_InF);
      BlockRead(_InF,Zd,Sizeof(TZdZs),res);
      BlockRead(_InF,Zs,Sizeof(TZdZs),res);
      BlockRead(_InF,R,Sizeof(longint),res);
      BlockRead(_InF,A21,Sizeof(word),res);
      BlockRead(_InF,A22,Sizeof(word),res);
      ZdZs_xy(Zd,Zs, stred.X,stred.Y)
    end;


{ urci, ci bod sa nachadza v suradniciach objektu
}
function  TKrVys.is_in_(x,y: real): bool;
   var    az, daz, d2221, p22,p21 : real;
   begin
     is_in_:= false;

     if vzdialenost (x,y,stred.x,stred.y)>r then Exit;

     x:= x - stred.x;
     y:= y - stred.y;

     if (-1.e-10<y) and (y<1.e-10) then
        begin
         { vypocet azimutu v rad }
          if      x<0. then az := 3*PI/2.
          else if x>0. then az := PI/2.
          else if x=0. then az := 0.
        end
     else begin
            if y<>0 then az:= arctan(x/y)
            else az:= arctan(x/1/999999999);
            if y<0. then      az := az+PI
            else if x<0. then az := az+(PI*2);
          end;

     az := (az/(2.*pi))*360;            { prepocet na stupne }

     p21:= a21; p22:= a22;              { kvoli konverzii word na real        }
     d2221:= p22-p21;                   { pootocenie do pociatku sur sustavy  }
     if d2221<0. then d2221:= d2221+360;

     daz:= p22-az;                      { pootocenie do pociatku sur sustavy }
     if daz<0. then daz:= daz+360;

     is_in_:= (d2221-daz)>=0.
   end;

function  TKrVys.is_in(_zd,_zs: TZdZs): bool;
   var    B : TGBod;
   begin
     zdzs_xy(_zd,_zs, B.x,B.y);
     is_in:= is_in_(B.x,B.y)
   end;


function TKrVys.is_cut(zdA,zsA,zdB,zsB: TZdZs;
                       var in1,in2, is1,is2: bool;
                       var zd1,zs1, zd2,zs2: TZdZs
                      ): bool;

   var    A,B,_1,_2 : TGBod;
          bres : bool;
   begin
     is_cut:= TGrOb.is_cut(zdA,zsA,zdB,zsB, in1,in2,is1,is2, zd1,zs1,zd2,zs2);
     zdzs_xy(zdA,zsA, A.x,A.y);
     zdzs_xy(zdB,zsB, B.x,B.y);

     bres:= priesecnik_usecky_s_kruznicou
                (A.x,A.y, B.x,B.y,
                 stred.x,stred.y,r,
                 in1,in2,is1,is2,
                 _1.x,_1.y,_2.x,_2.y
                );

     if bres then
        begin
          in1 := in1 and is_in_(A.x,A.y);
          in2 := in2 and is_in_(B.x,B.y);
          is1 := is1 and is_in_(_1.x,_1.y);
          is2 := is2 and is_in_(_2.x,_2.y);
          bres:= in1 or in2 or is1 or is2
        end;

     if bres then
        begin
          xy_zdzs(_1.x,_1.y, zd1,zs1);
          xy_zdzs(_2.x,_2.y, zd2,zs2);
        end
     else TGrOb.is_cut(zdA,zsA,zdB,zsB, in1,in2,is1,is2, zd1,zs1,zd2,zs2);

     is_cut:= bres
   end;


{$IFDEF DRAW}
  procedure _set_KrVys_par(stred: TGBod; r: long; var Xs,Ys,Xr,Yr: long);
      var    PB  : TGBod;
      begin
        BodXY(@stred, Xs,Ys);
        PB.X:= r+stred.X;
        PB.Y:= r+stred.Y;
        BodXY(@PB, Xr,Yr);
        Xr:= abs(Xr-Xs);
        Yr:= abs(Yr-Ys)
      end;

  procedure TKrVys.mapa_draw;
     var    Xs,Xr,Ys,Yr : long;
     begin
       _set_KrVys_par(stred,r, Xs,Ys,Xr,Yr);
       Ellipse(Xs,Ys,a21,a22,Xr,Yr)
     end;

  procedure TKrVys.mapa_fill;
     var    Xs,Xr,Ys,Yr : long;
     begin
       _set_KrVys_par(stred,r, Xs,Ys,Xr,Yr);
       PieSlice(Xs,Ys,A21,A22,Xr)
     end;
{$ENDIF}


{ --------------------
   Kruhovy vysek fill
  --------------------
}
procedure TFillKrVys.readGrOb(var _InF: file);
    begin
      inherited readGrOb(_InF);
      fill:= _fill_
    end;

