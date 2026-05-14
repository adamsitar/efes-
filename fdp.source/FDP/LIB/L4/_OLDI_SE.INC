{ odoslanie pola dat do X25 a jeho archivovanie
}
function O_OLDI._send_pkt (typ: byte; adr: string; data: pchars; size: word): bool;
    var  ms : msSystem;
         bres: bool;
    begin
      _send_pkt:= false;
      ms:= msSystem(typ);
      if (stat<>DATA_READY_STATE) and (ms in [msHeartBeat,hdData]) then Exit;

      bres:= true;
      {$IFDEF _X25}
       if (X25_net<>nil) {and (X25adr_REMOTE_<>'')} then X25_net^.send_data(X25adr_REMOTE_,X25adr_THIS, size,data);
      {$ENDIF}
     { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
       nastavenie vysielacieho timera
       תתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
     } handle_OLDI_event(L_data,nil);

      O_EXT._send_pkt(typ,adr,data,size);
      _send_pkt:= bres
    end;

{ odoslanie pkt typu ms
}
procedure O_OLDI.send_pkt_(ms: msSystem; adr: string; data: pchars; size: word);
    begin
      if ms in [msStartUp,msHeartBeat,msShutDown] then
         begin
           data:= pchars(headSystem[ms]);
           size:= strlen(headSystem[ms])
         end;
      send_pkt(byte(ms),adr, data,size)
    end;


{ odoslanie datovieho paketu
}
procedure O_OLDI.send_data (adr: string; head,cislo,header_data: string; data: pchars; size: word; key: string; typ: TNETtyp);
    var   pkt : pchars;
          dlz : word;
          header : string;
    begin
      if code_OLDI_pkt (_code_header(head,'','',cislo,header_data,data, header), data,size, pkt,dlz) then
         begin
           _send_data (byte(hdData),adr,header,pkt,dlz,key,typ);
           freemem(pkt,dlz)
         end
    end;
