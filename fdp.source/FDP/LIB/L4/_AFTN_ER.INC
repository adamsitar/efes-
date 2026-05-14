 procedure O_AFTN.process_ERR_HEAD (src: TPKT_SRC; data: pchars; size: word; res: string);
    var    prty: string;
    begin
     {$IFDEF TLG}
      if icao_HEAD_ERR and icao_HEAD_ERR_TLG then
         begin
           prty:= is_prty(data,size,res);
           _process_TLG (data,size,prty,true)
         end
      else
     {$ENDIF}
      inherited process_ERR_HEAD (src, data,size, res);
    end;

