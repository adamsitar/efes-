procedure prehlad_DVZ_act;
    begin
      spracuj_DVZ(get_dbDVZfn,
                  cnst_dvz_req+cnst_dvz_zac+cnst_dvz_zaa+cnst_dvz_alr, @_is_stata_DVZ,
                  {$IFDEF PROCESS_ZAM} @handle_DVZ, _TBFunc_p2,
                  {$ELSE} nil, _TNull, {$ENDIF}
                  true,
                  tit_dvz_prehlad,nil
                 )
    end;


procedure prehlad_DVZ(all: pointer; ppl: bool);
    var   FN: string;
    begin
      if ppl then FN:= get_PPL_FN(pathDVZ,extDVZ,tit_dvz_prehlad)
      else FN:= get_dbDVZfn;
      if all=nil then all:= @_is_stata_DVZ;
      spracuj_DVZ(FN, cnl_stat(cnst_all_valid), all,
                  {$IFDEF PROCESS_ZAM} @handle_DVZ, _TBFunc_p2,
                  {$ELSE} nil, _TNull, {$ENDIF}
                  true,tit_dvz_prehlad,nil
                 );
      if (all=@_is_stata_DVZ) or (not ppl) then isDVZ:= false;
    end;

procedure prehlad_DVZ_PPL;
    begin
      prehlad_DVZ(nil,true)
    end;


procedure prehlad_DVZ_ARCH;
    begin
      spracuj_DVZ(get_ARCH_FN(pathARCH_DVZ,extDVZ,tit_dvz_prehlad),
                  '',nil, {cnl_stat(cnst_all_valid), @_is_stat}
                  {$IFDEF PROCESS_ZAM} @handle_DVZ, _TBFunc_p2,
                  {$ELSE} nil, _TNull, {$ENDIF}
                  true,
                  tit_dvz_prehlad,nil
                 )
    end;
