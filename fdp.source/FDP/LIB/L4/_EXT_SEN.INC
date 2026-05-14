{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   vysielanie dat
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

{  Imlementacne funkcia pre kontretny stream.
   Pri zmene hlavicky ...send... sa musi prekodovat TicaoNETdata
}

 function  O_EXT._send_pkt(typ: byte; adr: string; data: pchars; size: word): bool;
    begin
      writeln_pkt(data,size, arch_PKT_SEND,'', cl_s,false,true);
      _send_pkt:= true;
      Ts_:= AbsTime;
    end;

 function  O_EXT._send_npkt(typ: byte; adr: string; data: pchars; size: word): bool;
     var   idata : TEXT_EXTpkt;
           res : bool;
     begin
       idata.typ := typ;
       idata.adr := adr;
       idata.data:= data;
       idata.size:= size;
       if NETsend_data
                    (SERVERaddress,
                     spr_send_ext, @idata,@code_EXT_EXTpkt,nil{@codekey_EXTpkt},nil,
                     true,strpas(sync_info),nil, false,false, net_flag_SEND
                    ) = netRES_OK
               then
          begin
            writeln_pkt(data,size, arch_PKT_SENN,'', cl_s,false,true);
            Ts_:= AbsTime;
            _send_npkt:= true
          end
       else _send_npkt:= false
     end;

 function O_EXT.send_pkt(typ: byte; adr: string; data: pchars; size: word): bool;
    var   bres: bool;
          {f: text;}
    begin
      {vytvor_novy_subor('1.bak');
      assign(f,'1.bak'); append(f);
      writeln(f,init_str(data,size));
      close(f);}

      indicate_ext(1);
      if power then
         begin
           if is_distribute_pkt then bres:= _send_pkt(typ,adr,data,size)
           else bres:= _send_npkt(typ,adr,data,size);
           Ts_:= AbsTime;
         end
      else bres:= false;
      indicate_ext(-1);
      send_pkt:= bres
    end;


 procedure O_EXT._send_data (typh: byte;
                             adr,header: string;
                             data: pchars; size: word;
                             key: string; typd: TNETtyp
                            );
     begin
       {$IFDEF BACKUP} {$IFNDEF BACKUP_ACTIVE_2_EXT}
        if (SERVERstatus) then Exit;
       {$ENDIF} {$ENDIF}

       {$IFDEF MASTER} {$IFDEF BACKUP_ACTIVE_2_EXT}
        if (BACKUPstatus) then Exit;
       {$ENDIF} {$ENDIF}

       if send_pkt(typh,adr,data,size) and (key<>'') then ocakavany_LAM (header,adr,key,typd);
     end;

 procedure O_EXT.send_data (adr: string;
                            head,cislo,header_data: string;
                            data: pchars; size: word;
                            key: string; typ: TNETtyp
                           );
     begin
     end;

