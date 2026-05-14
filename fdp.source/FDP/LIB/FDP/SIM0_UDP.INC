 const  SIM0_ADR_NOT_CONFIGURED = 'DOS simulator (SIM address) is not configured.';
        {SIM0_NOT_CONFIGURED     = 'DOS simulator is not configured.';}
        SIM0_ADR_FAILED         = 'SIM address for DOS simulator is not properly configured.';


 procedure _sim0_CNT; forward;
 procedure _sim0_ARR; forward;


{ spracovanie spravy o konfigurovani: kontrola
  na pritomnost vlastnej pseudoadresy
}
 procedure _sim0_CFG(rpkt : PSIM0pkt; ipadr : TIPname);
     var   hpkt  : TSIM0pkt_head;
           pocet : byte;
           adr   : word;
           i     : int;
     begin
       if sim0_is_configured then Exit;

       Move(rpkt^.data,pocet,sizeof(pocet));
       for i:= 1 to pocet do
           begin
             Move(rpkt^.data[sizeof(pocet) + (i-1)*sizeof(adr)],adr,sizeof(adr));
             sim0_is_configured:= (sim0_THIS<>0) and (adr=sim0_THIS);
             if sim0_is_configured then break
           end;

       if not sim0_is_configured then Exit;

       sim0_GROUP  := rpkt^.head.group;
       sim0_DEVICE := rpkt^.head.device;

     { potvrdenie konfiguracie }
       with hpkt do
         begin
           id     := ast_SIM_PKT;
           group  := sim0_GROUP;
           device := sim0_THIS;
           typ    := sim0_CFG_ACK
         end;
      {$IFDEF PCTCP}
       udp_send(UDP_PORT_BRC,false,ipadr,0,sizeof(hpkt),@hpkt)
      {$ENDIF}
     end;


{ zrusenie konfiguraaacie, odmazanie stripov
}
 procedure _sim0_CFG_CNL;
     begin
       if not sim0_is_configured then Exit;

       _sim0_ARR;
       SetCommand(Pending,nil,cmCNL_ALL_PLANs);
       sim0_is_configured:= false
     end;


{ zaciatok cvicenia, nastavenie casu
}
 type  PSim0Time = ^TSim0Time;
       TSim0Time = record
         Hod : byte;
         Min : byte;
         Sec : byte;
         Tik : byte;
       end;

 procedure _sim0_DEP(rpkt : PSIM0pkt);
     begin
       with PSim0Time(@rpkt^.data)^ do
         if sim0_is_configured and CheckTime(Hod,Min,Sec) then
            begin
              SetTimem(Hod,Min,Sec)
            end;
     end;


{ koniec cvicenia, odmazanie stripov
}
 procedure _sim0_ARR;
     begin
       _sim0_CNT;
       if sim0_is_configured then SetCommand(Pending,nil,cmCNL_ALL_PLANs)
     end;


 procedure _sim0_BRK;
     begin
       if sim0_is_configured then Clock^.zastav
     end;


 procedure _sim0_CNT;
     begin
       if sim0_is_configured then Clock^.pust
     end;


 procedure _sim0_STRIP(pkt : PNETpkt);
     var   rpkt : PSIM0pkt;
           npkt : TNETpkt;
           dlz  : TNETdlz;
           p    : word;

     begin
       if not sim0_is_configured then Exit;

       npkt:= pkt^; fillchar(npkt.pkt,sizeof(npkt.pkt),0);
       dlz := pkt^.pkt.dlz-sizeof(TSIM0pkt_head);

       p:= 0;
       rpkt:= PSIM0pkt(pkt^.pkt.data);
       Move(rpkt^.data[p],npkt.head.typ,sizeof(npkt.head.typ)); p:= sizeof(npkt.head.typ);
       Move(rpkt^.data[p],npkt.head.cis,sizeof(npkt.head.cis)); inc(p,sizeof(npkt.head.cis));
       new_NETpkt_data (@rpkt^.data[p],dlz-p,npkt.pkt);
       NET^.Add(@npkt);

       disp_NETpkt(@npkt)
     end;


 function is_SIM0_packet(pkt: PSIM0pkt): bool;
    begin
    end;


 procedure receive_SIM0pkt (data: pbytes; size: word; fhost: in_name);
     var   pkt  : TNETpkt;
           rpkt : PSIM0pkt;
     begin
       if sim_is_configured or (sim0_THIS=0) then Exit;
       if not ((size>1) and (data^[0]=ast_SIM_PKT)) then Exit;

       FillChar(pkt,sizeof(pkt),0);
       pkt.adr:= NETaddress;
       {$IFDEF PCTCP}
        pkt.ods:= is_IPadr(fhost);
       {$ENDIF}
       if pkt.adr=pkt.ods then Exit;
       pkt.head.typ:= spr_SIM;
       new_NETpkt_data (pchars(data),size,pkt.pkt);

       rpkt:= PSIM0pkt(pkt.pkt.data);
       if     (rpkt^.head.id = ast_SIM_PKT)
          and (   (not sim0_is_configured)
               or (rpkt^.head.group = sim0_GROUP)
              )
          then
          case rpkt^.head.typ of
            sim0_CFG     : _sim0_CFG(rpkt, pkt.ods);
            sim0_CFG_CNL : _sim0_CFG_CNL;

            sim0_DEP     : _sim0_DEP(rpkt);
            sim0_ARR     : _sim0_ARR;

            sim0_BRK     : _sim0_BRK;
            sim0_CNT     : _sim0_CNT;

            sim0_REC_DEP : ;
            sim0_REC_ARR : _sim0_ARR;
            sim0_REC_CNL : _sim0_ARR;

            sim0_STRIP   : _sim0_STRIP(@pkt)
          end;

       disp_NETpkt(@pkt)
     end;


 procedure SIM_DOS__init;
     var   s,t  : string;
           nl   : bool;
           i    : int;
           p    : pchar;
     begin
       {$IFDEF PCTCP}
        UDP_PORT_BRC.port:= SIM0_UDP_SOCKET_ADR;
       {$ENDIF}
       nl:= false;

       t:= cfg_sim0_THIS+#0;
       p:= strpos(NODEInfo,@t[1]);
       if p<>nil then
          begin
            s:= getstr(strpas(p),2,['=','/']);
            s:= getstr(s,1,[';',' ',',']);
            val(s,sim0_THIS,i);
            if (i>0) then RunError(NETcfg+' -> '+SIM0_ADR_FAILED)
          end
       else MessError(NETcfg+' -> '+SIM0_ADR_NOT_CONFIGURED,true,nl);

       {
       s:= __read_cfg(NETcfg,cfg_sim0_THIS, lst_aspon_1_polozka);
       if (s='') then MessError(NETcfg+' -> '+SIM0_ADR_NOT_CONFIGURED,true,nl)
       else begin
              s:= s+NULL; s:= _item_18 (@s[1], cfg_sim0_THIS,1);
              val(s,sim0_THIS,i);
              if (s='') or (i>0) then RunError(NETcfg+' -> '+SIM0_ADR_FAILED)
            end;
       }

       if nl then writeln;
       {_decode_SIM:= @spracuj_sim0_packet}
     end;
