{$IFDEF CONNECT_TO_FDA}

 procedure _pkt_PRS_FDA(PRS: PPRS);
     var   PRSp: TPRS;
           p: pointer;
           res,ods: string;
           nd,ires: int;
     begin
      { prisiel paket od FDP ?, ak nie, ignoruj ho...
      }
       ods:= '';
       {$IFDEF NET}
         {nd:= 0; while (nd<sizeof(PRS^.rec)) and (PRS^.rec[nd]<>is_rec) do inc(nd);}
         if (FDAnode >= 0) then {if nd < sizeof(PRS^.rec) then}
            begin
              nd:= FDAnode;
              ods:= NODEs^[nd].desc.adr;
              PRS^.rec[nd]:= no_ack; { -> aby som ho poslal opraveny naspat na FDA }
            end;
       {$ENDIF}

       if (ods='') or (strpos(NODEs^[nd].desc.inf,nd_FDA)=nil) then
          begin
            l4_err(a_FDP,ods,0,50, res);
            write_err_log(res);
            Exit
          end;

       if is_P(PRS^.kod) then
          begin
            Exit;
          end;

       {$IFDEF CONNECT_TO_OPL_EXT}
         PRS^.vys1:= code_vysOPL(PRS^.vys1);
         PRS^.vys2:= code_vysOPL(PRS^.vys2);
       {$ENDIF}

       if read_PRS(codekey_PRS(PRS),@PRSp)>-1 then p:= @PRSp else p:= nil;
       if    (_decode_stav(PRS^.stat)=_zruseny)
          or syntax_PRS (PRS,p, res,ires, false,nil)
             then _pkt_PRS(PRS)
       else begin
              res:= cs_ascii_str2(res);
              NETsend_err (ods,level_USER,true,@res[1],length(res));
            end;

       if p<>nil then disp_PRS(@PRSp);
     end;


 function  send2FDA: bool;
    begin
      send2FDA:=     (FDAnode >= 0)
                 and (FDAnodes > 0)

                 {$IFDEF BACKUP} {$IFNDEF BACKUP_ACTIVE_2_NET}
                  and (not SERVERstatus)
                 {$ENDIF} {$ENDIF}

                 {$IFDEF MASTER} {$IFDEF BACKUP_ACTIVE_2_NET}
                  and (not BACKUPstatus)
                 {$ENDIF} {$ENDIF}
    end;


 procedure send2FDA_nodes;
     var   buff   : pchars;
           size   : int;
           cislo,ind : byte;
           i,w    : word;
           b      : byte;
           uzol,s,t : string;
     begin
       if not send2FDA then Exit;

       getmem(buff,size_of_NETpkt);

      { pocet stanic }
       buff^[0]:= chr(FDAnodes);
       size:= sizeof(byte);

       for i:= 0 to NODEpoc-1 do with NODEs^[i].desc do if indFDA>-1 then
         begin
           ind:= 0; uzol:= '';

          { poradove cislo uzla }
           cislo:= indFDA;
           move(cislo,uzol[ind],sizeof(cislo)); inc(ind,sizeof(cislo));

          { nazov uzla }
           move(name^,uzol[ind],strlen(name)+1); inc(ind,strlen(name)+1);

          { telefonne cislo }
           t:= GetPStr(infFDA,2,['='])+kbNUL;
           move(t[1],uzol[ind],length(t)); inc(ind,length(t));

          { ip adresa }
           w:= adrip and $FFFF;
           uzol[ind]:= chr(lo(w)); inc(ind);
           uzol[ind]:= chr(hi(w)); inc(ind);
           w:= adrip shr 16;
           uzol[ind]:= chr(lo(w)); inc(ind);
           uzol[ind]:= chr(hi(w)); inc(ind);

          { arm adresa }
           w:=  adrr;
           uzol[ind]:= chr(lo(w)); inc(ind);
           uzol[ind]:= chr(hi(w)); inc(ind);

          { zapis do buffera }
           if (size+ind < size_of_NETpkt) then
              begin
                move(uzol[0],buff^[size],ind);
                inc(size,ind);
              end;
         end;

      { timeout uzlov }
       cislo:= tmout_HEARTBEAT_max div 10;
       move(cislo,buff^[size],sizeof(cislo)); inc(size,sizeof(cislo));

       NETsend_msg (NODEs^[FDAnode].desc.adr, spr__FDA_NODES , buff,size, false,net_flag_SEND);
       freemem(buff,size_of_NETpkt);
     end;


 procedure send2FDA_status;
     var   buff      : pchars;
           size      : int;
           cislo,ind : byte;
           i,w       : word;
           j         : shortint;
           uzol,s,t  : string;
     begin
       if not send2FDA then Exit;

       getmem(buff,size_of_NETpkt); size:= 0;

      { pocet stanic }
       buff^[0]:= chr(FDAnodes);
       size:= sizeof(byte);

       for i:= 0 to NODEpoc-1 do with NODEs^[i].desc do if indFDA>-1 then
         begin
           ind:= 0; uzol:= '';

          { stav uzla [0,1] / zatial o tom nemam informaciu }
           j:= 0;
           move(j,uzol[ind],sizeof(j)); inc(ind,sizeof(j));

          { stav spojenia [-1,0,1] }
           if NODEs^[i].stat.node_ON then
              begin
                if NODEs^[i].stat.trasaOK then j:= 1
                else j:= -1;
              end
           else j:= 0;
           move(j,uzol[ind],sizeof(j)); inc(ind,sizeof(j));

          { zapis do buffera }
           if (size+ind < size_of_NETpkt) then
              begin
                move(uzol[0],buff^[size],ind);
                inc(size,ind);
              end;
         end;

       NETsend_msg (NODEs^[FDAnode].desc.adr, spr__FDA_NODES_STATUS, buff,size, false,net_flag_SEND);
       freemem(buff,size_of_NETpkt);
     end;


 procedure send2FDA_timeout(ods: TNETadr; id: PNETpkt_head);
     var   buff  : string;
           size,nd : int;
           cislo : byte;
           w : word;
     begin
       if (not send2FDA) or (id=nil) then Exit;

       nd:= is_NETadr(ods);
       if (nd<0) or (NODES^[nd].desc.indFDA<0) then Exit;

       size:= 0; buff:= '';

      { poradove cislo uzla }
       cislo:= NODES^[nd].desc.indFDA;
       move(cislo,buff[size],sizeof(cislo)); inc(size,sizeof(cislo));

      { typ spravy }
       w:= id^.typ;
       buff[size]:= chr(lo(w)); inc(size);
       buff[size]:= chr(hi(w)); inc(size);

      { poradove cislo paketu }
       w:= id^.cis;
       buff[size]:= chr(lo(w)); inc(size);
       buff[size]:= chr(hi(w)); inc(size);

      { cislo paketu z paketov pre jedno pole dat }
       w:= id^.ind;
       buff[size]:= chr(lo(w)); inc(size);
       buff[size]:= chr(hi(w)); inc(size);

      { pocet paketov jedneho pola dat }
       w:= id^.poc;
       buff[size]:= chr(lo(w)); inc(size);
       buff[size]:= chr(hi(w)); inc(size);

       NETsend_msg (NODEs^[FDAnode].desc.adr, spr__FDA_NODE_TIMEOUT, @buff[0],size, false,net_flag_SEND);
     end;



 procedure TFDP_NET.nodeON(ods: TNETadr; _node_init,_node_on,_init_en: bool);
     begin
       inherited nodeON(ods,_node_init,_node_on,_init_en);
       if _node_init and (_node_on or _init_en) and (is_NETadr(ods) = FDAnode) then
          begin
            send2FDA_nodes;
            send2FDA_status;
          end;
     end;

 procedure TFDP_NET.nodeOFF(ods: TNETadr; _node_off: bool; id: PNETpkt_head);
     begin
       inherited nodeOFF(ods, _node_off,id);
       if id<>nil then
          begin
            send2FDA_timeout(ods,id);
            send2FDA_status;
          end;
     end;


 procedure TFDP_NET.check_nodes;
     const min : byte = 60;
     begin
       inherited check_nodes;
       if send2FDA and (min<>BIOS.min) then
          begin
            min:= BIOS.min;
            if     (FDAnode>=0)
               and (NODEs^[FDAnode].stat.Node_ON)
               and (NODEs^[FDAnode].stat.trasaOK)
               then send2FDA_status;
          end;
     end;


 function  TFDP_NET.id__distributed_data
                        ( typ     : word;
                          p_data  : pointer;
                          send_to : PBplan_rec
                        ): PNETpkt_head;

    var    data : string;
           pkt  : TNETpkt;
           id   : PNETpkt_head;
           i    : int;
    begin
     { Odosle vzor paketu kodovaneho v textovej forme
       ku FDA v jeho protokole, aby mohol spravu zobrazit
       ako nedorucenu...

       Jednoduche by to bolo, keby vsetky smery pouzivali
       rovnako kodovanie...
     }
      id__distributed_data:= nil;
      if not send2FDA then Exit;

      if (send_to <> nil) then
         begin
           i:= 0;
           while     (i<NODEpoc)
                 and (   (NODEs^[i].desc.indFDA<0)
                      or (send_to^[i]=false)
                     )
           do inc(i);
           if i=NODEpoc then Exit;
         end;

      id:= nil;
      data:= '';
      case typ of
        {$IFDEF FPL0}
         spr_FPLC,spr0_cFPL,spr0_RDP_cFPL :
           data:= PDcFPL(p_data)^.idn+#0 + codekey_FPLC(PDcFPL(p_data))+#0;

         spr_FPLM,spr0_mFPL,spr0_RDP_mFPL :
           data:= PDmFPL(p_data)^.idn+#0 + codekey_FPLM(PDmFPL(p_data))+#0;

         {spr_EST_CNL,spr0_RDP_EST_DEL : }
        {$ENDIF}

        {$IFDEF PRS}
         spr_PRS,spr0_PRS,spr0_RDP_PRS,spr0_RDPNX_PRS,
         spr_PRS_CNL,spr0_RDP_PRS_DEL
         :
           data:= PPRS(p_data)^.kod+#0 + codekey_PRS(PPRS(p_data))+#0;
        {$ENDIF}
      end;

      if data<>'' then
         begin
           net_pkt_head (pkt, spr__FDA_NODE_MESSAGE,NODEs^[FDAnode].desc.adr);
           net_pkt_data (pkt, length(data),@data[1]);
           getmem(id,sizeof(PNETpkt_head));
           id^:= pkt.head;
           NETsend_pkt (pkt, net_flag_SEND,false,'',nil,true);
           id^.typ:= typ;
         end;

      (*case typ of

        {$IFDEF FPL0}
         spr_FPLC,spr0_cFPL,spr0_RDP_cFPL :
             begin
               send_cFPL(PDcFPL(p_data), NODEs^[FDAnode].desc.adr, false);
               getmem(id,sizeof(PNETpkt_head));
               id^:= lastDataHead;
             end;

         spr_FPLM,spr0_mFPL,spr0_RDP_mFPL :
             begin
               send_mFPL(PDmFPL(p_data), NODEs^[FDAnode].desc.adr, false);
               getmem(id,sizeof(PNETpkt_head));
               id^:= lastDataHead;
             end;
        {$ENDIF}

        {$IFDEF PRS}
         spr_PRS,spr0_PRS,spr0_RDP_PRS,spr0_RDPNX_PRS :
             begin
               send_PRS(PPRS(p_data), NODEs^[FDAnode].desc.adr, false);
               getmem(id,sizeof(PNETpkt_head));
               id^:= lastDataHead;
             end;
        {$ENDIF}

      end;*)

      id__distributed_data:= id;
    end;


 procedure testFDAnodes;
     begin
       send2FDA_nodes;
       send2FDA_status;
     end;


{$ENDIF}