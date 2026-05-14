uses bios,time,typedef,datadef,data,db,archiv;


var f1,f2: string;

    i,m: int;

    FPL: DmFPL;


begin
  f1:= ParamStr(1);
  f2:= ParamStr(2);
  if (f1='') or (f2='') then
     begin
       f1:= 'd:\demo\opl\fpl\16-12-94.fpl';
       f2:= get_DBfn_(day,month,year,'c:\exe\opl\fpl\',ext_mFPL);
     end;

  i:= 0;
  m:= DB_poloziek(f1, db_mFPL_RIADKOV);
  while i<m do
    begin
      DB_citaj(i, @FPL,f1, db_mFPL_RIADKOV,@decodeDB_mFPL);
      FPL.date.d:= day;
      FPL.date.m:= month;
      FPL.date.r:= year;
      FPL.stat:= '.';
      DB_zapis(@FPL,i,f2,db_mFPL_RIADKOV,@codeDB_mFPL,@codeDBkey_mFPL,@dbchg_mFPL);
      inc(i);
    end;

end.

