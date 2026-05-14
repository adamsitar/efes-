(*-------------------------------------------------------------------*)
(* LETVIS FDP - generovanie hlaseni 3.0                              *)
(* (c) Ales Kosice 1993,5,9  (ab)                                    *)
(*-------------------------------------------------------------------*)
{$I comp.h}


unit FDP_rep;


interface


     uses   TypeDef,
            Report,
            _l4_def, _FDP_def;


     { I FDP_rep.h}      { docasne v _FDP_def }


implementation

 uses  BIOS, _Check, mem, str0, utime, math, io, mess, msg,
       {$I unit_gr.h},
       help_def, CMs, Events, Dialog,
       Kody, NET_def, _NET,
       {$I unit_fdp.h}
       _SSR, Status;


{$I _rep_fdp.inc}
{$I _rep_ssr.inc}

 var  SaveExit: pointer;
      SaveMainC, SaveMainD: TProc;


 procedure REP_done; far;
     begin
       {$IFDEF SSR_MANAGEMENT}
        if reports_SSR<>nil then Dispose(reports_SSR);
       {$ENDIF}

       {$IFDEF SPR}
        if reports_SPR<>nil then Dispose(reports_SPR);
       {$ENDIF}

       if reports_FDP<>nil then Dispose(reports_FDP);

       ExitProc:= SaveExit
     end;


 procedure REP_checkC; far;
     begin
      if @SaveMainC<>nil then SaveMainC;

      {$IFDEF SSR_MANAGEMENT}
       reports_SSR^.check;
      {$ENDIF}

      {$IFDEF SPR}
       reports_SPR^.check;
      {$ENDIF}
     end;


 procedure REP_checkD; far;
     begin
       if @SaveMainD<>nil then SaveMainD;

       reports_FDP^.check;
     end;


 procedure REP_init;
     begin
       reports_FDP:= New(POREP,Init(namREP,extREP, @process_report_FDP));

       {$IFDEF SPR}
        reports_SPR:= New(POREP,Init(namSPR,extSPR, @process_report_SPR));
       {$ENDIF}

       {$IFDEF SSR_MANAGEMENT}
        reports_SSR:= New(POREP,Init(namSSR,extSSR, @process_report_SSR));
       {$ENDIF}

       SaveExit:= ExitProc;
       ExitProc:= @REP_done;

       SaveMainC:= ACheckProcessesC;
       ACheckProcessesC:= REP_checkC;

       SaveMainD:= ACheckProcessesD;
       ACheckProcessesD:= REP_checkD
     end;

begin
  REP_init
end.