 procedure _report_FDP(const rep : TREP;
                       item_size : word;
                       p_disp_item   : PProc_p;
                       p_decode_item : Pdecode_l4_data;
                       p_read_item   : Pdbread_key_data;
                       p_info_proc   : Pdisplay_plan
                      );
     var   item : pointer;
           res  : bool;
     begin
       GetMem(item,item_size); FillChar(item^,item_size,0);
       res:= false;
       if p_decode_item<>nil then
          begin
            Tdecode_l4_data(p_decode_item)(rep.data,rep.dlz,pchars(item)^);
            res:= true
          end
       else if     (p_read_item<>nil)
               and (TdbRead_key_data(p_read_item)(rep.kluc,item)<>-1)
               then res:= true;
       if res and (p_info_proc<>nil) then Tdisplay_plan(p_info_proc)(item,rep.text);
       if p_disp_item<>nil then TProc_p(p_disp_item)(item);
       FreeMem(item,item_size)
     end;



{$IFDEF FPL4_ACT}

  procedure decode_pkt_REQ_MES (ods: TNETadr; data: pchars; dlz: TNETdlz); far;
      var   res : string;
      begin
        {Tdecode_l4_data(p_decode_item)(rep.data,rep.dlz,pchars(item)^);
        decode_msg (pkt,@res);
        Say2(res)}
      end;

(*
  procedure decode_pkt_REQ_FPLc (ods: TNETadr; data: pchars; dlz: TNETdlz); far;
      var   act : P_REQUEST_ACT_cFPL;
            pkt : TNETpkt;
      begin
        new(act); fillchar(act^,sizeof(act^),0);
        fillchar(pkt,sizeof(pkt),0);
        pkt.pkt.data:= data;
        pkt.pkt.dlz := dlz;
        decode_cFPL(pkt,@act^.FPL);
        act^.is:= true;
        odpoved_ACT_cFPL(act);
        dispose(act)
      end;

 {$ENDIF}


 {$IFDEF FPD}

  procedure decode_pkt_REQ_ACT (ods: TNETadr; data: pchars; dlz: TNETdlz);
      var   key : string;
      begin
        key[0]:= chr(N(minimum(dlz-1{#0},sizeof(key)-1)));
        move(data^,key[1],ord(key[0]));
        REQ_EST(ods,key)
      end;

 {$ENDIF}

 procedure process_report_FPL4(const REP: TREP); far;
     begin
       case REP.kod of

         0 :   ;

        {$IFDEF FPL4}
         spr_FPL4     : _report_FDP(REP, sizeof(DFPL4), @disp_FPL4, @decode_l4_FPL4_, @read_FPL4, @info_FPL4);
        {$ENDIF}

        {$IFDEF FPD}
         spr_REQ_ACT  : decode_pkt_REQ_ACT  (REP.ods, REP.data,REP.dlz);
        {$ENDIF}

        {$IFDEF FPL4_ACT}
         spr_REQ_MES  : decode_pkt_REQ_MES  (REP.ods, REP.data,REP.dlz);
         spr_REQ_EST  : decode_pkt_REQ_FPLc (REP.ods, REP.data,REP.dlz);
        {$ENDIF}

       end
     end;
*)

{$ENDIF}

 procedure process_report_FDP(const REP: TREP); far;
     begin
       case REP.kod of

          spr_SAY   : Say2(msgMESS,REP.text);

         {$IFDEF FPL4}
           spr_FPL4 : _report_FDP(REP, sizeof(DFPL4), @disp_FPL4, @decode_l4_FPL4_, @read_FPL4, @info_FPL4);

           spr_FPL4_MES,
           spr_FPL4_REQ,
           spr_FPL4_DATA : ;
         {$ENDIF}

         {$IFNDEF FPLM_DISABLED}
         {$IFDEF FPL0}
           spr_FPLM : _report_FDP(REP, sizeof(DmFPL), @disp_mFPL, @decode_l4_FPLM_, @read_mFPL, @info_mFPL);
         {$ENDIF}
         {$ENDIF}

         {$IFDEF ZAM}
           spr_ZAM  : _report_FDP(REP, sizeof(TZAM),  @disp_ZAM, @decode_l4_ZAM_, @read_ZAM, @report_ZAM);
         {$ENDIF}

         {$IFDEF DVZ}
           spr_DVZ  : _report_FDP(REP, sizeof(TDVZ),  @disp_DVZ, @decode_l4_DVZ_, @read_DVZ, @report_DVZ);
         {$ENDIF}

         {$IFDEF QGO}
           spr_QGO  : _report_FDP(REP, sizeof(TQGO),  @disp_QGO, @decode_l4_QGO_, @read_QGO, @report_QGO);
         {$ENDIF}

         else
       end;
     end;
