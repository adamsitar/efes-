
{ ----------
   DEP        - v ramci 24 hodin
  ----------
}
function _is_DEP(FPL: PDmFPL; s: Pstring): bool; far;
   begin
     {$IFDEF AIRBASE}
       _is_DEP:=    (    _plan_pre(FPL^.start.kod)
                     and (   (__is_stat(FPL^.stat, cnst_FPL_DEP))
                          or (is_VFR_FPLM(FPL) and __is_stat(FPL^.stat, cnst_planned+cnst_FPL_DEP))
                         )
                    )
     {$ENDIF}

     {$IFDEF MACC}
       _is_DEP:=  __is_stat(FPL^.stat, cnst_FPL_DEP)
     {$ENDIF}
   end;

(*
function  _DEP_FPL(sc: PScroller; FPL: PDmFPL): bool; far;
    var   x,y       :  int;
          pt,st,dep : TTime;
          tp,ts     : real;
          s,si      : string;
    begin
      _DEP_FPL:= false;
      si:= code_FPLM_7a(FPL);

     { bol uz plan pripomienkovany ?
     } {$IFDEF AIRBASE}
        if not (is_VFR_FPLM(FPL) or (pos(cnst_acc,FPL^.stat)<>0)) then
           if not (Ask2(msgWARNING,'FPL '+si+ask_not_FPL_ACC,titNO,
                   White,clBUTTON_COLOR,waitASK*18) = ansAno
                  ) then Exit;
       {$ENDIF}

     { upresnenie casu
     }
      sc_menu_xy(sc, x,y, 102,18);
      st.h:= FPL^.start.h; st.m:= FPL^.start.m;
      s:= msg_cas_DEP+si+'.'+NULL;
      if not formular_CAS(pt, st.h,st.m, x,y, hd_DEP+' '+si, @s[1]) then Exit; {ñ}

      with FPL^ do IncHMTime(prist.h,prist.m, pt.h,pt.m, start.h,start.m);
      with FPL^.start do IncHMTime(h,m, pt.h,pt.m, h,m);

     { Ak je IFR a start je zadavany vcas,
       potom kontrola na dodrzanie casu startu
       <rngDEP>
     }
      {$IFNDEF MACC} {$IFDEF OPL}
        if not (is_VFR_FPLM(FPL)) then
           begin
             ts:= TimetoSec(st.h,st.m,0);
             tp:= TimetoSec(FPL^.start.h,FPL^.start.m,0);
             if     (AbsTime <= DTtoSec(FPL^.date.r,FPL^.date.m,FPL^.date.d, FPL^.start.h,FPL^.start.m,0))
                and (not ((ts-60*rngDEP <= tp) and (tp <= ts+60*rngDEP))) then
                begin
                  if Ask2(msgWARNING,msg_dtcas_DEP+IntToStr(rngDEP,1,0)+'''. '+ask_REQ,titNO,
                          White,clBUTTON_COLOR, waitASK*18
                         ) = ansAno then _REQ_FPL(sc,FPL);
                  Exit
                end

           end;
      {$ENDIF} {$ENDIF}

     { sprava o starte 'A'
     }
      zarad_FPLm(FPL,cnst_stat_DEP,true,letvis)
    end;

*)


function _DEP_check(form: PmFPLform; FPL: PDmFPL): bool; far;
   var   bres  : bool;
         st    : TTime;
         tp,ts : real;
   begin
     bres:= _mFPL_check(form, FPL, true,false,true);

    { Ak je IFR a start je zadavany vcas,
      potom kontrola na dodrzanie casu startu
      <rngDEP>
    }
     {$IFDEF AIRBASE} {$IFDEF OPL}
       if (form^.adr_data<>nil) and (not (is_VFR_FPLM(FPL))) then
          begin
            st.h:= PDmFPL(form^.adr_data)^.start.h;
            st.m:= PDmFPL(form^.adr_data)^.start.m;
            ts:= TimetoSec(st.h,st.m,0);
            tp:= TimetoSec(FPL^.start.h,FPL^.start.m,0);
            if     (AbsTime <= DTtoSec(FPL^.date.r,FPL^.date.m,FPL^.date.d, FPL^.start.h,FPL^.start.m,0))
               and (not ((ts-60*rngDEP <= tp) and (tp <= ts+60*rngDEP))) then
               begin
                 if Ask2(msgWARNING,msg_dtcas_DEP+IntToStr(rngDEP,1,0)+'''. '+ask_REQ,titNO,
                         White,clBUTTON_COLOR, waitASK*18
                        ) = ansAno then _REQ_FPL(nil,FPL);
                 bres:= false;
               end

          end;
     {$ENDIF} {$ENDIF}

     {bolo by treba urcit, ci sa nespravilo MZP...}
     _DEP_check:= bres
   end;

function _DEP_FPL(sc: PScroller; FPL: PDmFPL): bool; far;
   var   res : bool;
         si  : string;
   begin
     _DEP_FPL:= false;
     si:= code_FPLM_7a(FPL);

     {$IFDEF AIRBASE}
     { bol uz plan pripomienkovany ? }
      if not (is_VFR_FPLM(FPL) or (pos(cnst_acc,FPL^.stat)<>0)) then
         if not (Ask2(msgWARNING,'FPL '+si+ask_not_FPL_ACC,titNO,
                 White,clBUTTON_COLOR,waitASK*18) = ansAno
                ) then Exit;
     {$ENDIF}

     res:= formular_mFPL(FPL,letvis,cnst_stat_DEP,false, msg_FPL_DEP,i_13Mb,@_DEP_check,hlp_mFPL_DEP);
   end;



procedure mFPL_DEP;
    begin
      spracuj_mFPL(find_and_process_FPLM,false,
                   false,false,false,true,
                   '', @_is_DEP,
                   @_DEP_FPL,_TBFunc_p2,
                   true,false,
                   msg_FPL_DEP,nil,hlp_mFPL_DEP
                   )
    end;


{ -----------
   ARR
  -----------
}
function _ARR_FPL(sc: PScroller; FPL: PDmFPL): bool; far;
   var   x,y : int;
         s,t : string;
         tp  : TTime;
   begin
     _ARR_FPL:= false;

     sc_menu_xy(sc, x,y, 102,18);
     s:= msg_cas_ARR+code_FPLM_7a(FPL)+'.'+#0;
     t:= code_FPLM_7a(FPL);
     if not formular_CAS(tp, FPL^.prist.h,FPL^.prist.m {hour,min}, x,y, ' '+hd_ARR+' '+t, @s[1]) then Exit;
     (*s := strpas(FPL^.pozn);
     t := s_ARR {$IFDEF AIRBASE}+icao_NXT+this_airbase{$ENDIF};
     t:= t+','+TimeToStr(tp.h,tp.m,':');
     if length(s+t)+1>dlz_rdk_FPLm*rdk_trat_FPLm then s:= copy(s,1,dlz_rdk_FPLm*rdk_trat_FPLm-length(t)-1);
     if s[length(s)]<>kbCRLF then t:= ' '+t;
     StrDispose(FPL^.pozn);
     FPL^.pozn:= StrPasNew(s+t);
     *)
     FPL^.prist.h:= tp.h;
     FPL^.prist.m:= tp.m;
     zarad_FPLm(FPL,cnst_stat_arr,true,letvis);

     (*formular_mFPL(FPL, msg_FPL_ARR,i_16Mb, false,false,cnst_stat_ARR, nil,hlp_mFPL_ARR)
     *)
   end;


function _is_ARR (FPL: PDmFPL; s: Pstring): bool; far;
   var   zmena : bool;
         z : TPoz;
   begin
     z:= stav_mFPL(FPL,abstime,zmena);
     _is_ARR:=     {__is_stat(FPL,cnst_FPL_ARR)
               and _plan_pre_pracovisko(FPL)
               and} (z in pozACT+[poz_SEDI,poz_HANGAR])
               and  (DateToSec(FPL^.date.r,FPL^.date.m,FPL^.date.d)>=DateToSec(year,month,day))

   end;

procedure mFPL_ARR;
    begin
      spracuj_mFPL(find_and_process_FPLM,false,
                   false,false,false,true,
                   '', @_is_ARR,
                   @_ARR_FPL,_TBFunc_p2,
                   true,false,
                   msg_FPL_ARR,nil,hlp_mFPL_ARR
                  )
    end;


{$IFDEF REPORT_FPLM_ARW}
  procedure mFPL_ARW;
      begin
        spracuj_mFPL(false,false,
                     false,false,false,true,
                     '', @_is_FPLM_ARW,
                     @_ARR_FPL,_TBFunc_p2,
                     true,false,
                     msg_FPL_ARRW,nil,hlp_mFPL_ARR
                    )
      end;
{$ENDIF}