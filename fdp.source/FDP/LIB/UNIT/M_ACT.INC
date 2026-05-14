{ -------------------------------------------------- }
{  buffer stlaceni buttonov mysi                     }
{ -------------------------------------------------- }
{
vrati true, ak bola pouzita mys
}
function m_hit: bool;
   begin
     m_hit:= mIntFlag and (mcit<>mzap);
     mIntFlag:= false
   end;

{
funkcia vlozi udaj do buffra dat, vola sa v interrupt rutine
}
procedure m_push;
    begin
      mbuffer[mzap]:= mouse_status.stat;
      if maxMouseBuff<>0 then
         begin
           mzap:= (mzap+1) mod maxMouseBuff;
           if (mcit = mzap) then mcit:= (mcit+1) mod maxMouseBuff { posledny udaj sa strati }
         end
    end;

{
funkcia precita udaj z buffra dat
vrati 1 ak je udaj platny, a ak je prazdny, vrati 0
}
function m_pop(var m: TMouseChar): bool;
   begin
     if (mcit <> mzap) then
        begin
          m:= mbuffer[mcit];
          if maxMouseBuff<>0 then mcit:= (mcit+1) mod maxMouseBuff;
          m_pop:= true
        end
     else m_pop:= false
   end;


procedure m_clear;
    begin
      mcit:= mzap;
      fillchar(mouse_status.stat,sizeof(TMouseChar),0)
    end;


{ -------------------------------------------------- }
{  poloha mysi                                       }
{ -------------------------------------------------- }
var dx_,dy_: int;

procedure get_dxy(var dx,dy: int);
    var   reg: Registers;
    begin
      if (is_mouse=0) then Exit;
      asm
          mov   ax,11
	  int	33h
          mov   dx_,cx
          mov   dy_,dx
      end;
      dx:= dx_;
      dy:= dy_
    end;



procedure set_m_xy(x,y: int);

    function Limit(val, lo,hi: int): int;
        begin
         if (val<lo) then Limit:= lo
         else if val>hi then Limit:= hi
              else Limit:= val
        end; { Limit }

    var   dx,dy: int;
    begin
      get_dxy(dx,dy);
      m_x:= Limit(m_x + dx, 0,MaxX-16);
      m_y:= Limit(m_y + dy, 1,MaxY);
     { chyba vo verzii drivera <= 6.0, kontrola na odchylku voci skutocnej polohe
      if is_ver_6 then
         begin
           if abs( abs(m_x) - abs(x)) > 16 then m_x:= x;
           if abs( abs(m_y) - abs(y)) > 16 then m_y:= y
         end
     }
    end;

function get_xy(var x,y: int): int;
   var   reg   : Registers;
         dx,dy : int;
   begin
     get_xy:= 0;
     if (is_mouse=0) then Exit;

     reg.ax:= 3;
     intr($33,reg);
     x := reg.cx;
     y := reg.dx;

     set_m_xy(x,y);  { prepocet do vlastneho citaca polohy }
     if (x<>mouse_status.stat.x) or (x<>mouse_status.stat.y) then get_xy:= 1;
     mouse_status.stat.x:= x;
     mouse_status.stat.y:= y
   end;


procedure set_xy(x,y: int);
    begin
      if (is_mouse=0) then Exit;
    { kontrola na spravnost suradnic ... }
    { ... }
      asm
	  push	ax
          push  cx
          push  dx
          mov   ax,4
          mov   cx,x
          mov   dx,y
	  int	33h
	  pop	dx
          pop   cx
          pop   ax
      end;
      mouse_status.stat.x:= x;
      mouse_status.stat.y:= y;
      m_x:= x;
      m_y:= y;
      if m_visible then m_put
    end;


{
  Funcia nastavi okamzity button status bt, ak bola zmena vrati 1, inak 0.
  Button status pozostava z tejto hodnoty:
    Bit 0 = lavy button (2 button mode, 3 button mode)
    Bit 1 = pravy button (2 button mode, 3 button mode)
    Bit 2 = stredny button (3 button mode)
    ak je button zatlaceny bit nastaveny na 1
}
function get_bt(var bt: byte): int;
   var   reg: Registers;
   begin
     get_bt:= 0;
     if (is_mouse=0) then Exit;
     reg.ax:= 3;
     intr($33,reg);
     bt:= reg.bl and $07;
     if (bt<>mouse_status.stat.bt) then get_bt:= 1;  { zmena bola }
     mouse_status.stat.bt:= bt
   end;

{
vrati true, ak bola zmena
}
function get_m(var x,y: int; var bt: byte): bool;
   begin
     get_m:= (get_xy(x,y)<>0) or (get_bt(bt)<>0);
   end;


