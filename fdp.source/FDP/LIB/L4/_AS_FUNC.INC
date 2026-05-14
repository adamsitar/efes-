{$IFDEF FPL0}

  procedure O_ASOC._send_message_FPLC(head: Thead_ICAO; zmeneny: bool; var FPL: DcFPL);
      begin
        send_CPLc(FPL);
      end;

{$ENDIF}
