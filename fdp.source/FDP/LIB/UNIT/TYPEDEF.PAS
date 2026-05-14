(*-------------------------------------------------------------------*)
(* Deklaracia pomocnych typov a pseudofunkcii  1.0                   *)
(* 1993                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$C FIXED PRELOAD PERMANENT}
{$F+,R-,S-,O- }


unit TypeDef;


interface


    const  MAX_ARRAY_SIZE  = 65520;
           MIN__HEAP_SIZE  = 100;   { kB } { minimalna velkost heapu }


    {$I type_pas.h}
    {$I type_arr.h}
    {$I type_rec.h}
    {$I type_utl.h}
    {$I type_prc.h}


    function   index_pola_s(strana: pchar; znakov: int; r,od: int; _1: bool): pchar;

    function   GetFalse: bool;
    procedure  Abstract;

    procedure  no_action;
    procedure  proc__adr_var(proc,adr_var: pointer);

    function   op_bool(prem: bool; op: bool): bool;
    function   get_pbool(p: pbool; alt: bool): bool;

    function   bool_to_char(b: bool): char;
    function   char_to_bool(ch: char): bool;
    function   word_to_str (w: word): string;
    function   str_to_word (s: string): word;


implementation

{
 Prepocet offestu, pretoze pole stringov ma roznu dlzku...
 _1 urcuje, ci od 1. alebo 0. indexu stringu
}
function index_pola_s(strana: pchar; znakov: int; r,od: int; _1: bool): pchar;
   var   p: pchar;
   begin
     p:= pointer(strana);     { ukazuje na alokovanu adresu }
     p:= p + r*(znakov+1) + ord(_1) + od; {=strana^[r][od+1]}
     index_pola_s:= p
   end;


function GetFalse: bool;
   begin
     GetFalse:= false
   end;

procedure Abstract;
    begin
      {$IFDEF DEBUG} RunError(211) {$ENDIF}
    end;


procedure no_action;
    begin
    end; { no_action }

procedure proc__adr_var(proc,adr_var: pointer);
    begin
      if proc<>nil then
         if (adr_var<>nil) then Tproc_p(proc)(adr_var)
         else Tproc(proc)
    end;


function op_bool(prem: bool; op: bool): bool;
   begin
     if op then op_bool:= prem
     else op_bool:= not prem
   end;


function get_pbool(p: pbool; alt: bool): bool;
   begin
     if p<>nil then get_pbool:= p^
     else get_pbool:= alt
   end;


function bool_to_char(b: bool): char;
   begin
     bool_to_char:= chr(int(b))
   end;

function char_to_bool(ch: char): bool;
   begin
     char_to_bool:= bool(ch)
   end;

function word_to_str(w: word): string;
   var   s: string;
   begin
     move(w,s[1],sizeof(w));
     s[0]:= chr(sizeof(w));
     word_to_str:= s
   end;

function str_to_word(s: string): word;
   var   w: word;
   begin
     move(s[1],w,sizeof(w));
     str_to_word:= w
   end;



end. { TypeDef }