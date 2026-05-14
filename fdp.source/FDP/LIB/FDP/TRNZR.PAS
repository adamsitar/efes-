(*-------------------------------------------------------------------*)
(* Trenazer                                                          *)
(* 1994,95                                                           *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$O-}


unit Trnzr;


interface


    uses   TypeDef,
           NET_def, IPX_def, PCTCPdef, _NET, RTR_def, _RTR,
           Kody, Menus;


    {$IFDEF TRENAZER}

     {$IFDEF TRENAZER_IPX}
       {$I trzr_ipx.h}

     {$ELSE}

      const  SIM_UNIX : bool =
                               {$IFDEF TRENAZER_UNIX}
                                true;
                               {$ELSE}
                                false;
                               {$ENDIF}


     { DOSovy simulator
     }
       const  SIM0_UDP_SOCKET_ADR  = $5000;
              sim0_is_configured   : bool = false;
              sim0_GROUP           : word = 0;
              sim0_DEVICE          : word = 0;

       const  sim0_THIS            : word = 0;
              cfg_sim0_THIS        = '@SIM';

       const  sim0_CFG             = $A0;
              sim0_CFG_ACK         = $A1;
              sim0_CFG_CNL         = $A2;

              sim0_DEP             = $A3;
              sim0_ARR             = $A4;

              sim0_BRK             = $06;
              sim0_CNT             = $07;

              sim0_REC_DEP         = $B1;
              sim0_REC_ARR         = $B2;
              sim0_REC_CNL         = $AC;

              sim0_STRIP           = $C8;


       type   TSIM0pkt_head = record
                id     : byte;
                group  : word;
                device : word;
                typ    : byte;
              end;

              PSIM0pkt = ^TSIM0pkt;
              TSIM0pkt = record
                head   : TSIM0pkt_head;
                data   : Tbytes
              end;



     { UNIXovy simulator
     }
       const  SIM_UDP_SOCKET_ADR   = $5100;
              sim_is_configured    : bool = false;
              SIM_MASTER           : TIPadr = 0;

       const  SIM_SCAT_SET_CFG     = $11;
              SIM_SCAT_SET_CFG_ACK = $12;

              SIM_SCAT_CANCEL_CFG  = $13;
              SIM_SCAT_START_EXERC = $15;
              SIM_SCAT_STOP_EXERC  = $17;
              SIM_SCAT_BREAK       = $19;
              SIM_SCAT_CONTINUE    = $1B;

              SIM_SCAT_STD_RLI     = $01;
              SIM_SCAT_STD_FPI     = $02;
              SIM_SCAT_ARC_CMD     = $03;


       type   TSIMpkt_head = record    { identifikator kazdeho paketu }
                id     : byte;         { astSIM }
                typ    : byte;         { SIM_SCAT_XX }
                master : TIPadr        { IP mastera v sieti pre identifikaciu v skupine }
              end;

              PSIMpkt = ^TSIMpkt;
              TSIMpkt = record
                head : TSIMpkt_head;
                data : Tbytes          { TSIMdata }
              end;

              PSIMdata_head = ^TSIMdata_head;
              TSIMdata_head = record
                ast  : byte;           { $F1 }
                kod  : byte;           { $C8 }
                nic  : byte;           { $00 }

                typ  : TNETtyp;        { typ udajov "data" }
                cis  : TNETcis;        { cislo paketu }
              end;

              PSIMdata = ^TSIMdata;
              TSIMdata = record
                head : TSIMdata_head;
                data : Tbytes          { kodovane data TNETpkt.pkt.data }
              end;


       function receive_astSIM_pkt (data: pbytes; size: word; fhost: in_name): bool;
     {$ENDIF}

     procedure SIM_init;
    {$ENDIF}



implementation

uses  crt, bios, io, math, str0, utime, mess,
      {$IFDEF IPX} _IPX, {$ENDIF}
      {$IFDEF UDP} PCTCP, {$ENDIF} _PCTCP,
      NET_utc,
      Events, Objects, CMs, CM,
      Hodiny, Body,
      _L4_def, _FDP_def, _FPL_def,
      Bod_Def,
      _FPL, _FPLc, _FPLm;


{$IFDEF TRENAZER}

 {$IFDEF TRENAZER_IPX}

  {$I trzr_ipx.inc}

 {$ELSE}

  {$I sim0_udp.inc}

  const SIMport : PUDP_port = nil;

  {$I sim_udp.inc}


  function receive_astSIM_pkt (data: pbytes; size: word; fhost: in_name): bool;
     begin
       if SIM_UNIX then receive_SIMpkt (data,size,fhost)
       else receive_SIM0pkt (data,size,fhost)
     end;


  procedure SIM_init;
      begin
       {$IFDEF TRENAZER_IPX}
         {$IFDEF IPX} isIPXbroadcast:= @is_IPXBpacket; {$ENDIF}
       {$ENDIF}
       {$IFDEF TRENAZER_DOS}
         SIM_DOS__init;
       {$ENDIF}
       {$IFDEF TRENAZER_UNIX}
         SIM_UNIX__init;
       {$ENDIF}
      end;

  {$ENDIF}

{$ENDIF}

begin
 {$IFDEF TRENAZER_DOS}
 {$IFDEF PCTCP}
   UDP_PORT_BRC.port:= SIM0_UDP_SOCKET_ADR;
 {$ENDIF}
 {$ENDIF}
end.