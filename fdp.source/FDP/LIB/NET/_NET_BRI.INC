function make_NETadr(var adr: TNETadr): int;
   begin
    {$IFDEF _X25}
     if is_NETadr(adr)<0 then make_NETadr:= is_X25_LANadr(adr)
     else
    {$ENDIF}
     make_NETadr:= netADDR_OK;
   end;


{ Pokuka, ci moze ku dakemu moze poslat paket,
  kedz nezna jak ho poslac na jeho adresu
}
function is_bridge: bool;
   begin
     is_bridge:=         false
                        {$IFDEF X25} {$IFNDEF BRIDGE}
                     or (X25bridge>-1)
                        {$ENDIF} {$ENDIF}
                        {$IFDEF PCTCP}
                     or (BRIDGEipadr<>'')
                        {$ENDIF}
                        {$IFDEF IPX}
                     or ((BRIDGEipx>-1) and (BRIDGEipx<>IPXnode) and (IPXnodes[BRIDGEipx]^.Connected))
                        {$IFDEF RTR}
                     or ((ROUTERipx>-1) and (RBRIDGEadr>0))
                        {$ENDIF}
                        {$ENDIF}
                        {$IFDEF COM}
                     or  (CBRIDGEadr<>'')
                        {$ENDIF}
   end;


{ Kontrola, ci adresa je v sieti X25.
  Siet X25 moze byt imitovana i sietou LAN, ak su rovnake adresy
  Protokol X25 dovoluje adresovat pre cfg nezname stanice
}
{$IFDEF _X25}

 function is_X25_LANadr(var adr: TNETadr): int;
    var   X25adr,LANadr     : TNETadr;
          NETnd,X25nd,IPXnd : int;
          res               : int;

    begin
      X25adr:= NETadr_wan(adr);
      LANadr:= NETadr_lan(adr);

      x25nd := isX25name(X25adr);

      if (X25nd=-1) and empty_str(LANadr) then
         begin
         { --------------------------------------------------------------------
            Len jedna polozka v adrese, a nie adresa X25, je to adresa v LAN ?
         }
         {$IFDEF IPX}
           if isIPXname(X25adr)>-1 then
              begin
                LANadr:= X25adr; X25adr:= '';
                X25nd:= isX25name(X25adr);
                if X25adr='' then X25adr:= NETadr_wan(NETaddress)
              end
         {$ENDIF}
         {$IFDEF PCTCP}

         {$ENDIF}
         end;

      if (X25nd>-1) then

         if is_this_X25node(X25adr) then
            begin
            { ----------------------------------------
               posiela sa cez LAN v ramci uzla X25adr
              ----------------------------------------
            }
              if (x25nd<>X25node) and (LANadr='') then
                 begin
                 { -------------------------------------------------------
                    imitacia X25 v LAN, bola detekovane rovnaka adr uzla,
                    posiela sa v LAN, napr. StrRLP a 150 su totozne X25
                    adresy
                 }
                   LANadr:= X25adr
                 end;

              NETnd:= is_NETadr(NETadr(X25adr,LANadr));
             {$IFDEF IPX}
               IPXnd:= isIPXname(LANadr);
             {$ENDIF}

              if   false then

              { UDP ? ............ }
             {$IFDEF PCTCP}
              else if (NETnd>-1) and (NODEs^[NETnd].desc.adrip<>0) then res:= netADDR_OK
             {$ENDIF}

              { IPX ? ............ }
             {$IFDEF IPX}
              else if (IPXnd>-1) then
                      if (IPXnd<>IPXnode) then res:= netADDR_OK
                      else res:= netSELF_ADDR
             {$ENDIF}

              { BRIDGE ? ......... }
              else {$IFDEF BRIDGE}
                     res:= netBAD_ADDR
                   {$ELSE}
                     if is_bridge then res:= netADDR_OK
                     else res:= netBAD_ADDR
                   {$ENDIF}
            end

         else begin
              { ----------------------------------
                 cez X25 alebo komnikacny pocitac
                ----------------------------------
              }
               {$IFDEF X25}
                 res:= netADDR_OK
               {$ELSE}
                  {$IFDEF BRIDGE}
                    res:= netADDR_OK   { pre ladenie bez X25ky }
                  {$ELSE}
                    if is_bridge then res:= netADDR_OK
                    else res:= netBRIDGE_MIS
                  {$ENDIF}
               {$ENDIF}
              end

      else { --------------------------------------
              presmerovanie na komunikacny pocitac
             --------------------------------------
           }
            {[1]}
             if     (is_bridge)
                 or ((X25adr = NETadr_wan(NETaddress)) {$IFDEF IPX} and (isIPXname(LANadr)>-1) {$ENDIF})
                    then res:= netADDR_OK
             else res:= x25BAD_ADDR;

      if NETres(res) then adr:= NETadr(X25adr,LANadr);
      is_X25_LANadr:= res
    end;

