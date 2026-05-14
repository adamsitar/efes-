{ Konverzia datovycch suborov
}

uses  Typedef,
      io, db, dos, math, str0, utime,
      Archiv,
      Kody,
      _L4_def, _FPL4;


const E = '@@@';

var   Dir      : PDir;
      Files, i : int;
      path     : string;
      D        : DirStr;
      Name     : NameStr;
      Ext      : ExtStr;

      FPL      : DFPL4;


{$I _FPL40.cod}


function C(FPL: PFPL4; p: pointer): byte;
   begin
     C:= do_item__NEXT;
     writeln(' '+FPL^._7+'...');
     DB_oprav(FPL, D+Name+'.'+E,db_FPL4_RIADKOV,@codeDB_FPL4,@code_key_FPL4,@dbchg_FPL4, dbattr_FP4)
   end;


begin
  fillchar(FPL,sizeof(FPL),0);
  path:= paramstr(1);
  if (length(path)>0) and (path[length(path)]<>'\') then path:= path+'\';
  GetDirFiles(path,'*.'+extFPL, Dir,Files);
  for i:= 0 to Files-1 do
    begin
      FSplit(path+Dir^[i]^.Name,D,Name,Ext);
      writeln('Converting '+path+Dir^[i]^.Name+'...');
      do_items_DB  (@C,nil,
                    @FPL,@disp_FPL4,
                    path+Dir^[i]^.Name,
                    db_FPL40_RIADKOV,
                    nil,
                    @decodeDB_FPL40,
                    nil,
                    nil
                   );
      DelFile(path+Dir^[i]^.Name);
    end;
  FreeDirFiles(Dir,Files);

  GetDirFiles(path,'*.'+E, Dir,Files);
  for i:= 0 to Files-1 do
    begin
      FSplit(path+Dir^[i]^.Name,D,Name,Ext);
      RenFile(path+Dir^[i]^.Name,D+Name+'.'+extFPL);
      DelFile(path+Dir^[i]^.Name)
    end;
  FreeDirFiles(Dir,Files);
end.
