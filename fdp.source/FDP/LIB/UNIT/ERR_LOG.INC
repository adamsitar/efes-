{ Err.log
}

procedure _write_err_log(s: string);
    begin
      if cut_(s)='' then Exit;
      if @another_log_proc<>nil then another_log_proc(s);
      _another_line_err_log:= false
    end;

procedure write_err_log(s: string);
    var   t     : text;
          f1,f2 : file;
          s1    : string;
          NumRead, NumWritten : word;
    begin
     { IFNDEF DEBUG}
      if cut_(s)='' then Exit;

      ResetIOError;
      (*vytvor_novy_subor(err_log_cfg);
      if _filesize(err_log_cfg) > err_log_cfg_size*1024 then
         begin
           RenFile(err_log_cfg,'log.$$$');
           Assign (f1,'log.$$$'); Reset(f1,1);
           Assign (f2,err_log_cfg); Rewrite(f2,1);
           Seek(f1,FileSize(f1) div 2);
           repeat
             BlockRead (F1,s1,sizeof(s1)-1,NumRead);
             BlockWrite(F2,s1,NumRead,NumWritten);
           until (NumRead = 0) or (NumWritten<>NumRead);
           Close(f2);
           Close(f1);
           DelFile('log.$$$')
         end;
      zapis_text_do_subora(err_log_cfg,s);*)

      _write_err_log(s)
     { ENDIF}
    end;


var SaveExit : pointer;

procedure DoneApp;
    var   s: string;
    begin
      ResetIOError;
      s:= cstr(day,1)+'.'+cstr(month,1)+'.'+cstr(year,1)+', '+TimeToStr2(hour,min,sec,':','.');
      if ErrorAddr<>nil then s:=   'System crashed on '+s
                                 + ' with ' + WordToHex(ExitCode)
                                 + ' in ' + WordToHex(PtrRec(ErrorAddr).Seg)+':'+WordToHex(PtrRec(ErrorAddr).Ofs)
                                 + '...'
      else s:= 'System done on '+s+'.';
      write_err_log(s);
      write_err_log('');
      if ErrorAddr<>nil then
        {$IFNDEF DEBUG}
         begin
         end
        {$ENDIF};
      ExitProc:= SaveExit
    end;
