
function cs_ascii_char(ch: char): char;
   begin
    {$IFNDEF A36YKA}
     case ch of
       '†','è'  : ch:= 'A';
       'á','Ä'  : ch:= 'C';
       'É','Ö'  : ch:= 'D';
       'Ç','ê',
       'à','â'  : ch:= 'E';
       '°','ã'  : ch:= 'I';
       'ç','ä',
       'å','ú'  : ch:= 'L';
       '§','•'  : ch:= 'N';
       '¢','ï',
       'ì','ß'  : ch:= 'O';
       '™','´',
       '©','û'  : ch:= 'R';
       '®','õ'  : ch:= 'S';
       'ü','Ü'  : ch:= 'T';
       '£','ó',
       'ñ','¶'  : ch:= 'U';
       'ò','ù'  : ch:= 'Y';
       'ë','í'  : ch:= 'Z';
       else ch:= upcase(ch)
     end;
     {$ELSE}
       ch:= upcase(ch);
     {$ENDIF}
     cs_ascii_char:= ch
   end;

function cs_ascii_char2(ch: char): char;
   begin
    {$IFNDEF A36YKA}
     case ch of
       '†'     : ch:= 'a';
       'è'     : ch:= 'A';
       'á'     : ch:= 'c';
       'Ä'     : ch:= 'C';
       'É'     : ch:= 'd';
       'Ö'     : ch:= 'D';
       'Ç','à' : ch:= 'e';
       'â','ê' : ch:= 'E';
       '°'     : ch:= 'i';
       'ã'     : ch:= 'I';
       'ç','å' : ch:= 'l';
       'ä','ú' : ch:= 'L';
       '§'     : ch:= 'n';
       '•'     : ch:= 'N';
       '¢','ì' : ch:= 'o';
       'ï','ß' : ch:= 'O';
       '™','©' : ch:= 'r';
       '´','û' : ch:= 'R';
       '®'     : ch:= 's';
       'õ'     : ch:= 'S';
       'ü'     : ch:= 't';
       'Ü'     : ch:= 'T';
       '£','ñ' : ch:= 'u';
       'ó','¶' : ch:= 'U';
       'ò'     : ch:= 'y';
       'ù'     : ch:= 'Y';
       'ë'     : ch:= 'z';
       'í'     : ch:= 'Z'
     end;
     {$ELSE}
       ch:= upcase(ch);
     {$ENDIF}
     cs_ascii_char2:= ch
   end;

function cs_ascii_str(s: string): string;
   var   i: int;
   begin
     for i:= 1 to length(s) do s[i]:= cs_ascii_char(s[i]);
     cs_ascii_str:= s
   end;

function cs_ascii_str2(s: string): string;
   var   i: int;
   begin
     for i:= 1 to length(s) do s[i]:= cs_ascii_char2(s[i]);
     cs_ascii_str2:= s
   end;

{
function int_to_ascii(b: pbytes; size: int): string;
   var   i : int;
   begin
     for i:= 0 to size-1 to
         if b^[i]
   end;
}

function getchar(s: string): char;
   begin
     if (s='') or (s=NULL) then getchar:= ' '
     else getchar:= s[1]
   end;

function getcharu(s: string): char;
   begin
     getcharu:= upcase(getchar(s))
   end;


function getcharp(s: string; pos: byte): char;
   begin
     if (length(s)<pos) or (s=#0) then getcharp:= ' '
     else getcharp:= s[pos]
   end;

{
 zarovna/oreze string S sprava/zlava na sirku width znakom fill
}
function InsChar_(S: string; width: int; fill: char; right: byte; dopln: bool): string;
   var   sf: string;
         sz: integer;
   begin
     InsChar_:= s;
     if width<0 then Exit;
     if s=NULL then s:= ' ';
     sz:= width-Length(S);
     if sz<1 then              { bolo 1 }
        begin
          if dopln then width:= N(width-3);
          s:= Copy(S,1,width);
          if dopln then s:= s+'...';
          InsChar_:= s
        end
     else begin
            FillChar(sf[1],sz,fill);
            sf[0]:= Char(sz);
            if bool(right) then InsChar_:= S+sf
            else InsChar_:= sf+S
          end
   end; { InsChar }

function InsChar(S: string; width: int; fill: char; right: byte): string;
   begin
     InsChar:= InsChar_(S,width,fill,right,false);
   end; { InsChar }

function RightChar(S: string; width: int; fill: char): string;
   begin
     RightChar:= InsChar_(s,width,fill,1,false);
   end;

{ nahradi znaky z mnoziny DelSet so stringu S znakom ch
}
function ReplChar(S: string; DelSet: TCharSet; ch: char): string;
   var   i: int;
   begin
     for i:= 1 to Length(S) do
         if S[i] in DelSet then S[i]:= ch;
     ReplChar:= S
   end; { ReplChar }


{ unifikuje string pre porovnanie
}
function uni_str(s: string): string;
   begin
     s:= cut_(s);
     s:= abc_str(s);             { odstranenie bielych znakov }
     uni_str:= cs_ascii_str(s)   { -//- diakritiky            }
   end;

{ unifikuje string pre porovnanie
}
function abc_str(s: string): string;
   var   i: int;
   begin
     for i:= 1 to length(s) do
       begin
         if (s[i]<' ') then s[i]:= ' ';
         s[i]:= upcase(s[i])
       end;
     abc_str:= s
   end;

{function abc_str(s: string): string;
   begin
     abc_str:= ReplChar(s, [#0..#31], ' ')
   end;}
