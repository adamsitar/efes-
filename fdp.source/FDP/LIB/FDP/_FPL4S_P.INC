
  procedure prehlad_FPL(ppl: bool);
      begin
        _spracuj_FPL (find_and_process_FPL4,false,
                      true,false,
                      ppl,false,nil,nil,
                      nil,[],'',
                      _TBFunc_vEp2,@handle_plan_FPL4, '',nil
                     )
      end;

  procedure prehlad_FPL_ARCH;
      begin
        _spracuj_FPL (find_and_process_FDR,false,
                      true,false,
                      false,true,nil,nil,
                      nil,[],'',
                      _TBFunc_vEp2,@handle_plan_FPL4, '',nil
                     )
      end;


  procedure prehlad_FPL_INACTIVATED;
      begin
        _spracuj_FDR (find_and_process_FDR,false,
                      false,false,
                      nil,[poz_PLAN],'',
                      _TBFunc_vEp2,@handle_plan_FDR, '',nil
                     )
      end;

  procedure prehlad_FPL_PREACTIVATED;
      begin
        _spracuj_FDR (find_and_process_FDR,false,
                      false,false,
                      nil,[poz_PREACTIVE],'',
                      _TBFunc_vEp2,@handle_plan_FDR, '',nil
                     )
      end;

  procedure prehlad_FPL_PROPOSED;
      begin
        _spracuj_FDR (find_and_process_FDR,false,
                      false,false,
                      nil,[poz_PROPOSED],'',
                      _TBFunc_vEp2,@handle_plan_FDR, '',nil
                     )
      end;

  procedure prehlad_FPL_COORDINATED;
      begin
        _spracuj_FDR (find_and_process_FDR,false,
                      false,false,
                      nil,[poz_COORDINATED..poz_PATRAT],'',
                      _TBFunc_vEp2,@handle_plan_FDR, '',nil
                     )
      end;

  {procedure prehlad_FPL_ACTIVED;
      begin
        _spracuj_FDR (find_and_process_FDR,false,
                      false,false, pozACT, '',nil,
                      _TBFunc_vEp3,@handle_plan_FDR,nil, '',nil
                     )
      end;}

  procedure prehlad_FPL_NOTACTIVED;
      begin
        _spracuj_FDR (find_and_process_FDR,false,
                      false,false,
                      nil,[poz_CANCELLED,poz_NOT_APPROVED,poz_NOT_ACTUAL],'',
                      _TBFunc_vEp2,@handle_plan_FDR, '',nil
                     )
      end;

  procedure prehlad_FPL_REALISED;
      begin
        _spracuj_FDR (find_and_process_FDR,false,
                      false,false,
                      nil,[poz_HANGAR],'',
                      _TBFunc_vEp2,@handle_plan_FDR, '',nil
                     )
      end;

  procedure prehlad_FPL_ALL;
      begin
        _spracuj_FDR (find_and_process_FDR,false,
                      false,false,
                      nil,[], '',
                      _TBFunc_vEp2,@handle_plan_FDR, '',nil
                     )
      end;


  procedure prehlad_FPL_ALL_PPL;
      begin
        _spracuj_FDR (find_and_process_FDR,false,
                      true,false,
                      nil,[],'',
                      _TBFunc_vEp2,@handle_plan_FDR, '',nil
                     )
      end;

  procedure prehlad_FPL_ALL_ARCH;
      begin
        _spracuj_FDR (find_and_process_FDR,false,
                      false,true,
                      nil,[],'',
                      _TBFunc_vEp2,@handle_plan_FDR, '',nil
                     )
      end;
