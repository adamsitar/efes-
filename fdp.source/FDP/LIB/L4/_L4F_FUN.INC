{ Implementacia spracovania prijateho planu
  a jeho rozoslania
  na ostatne smery i mimo LETVIsu
}

{$IFDEF FPL0}

  procedure O_L4_FDP._process_message_FPLC (dst: set_fdp_src; head: Thead_ICAO; stat: string; FPLp,FPL: PDcFPL);
      begin
      { zaradenie a rozoslanie spravy FPLC
      } zarad_FPLc(FPL,stat,true,src_type)
      end;

 {$IFNDEF FPLM_DISABLED}
  procedure O_L4_FDP._process_message_FPLM (dst: set_fdp_src; head: Thead_ICAO; stat: string; FPLp,FPL: PDmFPL);
      begin
      { zaradenie a rozoslanie spravy FPLM
      } zarad_FPLm(FPL,stat,true,src_type)
      end;
 {$ENDIF}

{$ENDIF}


{$IFDEF PRS}

  function  O_L4_FDP._is_process_PRS (PRSp,PRS: PPRS): bool;
      begin
        _is_process_PRS:= chg_PRS(@PRSp,PRS);
      end;

  procedure O_L4_FDP._process_message_PRS (dst: set_fdp_src; head: Thead_ICAO; stat: string;
                                           hladany: bool;
                                           p,PRS: PPRS
                                          );
      var   PRSp : TPRS;
            pi   : PPRS;
            ires : int;
      begin
        PRS^.stat:= stat;
        pi:= nil; ires:= -1;
        if (hladany) or (p<>nil) then pi:= p
        else begin
               ires:= read_PRS(codekey_PRS(PRS),@PRSp);
               if (ires>=0) then pi:= @PRSp;
             end;
        if (pi=nil) or _is_process_PRS(pi,PRS) then zarad_PRS(PRS,PRS^.stat,true,src_type);
        if (ires>=0) then disp_PRS(@PRSp)
      end;

{$ENDIF}



procedure O_L4_FDP._send_co_ordinate_message (src: fdp_src; dst: set_fdp_src;
                                              typ: TNETtyp; head: Thead_ICAO;
                                              zmeneny: bool;
                                              var plan
                                             );
    begin
      case typ of
        0         : ;

       {$IFDEF FPL0}
        spr_FPLC  : if    ((DcFPL(plan).stt=hd_EST) and (strpos(coor_info,inf_FPLC)<>nil))
                       or (strpos(coor_info,hd_CPL)<>nil)
                       then _send_message_FPLC(head, zmeneny, DcFPL(plan));

       {$IFNDEF FPLM_DISABLED}
        spr_FPLM  : if    ((is_mFPL(@(DmFPL(plan)))) and (strpos(coor_info,inf_FPLM)<>nil))
                       or ((not is_mFPL(@(DmFPL(plan)))) and (strpos(coor_info,inf_FPLO)<>nil))
                       then _send_message_FPLM(head, zmeneny, DmFPL(plan));
       {$ENDIF}
       {$ENDIF}

       {$IFDEF PRS}
         spr_PRS  : if _is_to_send_message_PRS(zmeneny,TPRS(plan)) then _send_message_PRS(head, zmeneny, TPRS(plan));
         {$IFDEF FUA_DATA}
          spr_AUP  : if ((strpos(coor_info,inf_FUA)<>nil)) then _send_message_AUP(head, zmeneny, string(plan));
          spr_UUP  : if ((strpos(coor_info,inf_FUA)<>nil)) then _send_message_UUP(head, zmeneny, string(plan));
         {$ENDIF}
       {$ENDIF}
      end;
    end;



{ Rozoslanie planu
  na ostatne smery
  i mimo LETVIsu
}

{$IFDEF FPL0}

  procedure O_L4_FDP._send_message_FPLC(head: Thead_ICAO; zmeneny: bool; var FPL: DcFPL);
      begin
       {$IFDEF FPL4}
         if      head = hd_CPL then send_CPLc (FPL)
         else if head = hd_EST then send_ESTc (FPL)
       {$ENDIF}
      end;


 {$IFNDEF FPLM_DISABLED}
  procedure O_L4_FDP._send_message_FPLM(head: Thead_ICAO; zmeneny: bool; var FPL: DmFPL);
      begin
       {$IFDEF FPL4}
        if not (     zmeneny
                and (send_VFR_FPL or (not is_VFR_FPLM(@FPL)) {(get_altM(FPLm.vys_,FPLm.vys)>alt_VFR)})
               ) then Exit;

        if      head = hd_FPL then send_FPLm (FPL)
        else if head = hd_CHG then send_CHGm (FPL)
        else if head = hd_DLA then send_DLAm (FPL)
        else if head = hd_CNL then send_CNLm (FPL)
        else if head = hd_ARR then send_ARRm (FPL)
        else if    (head = hd_CLR)
                or (head = hd_DEP)
                or (head = hd_ABI)
                or (head = hd_ACT) then send_ACTm (FPL)
       {$ENDIF}
      end;
 {$ENDIF}

{$ENDIF}
