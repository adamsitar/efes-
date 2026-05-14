function CenterStr(S: string; wide: byte): string;
   var  l,x: byte;
   begin
     l:= Length(s);
     x:= (wide-l) shr 1;
     CenterStr:= InsChar(InsChar(s,x+l+1,' ',0),wide+1,' ',1)
   end; { CenterStr }


function UpString(S: string): string;
   var   i: int;
   begin
     for i:= 1 to Length(S) do S[i]:= UpCase(S[i]);
     UpString:= S
   end; { UpString }


{ zmaze znaky z mnoziny DelSet so stringu S
}
function DelChar(S: string; DelSet: TCharSet): string;
   var   i: int;
   begin
     i:= 1;
     while (Length(S)<>0) and (i<=Length(S)) do
       begin
         if S[i] in DelSet then Delete(S,i,1)
         else Inc(i)
       end;
     DelChar:= S
   end; { DelChar }


{ zmaze inych znakov ako z mnoziny EnSet so stringu S
}
function DelCharN(S: string; EnSet: TCharSet): string;
   var   i: int;
   begin
     i:= 1;
     while (Length(S)<>0) and (i<=Length(S)) do
       begin
         if not (S[i] in EnSet) then Delete(S,i,1)
         else Inc(i)
       end;
     DelCharN:= S
   end; { DelCharN }


function  cut_(S: string): string;
   var   i: int;
   begin
     i:= 1;
     while (Length(S)<>0) and (S[1]=' ') do S:= Copy(S,2,Length(S)-1);
     while (Length(S)<>0) and (S[Length(S)]=' ') do S[0]:= chr(ord(S[0])-1);
     cut_:= S
   end; { cut_ }


function  cut_r(S: string): string;
   var   i: int;
   begin
     i:= 1;
     while (Length(S)<>0) and (S[Length(S)]=' ') do S[0]:= chr(ord(S[0])-1);
     cut_r:= S
   end; { cut_r }


function  cut_r0(S: string): string;    { sprava odreze 0 }
   var   i: int;
   begin
     i:= 1;
     while (Length(S)<>0) and (S[Length(S)]='0') do S[0]:= chr(ord(S[0])-1);
     cut_r0:= S
   end; { cut_r0 }


function cut_str(Substr: String; S: String): string;
   var   i,c: int;
   begin
     i:= Pos(Substr,S);
     if i>0 then S:= copy(S,1,i-1)+copy(S,i+length(SubStr),length(S)-length(SubStr)-i+1);
     cut_str:= S
   end;


function cut_3(s: string; size: int): string;
   begin
     if length(s)>size then s:= copy(s,1,N(size-3))+'...';
     cut_3:= s
   end;
