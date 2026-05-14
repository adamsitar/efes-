(*-------------------------------------------------------------------*)
(* PC TCP/IP                                                         *)
(* (c) Ales Kosice 1995, prepis z C LIB                              *)
(*-------------------------------------------------------------------*)
{
  Neviem, ci by nebolo lepsie nechat fcie v assebleri...
}

{$I comp.h}
{$I comp_tcp.h}

{$C FIXED PRELOAD PERMANENT}
{$F+,R-,S-}

{$IFDEF AS_PCTCP}
  {$O- }
{$ENDIF}



unit PCTCP;


interface


    uses  TypeDef, Arrays,
          NET_def,
          PCTCPdef;


    const   int_PCTCP = $61;

    const   UDPdata_size = size_of_NETpkt;

    type    TUDPdata = array[0..UDPdata_size-1] of char;

    {$IFDEF PCTCP}

            PUDPpkt = ^TUDPpkt;
            TUDPpkt = record
              desc : int;
              from : T_IPaddress;

              size : int;
              data : TUDPdata
            end;


      const UDP_buff_size = {$IFDEF DEBUG} 10 {$ELSE} maxNODEs {$ENDIF};
            UDP_buff      : PBuffer  = nil;


      var   netsuberrno : word;
            neterrno    : word;


      { Testovanie pritomnosti drivera         }


      { Network Descriptor System Calls        }
        function  net_connect(nd: int; ps_type: int; var _addr: T_IPaddress): int;

        function  net_getdesc: int;
        function  net_getglobdesc: int;
        function  net_globalize(nd: int): int;

        function  set_option(nd,level, option: int; opt_val  : long; length: int): int;
        function  get_option(nd,level,option: int; var buff; length: int): long;

        function  net_listen(nd,_type: int; var _addr: T_IPaddress): int;

        function  net_release(nd: int): int;
        function  net_releaseall: int;
        function  net_abort(nd: int): int;
        function  net_abortall: int;


      { Adresy                                 }
        function  nm_prs_addr(_str: string): in_name;
        function  inet_ntoa  (_in : in_name): string;


      { Asyncronous Communication System Calls } { Pre protected mod upravit ! }
        function  disable_asynch: int;
        function  enable_asynch: int;

        function  net_alarm  (nd: int; time: long; handler: pointer; hint: pointer): long;
        function  net_asynch (nd,event: int; handler: pointer; hint: pointer): long;

        procedure asynch_stub; far;
        procedure net_asynch_handler (nd: int; event: int; arg: pointer); far;


      { ICMP System Calls                      }
        function  icmp_ping(host: in_name; len: word): long;


      { Status Systems Calls                   }
        function  is_netnd(nd: int): int;
        function  get_kernel_info(nd: int; tag,dev_ID: byte; var buf; var size: long): long;


      { Receive System Calls                   }
        function  net_is_data  (nd: int; var buf; len: int; var _from: T_IPaddress): long;
        function  net_read     (nd: int; var buf; len: int; var _from: T_IPaddress; flags: word): long;
        function  net_readfrom (nd: int; var buf; len: int; var _from: T_IPaddress; flags: word): long;


      { Transmit System Calls                  }
        function  net_write   (nd: int; var buf; len: int; flags: word): int;
        function  net_writeto (nd: int; var buf; len: int; var _to: T_IPaddress; flags: word): int;

    {$ENDIF}


implementation

uses  Dos,Crt, Mem, {Str0,} Mess;

const FIRST_VEC   = $20;
      LAST_VEC    = $E0;
      MATCH       = 'TCPTSR';

      int_TCP_IP  : int  = $61;
      initialized : bool  = false;


{$IFDEF PCTCP}

procedure __dosyscall; assembler;
   asm
     int int_PCTCP
   end;

function net_call(var regs: Registers): long;
   begin
     if initialized then
        begin
          intr(int_TCP_IP,regs);
          netsuberrno := regs.ax;      { ak O.K. mala by tu byt 0 }
          net_call    := netsuberrno;
          if regs.FLAGS and fCarry = 1 then
             begin
               neterrno := netsuberrno shr 8;
               net_call := -1
             end
        end
     else net_call:= -1
   end;


{$I pctcp0.inc}     { Testovanie pritomnosti drivera         }
{$I pctcp1.inc}     { Network Descriptor System Calls        }
{$I pctcp2.inc}     { Adresy                                 }

const UDP_pkt       : PUDPpkt = nil;

{$I pctcp3.inc}     { Asyncronous Communication System Calls } { Pre protected mod upravit ! }
{$I pctcp4.inc}     { As... interrupt                        }

{$I pctcp5.inc}     { ICMP System Calls                      }

{$I pctcp7.inc}     { Status Systems Calls                   }
{$I pctcp8.inc}     { Receive System Calls                   }
{$I pctcp9.inc}     { Transmit System Calls                  }


const  SaveExit : pointer = nil;

procedure pctcp_done; far;
    begin
      pctcp_cleanup;
     {$IFDEF AS_PCTCP}
       if UDP_buff<>nil then Dispose(UDP_buff,Done);
       if UDP_pkt <>nil then Dispose(UDP_pkt);
     {$ENDIF}
      ExitProc:= SaveExit
    end;

procedure pctcp_init;
    begin
      if _find_vec<>0 then
         begin
           if SaveExit<>nil then Exit;
           SaveExit:= ExitProc;
           Exitproc:= @pctcp_done;

          {$IFDEF AS_PCTCP}
            if (UDP_pkt=nil)  then New(UDP_pkt);
            if (UDP_buff=nil) then UDP_buff:= New(PBuffer,Init(UDP_buff_size,SizeOf(UDP_pkt^), false));
          {$ENDIF}
         end
    end;


begin
  pctcp_init
{$ENDIF}

end.