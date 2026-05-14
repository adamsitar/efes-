function is_scish_(s: string; var cis: long; hex: bool): bool;
   var   I: long;
         R: int;
   begin
     R:= 0;
     if s<>'' then
        begin
          if hex and (s[1]<>'$') then s:= '$'+s;
          Val(s,I,R)
        end
     else I:= 0;
     cis:= I;
     is_scish_:= R=0
   end;

function is_scish(s: string; pos,len: int; var cis: long; hex: bool): bool;
   begin
     is_scish:= is_scish_(Copy(s,pos,len),cis,hex);
   end;

function is_scis(s: string; pos,len: int; var cis: long): bool;
   begin
     is_scis:= is_scish(s, pos,len, cis,false)
   end;


function scish_(s: string; hex: bool): long;
   var   cis: long;
   begin
     is_scish_(s, cis, hex);
     scish_:= cis
   end;

function scish(s: string; pos,len: int; hex: bool): long;
   var   cis: long;
   begin
     is_scish(s, pos,len, cis, hex);
     scish:= cis
   end;

function scis(s: string; pos,len: int): long;
   var   cis: long;
   begin
     is_scis(s, pos,len, cis);
     scis:= cis
   end;

function cstr(x: long; width: int): string;
   var   s: string;
   begin
     Str(x:width, s);
     cstr:= s
   end;


function eq_str(s1,s2: string): bool;
   begin
     eq_str:= uni_str(s1)=uni_str(s2)
   end;

function empty_str(s: string): bool;
   begin
     empty_str:= cut_(s)=''
   end;


function  init_str (data: pchars; num: int): string;
    var   s: string;
    begin
      num:= Minimum(num,sizeof(s)-1);
      s[0]:= chr(num);
      Move(data^,s[1],num);
      init_str:= s
    end;


function s_prizn(s: string): char;
   begin
     s_prizn:= getcharu(delchar(s,setCisl+['.',',']))
   end;

function s_int(s: string): int;
   var   c,i: int;
   begin
     s:= delchar(s,setPism_);
     val(s,i,c);
     s_int:= i
   end;

function s_real(s: string): real;
   var   c: int;
         r: real;
   begin
     s:= delchar(s,setPism_);
     val(s,r,c);
     s_real:= r
   end;


{
  vrati s_ v ktorom su len subretazce zo s ohranicene s ch,
  priklad: ~Q~uit  ~B~lb -> Q    B
}
function get_s_(s: string; ch: char; del: Tcharset): string;
   var   s_ : string;
         b_ : bool;
         i  : int;
   begin
     s:= delchar(s,del);
     s_:= ''; b_:= false;
     for i:= 1 to Length(s) do
         begin
           if s[i]=ch then b_:= not b_
           else { nebola zmena }
                 if b_ then s_ := s_+s[i] else s_ := s_ +' '
         end;
     get_s_:= s_
   end;

{
  vrati substring zo s od pozicie p,
  pricom vynecha medzery za p
  a nastavi p na p + length(p) + 1
}
function get_sp(s: string; var lo,hi: int): string;
   var   s_  : string;
         i,j : int;
   begin
     if lo<1 then lo:= 1; hi:= lo+1;
     i:= lo; s_:= '';
     while (i<=length(s)) and (s[i]=' ') do inc(i);
     if i<=length(s) then
        begin
          j:= i;
          while (j<=length(s)) and (s[j]<>' ') do inc(j);
          s_:= copy(s,i,j-i);
          lo:= i;
          hi:= j
        end;
     get_sp:= s_
   end;
