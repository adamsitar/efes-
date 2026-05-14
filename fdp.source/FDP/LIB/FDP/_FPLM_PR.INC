{ vytvori identifikaciu z idn a idn_ bez medzier
}

 function idn_mFPL(FPL: PDmFPL): string;
    begin
      if FPL<>nil then
         begin
          {$IFDEF SK}
           if _identifikacia_letu_do_tsa(FPL) then idn_mFPL:= FPL^.idn+'-'+FPL^.idn_
           else
          {$ENDIF}
           idn_mFPL:= code_FPLM_7a (FPL)
         end
      else idn_mFPL:= ''
    end;

 function ssr_mFPL(FPL: PDmFPL): string;
    begin
      if FPL<>nil then ssr_mFPL:= FPL^.ssr
      else ssr_mFPL:= ''
    end;


{ --------------------------
   8a
  --------------------------
}
 function is_VFR_FL_FPLM(FPL: PDmFPL): bool;
    var   vfr    : bool;
          _trat_ : POBxys;
          _bodov : int;
          is : bool;
          i  : int;
    begin
    { kontrola zakladne parametre
    } vfr:=  (     ( get_altM(FPL^.vys_,FPL^.vys) <= alt_VFR )
               and (    ( (FPL^.vys2_=' ') and (FPL^.vys2=0) )
                     or ( get_altM (FPL^.vys_,FPL^.vys) <= alt_VFR)
                   )
             );

    { kontrola, ci na celej trati je dodrzany VFR rezim
    } if vfr then
         begin
           is:= FPL^.trat_<>nil;
           if is then begin _trat_:= FPL^.trat_; _bodov:= FPL^.bodov end
           else decode_trat_FPLM(FPL, _trat_,_bodov, false,false,false);
           i:= 0; while vfr and (i<_bodov) do with _trat_^[i] do
             begin
               vfr:= ((vys_=' ') and (vys=0)) or (get_altM(vys_,vys) <= alt_VFR);
               inc(i)
             end;
           if not is then zrus_trat_FPLM (_trat_,_bodov);
         end;

      is_VFR_FL_FPLM:= vfr
    end;

 function is_VFR_FPLM(FPL: PDmFPL): bool;
    begin
      is_VFR_FPLM:= (FPL^._8a in [VFR_let]) {and is_VFR_FL_FPLM(FPL)}
    end;


{ --------------------------
   8b
  --------------------------
}

 function is_KRL(FPL: PDmFPL): bool;
    begin
      is_KRL:= cut_(idn_mFPL(FPL))=''
    end;

{ Je to vojensky
  alebo iny plan
  [predpoklada sa pod riadenim MACC]
  ?
}
 function _is_FPLM(FPL: PDmFPL): bool;
    begin
     { Povodne platilo pravidlo, ze
       identifikacia vojenskeho letu zacina dvojcisilm zhodnym
       s vojenskym kodom letiska.

       "_7a:= cut_(FPL^.idn);
        _is_FPLM:=      (_7a<>'')
                   and  (vojenske_letisko(copy(_7a,1,2)+'0'))
                   and  (_7a[length(_7a)] in ['0','1','3','5','7','9'])
       "

       LZ - po uprave pravidiel v suvislosti s prechodom na FUA
            je mozna lubovolna identifikacia, rozlisuje sa podla
            prevadzkovala

       LK - vsetky su vojesnke

     }
     {$IFDEF LZ}
      if cut_(FPL^.vu)<>'' then _is_FPLM:= is_flo_mil(FPL^.vu)
      else
     {$ENDIF}
      _is_FPLM:= true
                     {    ( not FPLM_INE
                          )
                       or (     FPLM_INE_9
                            and vojensky_kod_typu_lietadla(FPL^.typ)
                          )
                       or (     FPLM_INE_AP
                            and (vojenske_letisko(FPL^.start.kod))
                            and (vojenske_letisko(FPL^.prist.kod))
                          )
                     }
    end;


 function is_mFPL(FPL: PDmFPL): bool;
    begin
      is_mFPL:= _is_FPLM(FPL)
    end;

 function is_oFPL(FPL: PDmFPL): bool;
    begin
      is_oFPL:= not _is_FPLM(FPL)
    end;

