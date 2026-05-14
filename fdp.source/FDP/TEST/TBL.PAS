{$I comp.h}

uses  typedef,io,str0, _ipx;

var   dir   : pdir;
      files,i : int;
      s,t   : string;

begin
  s:= ParamStr(1);
  if (s<>'') and (s[length(s)]<>'\') then s:= s+'\';
  if GetDirFiles (s,'tablet.*', dir,files)>0 then
     for i:= 0 to files-1 do
         begin
           t:= getstr(Dir^[i]^.name,2,['.']);
           if eq_str(t,'ini') or eq_str(t,'kod') then continue;
           t:= t+'.tbl';
           writeln(s+Dir^[i]^.name,' -> ',s+t);
           copyfile(s+Dir^[i]^.name,s+t);
           delfile(s+Dir^[i]^.name)
         end;
  FreeDirFiles(Dir,Files)
end.