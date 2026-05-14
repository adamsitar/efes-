function isFileAttr (DirInfo: SearchRec; Attr: word): bool;
   begin
     isFileAttr:= ((DirInfo.Attr and Attr)<>0) and (DirInfo.Name<>subdir) and (DirInfo.Name<>prevdir)
   end;


function GetDirF_(Path: string; Attr: word; p_filter: PBFunc_s): int;
   var   DirInfo : SearchRec;
         Nmb     : int;
   begin
     ResetIOError;
     Nmb:= 0;
     FindFirst(Path,Attr,DirInfo);
     while DosError=0 do
       begin
         if     isFileAttr (DirInfo,Attr)
            and (   (p_filter=nil)
                 or (TBFunc_s(p_filter)(DirInfo.Name))
                )
         then Inc(Nmb);
         FindNext(DirInfo)
       end;
     GetDirF_:= Nmb;
     ResetIOError
   end;

function GetDirF(Path: string; Attr: word): int;
   begin
     GetDirF:= GetDirF_(Path,Attr,nil)
   end;


function GetDir_(Path: string; var Dir: PDir; Attr: word; var Files: int; p_filter: PBFunc_s): int;
   var   f       : file;
         DirInfo : SearchRec;
         i       : int;
         pom     : long;
   begin
     ResetIOError;
     Dir:= nil;
     Files:= GetDirF_(Path, Attr, p_filter);

     pom:= SizeOf(PFileAttr)+SizeOf(TFileAttr); pom:= pom*Files;
     if (MaxAvail-min__heap_size < pom) then Files:= Minimum(high(word),MaxAvail-min__heap_size) div Maximum(1,pom);
     if (Files=0) then begin GetDir_:= -1; Exit end;

     GetMem(Dir,SizeOf(PFileAttr)*Files);
     FillChar(Dir^,SizeOf(PFileAttr)*Files,0);
     FindFirst(Path,Attr,DirInfo);
     i:= 0;
     while (i<Files) and (DosError=0) do
        begin
          if     isFileAttr (DirInfo,Attr)
             and (   (p_filter=nil)
                  or (TBFunc_s(p_filter)(DirInfo.Name))
                 )
             then
             begin
               New(Dir^[i]);
               with Dir^[i]^ do
                 begin
                   attr:= DirInfo.attr;
                   name:= DirInfo.name;
                   date:= DirInfo.time;
                   size:= DirInfo.size;
                   inc(i)
                 end
             end;
          FindNext(DirInfo)
        end;
     GetDir_:= i;
     ResetIOError
   end; { GetDir }


function GetDir (Path: string; var Dir: PDir; Attr: word; var Files: int): int;
   begin
     GetDir:= GetDir_(Path,Dir,Attr,Files,nil)
   end;


procedure FreeDir(var Dir: PDir; var Files: int);
    var   i: int;
    begin
      if Dir<>nil then
         begin
           for i:= 0 to Files-1 do Dispose(Dir^[i]);
           FreeMem(Dir,SizeOf(PFileAttr)*Files)
         end;
      Dir:= nil; Files:= 0
    end; { FreeDir }



function GetNmbOfFiles(Path: string): int;
   begin
     GetNmbOfFiles:= GetDirF(Path,DataAttr)
   end; { GetNmbOfFiles }

function GetDirFiles(Path,Name: string; var Dir: PDir; var Files: int): int;
   begin
     GetDirFiles:= GetDir(Path+Name, Dir, DataAttr, Files)
   end; { GetDirFiles }

procedure FreeDirFiles(var Dir: PDir; var Files: int);
    begin
      FreeDir(Dir, Files)
    end; { FreeDirFiles }



{function  MoveDir (dirfnp, dirfnn: string): int;
   begin
   end;}

procedure check_files(fn, err: string; _halt: bool);
     var   s : string;
           nl: bool;
     begin
       nl:= false;
       if (Exists(fn)<>0) then
          begin
            if err<>'' then err:= ' '+err;
            s:= fn+' '+msgNOT_FOUND+err;
            if _halt then RunError(s)
            else if s<>'' then MessError(s,true,nl)
          end;
       ResetIOError
     end;

