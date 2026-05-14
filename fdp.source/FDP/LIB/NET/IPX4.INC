procedure IPXsave(pkt: PIPXdpkt); far;
    begin
      if nd_buff<>nil then nd_buff^.save(pkt)
    end;

procedure RTRsave(pkt: PIPXdpkt); far;
   begin
     if rtr_buff<>nil then rtr_buff^.save(pkt);
   end;


function IPXread(var pkt: TIPXdpkt): bool;
   begin
     IPXread:= (nd_buff<>nil) and nd_buff^.read(@pkt)
   end;

function RTRread(var pkt: TIPXdpkt): bool;
   var   res: bool;
   begin
     res:= (rtr_buff<>nil) and rtr_buff^.read(@pkt);
    {$IFDEF ARCHIVE_NET} {$IFDEF CONNECT_TO_ASOC}
      if archive_NET_REC then archivuj_data(path_NET, get_ARCHfn(0)+'.'+extNET, @pkt,sizeof(pkt), archSYS,true,false);
    {$ENDIF}; {$ENDIF};
     RTRread:= res
   end;


{$IFDEF IPX3}
  procedure SYSTEMsave(pkt: PIPXdpkt); far;
     begin
       if (system_buff<>nil) then system_buff^.save(pkt)
     end;
{$ENDIF}

{$IFDEF BROADCAST}
  procedure IPXBsave(pkt: PNETBpkt); far;
     begin
       if brd_buff<>nil then brd_buff^.save(pkt)
     end;

  function IPXBread(var pkt: TNETBpkt): bool;
     begin
       IPXBread:= (brd_buff<>nil) and brd_buff^.read(@pkt)
     end;
{$ENDIF}
