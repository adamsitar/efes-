function _is_stat_PRZ (PRZ: PPRZ; s: Pstring): bool; far;
   begin
     _is_stat_PRZ:= _is_stat_us (PRZ^.let, PRZ^.stt, s^)
   end;

function _is_stata_PRZ (PRZ: PPRZ; s: Pstring): bool; far;
   begin
     _is_stata_PRZ:= __is_stat(PRZ^.stt, s^)
   end;


{ volanie prehladu,
  bolo by vhodne vyvolavat i niektore danne priamo,
  ako v aftn "act -> tsa11"
}
{$IFDEF PRZ_REQUEST}
  procedure send_PRZs(PRZs: Pptrs; top: pointer); far; forward;
{$ENDIF}

procedure spracuj_PRZ(_FN: string;
                      _data_filter : string; _filter : pointer;
                      _handler : pointer; _handler_type : TScrollAct_handler_type;
                      _print, _send : bool;
                      _title: string
                     );
   var    print, send : pointer;
   begin
     send:= nil; print:= nil;

     if _print then print:= @print_PRZs;

     {$IFDEF PRZ_REQUEST}
       if _send then send:= @send_PRZs;
     {$ELSE}
      _handler:= nil;
      _handler_type:= _TNull;
     {$ENDIF}

     scroll_DB_FDP(_title,  false,false,false, nil,

                   max_PRZ, sizeof(TPRZ),
                   @new_PRZ,nil,@disp_PRZ,@eq_PRZ,
                   '',nil,
                   @_data_filter,nil,nil,_filter,_filter,
                   true,nil,nil,
                   _handler_type,_handler,nil,
                   nil,nil,nil, print,send,

                   _FN, {_FNfunc, _FNfunc_p,} nil,nil,
                   db_PRZ_RIADKOV,@decodeDB_PRZ, nil{@dbchg_PRZ},

                   dxi_NTM, dyi_NTM, @plan_PRZ,
                   nil {_info}, hlp_zoznam,
                   @p_prz_dbscroller
                  )
   end;