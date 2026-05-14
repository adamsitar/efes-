{$IFDEF FPL0}

 procedure O_VERA._send_message_FPLC (head: Thead_ICAO; zmeneny: bool; var FPL: DcFPL);
     begin
       send_ESTc (FPL)
     end;

 procedure O_VERA._send_message_FPLM (head: Thead_ICAO; zmeneny: bool; var FPL: DmFPL);
     var   res  : string;
           ires : int;
     begin
       if not zmeneny then Exit;

       if    (head=hd_DEP)
          or (head=hd_ABI)
          or (head=hd_ACT)
          or (head=hd_CLR)
          or (head=hd_EST)
          then send_ESTm (FPL);
     end;

{$ENDIF}
