    type   PEXTack = ^TEXTack;
           TEXTack = record
             head  : string[kod_HEAD];
             id    : string[kod_ID+length(icao_NXT)+kod_ID+kod_SQN];
             adr   : pchar;
             key   : pchar;
             typ   : TNETtyp;

             sent  : real;
             tmout : real
           end;

           POEXTack = ^OEXTack;
           OEXTack = object(TDynamic2)
             constructor Init (_items: word);
           end;


    function  eq_ack(ack1, ack2: PEXTack): bool; far;
    procedure new_ack(ack1, ack2: PEXTack); far;
    procedure disp_ack(ack: PEXTack); far;
