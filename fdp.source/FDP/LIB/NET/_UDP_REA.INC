{ תתתתתתתתתתתתתתתת
   nizsia uroven
  תתתתתתתתתתתתתתתת
}

{ "len" je velkost buffera..., vrati pocet nacitanych byte
}
function udp_read (desc: int; buff: pointer; max_len: int; var _from: T_IPaddress): int;
   begin
     if net_is_data(desc, buff^,max_len, _from) > 0 then
        udp_read:= net_read(desc, buff^,max_len, _from,NET_FLG_NONBLOCKING)
     else udp_read:= 0
   end;


function udp_read_port (port: TUDP_port; var Up: TUDPpkt): bool;
   begin
     udp_read_port:= false;

     udp_read_port:= true
   end;


{function udp_read_brc (port: TUDP_port; var Np: TNETpkt): bool;
   var   Up       : TUDPpkt;
   begin
     udp_read_rli:= false;
     if port.desc=-1 then Exit;

     if net_is_data(port.desc, Up.data,sizeof(Up.data), f)=0 then Exit;
     with Up do size:= net_read(port.desc, data, sizeof(data), from, NET_FLG_NONBLOCKING);
   end;
}


function UDPread (port: TUDP_port; var Np: TNETpkt): bool;

   var   Up       : TUDPpkt;
         u_id     : TRTCpkt_id;
         rtr_mess : TRTR_heartbeat;
         rtr_adr  : TRTRadr;

         adr      : TNETadr;
         p,d      : pointer;
         res,err  : bool;

   procedure archive(prompt: string);
       begin
         archive_data(path_NET,inttostr(month,2,0)+inttostr(day,2,0)+inttostr(hour,2,0)+inttostr(0,2,0)+'.'+extNET,
                      @Up.data,Up.size,prompt,true,false
                     );
       end;

   label X;

   begin
     UDPread:= false;
     if port.desc=-1 then Exit;

     if port.asynch then
          begin
          { nacitanie z buffera (naplneneho v preruseni)
          } if (UDP_buff=nil) or (not UDP_buff^.is) then Exit;
            UDP_buff^.read(@Up)
          end
     else begin
          { nacitanie z portu
          } if net_is_data(port.desc, Up.data,sizeof(Up.data), Up.from)>0 then
               with Up do size:= net_read(port.desc, data, sizeof(data), from, NET_FLG_NONBLOCKING)
            else Exit
          end;


     {$IFDEF DEBUG} {ARCHIVE_NET_BIN}
      archive('.');
     {$ENDIF}

     fillchar(Np,sizeof(Np),0);
     Np.adr:= NETaddress;
     Np.ods:= is_IPadr(Up.from.fhost);

     p:= @Up.data;
     Move(p^,u_id,sizeof(u_id));
     case u_id.prizn of

      {$IFDEF CAS_RLI}
       ast_RLI,
       ast_utcALas03 : decode_rliUTC(@Up.data,Up.size);
      {$ENDIF}

       ast_RTR_CALL : { UDP_PORT_SYS }
         begin
          { Vyzva od routera : 0xA0 2b 1b 4b 3b
          } move(Up.data[1], rtr_adr,sizeof(rtr_adr));
            if rtr_adr=ROUTERadr_rtr then
               begin
                 ROUTERadr_ip:= Up.from.fhost; { adresa sa mohla zmenit - prepnutie na zalozny router }
                 rtr_mess.kod:= ast_RTR_ACK;
                 rtr_mess.ods:= RTRadr;
                 rtr_mess.typ:= rtr_FDP;
                 udp_send(port, false,'',ROUTERadr_ip, sizeof(rtr_mess),@rtr_mess)
               end;
           {archive(archSYS)}
         end;


       ast_RTR_PKT   :
         begin
           res:= (Np.adr<>Np.ods) and decode_RTRpkt_to_NETpkt(TRTRpkt_bin(Up.data),Np,err);
           if not res then
              begin
                disp_NETpkt(@Np);
                if err then archive(archERR)
                {$IFDEF DEBUG}
                 else archive(archSYS)
                {$ENDIF}
              end;
           UDPread:= res
         end;


       ast_CISCO_PKT :
         begin
           res:=  (    (inRange(u_id.typ,rspr_FDP_lo,rspr_FDP_hi))
                   and (u_id.typ in set_rspr_CISCO)
                  );
           if res then decode_RTCpkt_to_NETpkt (Up.data,Up.size, Np)
           else archive(archERR);
           UDPread:= res
         end;


       ast_SIM_PKT   :
         begin
          {$IFDEF TRENAZER}
           if p_decode_SIMpkt<>nil then
              begin
                decode_SIMpkt (@Up.data,Up.size,Up.from.fhost);
                UDPread:= false
              end
          {$ELSE}
            UDPread:= false
          {$ENDIF}
         end;


       else begin
              {archive(archERR);}
            end;

     end;

     { 7.1. bolo na 500 RDC a 100 RDC nespravne nakonfigurovany
       protokol pre 500 OPL, IP adresa bola pripojena protokolom
       RTX... }
     if (nm_prs_addr(Np.adr) = IPadr) then Np.adr:= NETaddress;
   end;
