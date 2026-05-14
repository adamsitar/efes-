function  O_VERA._send_pkt(typ: byte; adr: string; data: pchars; size: word): bool;
    var   bres : bool;
          ires : int;
          b : pchars;
          p : int;
    begin
      bres:= true;
      b:= data;
      p:= size;

      if power then
         begin
           {$IFDEF UDP}
            ires:= udp_send (UDP_PORT_VERA,false,'',VERAadr_ip, p,b);
            bres:= ires=netRES_OK;
           {$ENDIF}
           if bres then writeln_pkt(b,p,arch_PKT_SEND,'',cl_s,false,false)
           else process_ERR_DATA (src_ext,b,p,err_ext_packet_not_sent+' ('+cstr(ires,1)+')', false,false,false)
         end;

      Ts_:= AbsTime;
      _send_pkt:= bres {true}
    end;


{ odoslanie datovieho paketu
}
procedure O_VERA.send_data (adr: string; head,cislo,header_data: string; data: pchars; size: word; key: string; typ: TNETtyp);
    var   pkt : pchars;
          dlz : word;
          header : string;
    begin
      if code_ICAO_pkt ('','',_code_header(head,'','',cislo,header_data,data, header), data,size, pkt,dlz) then
         begin
           _send_data (0,adr,header,pkt,dlz,key,typ);
           freemem(pkt,dlz)
         end
    end;
