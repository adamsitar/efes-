function  DelFile (fn: string): int;
    var   Reg : Registers;
          f   : file;
          res : int;
    begin
      res:= Exists(fn);
      DelFile:= res;
      if res<>0 then Exit;
      {
      f:= f+#0;
      with Reg do begin
        AH:= $41;
        DS:= Seg(f[1]);
        DX:= Ofs(f[1])
      end;
      asm cli end;
      MsDos(Reg);
      asm sti end
      }
      Assign(f,fn);
      SetFAttr(f,Archive);
      Erase(f);
      DelFile:= 0;
      ResetIOError
    end; { DelFile }


procedure Del (fn: string);
    var   di : SearchRec;
          D  : DirStr;
          N  : NameStr;
          E  : ExtStr;
    begin
      if (cut_(fn)='') then Exit;
      ResetIOError;
      FSplit(fn, D,N,E);
      FindFirst(fn,Archive,di);
      while (DosError=0) do
        begin
          if isFileAttr (di,DataAttr) then DelFile(D+di.name);
          FindNext(di)
        end
    end;

function  RenFile (fnp, fnn: string): int;
    var   f   : file;
          res : int;
    begin
      res:= Exists(fnp);
      RenFile:= res;
      if res<>0 then Exit;
      ResetIOError;
      Assign(f,fnp); Rename(f, fnn);
      IOError;
      RenFile:= IOErrorCode
    end;


{procedure Ren (fnp,fnn: string);
    var   di : SearchRec;
          D  : DirStr;
          N  : NameStr;
          E  : ExtStr;
    begin
      if (fnp<>'') then
         begin
           ResetIOError;
           FSplit(fn, D,N,E);
           FindFirst(fn,Archive,di);
           while (DosError=0) do
             begin
               RenFile(D+di.name);
               FindNext(di)
             end
         end;
    end;
}

function  MoveFile(oldf, newf: string): int;
     var  res : int;
{    var   Reg: Registers;
    begin
      oldf:= oldf+#0;
      newf:= newf+#0;
      with Reg do begin
        AH:= $56;
        DS:= Seg(oldf[1]);
        DX:= Ofs(oldf[1]);
        ES:= Seg(newf[1]);
        DI:= Ofs(newf[1])
      end;
      asm cli end;
      MsDos(Reg);
      asm sti end}
    var   f     : file;
          ftime : Longint; { For Get/SetFTime}
    begin
      res:= Exists(oldf);
      MoveFile:= res;
      if res<>0 then Exit;

      ResetIOError;
      Assign(f, oldf); Reset(f); GetFTime(f,ftime); Close(f);
      MoveFile:= CopyFile(oldf,newf);
      DelFile (oldf); { nepresuvam kvoli fragmentacii }
      Assign(f, newf); Reset(f); SetFTime(f,ftime); Close(f);
      ResetIOError
    end; { MoveFile }


{
  skopiruje f1 do f2:
  - ak je _pos>0, od pozicie pos
  - ak _append potom f1 pripoji na koniec f2
}
function  CopyFileI (FN1,FN2: string; _pos: long; _append, _main: bool): int;
    const BUFF_SIZE = $2000;
    var   Attr, NumRead, NumWritten : word;
          F1,F2     : file;
          buffer    : Pbytes;
          bufsize   : long;
          r         : int;

    label X;

    begin
      r:= FExists(FN1);
      CopyFileI:= r;
      if r<>0 then Exit;

      ResetIOError;
      bufsize:= Minimum(BUFF_SIZE,MaxAvail shr 2);
      GetMem(buffer,bufsize);

      Assign(F1,FN1);
      GetFAttr(F1, Attr);
      SetFAttr(F1, Archive);
      Reset(F1,1);
      if _pos>0 then Seek(F1,Minimum(_pos,FileSize(F1)));
      if _main then
         begin
           _pos:= FilePos(F1);
           Close(F1)
         end;

      Assign(F2,FN2);
      if (not _append) then Rewrite(F2,1)
      else if Exists(FN2)<>0 then Rewrite(F2,1)
      else begin
             Reset(F2,1);
             Seek(F2,FileSize(F2))
           end;

      repeat
        if _main then
           begin
             Reset(F1,1);
             Seek(F1,_pos)
           end;
        BlockRead (F1,buffer^,bufsize,NumRead);
        BlockWrite(F2,buffer^,NumRead,NumWritten);
        if _main then
           begin
             _pos:= FilePos(F1);
             Close(F1);
             CheckProcesses0
           end;
      until (NumRead = 0) or (NumWritten<>NumRead);

      Close(F2);
      if not _main then Close(F1);

      SetFAttr(F2, Attr);
      SetFAttr(F1, Attr);

      FreeMem(buffer,bufsize);
      ResetIOError
    end; { CopyFile }


