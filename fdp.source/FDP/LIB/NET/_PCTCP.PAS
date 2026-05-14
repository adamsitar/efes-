(*-------------------------------------------------------------------*)
(* PC TCP/IP, funkcie pre pipojenie ku _NET                          *)
(* (c) Ales Kosice 1995                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_tcp.h}

{$I comp_RTR.h}

{
  UDP by mohol byt jeden objekt, ale zatial to nema vyznam,

  kodovanie do siete LETVIS ma viacero formatov :
   - trenazer
   - cisco
   - rtr      : teraz len narychlo, chce to dalsi socket pre rtr data
                a presmerovanie na router pre wan...

}


unit _PCTCP;


interface


     uses  TypeDef,
           Kody,
           NET_def, RTR_def,
           PCTCPdef, PCTCP;


    {$I _udp_rtr.h}       { protokol pre komunikaciu cez CISCO }
    {$I _udp_port.h}      { definicia udp portov               }


    {$IFDEF UDP}
     procedure  udp_open_port(_UDP_FHOST,_UDP_PORT: word; var _UDP_desc: int; _asynch, _connect: bool);
     procedure  UDP_init;

     function   is_IPadr(adrip: TIPadr): TNETadr;

     function   udp_read(desc: int; buff: pointer; max_len: int; var _from: T_IPaddress): int;
     function   UDPread (port: TUDP_port; var Np: TNETpkt): bool;

     function   udp_send_(port: TUDP_port; brc: bool; adr: TIPname; adrip: TIPadr; size: int; buff: pointer; flags: word): int;
     function   udp_send (port: TUDP_port; brc: bool; adr: TIPname; adrip: TIPadr; size: int; buff: pointer): int;
    {$ENDIF}

     function   UDPsend_(const pkt: TNETpkt; adr: TNETadr; brc: bool; protocol, typ: word; flag: word): int;
     function   UDPsend (const pkt: TNETpkt; protocol,flag: word): int;
     function   UDBsend (const pkt: TNETpkt; adr: TNETadr; flag: word): int;



implementation

uses  Crt, Dos, BIOS, IO,
      mem, math, str0, sets, mess, keyb,
      Arrays,
      NET_utc,
      _RTR;


const max_routers  = 3;
      PPP_fr_size  = 0;
      DIX_fr_size  = 6;
      PING_delay   = 50;

var   my_ip_addr   : in_name;
      subnet_mask  : in_name;
      routers_num  : int;
      routers      : array[0..max_routers-1] of in_name;
      frame_type   : Tframe_type;


{$I _rtrc_pkt.inc}

{$IFDEF UDP}
 {$I _udp_ini.inc}
 {$I _udp_read.inc}
{$ENDIF}

{$I _udp_send.inc}

end.