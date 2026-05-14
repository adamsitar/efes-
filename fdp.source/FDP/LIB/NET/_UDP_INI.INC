{$IFDEF UDP}
 function is_IPadr(adrip: TIPadr): TNETadr;
    var   adr : TNETadr;
          i   : int;
    begin
      if adrip=IPadr then adr:= NETaddress
      else begin
             i:= 0; while (i<NODEpoc) and (NODEs^[i].desc.adrip<>adrip) do inc(i);
             if (i<NODEpoc) then adr:= NODEs^[i].desc.adr
             else adr:= inet_ntoa(adrip)
           end;
      is_IPadr:= adr
    end;
{$ENDIF}


{ I arp.inc}

{ --------------------------
  UDP
  ==========================
}
var  SaveExit : pointer;

procedure UDP_done;
    begin
      net_abort(UDP_PORT_FDP.desc);
      {$IFDEF BROADCAST} net_abort(UDP_PORT_BRC.desc); {$ENDIF}
      net_abort(UDP_PORT_SYS.desc);

      ExitProc:= SaveExit
    end;

{
  alokacia a otvorenie descriptora
}
procedure udp_open_port(_UDP_FHOST,_UDP_PORT: word; var _UDP_desc: int; _asynch, _connect: bool);
    var   UDP_address  : T_IPaddress;
          size : long;
          res  : bool;
          s : string;
    begin
      s:= WordToHex(_UDP_PORT);

     { תתתתתתתתתתתתתתתתתתתת }
     { alokacia descriptora }
     { תתתתתתתתתתתתתתתתתתתת }

      _UDP_desc:= {$IFDEF DEBUG} net_getdesc  {$ELSE} net_getglobdesc {$ENDIF};
      if _UDP_desc<0 then RunError(s+' -> net_getdesc: '+strpas(neterr_list[neterrno])+'.');

      set_option(_UDP_desc,DGRAM, NET_OPT_BUFSIZE, UDP_MTU,sizeof(UDP_MTU));
      { nastavi timeout }
      size:= 1; set_option(_UDP_desc,DGRAM, NET_OPT_TIMEOUT, size,sizeof(size));
      {$IFDEF DEBUG}
        get_option(_UDP_desc,DGRAM, NET_OPT_TIMEOUT, size,sizeof(size));
      {$ENDIF}
      { long Options=IP_TOS_LOW_COST|IP_TOS_LOW_DELAY;
        set_option(NetDesc[i],DGRAM,NET_OPT_TOS,(char *)Options,longSize);
      }

     { תתתתתתתתתתתתתתתתת }
     { otvorenie portov  }
     { תתתתתתתתתתתתתתתתת }
      UDP_address.fhost  := _UDP_FHOST;
      UDP_address.fsocket:= _UDP_PORT;
      UDP_address.lsocket:= _UDP_PORT;
      if (_asynch) then res:= (net_asynch(_UDP_desc,NET_AS_RCV,@asynch_stub,@net_asynch_handler)<>-1)
      else res:= true;
      if res then
         if _connect then res:= (net_connect(_UDP_desc,DGRAM,UDP_address)>=0)
         else res:= (net_listen(_UDP_desc,DGRAM,UDP_address)>=0);
      if not res then RunError(s+' -> net_connect: '+strpas(neterr_list[neterrno])+'.')
    end;


procedure UDP_init;
    var   buf    : array[0..100] of char;
          size   : long;
          res,i  : long;
    begin
      write('Initializing UDP...  ');

      disable_asynch;
      net_releaseall;

      { pctcp_init; -> uz v pctcp.pas }

      SaveExit:= ExitProc;
      Exitproc:= @UDP_done;

     { תתתתתתתתתתתתתתתתתת }
     { otvorenie portov   }
     { תתתתתתתתתתתתתתתתתת }
      UDP_PORT_SYS.asynch:= false;
      with UDP_PORT_SYS do udp_open_port (UDP_FHOST,port,desc,asynch,true);
      {$IFDEF BROADCAST}
        UDP_PORT_BRC.asynch:= false;
        with UDP_PORT_BRC do udp_open_port (UDP_FHOST,port,desc,asynch,true);
      {$ENDIF}
      with UDP_PORT_FDP do udp_open_port (UDP_FHOST,port,desc,asynch,true);

     { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }
     { vyhladanie vlastnej adresy, masky, adresy routera }
     { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }
      size:= 100; res:= get_kernel_info(0,TAG_IP_ADDR,0, buf,size);
      if (res<>0) or (size<>sizeof(in_name)) then RunError(err_ip_cfg+' (ip-address).');
      move(buf,my_ip_addr,sizeof(my_ip_addr));
      if (IPadr<>0) and (IPadr<>my_ip_addr) then RunError('Different IP address in pctcp.ini and '+NETcfg+'.');

      size:= 100; res:= get_kernel_info(0,TAG_SUBNET_MSK,0,buf,size);
      if (res<>0) or (size<>sizeof(in_name)) then RunError(err_ip_cfg+' (subnet-masks)');
      move(buf,subnet_mask,sizeof(subnet_mask));
      {if (my_ip_addr and subnet_mask)=0 then RunError('Invalid subnet mask.');}

      size:= 100; res:= get_kernel_info(0,TAG_GATEWAY,0,buf,size);
      routers_num:= size div sizeof(in_name);
      if (res<>0) or (routers_num>3) then RunError(err_ip_cfg+' (routers)');
      fillchar(routers,sizeof(routers),0);
      for i:= 0 to routers_num-1 do move(buf[i*sizeof(in_name)],routers[i],sizeof(in_name));

      size:= 100; res:= get_kernel_info(0,TAG_MAC_ADDR,0,buf,size);
      if (res<>0) or ((size<>PPP_fr_size) and (size<>DIX_fr_size)) then RunError(err_ip_cfg+' (frame-type)');
      if (size<>PPP_fr_size) then frame_type:= DIX_Ethernet
      else frame_type:= PPP;

      { --- ping na vsetky routre --- }
      for i:= 0 to routers_num-1 do
          begin
            {if (my_ip_addr and routers[i])=0 then RunError('Invalid subnet mask.');}
            icmp_ping(routers[i],50);
          end;

      {for i:= 0 to nodepoc-1 do icmp_ping(nodes^[i].desc.adrip,50);}

      enable_asynch;
      writeln('Done.',kbNL,
              'LETVIS initialized on UDP ports: '
                                 + ' sys: '  +WordToHex(UDP_PORT_SYS.port)
                                 + ', data: '+WordToHex(UDP_PORT_FDP.port)
               {$IFDEF BROADCAST}+ ', brc: ' +WordToHex(UDP_PORT_BRC.port){$ENDIF}
               + '.'
             );
      Delay(1000)
    end;
