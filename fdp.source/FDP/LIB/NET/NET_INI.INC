procedure NET_done; far;
    var   i: int;
    begin
      if NET<>nil then Dispose(NET,Done);
      NETcfg_done;

      ExitProc:= SaveExit
    end;


procedure NET_init(_NET: PNET);
    begin
     {$IFNDEF NET}
       Exit;
     {$ENDIF}

      NET:= _NET;
      NETcfg_read;

      {$IFDEF IPX}
       IPX_init;   { Musi byt za NETcfg_read ! }
      {$ENDIF}

      {$IFDEF UDP}
       UDP_init;
      {$ENDIF}

      {$IFDEF _X25}
       X25_init;
      {$ENDIF}

      {$IFDEF COM}
       COM_init;
      {$ENDIF}

      SaveMain0 := ACheckProcesses0;
      ACheckProcesses0 := NET_check0;

      SaveMainA := ACheckProcessesA;
      ACheckProcessesA := NET_checkA;

      SaveMainD := ACheckProcessesD;
      ACheckProcessesD := NET_checkD;

      SaveExit  := ExitProc;
      ExitProc  := @NET_done
    end;
