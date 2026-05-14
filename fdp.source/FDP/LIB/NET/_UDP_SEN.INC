{$IFDEF UDP}

 { adresa sa zada bud stringom "adr" alebo, ak = 0, tak adrip;
   arp.inc - ale nepristupne fcie pre arp...
 }
 function udp_send_(port: TUDP_port; brc: bool; adr: TIPname; adrip: TIPadr; size: int; buff: pointer; flags: word): int;
    var   _to : T_IPaddress;
         { pre test dostupnosti Ethernet adresy
          check_Ethernet, toLAN  : bool;
          i, flag, bad_rout, good_rout : int;
          hd_addr : array[0..5] of byte;
          endt : arp_entry;
         }
    begin
      neterrno:= netRES_OK;

      fillchar(_to,sizeof(_to),0);
      if adr<>'' then _to.fhost:= nm_prs_addr(adr)
      else _to.fhost:= adrip;
      _to.fsocket:= port.port;
      _to.lsocket:= port.port;

      if brc {and (adr=BROADCASTaddress)} then
         begin
           if net_write(port.desc, buff^,size, NET_FLG_BROADCAST)<>-1 then neterrno:= netRES_OK
           else neterrno:= net_TCP_IP + neterrno
         end
      else begin
             if neterrno<>netRES_OK then neterrno:= netBAD_ADDR
             else if neterrno=netRES_OK then
                  begin
                    if net_writeto(port.desc, buff^,size, _to, flags)<>-1 then neterrno:= netRES_OK
                    else neterrno:= net_TCP_IP + neterrno
                  end
           end;

      (*{$IFDEF DEBUG}
       if (neterrno=netRES_OK) then
          begin
            archive_data(path_NET,inttostr(month,2,0)+inttostr(day,2,0)+inttostr(hour,2,0)+inttostr(0,2,0)+'.'+extNET,
                         buff,size,'*',true,false
                        );
          end
       else begin
              archive_data(path_NET,inttostr(month,2,0)+inttostr(day,2,0)+inttostr(hour,2,0)+inttostr(0,2,0)+'.'+extNET,
                         buff,size,'%',true,false
                        );
            end;
      {$ENDIF}*)

      udp_send_:= neterrno
    end;


 function udp_send(port: TUDP_port; brc: bool; adr: TIPname; adrip: TIPadr; size: int; buff: pointer): int;
    begin
      udp_send:= udp_send_(port, brc,adr,adrip, size,buff, port.flag);
    end;

{$ENDIF}


{ תתתתתתתתתתתתתתתתתת
   aplikacna uroven
  תתתתתתתתתתתתתתתתתת
}
function UDPsend_ (const pkt: TNETpkt;
                   adr: TNETadr;
                   brc: bool;
                   protocol,typ: word;
                   flag: word
                  ): int;

   var   port      : TUDP_port;
         nd_ipadr  : TIPadr;
         nd        : int;

         Up        : TUDPdata;
         Rb        : TRTRpkt_bin;
         whole     : bool;

         data : pbytes;
         size : word;

         bres : bool;
         s    : string;

   label X;

   begin
     UDPsend_:= netNOT_SENDED;

     port:= UDP_PORT_FDP;
     nd_ipadr:= 0;
     data:= nil; size:= 0;

     case protocol of

       ast_CISCO_PKT :
          begin
            if not (    (inRange(typ,rspr_FDP_lo,rspr_FDP_hi))
                    and (typ in set_rspr_CISCO)
                   ) then
                   begin
                     {write_err_log('Invalid asterix paket type to send.');}
                     Exit;
                   end;

            port:= UDP_PORT_FDP;

            size:= code_NETpkt_to_RTCpkt (pkt,Up,size,typ);
            data:= @Up;
            nd:= is_NETadr(pkt.adr);

            if (adr=pkt.adr) and (nd>-1) then
               begin
                {$IFDEF NET_FLAG_SEND}
                { Na uzly, ktore nie su ok, sa informacia neposiela,
                  aby nedoslo ku zbytocnym oneskoreniam...
                }
                 if (not NODEs^[nd].stat.trasaok) and ((flag and net_flag_SEND)=0) then
                    begin
                      NODEs^[nd].stat.nodeinit:= true;
                      UDPsend_:= netNOT_SENDED;
                      Exit
                    end;
                {$ENDIF}
                 nd_ipadr:= NODEs^[nd].desc.adrip;
               end
            else begin
                  {$IFDEF UDP}
                    nd_ipadr:= nm_prs_addr(adr)
                  {$ENDIF}
                 end;
          end;


       ast_RTR_PKT   :
          begin
            port:= UDP_PORT_FDP;

            size:= code_NETpkt_to_RTRpkt (pkt,Rb, nil,rpRTR, whole);
            data:= @Rb;
            if (size=0) or (not whole) then Exit;
            nd_ipadr:= ROUTERadr_ip
          end;


       ast_SIM_PKT   :
          begin
            port:= UDP_PORT_FDP;
            size:= 0
          end
     end;

    {$IFDEF UDP}
     bres:= true;
     if (nd_ipadr<>0) then
        begin
          if (data<>nil) and (size>0) then UDPsend_:= udp_send(port, false,'',nd_ipadr, size,data);
        end
     else if brc then
             begin
               UDPsend_:= udp_send(port, true,adr,0, size,data)
               {net_write(port.desc, data,size, NET_FLG_BROADCAST)}
             end
     else begin
            bres:= false;
            {$IFDEF ARCHIVE_NET_BIN}
             s:= 'IP error, nm_prs_addr=0 for '+adr+', '+pkt.adr+'.';
             archive_data(path_NET,inttostr(month,2,0)+inttostr(day,2,0)+inttostr(hour,2,0)+inttostr(0,2,0)+'.'+extNET,
                          @s[1],length(s),'!',true,false
                         )
            {$ENDIF}
          end;

     {$IFDEF ARCHIVE_NET_BIN}
      if bres then
         archive_data(path_NET,inttostr(month,2,0)+inttostr(day,2,0)+inttostr(hour,2,0)+inttostr(0,2,0)+'.'+extNET,
                      @Up,sizeof(Up)-sizeof(TUDPdata)+UP.size,'U',true,false
                     );
     {$ENDIF}
    {$ENDIF}
   end;


function UDPsend(const pkt: TNETpkt; protocol,flag: word): int;
   begin
     UDPsend:= UDPsend_(pkt, pkt.adr,pkt.adr=BROADCASTaddress, protocol,rspr_RTR, flag)
   end;


function UDBsend(const pkt: TNETpkt; adr: TNETadr; flag: word): int;
   begin
{write_err_log('netNOT_SENDED-bridgesend '+adr+','+pkt.adr);}
     UDBsend:= UDPsend_(pkt, pkt.adr,pkt.adr=BROADCASTaddress, ast_CISCO_PKT,rspr_RT_, flag)
   end;
