procedure _prehlad_ZAM(all: bool; ppl: bool; stat, title: string);
    var   FN: string;
    begin
      if ppl then FN:= get_PPL_FN(pathZAM,extZAM,tit_planZAM) else FN:= get_dbZAMfn;
      spracuj_ZAM(FN, nil{@dbchg_ZAM},
                  {cnl_stat}(stat), _sw_stat_us (all,@_is_stata_ZAM,@_is_stat_ZAM),
                  {$IFDEF PROCESS_ZAM} @handle_ZAM, _TBFunc_p2,
                  {$ELSE} nil, _TNull, {$ENDIF}
                  true, not all, title
                 );
    end;

procedure prehlad_ZAM(all: bool; ppl: bool);
    var   FN: string;
    begin
      _prehlad_ZAM(all,ppl,cnst_all_valid,tit_planZAM);
      if all and (not ppl) then isZAM:= false
    end;

procedure prehlad_ZAM_ARCH (all: bool);
    begin
      spracuj_ZAM(get_ARCH_FN(pathARCH_ZAM,extZAM,tit_planZAM),nil{@dbchg_ZAM},
                  '', _sw_stat_us (all,@_is_stata_ZAM,@_is_stat_ZAM),
                  {$IFDEF PROCESS_ZAM} @handle_ZAM_ARCH, _TBFunc_p2,
                  {$ELSE}  nil, _TNull,
                  {$ENDIF}
                  true, not all,
                  tit_planZAM
                 )
    end;


procedure prehlad_ZAM_plan_nase;
    begin
      _prehlad_ZAM(false,false,cnst_disk+cnst_sended+cnst_cnl,tit_zamPLAN_L);
    end;

procedure prehlad_ZAM_plan;
    begin
      _prehlad_ZAM(true,false,cnst_disk+cnst_sended+cnst_cnl,tit_zamPLAN_L);
    end;


procedure prehlad_ZAM_act;
    begin
      _prehlad_ZAM(false,false,cnst_stat_act,tit_zamACT_L);
    end;


procedure prehlad_ZAM_arr;
    begin
      _prehlad_ZAM(false,false,cnst_stat_arr,tit_zamARR_L);
    end;


procedure prehlad_ZAM_all;
    begin
      _prehlad_ZAM(false,false,'',tit_zamARR_A);
    end;
