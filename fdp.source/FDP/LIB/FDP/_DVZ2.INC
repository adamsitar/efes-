function comp_DVZ(DVZ1,DVZ2: PDVZ): bool; far;
   var   res, bp1,bp2,bk1,bk2: bool;
         sp1,sp2,sk1,sk2: string;
   begin
     res:= false;
     sp1:= _mairbase(DVZ1^.pre);
     sp2:= _mairbase(DVZ2^.pre);
     sk1:= _mairbase(DVZ1^.kym);
     sk2:= _mairbase(DVZ2^.kym);

    (* {$IFDEF AIRBASE}
       bp1:= is_this_airbase(DVZ1^.pre);
       bp2:= is_this_airbase(DVZ2^.pre);
       bk1:= is_this_airbase(DVZ1^.kym);
       bk2:= is_this_airbase(DVZ2^.kym);

      { diverzie drzane pre toto letisko
      } if sp1=sp2 then
          if bk1 and bk2 then res:= false
          else if bk1 then res:= false
          else if bk2 then res:= true
          else res:= sk1<sk2
       else

       diverzie drzane na tomto letisku
       ostatne diverzie
    *)
     res:= sp1 = sp2;
     if res then res:= sk1 < sk2
     else res:= sp1 < sp2;

     comp_DVZ:= res
   end;

procedure sort_DVZ(DVZs: Pptrs; top: pointer);
    begin
      QuickSort(DVZs,@comp_DVZ,nil{@swap_DVZ},0,int(top^), false)
    end;


function _is_stata_DVZ (DVZ: PDVZ; s: Pstring): bool; far;
   begin
     _is_stata_DVZ:= _is_statp(DVZ^.stat,s,false)
   end;


function _is_stat_DVZ_pre (DVZ: PDVZ; s: Pstring): bool; far;
   begin
     _is_stat_DVZ_pre:= _is_statp(DVZ^.stat,s,false) and _plan_pre(DVZ^.pre)
   end;

function _is_stat_DVZ_kym (DVZ: PDVZ; s: Pstring): bool; far;
   begin
     _is_stat_DVZ_kym:= _is_statp(DVZ^.stat,s,false) and _plan_pre(DVZ^.kym)
   end;


function _plan_pre_pracovisko(DVZ: PDVZ): bool; far;
   begin
     _plan_pre_pracovisko:=  {$IFDEF AIRBASE}
                                  _plan_pre(DVZ^.pre)
                               or _plan_pre(DVZ^.kym)
                             {$ELSE}
                               true
                             {$ENDIF}

   end;

function _is_stat_DVZ (DVZ: PDVZ; s: Pstring): bool; far;
   begin
     _is_stat_DVZ:= _is_statp(DVZ^.stat,s,false) and _plan_pre_pracovisko(DVZ)
   end;


function _vlastne(DVZ: PDVZ; s: Pstring): bool; far;
   begin
     {$IFDEF AIRBASE}  _vlastne:= _plan_pre(DVZ^.pre) and _is_stata_DVZ(DVZ,s)
     {$ELSE}           _vlastne:= false
     {$ENDIF}
   end;

function _drzane(DVZ: PDVZ; s: Pstring): bool; far;
   begin
     {$IFDEF AIRBASE}  _drzane:= _plan_pre(DVZ^.kym) and _is_stata_DVZ(DVZ,s)
     {$ELSE}           _drzane:= false
     {$ENDIF}
   end;

function _platne(DVZ: PDVZ; s: Pstring): bool; far;
   begin
     {$IFDEF AIRBASE}  _platne:=  (_plan_pre(DVZ^.kym) or _plan_pre(DVZ^.pre)) and _is_stata_DVZ(DVZ,s)
     {$ELSE}           _platne:= false
     {$ENDIF}
   end;


procedure spracuj_DVZ(_FN: string;
                      _data_filter : string; _filter : pointer;
                      _handler : pointer; _handler_type : TScrollAct_handler_type;
                      _print : bool;
                      _title: string; _hlpXXX : Pchar
                     ); far;
   var    print : pointer;
   begin
     print:= nil;

     {$IFDEF MATCA} {$IFDEF PRN}
       if _print then print:= @print_DVZs;
     {$ENDIF} {$ENDIF}

     scroll_DB_FDP(_title, false,false,false, nil,

                   max_DVZ, sizeof(TDVZ),
                   @new_DVZ,nil,@disp_DVZ,@eq_DVZ,
                   '',nil,
                   @_data_filter, nil,nil,_filter,_filter,
                   true, @sort_DVZ,nil,
                   _handler_type,_handler,nil,
                   nil,nil,nil, print,nil,

                   _FN, {_FNfunc, _FNfunc_p,} nil,nil,
                   db_DVZ_RIADKOV,@decodeDB_DVZ, nil,{@dbchg_DVZ,}

                   dx_DVZ, dy_DVZ, @plan_DVZ,
                   nil, _hlpXXX,

                   @p_dvz_dbscroller
                  )
   end;
