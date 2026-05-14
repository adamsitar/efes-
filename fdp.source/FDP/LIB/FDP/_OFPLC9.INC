 function OcFPL.zmenene_parametre_platnosti: bool;
    var   bres: bool;
    begin
      bres:= inherited zmenene_parametre_platnosti;
      zmenene_parametre_platnosti:= _test_na(is_FPLC_CPL, @FPLC_CPL, false) or bres
    end;

