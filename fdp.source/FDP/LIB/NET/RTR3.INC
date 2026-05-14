  { --------------
     send
    --------------
  }
  function _RTRsend(const Np: TNETpkt): int;
     var   Rp    : PRTRpkt_bin;
           dlz   : word;
           whole : bool;
     begin
      {$IFDEF IPX}
        New(Rp);
        dlz:= code_NETpkt_to_RTRpkt(Np,Rp^,nil,rpRTR, whole);
        if (ROUTERipx>-1) and (dlz>0) and (whole) then _RTRsend:= ipx_send(ROUTERipx, dlz, Rp)
        else _RTRsend:= netNOT_SENDED; {netRES_OK}
        Dispose(Rp)
      {$ELSE}
        _RTRsend:= netRES_OK
      {$ENDIF}
     end;

  function _RTIsend(Np: TNETpkt): int;
     var   Rp    : PRTRpkt_bin;
           dlz   : word;
           adr   : TNETadr;
           nd,ires : int;
           whole : bool;
     begin
       New(Rp); ires:= netNOT_SENDED;

       {$IFDEF IPX}
        adr:= NETadr_lan_(Np.adr);
        nd:= isIPXname(adr);
        if nd>-1 then
           begin
             dlz:= code_NETpkt_to_RTRpkt(Np,Rp^,nil,rpRTI, whole);
             if (dlz>0) and (whole) then ires:= ipx_send(nd, dlz, Rp)
             else ires:= netNOT_SENDED {netRES_OK}
           end
        else ires:= netBAD_ADDR;
       {$ENDIF}

       {$IFDEF ARCHIVE_NET_BIN}
        archive_data (path_NET,get_ARCHfn(0)+'.'+extNET,pbytes(Rp),dlz,'RTIo,'+cstr(nd,1)+','+cstr(ires,1),true,false);
       {$ENDIF}

       Dispose(Rp);
       _RTIsend:= ires
     end;

  (*
  function _RTUsend(Np: PNETpacket; Rp: PRTRpkt_bin): int;
     var   dlz : word;
     begin
       {$IFDEF PCTCP}
         dlz:= code_NETpkt_to_RTRpkt(Np,Rp,nil,rpRTI);
         if dlz>0 then _RTUsend:= udp_send('',NETadr_tcp(Np^.head.adr), dlz,Rp)
         else _RTUsend:= netNOT_SENDED {netRES_OK}
       {$ELSE}
         _RTUsend:= netRES_OK
       {$ENDIF}
     end;
  *)

  function RTRsend(const Np: TNETpkt): int;
     begin
       case NETprotocol(Np.adr) of
         RTR : RTRsend:= _RTRsend(Np);
         RTI : RTRsend:= _RTIsend(Np);
        {RTU : RTRsend:= _RTUsend(Np)}
         else  RTRsend:= netNOT_SENDED
       end;
     end;

  function RTBsend(const Np: TNETpkt): int;
     var   Rp    : PRTRpkt_bin;
           dlz   : word;
           whole : bool;
     begin
      {$IFDEF IPX}
       New(Rp);
       dlz:= code_NETpkt_to_RTRpkt(Np,Rp^,nil, rpRTB, whole);
       if (ROUTERipx>-1) and (dlz>0) and (whole) then RTBsend:= ipx_send(ROUTERipx, dlz, Rp)
       else RTBsend:= netNOT_SENDED; {netRES_OK}
       Dispose(Rp)
      {$ELSE}
       RTBsend:= netNOT_SENDED; {netRES_OK}
      {$ENDIF}
     end;


  { -------------
     distribute
    -------------
  }
  function  RTIdistribute (Np: TNETpkt; distribute: PBplan_rec): int;
     var   i: int;
     begin
       if distribute<>nil then
          begin
            for i:= 0 to NODEpoc-1 do
                if distribute^[i] then
                   begin
                     Np.adr:= NODEs^[i].desc.adr;
                     _RTIsend(Np)
                   end;
            RTIdistribute:= netRES_OK
          end
       else RTIdistribute:= _RTIsend(Np)
     end;


  function RTRdistribute(Np: TNETpkt; distribute: PBplan_rec): bool;
     var   Rp       : PRTRpkt_bin;
           dlz,i    : word;
           send_rtr : TBplan_rec;
           send_rti : TBplan_rec;
           adr      : TNETadr;
           is_rtr,is_rti,res,whole : bool;

     begin
       RTRdistribute:= false;
       if distribute=nil then Exit;
       res:= false;

       {$IFDEF IPX}
         New(Rp);
         is_rtr:= false; is_rti:= false;
         fillchar(send_rtr,sizeof(send_rtr),0);
         fillchar(send_rti,sizeof(send_rti),0);

         for i:= 0 to NODEpoc-1 do
           begin
             if NODEs^[i].desc.pro=RTR then
                begin
                  send_rtr[i]:= distribute^[i];
                  is_rtr:= true
                end;
             if NODEs^[i].desc.pro=RTI then
                begin
                  send_rti[i]:= distribute^[i];
                  is_rti:= true
                end;
           end;

         if is_rtr and (ROUTERipx>-1) then
            begin
              dlz:= code_NETpkt_to_RTRpkt(Np,Rp^, @send_rtr, rpRTR, whole);
              if dlz>0 then
                 if whole then res:= NETres(ipx_send(ROUTERipx, dlz, Rp))
                 else begin
                       { vela adries, ubera to na dlzke dat paketu... }
                        adr:= Np.adr;
                        for i:= 0 to NODEpoc-1 do
                          if send_rtr[i] then
                             begin
                               Np.adr:= NODEs^[i].desc.adr;
                               res:= res or NETres(RTRsend(Np))
                             end;
                        Np.adr:= adr
                      end
            end;
         if is_rti then res:= NETres(RTIdistribute(Np, @send_rti)) or res;

         Dispose(Rp);
       {$ENDIF}

       RTRdistribute:= res
     end;
