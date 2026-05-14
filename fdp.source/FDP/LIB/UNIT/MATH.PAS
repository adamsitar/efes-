(*-------------------------------------------------------------------*)
(* Niektore sluzby - 1.0                                             *)
(* 1993                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}


unit Math;


interface


     uses  TypeDef;


     const inInt = 0;    { Pre Interval:                    }
           ofInt = 1;    {               povolenie pretiect }


     function  Prev(Val, maxValue: long): long;
     function  Next(Val, maxValue: long): long;

     function  Limit(Val, Lo,Hi: long; Pretec: byte): long;
     function  N(Val: long): word;
     function  aspon1(Val: long): word;
     function  Maximum(Val1,Val2: long): long;
     function  Minimum(Val1,Val2: long): long;
     function  Priemer(Val1,Val2: long): long;
     function  Centruj(Val1,Val2: long): long;
     function  Zaokruhli(val: real; na: long): long;
     function  Pocet(val,na: long): long;
     function  Znamienko(val: real): real;

     {procedure Swap(var v1,v2: long);}

     function  inRectangle(x,y, x0,y0,x1,y1 : int): bool;
     function  inRange    (val, lo,hi: real): bool;
     function  inRadius   (x,y, x0,y0,radius: real): bool;

     function  vzdialenost (x1,y1, x2,y2: real): real;
     procedure azimut (az,ra: real; var x,y: real);

     function  priesecnik_usecky_s_kruznicou
                 ( x1,y1, x2,y2: real;
                   xs,ys,rs: real;

                   var in1r, in2r: bool;
                   var is1p, is2p: bool;      { pretina   }
                   var x1p,y1p,x2p,y2p : real
                 ): bool;

     function  _div(delenec,delitel: real): longint;
     function  _mod(delenec,delitel: real): real;

     function  RMax(Val1,Val2: real): real;
     function  RMin(Val1,Val2: real): real;
     {function  RMod(Val: real): real;}
     function  RPrienik (D0z,D0k, D1z,D1k: real): bool;

     function  _10_X (cis,x: long): long;
     function  _X_10 (cis,x: long): long;


     function  _test_na (var pre: bool; p_pre: pbool; na: bool): bool;


implementation

{
 Vrati predchazajucu hodnotu Limitu pre kruhovy buffer
}
function Prev(Val, maxValue: long): long;
   begin
     if maxValue=0 then Exit;
     Prev:= (Val - 1 + maxValue) mod maxValue;
   end;

{
 Vrati nasledujucu hodnotu Limitu pre kruhovy buffer
}
function Next(Val, maxValue: long): long;
   begin
     if maxValue=0 then Exit;
     Next:= (Val + 1) mod maxValue;
   end;

{
 Nastavi Val do[Lo..Hi], ak Pretec<>0 then moze prejst na opacnu stranu
}
function Limit(Val, Lo,Hi: long; Pretec: byte): long;
    begin
     if (Val>=Lo) and (Val<=Hi) then Limit:= Val
     else if Val<Lo then
              if bool(Pretec) then Limit:= Hi
              else Limit:= Lo
         else if bool(Pretec) then Limit:= Lo
              else Limit:= Hi
    end; { Limit }

{
 Vrati prirodzene cislo
}
function N(Val: long): word;
   begin
    if Val<=0 then N:= 0 else N:= trunc(Val)
   end; { N }

function aspon1(Val: long): word;
   begin
    if Val<=0 then aspon1:= 1 else aspon1:= trunc(Val)
   end; { N }


function Maximum(Val1,Val2: long): long;
   begin
     if Val1>Val2 then Maximum:= Val1
     else Maximum:= Val2
   end; { Maximum }

function Minimum(Val1,Val2: long): long;
   begin
     if Val1<Val2 then Minimum:= Val1
     else Minimum:= Val2
   end; { Min }

function RMax(Val1,Val2: real): real;
   begin
     if Val1>Val2 then RMax:= Val1
     else RMax:= Val2
   end;

function RMin(Val1,Val2: real): real;
   begin
     if Val1<Val2 then RMin:= Val1
     else RMin:= Val2
   end; { Min }


function RPrienik (D0z,D0k, D1z,D1k: real): bool;
   begin
     RPrienik:=
            inRange(D1z, D0z,D0k)
         or inRange(D1k, D0z,D0k)
         or ((D1z<=D0z) and (D1k>=D0k))
         or ((D1z>=D0z) and (D1k<=D0k))
   end;

{function RMod(val: real; modr: real): real;
   var   r: real;
   begin
     r:= val;
     while r>modr then r:= r-modr;
     RMod
   end;  }


function Priemer(Val1,Val2: long): long;
   begin
     Priemer:= (Val1+Val2) shr 1
   end; { Priemer }

{
vystredi mensiu hodnotu do vacsej, vrati posun
}
function Centruj(Val1,Val2: long): long;
   begin
     Centruj:= Abs(Val1-Val2) shr 1
   end; { Priemer }

function Zaokruhli(val: real; na: long): long;
   var   val2, zv: real;
   begin
     if na=0 then na:= 1;
     val2:= trunc(val/na)*na;
     zv  := val - val2;
     if zv<(na/2) then zv:= 0 else zv:= na;
     val2:= val2+zv;
     Zaokruhli:= trunc(val2)
   end;

