 procedure new_ZAM(ZAM1, ZAM2: PZAM);
     begin
       FillChar(ZAM2^,SizeOf(ZAM2^),0);
       if ZAM1<>nil then
          begin
            ZAM2^:= ZAM1^;
            ZAM2^.ulohy := StrNew(ZAM1^.ulohy);
            ZAM2^.typy  := StrNew(ZAM1^.typy);
            ZAM2^.pozn  := StrNew(ZAM1^.pozn)
          end
     end;

 procedure disp_ZAM(ZAM: PZAM);
    begin
      StrDispose(ZAM^.ulohy);
      StrDispose(ZAM^.typy);
      StrDispose(ZAM^.pozn)
    end;

 procedure format_ZAM(ZAM: PZAM);
     begin
     end;


 function eq_ZAM(ZAM1,ZAM2: PZAM): bool;
    begin
      eq_ZAM:=      ((ZAM1<>nil) and (ZAM2<>nil))
                and (codekey_ZAM(ZAM1) = codekey_ZAM(ZAM2))
    end;

 function chg_ZAM(ZAM1,ZAM2: PZAM): bool;
    begin
      chg_ZAM:= not (    eq_ZAM (ZAM1,ZAM2)

                     and eq_datum (ZAM1^.zac, ZAM2^.zac)
                     and eq_datum (ZAM1^.kon, ZAM2^.kon)

                     and (ZAM1^.prav = ZAM2^.prav)
                     and (ZAM1^.vys  = ZAM2^.vys)

                     and (ZAM1^.vu   = ZAM2^.vu)

                     and (strcomp(ZAM1^.ulohy,ZAM2^.ulohy)=0)
                     and (strcomp(ZAM1^.typy,ZAM2^.typy)=0)

                     and (ZAM1^.planov = ZAM2^.planov)
                     and (ZAM1^.letov  = ZAM2^.letov)

                     and eq_lines(ZAM1^.pozn,ZAM2^.pozn)

                     and (ZAM1^.stat=ZAM2^.stat)
               )
    end;

 function idn_ZAM(ZAM: PZAM): string;
    begin
      idn_ZAM:= cut_(ZAM^.kod)
    end;


 { -------------------------- }
 { save                       }
 { -------------------------- }

 function get_dbZAMfn: string;
    begin
      get_dbZAMfn:= get_DBfn_(day,month,year, pathZAM,extZAM)
    end;

 function get_dbZAM_RPLfn: string;
    begin
      get_dbZAM_RPLfn:= pathRPL + {pathLST+ext_mFPL+'-'+}
                        {$IFDEF AIRBASE} this_airbase
                        {$ELSE}          extZAM
                        {$ENDIF}
                        +'.'+extZAM
    end;


 function read_ZAM(key: string; ZAM: PZAM): int;
    begin
      if (ZAM<>nil) and (key<>'') then
         begin
           decodekey_ZAM(key, ZAM);
           read_ZAM:= DB_najdi(ZAM,get_DBfn_(ZAM^.zac.den,ZAM^.zac.mes,ZAM^.zac.rok, pathZAM,extZAM),
                               db_ZAM_RIADKOV,@decodeDB_ZAM,@codekey_ZAM,true,
                               @disp_ZAM,''
                              )
         end
      else read_ZAM:= -1
    end;

 procedure save_ZAM(_ZAM: PZAM);
     var   ZAM: TZAM;
     begin
       new_ZAM(_ZAM,@ZAM);
       DB_oprav(@ZAM,get_DBfn_(ZAM.zac.den,ZAM.zac.mes,ZAM.zac.rok, pathZAM,extZAM),
                db_ZAM_RIADKOV,@codeDB_ZAM,@codekey_ZAM,
                @dbchg_ZAM, dbattr_ZAM
               );
       disp_ZAM(@ZAM)
     end;

 procedure save_ZAM_RPL(_ZAM: PZAM);
     var   ZAM: TZAM;
     begin
       new_ZAM(_ZAM,@ZAM);
       ZAM.stat:= cnst_disk;
       fillchar(ZAM.rec,sizeof(ZAM.rec),0);
       DB_oprav(@ZAM, get_dbZAM_RPLfn, db_ZAM_RIADKOV,@codeDB_ZAM,@codekey_ZAM_RPL,@dbchg_ZAM_RPL, dbattr_ZAM);
       disp_ZAM(@ZAM)
     end;
