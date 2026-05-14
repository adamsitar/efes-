type  POPoint = ^TOPoint;
      TOPoint = object
        x0,y0 : real;

        constructor Init(x,y: real);
        destructor  Done; virtual;
      end;


type  PTOLine = ^TOLine;
      TOLine  = object(TOPoint)
        sx,sy : real;
        x1,y1 : real;
        t     : real;   { vektor pre prienik dvoch useciek }

        constructor Init         (x0a,y0a, x1a,y1a: real);

        function    obsahuje_bod (x,y: real): bool;
        function    vlavo_bod    (x,y: real): bool;
        function    vpravo_bod   (x,y: real): bool;
        function    pretina      (x0b,y0b, x1b,y1b: real; px,py: Preal): TPolohaGrObs;
      end;


type  PTArc = ^TArc;
      TArc  = object(TOPoint)
        t11,t12 : real;  { pre parametricke vyjadrenie kr. vseku }
        a21, a22: real;  { azimut v stupnoch }
        r       : real;  { polomer }

        constructor Init    (x,y, _r, _a21,_a22: real);
        function    pretina (x0b,y0b, x1b,y1b: real; px,py: Preal): TPolohaGrObs;
      end;

{ ----------------------
  Point
  ----------------------
}

constructor TOPoint.Init(x,y: real);
      begin
        x:= x0; y:= y0
      end;

destructor  TOPoint.Done;
      begin
      end;


{ ----------------------
  Line
  ----------------------
}

constructor TOLine.Init(x0a,y0a, x1a,y1a: real);
      begin
        x0:= x0a; y0:= y0a;
        x1:= x1a; y1:= y1a;
        sx:= x1 - x0;
        sy:= y1 - y0
      end;


function TOLine.obsahuje_bod(x,y: real): bool;
   begin
     obsahuje_bod:=     (abs((x-x0)*sy - (y-y0)*sx) < 0.00001)
                    and ((y-y0)*sy + (x-x0)*sx >= 0)
                    and ((y-sy-y0)*sy + (x-sx-x0)*sx <= 0)
   end;

function TOLine.vlavo_bod(x,y: real): bool;
  begin
    vlavo_bod:= (x-x0)*sy >= (y-y0)*sx
  end;

function TOLine.vpravo_bod(x,y: real): bool;
  begin
    vpravo_bod:= (x-x0)*sy < (y-y0)*sx
  end;

{
  2 .. totozne
  1 .. rovnobezne
  0 .. x
}
function TOLine.pretina(x0b,y0b, x1b,y1b: real; px,py: Preal): TPolohaGrObs;
   var   AB: TOLine;
         xp,yp, det, c1,c2,cct1,cct2: real;
   begin
     AB.Init(x0b,y0b, x1b,y1b);

     det:= sy*AB.sx-sx*AB.sy;
     c1:= AB.x0-x0;
     c2:= AB.y0-y0;
     cct1:= c2*AB.sx-c1*AB.sy;
     cct2:= c2*sx-c1*sy;

     if abs(det)<0.0001 then
       begin
         if abs(cct1)<0.0001 then pretina:= pgo_totozne  { totozne }
	 else pretina:= pgo_rovnobezne                   { rovnobezne }
       end
     else begin
           { pretinaju sa
           }
            if t=0 then t:= 999999999;
            t:= cct1/det;
            AB.t:= cct2/det;

            xp:= x0+t*sx;
            yp:= y0+t*sy;

            if px<>nil then real(px^):= xp;
            if py<>nil then real(py^):= yp;

           { pretinaju sa usecky alebo priamky ?
             ak sa pretinaju usecky, potom plati
              - ze ak je usecka jednou z uhlopriecok stvorca (jej plochy)
                a bod prieniku je v stvorcoch oboch useciek
              - alebo plati jednoducha podmienka < a >
           }
            if     inRange(xp,x0,x1) and inRange(xp,x0b,x1b)
               and inRange(yp,y0,y1) and inRange(yp,y0b,y1b)
                   then pretina:= pgo_prienik
            else pretina:= pgo_prienik_mimo
          end;

    AB.Done
  end;


{ ----------------------
  Arc
  ---------------------- }

constructor TArc.Init (x,y, _r, _a21,_a22: real);
      begin
        x0:= x; y0:= y;
        r:= _r; a21:= _a21; a22:= _a22; t11:= 0; t12:= 0
      end;


function TArc.pretina (x0b,y0b, x1b,y1b: real; px,py: Preal): TPolohaGrObs;
   var   xp,yp, A,B,C,det : real;
         ret : int;
         U   : TOLine;

   begin
     U.Init (x0b,y0b, x1b,y1b);

     A:= U.sx*U.sx + U.sy*U.sy;
     B:= 2*(U.x0*U.sx + U.y0*U.sy);
     C:= U.x0*U.x0 + U.y0*U.y0 - r*r;
     det:= B*B - 4*A*C;

     if (det<0) then pretina:= pgo_mimo { prechadza mimo kruznice }
     else begin
            ret:= 0; if A=0 then A:= 999999999;
            t11:= (-B+sqrt(det))/(2*A);
            t12:= (-B-sqrt(det))/(2*A);
            if    ((xp<x0b) or (x1b<xp) or (yp<y0b) or (y1b<yp))
               {or}
                  then pretina:= pgo_prienik_mimo
            else pretina:= pgo_prienik
          end;

     U.Done
   end;

