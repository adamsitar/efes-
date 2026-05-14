{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ Null terminated strings - Borland's Library              €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
function BPStrLen(Str: PChar): Word; assembler;
asm
	CLD
	LES	DI,Str
	MOV	CX,0FFFFH
	XOR	AL,AL
	REPNE	SCASB
	MOV	AX,0FFFEH
	SUB	AX,CX
end;

function StrLen(Str: PChar): Long;  { aby sa mohlo porovnavat strlen()-1 }
   var   L : word;
   begin
     if (Str<>nil) and (Str^<>NULL) then L:= BPStrLen(Str) else L:= 0;
     StrLen:= L
   end;

function StrEnd(Str: PChar): PChar; assembler;
asm
	CLD
	LES	DI,Str
	MOV	CX,0FFFFH
	XOR	AL,AL
	REPNE	SCASB
	MOV	AX,DI
	MOV	DX,ES
	DEC	AX
end;

function StrMove(Dest, Source: PChar; Count: Word): PChar; assembler;
asm
	PUSH	DS
	CLD
	LDS	SI,Source
	LES	DI,Dest
	MOV	AX,DI
	MOV	DX,ES
	MOV	CX,Count
	CMP	SI,DI
	JAE	@@1
	STD
	ADD	SI,CX
	ADD	DI,CX
	DEC	SI
	DEC	DI
@@1:	REP	MOVSB
	CLD
	POP	DS
end;

function StrCopy(Dest, Source: PChar): PChar; assembler;
asm
	PUSH	DS
	CLD
	LES	DI,Source
	MOV	CX,0FFFFH
	XOR	AL,AL
	REPNE	SCASB
	NOT	CX
	LDS	SI,Source
	LES	DI,Dest
	MOV	AX,DI
	MOV	DX,ES
	REP	MOVSB
	POP	DS
end;

function StrECopy(Dest, Source: PChar): PChar; assembler;
asm
	PUSH	DS
	CLD
	LES	DI,Source
	MOV	CX,0FFFFH
	XOR	AL,AL
	REPNE	SCASB
	NOT	CX
	LDS	SI,Source
	LES	DI,Dest
	REP	MOVSB
	MOV	AX,DI
	MOV	DX,ES
	DEC	AX
	POP	DS
end;

function StrLCopy(Dest, Source: PChar; MaxLen: Word): PChar; assembler;
asm
	PUSH	DS
	CLD
	LES	DI,Source
	MOV	CX,MaxLen
	MOV	BX,CX
	XOR	AL,AL
	REPNE	SCASB
	SUB	BX,CX
	MOV	CX,BX
	LDS	SI,Source
	LES	DI,Dest
	MOV	BX,DI
	MOV	DX,ES
	REP	MOVSB
	STOSB
	XCHG	AX,BX
	POP	DS
end;

function _StrPCopy(Dest: PChar; Source: String): PChar; assembler;
asm
	PUSH	DS
	CLD
	LDS	SI,Source
	LES	DI,Dest
	MOV	BX,DI
	MOV	DX,ES
	LODSB
	XOR	AH,AH
	XCHG	AX,CX
	REP	MOVSB
	XOR	AL,AL
	STOSB
	XCHG	AX,BX
	POP	DS
end;

function StrPCopy(Dest: PChar; Source: String): PChar;
   var   _source: string;
   begin
     _source:= ReplChar(Source,[NULL],' ');
     StrPCopy:= _StrPCopy(Dest,_source);
   end;


function StrSCopy(Source: PChar; MaxLen: Word): string;
   var   ch: array[0..255] of char;
         s : string;
   begin
     if (Source<>nil) and (Source^<>NULL) then
        begin
          StrLCopy(ch,Source,minimum(MaxLen,sizeof(string)-1));
          s:= strpas(ch)
        end
     else s:= '';
     StrSCopy:= s
   end;

function StrNCopy(var s1,s2: PChar; disp_s1,disp_s2: bool): PChar;
   var   L     : Word;
         P,T   : PChar;
         L1,L2 : word;
   begin
     StrNCopy:= nil;
     L1:= StrLen(S1); L2:= StrLen(S2);
     L := L1+L2;
     if L<>0 then
        begin
          inc(L){NULL}; GetMem(P, L); T:= P;
          Move(S1^,T^,L1); incptr(pointer(T),L1);
          Move(S2^,T^,L2); incptr(pointer(T),L2);
          T^:= NULL;
          StrNCopy:= P
        end;
     if disp_s1 then StrDispose(s1);
     if disp_s2 then StrDispose(s2)
   end;

function StrACopy(var s1,s2: PChar; disp_s2: bool): PChar;
   begin
     s1:= StrNCopy(s1,s2, true,disp_s2);
     StrACopy:= s1
   end;


function StrNPCopy(var s1: PChar; s2: string; s1_first, disp_s1: bool): PChar;
   var   L     : Word;
         P,T   : PChar;
         L1,L2 : word;
   begin
     StrNPCopy:= nil;
     s2:= ReplChar(s2,[NULL],' ');
     L1:= StrLen(s1); L2:= Length(s2);
     L := L1+L2;
     if L<>0 then
        begin
          inc(L){NULL}; GetMem(P, L); T:= P;
          if s1_first then
             begin
               Move(s1^,T^,L1); incptr(pointer(T),L1);
               Move(s2[1],T^,L2); incptr(pointer(T),L2)
             end
          else begin
                 Move(s2[1],T^,L2); incptr(pointer(T),L2);
                 Move(s1^,T^,L1); incptr(pointer(T),L1)
               end;
          T^:= NULL;
        end
     else P:= nil;
     if disp_s1 then StrDispose(s1);
     StrNPCopy:= P
   end;


function StrPICopy(Dest: PChar; Source: String; sirka: int): PChar;
   begin
     StrPICopy:= StrPCopy(Dest,inschar(Source,sirka,' ',1))
   end;


function StrCat(Dest, Source: PChar): PChar; assembler;
asm
	PUSH	Dest.Word[2]
	PUSH	Dest.Word[0]
	PUSH	CS
	CALL	NEAR PTR StrEnd
	PUSH	DX
	PUSH	AX
	PUSH	Source.Word[2]
	PUSH	Source.Word[0]
	PUSH	CS
	CALL	NEAR PTR StrCopy
	MOV	AX,Dest.Word[0]
	MOV	DX,Dest.Word[2]
end;

function StrLCat(Dest, Source: PChar; MaxLen: Word): PChar; assembler;
asm
	PUSH	Dest.Word[2]
	PUSH	Dest.Word[0]
	PUSH	CS
	CALL	NEAR PTR StrEnd
	MOV	CX,Dest.Word[0]
	ADD	CX,MaxLen
	SUB	CX,AX
	JBE	@@1
	PUSH	DX
	PUSH	AX
	PUSH	Source.Word[2]
	PUSH	Source.Word[0]
	PUSH	CX
	PUSH	CS
	CALL	NEAR PTR StrLCopy
@@1:	MOV	AX,Dest.Word[0]
	MOV	DX,Dest.Word[2]
end;

function StrComp(Str1, Str2: PChar): Integer; assembler;
asm
	PUSH	DS
	CLD
	LES	DI,Str2
	MOV	SI,DI
	MOV	CX,0FFFFH
	XOR	AX,AX
	CWD
	REPNE	SCASB
	NOT	CX
	MOV	DI,SI
	LDS	SI,Str1
	REPE	CMPSB
	MOV	AL,DS:[SI-1]
	MOV	DL,ES:[DI-1]
	SUB	AX,DX
	POP	DS
end;

function StrIComp(Str1, Str2: PChar): Integer; assembler;
asm
	PUSH	DS
	CLD
	LES	DI,Str2
	MOV	SI,DI
	MOV	CX,0FFFFH
	XOR	AX,AX
	CWD
	REPNE	SCASB
	NOT	CX
	MOV	DI,SI
	LDS	SI,Str1
@@1:	REPE	CMPSB
	JE	@@4
	MOV	AL,DS:[SI-1]
	CMP	AL,'a'
	JB	@@2
	CMP	AL,'z'
	JA	@@2
	SUB	AL,20H
@@2:	MOV	DL,ES:[DI-1]
	CMP	DL,'a'
	JB	@@3
	CMP	DL,'z'
	JA	@@3
	SUB	DL,20H
@@3:	SUB	AX,DX
	JE	@@1
@@4:	POP	DS
end;

function StrLComp(Str1, Str2: PChar; MaxLen: Word): Integer; assembler;
asm
	PUSH	DS
	CLD
	LES	DI,Str2
	MOV	SI,DI
	MOV	AX,MaxLen
	MOV	CX,AX
	JCXZ	@@1
	XCHG	AX,BX
	XOR	AX,AX
	CWD
	REPNE	SCASB
	SUB	BX,CX
	MOV	CX,BX
	MOV	DI,SI
	LDS	SI,Str1
	REPE	CMPSB
	MOV	AL,DS:[SI-1]
	MOV	DL,ES:[DI-1]
	SUB	AX,DX
@@1:	POP	DS
end;

function StrLIComp(Str1, Str2: PChar; MaxLen: Word): Integer; assembler;
asm
	PUSH	DS
	CLD
	LES	DI,Str2
	MOV	SI,DI
	MOV	AX,MaxLen
	MOV	CX,AX
	JCXZ	@@4
	XCHG	AX,BX
	XOR	AX,AX
	CWD
	REPNE	SCASB
	SUB	BX,CX
	MOV	CX,BX
	MOV	DI,SI
	LDS	SI,Str1
@@1:	REPE	CMPSB
	JE	@@4
	MOV	AL,DS:[SI-1]
	CMP	AL,'a'
	JB	@@2
	CMP	AL,'z'
	JA	@@2
	SUB	AL,20H
@@2:	MOV	DL,ES:[DI-1]
	CMP	DL,'a'
	JB	@@3
	CMP	DL,'z'
	JA	@@3
	SUB	DL,20H
@@3:	SUB	AX,DX
	JE	@@1
@@4:	POP	DS
end;

function StrScan(Str: PChar; Chr: Char): PChar; assembler;
asm
	CLD
	LES	DI,Str
	MOV	SI,DI
	MOV	CX,0FFFFH
	XOR	AL,AL
	REPNE	SCASB
	NOT	CX
	MOV	DI,SI
	MOV	AL,Chr
	REPNE	SCASB
	MOV	AX,0
	CWD
	JNE	@@1
	MOV	AX,DI
	MOV	DX,ES
	DEC	AX
@@1:
end;

function StrRScan(Str: PChar; Chr: Char): PChar; assembler;
asm
	CLD
	LES	DI,Str
	MOV	CX,0FFFFH
	XOR	AL,AL
	REPNE	SCASB
	NOT	CX
	STD
	DEC	DI
	MOV	AL,Chr
	REPNE	SCASB
	MOV	AX,0
	CWD
	JNE	@@1
	MOV	AX,DI
	MOV	DX,ES
	INC	AX
@@1:	CLD
end;

function StrPos(Str1, Str2: PChar): PChar; assembler;
asm
	PUSH	DS
	CLD
	XOR	AL,AL
	LES	DI,Str2
	MOV	CX,0FFFFH
	REPNE	SCASB
	NOT	CX
	DEC	CX
	JE	@@2
	MOV	DX,CX
	MOV	BX,ES
	MOV	DS,BX
	LES	DI,Str1
	MOV	BX,DI
	MOV	CX,0FFFFH
	REPNE	SCASB
	NOT	CX
	SUB	CX,DX
	JBE	@@2
	MOV	DI,BX
@@1:	MOV	SI,Str2.Word[0]
	LODSB
	REPNE	SCASB
	JNE	@@2
	MOV	AX,CX
	MOV	BX,DI
	MOV	CX,DX
	DEC	CX
	REPE	CMPSB
	MOV	CX,AX
	MOV	DI,BX
	JNE	@@1
	MOV	AX,DI
	MOV	DX,ES
	DEC	AX
	JMP	@@3
@@2:	XOR	AX,AX
	MOV	DX,AX
@@3:	POP	DS
end;

function StrUpper(Str: PChar): PChar; assembler;
asm
	PUSH	DS
	CLD
	LDS	SI,Str
	MOV	BX,SI
	MOV	DX,DS
@@1:	LODSB
	OR	AL,AL
	JE	@@2
	CMP	AL,'a'
	JB	@@1
	CMP	AL,'z'
	JA	@@1
	SUB	AL,20H
	MOV	[SI-1],AL
	JMP	@@1
@@2:	XCHG	AX,BX
	POP	DS
end;

function StrLower(Str: PChar): PChar; assembler;
asm
	PUSH	DS
	CLD
	LDS	SI,Str
	MOV	BX,SI
	MOV	DX,DS
@@1:	LODSB
	OR	AL,AL
	JE	@@2
	CMP	AL,'A'
	JB	@@1
	CMP	AL,'Z'
	JA	@@1
	ADD	AL,20H
	MOV	[SI-1],AL
	JMP	@@1
@@2:	XCHG	AX,BX
	POP	DS
end;


function StrPas(Str: PChar): string;
   var   s : string;
         l : int;
   begin
     if (Str=nil) or (Str^=NULL) then StrPas:= ''
     else begin
            l:= strlen(Str);
            if l>sizeof(s)-1 then l:= sizeof(s)-1;
            s[0]:= chr(l);
            move(str^,s[1],l);
            StrPas:= s
          end
   end;

function StrNew(Str: PChar): PChar;
   var   L: Word;
         P: PChar;
   begin
     StrNew:= nil;
     if (Str<>nil) and (Str^<>NULL) then
     begin
       L:= StrLen(Str) + 1;
       GetMem(P,L);
       if P<>nil then StrNew:= StrMove(P, Str, L)
     end
   end;

function StrPasNew(Str: string): PChar;
   var   ch: array[0..255] of char;
   begin
     StrPCopy(ch,Str);
     StrPasNew:= StrNew(ch)
   end;

function StrArrNew(arr: pchars; poc: word): PChar;
   var   i : word;
         p : pchar;
   begin
     p:= nil;
     if (poc>0) and (MaxAvail>poc+1) then
        begin
          GetMem(p,poc+1);
          Move(arr^,p^,poc);
          p[poc]:= NULL;
          for i:= 0 to poc-1 do if p[i]=NULL then p[i]:= ' '
        end;
     StrArrNew:= p
   end;


function  StrAlloc (len: word): PChar;
   var    p : pchar;
   begin
     p:= nil;
     if (len>0) and AllocMem (pointer(p), len+1) then { pre istotu } p[len]:= NULL;
     StrAlloc:= p
   end;

procedure StrDispose(var Str: PChar);
    begin
      if Str<>nil then FreeMem(Str, StrLen(Str) + 1);
      Str:= nil
    end;


{
  vybratie substringu zo stringu
}
function GetPStrItems(P: pchar; Skip: TCharSet): word;
   var   p1,p2 : pchar;
         pos,i : word;
   begin
     pos:= 0;
     p1:= p; while (strlen(p1)>0) and (p1[0] in Skip) do inc(p1);
     while (p1<>nil) and (p1^<>NULL) do
       begin
         p2:= p1; {p1:= StrScan(p1, SkipChar); stare }
         while (strlen(p1)>0) and (not(p1[0] in Skip)) do inc(p1);
         if (p1<>nil) and (p1^<>NULL) then
            begin
              inc(pos);
              while (StrLen(p1)>0) and (p1[0] in Skip) do inc(p1)
            end
         else if (StrLen(p2)>0) and (not(p2[0] in Skip)) then inc(pos)
       end;
     GetPStrItems:= pos
   end;


function PosStr(P: pchar; pos: word; Skip: TCharSet): pchar;
   var   p1 : pchar;
         i  : word;
   begin
     p1:= p; while (strlen(p1)>0) and (p1[0] in Skip) do inc(p1);
     i:= 1; while (p1<>nil) and (p1^<>NULL) and (i<pos) do
       begin
         while (strlen(p1)>0) and (not(p1[0] in Skip)) do inc(p1);
         if (p1<>nil) and (p1^<>NULL) then
            begin
              inc(i);
              while (strlen(p1)>0) and (p1[0] in Skip) do inc(p1)
            end
       end;
     if strlen(p1)=0 then p1:= nil;
     PosStr:= p1
   end;

function Get0Str(P: pchar; pos: word; Skip: TCharSet): pchar;
   var   p1,p2,p3 : pchar;
         i,k      : word;
   begin
     p1:= PosStr(P, pos, Skip);
     if (p1<>nil) and (p1^<>NULL) then
        begin
          p2:= p1;
          while (strlen(p2)>0) and (not (p2[0] in Skip)) do inc(p2);
          k:= p2-p1+1;
          GetMem(p3,k);
          Move(p1^,p3^,k-1);
          p3[k-1]:= NULL;
          Get0Str:= p3
        end
     else Get0Str:= nil
   end;

function GetPStr(P: pchar; pos: word; Skip: TCharSet): string;
   var   p3 : pchar;
   begin
     p3:= Get0Str(P,pos,Skip);
     if (p3<>nil) and (p3^<>NULL) then
        begin
          GetPStr:= StrPas(p3);
          StrDispose(p3)
        end
     else GetPStr:= ''
   end;

{
  alokuje a vrati dst zo src zacinajuci na substr az po nasledujuci oddelovac odd_ch;
  ak je dlzka<=255 vrati string, inak pchar
  po vysledku true je potrebne odalokovat dst
}
function _get_pch(var dst: pchar; src: pchar; substr: pchar; odd_ch: char): bool;
   var   p1,p2 : pchar;
         L     : int;
   begin
     strdispose(dst);
     L:= 0;
     p1:= strpos(src,substr);
     if (p1<>nil) and (p1^<>NULL) then
        begin
          p2:= p1;
          inc(p2,strlen(substr));
          p2:= strscan(p2,odd_ch);
          if p2<>nil then L:= p2-p1
          else L:= strlen(p1);
          if L<>0 then
             begin
               getmem(dst,L+1);
               StrLCopy(dst,p1,L)
             end
        end;
     _get_pch:= L<>0
   end;


function ReplChar0 (p: pchar; DelSet: TCharSet; ch: str1; alloc: bool): pchar;
   var   pc  : pchar;
         i,l : int;
   begin
     if alloc then pc:= StrNew(p) else pc:= p;
     l:= StrLen(pc);
     i:= 0; while i<l do
       begin
         if pc[i] in DelSet then
            begin
              if (ch<>'') then
                 begin
                   pc[i]:= ch[1];
                   inc(i)
                 end
              else if not (' ' in DelSet) then
                      begin
                        move(pc[i+1],pc[i],l-i-1);
                        pc[l-1]:= ' '
                      end
            end
         else inc(i);
       end;
     ReplChar0:= pc
   end;


function UpString0 (p: pchar; alloc: bool): pchar;
   var   pc : pchar;
         i  : int;
   begin
     if alloc then pc:= StrNew(p) else pc:= p;
     for i:= 0 to StrLen(pc)-1 do pc[i]:= upcase(pc[i]);
     UpString0:= pc
   end;


function eq_str0 (p1,p2: pchar): bool;
   begin
     eq_str0:= strcomp(p1,p2)=0
   end;
