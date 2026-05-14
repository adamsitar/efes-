{ --------------------------
   INICIALIZACIA/UVOLNENIE
  --------------------------
}
 procedure new_mFPL(FPL1, FPL2: PDmFPL);
     begin
       FillChar(FPL2^,SizeOf(DmFPL),0);
       if FPL1<>nil then
          begin
            FPL2^:= FPL1^;
            with FPL2^ do
              begin
                trat := StrNew(FPL1^.trat);
                pozn := StrNew(FPL1^.pozn);
                trat_:= nil;
               {$IFDEF MAPY};
                mapa := nil
               {$ENDIF}
              end
          end
     end;

 procedure disp_mFPL(FPL: PDmFPL);
     begin
       with FPL^ do
         begin
           StrDispose(trat);
           StrDispose(pozn);
           if trat_<>nil then
              begin
                FreeMem(trat_, sizeof(TOBxy)*bodov);
                trat_:= nil
              end;
         end;
        {$IFDEF MAPY}
         if FPL^.mapa<>nil then begin Mapa^.vypni_trat(Mapa^.zTrate,FPL^.mapa); FPL^.mapa:= nil end;
        {$ENDIF}
      {fillchar(FPL^,sizeof(DmFPL),0) - ! nemozem, lebo by som zmazal nastavenia v checkFPL }
     end;


 procedure copy_mFPL(FPL1, FPL2: PDmFPL);
     begin
       disp_mFPL(FPL2);
       new_mFPL(FPL1, FPL2)
     end;


{ --------------------------
   POROVNANIE
  --------------------------
}

 function eq_mFPL (FPL1, FPL2: PDmFPL): bool;
    begin
      eq_mFPL:=      ((FPL1<>nil) and (FPL2<>nil))
                 and (codekey_FPLM(FPL1) = codekey_FPLM(FPL2))
    end;


 function eq_mFPL_data(FPL1, FPL2: PDmFPL): bool; far;
    begin
      eq_mFPL_data:= eq_mFPL(FPL1, FPL2)
    end;


 function chg_mFPL (FPL1, FPL2: PDmFPL): bool;
    var   bres: bool;
    begin
      bres:=    not (    eq_mFPL (FPL1,FPL2)

                     and (FPL1^.stat=FPL2^.stat)

                     and (FPL1^._8b=FPL2^._8b)
                     and (FPL1^._8a=FPL2^._8a)

                     and (FPL1^.ssr_=FPL2^.ssr_)
                     and (FPL1^.ssr=FPL2^.ssr)

                     and (FPL1^.com_=FPL2^.com_)

                     and (FPL1^.typ=FPL2^.typ)
                     and (FPL1^.typ2=FPL2^.typ2)

                     and (FPL1^.rych=FPL2^.rych)
                     and (FPL1^.rych_=FPL2^.rych_)

                     and (FPL1^.vys=FPL2^.vys)
                     and (FPL1^.vys_=FPL2^.vys_)

                     and (FPL1^.vys2=FPL2^.vys2)
                     and (FPL1^.vys2_=FPL2^.vys2_)

                     and (not chg_AP(FPL1^.start,FPL2^.start))
                     and (not chg_AP(FPL1^.prist,FPL2^.prist))
                     and (FPL1^.prist_=FPL2^.prist_)

                     and eq_lines(FPL1^.trat,FPL2^.trat)
                     and eq_lines(FPL1^.pozn,FPL2^.pozn)

                     and (FPL1^.vu=FPL2^.vu)
                     and memcomp(@FPL1^.ulohy,@FPL2^.ulohy,sizeof(FPL1^.ulohy))

                     {and dap}
                    );
      chg_mFPL:= bres
    end;


 function eq_KRL(FPL1, FPL2: PDmFPL): bool;
    begin
      eq_KRL:=       eq_mFPL(FPL1,FPL2)
                and (eq_airbase(FPL1^.let,FPL2^.let))
                and (eq_datum(FPL1^.dap,FPL2^.dap))
    end;


 function eq_KRL_data(FPL1, FPL2: PDmFPL): bool; far;
    begin
      eq_KRL_data:=

                    eq_mFPL_data(FPL1,FPL2)

                and (FPL1^._8b=FPL2^._8b)
                and (FPL1^._8a=FPL2^._8a)

                {and (FPL1^.ssr_=FPL2^.ssr_)
                and (FPL1^.ssr=FPL2^.ssr)

                and (FPL1^.com_=FPL2^.com_)}

                and (FPL1^.typ=FPL2^.typ)
                and (FPL1^.typ2=FPL2^.typ2)

                {and (FPL1^.rych=FPL2^.rych)
                and (FPL1^.rych_=FPL2^.rych_)}

                and (FPL1^.vys=FPL2^.vys)
                and (FPL1^.vys_=FPL2^.vys_)

                and (FPL1^.vys2=FPL2^.vys2)
                and (FPL1^.vys2_=FPL2^.vys2_)

                and (not chg_AP(FPL1^.start,FPL2^.start))
                and (not chg_AP(FPL1^.prist,FPL2^.prist))
                and (FPL1^.prist_=FPL2^.prist_)

                and eq_lines(FPL1^.trat,FPL2^.trat)
                {and eq_lines(FPL1^.pozn,FPL2^.pozn)}

                and (FPL1^.vu=FPL2^.vu)
                and memcomp(@FPL1^.ulohy,@FPL2^.ulohy,sizeof(FPL1^.ulohy))
    end;



 function comp_idn_mFPL(FPL1,FPL2: PDmFPL): bool;
    var   c1,c2: long;
          r1,r2: int;
    begin
      {
      val(cut_(FPL1^.idn),c1,r1); val(cut_(FPL2^.idn),c2,r2);
      if (r1=0) and (r2=0) then
         begin
           if c1=c2 then comp_idn_mFPL:= FPL1^.idn_ < FPL2^.idn_
           else comp_idn_mFPL:= c1 < c2
         end
      else comp_idn_mFPL:= idn_mFPL(FPL1) < idn_mFPL(FPL2)
      }
     {$IFNDEF L4444M}
      if FPL1^.idn=FPL2^.idn then comp_idn_mFPL:= FPL1^.idn_<FPL2^.idn_
      else
     {$ENDIF}
           comp_idn_mFPL:= FPL1^.idn<FPL2^.idn
    end;

