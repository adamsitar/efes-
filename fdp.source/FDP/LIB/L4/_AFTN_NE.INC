{$IFDEF SYNCHRONIZE_EXT}

 function  O_AFTN.decode_NETpkt (var pkt: TNETpkt): bool;
    begin
      if pkt.head.typ = 0 then decode_NETpkt:= false
      else if pkt.head.typ = spr_tlg then
         begin
           decode_NETpkt:= true;
           flush_NETpkt_buff (pkt.pkt);
           decode_pkt_spr_tlg (pkt)
         end
      else decode_NETpkt:= inherited decode_NETpkt(pkt)
    end;



 procedure O_AFTN.process_pkt_spr_ed(var data: TSYNC_EXTpkt);
     begin
       _save_txt_file (data.fn{_fn_data(data.data,data.size)}, data.tit, data.data,data.size, false)
       {_process_TLG (data.data,data.size,'',false)}
     end;


 procedure O_AFTN.decode_pkt_spr_tlg (var pkt: TNETpkt);
     var   data : TSYNC_EXTpkt;
     begin
       decode_SYNC_EXTpkt(pkt,@data);
       _process_TLG (data.data,data.size,'',false {is_distribute_pkt,from});
       disp_SYNC_EXTpkt(@data)
     end;

{$ENDIF}