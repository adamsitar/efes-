(*-------------------------------------------------------------------*)
(* LETVIS FDP                                                        *)
(* (c) Ales Kosice 1993  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}

(*{$IFDEF SERVER}
 {$X+,I-,S-,P-,F+,O-}
 {$C FIXED PRELOAD PERMANENT}

 { Kvoli castemu pouzivaniu funkcii a rovnako pouziti v intr...
{$ENDIF}
*)

{ Poznamka : volanie fcie StrDispose sa spolieha na to, ze sa kontroluje Str <> nil a priradi Str:= nil
}

unit str0;


interface


     uses TypeDef;


    { Null terminated strings }

     function  StrLen   (Str: PChar): Long;
     function  StrEnd   (Str: PChar): PChar;
     function  StrMove  (Dest, Source: PChar; Count: Word): PChar; { neverim jej ! }

     function  StrCopy  (Dest, Source: PChar): PChar;
     function  StrECopy (Dest, Source: PChar): PChar;
     function  StrLCopy (Dest, Source: PChar; MaxLen: Word): PChar;
     function  StrPCopy (Dest: PChar; Source: String): PChar;
     function  StrSCopy (Source: PChar; MaxLen: Word): string;
     function  StrNCopy (var s1,s2: PChar; disp_s1,disp_s2: bool): PChar;
     function  StrACopy (var s1,s2: PChar; disp_s2: bool): PChar;
     function  StrNPCopy(var s1: PChar; s2: string; s1_first,disp_s1: bool): PChar;
     function  StrPICopy(Dest: PChar; Source: String; sirka: int): PChar;

     function  StrCat   (Dest, Source: PChar): PChar;
     function  StrLCat  (Dest, Source: PChar; MaxLen: Word): PChar;
     function  StrComp  (Str1, Str2: PChar): Integer;
     function  StrIComp (Str1, Str2: PChar): Integer;
     function  StrLComp (Str1, Str2: PChar; MaxLen: Word): Integer;
     function  StrLIComp(Str1, Str2: PChar; MaxLen: Word): Integer;

     function  StrScan  (Str: PChar; Chr: Char): PChar;
     function  StrRScan (Str: PChar; Chr: Char): PChar;
     function  StrPos   (Str1, Str2: PChar): PChar;

     function  StrUpper (Str: PChar): PChar;
     function  StrLower (Str: PChar): PChar;

     function  StrPas     (Str: PChar): String;
     function  StrNew     (Str: PChar): PChar;
     function  StrPasNew  (Str: string): PChar;
     function  StrArrNew  (arr: pchars; poc: word): PChar;
     function  StrAlloc   (len: word): PChar;
     procedure StrDispose (var Str: PChar);

     function  GetPStrItems(P: pchar; Skip: TCharSet): word;
     function  PosStr      (P: pchar; pos: word; Skip: TCharSet): pchar;
     function  GetPStr     (P: pchar; pos: word; Skip: TCharSet): string;
     function  Get0Str     (P: pchar; pos: word; Skip: TCharSet): pchar;

     function  _get_pch (var dst: pchar; src: pchar; substr: pchar; odd_ch: char): bool;


    { vyber stringu alebo pchar-u z pola znakov }
     function  get_str_items (data: pchars; size: word; odd: TCharSet): word;
     function  get_ind_      (data: pchars; size: word; odd: char; var posi: word): bool;
     function  get_ind       (data: pchars; size: word; pos: int; odd: TCharSet; var zac,kon: word): bool;
     function  get_str_      (data: pchars; size: word; pos: int; odd: TCharSet; var res: bool; max_size: int): string;
     function  get_str       (data: pchars; size: word; pos: int; odd: TCharSet; max_size: int): string;
     function  get_str0_     (data: pchars; size: word; pos: int; odd: TCharSet; var res: bool): pchar;
     function  get_str0      (data: pchars; size: word; pos: int; odd: TCharSet): pchar;
     function  get_strs0     (data: pchars; size: word; prvy,posledny: int; odd: TCharSet): pchar;
     function  get_strs0p    (data: pchars; size: word; prvy,posledny: int; odd: TCharSet): string;


     function  str_item    (s: string; zac,kon: int): string;

    { vyber stringu alebo cisla zo stringu }

     function  GetStrItems (S: string; SkipSet: TCharSet): byte;
     function  GetStr      (S: string; pos: byte; SkipSet: TCharSet): string;
     function  GetStr_     (S: string; pos: byte; SkipSet: TCharSet; max_size: byte): string;
     function  WGetInt     (var Cislo: long; S: string; pos: byte; SkipSet: TCharSet): bool;
     function  GetInt      (S: string; pos: byte; SkipSet: TCharSet): long;

     procedure SetBound    (S: string; var _lo,_hi: int; pos: byte; SkipSet: TCharSet);
     procedure SetPBound   (S: PChar;  var _lo,_hi: int; pos: byte; SkipSet: TCharSet);
     {function  int_to_ascii(b: pbytes; size: int): string;}


    { transformacia na string }
     function  IntToStr   (Cislo: long; sirka: byte; nula: byte): string;
     function  WordToHex  (hex: word): string;
     function  ByteToHex  (hex: byte): string;


    { spracovanie stringu : konverzie, nahradenie, vlozenie znakov }
     function  CenterStr  (S: string; wide: byte): string;
     function  UpString   (S: string): string;
     function  DelChar    (S: string; DelSet: TCharSet): string;
     function  DelCharN   (S: string; EnSet: TCharSet): string;
     function  ReplChar   (S: string; DelSet: TCharSet; ch: char): string;
     function  InsChar_   (S: string; width: int; fill: char; right: byte; dopln: bool): string;
     function  InsChar    (S: string; width: int; fill: char; right: byte): string;
     function  RightChar  (S: string; width: int; fill: char): string;

     function  UpString0  (p: pchar; alloc: bool): pchar;
     function  ReplChar0  (p: pchar; DelSet: TCharSet; ch: str1; alloc: bool): pchar;

     function  cs_ascii_char  (ch: char) : char;
     function  cs_ascii_char2 (ch: char) : char;
     function  cs_ascii_str   (s: string): string;
     function  cs_ascii_str2  (s: string): string;

     function  uni_str (s: string): string;
     function  abc_str (s: string): string;


    { mazanie medzier }
     function  cut_    (S: string): string;
     function  cut_r   (S: string): string;    { sprava }
     function  cut_r0  (S: string): string;    { sprava odreze 0 }
     function  cut_str (Substr: string; s: string): string;
     function  cut_3   (s: string; size: int): string;

     function  getchar  (s: string): char;
     function  getcharu (s: string): char;
     function  getcharp (s: string; pos: byte): char;

     function  get_s_  (s: string; ch: char; del: Tcharset): string;
     function  get_sp  (s: string; var lo,hi: int): string;

     function  s_prizn (s: string): char;
     function  s_int   (s: string): int;
     function  s_real  (s: string): real;

     function  cNL_to_NL_ (ch : char): char;
     function  cNL__to_NL (ch : char): char;
     function  NL_to_NL_  (s: string): string;
     function  NL__to_NL  (s: string): string;
     procedure pNL_to_NL_ (data: pchars; dlz: int);
     procedure pNL__to_NL (data: pchars; dlz: int);


     function  is_scish_ (s: string; var cis: long; hex: bool): bool;
     function  is_scish  (s: string; pos,len: int; var cis: long; hex: bool): bool;
     function  is_scis   (s: string; pos,len: int; var cis: long): bool;

     function  scish_    (s: string; hex: bool): long;
     function  scish     (s: string; pos,len: int; hex: bool): long;
     function  scis      (s: string; pos,len: int): long;

     function  cstr      (x: long; width: int): string;

     function  init_str  (data: pchars; num: int): string;
     function  empty_str (s: string): bool;

     function  eq_str    (s1,s2: string): bool;
     function  eq_str0   (p1,p2: pchar): bool;

     function  get_chars  (s: string; ch: char): int;
     function  get_HotKey (var kbHot: char; key: string): char;

     function  format_    (var _: char): char;
     function  format_s   (s: string): string;
     function  format_s_  (s: string): string;

     procedure add_s (data: pchars; size: word; var s,t: string);
     procedure get_s (var p: pchars; data: pbytes; size: word);
     procedure get_s_x (var p: pchars; var data: string; max: word);

    { viacriadkove pole...
    }
     function   get_lines_i_     (p: pchar): int;
     function   get_data_lines_i_(p: pchar): int;

     function   get_line_i       (p: pchar; line: int): string;
     function   code_line_i_     (p: pchar; od,po: int; odd: string): string;
     function   code_line_i      (p: pchar; od,po: int): string;
     {function   code_line_i_nl   (p: pchar; i: int; odd: string): string;}

     function   decode_line_i    (s: string; p: pchar; odd: TCharSet): pchar;
     function   decode_line_ip   (d: pchar; p: pchar; odd: TCharSet): pchar;

     function   eq_lines         (p1,p2: pchar): bool;


implementation

uses mem, math, sets, keyb;

{$I str0.inc}  { Null terminated strings - Extended Borland's Library }
{$I str9.inc}  { spracovanie znakov z pola }

function str_item (s: string; zac,kon: int): string;
   begin
     if zac=0 then begin str_item:= ''; Exit end;
     if {(kon=0) or} (kon<zac) then kon:= length(s)+1;
     str_item:= cut_(copy(s,zac,kon-zac))
   end;

{ vrati pocet "ch" v "s"
}
 function get_chars(s: string; ch: char): int;
    var   i,j: int;
    begin
      j:= 0;
      for i:= 1 to length(s) do if s[i]=ch then inc(j);
      get_chars:= j
    end;

 function get_HotKey(var kbHot: char; key: string): char;
    var   p: int;
    begin
      p:= pos('~',key);
      if p<>0 then key:= copy(key,p+1, 1) else key:= '';
      if Length(key)=1 then kbHot:= cs_ascii_char(key[1])
      else kbHot:= #0;
      get_HotKey:= kbHot
    end;


{$I str1.inc}  { cary/mary      }
{$I str2.inc}  { mazanie znakov }
{$I str3.inc}  { upravy         }
{$I str4.inc}  { upravy - cisla }
{$I str5.inc}  { format }


 procedure add_s(data: pchars; size: word; var s,t: string);
    begin
      t[0]:= chr(size); move(data^,t[1],size);
      s:= s+t;
    end;

 procedure get_s(var p: pchars; data: pbytes; size: word);
     begin
       move(p^,data^,size);  incptr(pointer(p),size);
     end;

 procedure get_s_x (var p: pchars; var data: string; max: word);
     begin
       data[0]:= chr(minimum(pbyte(p)^,max));
       move(pchars(p)^[1],data[1],ord(data[0]));
       incptr(pointer(p),1+pbyte(p)^);
     end;

{$I strline.inc}  { format }

end. { str0 }