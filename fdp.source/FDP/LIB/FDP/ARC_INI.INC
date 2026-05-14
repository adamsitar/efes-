procedure init_archiv;
    var   i, d,m: int;
    begin
      write('Checking directories... ');
      wr_archive:= true;

      d:= ArchDays;
      ArchDays:= Limit(read_cfg_word(SYSTEMcfg,cfg_ArchDays,ArchDays),lo_ArchDays,hi_ArchDays,0);
      m:= ArchMonths;
      ArchMonths:= Limit(read_cfg_word(SYSTEMcfg,cfg_ArchMonths,ArchMonths),lo_ArchMonths,hi_ArchMonths,0);
      is_cfgArch:= (d<>ArchDays) or (m<>ArchMonths);

     {$IFDEF ARCHIVE_NET}
      archdaysNET := Limit(read_cfg_word(SYSTEMcfg,cfg_archdaysNET,archdaysNET),lo_archdaysNET,hi_archdaysNET,0);
     {$ENDIF}

     {$IFDEF ARCHIVE_OPL}
      archdaysOPL := Limit(read_cfg_word(SYSTEMcfg,cfg_archdaysOPL,archdaysOPL),lo_archdaysOPL,hi_archdaysOPL,0);
     {$ENDIF}

     {$IFDEF ARCHIVE_CAMUS}
      archdaysCAMUS := Limit(read_cfg_word(SYSTEMcfg,cfg_archdaysCAMUS,archdaysCAMUS),lo_archdaysCAMUS,hi_archdaysCAMUS,0);
     {$ENDIF}

      for i:= 0 to max_stream_dir-1 do _mkdir(StrPas(stream_dir[i].d));
      for i:= 0 to max_data_dir-1 do
          begin
            _mkdir(StrPas(data_dir[i].d));
            _mkdir(StrPas(data_dir[i].a))
          end;

      SaveMain:= nil;
      check_archiv;

      SaveMain:= ACheckProcessesA;
      ACheckProcessesA:= check_archiv;

      wr_archive:= false;
      writeln('Done.');

     { IFDEF ARCHIVE_COM}
       archivuj_cmn(' ');
       archivuj_cmn('System initialized on '
                    +cstr(day,1)+'.'+cstr(month,1)+'.'+cstr(year,1)+', '+TimeToStr2(hour,min,sec,':','.')
                   );
       IO.another_log_proc:= archivuj_cmn;
     { ENDIF}
    end;
