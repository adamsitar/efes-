(*-------------------------------------------------------------------*)
(* LETVIS FDP - IPX_def                                              *)
(* (c) Ales Kosice 1993  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_ipx.h}


unit IPX_def;


interface


     uses    TypeDef,
             IO, NET_def;


     const { kody pre komunikaciu v IPX }
            {$IFDEF IPX0}
              ipxVYZVA         =  0;
              ipxPOTVRDENIE    =  2;
              ipxDATA          =  4;
              ipxNESPRACOVANY  =  8;
              ipxTEST          = 16;
            {$ELSE}
              ipxDATA          =  4;
            {$ENDIF}

            {$IFDEF IPX3}
              ipx_sys_REQ      = $A0;  { ziadost o adresu }
              ipx_sys_RES      = $B0;  { tu mas...        }

              ipx_nd_RTR       = 1;
              ipx_nd_SYS       = 2;
              ipx_nd_RDP       = 3;
              ipx_nd_FDP       = 4;
            {$ENDIF}


     const  {$IFDEF SOCKET}
             maxIPX_NODEs  = 30;
            {$ELSE}
             maxIPX_NODEs  = 10;
            {$ENDIF}

             IPX__TIME_OUT        =  5;  { tick }    { 10 }
             IPX__HEARTBEAT: byte = 61;  { sec  }    { bude, len ked < 61 }

             IPXcfg = 'ipx'+ext_ini;


     {$I ipx_def0.h}

     type    PIPXdata = ^TIPXdata;
             TIPXdata = array[0..max_IPXdata_size-1] of byte; { < size_of_IPXpkt ! }


           { datovy packet
           }
             PIPXdpkt = ^TIPXdpkt;
             TIPXdpkt = record
               size : int;
               data : TIPXdata
             end;


           {$IFDEF SOCKET}
           { systemovy packet
           }
     const   max_IPXdata_size_system = 10;

     type    PIPXpkt_nd = ^TIPXpkt_nd;
             TIPXpkt_nd = record
               adr  : TEthernetAdr;
               nd   : int;

               size : int;
               data : array[0..max_IPXdata_size_system-1] of byte;
             end;
           {$ENDIF}


     type    TBFunc_PIPXp = function (pkt: PIPXdpkt): bool;
             TProc_PIPXp  = procedure(pkt: PIPXdpkt);


     const   IPXnode   : int = -1;  { cislo vlastneho uzla }

             ROUTERipx : int = -1;  { cislo routera }
             BRIDGEipx : int = -1;  { cislo bridgu  }



implementation

end.

