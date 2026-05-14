function O_ASOC._send_pkt (typ: byte; adr: string; data: pchars; size: word): bool;
   begin
     _send_pkt:= false;
     if NODE=-1 then Exit;
     NETsend_msg (NODEs^[NODE].desc.adr, spr_ASOC, data,size, false,net_flag_SEND);
     _send_pkt:= O_EXT._send_pkt(typ,adr,data,size)
   end;


{$IFDEF DEBUG}
  {$I _ITA2_pkt.inc}
  {$I _ITA2T_pkt.inc}
  {$I _IA5_pkt.inc}
{$ENDIF}

procedure O_ASOC.send_data (adr: string; head,cislo,header_data: string;
                            data: pchars; size: word;
                            key: string; typ: TNETtyp
                           );

    var   pkt,epkt,bpkt : pchars;
          dlz,edlz,bdlz : word;
          header   : string;
          bres     : bool;
          res,s    : string;
          i        : int;
    begin
     { Datovy paket sa koduje podla typu spravy,
       ak je to ICAO sprava - ako paket AFTN
                OLDI  -//-  - ako paket OLDI
     }
      i:= _icao_head_type(head,res);
      if i<0 then Exit;

      pkt := nil; dlz := 0;
      epkt:= nil; edlz:= 0;
      bpkt:= nil; bdlz:= 0;

      header:= _code_header(head,'','',cislo,header_data,data,header);

      if msData(i) in [msFPL..msEST] then
         begin
           if code_ICAO_pkt ('','',header, data,size, epkt,edlz) then
              begin
                s:= ADR_O+NULL;
                if IA5 then bres:= code_IA5_pkt
                                        (
                                         CHNL_I,CISLO_SPRAVY,tlgFF,@s[1],ADR_I,
                                         epkt,edlz,
                                         pkt,dlz
                                        )
                else if ITA2_ASCII then
                        begin
                          bres:= code_ITA2T_pkt
                                        (
                                         CHNL_I,CISLO_SPRAVY,tlgFF,@s[1],ADR_I,
                                         epkt,edlz,
                                         pkt,dlz
                                        )
                        end
                else begin
                       bres:= code_ITA2_pkt
                                     (
                                      CHNL_I,CISLO_SPRAVY,tlgFF,@s[1],ADR_I,
                                      epkt,edlz,
                                      pkt,dlz,
                                      ITA2_BIN,ITA2_BITS,
                                      bpkt,bdlz
                                     );
                       if bres and ITA2_BIN then
                          begin
                            freemem(pkt,dlz);
                            pkt:= bpkt; dlz:= bdlz;
                            bpkt:= nil; bdlz:= 0
                          end;
                     end;
                  freemem(epkt,edlz);
                end
           else bres:= false
         end

      else if msData(i) in [msABI..msREV] then
         begin
           bres:= code_OLDI_pkt (header, data,size, pkt,dlz)
         end

      else bres:= false;

      if bres then
         begin
           _send_data (byte(hdData),adr,header,pkt,dlz,key,typ);
           freemem(pkt,dlz);
           pkt:= nil; dlz:= 0
         end
    end;
