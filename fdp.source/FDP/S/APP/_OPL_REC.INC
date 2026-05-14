 function  O_OPL.read_inp_buff: bool;
    var    res    : bool;
           {$IFDEF OPL_EXT_UDP} {$IFDEF UDP}
            from   : T_IPaddress;
           {$ENDIF} {$ENDIF}

           data: pbytes;
           size: int;
           bres: bool;
    begin
      read_inp_buff:= false;

     {$IFDEF OPL_EXT_UDP} {$IFDEF UDP}
       if not power_OPL_udp then Exit;

       if UDP_PORT_OPL.desc=-1 then Exit;
       { nacitanie z portu
       } if net_is_data(UDP_PORT_OPL.desc,UDPpkt^.buf,sizeof(UDPpkt^.buf),from)>0 then
            begin
              UDPpkt^.poc:= net_read(UDP_PORT_OPL.desc, UDPpkt^.buf,sizeof(UDPpkt^.buf), from, NET_FLG_NONBLOCKING);
              if {from-...} UDPpkt^.poc>0 then
                 begin
                   ibuff^.save(UDPpkt);
                   read_inp_buff:= true;
                 end;
            end;
      {$ENDIF} {$ENDIF}
    end;


 function O_OPL.get_pkt_size(pkt: pointer): word;
    begin
      get_pkt_size:= TOPLpkt(pkt^).poc
    end;

 function O_OPL.get_pkt_data(pkt: pointer): pointer;
    begin
      get_pkt_data:= @TOPLpkt(pkt^).buf
    end;


{ -------------------------------------------
   Spracovanie paketov od Externej linky
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 function O_OPL.is_master_line: bool;
    var   bres: bool;
    begin
      {$IFDEF SERVER_2}
       { nelogicke, ale tvrde nastavenie, aby backup server
         prijimal udaje od async, pretoze po async do master
         nechodia
       }
        if power_OPL_async then bres:= false
        else bres:= inherited is_master_line;
      {$ELSE}
        bres:= inherited is_master_line;
      {$ENDIF}
      is_master_line:= bres;
    end;


 function  O_OPL.check_pkt_frame(data: pchars; size: word; var res: string): bool;
    begin
      check_pkt_frame:= (data<>nil) and (size>1) and (data^[0]=SOH) {IFNDEF DEBUG and (data^[size-1]=EOT) ENDIF}
    end;

