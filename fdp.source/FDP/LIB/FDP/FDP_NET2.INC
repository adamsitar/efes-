 procedure TFDP_NET.decode_app_ack_pkt(var pkt: TNETpkt);
     var   key : string;
           nd  : int;
           rec : Tplan_rec;
           fdp : bool;
     begin
       nd:= is_NETadr(pkt.ods);
       fillchar(rec,sizeof(rec),0);
       fdp:= false;

       if NET_ACK_ALL then
          begin
            read_ack_pkts (@pkt,key,rec,fdp);
          end
       else begin
              if (nd<0) {or (NODEs^[nd].desc.typ in [RDP0,RDP0NX,RDP,MON])} then Exit;
              fdp:= (not (NODEs^[nd].desc.typ in [RDP0,RDP0NX,RDP,MON]));
              key[0]:= chr(Minimum(sizeof(key),pkt.pkt.dlz));
              move(pkt.pkt.data^[0],key[1],ord(key[0]));
              if key='' then Exit;
            end;

       case pkt.head.typ of

         0 : ;

         {$IFDEF SPR}
          ack_SPR               : _ack_SPR(key,rec,fdp,nd);
         {$ENDIF}


         {$IFDEF FPL4}
          ack_FPL4,ack0_FPL4    : _ack_FPL4(key,rec,fdp,nd);
         {$ENDIF}

         {$IFDEF PLN}
          ack_PLN,ack0_PLN      : _ack_PLN(key,rec,fdp,nd);
         {$ENDIF}

         {$IFDEF FPL0}
          ack_FPLC,ack0_cFPL,
          ack0_RDP_cFPL         : _ack_FPLC(key,rec,fdp,nd);
         {$IFNDEF FPLM_DISABLED}
          ack_FPLM,ack0_mFPL,
          ack0_RDP_mFPL         : _ack_FPLM(key,rec,fdp,nd);
         {$ENDIF}
         {$ENDIF}


         {$IFDEF ZAM}
          ack_ZAM,ack0_ZAM      : _ack_ZAM(key,rec,fdp,nd);
         {$ENDIF}

         {$IFDEF DVZ}
          ack_DVZ,ack0_DVZ      : _ack_DVZ(key,rec,fdp,nd);
         {$ENDIF}

         {$IFDEF QGO}
          ack_QGO,ack0_QGO      : _ack_QGO(key,rec,fdp,nd);
         {$ENDIF}

         {$IFDEF RTZ}
          ack_RTZ               : _ack_RTZ(key,rec,fdp,nd);
         {$ENDIF}


         {$IFDEF PRZ}
          ack_PRZ,ack0_PRZ           : _ack_PRZ(key,rec,fdp,nd);
          ack_PRN,ack0_PRN           : _ack_PRN(key,rec,fdp,nd);
          ack_PRN_VLIS,ack0_PRN_VLIS : _ack_VLIS(key,rec,fdp,nd);
         {$ENDIF}


         {$IFDEF PRS}
          ack_PRS,
          ack0_PRS,
          ack0_RDP_PRS,
          ack0_RDPNX_PRS : _ack_PRS (key,rec,fdp,nd);
         {$ENDIF}

         {$IFDEF FUA_DATA}
          ack_AUP               : _ack_AUP (key,rec,fdp,nd);
          ack_UUP               : _ack_UUP (key,rec,fdp,nd);
         {$ENDIF}


         {$IFDEF MET}
          ack_SYNOP,ack0_SYN    : _ack_SYN(key,rec,fdp,nd);
          {ack0_MET,ack_METAR   : _ack_MET(key,rec,fdp,nd);}
         {$ENDIF}

         else

         {$IFDEF AFTN} {$IFDEF SYNCHRONIZE_EXT}
          if DEV_AFTN<>nil then DEV_AFTN^.decode_NETpkt(pkt)
         {$ENDIF} {$ENDIF}
       end
     end;
