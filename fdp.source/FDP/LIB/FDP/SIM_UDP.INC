{ spracovanie spravy o konfigurovani: kontrola
  na pritomnost vlastnej pseudoadresy
}
 procedure _sim_CFG (data: pbytes; size: word; fhost: in_name);
     type  pfhost = ^in_name;
     var   pkt  : PSIMpkt;
           apkt : TSIMpkt_head;
           i,pocet : int;
           ip : pfhost;
     begin
       if sim_is_configured then Exit;

       pocet:= (size-sizeof(TSIMpkt_head)) div sizeof(in_name);
       i:= 1; while (i<=pocet) and (not sim_is_configured) do
          begin
            ip:= @PSIMpkt(data)^.data[(i-1)*sizeof(in_name)];
            if ip^=IPadr then
               begin
                 sim_is_configured:= true;
                 SIM_MASTER := fhost;

                 apkt.id    := ast_SIM_PKT;
                 apkt.typ   := SIM_SCAT_SET_CFG_ACK;
                 apkt.master:= SIM_MASTER;
                 {$IFDEF PCTCP}
                  if (SIMport<>nil) and (SIMport^.desc<>-1) then
                      udp_send_(SIMport^,false,'',SIM_MASTER,sizeof(apkt),@apkt,NET_FLG_NONBLOCKING)
                 {$ENDIF};
                 break
               end;
            inc(i)
          end
     end;


 procedure _sim_DEP (data: pbytes; size: word; fhost: in_name);
     var   pkt : PSIMpkt;
           ut  : UNIX_time;
           dt  : TDatum;
     begin
       if not sim_is_configured then Exit;

       pkt:= PSIMpkt(data);
       move(pkt^.data,ut,sizeof(ut));
       unix2dos(ut,dt);
       if checkdate(dt.rok,dt.mes,dt.den,false) and checktime(dt.h,dt.m,dt.s) then
          begin
            novyDatum:= dt;
            nastavDatum:= true
          end
     end;


 procedure _sim_BRK;
     begin
       if sim_is_configured then Clock^.zastav
     end;


 procedure _sim_CNT;
     begin
       if sim_is_configured then Clock^.pust
     end;


{ koniec cvicenia, odmazanie stripov
}
 procedure _sim_ARR;
     begin
       _sim_CNT;
       if sim_is_configured then SetCommand(Pending,nil,cmCNL_ALL_PLANs)
     end;


 procedure _sim_RLI (data: pbytes; size: word; fhost: in_name);
     var   pkt : PSIMpkt;
     begin
       if not sim_is_configured then Exit;

       pkt:= PSIMpkt(data);
       decode_rliUTC(@pkt^.data,size-sizeof(TSIMpkt_head))
     end;

 procedure _sim_FPI (data: pbytes; size: word; fhost: in_name);
     var   pkt : PSIMpkt;
           dat : PSIMdata;
           npkt: TNETpkt;
           p   : word;
     begin
       if not sim_is_configured then Exit;

       pkt:= PSIMpkt(data);
       dat:= PSIMdata(@pkt^.data);

       fillchar(npkt,sizeof(npkt),0);
       npkt.adr:= NETaddress;
      {$IFDEF PCTCP}
       npkt.ods:= is_IPadr(fhost);
      {$ENDIF}
       npkt.head.typ:= dat^.head.typ;
       npkt.head.cis:= dat^.head.cis;
       if not new_NETpkt_data (@dat^.data, size-sizeof(TSIMpkt_head)-sizeof(TSIMdata_head), npkt.pkt) then Exit;
       NET^.Add(@npkt);
       disp_NETpkt(@npkt)
     end;


{ zrusenie konfiguraaacie, odmazanie stripov
}
 procedure _sim_CFG_CNL;
     begin
       if not sim_is_configured then Exit;

       _sim_ARR;
       SetCommand(Pending,nil,cmCNL_ALL_PLANs);
       sim_is_configured:= false
     end;


 procedure receive_SIMpkt (data: pbytes; size: word; fhost: in_name);
     var   pkt : PSIMpkt;
     begin
       if sim0_is_configured then Exit;

       pkt:= PSIMpkt(data);
       if      (pkt^.head.id = ast_SIM_PKT)
           and (   ((not sim_is_configured) and (pkt^.head.typ = SIM_SCAT_SET_CFG))
                or ((sim_is_configured) and (pkt^.head.master = SIM_MASTER))
               )
                then

          case pkt^.head.typ of
            SIM_SCAT_SET_CFG     : _sim_CFG (data,size,fhost);
            SIM_SCAT_CANCEL_CFG  : _sim_CFG_CNL;

            SIM_SCAT_START_EXERC : _sim_DEP (data,size,fhost);
            SIM_SCAT_STOP_EXERC  : _sim_ARR;

            SIM_SCAT_BREAK       : _sim_BRK;
            SIM_SCAT_CONTINUE    : _sim_CNT;

            SIM_SCAT_STD_RLI     : _sim_RLI (data,size,fhost);
            SIM_SCAT_STD_FPI     : _sim_FPI (data,size,fhost);
            SIM_SCAT_ARC_CMD     : ;
          end
     end;

 procedure SIM_UNIX__init;
     begin
       {p_decode_SIMpkt:= @receive_astSIM_pkt;}
       SIMport:= @UDP_PORT_BRC;
       UDP_PORT_BRC.flag:= UDP_PORT_BRC.flag or NET_FLG_NONBLOCKING
     end;
