procedure prehlad_PRZ (all: bool; ppl: bool);
    var   FN : string;
    begin
      if ppl then FN:= get_PPL_FN(pathPRZ,extPRZ,tit_przPLANNED)
      else FN:= get_DBfn_(not_archive_day,month,year, pathPRZ,extPRZ);
      spracuj_PRZ(FN,
                  cnl_stat(cnst_all_valid), _sw_stat_us (all, @_is_stata_PRZ,@_is_stat_PRZ),
                  @handle_PRZ, _TBFunc_p2,
                  true,not all, tit_przPLANNED
                 )
    end;

procedure prehlad_PRZ_PPL (all: bool);
    begin
      spracuj_PRZ(get_PPL_FN(pathPRZ,extPRZ,tit_przPLANNED),
                  cnl_stat(cnst_all_valid), _sw_stat_us (all, @_is_stata_PRZ,@_is_stat_PRZ),
                  @handle_PRZ, _TBFunc_p2,
                  true,not all, tit_przPLANNED
                 )
    end;

procedure prehlad_PRZ_ARCH (all: bool);
    begin
      spracuj_PRZ(get_ARCH_FN(pathARCH_PRZ,extPRZ,tit_przPLANNED),
                  '',_sw_stat_us (all, @_is_stata_PRZ,@_is_stat_PRZ),
                  @handle_PRZ_ARCH, _TBFunc_p2,
                  true,false, tit_przPLANNED
                  )
    end;