{ priradenie alebo vypocet typu planu, ak nie je typ priradeny
}
 function _8b_FPLM(FPL: PDmFPL): char;
    begin
      if (FPL^._8b in set_8bM) then _8b_FPLM:= FPL^._8b
      {IFDEF L4444M}
       else if FPL^.start.kod<>FPL^.prist.kod then _8b_FPLM:= VOJENSKY_LET_OAT
       else _8b_FPLM:= VOJENSKY_LET_AP
      {ELSE
       else _8b_FPLM:= VOJENSKY_LET_GAT
      ENDIF}
    end;


{ --------------------------
   9b
  --------------------------
}

 function kod_typu_lietadla (typ: string): string;
    var   _9a,_9c: string;
    begin
      {$IFDEF L4444M}
       decode_l4_9(typ,_9a,typ,_9c);
      {$ELSE}
       if (length(typ)>2) and (typ[1] in setCisl) and (typ[2] in setCisl) then typ:= copy(typ,length(typ)-1,2);
       typ:= getstr(typ,1,[icao_NXT]);
      {$ENDIF}
      kod_typu_lietadla:= typ
    end;

 function vojensky_kod_typu_lietadla(typ: string): bool;
    var   ires : int;
          res  : string;
    begin
      vojensky_kod_typu_lietadla:= false;
      if (lst_9bMIL=nil) or (lst_9bMIL^.find (kod_typu_lietadla(typ),res,ires)=-1) then Exit;
      vojensky_kod_typu_lietadla:= {system.pos(idMIL,lst_9bMIL^._rmk(res))>0}
                                   lst_9bMIL^._mil(res);
    end;

 function iny_kod_typu_lietadla(typ: string): bool;
    var   ires : int;
          res  : string;
    begin
      iny_kod_typu_lietadla:= false;
      if (lst_9bMIL=nil) or (lst_9bMIL^.find (kod_typu_lietadla(typ),res,ires)=-1) then Exit;
      iny_kod_typu_lietadla:= not lst_9bMIL^._mil(res);
    end;


{ --------------------------
   Pripomienka
  --------------------------
}

 function  pripomienka_ku_FPLM (FPL: PDmFPL): bool;
    begin
      pripomienka_ku_FPLM:=  _plan_pre(FPL^.let) and (pos(cnst_read,FPL^.stat)<>0)
    end;


