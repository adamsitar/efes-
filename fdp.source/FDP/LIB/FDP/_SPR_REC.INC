{ ----------------
   Prijata sprava
  ----------------
}
 procedure _ack_SPR(key: string; rec: Tplan_rec; fdp: bool; nd: int);
     var   SPR : DSPR;
     begin
       if read_SPR(key, @SPR)<>-1 then
          begin
            if NET_ACK_ALL then
               begin
                 rec_copy (rec,SPR.rec);
               end
            else begin
                   rec_pkt(nd,SPR.rec,is_ack);
                 end;
            save_SPR(@SPR);
            disp_SPR(@SPR)
          end
     end;


 procedure _pkt_SPR_REC(const pkt: TNETpkt);
     var   SPR: DSPR;
     begin
       decode_SPR(pkt,@SPR);
       save_SPR(@SPR);
       reports_SPR^.save_rep(pkt.head.typ, SPR.ods, codekey_SPR(@SPR),tit_MSG, 0,nil);
       {$IFDEF STATISTIKA_SERVER}
        if p_save_STA_SPR<>nil then TProc_p(p_save_STA_SPR)(@SPR);
       {$ENDIF}
       disp_SPR(@SPR)
     end;


 procedure _pkt_SPR_LAM(const pkt: TNETpkt);
     var   SPR,SPRi : DSPR;
           s : string;
           nd : int;
           {zapis : bool;}
     begin
       if    (pkt.head.typ = spr_SPR_LAM)
          or ((pkt.head.typ = spr0_SPR_LAM) and (pkt.pkt.data^[0]=_spr0_ack))
          then
            begin
              s:= decode_SPR_LAM(pkt,SPR{,zapis});
              if {zapis and} (read_SPR(codekey_SPR(@SPR),@SPRi)>-1) then
                 begin
                   { zapis potvrdenia }
                   if (not _adrmult(SPR.adr)) and (not _adrbrc(_adri(@SPR,1))) then
                      begin
                        if (SPR.daz.rok<>0) then SPRi.daz:= SPR.daz;
                      end;
                   {$IFDEF NET}
                    nd:= is_NETadr  (pkt.ods);
                    if nd>-1 then
                       begin
                         SPRi.acc[nd]:= SPR.acs;
                         rec_pkt_ (nd,SPRi.rec,is_ack,false);
                       end;
                   {$ENDIF}
                   save_SPR(@SPRi);
                   disp_SPR(@SPRi)
                 end;
              reports_SPR^.save_rep(spr_SPR_LAM,pkt.ods, msgACCEPT,s, 0,nil);
              disp_SPR(@SPR)
            end;
     end;


{ --------------------
   Prijate potvrdenie
  --------------------
}


{ --------------------
   Inicializacia uzla
  --------------------
}


{ --------------------
  Spracovanie hlasenia
  --------------------
}

  procedure process_report_SPR(const REP: TREP);
      var   res : bool;
            SPR : DSPR;
            kod : TNETtyp;
            s   : string;
            t_o : bool;
      begin
        case REP.kod of

          spr_SPR, spr0_SPR :
            begin
               if read_SPR(REP.kluc, @SPR)=-1 then Exit;
               datum_init (SPR.daz, day,month,year, hour,min,sec);
               save_SPR(@SPR);
               Beep2;

               write_acc:= false;
               res:= info_SPRr_ (@SPR, REP.text,titPOTVRD, true, waitSPRAVA*18, t_o);
               if res then SPR.acs:= _accepted
               else if not t_o then SPR.acs:= _cancelled
               else SPR.acs:= _unprocessed;
               if REP.kod = spr_SPR then kod:= spr_SPR_LAM
               else kod:= spr0_SPR_LAM;
               s:= code_SPR_LAM(@SPR,kod);
               NETsend_msg (SPR.ods, kod, @s[1],length(s), false,net_flag_SEND);
               save_SPR(@SPR);
               disp_SPR(@SPR);

               isSPR:= isSPR or (not res)
             end;

          spr_SPR_LAM, spr0_SPR_LAM :
            begin
              Say(REP.kluc,REP.text,black,clGRe, @Beep1,@Beep3, waitINFO*18{waitackSPRAVA}, 0,nil,nil)
            end;

        end;
      end;
