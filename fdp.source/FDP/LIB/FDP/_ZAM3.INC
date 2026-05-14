{ -------------------------------
   PLANOVANIE
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

{ -------------------------------
  CHG
}

  function _is_CHG(ZAM: PZAM; s: Pstring): bool; far;
      var   cond: string;
      begin
        cond:= cnl_stat(cnst_all_valid);
        _is_CHG:= _is_stat_ZAM(ZAM,@cond)
      end;

  function _ZAM_CHG(ZAM: PZAM): bool; far;
     var   res : bool;
     begin
       res:= formular_ZAM(ZAM, not _FDP_def._is_stat(ZAM^.stat, cnst_sended+cnst_stat_act, false), false,
                          {add_stat(}del_cnl_stat(ZAM^.stat){,cnst_chg)},
                          tit_zamCHG
                         );
       _ZAM_CHG:= false
     end;

  procedure ZAM_zmena;
      begin
        spracuj_ZAM(get_PPL_FN(pathZAM,extZAM,tit_zamCHG),nil{@dbchg_ZAM},
                    '', @_is_CHG,
                    @_ZAM_CHG, _TBFunc_p,
                    false, false,
                    tit_zamCHG
                   )
      end;


{ -------------------------------
  CNL
}
  function _is_CNL(ZAM: PZAM; s: Pstring): bool; far;
      var   cond: string;
      begin
        cond:= cnst_all_valid;
        _is_CNL:= _is_stat_ZAM(ZAM,@cond)
      end;

  function _ZAM_CNL(ZAM: PZAM): bool; far;
     var   s : string;
           b : bool;
     begin
       s:= ask_zamCNL+' ('+ZAM^.kod+') ';
       b:= pos(cnst_disk,ZAM^.stat)=0;
       if b then s:= s+ask_rozoslat+' ';
       s:= s + '?';
       if (Ask2(msgVERIPHY,s, titNO,White,clBUTTON_COLOR,waitASK*18) = ansAno) then
          zarad_ZAM(ZAM, {add_stat(ZAM^.stat,}cnst_cnl{)}, b, letvis);
       _ZAM_CNL:= false
     end;

  procedure ZAM_zrusenie;
      begin
        spracuj_ZAM(get_PPL_FN(pathZAM,extZAM,tit_zamCNL),nil{@dbchg_ZAM},
                    '', @_is_CNL,
                    @_ZAM_CNL, _TBFunc_p, false, false,
                    tit_zamCNL
                   )
      end;


  { -------------------------------
    ROZOSLANIE
  }
  function _is_SEND(ZAM: PZAM; s: Pstring): bool; far;
     var   cond: string;
     begin
       cond:= cnst_disk;
       {cond2:= cnst_sended+cnst_cnl;}
       _is_SEND:=     (    (SERVERnode>-1)
                       and (ZAM^.rec[SERVERnode]=no_ack)
                       and _is_stat_ZAM(ZAM,@cond)
                      )
     end;

  function _SEND_ZAM(ZAM: PZAM): bool; far;
     begin
       if pos(cnst_disk,ZAM^.stat)<>0 then _SEND_ZAM:= zarad_ZAM(ZAM,cnst_sended,true,letvis)
       else _SEND_ZAM:= distribute_ZAM(ZAM,[],[]){send_ZAM(ZAM,SERVERaddress,WAIT_INIT_NODE)}
     end;

  procedure send_ZAMs(ZAMs: Pptrs; top: pointer);
     var   i : int;
           b : bool;
     begin
       if int(top^)<0 then Exit;

       i:= 0; b:= true;
       while b and (i<=int(top^)) do
         begin
           if _is_SEND(ZAMs^[i],nil) then
              begin
                b:= _SEND_ZAM(ZAMs^[i]);
                {if not WAIT_INIT_NODE then} Wait(3,CheckProcesses)
              end;
           inc(i)
         end;
       say_data_sended(b)
    end;


{ -------------------------------
   AKTIVACIA
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
  procedure _ZAM_(ZAM: PZAM; stat,title: string);
      var   res: bool;
      begin
        res:= formular_ZAM(ZAM, false,false, stat,title+' '+ZAM^.kod)
      end;


{ -------------------------------
  ZACIATOK
}
  function _is_DEP(ZAM: PZAM; s: Pstring): bool; far;
      var   cond: string;
      begin
        cond:= cnst_disk+cnst_sended;
        _is_DEP:= _is_stat_ZAM(ZAM,@cond)
      end;

  function _ZAM_DEP(ZAM: PZAM): bool; far;
      begin
        {cas_init(ZAM^.zac, BIOS.hour,BIOS.min);}
        _ZAM_(ZAM, cnst_stat_DEP, tit_zamDEP);
        _ZAM_DEP:= false
      end;

  procedure ZAM_zaciatok;
      begin
        spracuj_ZAM(get_dbZAMfn,nil{@dbchg_ZAM},
                    '', @_is_DEP,
                    @_ZAM_DEP, _TBFunc_p,
                    false, false,
                    tit_zamDEP
                   )
      end;


{ -------------------------------
  PRERUSENIE
}
  function _is_BRK(ZAM: PZAM; s: Pstring): bool; far;
      var   cond: string;
      begin
        cond:= cnst_active;
        _is_BRK:= _is_stat_ZAM(ZAM,@cond)
      end;

  function _ZAM_BRK(ZAM: PZAM): bool; far;
      begin
        _ZAM_(ZAM, cnst_pause, tit_zamBRK);
        _ZAM_BRK:= false
      end;

  procedure ZAM_prerusenie;
      begin
        {$IFDEF VER_3.0}
          spracuj_ZAM(get_dbZAMfn,nil{@dbchg_ZAM},
                      '', @_is_BRK,
                      @_ZAM_BRK, _TBFunc_p,
                      false, false,
                      tit_zamBRK
                     )
        {$ELSE}
          ZAMs^.Spracovanie_(tit_zamBRK,cnst_active,_TBFunc_p,@_ZAM_BRK,nil,hlp_zoznam)
        {$ENDIF}
      end;


{ -------------------------------
  POKRACOVANIE
}
  function _is_CNT(ZAM: PZAM; s: Pstring): bool; far;
      var   cond: string;
      begin
        cond:= cnst_pause;
        _is_CNT:= _is_stat_ZAM(ZAM,@cond)
      end;

  function _ZAM_CNT(ZAM: PZAM): bool; far;
      begin
        _ZAM_(ZAM, cnst_active, tit_zamCNT);
        _ZAM_CNT:= true
      end;

  procedure ZAM_pokracovanie;
      begin
        {$IFDEF VER_3.0}
          spracuj_ZAM(get_dbZAMfn,nil{@dbchg_ZAM},
                      cnst_pause, @_is_CNT,
                      _TBFunc_p, @_ZAM_CNT, false, false,
                      tit_zamCNT
                     )
        {$ELSE}
          ZAMs^.Spracovanie_(tit_zamCNT,cnst_pause,_TBFunc_p,@_ZAM_CNT,nil,hlp_zoznam)
        {$ENDIF}
      end;


{ -------------------------------
  KONIEC
}
  function _is_ARR(ZAM: PZAM; s: Pstring): bool; far;
      var   cond: string;
      begin
        cond:= cnst_active+cnst_pause;
        _is_ARR:= _is_stat_ZAM(ZAM,@cond)
      end;

  function _ZAM_ARR(sc: PScroller; ZAM: PZAM): bool; far;
     var   arr : TDatum;
     begin
       _ZAM_ARR:= false;
       if formular_ARR (ZAM^.zac,ZAM^.kon, arr,
                        sc, tit_zamARRtime,ZAM^.kod,
                        a_L4, 321,true,322
                       ) then
          begin
            ZAM^.kon:= arr;
            zarad_ZAM(ZAM,cnst_stat_ARR,true,letvis)
          end
     end;



  procedure ZAM_koniec;
      begin
        {IFDEF VER_3.0}
          spracuj_ZAM(get_dbZAMfn,nil{@dbchg_ZAM},
                      '', @_is_ARR,
                      @_ZAM_ARR, _TBFunc_p2, false,false,
                      tit_zamARR
                     )
        {ELSE
          ZAMs^.Spracovanie_(tit_zamARR,cnst_active+cnst_pause,_TBFunc_p2,@_ZAM_ARR,nil,hlp_zoznam)
        ENDIF}
      end;


{ --------------------------------------------------------
  AKTUALIZACIA LETOV,
  realizovanych v ramci zamestnania,
  pretoze v okamihu vydavania spravy
  nie je znamy celkovy pocet realizovanych letov.

  Casto sa to dozvedia az druhy den...
}
  procedure aktualizovany_pocet_letov(ZAM: PZAM);
      var   date : TDate;
      begin
        init_date (date, ZAM^.zac.rok,ZAM^.zac.mes,ZAM^.zac.den);
       {$IFDEF STATISTIKA}
         if p_modify_STA_ZAM<>nil then TProc_date(p_modify_STA_ZAM)(date);
       {$ENDIF}
      end;

  function _is_LETOV(ZAM: PZAM; s: Pstring): bool; far;
      var   cond : string;
            date : TDate;
      begin
        init_date (date, ZAM^.zac.rok,ZAM^.zac.mes,ZAM^.zac.den);
        cond:= cnst_active+cnst_pause+cnst_finish;
        _is_LETOV:= _is_stat_ZAM (ZAM,@cond)
                    {$IFDEF STATISTIKA}
                     and (   (StatistikaAPP=nil)
                          or StatistikaAPP^.povolena_aktualizacia_statistiky(date)
                         )
                    {$ENDIF}
      end;


  function _ZAM_LETOV(ZAM: PZAM): bool; far;
     begin
       if formular_ZAM(ZAM, false,false,ZAM^.stat,tit_zamLETOV) then
          aktualizovany_pocet_letov(ZAM);
       _ZAM_LETOV:= false
     end;

  procedure ZAM_letov;
      var   date : TDate;
            sres : string;
      begin
        if not formular_DATUM (date,initX,initY,tit_zamLETOVdna) then Exit;
        {$IFDEF STATISTIKA}
         if     (StatistikaAPP<>nil)
            and (not StatistikaAPP^.povolena_aktualizacia_statistiky(date)
                ) then
            begin
              l4_err(a_STA,'',0,err_AKTUALIZACIA_NEDOVOLENA,sres);
              Err2('',sres);
              Exit
            end;
        {$ENDIF}
        spracuj_ZAM(get_DBfn (date, pathZAM,extZAM),nil{@dbchg_ZAM},
                    '', @_is_LETOV,
                    @_ZAM_LETOV, _TBFunc_p2, false,false,
                    tit_zamLETOV
                   )
      end;