{$IFDEF PROCESS_FPLM} {$IFDEF OPL}

 {$IFDEF AIRBASE}

  function _spracovanie_na_ACC (p, FPL: PDmFPL): bool;
     begin
      { oprava alebo pripomienka tu podaneho planu ?
      }
       _spracovanie_na_ACC:=     (FPL<>nil)
                             and _plan_pre(FPL^.let)
                             and (pos(cnst_read,FPL^.stat)<>0)
     end;

  procedure pozri_opravy_na_ACC(FPL: PDmFPL);
      begin
        if _spracovanie_na_ACC(nil,FPL) then isFPLM_ACC:= true
        else isFPLM_ACC:= find_FPLM(nil,@_spracovanie_na_ACC)<>-1; { pripomienka uz mohla byt vydana na inom stroji }
      end;

 {$ENDIF}


 {$IFDEF MACC}

  function _ziadost_o_pripomienku (p, FPL: PDmFPL): bool;           {_is_REQ_FPL}
     begin
        _ziadost_o_pripomienku:=
                           (FPL<>nil)
                       and ((get_chars(FPL^.stat, cnst_prop) = 1))
     end;

  function _odlozena_ziadost_o_pripomienku (p, FPL: PDmFPL): bool;  {_is_REQ_FPL_}
     begin
       _odlozena_ziadost_o_pripomienku:=
                           (FPL<>nil)
                       and ((get_chars(FPL^.stat, cnst_prop) = 2))
     end;

  function _ziadost_o_pripomienku_pre_ACC (p, FPL: PDmFPL): bool;           {_is_REQ_FPL}
     begin
       isFPLM_REQ:= isFPLM_REQ or _ziadost_o_pripomienku (p,FPL);
       isFPLM_REQ_DLA:= isFPLM_REQ_DLA or _odlozena_ziadost_o_pripomienku (p,FPL);
       _ziadost_o_pripomienku_pre_ACC:= isFPLM_REQ and isFPLM_REQ_DLA
     end;


  (*procedure pozri_ziadosti_o_pripomienku(FPL: PDmFPL);
      begin
       { prisla poziadavka na vydanie pripomienky ?
       }
        if _ziadost_o_pripomienku(nil,FPL) then isFPLM_REQ:= true
        else isFPLM_REQ:= find_FPLM(nil,@_ziadost_o_pripomienku)<>-1; { pripomienka uz mohla byt vydana na inom stroji }
      end;

  procedure pozri_odlozene_ziadosti_o_pripomienku(FPL: PDmFPL);
      begin
       { odlozenie poziadavky na pripomienku ?
       }
        if _odlozena_ziadost_o_pripomienku(nil,FPL) then isFPLM_REQ_DLA:= true
        else isFPLM_REQ_DLA:= find_FPLM(nil,@_odlozena_ziadost_o_pripomienku)<>-1;
      end;
  *)

  procedure pozri_ziadosti_o_pripomienky_pre_ACC (FPL: PDmFPL);
      begin
        isFPLM_REQ:=     _ziadost_o_pripomienku (nil,FPL);
        isFPLM_REQ_DLA:= _odlozena_ziadost_o_pripomienku (nil,FPL);

       { overenie, ci plan neprepisal povodnu ziadost
       } if not (isFPLM_REQ and isFPLM_REQ_DLA) then find_FPLM(nil,@_ziadost_o_pripomienku_pre_ACC)
         else if not isFPLM_REQ then isFPLM_REQ:= find_FPLM(nil,@_ziadost_o_pripomienku)<>-1
         else if not isFPLM_REQ_DLA then isFPLM_REQ_DLA:= find_FPLM(nil,@_odlozena_ziadost_o_pripomienku)<>-1;
      end;

 {$ENDIF}


 procedure pozri_pripomienky_na_FPLM (FPL: PDmFPL);
     begin
       { if FPL<>nil then -> zabezpecia fcie same }
       {$IFDEF AIRBASE}
         pozri_opravy_na_ACC(FPL);
       {$ENDIF}

       {$IFDEF MACC}
         pozri_ziadosti_o_pripomienky_pre_ACC(FPL);
       {$ENDIF}
     end;

{$ENDIF} {$ENDIF}

 function kontrola_na_FPLM_ARW (FPL: PDmFPL): bool;
    begin
      kontrola_na_FPLM_ARW:= false
                              {$IFDEF REPORT_FPLM_ARW}
                               or (    FPLM_ARR_WARN
                                   and (   FPLM_ARR_WARN_ALL
                                        or __plan_pre_pracovisko(FPL,false)
                                       )
                                  )
                              {$ENDIF}
    end;

{$IFDEF REPORT_FPLM_ARW}

 {procedure pozri_vydanie_spravy_ARR_na_FPLM (FPL: PDmFPL);
     begin
       isFPLM_ARW:= isFPLM_ARW or
     end;}

 function _is_FPLM_ARW (FPL: PDmFPL; s: Pstring): bool;
    var   zmena : bool;
    begin
      _is_FPLM_ARW:= kontrola_na_FPLM_ARW (FPL) and (stav_mFPL(FPL,abstime,zmena) in [poz_PATRAT])
    end;

 procedure pozri_nevydane_spravy_FPLM_ARR (zmena: bool);

     function nevydane_arr(iFPL: PmFPL): bool;
        var   i  : int;
              b  : bool;
        begin
          b:= false; i:= 0;
          if iFPL<>nil then while (not b) and (i<=iFPL^.top) do
             begin
               b:= _is_FPLM_ARW(PDmFPL(iFPL^.ap^[i]),nil);
               inc(i)
             end;
          nevydane_arr:= b
        end;

     const _FPLM_ARR_WARN     : bool = false;
           _FPLM_ARR_WARN_ALL : bool = false;

     begin
        if    (_FPLM_ARR_WARN<>FPLM_ARR_WARN)
           or (_FPLM_ARR_WARN_ALL<>FPLM_ARR_WARN_ALL)
           or zmena
              then
           begin
             _FPLM_ARR_WARN     := FPLM_ARR_WARN;
             _FPLM_ARR_WARN_ALL := FPLM_ARR_WARN_ALL;
             isFPLM_ARW:= nevydane_arr(mFPL) or nevydane_arr(oFPL)
           end;
     end;
{$ENDIF}
