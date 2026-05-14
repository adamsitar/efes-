{ --------------
   Prijaty plan
  --------------
}

 { hlasenia sa zobrazuju len na plany, ktore sa daneho pracoviska tykaju,
   napr. plany podane alebo schvalene/zamietnute od/pre A-A,
   ziadosti na pracovisku schvalenia (AMC)
   alebo priebeh spracovania na ...

   is_this_airbase(PRS^.let)
 }

  procedure _pkt_PRS(PRS: PPRS);
      var   rep, sttp: string;
            PRSp: TPRS;
            p: pchar;
            is: bool;

      label X;

      begin
        sttp:= PRS^.stat;
        {PRS^.stat:= del_stat(PRS^.stat,cnst_chg);  aby sa nobjavovala sprava o oprave... }
        is:= read_PRS(codekey_PRS(PRS),@PRSp)>-1;
        if is then
           begin
             if (not chg_PRS (PRS,@PRSp)) then goto X;
             PRS^.oprava:= (PRS^.stat = PRSp.stat);

           { prepis hodnot }
             PRS^.vys1_aup := PRSp.vys1_aup;
             PRS^.vys2_aup := PRSp.vys2_aup;
             PRS^.zac_aup  := PRSp.zac_aup;
             PRS^.kon_aup  := PRSp.kon_aup;
           end;

        {$IFDEF AMC}
          { zmena genegeruje zmenu... => UUP
          }
        {$ENDIF}

        {$IFDEF PRS_REPORT}
           if (reports_FDP<>nil) then
              begin
                rep:= ''; {decode_stat_act (sttp);}

                {$IFDEF A-A}
                  if
                     (   ({ vlastne ziadosti }
                          hlas_PRS_plan and _plan_pre_pracovisko(PRS) and __is_stat (sttp,cnst_req_approved)
                         )
                      or ({ aktivity ostatnych }
                          hlas_PRS_act  and (not _plan_pre_pracovisko(PRS)) and __is_stat (sttp,cnst_stat_actived)
                         )
                     )
                     then rep:= decode_stat_act (sttp);
                {$ELSE}

                {$IFDEF AMC}
                 if      ( { ziadosti... }
                           hlas_PRS_plan and __is_stat (sttp,cnst_planned)
                         ) then rep:= st_plan

                 else if ( { priebeh ... }
                           hlas_PRS_act  and __is_stat (sttp,cnst_stat_actived)
                         ) then rep:= decode_stat_act (sttp);

                {$ELSE}
                      if ( { priebeh ... }
                           hlas_PRS_act  and __is_stat (sttp,cnst_stat_actived)
                         ) then rep:= decode_stat_act (sttp);

                {$ENDIF}

                {$ENDIF}

                if rep<>'' then
                   begin
                     p:= code_l4_PRS_(PRS,'');
                     reports_FDP^.save_rep
                        (spr_PRS,'',codekey_PRS(PRS),
                         rep+' '+tit_PRS_+' ('+PRS^.kod+')',
                         strlen(p),pchars(p)
                        );
                     strdispose(p)
                   end;
              end;
        {$ENDIF}

        zarad_PRS (PRS,PRS^.stat,true,letvis);

        X: if is then disp_PRS(@PRSp)
      end;



{ --------------------
   Prijate potvrdenie
  --------------------
}
 procedure _codeDBB_PRSrec (src: Pplan_rec; buff: PDB_riadok; head: PDB_head); far;
     var   size : int;
           s,t  : string;
           i : int;
           p : pchars;
           rec : Tplan_rec;
     begin
       s:= DBstr_to_str_ (buff^); p:= @s[1];
       get_s (p, @rec,sizeof(rec));
       rec_copy (src^,rec);
       s:= '';
       add_s (@rec,sizeof(rec), s,t);
       str_toDBstr_ (s,buff^)
     end;

 procedure _codeDBB_PRSnd (nd: pint; buff: PDB_riadok; head: PDB_head); far;
     var   size : int;
           s,t  : string;
           i : int;
           p : pchars;
           rec : Tplan_rec;
     begin
       s:= DBstr_to_str_ (buff^); p:= @s[1];
       get_s (p, @rec,sizeof(rec));
       rec_pkt (nd^,rec,is_ack);
       s:= '';
       add_s (@rec,sizeof(rec), s,t);
       str_toDBstr_ (s,buff^)
     end;


 procedure _ack_PRS(key: string; rec: Tplan_rec; fdp: bool; nd: int);
     var   PRS  : TPRS;
           plan : PPRS;
           p1,p2 : pointer;
           i : int;
     begin
       plan:= nil;
       if (PRSs<>nil) then
          begin
            i:= PRSs^.find_key(key);
            if i>-1 then plan:= PPRS(PRSs^.ap^[i])
          end;

       if NET_ACK_ALL then
          begin
            if plan<>nil then rec_copy (rec, plan^.rec);
            p1:= @rec;
            p2:= @_codeDBB_PRSrec
          end
       else begin
              if plan<>nil then rec_pkt (nd, plan^.rec,is_ack);
              p1:= @nd;
              p2:= @_codeDBB_PRSnd
            end;
       if not fdp then Exit;

       decodekey_PRS(key,@PRS);
       DB_oprav_riadok (p1,nil,key,
                        get_dbPRSifn(@PRS),db_PRS_RIADKOV,
                        @codeDB_PRS,@codekey_PRS,
                        db_PRS_ine,p2,
                        dbattr_PRS
                       );
     end;


{ --------------------
   Inicializacia uzla
  --------------------
}
