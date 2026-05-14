(*-------------------------------------------------------------------*)
(*                                                                   *)
(*  BGI Graph unit                                                   *)
(*                                                                   *)
(*-------------------------------------------------------------------*)
{$I comp.h}

unit mess;


interface


    uses   Typedef;

    const  waitSPRAVA    : int  = {$IFDEF DEBUG} 10 {$ELSE} 90 {$ENDIF};  { pocet sekund pre okno s poslednou spravou }
           waitBEEP      : int  = {$IFDEF DEBUG} 1  {$ELSE} 10 {$ENDIF};  { zapipa pri prijme spravy }

           ALARM         : bool = true;   { bordel pri prichode spravy }
           ExitMessage   : string = '';


    function  BeepErr : bool;
    function  Beep1   : bool;
    function  Beep2   : bool;
    function  Beep3   : bool;
    function  Beep4   : bool;
    function  Beep5   : bool;

    function  Beep99  : bool;
    function  Beep999(PBFunc_p,par: pointer): bool;
    function  BeepVB (PBFunc_p,par: pointer; start_tick, loops: long; _beep: byte): bool;

    procedure RunError (mess: string);
    procedure MessError(mess: string; wait: bool; var nl: bool);


implementation

uses  Crt, IO, BIOS, _Check, str0, keyb, keyb_int, mouse,
     {$IFDEF BGI} Graph {$ELSE} Graphs {$ENDIF},
      BGIgraph, SVGA;


const evNothing = 0;
      evTimeOut = 1;
      evKey     = 2;
      evBF      = 4;


function BeepErr: bool;
   begin
     BeepErr:= false;
    {$IFNDEF DEBUG}
     Beep(155,172{344});
     Beep(125,172{344});
     Beep(75,500{1000});
    {$ENDIF}
   end; { Err }


function Beep1: bool;
   begin
     Beep1:= false;
     Beep(300,60{120});
     Beep(600,30{60});
     Beep(900,20{40});
   end; { Acc }


function Beep2: bool;
   begin
     Beep2:= false;
     Beep(25,1200);
   end;


function Beep3: bool;
   begin
     Beep3:= false;
     if not ZVUK then Exit;
     Beep(500,70);
     Delay(5);
     Beep(800,50);
     Delay(50);
     Beep(2000,40);
   end;


function Beep4: bool;
   begin
     if not ZVUK then Exit;
     Sound(700); Delay(70);  NoSound;
     Delay(30);  Sound(700); Delay(70); NoSound;
     Beep4:= false
   end;


function Beep5: bool;
   var   i: int;
   begin
     Beep5:= false;
     for i:= 3 to 8 do Beep(100 + 50*i,50)
   end;


function Stop(PBFunc_p,par: pointer; start_tick, loops: long): byte;
   begin
     if   ((PBFunc_p<>nil) and (TBFunc_p(PBFunc_p)(par))) then Stop:= evBF
     else if (kbhit) or (m_hit) then Stop:= evKey
     else if (TimeOut(start_tick, getticks, loops)) then Stop:= evTimeOut
     else Stop:= evNothing
   end;

function BeepVB(PBFunc_p,par: pointer; start_tick, loops: long; _beep: byte): bool;
   const MinF = 550;
         MaxF = 1440;
         P    : array[0..3] of word = (4,2,36,50);

   var   count: byte;
         F    : word;
         S,i,j: int;
         C    : bool;
         SPEED: byte;
         res  : byte;
   label endp;

   begin
     BeepVB:= true;
     if not ZVUK then Exit;

     if _486=1 then SPEED:= 1 else SPEED:= 2;
     for count:= 1 to _beep do
         begin
           for i:= 1 to 5 do
               begin
                 Beep(100,100 div SPEED);
                 res:= Stop(PBFunc_p,par, start_tick,loops);
                 if res<>evNothing then goto endp;
                 Delay(100 div SPEED);
                 CheckProcesses
               end;
           for j:= 1 to 20 do
               begin
                 res:= Stop(PBFunc_p,par, start_tick, loops);
                 if res<>evNothing then goto endp;
                 Delay(100 div SPEED);
                 CheckProcesses
               end;
         end;

     F:= MinF; C:= false;
     repeat
       S:= P[byte(C)*2+1];
       for i:= 1 to P[byte(C)*2] do
           begin
             S:= -S;
             repeat
               Sound(F); Delay(5 div SPEED);
               F:= F+S;
               res:= Stop(PBFunc_p,par, start_tick, loops);
               if res<>evNothing then goto endp;
             until (F < MinF) or (F > MaxF);
             CheckProcesses
           end;
       C:= not C;
       res:= Stop(PBFunc_p,par, start_tick, loops)
     until res<>evNothing;

     endp: BeepVB:= res=evBF;
           NoSound;
           kb_clear
   end; { BeepVB }


function Beep99: bool;
   var   b: bool;
         r: long;
   begin
     (*{$IFNDEF NO_SOUND} b:= ZVUK; ZVUK:= true; {$ENDIF}*)
     r:= waitSPRAVA; r:= r*18;
     if ALARM then Beep99:= BeepVB(nil,nil, GetTicks, r, waitBEEP)
     else Beep99:= Beep1;
     (*{$IFNDEF NO_SOUND} ZVUK:= b {$ENDIF}*)
   end;

function Beep999(PBFunc_p,par: pointer): bool;
   var   b: bool;
         r: long;
   begin
     (*{$IFNDEF NO_SOUND} b:= ZVUK; ZVUK:= true; {$ENDIF}*)
     r:= waitSPRAVA; r:= r*18;
     if ALARM then Beep999:= BeepVB(PBFunc_p,par, GetTicks, r, waitBEEP)
     else Beep999:= Beep1;
     (*{$IFNDEF NO_SOUND} ZVUK:= b {$ENDIF}*)
   end;


{
  chyby je mozne zapisovat do subora err.log
}

procedure RunError(mess: string);
    begin
      ResetIOError;
      ProgramError:= true;
      write_err_log(mess);
      mess:= #13#10#13#10{$IFNDEF DEBUG}+#7{$ENDIF}{'Program aborted:  '+}+mess+{$IFNDEF DEBUG}#7+{$ENDIF}#13#10;
      if (InGraphMode) then ExitMessage:= mess
      else writeln(mess);
      if InGraphMode then begin CloseGraph; GotoXY(1,22) end;
      {writeln(ExitMessage);}
      Halt(1)
    end; { RunError }


procedure MessError(mess: string; wait: bool; var nl: bool);
    begin
      write_err_log(mess);
      if InGraphMode then WriteStr(10,GetMaxY-30, mess, lightgray, black)
      else begin
             {if (not InGraphMode) and NL then writeln;}
             write(kbNL+{$IFNDEF DEBUG} {$IFNDEF DEMO} #7,{$ENDIF} {$ENDIF} mess);
           end;
      if wait then {getkey
      else} begin
              kb_clear;
              ReadKey(18*3, no_action);
            end;
      kb_clear;
      {if (not InGraphMode) then writeln;}
      nl:= true
    end; { MessError }


{
procedure vrtula;
    const vrtulka : array[0..4] of char = ('|','/','-','\');
          i: int = 0;
    begin
      write(vrtulka[i]);
      i:= (i+1) mod sizeof*(vrtulka)
    end;
}

begin
  writeln
end. { mess }