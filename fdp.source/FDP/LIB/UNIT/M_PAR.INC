{ -------------------------------------------------- }
{  parametre mysi                                    }
{ -------------------------------------------------- }
{
  rozsah pre mys
}
procedure m_clip(x0,y0,x1,y1: int);
    var   reg : Registers;
          bp : bool; xl,yl : int;
    begin
      if (is_mouse=0) then Exit;
      m_off(bp, xl,yl);
      reg.ax:= 7;
      reg.cx:= x0;
      reg.dx:= x1;
      Intr($33,reg);
      reg.ax:= 8;
      reg.cx:= y0;
      reg.dx:= y1;
      Intr($33,reg);
      m_on(bp, xl,yl)
    end;


procedure m_sensitivity(dx,dy: int);
    var   reg: Registers;
    begin
      if (is_mouse=0) then Exit;
      reg.ax:= 15;
      reg.cx:= dx;
      reg.dx:= dy;
      Intr($33,reg)
    end;


procedure m_speed(treshold: word);
    var   reg: Registers;
    begin
      if (is_mouse=0) then Exit;
      reg.ax:= 19;
      reg.dx:= treshold; { motion per second }
      Intr($33,reg)
    end;

