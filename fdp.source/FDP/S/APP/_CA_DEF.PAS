(*-------------------------------------------------------------------*)
(* LETVIS FDP - driver pre komunikaciu s OPL v Prahienke             *)
(* (c) Ales Kosice 1993,95,98 (ab)                                   *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{ DEFINE OPL__SAVE_STREAM}

{$X+,I-,S-,P-,F+,O+}


{$IFNDEF CAMUS_OLDI}
  {$O-}
  {$C FIXED PRELOAD PERMANENT}
{$ENDIF}


unit _CA_def;


interface

    uses   TypeDef,
           _EXT_def;


    const  CAMUS_PACKET_SIZE = 1024;
           CAMUS_BUFFER_SIZE = {$IFDEF DEBUG} 3 {$ELSE} 15 {$ENDIF};


           power_CAMUS : bool = true;


    {$IFNDEF CAMUS_OLDI}
     const  {SOH = #01;        start of heading }
            STX = '(';       { start of text }
            ETX = ')';       { end of text   }
            EOT = #10;

            HEARTBEAT = 'CH';


     type   PCAMUSpkt = ^TCAMUSpkt;
            TCAMUSpkt = record
              poc : word;
              buf : array[0..CAMUS_PACKET_SIZE-1] of char
            end;
    {$ENDIF}


    const  P_DEV_CAMUS : PP_EXT_ibuff = nil;


implementation


end.