{ ----------------------------------------
  identifikacia typu a spracovania paketu
}
 function is_ack_pkt(const pkt: TNETpkt): bool;
    begin
      is_ack_pkt:= odd(pkt.head.typ)
    end;

 function is_mess_pkt(const pkt: TNETpkt): bool;
    begin
      is_mess_pkt:= {(pkt^.head.typ >= 0 spr_MESSlo) and} (pkt.head.typ < spr_DATAlo)
    end;

 function is_data_pkt(const pkt: TNETpkt): bool;
    begin
      is_data_pkt:= (pkt.head.typ >= spr_DATAlo)
    end;


{ --------------------------------------------------
  nastavenie priznakov odoslania/spracovania spravy
}
 procedure node_ok (nd: int; _node_init,_node_on,_init_en: bool); far;
     var   s: string;
     begin
       if (nd>-1) then with NODEs^[nd].stat do
           begin
             if (_node_on) or (_init_en) then InitEn:= true;                       { povolenie inicializacie uzla  }
             if (_node_on) or (_node_init) or (not TrasaOK) then NodeInit:= true;  { prikaz pre inicializaciu uzla }
             if (_node_on) {or (not TrasaOK)} then Node_ON:= true;                   { uzol je ON }
             TrasaOK  := true; {SendOK   := true;}
             SendTick := getticks;
             RecTick  := SendTick;
             NextTest := Maximum(tmout_CALL,NODEs^[nd].desc.tmout)
           end
     end;

 procedure node_off(nd: int; _node_off: bool); far;
     var   s: string;
     begin
       if (nd>-1) then with NODEs^[nd].stat do
          begin
            if _node_off then Node_ON:= false;

            if TrasaOK then
               begin
                 s:=   NODEs^[nd].desc.adr+' - NODE TIME OUT ('
                     + IntToStr(GetTicks,5,0)+', '+IntToStr(SendTick,5,0)+', '+IntToStr(RecTick,5,0)
                     + ')';
                 {$IFDEF WRITELN_NET}
                   if (MainApp<>nil) then
                      MainApp^.writeln_(@s[1],length(s), cl_NODE_OFF, arch_SYS, true,false);
                 {$ENDIF}
                 {$IFDEF ARCHIVE_NET}
                   if archive_NET_REC then
                      archivuj_data(path_NET, get_ARCHfn(0)+'.'+extNET, @s[1],length(s), arch_SYS, true,false)
                 {$ENDIF}
               end;

           {$IFDEF BACKUP}
             if (nd=SERVERnode) or (-1=SERVERnode) then
                begin
                  SERVERstatus:= false;
                  send_mail(nil,MainApp,cmSERVER_STATUS,One,nil,0);
                  (*{$IFDEF STATUS}
                    if btFDPBCK<>nil then btFDPBCK^.visibility(not SERVERstatus);
                  {$ENDIF}*)
                  {NETsend_msg(spr_CALL,SERVERaddress, nil,0, true, net_flag_SEND)}
                end;
           {$ENDIF}

           {$IFDEF MASTER}
             if (nd=BACKUPnode) or (-1=BACKUPnode) then
                begin
                  BACKUPstatus:= false;
                  {send_mail(nil,MainApp,cmSERVER_STATUS,One,nil,0);}
                end;
           {$ENDIF}

            TrasaOK  := false; {SendOK := true }
            SendTick := GetTicks;
            RecTick  := SendTick;

           {$IFDEF IPX} {$IFDEF IPX3}
            if NODEs^[nd].desc.pro in [RTR,RTI,RTB] then IPX_login;
           {$ENDIF} {$ENDIF}
          end
     end;


 procedure pkt_sended(const pkt: TNETpkt); far;
     var   nd : int;
     begin
       if     (not is_ack_pkt(pkt))             { nie je to potvrdenie }
          and (pkt.head.typ > ack_CAS)          {                      }
          and (pkt.ods = self_NETadr(pkt.adr))  { sprava od tohto uzla }
              then
          begin
            nd:= is_NETadr(pkt.adr);
            if nd>-1 then
               begin
                 NODEs^[nd].stat.SendTick:= getticks;
                 {NODEs^[nd].stat.SendOK:= false}
               end
          end
     end;

{ nastavenie, ze ku uzlu nd je spojenie ok:
  SendOK, prip. TrasaOK
}
 procedure say_data_sended(res: bool);
     begin
       if res then Say2(msgINFO,msgDATA_SENDED)
       else Err2 (msgWARNING,msgDATA_NOT_SENDED)
     end;


 procedure TNET.nodeON(ods: TNETadr; _node_init,_node_on,_init_en: bool);
     begin
       node_ok (is_NETadr(ods), _node_init,_node_on,_init_en);
     end;

 procedure TNET.nodeOFF(ods: TNETadr; _node_off: bool; id: PNETpkt_head);
     begin
       node_off(is_NETadr(ods),_node_off)
     end;


 procedure pkt_received(const pkt: TNETpkt); far;
     begin
       if NET<>nil then NET^.nodeON(pkt.ods, false,false,false);
     end;

 procedure pkt_not_received(nd: int; _node_off: bool; id: PNETpkt_head); far;
     begin
       if NET<>nil then NET^.nodeOFF(NODEs^[nd].desc.adr, _node_off, id);
     end;
