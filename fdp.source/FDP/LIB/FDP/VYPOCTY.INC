{
  true znamena, ze poloha je ok-> medzi bodmi
}
function get_poloha(x1,y1,t1: real; x2,y2,t2: real;
                    _abstime: real;
                    rych: single; rych_: char;
                    vys : word; vys_ : char;
                    var xp,yp: real
                   ): bool;
   var   res: bool;
         spd, dt: real;
   begin
     spd:= get_rych_kmh(rych, rych_, vys, vys_);
     if _absTime<t1 then begin xp:= x1; yp:= y1; res:= false end
     else if _absTime<=t2 then
          begin
            if t2<>t1 then dt:= (_abstime-t1)/(t2-t1)
            else dt:= 0;
            xp  := x1 + (x2-x1) * dt;
            yp  := y1 + (y2-y1) * dt;
            res := true
          end
     else begin xp:= x2; yp:= y2; res:= false end;
     get_poloha:= res
   end;

