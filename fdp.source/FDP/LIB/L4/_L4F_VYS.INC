
 function prienik_vysok (vys1s,vys1h, vys2s,vys2h: string): bool;
    begin
      prienik_vysok:= RPrienik (decode_l4_vys_M (vys1s),
                                decode_l4_vys_M (vys1h),
                                decode_l4_vys_M (vys2s),
                                decode_l4_vys_M (vys2h)
                               )
    end;


 function _check_rychvys_by4444 (kod : string; typ : string;
                                 var rych: single; var rych_: char;
                                 var vys: word; var vys_: char;
                                 var res: string
                                ): int;
    var   ires: int;
          sr,sv : string;
          rres,vres : bool;
    begin
      ires:= 0; res:= '';
      decode_l4_rych_vys_ (kod,rych,rych_, sr,rres, vys,vys_,sv,vres);
      if not rres then ires:= l4_err(a_15a,'',i_15a,err_15a_chybne, res)
      else if not vres then ires:= l4_err(a_15b,'',i_15b,err_15b_chybne, res)
      else _9_rychvys_rozsah(typ,
                             get_rych_kmh(rych,rych_,0,altS),
                             get_altM(vys_,vys) div m_S,
                             res,ires
                            );
      _check_rychvys_by4444:= ires
    end;


 function _check_rychvys2_by4444 (kod : string; typ : string;
                                  var rych: single; var rych_: char;
                                  var vys: word; var vys_,vys_a: char;
                                  var vys2: word; var vys2_: char;
                                  var res: string
                                 ): int;
    var   rres,vres,v2res : bool;
          ires : int;
    begin
      ires:= 0; res:= '';
      decode_l4_rych_vys2_ (kod,rych,rych_,rres, vys,vys_,vys_a,vres, vys2,vys2_,v2res);
      if not rres then ires:= l4_err(a_15a,'',i_14c,err_15a_chybne, res)
      else if not vres then ires:= l4_err(a_15b,'',i_14d,err_15b_chybne, res)
      else if not v2res then ires:= l4_err(a_15b,'',i_14e,err_15b_chybne, res)
      else _9_rychvys_rozsah(typ,
                             get_rych_kmh(rych,rych_,0,altS),
                             get_altM(vys_,vys) div m_S,
                             res,ires
                            );
      _check_rychvys2_by4444:= ires
    end;
