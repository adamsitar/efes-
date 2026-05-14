{ --------------
   Prijaty plan
  --------------
}

 procedure _pkt_RTZ(RTZ: PRTZ);
     var   rep, sttp : string;
           RTZp : TRTZ;
           p : pchar;
     label X;

     begin
       {sttp:= RTZ^.stat;}
       if (read_RTZ(codekey_RTZ(RTZ),@RTZp)>-1) and (not chg_RTZ (RTZ,@RTZp)) then goto X;
       {RTZ^.stat:= sttp;}

       {$IFDEF RTZ_REPORT}
        rep:= rep_schopnost;
        if     (rep<>'')
           and (reports_FDP<>nil)
           and hlas_RTZ
           and is_this_date(RTZ^.date, year,month,day)
           then
             begin
               p:= code_l4_RTZ_(RTZ,'');
               reports_FDP^.save_rep
                 (spr_RTZ,'',codekey_RTZ(RTZ),
                  rep_schopnost+' ('+RTZ^.kod+')',
                  strlen(p),pchars(p)
                 );
               strdispose(p)
             end;
       {$ENDIF}

       zarad_RTZ(RTZ,'',true,letvis);

       X: disp_RTZ(@RTZp)
     end;


{ --------------------
   Prijate potvrdenie
  --------------------
}
 procedure _ack_RTZ(key: string; rec: Tplan_rec; fdp: bool; nd: int);
     var   RTZ : TRTZ;
     begin
       if read_RTZ(key, @RTZ)<>-1 then
          begin
            if NET_ACK_ALL then
               begin
                 rec_copy (rec,RTZ.rec);
               end
            else begin
                   rec_pkt (nd,RTZ.rec,is_ack);
                 end;
            save_RTZ(@RTZ);
            disp_RTZ(@RTZ)
          end
     end;


{ --------------------
   Inicializacia uzla
  --------------------
}
