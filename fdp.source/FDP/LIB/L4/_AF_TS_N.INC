{$IFDEF SYNCHRONIZE_EXT}

 function  O_AFTN_TSGA.decode_NETpkt(var pkt: TNETpkt): bool;
    var    res : bool;
           fn  : string;
    begin
      if pkt.head.typ = 0 then decode_NETpkt:= false
      else if pkt.head.typ = spr_AFTN_PLN then
         begin
           decode_NETpkt:= true;
           flush_NETpkt_buff (pkt.pkt);
           decode_pkt_spr_pln (pkt);
         end
      else decode_NETpkt:= inherited decode_NETpkt(pkt)
    end;


 procedure O_AFTN_TSGA.decode_pkt_spr_pln(var pkt: TNETpkt);
     var   data : TSYNC_EXTpkt;
           res  : string;
     begin
      {$IFDEF PLN}
       decode_SYNC_EXTpkt(pkt,@data);
       _save_PLN (data.data,data.size,data.tit,data.fn,pkt.ods);
       disp_SYNC_EXTpkt(@data)
      {$ENDIF}
     end;

{$ENDIF}