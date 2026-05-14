 function O_CAMUS.decode_data (data: pchars; size: word;
                               header: string;
                               var head: string;
                               var res: string
                              ): bool;
    var   bres : bool;
          i : int;
          s : string;
          {$IFDEF FPL4} {$IFDEF FPL0}
           FPL  : PFPL4;
          {$ENDIF} {$ENDIF}
    begin
      decode_data:= false;

      {$IFNDEF CAMUS_OLDI}
       if head=HEARTBEAT then Exit;
      {$ENDIF}

      { kontrola na prazdne polia
      } i:= 1; while (i<size) do
         if (data^[i-1]=icao_ARR) and (data^[i]=icao_ARR) then
            begin
              res:= 'Empty array "--" in message.';
              Exit
            end
         else inc(i);

      i:= _icao_head_type(head,res);
      if i<0 then
         begin
           if not process_all_msg then res:= err_ext_unprocessed_message_type;
           Exit
         end;

      {$IFDEF FPL4} {$IFDEF FPL0}
       new_FPL4_(nil,FPL);
      {$ENDIF} {$ENDIF}
      bres:= false;
      case msData(i) of
        msLAM   : bres:= decode_LAM(data,size, header, res);

        {
        msACT   : decode_data:= decode_ACT(data,size, FPL^, res);
        msABI   : decode_data:= decode_ABI(data,size, head);
        msPAC   : decode_data:= decode_PAC(data,size, head);
        msREV   : decode_data:= decode_REV(data,size, FPL^, res);
        }

        {$IFDEF FPL4} {$IFDEF FPL0}
         msCPL   : decode_CPL(data,size, FPL^, res);   { vysledok musi byt false }
         msEST   : bres:= decode_EST(data,size, FPL^, res);
        {$ENDIF} {$ENDIF}

        else if not process_all_msg then res:= err_ext_unprocessed_message_type
      end;
      if res<>'' then bres:= false;
      {$IFDEF FPL4} {$IFDEF FPL0}
       disp_FPL4_(FPL);
      {$ENDIF} {$ENDIF}

      {$IFDEF CONNECT_TO_FDPOX} {$IFDEF UDP}
       {if power_FDPOX then}
           begin
             udp_send (UDP_PORT_FDPOX,false,'',FDPOXadr_ip, size,data);
             {_writeln_pkt (data,size,'FDP','',lightgreen,false);}
           end;
      {$ENDIF} {$ENDIF}

      decode_data:= bres;
    end;

