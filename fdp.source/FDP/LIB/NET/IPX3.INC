function ipx_send(node: int; size: word; buff: pointer): int;
   var   res,c : int;
   begin
    {$IFDEF IPX}
      if (node>-1) and (node<>IPXnode) {and (IPXnodes[node]^.Connected)} then with IPXnodes[node]^ do
         begin
          { IFDEF IPX0
            c:= ipx_REPEAT;
            ENDIF}
           res:= SendData(buff, size);
          { IFDEF IPX0
            while c>0 do
              begin
                Wait;
                if (TrasaOK and SendOK) then break;
                dec(c);
                res:= SendData(buff, size)
              end;
            ENDIF}
           ipx_send:= res
         end
      else ipx_send:= ipxBAD_ADDR
    {$ELSE}
      {$IFDEF DEMO}
      if (node>-1) and (node<>IPXnode) and (node<>BRIDGEipx) and (IPXnodes[node]^.Connected) then with IPXnodes[node]^ do
         ipx_send:= ipxRES_OK
      else
      {$ENDIF} ipx_send:= ipxBAD_ADDR
    {$ENDIF}
   end;


{function IPXsend(adr: TNETadr; size: word; buff: pointer): int;
}
function IPXsend (const pkt: TNETpkt; adr: TNETadr) : int;
   var   Lp: TIPXdpkt;
         node: int;
   begin
     code_NETpkt_to_ipxIPXpkt (pkt,Lp);
     if cut_(adr)<>'' then
        begin
          node:= isIPXname(adr)
         {$IFNDEF BRIDGE};
           if node=-1 then node:= BRIDGEipx
         {$ENDIF}
       end
     else node:= BRIDGEipx;
     IPXsend:= ipx_send(node, Lp.size, @Lp.data)
   end;


procedure IPXstatus;
    var   i: int;
    begin
     {$IFDEF IPX0}
       if IPX__HEARTBEAT<61 then for i:= 1 to maxIPX_NODEs-1 do IPXnodes[i]^.Test;
     {$ENDIF}
     {$IFDEF IPX3}
       IPX_check_system_mess;
     {$ENDIF}
    end;
