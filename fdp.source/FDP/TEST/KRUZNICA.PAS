{$I comp.h}

uses typedef (*, _l4_def, body, {$I map_unit.h}*);


function priesecnik_usecky_s_kruznicou

            ( x1,y1, x2,y2: real;
              xs,ys,rs: real;
              var is1r, is2r: bool;
              var x1r,y1r,x2r,y2r : real
            ): bool;

   var   x1s,x21,y1s,y21, a,b,c, d, t1,t2 : real;

   begin
     is1r:= false; is2r:= false;
     x1r:= 0; y1r:= 0; x2r:= 0; y2r:= 0;
     priesecnik_usecky_s_kruznicou:= false;

     x1s:= x1-xs;
     x21:= x2-x1;
     y1s:= y1-ys;
     y21:= y2-y1;

     a:= sqr(x21)+sqr(y21);
     b:= 2*(x21*x1s + y21*y1s);
     c:= sqr(x1s)+sqr(y1s)-sqr(rs);

     d:= sqr(b)-4*a*c;
     if d<0 then Exit;

     t1:= (-b+sqrt(d))/(2*a);
     t2:= (-b-sqrt(d))/(2*a);

     if abs(t1)<=1 then
        begin
          is1r:= true;
          x1r:= x1+t1*(x2-x1);
          y1r:= y1+t1*(y2-y1);
        end;

     if abs(t2)<=1 then
        begin
          is2r:= true;
          x2r:= x1+t2*(x2-x1);
          y2r:= y1+t2*(y2-y1);
        end;

     priesecnik_usecky_s_kruznicou:= is2r or is2r
   end;


var is1r, is2r: bool;
    x1r,y1r,x2r,y2r : real;

begin
  priesecnik_usecky_s_kruznicou (-1,0, 1,1, 2,1,1, is1r, is2r, x1r,y1r,x2r,y2r);
  priesecnik_usecky_s_kruznicou (-1,0, 1,1, 2,2,1, is1r, is2r, x1r,y1r,x2r,y2r);
  priesecnik_usecky_s_kruznicou (-1,1, 1,1, 1,1,1, is1r, is2r, x1r,y1r,x2r,y2r);
  priesecnik_usecky_s_kruznicou (-1,1, 1,1, 1,1,1, is1r, is2r, x1r,y1r,x2r,y2r);
end.