{$ENDIF}

{ odoslanie pripraveneho paketu ma X25/IPX/UDP/BRIDGE
}
function BRIDGEsend(const pkt: TNETpkt; flag: word): int;
   begin
     {$IFDEF X25}
       if (X25bridge>-1) and (not is_this_X25node(pkt.adr)) then
                BRIDGEsend:= X25send(pkt, NETadr_wan(BRIDGEadr)) {sizeof(pkt^.head)+pkt^.head.dlz}
       else
     {$ENDIF}
     {$IFDEF PCTCP}
       if (BRIDGEipadr<>'') then
                BRIDGEsend:= UDBsend(pkt, BRIDGEipadr, net_flag_SEND)
       else
     {$ENDIF}
     {$IFDEF IPX}
       if (BRIDGEipx>-1) and (BRIDGEipx<>IPXnode) then
                BRIDGEsend:= IPXsend(pkt, BRIDGEadr) {ipx_send(BRIDGEipx, sizeof(pkt^.head)+pkt^.head.dlz, pkt)}
       else
     {$IFDEF RTR}
       if (ROUTERipx>-1) and (RBRIDGEadr>0) then
                BRIDGEsend:= RTBsend(pkt)
       else
     {$ENDIF}
     {$ENDIF}
     {$IFDEF COM}
       if (CBRIDGEadr<>'') then
                BRIDGEsend:= COMsend(pkt)
       else
     {$ENDIF}
                begin
                  BRIDGEsend:= netNOT_SENDED;
                end
   end;


{$IFDEF _X25}

 function X25_LANsend(var pkt: TNETpkt; flag: word): int;
    var   adr : TNETadr;
          nd  : int;

    begin
      if not NETres(make_NETadr(pkt.adr)) then
         begin
           X25_LANsend:= netBAD_ADDR;
         end
      else begin
             X25_LANsend:= netNOT_SENDED;
             nd:= is_NETadr(pkt.adr);

             if is_this_X25node(pkt.adr) then
                begin
                { ------------------
                   posiela sa v LAN
                  ------------------
                }
                 {$IFDEF PCTCP}
                   if (nd>-1) and (NODEs^[nd].desc.adrip<>0) then
                      begin
                        X25_LANsend:= UDBsend(pkt, pkt.adr, flag);
                        Exit
                      end;
                 {$ENDIF}

                 {$IFDEF IPX}
                   adr:= NETadr_lan(pkt.adr);
                   if (isIPXname(adr)>-1) then
                      begin
                        X25_LANsend:= IPXsend(pkt, adr);
                        Exit
                      end;
                 {$ENDIF}

                  X25_LANsend:= BRIDGEsend(pkt, flag)
                end

             else begin
                  { -----------------------------------
                     cez X25 alebo komunikacny pocitac
                    -----------------------------------
                  }
                   {$IFDEF X25}
                     adr:= NETadr_wan(pkt.adr);
                     if isX25name(adr)>-1 then X25_LANsend:= X25send(pkt,adr) {sizeof(pkt.head)+pkt.head.dlz}
                     else
                   {$ENDIF}
                   {[2]}
                    X25_LANsend:= BRIDGEsend(pkt, flag)
                  end
           end
    end;

{$ENDIF}