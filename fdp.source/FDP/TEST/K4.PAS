uses crt;

var i: string;
    ch: char;

begin

{repeat Ch := GetChar until Ch <> ' ';}

repeat
  Write('Enter value: ');
  ReadLn(I);
until (I >= '0') and (I <= '9');


end.