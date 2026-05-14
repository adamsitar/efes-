{
  Send an ICMP echo request to the specified host,
  and then reads the ICMP echo response an reports
  succes or failure.
}
function icmp_ping(host: in_name; len: word): long;
   var   regs: Registers;
   begin
     regs.ah:= _ICMP_PING;
     regs.bx:= seg(host);
     regs.dx:= ofs(host);
     regs.cx:= len;

     icmp_ping:= net_call(regs)
   end;
