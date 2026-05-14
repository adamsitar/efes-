procedure prehlad_PRS(all: bool; ppl: bool);
    begin
      spracuj_PRS(false,false,
                  ppl,false,false,
                  cnl_stat(cnst_all_valid), _sw_stat_us (all,@_is_stata_PRS,@_is_stat_PRS),
                  {$IFDEF PROCESS_PRS} @handle_PRS, _TBFunc_p2,
                  {$ELSE} nil, _TNull, {$ENDIF}
                  true,not all,
                  tit_planPRS, nil,nil
                 )
    end;

procedure prehlad_PRS_ARCH (all: bool);
    begin
      spracuj_PRS(false,false,
                  false,true,false,
                  '', _sw_stat_us (all,@_is_stata_PRS,@_is_stat_PRS),
                  {$IFDEF PROCESS_PRS} @handle_PRS_ARCH, _TBFunc_p2,
                  {$ELSE}  nil, _TNull,
                  {$ENDIF}
                  true, not all,
                  tit_planPRS_A, nil,nil
                 )
    end;


{procedure prehlad_PRS_plan;
    begin
      spracuj_PRS(false,false,
                  true,false,false,
                  cnst_disk+cnst_sended+cnst_cnl, @_is_stat_PRS,
                  @handle_PRS, _TBFunc_p2,
                  true,false,
                  tit_prsPLAN_L, nil,nil
                 )
    end;
}

procedure prehlad_PRS_acc;
    begin
      spracuj_PRS(false,false,
                  true,false,false,
                  cnst_sended+cnst_prop+cnst_dec+cnst_acc, @_is_stat_PRS,
                  @handle_PRS, _TBFunc_p2,
                  true,false,
                  tit_prsACC_L, nil,nil
                 )
    end;

procedure prehlad_PRS_act;
    begin
      spracuj_PRS(false,false,
                  false,false,false,
                  cnst_stat_act, @_is_stat_PRS,
                  @handle_PRS, _TBFunc_p2,
                  true,false,
                  tit_prsACT_L, nil,nil
                 )
    end;

procedure prehlad_PRS_arr;
    begin
      spracuj_PRS(false,false,
                  false,false,false,
                  cnst_stat_arr, @_is_stat_PRS,
                  @handle_PRS, _TBFunc_p2,
                  true,false,
                  tit_prsARR_L, nil,nil
                 )
    end;

procedure prehlad_PRS_all;
    begin
      spracuj_PRS(false,false,
                  false,false,false,
                  '', @_is_stat_PRS,
                  @handle_PRS, _TBFunc_p2,
                  true,false,
                  tit_prsALL_L, nil,nil
                 )
    end;
