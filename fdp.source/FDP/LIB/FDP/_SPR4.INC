procedure prehlad_SPR;
    begin
      spracuj_SPR(get_dbSPRfn(nil),nil,tit_MSGL)
    end;

procedure  prehlad_SPR_odo;
    begin
      spracuj_SPR(get_dbSPRfn(nil),@_is_odo,tit_MSGS)
    end;

procedure  prehlad_SPR_dor;
    begin
      spracuj_SPR(get_dbSPRfn(nil),@_is_dor,tit_MSGR);
      isSPR:= false
    end;


procedure prehlad_SPR_ARCH;
    begin
      spracuj_SPR(get_ARCH_FN(pathARCH_MES,extMES,tit_MSG),nil,tit_MSG)
    end;

procedure prehlad_SPR_ARCH_odo;
    begin
      spracuj_SPR(get_ARCH_FN(pathARCH_MES,extMES,tit_MSGS),@_is_odo,tit_MSGS)
    end;

procedure prehlad_SPR_ARCH_dor;
    begin
      spracuj_SPR(get_ARCH_FN(pathARCH_MES,extMES,tit_MSGR),@_is_dor,tit_MSGR)
    end;


