Unit Basic;

{
   translated from C++ definition module basic.h

   basic universal functions & definitions

   Copyright (c) Rastislav B”hmer, 1994

}

INTERFACE

Uses Crt,Str0,Objects,Types;

procedure SetBit(var Where:bit_mask; Which:bit_mask);
procedure ClearBit(var Where:bit_mask; Which:bit_mask);
procedure InvertBit(var Where:bit_mask; Which:bit_mask);

function IsSet(Where:bit_mask; Which:bit_mask) :logic;
function IsntSet(Where:bit_mask; Which:bit_mask) :logic;
function HasOne(Where:bit_mask; Which:bit_mask) :logic;
function HasZero(Where:bit_mask; Which:bit_mask) :logic;

function IsAlpha(c:char) :logic;
procedure ToUpper(var Text:String);

procedure Beep(SoundVal,Length :uint);
procedure ErrorSound;
procedure MiddleSound;
procedure LowSound;

IMPLEMENTATION

procedure SetBit(var Where:bit_mask; Which:bit_mask);
begin
Where := Where or Which;
end;

procedure ClearBit(var Where:bit_mask; Which:bit_mask);
begin
Where := Where and (not Which);
end;

procedure InvertBit(var Where:bit_mask; Which:bit_mask);
begin
Where := Where xor Which;
end;


function IsSet(Where:bit_mask; Which:bit_mask) :logic;
begin
if (Where and Which)=Which then
  IsSet:=YES
else
  IsSet:=NO;
end;

function IsntSet(Where:bit_mask; Which:bit_mask) :logic;
begin
if (Where and Which)=Which then
  IsntSet:=NO
else
  IsntSet:=YES;
end;

function HasOne(Where:bit_mask; Which:bit_mask) :logic;
begin
if (Where and Which)<>0 then
  HasOne:=YES
else
  HasOne:=NO;
end;

function HasZero(Where:bit_mask; Which:bit_mask) :logic;
begin
if (Where and Which)<>0 then
  HasZero:=NO
else
  HasZero:=YES;
end;

function IsAlpha(c:char) :logic;
begin
  if ((c>='A') and (c<='Z'))  or  ((c>='a') and (c<='z')) then
    IsAlpha:=YES
  else
    IsAlpha:=NO;
end;

procedure ToUpper(var Text:String);
var
  TmpStr :PChar;
begin
GetMem(TmpStr,Length(Text)+1);
StrPCopy(TmpStr,Text);
StrUpper(TmpStr);
Text:=StrPas(TmpStr);
Dispose(TmpStr);
end;

procedure Beep(SoundVal,Length :uint);
begin
sound(SoundVal); delay(Length); nosound;
end;

procedure ErrorSound;
begin
Beep(500,10);
end;

procedure MiddleSound;
begin
Beep(400,20);
end;

procedure LowSound;
begin
Beep(200,30);
end;

BEGIN
END.