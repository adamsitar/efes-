function get_kernel_info(nd: int; tag,dev_ID: byte; var buf; var size: long): long;
   var   regs: Registers;
   begin
     regs.bx:= nd;
     regs.dh:= tag;
     regs.dl:= dev_ID;

     regs.ds:= seg(buf);
     regs.si:= ofs(buf);

     regs.es:= seg(size);
     regs.di:= ofs(size);

     regs.ah:= _GET_KERNEL_INFO;

     if net_call(regs)<>-1 then get_kernel_info:= 0
     else get_kernel_info:= -1
   end;
