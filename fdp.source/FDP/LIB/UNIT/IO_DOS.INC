function _Exists(Path: string; Attr: Word; var F: SearchRec): byte;
   var   b : bool;
   begin
     if Path<>'' then
        begin
          ResetIOError;
          FindFirst(Path,Attr,F);
          b:= IOError; if DosError=18 then IOErrorCode:= 2;
          _Exists:= IOErrorCode;
          ResetIOError
        end
     else _Exists:= 2
   end; { _Exists }


function Exists(FileName: string): byte;
   var   F : SearchRec;
   begin
     Exists:= _Exists(FileName, AnyFile, F);
     ResetIOError;
   end; { Exists }


function FExists(FileName: string): byte;
   var   F : SearchRec;
   begin
     ResetIOError;
     FExists:= _Exists(FileName, ReadOnly+Hidden+SysFile+Archive, F)
   end; { FExists }


{
 vrati plne meno, ak nim nie je
}
function GetFname(fname, fpath, fext: string): string;
   begin
     FSplit(fname, sDir,sName,sExt);
     if sExt='' then fname:= fName + fExt;
     if sDir='' then fname:= fPath + fName;
     GetFName:= fname
   end;

function _filesize(name: string): long;
   var   f: file of byte;
         l: longint;
   begin
     if FExists(name)<>0 then _filesize:= 0
     else begin
            Assign(f,name);
            Reset(f);
            _filesize:= FileSize(f);
            Close(f)
           end;
     ResetIOError
   end;


function _find_file(path,fn: string): string;
    var  Dir,Fil :  PDir;
         i,j,k, dpoc,fpoc : int;
         res : string;
    begin
      res:= '';
      if path[length(path)]<>'\' then path:= path+'\';

      GetDir(path+allfiles, Dir,Directory,dpoc);
      i:= 0;
      while (i<dpoc) and (res='') do
        begin
          res:= _find_file(path+Dir^[i]^.name,fn);
          inc(i)
        end;
      FreeDirFiles(Dir,dpoc);

      if res='' then
         begin
           GetDirFiles (path,allfiles, Fil,fpoc);
           j:= 0;
           while (j<fpoc) and (res='') do
               begin
                 if eq_str(Fil^[j]^.name,fn) then res:= path+fn;
                 inc(j)
                end;
           FreeDirFiles(Fil,fpoc)
         end;

      ResetIOError;
      _find_file:= res
    end;


function FindFile(path,fn: string): string;
   begin
     FindFile:= _find_file(path,fn)
   end;


function ReadFile(var p: pointer; var size: long; fname: string): bool;
    var  f: file;
    begin
      ReadFile:= false; p:= nil;
      if Exists(fname)<>0 then Exit;

      Assign(f,fname); Reset(f,1); size:= FileSize(f);
      if AllocMem(p,size) then
         begin
           BlockRead(f,p^,size);
           ReadFile:= true
        end;
      Close(f)
    end; { ReadFile }


function _GetFTime(FN: string): long;
   var   f   : file;
         ftF : long;
   begin
     if Exists(FN)<>0 then _GetFTime:= 0
     else begin
            Assign(f,FN);
            Reset(f);
            GetFTime(f,ftF);
            Close(f);
            _GetFTime:= ftF
          end
   end;

procedure _SetFTime(FN: string; T: long);
   var    f : file;
   begin
     if Exists(FN)<>0 then Exit
     else begin
            Assign(f,FN);
            Reset(f);
            SetFTime(f,T);
            Close(f)
          end
   end;


{procedure _UpDateFTime_(var f: file);
    begin
    end;}

procedure _UpDateFTime(FN: string);
    var   T: long;
          D: DateTime;
    begin
      D.Year:= Year; D.Month:= Month; D.Day:= Day;
      D.Hour:= Hour; D.Min:= Min; D.Sec:= Sec;
      packtime(D,T);
      _SetFTime(FN,T)
    end;


procedure _BlockRW(RW: byte; var f: File; var buf; count: word; var res: word);
    begin
      if RW=0 then BlockRead(f, buf,count, res)
      else BlockWrite(f, buf,count, res)
    end;


function drive_ind(dir: string): int;
   var   d: char;
   begin
     drive_ind:= 0;
     dir:= getchar(cut_(dir));
     if (dir<>'') and (dir[1]<>'\') then
        begin
          d:= upcase(dir[1]);
          if d in ['A'..'Z'] then drive_ind:= ord(d)-ord('C')+3
          else drive_ind:= -1
        end
   end;

