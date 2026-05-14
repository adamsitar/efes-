(*-------------------------------------------------------------------*)
(* LETVIS FDP - driver pre komunikaciu s OPL v Prahienke             *)
(* (c) Ales Kosice 1993,95,98 (ab)                                   *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{ DEFINE OPL__SAVE_STREAM}

{$X+,I-,S-,P-,F+,O+}

{$IFDEF OPL_EXT_ASYNC}
 {$O-}
 {$C FIXED PRELOAD PERMANENT}
{$ENDIF}


unit _OPL_def;


interface

    uses   TypeDef,
           _EXT_Def;



    const  SOH = #01;       { start of heading }
           STX = #02;       { start of text }
           ETX = #03;       { end of text   }
           EOT = #04;       { end of transmition }

           QRY = '#';       { querry }
           MES = '$';       { answer }

    const  opl_HEARTBEAT = '3';


    const  OPL_BUFFER_SIZE   = {$IFDEF DEBUG} 3 {$ELSE} 10 {$ENDIF};
           OPL_MESSAGE_SIZE  = 2048 + 4 {512};

    type   POPLpkt = ^TOPLpkt;
           TOPLpkt = record
             poc : word;
             buf : array[0..OPL_MESSAGE_SIZE-1] of char
           end;


    const  power_OPL_async : bool = true;
           power_OPL_udp   : bool = true;

           line_master_OPL : bool = true;


    const  IBUFF_OPL_ASYNC : PP_EXT_ibuff = nil;


implementation


end.