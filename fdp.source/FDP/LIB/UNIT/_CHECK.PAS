(*-------------------------------------------------------------------*)
(* zabezpecenie neustale beziacich uloh                              *)
(* 1993                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-,F+,O-}
{$C FIXED PRELOAD PERMANENT}


unit _Check;


interface


    uses   Typedef;

    var    TickCounter : tick_counter;

    const  { Zahodno vymysliet, aby sa do MainProgramu dali
             vkladat, zretazovat a vyberat volania...
             Teraz si adresu povodneho Mainu pamata kazdy instalujuci
             modul, diagnose moze byt len jeden
           }

           MainEnabled  : bool  = false;
           MainEnabledD : int   = 0;

           ACheckProcesses0   : TProc = nil;   { hlavna cinnost programu, vykonavana neustale }
           ACheckProcessesA   : TProc = nil;
           ACheckProcessesC   : TProc = nil;
           ACheckProcessesD   : TProc = nil;   { spracovanie dat, semafory sa riesia lokalne }

           ADaemon   : Tproc = nil;
           ADiagnose : TProc = nil;


    procedure  CheckProcesses0;   far;
    {procedure  CheckProcessesA;   far;
    procedure  CheckProcessesC;   far;
    procedure  CheckProcessesD;   far;}

    procedure  CheckProcesses;    far;

    procedure  Diagnose;



implementation

uses DOS, BIOS;

const  cit_0: long = 0;
       cit_A: long = 0;
       cit_C: long = 0;

procedure CheckProcesses0;
    begin
      if MainEnabled then
         begin
           inc(cit_0);
           if (@ACheckProcesses0 <> nil) then ACheckProcesses0;
           dec(cit_0);
         end;
    end;

procedure CheckProcessesA;
    begin
      if MainEnabled then
         begin
           CheckProcesses0;
           inc(cit_A);
           if (@ACheckProcessesA <> nil) then ACheckProcessesA;
           if (@ADiagnose <> nil) then ADiagnose;
           dec(cit_A);
         end;
    end;

procedure CheckProcessesC;
    begin
      if MainEnabled then
         begin
           inc(cit_C);
           if (@ACheckProcessesC <> nil) then ACheckProcessesC;
           dec(cit_C);
         end;
    end;

procedure CheckProcessesD;
    begin
      if MainEnabled and (cit_0=0) and (cit_A=0) then
         begin
           if (@ACheckProcessesD<>nil) then ACheckProcessesD
         end;
    end;

procedure CheckProcesses;
    begin
      if MainEnabled then
         begin
           {if (@Demon <> nil) then Demon;}
           CheckProcesses0;
           CheckProcessesA;
           if MainEnabledD=0 then
              begin
                CheckProcessesC;
                CheckProcessesD
              end
         end;
    end;

procedure Diagnose;
    begin
      if (@ADiagnose <> nil) then ADiagnose
    end;


const TimerIntVect:Byte = $1C;

var   OldTimeHandler : procedure;
      SaveExit       : pointer;

(*
{ prerusovacia procedura,
  vola povodnu systemovu proceduru
}
procedure TimerHandler; assembler;
    asm
                            { pushf - simulate an INT         }
          call  Int08Save   { perform normal timer activities } {dword ptr}
          call  TimerProc
    end;
*)

procedure TimeHandler; interrupt;
    begin
      Inc(TickCounter);
    end;

procedure RestoreTimeHandler; far;
    begin
      SetIntVec(TimerIntVect,@OldTimeHandler);
      ExitProc:= SaveExit
    end;

procedure SetTimeHandler;
    begin
      GetIntVec(TimerIntVect,@OldTimeHandler);
      SetIntVec(TimerIntVect,@TimeHandler);
      saveexit:= exitproc;
      exitproc:= @RestoreTimeHandler
    end;

begin
  TickCounter := 0;
  SetTimeHandler;
end.