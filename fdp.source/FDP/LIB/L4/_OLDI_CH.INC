procedure O_OLDI.check0;
    const smphr  : bool = false;
          power0 : bool = true;

    var   p    : pchar;
          data : pchars;
          len  : word;
          s    : string;

    label X;

    begin
{
      if (power0<>power) then power0:= power
      else if not power then Exit;
}

      { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
         0. prijem dat
        תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
      } inherited check0; { nacitanie dat, receive a potvrdenie }


      if smphr then Exit;
      smphr:= true;

      { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
         1. kontrola na stav X25
        תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
      }
        if {   (not power)
            or}(
                     (stat<>IDLE_STATE)
                {$IFDEF _X25}
                 and (X25_net<>nil)
                 and (OLDI_X25node_>-1)
                 and (X25nodes^.NODE^[OLDI_X25node_]^.chan=0)
                {$ENDIF}
               )
            then
               begin
                 if OLDI_X25node_=OLDI_X25nodeA then s:= X25adr_MASTER
                 else if OLDI_X25node_=OLDI_X25nodeB then s:= X25adr_MASTER
                 else s:= '?';
                 writeln_pkt(nil,0,arch_SYS,'X25 channel ('+s+') is not open...',cl_SYS,false,false);
                 handle_OLDI_event(X25_Error,nil);
                 goto X
               end;

        if (stat=READY_STATE) then handle_OLDI_event(L_Startup,nil);


      { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
         2. Testovanie na Tr,Ts
        תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
      } if (stat=CONNECTION_PENDING_STATE) and (TrTimeOut<>0) and (Tr_+TrTimeOut<=absTime) then
           handle_OLDI_event(Tr_TimeOut,nil);

        if (stat=DATA_READY_STATE) then
           if (Ts_+TsTimeOut<=absTime) then handle_OLDI_event(Ts_Timeout,nil)
           else if (TrTimeOut<>0) and (Tr_+TrTimeOut<=absTime) then
                   begin
                     { When an expected HeartBeat does not arrive within Tr,
                       the transmision of all messages is stopped and then X.25
                       connection is optionally cleared withoud sending a ShutDown
                       message. OLDI partner will recover and resynchronize
                       through the exchange of StartUp messages
                     }
                      {$IFNDEF DEBUG}
                       handle_OLDI_event(Tr_Timeout,nil)
                      {$ENDIF}
                   end;

      X: smphr:= false
    end;
