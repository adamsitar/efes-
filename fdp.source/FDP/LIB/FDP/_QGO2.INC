function _plan_pre_pracovisko (QGO: PQGO): bool; far;
   begin
     _plan_pre_pracovisko:= _plan_pre(QGO^.kod)
   end;

function _is_stata_QGO (QGO: PQGO; s: Pstring): bool; far;
   begin
     _is_stata_QGO:= _is_statp(QGO^.stat,s,false)
   end;

function _is_stat_QGO (QGO: PQGO; s: Pstring): bool; far;
   begin
     _is_stat_QGO:= _is_stata_QGO(QGO,s) and _plan_pre_pracovisko(QGO)
   end;


function comp_QGO(QGO1,QGO2: PQGO): bool; far;
   begin
     comp_QGO:= _mairbase(QGO1^.kod) < _mairbase(QGO2^.kod)
   end;

procedure sort_QGO(QGOs: Pptrs; top: pointer); far;
    begin
      QuickSort(QGOs,@comp_QGO,nil,0,int(top^), false)
    end;


procedure spracuj_QGO(_FN: string; _dbchg: pointer;
                      _data_filter : string; _filter : pointer;
                      _handler : pointer; _handler_type : TScrollAct_handler_type;
                      _print : bool;
                      _title : string; _hlpXXX : Pchar
                     ); far;

   var    print : pointer;
   begin
     print:= nil;

     {$IFDEF MATCA} {$IFDEF PRN}
       if _print then print:= @print_QGOs;
     {$ENDIF} {$ENDIF}

     scroll_DB_FDP(_title, false,false,false, nil,
                   max_QGO, sizeof(TQGO),
                   @new_QGO,nil,@disp_QGO,@eq_QGO,
                   '',nil,
                   @_data_filter,nil,nil,_filter,_filter,
                   true, @sort_QGO,nil,
                   _handler_type,_handler,nil,
                   nil,nil,nil, print,nil,

                   _FN, {_FNfunc, _FNfunc_p,} nil,nil,
                   db_QGO_RIADKOV,@decodeDB_QGO, _dbchg,

                   dx_QGO, dy_QGO, @plan_QGO,
                   nil, _hlpXXX,
                   @p_qgo_dbscroller
                  )
    end;
