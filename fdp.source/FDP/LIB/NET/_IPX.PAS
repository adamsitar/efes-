(*-------------------------------------------------------------------*)
(* LETVIS FDP - IPX 3.0                                              *)
(* (c) Ales Kosice 1993,95  (Jirko,Miro a trochu i ab)               *)
(*-------------------------------------------------------------------*)
{$I comp.h}
{$I comp_ipx.h}
{$I comp_rtr.h}

{$X+,I-,S-,P-,F+,O-}
{$C FIXED PRELOAD PERMANENT}


{ V module ipx3.inc je direktiva OPL, pri prerobeni OPL na nove - vyhodit }


unit _IPX;


interface


      uses  TypeDef, Arrays,
            NET_def, IPX_def, RTR_def;


      const IPX_installed   : bool = false;
            IPX_initialized : bool = false;

            IPX_GLOBAL_INIT : bool = false;
            cfg_IPX_GLOBAL_INIT = 'IPX_GLOBAL_INIT';


      {$IFDEF IPX}
        {$I IPX_def.h}
        {$I IPX_var.h}

        {$I IPX.h}


       {$IFDEF ARCHIVE_DAR}
        const  save_RLI       : pointer = nil;
       {$ENDIF}

       {$IFDEF BROADCAST}
        const  isIPXbroadcast : pointer = nil;
       {$ENDIF}

        var   IPXnodes: array[0..maxIPX_NODEs-1] of PIPXnode; { V/V bufery a drivery }

        {$IFDEF SOCKET}
          function  IPX_adr_nil (ad: TNodeAdr): bool; far;
          function  IPX_adr_eq  (ad1,ad2: TNodeAdr): bool; far;
          procedure IPX_get_lan_adress (var adresa: TIPXadr); far;
         {$IFDEF IPX3}
           procedure IPX_login;
           procedure IPX_read_system_mess;
         {$ENDIF}
        {$ELSE}
          function  ListenIPX (node: byte): byte; far;
          procedure SendIPX   (node: byte); far;
          procedure MessIPX   (node,sprava: byte); far;
        {$ENDIF}
      { ENDIF}

       function   isIPXname (var adr: TNETadr): int;
       function   is_this_IPXnode (adr: TNETadr): bool;

       function   code_NETpkt_to_ipxIPXpkt (const Np: TNETpkt; var Lp: TIPXdpkt): bool;
       function   code_ipxIPXpkt_to_NETpkt (const Lp: TIPXdpkt; var Np: TNETpkt): bool;

      { IFDEF IPX}
        function   ipx_send (node: int; size: word; buff: pointer): int;
        function   IPXsend  (const pkt: TNETpkt; adr: TNETadr) : int;

        function   IPXread (var pkt: TIPXdpkt): bool;
        function   RTRread (var pkt: TIPXdpkt): bool;

        {$IFDEF BROADCAST}
         function  IPXBread(var pkt: TNETBpkt): bool;
        {$ENDIF}

        procedure  IPXstatus;
      {$ENDIF}



implementation

uses Crt, Dos, BIOS, IO,
     mem, math, str0, sets, mess,
     _IPX_ini;


{$IFDEF IPX}

  {$IFDEF SOCKET}
    {$I IPX1s.inc}      { ECB, deklaracie }
    {$IFDEF IPX3}
      {$I IPX4s.inc}
    {$ENDIF}
  {$ELSE}
    {$I IPX1.inc}
  {$ENDIF}

  {$I IPX0.inc}
  {$I IPX2.inc}         { TIPXnode }
  {$I IPX3.inc}         { IPXsend, IPXsend ... }
  {$I IPX4.inc}         { buffery }

  {$IFDEF SOCKET}
    {$I IPX_ints.inc}
  {$ELSE}
    {$I IPX_int.inc}
  {$ENDIF}

 begin
   IPX_GLOBAL_INIT:= read_cfg_bool(SYSTEMcfg, cfg_IPX_GLOBAL_INIT, IPX_GLOBAL_INIT);

   nd_buff_size  := Limit(read_cfg_word(SYSTEMcfg,cfg_nd_buff_size,nd_buff_size),10,100, 0);
   rtr_buff_size := Limit(read_cfg_word(SYSTEMcfg,cfg_rtr_buff_size,rtr_buff_size),10,100, 0);
  {ipx_repeat    := Limit(read_cfg_word(SYSTEMcfg,cfg_ipx_repeat,ipx_repeat), 0,5, 0);}
   IPX__HEARTBEAT:= Limit(read_cfg_word(SYSTEMcfg,cfg_IPX__HEARTBEAT,IPX__HEARTBEAT),1,61, 0);

   IPX_detect
 {$ENDIF}
end.  { Novell - IPX }
