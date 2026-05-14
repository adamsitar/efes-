{ -----------
   FPL
  -----------
}

 function  _FRM_FPL4(FPL: PFPL4): bool;
     var   s: string;
     begin
       if FPL<>nil then s:= tit_fpl_copy else s:= tit_FPL4_PLAN;
       formular_FPL4(FPL,user,hd_FPL,true,s,nil,nil);
       _FRM_FPL4:= false
     end;


{ -----------
   CHG
  -----------
}

{ Oprava lubovolneho planovaneho
}
 {function _is_CHG(FPL: PDFPL4; s: Pstring): bool; far;
    var   cond: string;
    begin
      cond:= cnl_stat(cnst_FPL_CHG);
      _is_CHG:= _is_stat_FPLm(FPL,@cond)
    end;}

 function  _CHG_FPL4(FPL: PFPL4): bool; far;
     begin
       _CHG_FPL4:= false;
       if FPL<>nil then formular_FPL4(FPL,user,hd_CHG,false,tit_fpl_chg,nil,nil)
     end;

 procedure CHG_FPL4i;
     begin
       _spracuj_FPL (true,true,true,false, true,false, nil,nil,
                     nil,ms_ICAOplan+ms_ICAOact,'',
                     _TBFunc_p,@_CHG_FPL4,
                     tit_fpl_chg,hlpmnuFPL4
                    );
     end;



{ -----------
   CNL
  -----------
}

 function  _CNL_FPL4(FPL: PFPL4): bool; far;
     var   res  : string;
           ires : int;
     begin
       _CNL_FPL4:= false;
       if Ask2(msgVERIPHY,ask_fpl_cnl+' '+codekey_FPL4(FPL)+'?',titNO,White,clBUTTON_COLOR,waitASK*18) <> ansAno then Exit;
       zarad_FPL4 (FPL,hd_CNL,true,user);
     end;

 procedure CNL_FPL4i;
     begin
       _spracuj_FPL (true,true,true,false, true,false, nil,nil,
                     nil,ms_ICAOplan+ms_ICAOact,'',
                     _TBFunc_p,@_CNL_FPL4,
                     tit_fpl_cnl,hlpmnuFPL4
                    );
     end;


{ -----------
   DLA
  -----------
}

{ Start len z vlastneho letiska
}
 function _filter_FPL_DEP (FPL: PFPL4; pitem: PFPL4_item_filter): bool; far;
    var   kod: string; h,m: byte;
          B: TsBod;
    begin
      _filter_FPL_DEP:=     _ACT_OR_DEP
                         or (not decode_l4_13(FPL^._13, kod,h,m,h,m))
                         or (is_OB(kod,B,true) and (B.ine.podriadene))
    end;

 function  _DLA_FPL4(FPL: PFPL4): bool; far;
     begin
       _DLA_FPL4:= false;
       if FPL<>nil then formular_FPL4(FPL,user,hd_DLA,false,tit_fpl_dla,nil,nil)
     end;

 procedure DLA_FPL4i;
     begin
       _spracuj_FPL (true,true,true,false, true,false, nil,nil,
                     @_filter_FPL_DEP,ms_ICAOplan,'',
                     _TBFunc_p,@_DLA_FPL4,
                     tit_fpl_dla,hlpmnuFPL4
                    );
     end;


{ -----------
   DEP
  -----------
}

 function  _DEP_FPL4(FPL: PFPL4): bool; far;
     begin
       _DEP_FPL4:= false;
       if FPL<>nil then formular_FPL4(FPL,user,hd_DEP,false,tit_fpl_dep,nil,nil)
     end;

 procedure DEP_FPL4i;
     begin
       _spracuj_FPL (true,true,true,false, true,false, nil,nil,
                     @_filter_FPL_DEP,ms_ICAOplan,'',
                     _TBFunc_p,@_DEP_FPL4,
                     tit_fpl_dep,hlpmnuFPL4
                    );
     end;


{ -----------
   ARR
  -----------
}

{ ARR len na vlastnom letisku
}
 function _filter_FPL_ARR(FPL: PFPL4; pitem: PFPL4_item_filter): bool; far;
    var   kod,kodb: string; h,m: byte;
          B: TsBod;
    begin
      _filter_FPL_ARR:=    (not decode_l4_16(FPL^._16, 0,0,kod,h,m,h,m,kodb))
                        or (is_OB(kod,  B, true))
                        or (is_OB(kodb, B, true))
    end;

 function  _ARR_FPL4(FPL: PFPL4): bool; far;
     begin
       _ARR_FPL4:= false;
       if FPL<>nil then formular_FPL4(FPL,user,hd_ARR,false,tit_fpl_arr,nil,nil)
     end;

 procedure ARR_FPL4i;
     begin
       _spracuj_FPL (true,true,false,false, true,false, nil,nil,
                     @_filter_FPL_ARR,ms_ICAOact,'',
                     _TBFunc_p,@_ARR_FPL4,
                     tit_fpl_arr,hlpmnuFPL4
                    );
     end;

