{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ Udrzba disku                                             €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

{
  Vola sa kazdu novu hodinu, udrzba archivu;
  - presunie subory starsie ako den do adresa archiv
  - zmaze subory archivu starsie ako ArchDays.

  Subory musia byt oznacene konvenciou
         -----
                den-mes-rok.*
                -------------
  pretoze dnes mozem pripravit plan na pozajtra,
  teda nemozem brat datum vytvorenia subora.
}


{ I io_dir.inc} { len ladenie }

const wr_archive: bool = false;

procedure archivuj_subory(path,mask, arch  : string;
                          podla_mena : bool;       { ak nie, tak podla casu vytvorenia }
                          archive_by : TypeOfArchive
                         );

    var   DirInfo : SearchRec;
          fn : string;
          {Dir  : PDir;
          Files, i : int;}

          rr : word; mm,dd,hh : byte;
          tm,td,th ,tp : real;
          ar,gm : bool;
          D  : DirStr;

          x,y : int;
          s : string;

    const semaphor: bool = false;

    begin
      if semaphor or (archive_by = not_archive) then Exit;

     {$IFNDEF DEMO}
      semaphor:= true;

      if arch[length(arch)]<>'\' then arch:= arch+'\';

      gm:= InGraphMode;
      tm:= DateToSec(Year,Month,0);
      tp:= Day;  td:= tm + tp*secDAY;
      tp:= Hour; th:= td + tp*secHOUR;

      (*GetDirFiles(path,mask, Dir,Files);
      {if Files>0 then InfoCakaj(msgWAITING,msg_ARCHIV_CHECK);}
      for i:= 0 to Files-1 do
      *)

      FindFirst(path+mask,DataAttr,DirInfo);
      while DosError=0 do
        begin
          if isFileAttr (DirInfo,DataAttr) then
            begin
              ar:= false; fn:= path+DirInfo.Name;
              if decode_archived_date (fn,podla_mena, rr,mm,dd,hh) then
                 case archive_by of
                   by_hours  : ar:= th > DTtoSec(rr,mm,dd,hh+ArchHours,0,0);
                   by_days   : ar:= td > DateToSec(rr,mm,dd);
                   by_months : ar:= tm > DateToSec(rr,mm,0)
                 end;
              if ar then
                 begin
                   if wr_archive and (not gm) then
                      begin
                        x:= whereX; y:= whereY;
                        if arch<>'' then s:= '-> archiving ' else s:= '-> deleting ';
                        s:= s + fn + '...';
                        GoToXY(x+3,y);
                        write(s)
                      end;
                   if arch<>'' then MoveFile(fn, arch+DirInfo.Name) else DelFile(fn);
                   if wr_archive and (not gm) then
                      begin
                        GoToXY(X,Y);
                        ClrEol;
                        GoToXY(X,Y)
                      end
                 end
            end;
          CheckProcesses0;
          FindNext(DirInfo)
        end;

      (*{if Files>0 then InfoCakaj_zatvor;}
      FreeDirFiles(Dir,Files);*)
      semaphor:= false
     {$ENDIF}
    end;


procedure uprac_archiv (path,mask    : string;
                        podla_mena   : bool;       { ak nie, tak podla casu vytvorenia }
                        archive_by   : TypeOfArchive;
                        archive_then : Tarch_nmb
                       );

    var   DirInfo : SearchRec;
          fn : string;
          {Dir : PDir;
          Files, i : int;}

          tm,td,th, tp : real;
          mm,dd,hh : byte; rr : word;

          gm,ar : bool;
          x,y : int;


    const semaphor: bool = false;

    begin
      if semaphor then Exit;

     {$IFNDEF DEMO}
      semaphor:= true;

      gm:= InGraphMode;
      tm:= DateToSec(Year,Month,0);
      tp:= Day;   td:= tm + tp*secDAY;
      tp:= Hour;  th:= td + tp*secHOUR;

      (*GetDirFiles(path,mask, Dir,Files);
      {if Files>0 then InfoCakaj(msgWAITING,msg_ARCHIV_CHECK);}
      for i:= 0 to Files-1 do
      *)

      FindFirst(path+mask,DataAttr,DirInfo);
      while DosError=0 do
        begin
          if isFileAttr (DirInfo,DataAttr) then
             begin
               ar:= false; fn:= path+{Dir^[i]^.name}DirInfo.Name;
               if archive_then<>nil then
                  begin
                    if decode_archived_date (fn,podla_mena, rr,mm,dd,hh) then
                       case archive_by of
                         by_hours  : ar:= th > DTtoSec(rr,mm,dd+archive_then^,hh,0,0);
                         by_days   : ar:= td > DateToSec(rr,mm,dd+archive_then^);
                         by_months : ar:= tm > DateToSec(rr,mm+archive_then^,0);
                       end
                    else ar:= true
                  end;
               if ar then
                  begin
                    if wr_archive and (not gm) then begin
                         x:= whereX; y:= whereY;
                         GoToXY(x+3,y); write('-> deleting ' + fn + '...')
                       end;
                    DelFile(fn);
                    if wr_archive and (not gm) then
                       begin
                         GoToXY(X,Y); ClrEol;
                         GoToXY(X,Y)
                       end
                  end;
             end;

          CheckProcesses0;
          FindNext(DirInfo)
        end;
      (*{if Files>0 then InfoCakaj_zatvor;}
      FreeDirFiles(Dir,Files);*)
      semaphor:= false
     {$ENDIF}
    end;


procedure archivuj_stare_plany;
    var   j : int;

    const semaphor: bool = false;

    begin
      if semaphor then Exit;
      semaphor:= true;

     { presun suborov s dennymi/mesacnymi planmi
       do archivacnych adresarov
     }
       for j:= 0 to max_data_dir-1 do with data_dir[j] do archivuj_subory (strpas(d),'*.*',strpas(a), true,t);

     { odmazanie suborov za periodou ArchDays archivacie
     }
       for j:= 0 to max_data_dir-1 do with data_dir[j] do uprac_archiv (strpas(a),'*.*', i, t,n);

     { odmazanie hodinovych nahravok
     }
       for j:= 0 to max_stream_dir-1 do with stream_dir[j] do uprac_archiv (strpas(d),'*.*', i, t,n);
       zmaz_stare_subory(pathTMP,'*.*',24{*ArchDays});

      ResetIOError;
      archiv_HODfn:= get_PLANfn(day,month,year)+'.'+IntToStr(hour,2,0);

      semaphor:= false
    end;


procedure zmaz_najstarsie_archivovane_subory;
    const semaphor: bool = false;
    var   i : int;
    begin
      if semaphor then Exit;
      semaphor:= true;
      for i:= 0 to max_stream_dir-1 do zmaz_najstarsi_subor(strpas(stream_dir[i].d),'*.*');
      ResetIOError;
      semaphor:= false
    end;
