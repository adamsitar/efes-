{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   kodovanie pre povodny protokol
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
procedure code_NETpkt_to_X25pkt (const Np: TNETpkt; var data: TX25data; var size: word);
    var   Rp : TRTRpkt_bin;
          whole: bool;
    begin
      {move(Np.head,data,sizeof(Np.head));
      size:= minimum(Np.pkt.dlz,sizeof(data)-sizeof(Np.head));
      move(Np.pkt.data^,data[sizeof(Np.head)],size);
      size:= size+sizeof(Np.head)}
      size:= Minimum(Minimum(code_NETpkt_to_RTRpkt (Np, Rp, nil,rpRT_, whole), sizeof(data)),size_of_NETdata);
      move(Rp,data, size)
    end;

procedure code_NET0pkt_to_X25pkt (const Np: TNET0pkt; var data: TX25data; var size: word);
    begin
      size:= minimum(sizeof(data),sizeof(Np.head)+Np.head.dlz);
      move(Np,data,size)
    end;


procedure decode_X25pkt_to_NETpkt (data: TX25data; size: word; var Np: TNETpkt);
    var   Rp  : TRTRpkt_bin;
          err : bool;
    begin
      {fillchar(Np, sizeof(Np),0);
      move(data, Np.head, sizeof(Np.head));
      Np.pkt.dlz:= size-sizeof(Np.head);
      new_NETpkt_data(@?data[sizeof(Np.head)],Np.pkt.dlz, Np.pkt)}
      move(data,Rp, minimum(size,sizeof(Rp)));
      decode_RTRpkt_to_NETpkt (Rp, Np, err)
    end;

procedure decode_X25pkt_to_NET0pkt (data: TX25data; size: word; var Np: TNET0pkt);
    begin
      Move(data,Np,minimum(size,sizeof(Np)))
    end;


{ תתתתתתתתתתתתתתתת
   nizsia uroven
  תתתתתתתתתתתתתתתת
}

function X25_send(_to,_from: TX25name; size: int; buff: pointer): int;
   begin
     X25_send:= x25NOT_INITIALIZED;
    {$IFDEF _X25}
      X25_send:= X25_net^.send_DATA(_to,_from, size,buff)
    {$ENDIF}
  end; { X25_send }

function X25_read(var PACKET: X25_INPUT_BUFFER): bool;
   begin
    {$IFDEF _X25}
      X25_read:= X25_net^.read_PACKET(PACKET)
    {$ELSE}
      X25_read:= false
    {$ENDIF}
   end;


{ תתתתתתתתתתתתתתתתתת
   aplikacna uroven
  תתתתתתתתתתתתתתתתתת
}
{ funkcie transformuju medzi starym a novym protokolom,
  neskor sam moze dolozit detekcia protokolu
}
function X25read(var pkt: TNETpkt): bool;
   var   PACKET : X25_INPUT_BUFFER;
         pkt0   : TNET0pkt;
         ind    : int;
   begin
     X25read:= false;
     while X25_read(PACKET) do
       begin
         fillchar(pkt,sizeof(pkt),0);
         ind:= X25nodes^.isX25chan(PACKET.CHAN,1);
         if is_proL(pkt.ods) {if (ind>=0) and (X25nodes^.NODE^[ind]^.PROL)} then
            begin
              decode_X25pkt_to_NETpkt (PACKET.DATA,PACKET.SIZE, pkt);
            end
         else begin
                decode_X25pkt_to_NET0pkt (PACKET.DATA,PACKET.SIZE, pkt0);
                NET0pkt_NETpkt (pkt0,pkt)
              end;
         X25read:= true
       end
   end; { X25read }


function X25send(pkt: TNETpkt; adr: TX25name): int;
   var   data : TX25data;
         size : word;
         pkt0 : TNET0pkt;
         n,a  : int;
   begin
    {$IFDEF _X25}
      if (adr<>X25address) then
         begin
           n:= isX25name(adr);
           a:= isX25adr (adr,0);

           {$IFDEF X25} {$IFNDEF BRIDGE}
             if (n=-1) and (a=-1) and (X25bridge>-1) then adr:= X25nodes^.NODE^[X25bridge]^.NAME;
           {$ENDIF} {$ENDIF}
           a:= isX25name(adr);
           if a<0 then a:= isX25adr(adr,0);

           if (a>=0) and (X25node>-1) then
              begin
                if is_proL(pkt.adr) {if (a>=0) and (X25nodes^.NODE^[a]^.PROL)} then
                   begin
                     code_NETpkt_to_X25pkt (pkt, data,size)
                   end
                else begin
                       NETpkt_NET0pkt (pkt,pkt0);
                       code_NET0pkt_to_X25pkt (pkt0, data,size)
                     end;
                with X25nodes^ do
                     X25send:= X25_net^.send_DATA(NODE^[a]^.ADR,
                                                  NODE^[X25node]^.ADR,
                                                  size,@data
                                                 )
              end
           else X25send:= x25BAD_ADDR
          end
       else X25send:= x25BAD_ADDR
    {$ELSE}
      X25send:= x25NOT_INITIALIZED
    {$ENDIF}
  end; { X25send }

procedure X25sending;
    begin
     {$IFDEF _X25}
       X25_net^.send_packets   { posiela nevyslane data }
     {$ENDIF}
    end;
