{
  Peek an incoming data without dequeuing it.
}
function net_is_data(nd: int; var buf; len: int; var _from: T_IPaddress): long;
   var   regs: Registers;
         p   : ^pointer;
   begin
     p:= nil;

     regs.si:= ofs(buf);
     regs.ds:= seg(buf);

     regs.cx:= len;

     regs.di:= ofs(p^);
     regs.es:= seg(p^);

     regs.dx:= NET_FLG_NONBLOCKING or NET_FLG_PEEK;
     regs.bx:= nd;

     regs.ah:= _NET_READ;

     if net_call(regs)<>-1 then net_is_data:= regs.cx
     else net_is_data:= -1
   end;


{
  Reads into a buffer data received on a network descriptor
}
function net_read(nd: int; var buf; len: int; var _from: T_IPaddress; flags: word): long;
   var   regs: Registers;
   begin
     regs.si:= ofs(buf);
     regs.ds:= seg(buf);

     regs.cx:= len;

     regs.di:= ofs(_from);
     regs.es:= seg(_from);

     regs.dx:= flags;
     regs.bx:= nd;

     regs.ah:= _NET_READ;

     if net_call(regs)<>-1 then net_read:= regs.cx
     else net_read:= -1
   end;


{
  Reads into buffer data received on DGRAM or RAW_IP network descriptor
}
function net_readfrom(nd: int; var buf; len: int; var _from: T_IPaddress; flags: word): long;
   var   regs: Registers;
   begin
     regs.si:= ofs(buf);
     regs.ds:= seg(buf);

     regs.cx:= len;

     regs.di:= ofs(_from);
     regs.es:= seg(_from);

     regs.dx:= flags;
     regs.bx:= nd;

     regs.ah:= _NET_READFROM;

     if net_call(regs)<>-1 then net_readfrom:= regs.cx
     else net_readfrom:= -1
   end;
