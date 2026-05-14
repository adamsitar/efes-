procedure O_AFTN.send_pkt(typ: byte; adr: string; data: pchars; size: word);
    var   b    : pchars;
          p,pi : word;
          eop  : string;
          cl   : byte;
    begin
     (*
      if not (msAFTNdata(typ) in [msHB,msAUP,msRTZ]) then eop:= ETX+check_sum(data,size)
      else eop:= '';
      p:= 1+1+size+length(eop)+1;  { SOH+typp+size+eop+EOT  }
      if p<=size then Exit;        { pretecenie }

      getmem(b,p);
      b^[0]:= SOH;
      if (msAFTNdata(typ) in [msAUP,msRTZ]) then b^[1]:= QRY else b^[1]:= MES;
      move(data^,b^[2],size);           pi:= 2+size;
      move(eop[1],b^[pi],length(eop));  inc(pi,length(eop));
      b^[pi]:= EOT;
      SendCOMib(AFTNCOM, pbytes(b), p);
      if (msAFTNdata(typ)<>msHB) or writeln_AFTN_HeartBeat then
         begin
           writeln_pkt(b,p,arch_PKT_SEND,'',cl_s)
         end;
      freemem(b,p);
      Ts:= absTime
     *)
    end;

procedure O_AFTN.send_data(adr: TNETadr; hd,hd_data: string; data: pchars; size: word; key: string);
    var   b    : pchars;
          p,pi : word;
          i    : int;
          head : string;
          eop  : string;
    begin
      (*
      i:= head_type(hd);
      if i<0 then Exit;

      head:= icao_STD+code_head(hd,hd_data, data);
      eop:= icao_END;

      p:= length(head)+size+length(eop);    { typ + head + ETX + chks }
      if p<=size then Exit;                 { pretecenie }

      getmem(b,p);
      move(head[1],b^[0],length(head)); pi:= length(head);
      move(data^,b^[pi],size);          inc(pi,size);
      move(eop[1],b^[pi],length(eop));  inc(pi,length(eop));
      send_pkt(i, adr,b,p);
      freemem(b,p)
      *)
    end;
