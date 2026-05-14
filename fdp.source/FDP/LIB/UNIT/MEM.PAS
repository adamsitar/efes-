(*-------------------------------------------------------------------*)
(* Mem 1.0                                                           *)
(* 1993                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}

unit Mem;

{ C FIXED PRELOAD PERMANENT}
{ F+,X+,I-,R-,S-,O- }


interface


     uses TypeDef;


     const  MIN_NET_HEAP_SIZE = 30000;  { pod tuto hranicu pamate nie su prijimane pakety }


     function  AllocMem     (var P: pointer; Bytes: word): bool;
     function  AllocCopyMem (var P: pointer; Bytes: word; S: pointer): bool;
     procedure DeallocMem   (var P: pointer; Bytes: word);

     function  NewVar  (var varn: pointer; var_size: word; alloc: bool;
                        p_new: PProc_p2; varp: pointer
                       ): bool;
     procedure DispVar (var varn: pointer; var_size: word;
                        p_disp: PProc_p;
                        dealloc: bool
                       );

     function  memcomp (p1,p2: pointer; size: word): bool;

     function  GetPtr     (P: pointer; Ofs: long): pointer;
     function  GetFuncPtr (P: pointer): pointer;

     function  IncPtr (var P: pointer; i: long): pointer;
     function  DecPtr (var P: pointer; i: long): pointer;

     type  PPtrRec = ^TPtrRec;
           TPtrRec = record
              Prev: pointer;
              Ptr : pointer;
           end;

     procedure Push(var Reg; Ptr: pointer);
     procedure Pop (var Reg);

     function  PrevPRec(var Reg: PPtrRec): PPtrRec;
     function  PtrPRec (const Reg: PPtrRec): pointer;



implementation


function  memcomp(p1,p2: pointer; size: word): bool;
   var    i : long;
   begin
     i:= 0; while (i<size) and (pchars(p1)^[i]=pchars(p2)^[i]) do inc(i);
     memcomp:= i=size
   end;

function AllocMem(var P: pointer; Bytes: word): bool;
   begin
     if MaxAvail > Bytes then
        begin
          GetMem(P, Bytes);
          FillChar(byte(P^), Bytes, 0);
          AllocMem:= true
        end
     else begin
            P:= nil;
            AllocMem:= false
          end
   end; { AllocMem }

function AllocCopyMem(var P: pointer; Bytes: word; S: pointer): bool;
   var   res: bool;
   begin
     res:= AllocMem(P,Bytes);
     if res and (s<>nil) then Move(S^,P^,Bytes);
     AllocCopyMem:= res
   end; { AllocMem }


procedure DeallocMem(var P: pointer; Bytes: word);
    begin
      if P<>nil then
         begin
           FreeMem(P, Bytes);
           P:= nil
         end;
    end; { FreeMem }

function  NewVar (var varn: pointer; var_size: word; alloc: bool;
                  p_new: PProc_p2; varp: pointer
                 ): bool;
   begin
      NewVar:= false;
      if alloc and (not AllocMem(varn,var_size)) then Exit;
      NewVar:= true;
      if varp<>nil then
         if (p_new<>nil) then TProc_p2(p_new)(varp,varn)
         else move(pbytes(varp)^,pbytes(varn)^,var_size)
      else fillchar(pbytes(varn)^,var_size,0)
    end;

procedure DispVar (var varn: pointer; var_size: word;
                   p_disp: PProc_p;
                   dealloc: bool
                  );
    begin
      if p_disp<>nil then TProc_p(p_disp)(varn);
      if dealloc then DeallocMem (varn,var_size);
    end;


function GetPtr(P: pointer; Ofs: long): pointer;
   begin
     GetPtr:= Ptr(
                  PtrRec(P).Seg + PtrRec(Ofs).Seg * SelectorInc,
                  PtrRec(P).Ofs + PtrRec(Ofs).Ofs
                 );
   end;

{
vrati adresu CS v protected mode, aby sa don mohlo zapisovat
}
function GetFuncPtr(P: pointer): pointer;
   begin
     GetFuncPtr:= Ptr(Seg(P) + SelectorInc, Ofs(P))
   end;


function IncPtr(var P: pointer; i: long): pointer;
   begin
     P:= Ptr(
             PtrRec(P).Seg + PtrRec(i).Seg * SelectorInc,
             PtrRec(P).Ofs + PtrRec(i).Ofs
            );
     IncPtr:= P
   end; { IncPtr }


function DecPtr(var P: pointer; i: long): pointer;
   begin
     P:= Ptr(
             PtrRec(P).Seg - PtrRec(i).Seg * SelectorInc,
             PtrRec(P).Ofs - PtrRec(i).Ofs
            );
     DecPtr:= P
   end; { DecPtr }


procedure Push(var Reg; Ptr: pointer);
    var   Temp: PPtrRec;
    begin
      New(Temp);
      Temp^.Prev:= pointer(Reg);  { zapamatanie adresy posledneho clanku Reg }
      Temp^.Ptr := Ptr;           { ulozenie smernika na objekt, pole...     }
      pointer(Reg):= Temp
     end; { Push }

procedure Pop(var Reg);
    var   Temp: PPtrRec;
    begin
      if pointer(Reg)=nil then Exit;
      Temp:= pointer(Reg);
      pointer(Reg):= Temp^.Prev;
      Dispose(Temp)
     end; { Pop }


function PrevPRec(var Reg: PPtrRec): PPtrRec;
   begin
     Reg:= Reg^.Prev;
     PrevPRec:= Reg
   end; { Prev }

function PtrPRec(const Reg: PPtrRec): pointer;
   begin
     PtrPRec:= Reg^.Ptr
   end; { Ptr }


end. { Mem }