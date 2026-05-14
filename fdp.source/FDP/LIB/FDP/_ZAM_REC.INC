{ --------------
   Prijaty plan
  --------------
}

 (*function _accept_ZAM(ods: TNETadr; ZAM: PZAM): bool; far;
    begin
      {$IFDEF FDP_OPL}
        {$IFDEF AIRBASE}
          _accept_ZAM:= not is_this_airbase(ZAM^.let)
        {$ELSE}
          _accept_ZAM:= true
        {$ENDIF}
      {$ELSE}
         _accept_ZAM:= true
      {$ENDIF}
    end;
 *)


 procedure _pkt_ZAM(ZAM: PZAM);
     var   rep, sttp: string;
           ZAMp: TZAM;
           p: pchar;
     label X;

     begin
       sttp:= ZAM^.stat;
       {ZAM^.stat:= del_stat(ZAM^.stat,cnst_chg);  aby sa neobjavovala sprava o oprave... }
       if (read_ZAM(codekey_ZAM(ZAM),@ZAMp)>-1) and (not chg_ZAM (ZAM,@ZAMp)) then goto X;
       ZAM^.stat:= sttp;

      {$IFDEF ZAM_REPORT}
       rep:= decode_stat_act (sttp);

       if     (rep<>'') and hlas_ZAM
          and (reports_FDP<>nil)
          and (__is_stat (sttp,cnst_stat_actived))
          {IFDEF AIRBASE and (not is_this_airbase(ZAM^.src))
          ENDIF}
          then begin
                 p:= code_l4_ZAM_(ZAM,'');
                 reports_FDP^.save_rep
                      (spr_ZAM,'',codekey_ZAM(ZAM),
                       rep+' '+tit_zam_+' ('+ZAM^.kod+')',
                       strlen(p),pchars(p)
                      );
                 strdispose(p)
               end;
      {$ENDIF}

      zarad_ZAM (ZAM,ZAM^.stat,true,letvis);

      X: disp_ZAM(@ZAMp)
    end;


{ --------------------
   Prijate potvrdenie
  --------------------
}
  procedure _ack_ZAM(key: string; rec: Tplan_rec; fdp: bool; nd: int);
      var   ZAM  : TZAM;
            plan : PZAM;
            i  : int;
            db : bool;
      begin
        db:= false;
        plan:= nil;

        if (ZAMs<>nil) then
           begin
             i:= ZAMs^.find_key(key);
             if i>-1 then plan:= PZAM(ZAMs^.ap^[i])
           end;
        if plan=nil then
           if (read_ZAM(key, @ZAM)<>-1) then
              begin
                plan:= @ZAM;
                db:= true
              end;

        if plan<>nil then
           begin
             if NET_ACK_ALL then
                begin
                  rec_copy (rec, plan^.rec);
                end
             else begin
                    rec_pkt (nd, plan^.rec,is_ack);
                  end;

             if fdp then save_ZAM(plan);
             if db then disp_ZAM(plan)
           end
      end;


{ --------------------
   Inicializacia uzla
  --------------------
}
