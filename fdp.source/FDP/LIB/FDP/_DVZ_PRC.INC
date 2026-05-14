{
  DVZ schvalene, odmietnute, ... sa vracaju s priznakom cnst_read
}

{ -------------------------------
  CHG
}
function CHG_DVZ(DVZ: PDVZ): bool; far;
   var   res: bool;
   begin
     CHG_DVZ:= false;
     res:= formular_DVZ(DVZ, false, DVZ^.stat {add_stat(DVZ^.stat,cnst_chg),} tit_dvz_chg)
   end;

procedure DVZ_oprava;
    var   tit: string;
    begin
      tit:= tit_dvz_chg;
      spracuj_DVZ(get_PPL_FN(pathDVZ,extDVZ,tit),
                  cnst_all_valid, @_is_platne,
                  @CHG_DVZ, _TBFunc_p,
                  false,
                  tit,nil
                 )
    end;


{ ----------------------
a) ZIADOST O DIVERZIU
----------------------
}
{ -------------------------------
  REQ
}
function REQ_DVZ(DVZ: PDVZ): bool; far;
   var   res: bool;
   begin
     REQ_DVZ:= false;
     res:= formular_DVZ(DVZ, false, cnst_prop, tit_dvz_req)
   end;

{ -------------------------------
  DEP  -  zrusenie alebo odoslanie na DVZ
}
function DEP_DVZ(DVZ: PDVZ): bool; far;
   var   res: bool;
   begin
     DEP_DVZ:= false;
     formular_DVZ(DVZ, false, {cnst_prop+}cnst_active,tit_dvz_act)
   end;

{ -------------------------------
  ARR  -  ukoncenie DVZ
}
function ARR_DVZ(DVZ: PDVZ): bool; far;
   var   res: bool;
   begin
     ARR_DVZ:= false;
     if pos(cnst_disk,DVZ^.stat)<>0 then
        begin
          DVZ^.stat:= cnst_CNL;
          save_DVZ(DVZ)
        end
     else zmen_stat_DVZ(DVZ,cnst_finish,true)
   end;



procedure DVZ_poziadavka;
    var   tit: string;
    begin
      tit:= tit_dvz_req;
      spracuj_DVZ(get_dbDVZfn,
                  cnst_disk, @_is_vlastne,
                  @REQ_DVZ, _TBFunc_p,
                  false,
                  tit,nil
                 )
    end;

procedure DVZ_odosli;
    var   tit: string;
    begin
      tit:= tit_dvz_act;
      spracuj_DVZ(get_dbDVZfn,
                  cnst_acc, @_is_vlastne,
                  @DEP_DVZ, _TBFunc_p,
                  false,
                  tit,nil
                 )
    end;

procedure DVZ_koniec;
    var   tit: string;
    begin
      tit:= tit_dvz_end;
      spracuj_DVZ(get_PPL_FN(pathDVZ,extDVZ,tit),
                  cnst_acc+cnst_active+cnst_warn, @_is_vlastne,
                  @ARR_DVZ, _TBFunc_p,
                  false,
                  tit,nil
                 )
    end;



{ --------------------------
b) SCHVALOVANIE DIVERZIE
--------------------------
}
{ -------------------------------
  REQ_REC
}
function REQ_REC_DVZ(DVZ: PDVZ): bool; far;
   var   res: bool;
   begin
     REQ_REC_DVZ:= false;
     res:= formular_DVZ_REQ(DVZ,false)
   end;


{ -------------------------------
  WARN_DVZ
}
function WARN_DVZ(DVZ: PDVZ): bool; far;
   var   res: bool;
   begin
     WARN_DVZ:= false;
     res:= formular_DVZ____(DVZ,false, cnst_read+cnst_warn, tit_dvz_alr)
   end;

function CNL_WARN_DVZ(DVZ: PDVZ): bool; far;
   var   res: bool;
   begin
     CNL_WARN_DVZ:= false;
     res:= formular_DVZ____(DVZ,false, cnst_read+cnst_active, tit_dvz_cln)
   end;



{ -------------------------------
  CNL  -  ukoncenie DVZ
}
function CNL_DVZ(DVZ: PDVZ): bool; far;
   var   res: bool;
   begin
     CNL_DVZ:= false;
     zmen_stat_DVZ(DVZ,cnst_read+cnst_CNL,DVZ^.stat<>cnst_disk)
   end;




procedure DVZ_spracuj_ziadost;
    var   tit: string;
    begin
      tit:= tit_dvz_acc;
      spracuj_DVZ(get_dbDVZfn,
                  cnst_prop, @_is_drzane,
                  @REQ_REC_DVZ, _TBFunc_p,
                  false,
                  tit,nil
                 );
      isREQ_DVZ_:= find_DVZ(nil,@_is_prop_DVZ_)<>-1;
      (*{$IFDEF STATUS} {$IFDEF A-A}
        if isREQ_DVZ_ then btREQ^.show else btREQ^.hide to predsa vyriesi odlozena ziadost
      {$ENDIF} {$ENDIF}*)
    end;


procedure DVZ_vystraha;
    var   tit: string;
    begin
      tit:= tit_dvz_alr;
      spracuj_DVZ(get_dbDVZfn,
                  cnst_prop+cnst_acc+cnst_active, @_is_drzane,
                  @WARN_DVZ, _TBFunc_p,
                  false, tit,nil
                 )
    end;

procedure DVZ_vystraha_zrusenie;
    var   tit: string;
    begin
      tit:= tit_dvz_cln;
      spracuj_DVZ(get_dbDVZfn,
                  cnst_warn, @_is_drzane,
                  @CNL_WARN_DVZ, _TBFunc_p,
                  false, tit,nil
                 )
    end;


procedure DVZ_zrusenie;
    var   tit: string;
    begin
      tit:= tit_dvz_acn;
      spracuj_DVZ(get_dbDVZfn,
                  cnst_warn, @_is_drzane,
                  @CNL_DVZ, _TBFunc_p,
                  false,
                  tit,nil
                 )
    end;
