procedure prehlad_SYN;
    begin
      spracuj_SYN(get_dbSYNfn,tit_syn_last);
    end;

procedure prehlad_SYN_ARCH;
    begin
      spracuj_SYN(get_ARCH_FN(pathARCH_SYN,extSYN,tit_syn_arch),tit_syn_arch)
    end;


(*
procedure prehlad_MET;
    begin
      spracuj_MET(get_dbMETfn,'Prehåad poslednòch spr†v METAR');
    end;

procedure prehlad_MET_ARCH;
    var   tit: string;
    begin
      tit:= 'Prehåad archivovanòch spr†v METAR';
      spracuj_MET(get_ARCH_FN(extMET,extMET,tit),tit)
    end;
*)
