(*
  zatial nic z toho ARP je v LIB

  }
     { ARP }
     check_Ethernet:= (frame_type = DIX_Ethernet) { && !(flag&NET_FLG_BROADCAST))};
     toLAN:= (to.fhost and subnet_mask) = (my_ip_addr and subnet_mask);

     { ---- kontrola falosneho routra v ARP cache ----- }
     if (check_Ethernet and (not toLAN)) then
        begin
          bad_rout:= -1; good_rout:= -1;
          fillchar(hd_addr,sizeof(hd_addr),0); hd_addr[0]:= $10;
          for i:= 0 to routers_num-1 do
              begin
                fillchar(ent,sizeof(ent),0);
                ent.ip_addr:= routers[i];
                if (arp_get_entry(&ent) == 0)
            if(memcmp(ent.hd_addr,hd_addr,6) ==0) bad_rout =i;
            else                                  good_rout=i;
      }
      if(good_rout>-1 && bad_rout>-1)
         arp_delete_entry(routers[bad_rout]);
   }


   //---- vyslanie paketu ----
   if(net_writeto(NetDesc[pck.SocketNo],(char *)pck.data,pck.len,&to,flag)<=0)
      {
      #ifdef DBG
      //ServeError(FailedOperation);
      EM.Message("\nPCTCP kernel error - %s",neterr_list[neterrno]);
      switch(neterrno)
        {
        case NET_ERR_NET_UNREACHABLE:
        case NET_ERR_HOST_UNREACHABLE:
        case NET_ERR_ICMPMSG:
          EM.Message(" while sending to %4.4X",pck.num);
        }
      #endif DBG
      return_value=0;
      }
   //--- kontrola ARP_cache ---
   if(check_Ethernet)
   {
      if(toLAN) //send do LAN
      {
         ent.ip_addr=to.fhost;
         memset(ent.hd_addr,0,6);
         if(arp_get_entry(&ent) == -1)  //zaradenie falosnej polozky
         {
            ent.hd_addr[0]=0x10;
            arp_set_entry(&ent);
         }
      }
      else if(routers_num > 0)  //je konfigurovany aspon jeden router
      {
         memset(ent.hd_addr,0,6);
         for(int i=0;i<routers_num;i++)
         {
            ent.ip_addr=routers[i];
            if(arp_get_entry(&ent) == 0)
               break;
         }
         if(i==routers_num) //ziaden router nie je aktivny
         {
            ent.ip_addr=routers[routers_num-1];
            ent.hd_addr[0]=0x10;
            arp_set_entry(&ent);
         }
      }
   }
   return return_value;

   (*  DOPLNIT PO IMPLEMENTACII ARP ...

     {
     if(pck.len > 1024) pck.len=1024;
     if(pck.SocketNo==NoIndex) pck.SocketNo=MessageSocket;
     struct addr to;
     int flag=NET_FLG_NONBLOCKING;
     to.fsocket=PortTCPIP[pck.SocketNo];
     to.lsocket=PortTCPIP[pck.SocketNo];
     if(pck.num==0 || pck.num==BROADCAST_ADDR)   // broadcast
       flag|=NET_FLG_BROADCAST;
     else if((to.fhost=get_IP_addr(pck.num)) == 0L)
       return 0;

     int return_value=1;
     }

     { kontrola existencie falosneho routra v ARP cache }
     check_Ethernet:= (frame_type==DIX_Ethernet && !(flag&NET_FLG_BROADCAST));
     toLAN:= ((_to.fhost&subnet_mask) == (my_ip_addr&subnet_mask));
     if (check_Ethernet && !toLAN) then
        begin
          bad_rout:= -1; good_rout:= -1;
          fillchar(hd_addr,sizeof(hd_addr),0); hd_addr[0]:= $10;
          for i:= 0 to routers_num-1 do
            begin
              ent.ip_addr:= routers[i];
              fillchar(ent.hd_addr,sizeof(ent.hd_addr),0);
              if (arp_get_entry(ent) = 0) then
                 if (memcmp(ent.hd_addr,hd_addr,6) ==0) then bad_rout:= i
                 else good_rout:= i
            end;
          if (good_rout>-1 && bad_rout>-1) then arp_delete_entry(routers[bad_rout]);
        end;

     { vyslanie paketu }

     { kontrola ARP_cache }
     if (check_Ethernet) then
        begin
          fillchar(ent.hd_addr,sizeof(ent.hd_addr),0);
          if (toLAN) then { sended do LAM }
             begin
               ent.ip_addr= _to.fhost;
               if (arp_get_entry(ent)=-1) then { neuspesne vyslanie, zaradenie falosnej polozky }
                  begin
                    ent.hd_addr[0]:= $10;
                    arp_set_entry(ent)
                  end
             end
          else if (routers_num>0) then { je konfigurovany aspon jeden router ? }
                  begin
                    i:= 0;
                    while i<routers_num do
                      begin
                        ent.ip_addr:= routers[i];
                        if arp_get_entry(ent)=0 then break;
                        inc(i)
                      end;
                    if (i>=routers_num) then { ziaden router nie je aktivny }
                       begin
                         ent.ip_addr:= routers[0{routers_num-1}];
                         ent.hd_addr[0]:= $10;
                         arp_set_entry(ent)
                       end
        end
*)
