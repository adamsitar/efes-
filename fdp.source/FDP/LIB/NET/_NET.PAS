(*-------------------------------------------------------------------*)
(* LETVIS FDP - NET 3.0                                              *)
(* (c) Ales Kosice 1993,95 (ab)                                      *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$I comp_NET.h}
{$I comp_RTR.h}
{$I comp_IPX.h}
{$I comp_X25.h}
{$I comp_TCP.h}


{ Obmedzenie :

  Stanice smu byt skonfigurovane len skrz SERVER a BSERVER,
  aby nedoslo ku kruhovym referenciam...
}

unit _NET;


interface


     uses  TypeDef,
           Arrays, Astream,
           {$I unit_gr.h},
           Objects, App,
           NET_def, _NETack
           {$IFDEF IPX}  , IPX_def  {$ENDIF}
           {$IFDEF PCTCP}, PCTCPdef {$ENDIF}
           ;


     {$I net_cnst.h}
     {$I net_variables.h}
     {$I net_title.h}
     {$I net_object.h}
     {$I net_functions.h}


     const  NET    : PNET = nil;
            NETack : PONETack = nil;


implementation


uses  DOS, BIOS, _Check, IO, DB,
      keyb, str0, sets, utime, mess, math, mem, msg, prnt,
      CMs, Dialog,

      {$IFDEF IPX}    _IPX_ini,_IPX,    {$ELSE} {$IFDEF DEBUG} _IPX_ini,_IPX, {$ENDIF} {$ENDIF}
                      _X25, RTR_def,
      {$IFDEF RTR}    _RTR,             {$ENDIF}
      {$IFDEF COM}    _COM,             {$ENDIF}
      {$IFDEF PCTCP}  PCTCP,            {$ENDIF}
                      _PCTCP,

      {$IFDEF ARCHIVE_DAR} DAR_def, DAR_arch, {$ENDIF}
      { IFDEF ARCHIVE_NET} Archiv,            { ENDIF}

      {$IFDEF MPU}       MPU,           {$ENDIF}

      Kody, NET_utc;


var   SaveMain0 : TProc;
      SaveMainA : TProc;
      SaveMainD : TProc;
      SaveExit  : pointer;


{$I _net.inc}             { is_pkt_..., trasy, rec  }
{$I _net_bridge.inc}      { bridge                  }
{$I _net_archive.inc}     { vypis paketov, testy    }
{$I _net_system.inc}      { systemove spravy        }
{$I _net_prn.inc}

{$I _net_object.inc}      { TNET ...                }
{$I _net_packet.inc}      {                         }

{$I _net_buffers.inc}     { prijem sprav od komunikacnych bufferov    }

{$I _net_send.inc}        { priprava, odoslanie pkt }
{$I _net_data_send.inc}   { data  : send, distribute                  }
{$I _net_files_send.inc}  { subor : send, distribute, receive,...     }

{$I _net_receive.inc}     { spracovanie/potvrdenie/zaradenie prijateho paketu }
{$I _net_process.inc}     { spracovanie sprav a presmerovanie paketov }
{$I _net_acknowledge.inc} { spracovanie potvrdeni                     }

{$I _net_nodes_check.inc} { kontrola uzlov                            }
{$I _net_check.inc}

{$I net_err.inc}
{$I net_cfg.inc}
{$I net_ini.inc}


begin
  p_print_str:=  print_str_to_net;
  max_NETBuffer:= Limit(read_cfg_word(SYSTEMcfg,cfg_NETBuffer,max_NETBuffer),10,500, 0);
  fillchar(lastDataHead,sizeof(lastDataHead),0);
end.
