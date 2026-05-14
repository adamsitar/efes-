{$IFDEF OPL}

 function OmFPL.test_na(na: bool): bool;
    var   bres: bool;
    begin
      bres:= false;

      bres:= _test_na(pre_i,  p_pre_i,  na) or bres;
      bres:= _test_na(pre_iot,p_pre_iot,na) or bres;

      bres:= _test_na(pro_i,  p_pro_i,  na) or bres;
      bres:= _test_na(pro_iot,p_pro_iot,na) or bres;

      bres:= _test_na(coo_i,  p_coo_i,  na) or bres;
      bres:= _test_na(coo_iot,p_coo_iot,na) or bres;

      bres:= _test_na(act_iot,p_act_iot,na) or bres;

      bres:= _test_na(prop_day,p_prop_day,na) or bres;
      bres:= _test_na(cnl_day, p_cnl_day,na) or bres;

      test_na:= bres
    end;


 function OmFPL.zmenene_parametre_platnosti: bool;
    var   bres: bool;
    begin
      bres:= inherited zmenene_parametre_platnosti;

     { zmenil sa niektory parameter na false,
       t.j. vypadla niektora polozka
       zo sledovania ?
     } bres:= test_na(false) or bres;

      zmenene_parametre_platnosti:= bres
    end;


 function OmFPL.cas_pre_preaktivaciu_planov: bool;
    var   bres: bool;
    begin
      bres:= inherited cas_pre_preaktivaciu_planov;

     { zmenil sa niektory parameter na true,
       t.j. pribudla niektora polozka
       do sledovania ?
     } bres:= test_na(true) or bres;

      cas_pre_preaktivaciu_planov:= bres
    end;

{$ENDIF}
