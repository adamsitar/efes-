function  cNL_to_NL_(ch : char): char;
   begin
     if ch=kbLF then cNL_to_NL_:= kbLF_
     else if ch=kbCR then cNL_to_NL_:= kbCR_
     else cNL_to_NL_:= ch
   end;

function  cNL__to_NL(ch : char): char;
   begin
     if ch=kbLF_ then cNL__to_NL:= kbLF
     else if ch=kbCR_ then cNL__to_NL:= kbCR
     else cNL__to_NL:= ch
   end;

function  NL_to_NL_(s: string): string;
   var    i: int;
   begin
     for i:= 1 to length(s) do
         begin
           if s[i]=kbCR then s[i]:= kbCR_;
           if s[i]=kbLF then s[i]:= kbLF_;
         end;
     NL_to_NL_:= s
   end;

function  NL__to_NL (s: string): string;
   var    i: int;
   begin
     for i:= 1 to length(s) do
         begin
           if s[i]=kbCR_ then s[i]:= kbCR;
           if s[i]=kbLF_ then s[i]:= kbLF;
         end;
     NL__to_NL:= s
   end;


procedure pNL_to_NL_ (data: pchars; dlz: int);
    var   i: word;
    begin
      if data<>nil then for i:= 0 to dlz-1 do
          begin
            if data^[i]=kbCR then data^[i]:= kbCR_;
            if data^[i]=kbLF then data^[i]:= kbLF_;
          end;
    end;

procedure pNL__to_NL (data: pchars; dlz: int);
    var   i: word;
    begin
      if data<>nil then for i:= 0 to dlz-1 do
         begin
           if data^[i]=kbCR_ then data^[i]:= kbCR;
           if data^[i]=kbLF_ then data^[i]:= kbLF;
         end;
    end;


function format_(var _: char): char;
   begin
     _:= UpCase(_);  if _ =#0 then _:= ' ';
     format_:= _
   end;

function format_s(s: string): string;
   begin
     s:= cut_(s);
     if (s='') or (s=#0) then s:= ' ';
     format_s:= s
   end;

function format_s_(s: string): string;
   begin
     if (s='') or (s=#0) then s:= ' ';
     format_s_:= s
   end;
