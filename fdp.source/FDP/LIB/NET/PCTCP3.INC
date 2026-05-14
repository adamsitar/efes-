function disable_asynch: int;
   var   regs: Registers;
   begin
     disable_asynch:= -1;
     if not initialized then Exit;

     regs.ah:= _DISABLE_ASYNCH;
     intr(int_TCP_IP,regs);

     disable_asynch:= regs.ax
   end;

function enable_asynch: int;
   var   regs: Registers;
   begin
     enable_asynch:= -1;
     if not initialized then Exit;

     regs.ah:= _ENABLE_ASYNCH;
     intr(int_TCP_IP,regs);

     enable_asynch:= regs.ax
   end;


{
  Enables a TSR, or other program, using asychronous facilities to
  regain control at specific time, regardles of the state of its
  network connections
}
function net_alarm(nd: int; time: long; handler: pointer; hint: pointer): long;
   var   regs      : Registers;
         li        : long;
         lihandler : long;
   begin
     regs.bx:= nd;

     lihandler:= long(handler);
     li:= time;
     regs.dx:= li;
     li:= li shr 16;
     regs.cx:= li;

     li:= long(hint);
     regs.di:= li;
     li:=li shr 16;
     regs.es:= li;

     regs.si:= lihandler;
     lihandler:= lihandler shr 16;
     regs.ds:= lihandler;

     regs.ah:= _NET_ALARM;

     if net_call(regs)<>-1 then net_alarm:= 0
     else net_alarm:= -1
   end;


{
  Specifies or cancels a handler routine for an asynchronous network event.
  Vystupna hodnota by mala byt adresa predchadzajuceho handlera
}
function net_asynch(nd, event: int; handler: pointer; hint: pointer): long;
   var   regs      : Registers;
         li        : long;
         lihandler : long;
   begin
     li:= long(hint);
     lihandler:= long(handler);

     regs.bx:= nd;
     regs.cx:= event;

     regs.dx:= lihandler;
     lihandler:= lihandler shr 16;
     regs.ds:= lihandler;

     regs.di:= li;
     li:= li shr 16;
     regs.es:= li;

     regs.ah:= _NET_ASYNCH;

     if net_call(regs)<>-1 then
        begin
          li:= regs.dx;
          li:= li shl 16;
          net_asynch:= li + netsuberrno
        end
     else net_asynch:= 0
   end;
