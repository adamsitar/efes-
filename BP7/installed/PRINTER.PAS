
{*******************************************************}
{                                                       }
{       Turbo Pascal Runtime Library                    }
{       Printer Interface Unit                          }
{                                                       }
{       Copyright (C) 1988,92 Borland International     }
{                                                       }
{*******************************************************}

unit Printer;

{$I-,S-}

interface

var
  Lst: Text;

implementation

procedure LstBinaryMode;
inline(
  $8B/$1E/Lst/        { MOV   BX,Lst.Handle }
  $B8/$00/$44/        { MOV   AX,4400H      }
  $CD/$21/            { INT   21H           }
  $80/$CA/$20/        { OR    DL,20H        }
  $B6/$00/            { MOV   DH,0          }
  $B8/$01/$44/        { MOV   AX,4401H      }
  $CD/$21);           { INT   21H           }

begin
  Assign(Lst,'LPT1');
  Rewrite(Lst);
  LstBinaryMode;
end.
