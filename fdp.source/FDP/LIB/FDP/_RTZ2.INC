function comp_RTZ(RTZ1,RTZ2: PRTZ): bool; far;
   begin
     comp_RTZ:= RTZ1^.id < RTZ2^.id
   end;

procedure sort_RTZ(RTZs: Pptrs; top: pointer); far;
    begin
      QuickSort(RTZs,@comp_RTZ,nil,0,int(top^), false)
    end;


procedure spracuj_RTZ(_FN: string; _dbchg: pointer;
                      _data_filter : string; _filter : pointer;
                      _handler : pointer; _handler_type : TScrollAct_handler_type;
                      _print : bool;
                      _title : string; _hlpXXX : Pchar
                     ); far;

   var    print : pointer;
   begin
     print:= nil;

     {$IFDEF MATCA} {$IFDEF PRN}
       if _print then print:= @print_RTZs;
     {$ENDIF} {$ENDIF}

     scroll_DB_FDP(_title,

                   false,false,false, nil,

                   max_RTZ, sizeof(TRTZ),
                   @new_RTZ,nil,@disp_RTZ,@eq_RTZ,

                   '',nil,
                   @_data_filter,nil,nil,_filter,_filter,

                   true, @sort_RTZ,nil,
                   _handler_type,_handler,nil,
                   nil,nil,nil,

                   print,nil,

                   _FN, nil,nil,
                   db_RTZ_RIADKOV,@decodeDB_RTZ, _dbchg,

                   dx_RTZ, dy_RTZ, @plan_RTZ,

                   nil, _hlpXXX,

                   nil
                  )
    end;