function Pocet(val,na: long): long;
   var   res: long;
   begin
     if na=0 then na:= 1;
     res:= val div na;
     if res < val / na then inc(res);
     Pocet:= res
   end;

function Znamienko(val: real): real;
   begin
     if val<0 then Znamienko:= -1
     else if val>0 then Znamienko:= 1
     else Znamienko:= 0
   end;

{procedure Swap(var v1,v2: long);
   var    v: long;
   begin
     v := v1;
     v1:= v2;
     v2:= v
   end;}


 function inRectangle(x,y, x0,y0,x1,y1 : int): bool;
    begin
      inRectangle:= (x>=x0) and (x<=x1) and (y>=y0) and (y<=y1)
    end; { inRectangle }

 function inRange(val, lo,hi: real): bool;
    begin
      if lo<hi then inRange:= (val>=lo) and (val<=hi)
      else inRange:= (val>=hi) and (val<=lo)
    end;

 function inRadius(x,y, x0,y0,radius: real): bool;
    begin
      inRadius:= (Sqrt(Sqr(x-x0) + Sqr(y-y0)) <= radius)
    end; { inRadius }


 function vzdialenost(x1,y1, x2,y2: real): real;
    begin
      vzdialenost:= sqrt(sqr(x1-x2)+sqr(y1-y2))
    end;

 procedure azimut(az,ra: real; var x,y: real);
    begin
      x:= ra*sin(az);
      y:= ra*cos(az)
    end;


 function  priesecnik_usecky_s_kruznicou

             ( x1,y1, x2,y2: real;
               xs,ys,rs: real;

               var in1r, in2r: bool;      { v objekte }
               var is1p, is2p: bool;      { pretina   }
               var x1p,y1p,x2p,y2p : real
             ): bool;

     var   x1s,x21,y1s,y21, a,b,c, d, t1,t2 : real;

     begin
       priesecnik_usecky_s_kruznicou:= false;

       in1r:= false; in2r:= false;
       is1p:= false; is2p:= false;
       x1p:= 0; y1p:= 0; x2p:= 0; y2p:= 0;

       x1s:= x1-xs;
       x21:= x2-x1;
       y1s:= y1-ys;
       y21:= y2-y1;

       a:= sqr(x21)+sqr(y21);
       b:= 2*(x21*x1s + y21*y1s);
       c:= sqr(x1s)+sqr(y1s)-sqr(rs);

       d:= sqr(b)-4*a*c;
       if (d<0) or (a=0) then Exit;

       t1:= (-b+sqrt(d))/(2*a);
       t2:= (-b-sqrt(d))/(2*a);

       in1r:= vzdialenost (x1,y1, xs,ys)<=rs; { t1 z <0,1> }
       is1p:= (t1>=0) and (t1<=1);
       if is1p then
          begin
            x1p:= x1+t1*(x2-x1);
            y1p:= y1+t1*(y2-y1);
          end;

       in2r:= vzdialenost (x2,y2, xs,ys)<=rs; { t2 z <0,1> }
       is2p:= (t2>=0) and (t2<=1);
       if is2p then
          begin
            x2p:= x1+t2*(x2-x1);
            y2p:= y1+t2*(y2-y1);
          end;

       priesecnik_usecky_s_kruznicou:= in1r or in2r or is1p or is2p
     end;


function _div(delenec,delitel: real): long;
   begin
     if delitel=0 then delitel:= 1;
     _div:= Trunc(delenec / delitel)
   end; { _div }


function _mod(delenec,delitel: real): real;
   begin
     if delitel=0 then delitel:= 1;
     _mod:= delenec - _div(delenec,delitel) * delitel;
   end; { _mod }


{ Len po deviatkovu sustavu, lebo netrasformujem na pismena
}
{ 11:2=5:2=2:2=1:2=0
       1   1   0   1
}
function _10_X(cis,x: long): long;
   var   res,del,pos,zv : long;
   begin
     res:= 0; pos:= 1;
     while cis<>0 do
       begin
         del:= cis div x;
         zv := cis - del*x;
         res:= res+pos*zv;
         pos:= 10*pos;
         cis:= del
       end;
     _10_X:= res
   end;

{ 1010 = 0*2(0)+1*2(1)+0*2(2)+1*2(3)
}
function _X_10(cis,x: long): long;
   var   res,del,exp,zv : long;
         i,ind : int;
   begin
     res:= 0; exp:= 1;
     while cis>0 do
       begin
         del:= cis mod 10;
         res:= res+del*exp;
         exp:= exp*x;
         cis:= (cis - del) div 10
       end;
     _X_10:= res
   end;


function _test_na (var pre: bool; p_pre: pbool; na: bool): bool;
   var   bres, _pre: bool;
   begin
     _pre:= get_pbool(p_pre,false);
     if na then bres:= (not pre) and _pre  { zmena na true  ? }
     else bres:= pre and (not _pre);       { zmena na false ? }
     if bres then pre:= _pre;              { nastavenie testovanej zmeny }
     _test_na:= bres
   end;


end. { Math }