{ -------------------------- }
{ save                       }
{ -------------------------- }

 function get_fn_mFPL_let: string;
    begin
      get_fn_mFPL_let:= get_DBfn_(day,month,year, pathFPL_M,ext_mFPL)
    end;

 function get_fn_mFPL_RPL_let: string;
    begin
      get_fn_mFPL_RPL_let:= pathRPL + {pathLST+ext_mFPL+'-'+}
                            {$IFDEF AIRBASE} this_airbase
                            {$ELSE}          ext_mFPL
                            {$ENDIF}
                            +'.'+ext_mFPL
    end;


 function _find_FPLM(FPL: PDmFPL; _if: pointer; fn,ext: string): int;
    var   FPLi: DmFPL;
    begin
      fillchar(FPLi,sizeof(FPLi),0);
      if (fn='') then
         if FPL<>nil then fn:= get_DBfn(FPL^.date, pathFPL_M,ext)
         else fn:= get_DBfn_(day,month,year, pathFPL_M,ext);
      if _if=nil then _find_FPLM:= DB_najdi(FPL,fn,db_mFPL_RIADKOV,@decodeDB_FPLM,@codekey_FPLM,false,@disp_mFPL,'')
      else _find_FPLM:= DB_prehladaj(_if, FPL,@FPLi, @disp_mFPL, fn,db_mFPL_RIADKOV,@decodeDB_FPLM,@codekey_FPLM,false,'')
    end;

 function find_KRL(FPL: PDmFPL; _if: pointer): int;
    begin
      find_KRL:= _find_FPLM(FPL, _if, '',ext_KRL)
    end;

 function find_FPLM(FPL: PDmFPL; _if: pointer): int;
    begin
      find_FPLM:= _find_FPLM(FPL, _if, '',ext_mFPL)
    end;

 function  find_FPLMa (key: string): PFPLM;
    var    i : int;
           p : PFPLM;
    begin
      p:= nil;
      if mFPL<>nil then
         begin
           i:= mFPL^.find_key(key);
           if i>-1 then p:= mFPL^.ap^[i]
         end;
      {$IFDEF EDD}
       if (p=nil) and (PROP_mFPL<>nil) then
          begin
            i:= PROP_mFPL^.find_key(key);
            if i>-1 then p:= PROP_mFPL^.ap^[i]
          end;
      {$ENDIF}
      find_FPLMa:= p
    end;


 { predpoklada, ze FPL je neinicalizovana struktura !
 }
 function read_mFPL(key: string; FPL: PDmFPL): int;
    var   res: int;
    begin
      if (FPL<>nil) and (key<>'') then
         begin
         {$IFDEF KRL}
           if is_KRL(FPL) then
              begin
                decodekey_KRL(key, FPL);
                res:= DB_najdi(FPL,get_DBfn(FPL^.date, pathFPL_M,ext_KRL),
                               db_mFPL_RIADKOV,@decodeDB_FPLM,@codekey_KRL,
                               true, @disp_mFPL,''
                              )
              end
           else
         {$ENDIF}
                begin
                  decodekey_FPLM(key, FPL);
                  res:= DB_najdi(FPL,get_DBfn(FPL^.date, pathFPL_M,ext_mFPL),
                                 db_mFPL_RIADKOV,@decodeDB_FPLM,@codekey_FPLM,
                                 true, @disp_mFPL,''
                                );
                end;
           {if res>-1 then format_mFPL(FPL);}
           read_mFPL:= res
         end
      else read_mFPL:= -1
    end;


 procedure save_mFPL(_FPL: PDmFPL);
     var   FPL{,FPLp} : DmFPL;
           FN   : PathStr;
           ext  : ExtStr;
           b,is : bool;
           i    : int;

     begin
      {$IFDEF TRENAZER} Exit; {$ENDIF}
       new_mFPL(_FPL,@FPL); { naplnenie buffera, pretoze v nasledujucom prikaze sa caka na spracovanie }
      {new_mFPL(nil,@FPLp);}

       if is_KRL(@FPL) then
          begin
           {$IFDEF KRL}
             FN:= get_dbfn(FPL.date, pathFPL_M,ext_KRL);
             i:= _find_FPLM(@FPL,@eq_KRL,FN,'');
             DB_zapis(@FPL,i,FN,db_mFPL_RIADKOV,@codeDB_FPLM,@codekey_KRL,@dbchg_KRL,dbattr_FPM);
           {$ENDIF}
          end
        else begin
               {$IFDEF PROCESS_FPLM}
                 b:= isFPLM_PROC; isFPLM_PROC:= false;
                 {is:= read_mFPL(codekey_FPLM(FPL),@FPLp)<>-1;}
               {$ENDIF}

               {if is_mFPL(FPL) then} ext:= ext_mFPL {else ext:= ext_oFPL};
               FN:= get_DBfn(FPL.date, pathFPL_M,ext);
               DB_oprav(@FPL, FN,db_mFPL_RIADKOV,@codeDB_FPLM,@codekey_FPLM,@dbchg_mFPL, dbattr_FPM);

               {$IFDEF PROCESS_FPLM}
                 {$IFDEF OPL} pozri_pripomienky_na_FPLM(@FPL); {$ENDIF}
                 isFPLM_SAVED:= true; { pouziva sa na kontrolu v check_REQ_FPL }
                 isFPLM_PROC:= b;
               {$ENDIF}
             end;

       {disp_mFPL(@FPLp);}
       disp_mFPL(@FPL)
     end;


 procedure save_mFPL_RPL_ (_FPL: PDmFPL; prepisat: bool);
     var   FPL : DmFPL;
           fn : string;
     begin
       fn:= get_fn_mFPL_RPL_let;
       new_mFPL(_FPL,@FPL);
       FPL.date:= RPL_DATE;
       FPL.stat:= cnst_disk;
       fillchar(FPL.rec,sizeof(FPL.rec),0);

       if    (prepisat)
          or (_find_FPLM(@FPL,nil, fn,'')=-1)
          or (Ask2(msgWARNING,
                  'RPL '+code_FPLM_7a(@FPL)+'-'+FPL.start.kod+' '+inf_exist+' '+ask_prepisat,'',
                  White,clBUTTON_COLOR,waitASK*18
                 ) = ansAno
             )
          then DB_oprav(@FPL,get_fn_mFPL_RPL_let,db_mFPL_RIADKOV,@codeDB_FPLM,@codekey_FPLM,@dbchg_mFPL_RPL, dbattr_FPM);

       disp_mFPL(@FPL)
     end;

 procedure save_mFPL_RPL (_FPL: PDmFPL);
     begin
       save_mFPL_RPL_ (_FPL,true);
     end;
