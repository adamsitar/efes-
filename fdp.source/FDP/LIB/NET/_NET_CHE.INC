procedure NET_check0;
    begin
      if @SaveMain0<>nil then SaveMain0;
      if not _NET_EN then Exit;

    { nacitanie dat zo vstupnych bufferov }
      NET^.read_inp_buff;

    { spracovanie prijatych potvrdeni, aby im nevyprsal TimeOut }
      NET^.read_net_buff_ack;

    { presmerovanie
    } NET^.read_net_reroute_pkt;
    end; { NET_check0 }


procedure NET_checkA;
    begin
      if @SaveMainA<>nil then SaveMainA;
      if not _NET_EN then Exit;

    { nacitanie dat }
      NET^.read_net_buff_data;
    end; { NET_check }


procedure NET_checkD;
    begin
      if @SaveMainD<>nil then SaveMainD;
      if not _NET_EN then Exit;

    { nacitanie dat docasne ulozenych v subore }
      NET^.read_net_file_data;

    { kontrola na time_out odoslanych sprav }
      NETack^.check;

    { kontrola stavu uzlov }
      NET^.check_nodes;
    end; { NET_check }


