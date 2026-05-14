{
  init_pkt, ...
     _local_name
     _name_num
     _local_session_num
}
procedure O_TSF.init_pkt(var pkt: TSFpacket);
    begin
      fillchar(pkt,sizeof(pkt),0);

      pkt.ncb.buffer   := @pkt.conn;
      pkt.ncb.lana_num := ADPTR_NUM;

      { name := _local_name; num := _name_num; lsn := _local_session_num }
    end;

{
  Initialise a pkt for use in CALL and LISTEN commands
}
procedure O_TSF.init_call_pkt(var pkt: TSFpacket; _local_name: Network_Service_Access_Point);
    begin
      init_pkt(pkt);
      pkt.ncb.name:= _local_name;
      pkt.conn.x_cr.window_size:= PKTWINDOWSZ;
      pkt.conn.x_cr.packet_size:= PKTPKTSZ;
      { Fill in some call packet details... }
    end;

{
  Initialise a pkt for use in data commands
}
procedure O_TSF.init_data_pkt(var pkt: TSFpacket; _local_session_num: byte);
    begin
      pkt.ncb.lsn := _local_session_num;
      pkt.ncb.buffer := @pkt.conn.data; {.preamble.mbit; }
      fillchar (pkt.conn.x_cr.name, NAME_SIZE, ' ')
    end;