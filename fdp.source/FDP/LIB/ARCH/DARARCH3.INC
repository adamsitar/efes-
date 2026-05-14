{ ---------------------------------------- }
{  ulozenie dat                            }
{ ---------------------------------------- }

procedure save_FDP(typ: word; p_data: pointer; p_code: Pcode_NETpkt_data);
    var   Np  : TNETpkt;
          res : word;
         {$IFDEF IPX}
          Rp        : TRTRpkt_bin;
          dlz       : word;
          len_ok    : bool;
         {$ENDIF}
         {$IFDEF UDP}
          Up        : TUDPdata;
          size      : word;
         {$ENDIF}
    begin
     fillchar(Np,sizeof(Np),0);
     if (p_data=nil) or (p_code=nil) then Exit;

     if NODEpoc>0 then Np.adr:= NODEs^[posRLI_ARCH].desc.adr
     else Np.adr:= NETaddress;
     net_pkt_head (Np,typ, Np.adr);
     Tcode_NETpkt_data(p_code)(p_data,Np);

     {$IFDEF IPX}
       dlz:= code_NETpkt_to_RTRpkt(@Np,@Rp,nil,rpRTI, len_ok);
       save_DARpacket(@Rp, dlz, SaveStrip);
     {$ENDIF}
     {$IFDEF PCTCP}
       size:= code_NETpkt_to_RTCpkt (Np,Up,size,rspr_RTR);
       save_DARpacket(@Up, size, SaveStrip);
     {$ENDIF}

      disp_NETpkt(@Np)
    end;

procedure save_RLI(data: pbytes; data_length: word);
    begin
      save_DARpacket(data, data_length, SaveRLI)
    end;

