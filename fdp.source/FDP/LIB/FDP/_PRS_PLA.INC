 procedure new_PRS(PRS1,PRS2 : PPRS);
     begin
       FillChar(PRS2^,SizeOf(TPRS),0);
       if PRS1<>nil then
          begin
            PRS2^:= PRS1^;
            PRS2^.pozn:= StrNew(PRS1^.pozn)
          end
     end;

 procedure copy_PRS(PRS1,PRS2 : PPRS);
     begin
       disp_PRS(PRS2);
       new_PRS(PRS1,PRS2)
     end;

 procedure disp_PRS(PRS: PPRS);
     begin
       StrDispose(PRS^.pozn)
     end;


 function test_PRS(PRS: PPRS): bool;
    begin
      test_PRS:= _item_18_(PRS^.pozn,rmk_TEST,1) <> ''
    end;


 function eq_PRS(PRS1,PRS2: PPRS): bool;
    begin
      eq_PRS:=      ((PRS1<>nil) and (PRS2<>nil))
                and (codekey_PRS(PRS1) = codekey_PRS(PRS2))
    end;

 {function eq_PRS_data(PRS1,PRS2: PPRS): bool; far;
    begin
      eq_PRS_data:=      ((PRS1<>nil) and (PRS2<>nil))
                     and (codekey_PRS(PRS1) = codekey_PRS(PRS2))
    end;
 }

 function chg_PRS(PRS1,PRS2 : PPRS): bool;
    begin
      chg_PRS:= not (     eq_PRS   (PRS1,PRS2)

                     and  eq_str   (PRS1^.vys1, PRS2^.vys1)
                     and  eq_str   (PRS1^.vys2, PRS2^.vys2)

                     and  eq_datum (PRS1^.zac,  PRS2^.zac)
                     and  eq_datum (PRS1^.kon,  PRS2^.kon)

                     and  eq_str   (PRS1^.unt,  PRS2^.unt)
                     and  eq_lines (PRS1^.pozn, PRS2^.pozn)

                     and  eq_str   (PRS1^.stat, PRS2^.stat)
                )
    end;


{ -------------------------- }
{ save                       }
{ -------------------------- }

 function get_dbPRSfn: string;
    begin
      get_dbPRSfn:= get_DBfn_(day,month,year, pathPRS,extPRS)
    end;

 function get_dbPRS_RPLfn: string;
    begin
      get_dbPRS_RPLfn:= pathRPL + {pathLST+ext_mFPL+'-'+}
                        {$IFDEF AIRBASE} this_airbase
                        {$ELSE}          extPRS
                        {$ENDIF}
                        +'.'+extPRS
    end;

 function get_dbPRSdfn (das: TDate): string;
    begin
      get_dbPRSdfn:= get_DBfn_ (das.d,das.m,das.r, pathPRS,extPRS)
    end;

 function get_dbPRSifn (PRS: PPRS): string;
    begin
      if PRS<>nil then get_dbPRSifn:= get_dbPRSdfn (PRS^.das)
      else get_dbPRSifn:= get_dbPRSfn
    end;


 function _find_PRS(PRS: PPRS; _if: pointer; fn,ext: string): int;
    var   PRSi: TPRS;
    begin
      fillchar(PRSi,sizeof(PRSi),0);
      if (fn='') then fn:= get_dbPRSifn(PRS);
      _find_PRS:= DB_prehladaj(_if, PRS,@PRSi, @disp_PRS, fn,db_PRS_RIADKOV,@decodeDB_PRS,@codekey_PRS,false,'')
    end;


 function read_PRS(key: string; PRS: PPRS): int;
    var   res : int;
    begin
      if (PRS<>nil) and (key<>'') then
         begin
           decodekey_PRS (key, PRS);
           res:= DB_najdi (PRS,get_dbPRSifn(PRS),db_PRS_RIADKOV,@decodeDB_PRS,@codekey_PRS,true,@disp_PRS,'');
           if res>-1 then format_PRS(PRS);
           read_PRS:= res
         end
      else read_PRS:= -1
    end;


 procedure save_PRS(PRS: PPRS);
     var   PRSi : TPRS;
     begin
       new_PRS (PRS,@PRSi);
       DB_oprav (@PRSi, get_dbPRSifn(PRS), db_PRS_RIADKOV,@codeDB_PRS,@codekey_PRS,@dbchg_PRS, dbattr_PRS);
       disp_PRS (@PRSi)
     end;

 procedure save_PRS_RPL(PRS: PPRS);
     var   PRSi: TPRS;
     begin
       new_PRS (PRS,@PRSi);
       PRSi.das := RPL_DATE;
       PRSi.stat:= cnst_disk;
       fillchar (PRSi.rec,sizeof(PRSi.rec),0);
       DB_oprav (@PRSi,get_dbPRS_RPLfn, db_PRS_RIADKOV,@codeDB_PRS,@codekey_PRS_RPL,@dbchg_PRS_RPL, dbattr_PRS);
       disp_PRS (@PRSi)
     end;

