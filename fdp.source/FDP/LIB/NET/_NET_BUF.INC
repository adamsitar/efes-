{ ------------------------------------------
   nacitanie paketov zo zachytnych bufferov
  ------------------------------------------
  - vo funkciach sa nesmie volat slucka Main... , aby sa znova nevyvolalo
    read_inp_buff, pretoze by sa mohli pakety predbehnut, zbytocne sa preplna
    stack..., inac je bezpecny semafor
}

procedure TNET.read_inp_buff;

    var   Np : TNETpkt;
         {$IFDEF IPX}
          Lp : TIPXdpkt;
         {$ENDIF}
         {$IFDEF BROADCAST}
          Bp : TNETBpkt;
         {$IFDEF UDP} from : T_IPaddress; {$ENDIF}
         {$ENDIF}

    begin
    { v nacitani musi ostat while, pretoze tak sa nacita viac paketov
      (potvrdeni) spracovatelnych neskor naraz
    }
      if (not is_dta) then
         begin
           is_dta:= true;
           {$IFDEF IPX}
             while IPXread(Lp) do
               if code_ipxIPXpkt_to_NETpkt (Lp,Np) then NET^.receive_pkt(Np)
               else disp_NETpkt(@Np);
            {$IFDEF RTR}
              while RTRread(Lp) do
                if decode_ipxRTRpkt_to_NETpkt (Lp,Np) then NET^.receive_pkt(Np)
                else disp_NETpkt(@Np);
            {$ENDIF}
           {$ENDIF}

           {$IFDEF UDP}
             while UDPread(UDP_PORT_FDP,Np) do NET^.receive_pkt(Np);
             while UDPread(UDP_PORT_SYS,Np) do NET^.receive_pkt(Np);
           {$ENDIF}

           {$IFDEF COM}
             while COMread(Np) do NET^.receive_pkt(Np);
           {$ENDIF}

           {$IFDEF _X25}
             while X25read(Np) do NET^.receive_pkt(Np);
           {$ENDIF}
           is_dta:= false
         end;

      {$IFDEF BROADCAST}
        if (not is_brc) then
           begin
             is_brc:= true;

             {$IFDEF IPX}
               if IPXBread(Bp) then receive_brc(Bp);
             {$ENDIF}

             {$IFDEF UDP}
              Bp.size:= udp_read(UDP_PORT_BRC.desc, @Bp.data,sizeof(Bp.data), from);
              if Bp.size>0 then receive_brc(Bp, from);
              {$IFDEF ARCHIVE_DAR}
                if Bp.size>0 then save_RLI(@Bp.data,Bp.size);
              {$ENDIF}
             {$ENDIF}

             is_brc:= false
           end;
      {$ENDIF}

      {$IFDEF IPX}
        IPXstatus;  { kontrola stavu pre protokol IPX3  }
      {$ENDIF}

      {$IFDEF _X25} {$IFDEF X25_BUFFER}
        X25sending
      {$ENDIF} {$ENDIF}

    end; { read_inp_buff }
