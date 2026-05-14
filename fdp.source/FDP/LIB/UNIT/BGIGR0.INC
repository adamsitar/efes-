{ -------------------------------------------------- }
{  pomocne funkcie                                   }
{ -------------------------------------------------- }

procedure get_region(R: TRegion; var x0,y0,x1,y1: int);
    begin
      x0:= R.x0; y0:= R.y0; x1:= R.x1; y1:= R.y1
    end;

procedure set_region(x0,y0,x1,y1: int; var R: TRegion);
    begin
      R.x0:= x0; R.y0:= y0; R.x1:= x1; R.y1:= y1
    end;


function move_reg(var x0,y0, x1,y1: int; dx,dy: int): byte;
   var   r: byte;
   begin
     r:= 0;
     if (x0+dx > btmdXY.x0) and (x1+dx < MaxX-btmdXY.x1) then
        begin
          inc(x0,dx);
          inc(x1,dx);
          inc(r)
        end;
     if (y0+dy > btmdXY.y0) and (y1+dy < MaxY-btmdXY.y1) then
        begin
          inc(y0,dy);
          inc(y1,dy);
          inc(r)
        end;
     move_reg:= r
   end;


function kbset_xy(kbXXXX: char): bool;
   var   dx,dy, xp,yp: int;
   begin
     kbset_xy:= false;
     if (is_mouse=0) or (not (kbXXXX in [kbLeft,kbRight,kbDown,kbUp])) then Exit;
     with mouse_status.stat do
       begin
         dx:= 0; dy:= 0; xp:= x; yp:= y;
         case kbXXXX of
           kbLeft : dx:=-5;
           kbRight: dx:= 5;
           kbDown : dy:= 5;
           kbUp   : dy:=-5
         end;
         move_reg( x,y, xp,yp, dx,dy);
         set_xy(x,y)
       end;
     {if not m_visible then m_on(true, mouse_status.stat.x,mouse_status.stat.y);}
     kbset_xy:= true
   end;


function m_to_kb(m: TMouseChar): char;
   var   res  : char;
   const Yvzt : int = 0;
   begin
     {Yvzt:= MaxY shr 1;}
     res:= ' ';
     if (m.y<>0) and (Yvzt<>m.y) then
        begin
          if m.y-Yvzt<-10 then res:= kbUp
          else if m.y-Yvzt>10 then res:= kbDown;
          if res<>' 'then
             begin
               if (m.y<10) or (m.y>MaxY-10) then
                  begin
                    m.y:= MaxY shr 1;
                    set_xy(m.x{MaxX shr 1},m.y)
                  end;
               Yvzt:= m.y
             end;
          {m_hide;}
        end;
     if (m.bt<>0) then
        if bool(M.bt and mbLeftButton) then res:= kbEnter
        else if bool(M.bt and mbRightButton) then res:= kbEsc;
     m_to_kb:= res
   end;

