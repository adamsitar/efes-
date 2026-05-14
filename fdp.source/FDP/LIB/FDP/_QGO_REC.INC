{ --------------
   Prijaty plan
  --------------
}

 (*
 function _accept_QGO(ods: TNETadr; QGO: PQGO): bool; far;
    begin
      {$IFDEF FDP_OPL}
        {$IFDEF AIRBASE}
          _accept_QGO:= {not is_this_airbase(QGO^.let)} true
        {$ELSE}
          _accept_QGO:= true
        {$ENDIF}
      {$ELSE}
          _accept_QGO:= true
      {$ENDIF}
    end;
 *)

 procedure _pkt_QGO(QGO: PQGO);
     var   rep, sttp : string;
           QGOp : TQGO;
           p : pchar;
     label X;

     begin
       sttp:= QGO^.stat;
       {QGO^.stat:= del_stat(QGO^.stat,cnst_chg); aby sa neobjavovala sprava o oprave... }
       if (read_QGO(codekey_QGO(QGO),@QGOp)>-1) and (not chg_QGO (QGO,@QGOp)) then goto X;
       QGO^.stat:= sttp;

       {$IFDEF QGO_REPORT}
        rep:= rep_schopnost;
        if     (rep<>'')
           and (reports_FDP<>nil)
           and hlas_QGO
           and is_this_date(QGO^.date, year,month,day)
           then
             begin
               p:= code_l4_QGO_(QGO,'');
               reports_FDP^.save_rep
                 (spr_QGO,'',codekey_QGO(QGO),
                  rep_schopnost+' ('+QGO^.kod+')',
                  strlen(p),pchars(p)
                 );
               strdispose(p)
             end;
       {$ENDIF}

       zarad_QGO(QGO,QGO^.stat,true,letvis);

       X: disp_QGO(@QGOp)
     end;


{ --------------------
   Prijate potvrdenie
  --------------------
}
 procedure _ack_QGO(key: string; rec: Tplan_rec; fdp: bool; nd: int);
     var   QGO : TQGO;
     begin
       if read_QGO(key, @QGO)<>-1 then
          begin
            if NET_ACK_ALL then
               begin
                 rec_copy (rec,QGO.rec);
               end
            else begin
                   rec_pkt(nd,QGO.rec,is_ack);
                 end;
            save_QGO(@QGO);
            disp_QGO(@QGO)
          end
     end;


{ --------------------
   Inicializacia uzla
  --------------------
}
