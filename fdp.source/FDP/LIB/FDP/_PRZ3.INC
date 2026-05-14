{$IFDEF PRZ_REQUEST}

{ -------------------------------
  CHG
}
  function _is_CHG (PRZ: PPRZ; s: Pstring): bool; far;
     var   cond : string;
     begin
       cond:= cnst_requested;
       _is_CHG:= _is_stat_PRZ (PRZ,@cond)
     end;

  function _PRZ_CHG (PRZ: PPRZ): bool; far;
     begin
       _PRZ_CHG:= false;
       formular_PRZ (PRZ,PRZ^.stt=cnst_disk,false,add_stat(PRZ^.stt,cnst_chg),tit_przCHG)
     end;

  procedure PRZ_zmena;
      begin
        spracuj_PRZ(get_PPL_FN(pathPRZ,extPRZ, tit_przCHG),
                    '', @_is_CHG,
                    @_PRZ_CHG,_TBFunc_p,
                    false,false,
                    tit_przCHG
                   )
      end;


{ -------------------------------
  CNL, DIS
}
  function _PRZ_CNL_DIS (PRZ: PPRZ; stt: string; tit: string): bool; far;
     var   s : string;
           b : bool;
     begin
       _PRZ_CNL_DIS:= false;
       b:= (PRZ^.stt<>cnst_disk) and ((_plan_pre(PRZ^.let)));
       s:= tit+' '{+cut_(PRZ^.kod)+' '};
       if b then s:= s+ask_rozoslat+' ';
       s:= s + '?';
       if (Ask2(msgVERIPHY,s, titNO,clGRe,clBUTTON_COLOR-2,waitASK*18)
           = ansAno
          ) then zarad_PRZ(PRZ, stt, b, letvis)
     end;


  function _is_CNL (PRZ: PPRZ; s: Pstring): bool; far;
     var   cond: string;
     begin
       cond:= cnst_planned;
       _is_CNL:=    {(DateToSec(year,month,day) <= DateToSec(PRZ^.das.r,PRZ^.das.m,PRZ^.das.d))
                 and} _is_stat_PRZ(PRZ,@cond)
     end;

  function _PRZ_CNL(PRZ: PPRZ): bool; far;
     begin
       _PRZ_CNL:= _PRZ_CNL_DIS(PRZ,cnst_cnl,ask_przCNL);
     end;

  procedure PRZ_zrusenie;
      begin
        spracuj_PRZ(get_PPL_FN(pathPRZ,extPRZ, tit_przCNL),
                    '', @_is_CNL,
                    @_PRZ_CNL, _TBFunc_p,
                    false,false,
                    tit_przCNL
                   )
      end;


{ -------------------------------
  ROZOSLANIE
}
  function _is_SEND(PRZ: PPRZ; s: Pstring): bool; far;
     var   cond: string;
     begin
       cond:= cnst_disk;
       _is_SEND:=      (SERVERnode>-1)
                   and (PRZ^.rec[SERVERnode]=no_ack)
                   and _is_stat_PRZ(PRZ,@cond)
     end;

  function _SEND_PRZ(PRZ: PPRZ): bool; far;
     begin
       _SEND_PRZ:= zarad_PRZ(PRZ,PRZ^.stt,true,letvis)
     end;

  procedure send_PRZs(PRZs: Pptrs; top: pointer);
     var   i : int;
           b : bool;
     begin
       if int(top^)<0 then Exit;

       i:= 0; b:= true;
       while b and (i<=int(top^)) do
         begin
           if _is_SEND(PRZs^[i],nil) then
              begin
                b:= _SEND_PRZ(PRZs^[i]);
                {if not WAIT_INIT_NODE then} Wait(3,CheckProcesses)
              end;
           inc(i)
         end;
       say_data_sended(b)
    end;

{$ENDIF}