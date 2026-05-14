type   PNET_PRN_RES = ^TNET_PRN_RES;
       TNET_PRN_RES = record
         is  : bool;
         pkt : TNETpkt;
       end;


const  pkt_prn_res: PNET_PRN_RES = nil;


function prn_res_is_expected(ack: PNET_PRN_RES): bool; far;
   begin
     prn_res_is_expected:= (ack<>nil) and (ack^.is)
   end;


function print_str_to_net (PortNo: byte; s: string): string;
   var   res,adr : string;
         msg : bool;
         nd  : int;
         ft : text;
   begin
     {
     vytvor_novy_subor('1.bak');
     assign(ft,'1.bak'); reset(ft);
     writeln(ft,s);
     close(ft);
     print_str_to_net:= '';
     exit;
     }
     res:= '';
     msg:= true;
     if (PRNaddress<>'') and PRN_NET then
        begin
          nd:= is_NETadr(PRNaddress);
          if nd>-1 then adr:= strpas(NODEs^[nd].desc.name) else adr:= PRNaddress;
          new(pkt_prn_res); fillchar(pkt_prn_res^,sizeof(pkt_prn_res^),0);
          NETsend_msg (PRNaddress,spr_PRN_NET, @s[1],length(s), false,net_flag_SEND);
          if msg then Say(msgWAITING,msg_prn_IS_PRINTING+' ('+adr+')',
                          clGRc, clBUTTON_COLOR, nil,nil, 3*time_out_nd(nd),
                          GetTicks, @prn_res_is_expected, pkt_prn_res
                         )
          else repeat CheckProcesses until (prn_res_is_expected(pkt_prn_res));
          if not pkt_prn_res^.is then res:= msg_prn_TIME_OUT
          else res:= init_str(@(pkt_prn_res^.pkt.pkt.data^[0]),pkt_prn_res^.pkt.pkt.dlz);
          disp_NETpkt(@(pkt_prn_res^.pkt));
          if res<>'' then Err2(msgWARNING,res);
          dispose(pkt_prn_res); pkt_prn_res:= nil
        end
     else res:= send_string_to_prn(PortNo,s,false);
     print_str_to_net:= res
   end;


function print_str_from_net (pkt: TNETpkt): string;
   const smphr: bool = false;
   var   s,res: string;
   begin
     if smphr then Exit;
     smphr:= true;
     s:= init_str(@pkt.pkt.data^[0],minimum(pkt.pkt.dlz,sizeof(s)-1));
     res:= send_string_to_prn(PortNo,s,true);
     NETsend_msg (pkt.ods,spr_PRN_NET_RES, @res[1],length(res), false,net_flag_SEND);
     print_str_from_net:= res;
     smphr:= false;
   end;
