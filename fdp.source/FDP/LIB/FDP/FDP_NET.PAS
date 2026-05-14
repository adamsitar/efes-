(*-------------------------------------------------------------------*)
(* LETVIS FDP - NET 3.0                                              *)
(* (c) Ales Kosice 1993,95 (ab)                                      *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$IFDEF DB_DATA}
  {$DEFINE INIT_PLANY_ZO_SUBORA}
{$ENDIF}


unit FDP_NET;


interface


     uses  TypeDef,
           NET_def, _NETack,
           {$IFDEF IPX} IPX_def, _IPX, _IPX_ini, {$ENDIF}
           {$IFDEF PCTCP} PCTCPdef, {$ENDIF}
           _NET;


     type  PFDP_NET = ^TFDP_NET;
           TFDP_NET = object(TNET)

            {$IFDEF CONNECT_TO_FDA}
             procedure  nodeON  (ods: TNETadr; _node_init,_node_on,_init_en: bool); virtual;
             procedure  nodeOFF (ods: TNETadr; _node_off: bool; id: PNETpkt_head); virtual;
             procedure  check_nodes; virtual;

             function   id__distributed_data
                               ( typ     : word;
                                 p_data  : pointer;
                                 send_to : PBplan_rec
                               ): PNETpkt_head; virtual;
            {$ENDIF}



             {$IFDEF BROADCAST}
              procedure  receive_brc (const Bpkt : TNETBpkt {$IFDEF UDP}; from : T_IPaddress {$ENDIF}); virtual;
             {$ENDIF}

             procedure   decode_app_ack_pkt    (var  pkt: TNETpkt); virtual;
             procedure   decode_app_data_pkt   (var  pkt: TNETpkt; _stream: bool); virtual;
             {$IFDEF DATA_BIN}
               function  decode_app_data_bin_pkt (var  pkt: TNETpkt; _stream: bool) : bool;
             {$ENDIF}


             procedure   initialize_node       (nd: int); virtual;

             private
             function    node_initialize_est   (nd: int): bool;
             function    node_initialize_plan  (nd: int): bool;
             function    node_initialize_files (nd: int): bool;
           end;


     procedure NODEs_info(uplna: bool);


     {$IFDEF DEBUG}
      {procedure testFDAnodes;}
     {$ENDIF}


implementation

uses  Crt, DOS, BIOS, _Check, IO, DB,
      math, mem, keyb, str0, utime, mess, mouse, msg,
      {$I unit_gr.h},
      {$I unit_oop.h}, Lists,
      Kody, RTR_def, _RTR,
      NET_utc,
      _L4_def,_FDP_def, FIR_def,
      Archiv,
      {$IFDEF IPX} FDP_NETB, {$ENDIF}
      {$I unit_fdp.h}
      {$I unit_ext.h},
      FDP_msg, FDP_func, FDP_rep,
      {$IFDEF TRENAZER} Trnzr,  {$ENDIF}
      {$IFDEF STATUS}   Status, {$ENDIF}
      _SSR, Sector;


const  NODE_WIN: bool = true;

{$IFDEF BROADCAST}
  {$I fdp_netb.inc}  { decode_NETpkt   }
{$ENDIF}

{ nastavit volbu "spracovavam paket"
}

{$I fda_net.inc}
{$I fdp_net0.inc}    { testovanie      }
{$I fdp_net1.inc}    { decode_NETpkt   }
{$I fdp_net2.inc}    { decode_NETack   }
{$I fdp_net3.inc}    { node_initialize }
{$I fdp_net4.inc}    { node_info       }

end.