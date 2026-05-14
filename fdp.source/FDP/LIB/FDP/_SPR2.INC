function handle_SPR(sc: PScroller; SPR: PSPR): bool; far; forward;


function _is_odo(SPR: PSPR; s: Pstring): bool; far;
   begin
     _is_odo:= eq_str(SPR^.ods,NETaddress)
   end;

function _is_dor(SPR: PSPR; s: Pstring): bool; far;
   begin
     _is_dor:= not eq_str(SPR^.ods,NETaddress)
   end;


procedure spracuj_SPR(_FN: string; _filter : pointer; _title: string); far;
    var   print : pointer;
    begin
      print:= nil;

      {$IFDEF PRN}
        print:= @print_SPRs;
      {$ENDIF}

      scroll_DB_FDP(_title, false,false,false, nil,

                    MAX_SPRs, sizeof(DSPR),
                    @new_SPR,nil,@disp_SPR,nil,

                    '',nil,
                    nil,nil,nil,_filter,nil,
                    false,nil,nil,

                    _TBFunc_p2, @handle_SPR, nil,
                    nil,nil,nil, print,nil,

                    _FN, nil,nil,
                    db_SPR_RIADKOV,@decodeDB_SPR, @dbchg_SPR,

                    dxi_SPR, dyi_SPR, @plan_SPR,
                    nil,nil,
                    nil
                   )
   end;
