{ ---------------------------
   Init
  --------------------------- }

{
  Initializes a network descriptor with protocol type and endpoint information.
}
function net_connect(nd: int; ps_type: int; var _addr: T_IPaddress): int;
   var   regs: Registers;
   begin
     regs.bx:= nd;
     regs.dx:= ps_type;
     regs.ds:= seg(_addr);
     regs.si:= ofs(_addr);
     regs.ah:= _NET_CONNECT;
     net_connect:= net_call(regs)
   end;


{
  Allocates a local network descriptor.
}
function net_getdesc: int;
   var   regs: Registers;
   begin
     regs.ah:=_NET_GETDESC;
     net_getdesc:= net_call(regs)
   end;

{
  Allocates a global network descriptor.
}
function net_getglobdesc: int;
   var   regs: Registers;
   begin
     regs.ah:= _NET_GETGLOBDESC;
     net_getglobdesc:= net_call(regs)
   end;


{
  Changes a local network descriptor, which is specific to one process,
  into a global network descriptor, which is accessible from all processes
}
function net_globalize(nd: int): int;
   var   regs: Registers;
   begin
     regs.bx:= nd;
     regs.ah:= _NET_GLOBALIZE;
     net_globalize:= net_call(regs)
   end;


{
  Set and reset options associated with a network descriptor.
}
function set_option(nd,level,option: int; opt_val: long; length: int): int;
   var   regs: Registers;
         w   : word;
   begin
     regs.bx:= nd;
     regs.si:= level;
     regs.di:= option;

     w:= opt_val;
     regs.dx:= w;
     opt_val:= opt_val shr 16;
     w:= opt_val;
     regs.ds:= w;
     regs.cx:= length;

     regs.ah:= _SET_OPTION;
     if net_call(regs)<>-1 then set_option:= 0
     else set_option:= -1
   end;

{
  Retrieves the value of an option set on a network descriptor.
}
function get_option(nd,level,option: int; var buff; length: int): long;
   var   regs: Registers;
   begin
     regs.bx:= nd;
     regs.si:= level;
     regs.di:= option;
     regs.dx:= ofs(buff);
     regs.ds:= seg(buff);
     regs.cx:= length;

     regs.ah:= _GET_OPTION;
     if net_call(regs)<>-1 then get_option:= 0
     else get_option:= -1
   end;


{
  Initializes a network connection with protocol type and endpoint information.
}
function net_listen(nd,_type: int; var _addr: T_IPaddress): int;
   var   regs: Registers;
   begin
     regs.bx:= nd;
     regs.dx:= _type;

     regs.ds:= seg(_addr);
     regs.si:= ofs(_addr);

     regs.ah:= _NET_LISTEN;

     net_listen:= net_call(regs)
   end;



{ ---------------------------
   Done
  --------------------------- }

{
  Close a network connection, releasing the network descriptor
  and deallocating internall resources associated with the network descriptor.
}
function net_release(nd: int): int;
   var   regs: Registers;
   begin
     regs.bx:= nd;
     regs.ah:= _NET_RELEASE;
     net_release:= net_call(regs)
   end;

{
  Performs a net_release() on all local descriptors in use by this process.
}
function net_releaseall: int;
   var   regs: Registers;
   begin
     regs.ah:= _NET_RELEASEALL;
     net_releaseall:= net_call(regs)
  end;



{
  Immediately releases a network descriptor and deallocates the resources
  associated with it.
}
function net_abort(nd: int): int;
   var   regs: Registers;
   begin
     regs.ah:= _NET_ABORT;
     regs.bx:= nd;
     net_abort:= net_call(regs)
   end;

{
  Performs a net_abort() on all local descriptors in use by this process.
}
function net_abortall: int;
   var   regs: Registers;
   begin
     regs.ah:= _NET_ABORTALL;
     net_abortall:= net_call(regs)
   end;

{
  Determines if the input argument is a network descriptor.
}
function is_netnd(nd: int): int;
   var   regs:Registers;
   begin
     regs.bx:= nd;
     regs.ah:= _IS_NETND;
     is_netnd:= net_call(regs)
   end;
