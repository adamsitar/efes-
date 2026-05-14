{*********************************************************}
{*                    Turbo Pascal 6.0                   *}
{*              CrtII - Crt expanding unit               *}
{*               Copyright (c) Arnie 1991                *}
{*********************************************************}

{$O+}

unit CrtII;

interface

     uses  TypeDef;

     procedure WriteWin(var Buf);
     procedure ReadWin(var Buf);
     function  WinSize: Word;


implementation

uses DOS, Crt;

var  Reg: Registers;

{$F+}
procedure WriteStr(X,Y: byte; S: String; Attr: byte); external;
procedure WriteChar(X,Y,Count: byte; Ch: Char; Attr: Byte); external;
procedure FillWin(Ch: Char; Attr: byte); external;
procedure WriteWin(var Buf); external;
procedure ReadWin(var Buf); external;
function  WinSize: Word; external;
{$L WIN.OBJ}
{$F-}

end. { CrtII }
