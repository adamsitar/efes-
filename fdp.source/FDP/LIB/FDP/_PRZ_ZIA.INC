 procedure new_PRZ (PRZ1,PRZ2 : PPRZ);
     begin
       new_NTM(PNTM(PRZ1),PNTM(PRZ2))
     end;

 procedure disp_PRZ (PRZ: PPRZ);
     begin
       disp_NTM(PNTM(PRZ))
     end;


 function eq_PRZ (PRZ1,PRZ2: PPRZ): bool;
    begin
      eq_PRZ:= eq_NTM(PNTM(PRZ1),PNTM(PRZ2))
    end;

 function chg_PRZ (PRZ1,PRZ2: PPRZ): bool;
    begin
      chg_PRZ:= chg_NTM(PNTM(PRZ1),PNTM(PRZ2))
    end;


 procedure format_PRZ (PRZ: PPRZ);
     begin
       format_NTM_ (PNTM(PRZ){,'','',0})
     end;


 function idn_PRZ(PRZ: PPRZ): string;
    begin
      idn_PRZ:= cislo_NTM(PNTM(PRZ))
    end;


{ -------------------------- }
{ save                       }
{ -------------------------- }

 function  read_PRZ (key: string; PRZ: PPRZ): int;
    var    FN : string;
    begin
      if (PRZ<>nil) and (key<>'') then
         begin
           decodekey_PRZ (key, PRZ);
           FN:= get_DBfn_ (PRZ^.dav.d,PRZ^.dav.m,PRZ^.dav.r, pathPRZ,extPRZ);
           read_PRZ:= DB_najdi (PRZ,FN,db_PRZ_RIADKOV,@decodeDB_PRZ,@codekey_PRZ,true,@disp_PRZ,'')
         end
      else read_PRZ:= -1
    end;

 procedure save_PRZ (PRZ: PPRZ);
     var   FN   : string;
     begin
       FN:= get_DBfn_ (PRZ^.dav.d,PRZ^.dav.m,PRZ^.dav.r, pathPRZ,extPRZ);
       DB_oprav (PRZ, FN, db_PRZ_RIADKOV,@codeDB_PRZ,@codekey_PRZ,@dbchg_PRZ, dbattr_NTM);
     end;
