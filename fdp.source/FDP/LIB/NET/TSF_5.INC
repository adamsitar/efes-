
function O_TSF.receive: bool;
   begin
     receive:= false;

     case tsf_stat of
       tsf_listen  : ;
       tsf_call    : ;
       tsf_receive :
       else Exit
     end
   end;

(*
(var pkt: TSFpacket; _local_name: Network_Service_Access_Point; _local_session_num: byte)

     init_call_pkt (pkt, _local_name);                  { not strictly necessary? - but good practice }
     init_data_pkt (pkt, _local_session_num);

     pkt.ncb.command:= NCB_RECEIVE;
     pkt.ncb.sl.length:= sizeof(pkt.conn.data);  { Note the use of the preamble in X25mode }

     res:= call_X25_API(pkt.ncb);
     if (res = 0) then
        begin
          X25_receive:= true;
        end
   end;
*)