procedure X25_detect;
    var  _err: bool;
    begin
      _err:= false;
      X25nodes:= New(PO_X25nodes,Init);
      X25nodes^.read_cfg(_err);
      if _err then writeln
    end;

procedure X25_init;
    var   res: string;
    begin
     {$IFDEF _X25}
       write('Initializing Xú25... ');
       X25_net:= New(P_X25net, Init);
       {$IFNDEF _X25_NOINIT}
        if X25_net^.CONNECTED then
           begin
             writeln('Done. Connected to Xú25. ');
            {$IFNDEF DEBUG} Delay(2000) {$ENDIF}
           end
        {else res:= 'Cannot connect to Xú25... '#7}
       {$ENDIF};
       { nadviazanie spojenia so vsetkymi stanicami }
       X25_Net^.OPEN_SVCs;
       X25_installed:= true;
       X25_initialized:= true;
     {$ELSE}
       X25_installed:= false
     {$ENDIF}
    end; { X25_Init }


procedure X25_done;
    var   i: int;
    begin
     {$IFDEF DEBUG_EXIT} writeln('X25'); {$ENDIF}

     {$IFDEF _X25}
       if X25_installed then {X25_Net^.CLOSE_SVCs;} Dispose(X25_Net,Done);
     {$ENDIF}
      if X25nodes<>nil then Dispose(X25nodes,Done);

      ExitProc:= SaveExit
    end; { X25_Done }

