{$I comp.h}

{uses {ovr, bios, typedef, math, str0,crt,}

var  w: word;
     s: string;

begin
 w:= 1;
 move(w,s[1],sizeof(word)); s[0]:= chr(sizeof(word));
end.
