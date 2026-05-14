{$IFDEF RDP_ACCEPT}

 {$IFDEF DATA_BIN}

   procedure _pkt_RDP_A(const pkt: TNETpkt); far;
       var   idn  : string;
             nd   : TRTRadr;
       begin
         idn[0]:= chr(N(minimum(pkt.pkt.dlz-1,sizeof(string))));
         Move(pkt.pkt.data^[0],idn[1],length(idn));
         nd:= NETrtr_adr(pkt.ods);
         case pkt.head.typ of
           0 : ;
          {$IFDEF FPL0}
           spr0_RDP_A  : FL_ACCEPT     (idn, nd);
           spr0_RDP_UA : FL_UNACCEPT   (idn, nd);
           spr0_RDP_H  : FL_A_HANDOVER (idn, nd); { mal by som i dostat adresu handoveru }
           spr0_RDP_UH : FL_U_HANDOVER (idn, nd)
          {$ENDIF}
         end
       end;

 {$ENDIF}

   procedure _pkt_TARGET_CONTROL(const pkt: TNETpkt); far;
       var   idn  : string;
             nd   : TRTRadr;
       begin
         idn[0]:= chr(N(minimum(pkt.pkt.dlz-1,sizeof(string))));
         Move(pkt.pkt.data^[0],idn[1],length(idn));
         nd:= NETrtr_adr(pkt.ods);

         case pkt.head.typ of
           0 : ;
          {$IFDEF FPL0}
           spr_ACCEPT,
           spr_UNACCEPT,
           spr_HANDOVER,
           spr_UNHANDOVER : _pkt_RDP_A(pkt);
          {$ENDIF}
         end;
       end;

{$ENDIF}
