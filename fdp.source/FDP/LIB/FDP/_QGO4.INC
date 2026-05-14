procedure prehlad_QGO(ppl: bool);
    var   FN : string;
    begin
      if ppl then FN:= get_PPL_FN(pathQGO,extQGO,tit_QGO)
      else FN:= get_dbQGOfn;
      spracuj_QGO(FN, nil,{@dbchg_QGO,}
                  cnl_stat(cnst_all_valid), @_is_stata_QGO,
                  @handle_QGO,_TBFunc_p2,
                  true, tit_QGO,nil
                 );
      if not ppl then isQGO:= false
    end;

procedure prehlad_QGO_PPL;
    begin
      prehlad_QGO(true)
    end;

procedure prehlad_QGO_ARCH;
    begin
      spracuj_QGO(get_ARCH_FN(pathARCH_QGO,extQGO,tit_QGO), nil,{@dbchg_QGO,}
                  '',nil,
                  nil,_TNull,
                  true,
                  tit_QGO,nil
                 )
    end;
