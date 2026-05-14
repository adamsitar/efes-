function comp_SYN(SYN1,SYN2: PSYN): bool; far;
   begin
     comp_SYN:= StrComp(SYN1^.nazov,SYN2^.nazov)<0
   end;

procedure sort_SYN(SYNs: Pptrs; top: pointer); far;
    begin
      QuickSort(SYNs,@comp_SYN,nil{@swap_SYN},0,int(top^), false)
    end;


function handle_SYN(SYN: PSYN): bool; far; forward;


procedure spracuj_SYN(_FN: string; _title: string); far;
   var    print : pointer;
   begin
     print:= nil;

     {$IFDEF PRN}
       print:= @print_SYNs;
     {$ENDIF}

     scroll_DB_FDP(_title, false,false,false, nil,
                   max_SYNs, sizeof(TSYN),
                   @new_SYN,nil,@disp_SYN,@eq_SYN,
                   '',nil,
                   nil,nil,nil,nil,nil,
                   true, @sort_SYN,nil,
                   _TBFunc_p,@handle_SYN, nil,
                   nil,nil,nil, {$IFDEF PRN} @print_SYNs {$ELSE} nil {$ENDIF}, nil,

                   _FN, nil,nil,
                   db_SYN_RIADKOV,@decodeDB_SYN, nil{@dbchg_SYN},

                   dx_sc_SYN, dy_sc_SYN, @plan_SYN,
                   nil,nil,

                   @p_syn_dbscroller
                  )
   end;


(*
function comp_MET(MET1,MET2: PMET): bool; far;
   begin
     comp_MET:= StrComp(MET1^.nazov,MET2^.nazov)<0
   end;

procedure sort_MET(METs: Pptrs; top: pointer); far;
    begin
      QuickSort(METs,@comp_MET,nil{@swap_MET},0,int(top^))
    end;


procedure spracuj_MET(_FN: string; _title: string); far;
   begin
     scroll_DB_FDP(_title,
                   max_METs, sizeof(TMET), @new_MET,nil,@disp_MET,
                   nil,nil, true, @sort_MET,
                   @handle_MET, _TBFunc_p,
                   {$IFDEF PRN} @print_METs {$ELSE} nil {$ENDIF}, nil,

                   _FN, nil,nil,
                   db_MET_RIADKOV,@decodeDB_MET, @dbchg_MET,

                   dx_MET, dy_MET, @draw_MET,
                   nil,nil
                  )
   end;

*)