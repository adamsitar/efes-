{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ zakladne spracovanie                                     €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

function eq_DVZ(DVZ1, DVZ2: PDVZ): bool;
   begin
     eq_DVZ:=      ((DVZ1<>nil) and (DVZ2<>nil))
               and (codekey_DVZ(DVZ1) = codekey_DVZ(DVZ2))
   end;


function chg_DVZ (DVZ1, DVZ2: PDVZ): bool;
   begin
     chg_DVZ:= not (    eq_DVZ (DVZ1,DVZ2)

                    and (DVZ1^.zac=DVZ2^.zac)
                    and (DVZ1^.kon=DVZ2^.kon)
                    and (DVZ1^.od =DVZ2^.od )

                    and eq_lines(DVZ1^.poziadavka,  DVZ2^.poziadavka)
                    and eq_lines(DVZ1^.odoslanie,   DVZ2^.odoslanie)
                    and eq_lines(DVZ1^.zabezpecenie,DVZ2^.zabezpecenie)

                    and eq_str(DVZ1^.stat,DVZ2^.stat)
                   )
   end;


procedure new_DVZ(DVZ1, DVZ2: PDVZ);
    begin
      FillChar(DVZ2^,SizeOf(TDVZ),0);
      if DVZ1<>nil then
         begin
           DVZ2^:= DVZ1^;
           DVZ2^.poziadavka   := StrNew(DVZ1^.poziadavka);
           DVZ2^.odoslanie    := StrNew(DVZ1^.odoslanie);
           DVZ2^.zabezpecenie := StrNew(DVZ1^.zabezpecenie)
         end
    end;

procedure copy_DVZ(DVZ1, DVZ2: PDVZ);
    begin
      disp_DVZ(DVZ2);
      new_DVZ(DVZ1,DVZ2)
    end;

procedure disp_DVZ(DVZ: PDVZ);
    begin
      with DVZ^ do
        begin
          StrDispose(poziadavka);
          StrDispose(odoslanie);
          StrDispose(zabezpecenie)
        end
    end;

procedure format_DVZ(DVZ: PDVZ);
    begin
    end;


{ -------------------------- }
{ save                       }
{ -------------------------- }

function get_dbDVZfn: string;
   begin
     get_dbDVZfn:= get_DBfn_(day,month,year, pathDVZ,extDVZ)
   end;


{ hlada DVZ ulozene v subore DB, ak ho nenajde, vrati -1
}
function find_DVZ(DVZ: PDVZ; _if: pointer): int;
   var   DVZi : TDVZ;
         FN   : string;
   begin
     if DVZ<>nil then FN:= get_DBfn(DVZ^.date, pathDVZ,extDVZ)
     else FN:= get_dbDVZfn;
     find_DVZ:= DB_prehladaj(_if, DVZ,@DVZi, @disp_DVZ, FN, db_DVZ_RIADKOV, @decodeDB_DVZ,@codekey_DVZ, false,'')
   end;


function read_DVZ(key: string; DVZ: PDVZ): int;
   begin
     if (DVZ<>nil) and (key<>'') then
        begin
          decodekey_DVZ(key, DVZ);
          read_DVZ:= DB_najdi(DVZ,get_DBfn(DVZ^.date,pathDVZ,extDVZ),db_DVZ_RIADKOV,
                              @decodeDB_DVZ,@codekey_DVZ,true,@disp_DVZ,''
                             )
        end
     else read_DVZ:= -1
   end;


procedure save_DVZ(_DVZ: PDVZ);
    var   DVZ : TDVZ;
          b : bool;
    begin
      new_DVZ(_DVZ,@DVZ);
      {$IFDEF PROCESS_DVZ}
        b:= PROC_DVZ; PROC_DVZ:= false;
      {$ENDIF}
      DB_oprav(@DVZ, get_DBfn(DVZ.date, pathDVZ,extDVZ), db_DVZ_RIADKOV,@codeDB_DVZ,@codekey_DVZ,@dbchg_DVZ, dbattr_DVZ);
      {$IFDEF PROCESS_DVZ}
       pozri_ziadosti_o_DVZ(@DVZ);
       PROC_DVZ:= b;
      {$ENDIF};
      disp_DVZ(@DVZ);
    end;


