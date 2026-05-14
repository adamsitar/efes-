{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ Udrzba disku                                             €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
function comp_time_FileAttr(f1,f2: PFileAttr): bool;
   begin
     if f1^.date=f2^.date then comp_time_FileAttr:= f1^.name<f2^.name
     else comp_time_FileAttr:= f1^.date<=f2^.date
   end;

function comp_fn_FileAttr(d1,d2: PFileAttr): bool;
   begin
     comp_fn_FileAttr:= d1^.name < d2^.name
   end;


function najstarsi_subor(Path,Name: string): string;
   var   DirInfo   : SearchRec;
         fn        : string;
         najstCas  : real;
         {najstSub : int;
         Dir       : PDir;
         Files,i   : int;}
   begin
   { Rok 2000... co budes robit, dievca? }
     fn:= ''; najstCas:= DateToSec(2999,12,31) + TimeToSec(23,59,59);
     {najstSub:= -1;
     GetDirFiles(Path,Name,Dir,Files);
     for i:= 0 to Files-1 do}
     FindFirst(path+name,DataAttr,DirInfo);
     while DosError=0 do
       begin
         if isFileAttr (DirInfo,DataAttr) and (najstCas > DirInfo.time) then
            begin
              najstCas:= DirInfo.time;
              fn:= DirInfo.name;
            end;
         ResetIOError;
         FindNext(DirInfo)
       end;
     najstarsi_subor:= fn;
     {FreeDirFiles(Dir,Files)}
   end; { get_najstarsi_subor }


function najmladsi_subor (Path,Name: string): string;
   var   DirInfo   : SearchRec;
         fn        : string;
         najmlCas  : real;
         {najmlSub : int;
         Dir       : PDir;
         Files     : int;}
   begin
     fn:= ''; najmlCas:= 0;
     {GetDirFiles(Path,Name,Dir,Files);
     najmlSub:= -1;
     for i:= 0 to Files-1 do}
     FindFirst(path+name,DataAttr,DirInfo);
     while DosError=0 do
       begin
         if isFileAttr (DirInfo,DataAttr) and (najmlCas < DirInfo.time) then
            begin { hladam najstarsi subor }
              najmlCas:= DirInfo.time;
              fn:= DirInfo.name;
            end;
         ResetIOError;
         FindNext(DirInfo)
       end;
     najmladsi_subor:= fn
     {FreeDirFiles(Dir,Files)}
   end; { najmladsi_subor }


function dalsi_subor(path,name, iname: string; smer: int): string;
   var   Dir       : PDir;
         Files,i,p : int;
   begin
     dalsi_subor:= '';
     GetDirFiles(Path,Name,Dir,Files);
     if Files=0 then Exit;
     FSplit(iname, sDir,sName,sExt); iname:= sName+sExt;
     QuickSort(PPtrs(Dir),@comp_time_FileAttr,nil,0,Files-1,false);
     i:= 0; while (i<Files) and (Dir^[i]^.name<>iname) do inc(i);
     if i<Files then
        begin
          if smer>0 then i:= minimum(i+1,N(Files-1))
          else i:= minimum(N(i-1),i);
          dalsi_subor:= Dir^[i]^.name
        end
     else dalsi_subor:= Dir^[Files-1]^.name;
     FreeDirFiles(Dir,Files)
   end;



procedure zmaz_najstarsi_subor(Path,Name: string);
    var   s: string;
    begin
      s:= najstarsi_subor(Path,Name);
      if s<>'' then DelFile(Path+s)
    end; { zmaz_najstarsi_subor }


procedure zmaz_stare_subory(Path,Name: string; pocet_hodin: longint);
    var   i  : int;
          dt : DateTime; { For Pack/UnpackTime }
          Datum,DatumS  : real;
          Dir    : PDir;
          Files  : int;
    begin
      if pocet_hodin=0 then Exit;

      Datum:= DateToSec(Year,Month,Day) + TimeToSec(hour,min,sec) - 60*60 * pocet_hodin;
      GetDirFiles(Path,Name,Dir,Files);
      for i:= 0 to Files-1 do
          begin
            UnpackTime(Dir^[i]^.date,dt);
            DatumS:= DTtoSec(dt.Year,dt.Month,dt.Day,dt.hour,dt.min,dt.sec);
            if (Datum > DatumS) then DelFile(Path+Dir^[i]^.name);
            CheckProcesses0
          end;
      FreeDirFiles(Dir,Files)
    end; { zmaz_stare_subory }



function vytvor_novy_subor(Path: string): bool;
   var   f : file;
   begin
     ResetIOError;
     if Exists(Path) in [2,18] then
        begin
          Assign(f,Path); Rewrite(f);
          Close(f);
          vytvor_novy_subor:= true
        end
     else vytvor_novy_subor:= false;
     ResetIOError;
   end;  { vytvor_novy_subor }


procedure zapis_text_do_subora(fn,s: string);
    var   t : text;
    begin
      if cut_(s)='' then Exit;

      ResetIOError;
      vytvor_novy_subor(fn);
      Assign(t,fn); Append(t);
      writeln(t,s);
      Close(t);
      ResetIOError
    end;
