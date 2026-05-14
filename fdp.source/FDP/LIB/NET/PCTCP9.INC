{
  Transit data over a network descriptor
}
function net_write(nd: int; var buf; len: int; flags: word): int;
   var   regs: Registers;
   begin
     regs.ds:= seg(buf);
     regs.si:= ofs(buf);

     regs.cx:= len;
     regs.dx:= flags;
     regs.bx:= nd;

     regs.ah:= _NET_WRITE;

     net_write:= net_call(regs)
   end;


{
  Transmit data over a DGRAM or RAW_IP newtwork descriptor
}
function net_writeto(nd: int; var buf; len: int; var _to: T_IPaddress; flags: word): int;
   var   regs:Registers;
   begin
     regs.si:= ofs(buf);
     regs.ds:= seg(buf);

     regs.cx:= len;

     regs.di:= ofs(_to);
     regs.es:= seg(_to);

     regs.dx:= flags;
     regs.bx:= nd;

     regs.ah:= _NET_WRITETO;

     net_writeto:= net_call(regs)
   end;

