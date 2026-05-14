function Vy_r(R_r: real): real;
   begin
     if krok=0 then krok:= 1;
     Vy_r:= R_r/krok
   end; { Vy_r }


procedure TMapa.Centr;
    begin
      Xvystred := cXvystred - dcXvystred;
      Yvystred := cYvystred - dcYvystred;
      Rozsah   := cRozsah
    end; { Centr }

procedure TMapa.Stred(XXstr,YYstr: real);
    begin
      Xvystred:= XXstr;
      Yvystred:= YYstr
    end; { Stred }


procedure TMapa.Point(X1z,Y1z: real);
    begin
      Txx:= trunc(0.5+(X1z-Xs2)* Kon2);
      Tyy:= trunc(0.5+(Y1z-Ys2)* Kon1) - dTyy;
      if Txx>5000 then Txx:= 5000
      else if Txx<-5000 then Txx:= - 5000;
      if Tyy>5000 then Tyy:= 5000
      else if Tyy<-5000 then Tyy:= - 5000;
      Tyy:= MaxY - Tyy
    end; { Point }

procedure TMapa.InvPoint(var X1z,Y1z: real);
    begin
      if Kon2=0 then Kon2:= 1;
      X1z:= (Txx/Kon2)+Xs2;
      if Kon1=0 then Kon1:= 1;
      Y1z:= (((MaxY-Tyy)+dTyy)/Kon1)+Ys2;
    end; { InvPoint }

procedure TMapa.InvPoint_(_Txx,_Tyy: real; var X1z,Y1z: real);
    begin
      if Kon2=0 then Kon2:= 1;
      X1z:= (_Txx/Kon2)+Xs2;
      if Kon1=0 then Kon1:= 1;
      Y1z:= (((MaxY-_Tyy)+dTyy)/Kon1)+Ys2;
    end; { _InvPoint }


{ -------------------------------------
  Zmeny mierky a stredu
  -------------------------------------
}

{function Vy_r(R_r: real): real;
   begin
     Vy_r:= R_r/krok
   end;  Vy_r }


procedure TMapa.Centruj;
    begin
      if not ({(p_mapy_en=nil) or (bool(p_mapy_en^))} PLANZET_MAPA or ZOBRAZ_MAPU) then Exit;
      Centr;
      Draw
    end;

procedure TMapa.Vystred;
    var   _Event: TEvent;
    begin
      if not ({(p_mapy_en=nil) or (bool(p_mapy_en^))} PLANZET_MAPA or ZOBRAZ_MAPU) then Exit;

     {$IFDEF LIS} CO_ROBIT:= robVYSTREDENIE; {$ENDIF}
      set_xy(integer((x1-x0) div 2),(y1-y0) div 2);
      hlpXXX:= hlpmnuMMI_MAPS_CENTRE;
      m_clip(x0,y0,x1,y1);
      m_set_shape(KRIZ);
      RunLocalFunc(_Event,tit_MAP_CENTR);
      m_restore_shape;
      m_clip(0,0,MaxX,MaxY);
      hlpXXX:= nil;
     {$IFDEF LIS} CO_ROBIT:= cmNil; {$ENDIF}
    end;
