procedure prehlad_RTZ(ppl: bool);
    var   FN : string;
    begin
      if ppl then FN:= get_PPL_FN(pathRTZ,extRTZ,tit_RTZ)
      else FN:= get_dbRTZfn;
      spracuj_RTZ(FN, @dbchg_RTZ,
                  '',nil,
                  @handle_RTZ,_TBFunc_p2,
                  true,tit_RTZ,nil
                 );
      {if not ppl then isRTZ:= false}
    end;

procedure prehlad_RTZ_PPL;
    begin
      prehlad_RTZ(true)
    end;

procedure prehlad_RTZ_ARCH;
    begin
      spracuj_RTZ(get_ARCH_FN(pathARCH_RTZ,extRTZ,tit_RTZ), @dbchg_RTZ,
                  '',nil,
                  nil,_TNull,
                  true,
                  tit_RTZ,nil
                 )
    end;
