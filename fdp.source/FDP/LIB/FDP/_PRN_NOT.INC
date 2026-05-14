
 procedure new_PRN (PRN1,PRN2 : PPRN);
     begin
       new_NTM(PNTM(PRN1),PNTM(PRN2))
     end;

 procedure disp_PRN (PRN: PPRN);
     begin
       disp_NTM(PNTM(PRN))
     end;


 function eq_PRN (PRN1,PRN2: PPRN): bool;
    begin
      eq_PRN:= eq_NTM(PNTM(PRN1),PNTM(PRN2))
    end;

 function chg_PRN (PRN1,PRN2: PPRN): bool;
    begin
      chg_PRN:= chg_NTM(PNTM(PRN1),PNTM(PRN2))
    end;


 function idn_PRN (PRN: PPRN): string;
    begin
      idn_PRN:= cislo_NTM(PNTM(PRN))
    end;

 procedure format_PRN (PRN: PPRN);
     begin
       format_NTM_(PNTM(PRN){,pathPRN,extPRN,db_PRN_RIADKOV})
     end;


{ -------------------------- }
{ save                       }
{ -------------------------- }

 function read_PRN(key: string; PRN: PPRN): int;
    var   FN : string;
    begin
      if (PRN<>nil) and (key<>'') then
         begin
           decodekey_PRN (key, PRN);
           FN:= get_DBfn_ (PRN^.dav.d,PRN^.dav.m,PRN^.dav.r, pathPRN,extPRN);
           read_PRN:= DB_najdi (PRN,FN,db_PRN_RIADKOV,@decodeDB_PRN,@codekey_PRN,true,@disp_PRN,'')
         end
      else read_PRN:= -1
    end;

 procedure save_PRN(PRN: PPRN);
     {begin
       new_PRN (PRN,@PRNi);
       FN:= get_DBfn_ (PRN^.dav.d,PRN^.dav.m,PRN^.dav.r, pathPRN,extPRN);
       DB_oprav (@PRNi, FN, db_PRN_RIADKOV,@codeDB_PRN,@codekey_PRN,@dbchg_PRN, dbattr_NTM);
       disp_PRN (@PRNi)}
     var   DB   : PDB;
           PRNi : TPRN;
           FN   : string;
           kluc : string;
           _pos : long;
     begin
       new_PRN (PRN,@PRNi);
       FN:= get_DBfn_ (PRN^.dav.d,PRN^.dav.m,PRN^.dav.r, pathPRN,extPRN);
       DB:= New(PDB,Init(FN,DB_RWClose,db_PRN_RIADKOV,@codeDB_PRN,@decodeDB_PRN,@codekey_PRN,@dbchg_PRN,dbattr_NTM));
       kluc:= key_NTM (@PRNi);
       _pos:= DB^.vyhladaj_kluc(codekey_NTM_(kluc,PRNi.dav));
       DB^.zapis(@PRNi,_pos,false);
       Dispose(DB,Done);
       disp_PRN (@PRNi)
     end;
