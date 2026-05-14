{$I comp.h}

unit ovr;

interface


    {$I program.h}

    const size_ovr_buff = $FFFF;

        { neodalokuje pouzity heap }


implementation

{$IFDEF _OVR}

 uses  Overlay;


 { var   SaveOvrRead: OvrReadFunc;

   function MyOvrRead(OvrSeg: word): integer; far;
      var   E: integer;
      begin
        repeat
          E:= SaveOvr(OVrSeg);
          if E<>0 then ... vid s 253
        until E = 0;
        MyOvrRead:= 0
      end;

 }



 var  SaveExit: pointer;

 procedure done_ovr; far;
     begin
      {$IFDEF DEBUG_EXIT} writeln('OVR'); {$ENDIF}
       OvrSetBuf(0);
       ExitProc:= SaveExit
     end;

 procedure init_ovr;
     var   buf: longint;
     begin
       writeln;

       OvrInit(path_exe+exe+'.ovr');
       OvrInitEMS;
       if OvrResult<>ovrOk then
          if (OvrResult=ovrNoEMSDriver) or (OvrResult=ovrNoEMSMemory) then
             begin
               writeln({$IFNDEF DEBUG}#7,{$ENDIF}'EMS is not available.')
             end
          else begin
                 writeln('Overlay manager error (',ovrresult,').');
                 Halt(1)
               end
        else writeln('Overlay loaded in to EMS.');

       {$IFDEF DEBUG} buf:=  OvrGetBuf; buf:=  OvrGetRetry; {$ENDIF}
       {IFNDEF SERVER}
        OvrSetBuf(size_ovr_buff);
        OvrSetRetry($1000);
       {ENDIF}
       {$IFDEF DEBUG} buf:=  OvrGetBuf; buf:=  OvrGetRetry; {$ENDIF}

       writeln('Overlay manager installed (',ovrresult,').');
       SaveExit := ExitProc;
       ExitProc := @done_ovr
     end;


 begin
  init_ovr
{$ENDIF}
end.


