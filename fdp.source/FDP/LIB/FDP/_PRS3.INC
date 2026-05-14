{ -------------------------------
   PLANOVANIE
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
  function _PRS_CNL_ (PRS: PPRS; stt: string; tit: string): bool; far; forward;

 { -------------------------------
    CHG
 }
  function _is_CHG (PRS: PPRS; s: Pstring): bool; far;
     var   cond: string;
     begin
       cond:= {$IFDEF AMC} cnst_prs_planned
              {$ELSE}      cnst_prs_change
              {$ENDIF}
              ;
       _is_CHG:=      (not is_P(PRS^.kod))
                  and (_is_stat_PRS (PRS,@cond)
                  and plan_pred_poslednym_schvalenim (PRS))
     end;

  function _PRS_CHG (PRS: PPRS): bool; far;
     begin
       _PRS_CHG:= false;
       formular_PRS(PRS,PRS^.stat=cnst_disk,false,letvis,
                    {add_stat(}del_cnl_stat(PRS^.stat){,cnst_chg)},
                    tit_prsCHG
                   )
     end;


  function _is_ACT (PRS: PPRS; s: Pstring): bool; far;
     var   cond: string;
     begin
       cond:= cnst_stat_act;
       _is_ACT:=  (not is_P(PRS^.kod)) and _is_stat_PRS (PRS,@cond)
     end;

  function _PRS_ACT (PRS: PPRS): bool; far;
     begin
       _PRS_ACT:= false;
       formular_PRS(PRS,PRS^.stat=cnst_disk,false,letvis,
                    {add_stat(}del_cnl_stat(PRS^.stat){,cnst_chg)},
                    tit_prsACT
                   )
     end;


  procedure PRS_zmena_(p_filter: PBFunc_p2; p_handler: PBFunc_p; title: string );
      begin
        spracuj_PRS(find_and_process_PRS,find_and_process_PRS,
                    true,false,false,
                    '', p_filter,
                    p_handler,_TBFunc_p,
                    false,false,
                    title, nil,nil
                   )
      end;


 { -------------------------------
   ROZOSLANIE
 }
  function _is_SEND(PRS: PPRS; s: Pstring): bool; far;
     var   cond: string;
     begin
       cond:= cnst_disk;
       {cond2:= cnst_sended+cnst_cnl;}
       _is_SEND:=      (not is_P(PRS^.kod))
                   and (SERVERnode>-1)
                   and (PRS^.rec[SERVERnode]=no_ack)
                   and _is_stat_PRS(PRS,@cond)
     end;

  function _SEND_PRS(PRS: PPRS): bool; far;
     begin
       if pos(cnst_disk,PRS^.stat)<>0 then _SEND_PRS:= zarad_PRS(PRS,cnst_sended,true, letvis)
       else _SEND_PRS:= distribute_PRS(PRS,[],[]){send_PRS(PRS,SERVERaddress,WAIT_INIT_NODE)}
     end;

  procedure send_PRSs(PRSs: Pptrs; top: pointer);
     var   i : int;
           b : bool;
     begin
       if int(top^)<0 then Exit;

       i:= 0; b:= true;
       while b and (i<=int(top^)) do
         begin
           if _is_SEND(PRSs^[i],nil) then
              begin
                b:= _SEND_PRS(PRSs^[i]);
                {if not WAIT_INIT_NODE then} Wait(3,CheckProcesses)
              end;
           inc(i)
         end;
       say_data_sended(b)
    end;


{ -------------------------------
   SCHVALENIE
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
{$IFDEF AMC}

 { -------------------------------
    DEC
 }
  function _is_DEC (PRS: PPRS; s: Pstring): bool; far;
     var   cond: string;
     begin
       cond:= cnst_requested+cnst_acc;
       _is_DEC:=     (not is_P(PRS^.kod))
                 and _is_stat_PRS(PRS, @cond)
                 and plan_pred_poslednym_schvalenim (PRS)
     end;

   function _PRS_DEC (PRS: PPRS): bool; far;
      begin
        _PRS_DEC:= _PRS_CNL_(PRS,cnst_dec,ask_prsDIS);
      end;

   procedure PRS_zamietnutie;
       begin
         spracuj_PRS(find_and_process_PRS,find_and_process_PRS,
                     true,false,false,
                     '', @_is_DEC,
                     @_PRS_DEC, _TBFunc_p,
                     false,false,
                     tit_prsDEC, nil,nil
                    )
       end;

 { -------------------------------
    ACC
 }
   function _is_ACC (PRS: PPRS; s: Pstring): bool; far;
     var    r1,r2 : real;
            cond: string;
     begin
       cond:= cnst_requested+cnst_dec;
       _is_ACC:=      (not is_P(PRS^.kod))
                  and _is_stat_PRS(PRS, @cond)
                  and plan_pred_poslednym_schvalenim (PRS)
     end;

   function _PRS_ACC(PRS: PPRS): bool; far;
      begin
        _PRS_ACC:= false;
        formular_PRS(PRS,false,false,letvis,cnst_acc,tit_prsACC)
      end;

   procedure PRS_schvalenie;
       begin
         spracuj_PRS(find_and_process_PRS,find_and_process_PRS,
                     true,false,false,
                     '', @_is_ACC,
                     @_PRS_ACC,_TBFunc_p,
                     false, false,
                     tit_prsACC, nil,nil
                    )
       end;


 { -------------------------------
    REQ
 }

   function _is_REQ (PRS: PPRS; s: Pstring): bool; far;
      begin
        _is_REQ:= _is_ACC(PRS,s) or _is_DEC(PRS,s)
      end;

   function _PRS_REQ(sc: PScroller; PRS: PPRS): bool; far;
      var   M : PWinMenu;
            E : TEvent;
            x,y : int;
      begin
        _PRS_REQ:= false;

        M := WinMenu(' '+PRS^.kod+' ',nil,
                     Item(tit_ACC_, cmPRSacc,
                     Item(tit_DEC_, cmPRSdec,
                     nil ) )
                    );
        if sc<>nil then
           begin
             sc^.get_pos_xy(sc^.pos, x,y);
             M^.MoveRel(x+15-M^.x0,y+30-M^.y0)
           end
        else M^.Centre;
        RunMenu(M,E);
        Dispose(M,Done);

        if ((E.What and evMessage) <> 0) then
           case E.Command of
             cmPRSacc : _PRS_ACC(PRS);
             cmPRSdec : _PRS_DEC(PRS)
           end
      end;


   procedure PRS_ziadost;
       begin
         spracuj_PRS(find_and_process_PRS,find_and_process_PRS,
                     true,false,false,
                     '', @_is_REQ,
                     @_PRS_REQ,_TBFunc_p2,
                     false, false,
                     tit_prsREQ, nil,nil
                    )
       end;

{$ENDIF}


{ -------------------------------
   AKTIVACIA
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

 { -------------------------------
   ZACIATOK
 }
  function isnt_fua: bool;
     begin
       isnt_fua:= true {$IFDEF FUA} or (not cas_FUA_24H_EN) {$ENDIF};
     end;

  function _is_DEP (PRS: PPRS; s: Pstring): bool; far;
     var   cond : string;
     begin
       cond:=  cnst_acc;
       if isnt_fua then cond:=  cond + cnst_planned;
       _is_DEP:=     (not is_P(PRS^.kod))
                 and (isnt_fua or est_PRS(PRS))
                 and (absTime < DTtoSec(PRS^.kon.rok,PRS^.kon.mes,PRS^.kon.den,PRS^.kon.h,PRS^.kon.m,PRS^.kon.s))
                 and _is_stat_PRS(PRS,@cond)
     end;

  function _PRS_DEP(PRS: PPRS): bool; far;
      begin
        _PRS_DEP:= false;
        {cas_init (PRS^.zac, BIOS.hour,BIOS.min);}
       {$IFDEF FUA}
        if     (_decode_stav(PRS^.stat) in [_ziadost])
           and (Ask2(msgWARNING,tit_formPRS+ask_not_PRS_ACC,titNO,
                     White,clBUTTON_COLOR,waitASK*18) <> ansAno
               ) then Exit;
       {$ENDIF}
        formular_PRS(PRS, false,false, letvis, cnst_stat_DEP,tit_prsDEP)
      end;

  procedure PRS_zaciatok;
      begin
        spracuj_PRS(find_and_process_PRS,false,
                    false,false,false,
                    '', @_is_DEP,
                    @_PRS_DEP, _TBFunc_p,
                    false,false,
                    tit_prsDEP, nil,nil
                   )
      end;


 { -------------------------------
   PRERUSENIE
 }
  function _is_BRK (PRS: PPRS; s: Pstring): bool; far;
     var   cond: string;
     begin
       cond:= cnst_active;
       _is_BRK:=     (not is_P(PRS^.kod))
                 and (isnt_fua or est_PRS(PRS))
                 and (absTime < DTtoSec(PRS^.kon.rok,PRS^.kon.mes,PRS^.kon.den,PRS^.kon.h,PRS^.kon.m,PRS^.kon.s))
                 and _is_stat_PRS(PRS,@cond);
     end;

  function _PRS_BRK(PRS: PPRS): bool; far;
      begin
        _PRS_BRK:= false;
        formular_PRS(PRS, false,false, letvis, cnst_pause,tit_prsBRK)
      end;

  procedure PRS_prerusenie;
      begin
        spracuj_PRS(find_and_process_PRS,false,
                    false,false,false,
                    '', @_is_BRK,
                    @_PRS_BRK, _TBFunc_p,
                    false,false,
                    tit_prsBRK, nil,nil
                   )
        {PRSs^.Spracovanie (tit_prsBRK,
                           nil,@_is_BRK,
                           _TBFunc_p,@_PRS_BRK,nil,
                           nil, nil,
                           hlp_zoznam
                          )}
      end;


 { -------------------------------
   POKRACOVANIE
 }
  function _is_CNT (PRS: PPRS; s: Pstring): bool; far;
     var   cond: string;
     begin
       cond:= cnst_pause;
       _is_CNT:=      (not is_P(PRS^.kod))
                  and (isnt_fua or est_PRS(PRS))
                  and (absTime < DTtoSec(PRS^.kon.rok,PRS^.kon.mes,PRS^.kon.den,PRS^.kon.h,PRS^.kon.m,PRS^.kon.s))
                  and _is_stat_PRS(PRS,@cond)
     end;

  function _PRS_CNT(PRS: PPRS): bool; far;
      begin
        _PRS_CNT:= true;
        formular_PRS(PRS, false,false, letvis, cnst_active,tit_prsCNT)
      end;

  procedure PRS_pokracovanie;
      begin
        spracuj_PRS(find_and_process_PRS,false,
                    false,false,false,
                    '', @_is_CNT,
                    @_PRS_CNT, _TBFunc_p,
                    false,false,
                    tit_prsCNT, nil,nil
                   )
        {PRSs^.Spracovanie (tit_prsCNT,
                           nil,@_is_CNT,
                           _TBFunc_p,@_PRS_CNT,nil,
                           nil, nil,
                           hlp_zoznam
                          )}
      end;


 { -------------------------------
   KONIEC
 }
  function _is_ARR (PRS: PPRS; s: Pstring): bool; far;
     var   cond: string;
     begin
       cond:= cnst_pause+cnst_active;
       _is_ARR:=       (not is_P(PRS^.kod))
                  and _is_stat_PRS(PRS,@cond)
     end;

  function _PRS_ARR(sc: PScroller; PRS: PPRS): bool; far;
     var   arr : TDatum;
     begin
       _PRS_ARR:= false;
       if formular_ARR (PRS^.zac,PRS^.kon, arr,
                        sc, tit_prsARRtime,PRS^.kod,
                        a_FUA, 23,false,24
                       ) then
          begin
            PRS^.kon:= arr;
            zarad_PRS(PRS,cnst_stat_ARR,true, letvis)
          end
       {formular_PRS(PRS, false,false, cnst_stat_arr,tit_prsARR)}
     end;

  procedure PRS_koniec;
      begin
        (*PRSs^.Spracovanie (tit_prsARR, @dbchg_PRS,
                           nil,@_is_ARR,
                           _TBFunc_p{2},@_PRS_ARR,nil,
                           {$IFDEF MATCA} nil, nil, {$ENDIF}
                           hlp_zoznam
                          )*)
        spracuj_PRS(find_and_process_PRS,false,
                    false,false,false,
                    '', @_is_ARR,
                    @_PRS_ARR, _TBFunc_p2,
                    false,false,
                    tit_prsARR, nil,nil
                   )
      end;


 { -------------------------------
    CNL
 }
  function _PRS_CNL_ (PRS: PPRS; stt: string; tit: string): bool;
     var   b : bool;
     begin
       _PRS_CNL_:= false;
       b:= (PRS^.stat<>cnst_disk) and _plan_pre_pracovisko(PRS);
       tit:= tit+' '+PRS^.kod+' ';
       if b then tit:= tit+ask_rozoslat+' ';
       tit:= tit + '?';
       if (Ask2(msgVERIPHY,tit, titNO,clGRe,clBUTTON_COLOR-2,waitASK*18) = ansAno) then
          zarad_PRS(PRS, stt, b, letvis)
     end;


  function _is_CNL (PRS: PPRS; s: Pstring): bool; far;
     var   cond: string;
     begin
       cond:= cnst_prs_planned;
       _is_CNL:=      (not is_P(PRS^.kod))
                  and ((_is_stat_PRS(PRS,@cond)
                       {$IFDEF FUA}
                         and (DateToSec(year,month,day) <= DateToSec(PRS^.das.r,PRS^.das.m,PRS^.das.d))
                       {$ENDIF}
                       )
                       or _is_ARR (PRS, s)
                      )
     end;

  function _PRS_CNL(PRS: PPRS): bool; far;
     begin
       _PRS_CNL:= _PRS_CNL_(PRS,{add_stat(PRS^.stat,}cnst_cnl{)},ask_prsCNL);
     end;

  procedure PRS_zrusenie;
      begin
        spracuj_PRS(find_and_process_PRS,false,
                    true,false,false,
                    '', @_is_CNL,
                    @_PRS_CNL, _TBFunc_p,
                    false,false,
                    tit_prsCNL, nil,nil
                   )
      end;
