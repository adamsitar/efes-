 procedure prehlad_PRN(ppl: bool);
     var   FN : string;
     begin
       if ppl then FN:= get_PPL_FN(pathPRN,extPRN,tit_PRN)
       else FN:= get_DBfn_(not_archive_day,month,year, pathPRN,extPRN);
       spracuj_PRZ(FN,
                   cnl_stat(cnst_all_valid), @_is_stata_PRN,
                   @handle_PRN, _TBFunc_p2,
                   true,false, tit_PRN
                  )
     end;

 procedure prehlad_PRN_ARCH;
     begin
       spracuj_PRZ(get_ARCH_FN(pathARCH_PRN,extPRN,tit_PRN),
                   '', nil,
                   @handle_PRN_ARCH, _TBFunc_p2,
                   true,false, tit_PRN
                   )
     end;



 procedure prehlad_PRN_VLIS(ppl: bool);
     var   FN : string;
     begin
       if ppl then FN:= get_PPL_FN(pathPRN_VLIS,extPRN_VLIS,tit_PRN_VLIS)
       else FN:= get_DBfn_(not_archive_day,month,year, pathPRN_VLIS,extPRN_VLIS);
       if FN<>'' then _infop(FN,tit_PRN_VLIS,0,0, true,false,nil)
     end;

 procedure prehlad_PRN_VLIS_ARCH;
     var   FN : string;
     begin
       FN:= get_ARCH_FN(pathARCH_PRN_VLIS,extPRN_VLIS,tit_PRN_VLIS);
       if FN<>'' then _infop(FN,tit_PRN_VLIS,0,0, true,false,nil)
     end;
