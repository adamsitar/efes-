procedure SetBound(S: string; var _lo,_hi: int; pos: byte; SkipSet: TCharSet);
   var    i,j: int;

   procedure Set_lo;
       begin
         while (i<=Length(S)) and (S[i] in SkipSet) do Inc(i);
         (*if {not ((S[i] in SkipSet) and} (i<=Length(S))
            then*) _lo:= i
            (*else _lo:= Length(S)*)
       end; { Set_lo }

   procedure Set_hi;
       begin
         while (i<=Length(S)) and (not(S[i] in SkipSet)) do Inc(i);
         if (i<=Length(S)) and (S[i] in SkipSet)
            then _hi:= i-1
            else _hi:= Length(S)
       end; { Set_hi }

    begin
      i:= 1;
      if not (S[i] in SkipSet) then _lo:= i
      else Set_lo;
      Set_hi;
      for j:= 2 to pos do
        begin
          Set_lo;
          Set_hi
        end
    end; { SetBound }

procedure SetPBound(S: PChar; var _lo,_hi: int; pos: byte; SkipSet: TCharSet);
    {var   __lo,__hi: int;}
    begin
     {__lo := _lo+1; __hi := _hi+1;}
      SetBound(StrPas(S),_lo,_hi, pos, SkipSet);
      Dec(_lo);
      Dec(_hi);
    end;


{
 vrati pocet poloziek v stringu s
}
function GetStrItems(S: string; SkipSet: TCharSet): byte;
   var   i: int;
   begin
     i:= 0;
     while (i<(sizeof(s)-1)) and (GetStr(S,i+1,SkipSet)<>'') do inc(i);
     GetStrItems:= i
   end;

{
 formular -> polozka string
}
function GetStr(S: string; pos: byte; SkipSet: TCharSet): string;
   var   _lo,_hi: int;
   begin
     SetBound(S,_lo,_hi,pos,SkipSet);
     GetStr:= Copy(S,_lo,N(_hi-_lo+1))
   end; { GetStr }

function GetStr_(S: string; pos: byte; SkipSet: TCharSet; max_size: byte): string;
   begin
     s:= GetStr(s,pos,SkipSet);
     if length(s)>max_size then s[0]:= chr(max_size);
     GetStr_:= s
   end; { GetStr_ }

function gesstr_c(S: string; pos: byte; SkipSet: TCharSet): string;
   begin
   end;


{
  longint -> string
}
function WGetInt(var Cislo: long; S: string; pos: byte; SkipSet: TCharSet): bool;
  var    I: long;
         R: int;
  begin
    S:= DelChar(GetStr(S,pos,SkipSet),[' ']);
    Val(S,Cislo,R);
    WGetInt:= R=0
  end; { WGetInt }

{
  longint -> string
}
function GetInt(S: string; pos: byte; SkipSet: TCharSet): long;
   var   Cislo: long;
   begin
     if WGetInt(Cislo,S,Pos,SkipSet) then GetInt:= Cislo
     else GetInt:= 0
   end; { GetInt }



{
 string -> longint
}
function IntToStr(Cislo: long; sirka: byte; nula: byte): string;
  var    S: string;
  begin
    Str(Cislo:sirka,S);
    if nula=0 then S:= InsChar(DelChar(S,[' ']),sirka,'0',0)
    else if (cislo=0) and (nula=$FF) then S:= InsChar(' ',sirka,' ',0);
    IntToStr:= S
  end; { IntToStr }


const  hexchar: array [1..16] of char = '0123456789ABCDEF';

function  WordToHex(hex: word): string;
   var    h1, h2 : word;
   begin
     h1 := hex div 256; h2 := hex mod 256;
     WordToHex := '$' + hexchar[ ord(h1) div 16 + 1] + hexchar[ ord(h1) mod 16 + 1]
                      + hexchar[ ord(h2) div 16 + 1] + hexchar[ ord(h2) mod 16 + 1]
   end;

function  ByteToHex(hex: byte): string;
   begin
     ByteToHex:= '$' + hexchar[ ord(hex) div 16 + 1] + hexchar[ ord(hex) mod 16 + 1]
   end;
