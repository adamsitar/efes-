 procedure TFDP_NET.receive_brc(const Bpkt : TNETBpkt {$IFDEF PCTCP}; from : T_IPaddress {$ENDIF});
     begin
      {$IFDEF PCTCP}
       if decode_rliUTC(@Bpkt.data,Bpkt.size) then
          begin
            {archivuj_data(path_NET, get_ARCHfn(0)+'.'+extNET, @Bp.data,Bp.size,'*',false,false);}
            Exit
          end;
      {$ENDIF}

      {$IFDEF TRENAZER}
       {$IFDEF PCTCP}
        receive_astSIM_pkt (@Bpkt.data,Bpkt.size, from.fhost);
       {$ENDIF}
       {$IFDEF IPX}
        Trnzr.receive_brc(Bpkt);
       {$ENDIF}
      {$ENDIF}
     end;