function  CopyFile (FN1,FN2: string): int;
   begin
     CopyFile:= CopyFileI (FN1,FN2, 0,false,false)
   end;


function  BackupFile_(path: string; dest: string): int;
   var    info : SearchRec;
          r  : word;
          pdir,pname,pext,
          ddir,dname,dext: string;
          i : int;
   begin
     ResetIOError;

     FSplit(path, pdir,pname,pext);
     FSplit(dest, ddir,dname,dext);

     r:= Exists(path);
     if r<>0 then begin BackupFile_:= r; Exit end;

     r:= Exists(ddir+allfiles {'a:\*.*'});
     if not(r in[0,2,18]) then begin BackupFile_:= r; Exit end;

     FindFirst(path,Archive,info);
     FSplit(path, sDir,sName,sExt);
     i:= drive_ind(ddir);
     if (i<0) or (DiskFree(i)<info.Size) then begin BackupFile_:= 1001; Exit end;
     if dname='' then
        begin
          dname:= pname;
          dext := pext;
        end;
     r:= CopyFileI(path, ddir{'a:\'}+dname+dext, 0,false,true);
     BackupFile_:= r;
     ResetIOError
   end;

function  BackupFile(Path: string): int;
   begin
     BackupFile:= BackupFile_(Path,'a:\')
   end;


(*
function  CopyTxtFile(f1name, f2name: string; _append: bool): int;
    var   f1,f2: text;
          s: string;
    begin
      CopyTxtFile:= 0;

      Assign(f1,f1name);
      Assign(f2,f2name);
      Reset(f1);
      if (not _append) then Rewrite(f2)
      else if Exists(f2name) in [2,18] then Rewrite(f2)
           else Append(f2);
      while not(IOError or Eof(f1)) do
        begin
          ReadLn(f1,s);
          WriteLn(f2,s);
        end;
      Close(f2);
      Close(f1)
    end; { CopyTxtFile }
*)

procedure _mkdir(s: string);
    var   i : int;
          t,u : string;
    begin
      ResetIOError;
      if s='' then Exit;

      u:= ''; i:= 1;
      while (i<=length(s)) and (s[i] in ['\','.']) do begin u:= u+s[i]; inc(i) end;
      i:= 1;
      repeat
        t:= getstr(s,i,['\']);
        if (t<>'') then
           begin
             u:= u+t;
             if (Exists(u)<>0) then mkdir(u);
             u:= u+'\'
           end;
        inc(i)
      until t=''
    end;

function  MoveDir (dirfnp, dirfnn: string): int;
   var    Dp,Dn : DirStr;
          Np,Nn : NameStr;
          Ep,En : ExtStr;
          Dir   : PDir;
          Files,i : int;
   begin
     FSplit(dirfnn, Dn,Nn,En);
     _mkdir(Dn);
     FSplit(dirfnp, Dp,Np,Ep);
     GetDir(dirfnp, Dir,ReadOnly+Archive,Files);
     if Files>0 then
        begin
          for i:= 0 to Files-1 do MoveFile(Dp+Dir^[i]^.name,Dn+Dir^[i]^.name);
          FreeDir(Dir,Files)
        end;
   end;
