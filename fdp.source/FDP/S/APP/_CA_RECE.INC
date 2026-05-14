{$IFNDEF CAMUS_OLDI}
 function O_CAMUS.get_pkt_size(pkt: pointer): word;
    begin
      get_pkt_size:= TCAMUSpkt(pkt^).poc
    end;

 function O_CAMUS.get_pkt_data(pkt: pointer): pointer;
    begin
      get_pkt_data:= @TCAMUSpkt(pkt^).buf
    end;
{$ENDIF}

{ -------------------------------------------
   Spracovanie paketov od Externej linky
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
function  O_CAMUS.check_pkt_frame(data: pchars; size: word; var res: string): bool;
   begin
     check_pkt_frame:= true (*(data<>nil) and (size>1) and (data^[0]=STX) {$IFNDEF DEBUG} and (data^[size-1]=ETX) {$ENDIF}*)
   end;
