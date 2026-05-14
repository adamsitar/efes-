{ --------------
   Prijaty plan
  --------------
}

 function _accept_FPLm(ods: TNETadr; FPL: PDmFPL): bool;
    var   nd: int;
    begin
     _accept_FPLm:= true;
     {$IFDEF MPU}
       nd:= is_NETadr(ods);
       if (nd>-1) and (NODEs^[nd].desc.ai<>$FF) then print_mFPL_MPU(FPL,nd,NODEs^[nd].desc.ai);
      _accept_FPLm:=false
     {$ENDIF}
    end;


 procedure _pkt_FPLM(FPL: PDmFPL);
     var   rep : string;
           FPLp : DmFPL;
           p : pchar;

     label E,X ;

     begin
       {$IFDEF NO_PLAN}
         Exit;
       {$ENDIF}

       if (read_mFPL(codekey_FPLM(FPL),@FPLp)>-1) and (not chg_mFPL (FPL,@FPLp)) then goto X;

       if is_KRL(FPL) then
          begin
            {$IFDEF KRL} {$IFDEF PROCESS_FPLM}
             if _FPLM._plan_pre_pracovisko(FPL) then isKRL:= true;
            {$ENDIF} {$ENDIF}
            goto E
          end;

       {$IFDEF FPLM_REPORT}
        {$IFDEF PROCESS_FPLM}
         if pripomienka_ku_FPLM(FPL) then rep:= ''
         else
        {$ENDIF}
        rep:= decode_stat_fpl(FPL^.stat);
        if (rep='') and (pos(cnst_active,FPL^.stat)<>0) and (FPLp.stat<>'') then rep:= st_fpl_rte;

        if     (rep<>'') and (reports_FDP<>nil)
           and {$IFDEF AIRBASE}
                (   (hlas_vsetky_FPLM  and _FPLM._plan_pre_pracovisko(FPL))
                 or (      hlas_vlastne_FPLM
                      and (   _plan_pre(FPL^.let)
                           or _plan_pre(FPL^.start.kod)
                          )
                     )
                )
               {$ELSE}
                (hlas_vsetky_FPLM)
               {$ENDIF}

           then begin
                  p:= code_l4_FPLM_(FPL,'');
                  reports_FDP^.save_rep
                     (spr_FPLM,'',codekey_FPLM(FPL),
                      rep+' '+code_FPLM_7a(FPL)+'',
                      strlen(p),pchars(p)
                     );
                  strdispose(p)
                end;
       {$ENDIF}

       { --------------------------------- }
       { tlac                              }
       { --------------------------------- }

       E: _zarad_FPLm (FPL,FPL^.stat,true,letvis,true);

          if p_formular_REQ_FPL<>nil then p_formular_REQ_FPL^.spracovany_plan(FPL);
          send_mail(nil,nil, cmFPLMrec, All, @FPL,sizeof(FPL));  { vydanie spravy o prijati FPL }

       X: disp_mFPL(@FPLp)
     end;


{ --------------------
   Prijate potvrdenie
  --------------------
}

{ redundantnost + optimalizacia zabezpecia,
  aby sa zbytocne nenacitaval/neukladal cely plan
}
 procedure _codeDBB_FPLMrec (src: Pplan_rec; buff: PDB_riadok; head: PDB_head); far;
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

 procedure _codeDBB_FPLMnd (nd: pint; buff: PDB_riadok; head: PDB_head); far;
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


 procedure _ack_FPLM(key: string; rec: Tplan_rec; fdp: bool; nd: int);
     var   FPL  : PFPLM;
           iFPL : P_OFPL;
           date : TDate;
           s,t  : string;
           p1,p2 : pointer;
           i : int;
           x : char;
     begin
       FPL:= find_FPLMa (key);

       decodekey_fpl(key,s,t,date);
       t:= ext_mFPL;
       {$IFDEF KRL}
         decode_FPLM_7a (s,s,{$IFNDEF L4444M}x{$ENDIF});
         if cut_(s)='' then t:= ext_KRL;
       {$ENDIF}

       if NET_ACK_ALL then
          begin
            if FPL<>nil then rec_copy (rec, FPL^.rec);
            p1:= @rec;
            p2:= @_codeDBB_FPLMrec
          end
       else begin
              if FPL<>nil then rec_pkt (nd,FPL^.rec,is_ack);
              p1:= @nd;
              p2:= @_codeDBB_FPLMnd
            end;
       if not fdp then Exit;

       DB_oprav_riadok (p1,nil,key,
                        get_DBfn(date, pathFPL_M,t),db_mFPL_RIADKOV,
                        @codeDB_FPLM,@codekey_FPLM,
                        db_mFPL_ine,p2,
                        dbattr_FPM
                       );


       {$IFDEF EDD}
        if (FPL<>nil) and pis_STRIP_ACK then
           begin
             i:= PROP_mFPL^.find_key(key);
             if i>-1 then iFPL:= PROP_mFPL
             else begin
                    i:= mFPL^.find_key(key);
                    if i>-1 then iFPL:= mFPL
                  end;
             if i>-1 then iFPL^.vypis_plan(i, false,false);
           end;
       {$ENDIF}

     end;
