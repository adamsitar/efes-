procedure IPX_init;
    var   s,t : string;
          i,j : int;
    begin
      write('Initializing IPX...  ');
      nd_buff := New(PBuffer,Init(nd_buff_size, sizeof(TIPXdpkt), false));
      rtr_buff:= New(PBuffer,Init(rtr_buff_size,sizeof(TIPXdpkt), false));

     {$IFDEF IPX3}
       system_buff:= New(PBuffer,Init(system_buff_size, sizeof(TIPXpkt_nd), false));
     {$ENDIF}

     {$IFDEF BROADCAST}
      New(inp_brd_buff);
      brd_buff:= New(PBuffer,Init(brd_buff_size,sizeof(TNETBpkt), false));
     {$ENDIF}

      IPX_initialized:= true;

    { inicializacia socketov a obsluznych rutin ------------------ }
      New(S_ECB,Init);
      S_ECB^.socket_number    := Local_socket;
      S_ECB^.ESR_adress       := nil;

      New(R_ECB[0],Init);
      R_ECB[0]^.socket_number := Broadcast_socket;
      R_ECB[0]^.ESR_adress    := @interrupt__IPX_broadcast;

      New(R_ECB[1],Init);
      R_ECB[1]^.socket_number := Peer_socket;
      R_ECB[1]^.ESR_adress    := @interrupt__IPX_node;

     {$IFDEF IPX3}
       New(R_ECB[2],Init);
       R_ECB[2]^.socket_number := System_socket;
       R_ECB[2]^.ESR_adress    := @interrupt__IPX_system;
     {$ENDIF}

    { otvorenie socketov ----------------------------------------- }
      IPX_open_socket(Local_socket);

      IPX_open_socket(Peer_socket);
      R_ECB[1]^.listen_for_packet;

     {$IFDEF IPX3}
       IPX_open_socket(System_socket);
       R_ECB[2]^.listen_for_packet;
     {$ENDIF}

     {$IFDEF BROADCAST}
       IPX_open_socket(Broadcast_socket);
       R_ECB[0]^.listen_for_packet;
     {$ENDIF}

    { inicializacia prenosovych liniek --------------------------- }
     {$IFDEF IPX0}
       for i:= 0 to maxIPX_NODEs-1 do
           if (i<>IPXnode) and IPXnodes[i]^.Connected then
              IPXnodes[i]^.Send(ipxVYZVA);
     {$ENDIF}

      {$IFDEF IPX3}
       IPX_read_system_mess;
      {$ENDIF}

      writeln('Done. IPX initialized.');
      Delay(2000);


     {$IFDEF ARCHIVE_NET_BIN}
      for j:= 0 to maxIPX_NODEs-1 do with IPXnodes[j]^ do
        begin
          s:= 'c:'+cstr(node,1);
          if connected then s:= s+' +,';
          s:= s+' n: '+name+', ';
          t:= ''; for i:= 0 to sizeof(TEthernetAdr)-1 do t:= t+ByteToHex(adr[i]);
          s:= s+', a: $'+delchar(t,['$']);
          s:= s+', p'+cstr(ord(pro),1);
          s:= s+', i'+strpas(info);
          archive_data (path_NET,get_ARCHfn(0)+'.'+extNET,@s[1],length(s),'-> ',true,false);
        end;
     {$ENDIF}

    end; { IPX_init }


procedure IPX_done;
    var   i: byte;
    begin
     {$IFDEF DEBUG_EXIT} writeln('IPX'); {$ENDIF}

      if IPX_installed and IPX_initialized then
         begin
          {$IFDEF BROADCAST}
             IPX_close_socket(Broadcast_socket);
          {$ENDIF}
          {$IFDEF IPX3}
             IPX_close_socket(System_socket);
          {$ENDIF}
           IPX_close_socket(Peer_socket);
           IPX_close_socket(Local_socket);
         end;

      if S_ECB<>nil then
         begin
          {$IFDEF IPX3}
            Dispose(R_ECB[2],Done);
          {$ENDIF}
           Dispose(R_ECB[1],Done);
           Dispose(R_ECB[0],Done);
           Dispose(S_ECB,Done)
         end;

     {$IFDEF BROADCAST}
       if inp_brd_buff<>nil then Dispose(inp_brd_buff);
       if brd_buff<>nil then Dispose(brd_buff,Done);
     {$ENDIF}
     {$IFDEF IPX3}
       if system_buff<>nil then Dispose(system_buff,Done);
     {$ENDIF}
      if rtr_buff<>nil then Dispose(rtr_buff,Done);
      if nd_buff<>nil  then Dispose(nd_buff,Done);

      for i:= 0 to maxIPX_NODEs-1 do Dispose(IPXnodes[i],Done);

      ExitProc:= SaveExit
    end;
