{
  Priklady sprav a ich potvrdeni:

  ú $(ESTMI/PL001-KAL511...
 ÿ  $(LAMMI/PL111PL/MI792)

  ú $(ASMPL/MI432-...
 ÿ  $(LAMMI/PL111PL/MI432)

  ú #AUP/001120(01-LKR35... )9999
 ÿ  #(LAMMI/PL111/AUP/001120/9999)

  ú #RTZ...4152
 ÿ  #(LAMMI/PL111/RTZ/9999)
}


{ STX+1..ETX-1
}
function check_sum(b2: pchars; p2: word): string;
   var   sum : long;
         i   : word;
   begin
     sum:= 0;
     i:= 0;  while (i<p2) and (b2^[i] in[SOH,QRY,MES,STX]) do inc(i);
     while (i<p2) do
       begin
         if (b2^[i] in [ETX,EOT]) then break;
         sum:= sum + ord(b2^[i]);
         inc(i)
       end;
     check_sum:= IntToStr(sum,4,0)
   end;


function  O_OPL._send_pkt(typ: byte; adr: string; data: pchars; size: word): bool;
    var   b    : pchars;
          p,pi : word;
          eop  : string;
          cl   : byte;

          ires : int;
          sres : string;
          bres : bool;

    begin
      bres:= true;

      if not (msOPLdata(typ) in [msHB,msAUP,msRTZ]) then eop:= ETX+check_sum(data,size)
      else eop:= '';
      p:= 1+1+size+length(eop)+1;  { SOH+typ+size+eop+EOT  }
      if p<=size then Exit;        { pretecenie }

      getmem(b,p);
      b^[0]:= SOH;
      if (msOPLdata(typ) in [msAUP,msAUM,msRTZ]) then b^[1]:= QRY
      else b^[1]:= MES;

      move(data^,b^[2],size);           pi:= 2+size;
      move(eop[1],b^[pi],length(eop));  inc(pi,length(eop));
      b^[pi]:= EOT;

      sres:= err_ext_packet_not_sent;

      {$IFDEF OPL_EXT_ASYNC}
       if power_OPL_async then bres:= SendCOMib (asyncCOM, pbytes(b), p, false)
       else sres:= NULL;
      {$ENDIF}

      {$IFDEF OPL_EXT_UDP} {$IFDEF UDP}
       if power_OPL_udp then
          begin
            ires:= udp_send (UDP_PORT_OPL,false,'',OPLadr_ip, p,b);
            bres:= ires=netRES_OK;
            if not bres then sres:= sres++' ('+cstr(ires,1)+')';
          end
       else sres:= NULL;
      {$ENDIF} {$ENDIF}

      if sres<>NULL then
         if bres then
            begin
              if (msOPLdata(typ)<>msHB) or writeln_OPL_HeartBeat then writeln_pkt(b,p,arch_PKT_SEND,'',cl_s,false,false)
            end
         else process_ERR_DATA (src_ext,b,p,sres, false,false,false);

      Ts_:= AbsTime;
      freemem(b,p);
      _send_pkt:= true
    end;


procedure O_OPL.send_data (adr: string; head,cislo,header_data: string;
                           data: pchars; size: word;
                           key: string; typ: TNETtyp
                          );
    var   b    : pchars;
          p,pi : word;
          i    : int;
          header : string;
          eop  : string;
    begin
      i:= _icao_head_type(head,eop);
      if i<0 then Exit;

      if (msOPLdata(i) in [msAUP,msAUM,msRTZ]) then
         begin
           header:= head;
           if header_data<>''then header:= header+icao_NXT+header_data;
           eop:= '';
         end
      else begin
             header:= icao_STD+_code_header(head,'','',cislo,header_data,data,header);
             eop:= icao_END;
           end;

      p:= length(header)+size+length(eop);  { typ + head + ETX + chks }
      if p<=size then Exit;                 { pretecenie }

      getmem(b,p);
      move(header[1],b^[0],length(header)); pi:= length(header);
      move(data^,b^[pi],size);              inc(pi,size);
      move(eop[1],b^[pi],length(eop));      inc(pi,length(eop));
      _send_data (i,adr,header,b,p,key,typ);
      freemem(b,p)
    end;



{ Pr. LAMMI/PL001PL/MI232

function  O_OPL._LAM_data(header: string): string;
   begin
     _lam_data:= copy(header,kod_HEAD+1,length(header)-kod_HEAD);
   end;
}
{ I str9.inc}  { spracovanie znakov z pola }

procedure O_OPL.send_LAM (data: pchars; size: word; header: string);
    var   res, head,adr,ods,cislo, header_data : string;
          bres : bool;
    begin
      res:= '';
      head:= get_str_(data,size, 1, [SOH,STX], bres, sizeof(header)-1);
      if (head='') then Exit;

     { $(FPLPL/MI792-F4205-... }
      if (MES = head[1]) and (icao_STD = head[2]) then
         begin
           if not _decode_header (header, head,adr,ods,cislo, header_data, @res) then Exit;
           header_data:= copy(header,kod_HEAD+1,length(header)-kod_HEAD);
         end

     { #AUP/001120(01-LKR35... }
      else if     (head[1] in [QRY,MES])
              and (length(getstr(head,1,[icao_NXT]))=1+kod_HEAD) then
         begin
           ods:= NODE_REMOTE;
           header_data:= icao_NXT+copy(header,2,length(header)-1);
           if data^[size-1] = EOT then cislo:= get_str (data,size,2,[ETX,EOT],sizeof(cislo)-1)
           else cislo:= '';
           if cislo<>''then header_data:= header_data+icao_NXT+cislo;
         end;

      if (ods<>'') and (ods<>NODE_THIS) then send_data (NODE_REMOTE,hd_LAM,'',header_data, nil,0, '',0)
      else writeln_pkt(@head[1],length(head), arch_ERR,err_ext_uncorrect_address+' ('+ods+')...',cl_ERR,false,false)
    end;
