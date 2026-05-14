(*-------------------------------------------------------------------*)
(* Ovladac klavesnice intr 1.0                                       *)
(* 1993,94                                                           *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$X+,I-,S-,P-,F+,O-}
{$C FIXED PRELOAD PERMANENT}

unit keyb_int;


interface

    procedure kb_clear;


implementation

uses Typedef, Dos;

{ Nuluje buffer klavesnice.
}
procedure kb_clear;
    var   Reg: Registers;
    begin
      Reg.AH := $0C;
      Reg.AL := $06;
      Reg.DL := $FF;
      asm cli end;
      MsDos(Reg);
      asm sti end;
    end;


var  OldKeyHandle: procedure;

procedure NewKeyHandle; interrupt;
    const count : byte = 0;
    var   pom   : byte;
    begin
      asm
        in al,60h
        mov pom,al
      end;
      if (count=0) and (pom=$e1) then count:= 6;    { Break stlacene }
      if count>0 then
         begin
           dec(count);
           asm
              in al,61h    {daj do AL stav portu}
              mov ah,al    {uchovaj ho v AH}
              or al,80h    {nastav bit spristupnenia klavesnice}
              out 61h,al   {vysli ho na port}
              xchg ah,al   {vezmi povodnu hodnotu portu}
              out 61h,al   {a nastav ju spat}
              mov al,20h   {tu je vyslanie          }
              out 20h,al   {signalu konca prerusenia}
           end;
         end
      else asm
             pushf
             call OldKeyHandle
           end
    end;

var SaveExit: pointer;

procedure keyb_done;
    begin
     {$IFDEF DEBUG_EXIT} writeln('KEYB'); {$ENDIF}
      SetIntVec($09,@OldKeyHandle);
      ExitProc:= SaveExit
    end;

begin
 {$IFNDEF DEBUG}
   SaveExit:= ExitProc;
   ExitProc:= @keyb_done;
   GetIntVec($09,@OldKeyHandle);
   SetIntVec($09,@NewKeyHandle);
 {$ENDIF}
end.
