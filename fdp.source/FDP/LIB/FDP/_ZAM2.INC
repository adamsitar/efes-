function _plan_pre_pracovisko(ZAM: PZAM): bool; far;
   begin
     _plan_pre_pracovisko:= _plan_pre(ZAM^.kod) or _plan_pre(ZAM^.src)
   end;


function _is_stata_ZAM (ZAM: PZAM; s: Pstring): bool; far;
   begin
     _is_stata_ZAM:= __is_stat(ZAM^.stat, s^)
   end;

function _is_stat_ZAM (ZAM: PZAM; s: Pstring): bool; far;
   begin
     _is_stat_ZAM:= _is_stata_ZAM(ZAM,s) and _plan_pre_pracovisko(ZAM)
   end;


function comp_ZAM(ZAM1,ZAM2: PZAM): bool; far;
   var   r1,r2: string;
   begin
     r1:= _mairbase(ZAM1^.kod);
     r2:= _mairbase(ZAM2^.kod);
     if  r1 = r2 then comp_ZAM:=    DTtoSec(ZAM1^.zac.rok,ZAM1^.zac.mes,ZAM1^.zac.den, ZAM1^.zac.h,ZAM1^.zac.m,0)
                                  < DTtoSec(ZAM2^.zac.rok,ZAM2^.zac.mes,ZAM2^.zac.den, ZAM2^.zac.h,ZAM2^.zac.m,0)
     else comp_ZAM:= r1 < r2
   end;

procedure sort_ZAM(pole: pointer; top: pointer);
    begin
      QuickSort(pole,@comp_ZAM,nil{@swap_ZAM},0,int(top^), false)
    end;

{$IFDEF PROCESS_ZAM}
  procedure send_ZAMs (ZAMs: Pptrs; top: pointer); far; forward;
{$ENDIF}


procedure spracuj_ZAM(_FN: string; _dbchg: pointer; { _FNfunc: pointer; _FNfunc_p: pointer;}
                      _data_filter : string; _filter : pointer;
                      _handler : pointer; _handler_type : TScrollAct_handler_type;
                      _print, _send : bool;
                      _title: string{; _info: pchar; _hlpXXX : Pchar}
                     ); far;

   var    print, send : pointer;

   begin
     send:= nil; print:= nil;

     {$IFDEF PROCESS_ZAM} {$IFDEF AIRBASE}
       if _send then send:= @send_ZAMs;
     {$ENDIF} {$ENDIF}

     {$IFDEF PROCESS_ZAM} {$IFDEF PRN}
       if _print then print:= @print_ZAMs;
     {$ENDIF} {$ENDIF}

     scroll_DB_FDP(_title, false,false,false, nil,

                   max_ZAM, sizeof(TZAM),
                   @new_ZAM,@format_ZAM,@disp_ZAM,@eq_ZAM,
                   '',nil,
                   @_data_filter,nil,nil,_filter,_filter,

                   true, @sort_ZAM, nil,
                   _handler_type,_handler,nil,
                   nil,nil,nil, print,send,

                   _FN, {_FNfunc, _FNfunc_p,} nil,nil,
                   db_ZAM_RIADKOV,@decodeDB_ZAM,_dbchg,

                   dx_ZAM, dy_ZAM, @plan_ZAM,
                   nil, hlp_zoznam,

                   @p_zam_dbscroller
                  )
   end;