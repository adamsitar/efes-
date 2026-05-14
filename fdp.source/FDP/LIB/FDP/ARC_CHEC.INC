procedure kontroluj_miesto_HDD;
    var   i,j: longint;
    begin
     {$IFNDEF DD_EXE}
      if DiskFree(0) < MIN_SPACE_HDD then
         begin
           zmaz_najstarsie_archivovane_subory;
           CheckProcesses0
         end
     {$ENDIF}
    end;


var  SaveMain : TProc;

procedure _check_archiv(msg: bool); far;
    const hh : byte = 25;
          mm : byte = 60;
    begin
      if (hh <> hour) then
         begin
           {$IFDEF ARCHIVE_PROGRAM_ERR}
            _write_err_log('Archives checking...');
           {$ENDIF}
           hh:= hour;
           archivuj_stare_plany;
           {$IFDEF ARCHIVE_PROGRAM_ERR}
            _write_err_log('Archives checked.');
           {$ENDIF}
         end;
      if (mm <> min) then
         begin
           mm:= min;
           kontroluj_miesto_HDD
         end;
    end;

procedure check_archiv; {far;}
    const semaphor: bool = false;
          hh: byte = 25;
          mm: byte = 60;
    begin
      if @SaveMain<>nil then SaveMain;
      if semaphor then Exit;

      semaphor:= true;
      _check_archiv(false);
      semaphor:= false
    end;
