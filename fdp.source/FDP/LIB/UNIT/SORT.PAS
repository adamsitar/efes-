(*-------------------------------------------------------------------*)
(* Sort 1994.12.27.                                                  *)
(*                                                                   *)
(*-------------------------------------------------------------------*)
{$I comp.h}

{$B-}


{ Funkcia porovnavajuca hodnoty nesmie vratit true,
  ak su hodnoty rovne, sposobi to zacyklenie algoritmu
}

unit Sort;


interface


    uses   TypeDef;


    type   Tproc_cp2 = procedure(const p1,p2: pointer);

    function  QuickSort(arr        : Pptrs;    { pole premennych }
                        comp       : pointer;  { @TBfunc_p2: bool; pre porovnanie }
                        swap       : pointer;  { @Tproc_p2 pre prehodenie p1 a p2 }
                        left,right : int;      { hranice }
                        main_en    : bool
                       ): bool; far;

    function  QuickSort_IndArr
                       (ind        : Pints;    { pole indexov    }
                        arr        : Pptrs;    { pole premennych }
                        comp       : pointer;  { @TBfunc_p2: bool; pre porovnanie }
                        left,right : int       { hranice }
                       ): bool; far;

    function  QuickSort_Arr
                       (arr     : pointer;  { pole premennych }
                        comp    : pointer;  { @TBFunc_pi2: bool; pre porovnanie }
                        swap    : pointer;  { @TProc_pi2 pre prehodenie p1 a p2 }
                        left,
                        right   : int;      { hranice }
                        main_en : bool
                       ): bool;

    function  SortStr0 (arr: PPchars;
                        top: int
                       ): bool;


implementation

uses _Check, str0;


{ ----------------------------------------------------------------
  triedenie
  ----------- }

function  QuickSort(arr     : Pptrs;    { pole premennych }
                    comp    : pointer;  { @TBfunc_p2: bool; pre porovnanie }
                    swap    : pointer;  { @Tproc_vp2 pre prehodenie p1 a p2 }
                    left,
                    right   : int;      { hranice }
                    main_en : bool
                   ): bool;

    var   i,j     : int;
          x_val,p : pointer;
          res     : bool;

    begin
      QuickSort:= false;
      if (arr=nil) or (comp=nil) then Exit;

      res:= false;
      if left<right then
         begin
           i:= left; j:= right; x_val:= arr^[(left+right) div 2];
           repeat
             while (i<=right) and ((TBFunc_p2(comp)(arr^[i],x_val))) do inc(i);
             while (j>=left ) and ((TBFunc_p2(comp)(x_val,arr^[j]))) do dec(j);
             if i <= j then
                begin
                  if i < j then
                     begin
                       if swap<>nil then Tproc_cp2(swap)(arr^[j],arr^[i])
                       else begin p:= arr^[i]; arr^[i]:= arr^[j]; arr^[j]:= p end;
                       res:= true
                     end;
                  inc(i); dec(j);
                end
           until i > j;
           if left < j then
              begin
                res:= QuickSort(arr,comp,swap, left,j, main_en)  or res;
                if main_en then CheckProcesses0
              end;
           if i < right then
              begin
                res:= QuickSort(arr,comp,swap, i,right, main_en) or res;
                if main_en then CheckProcesses0
              end;
         end;
      QuickSort:= res
    end; { QuickSort }


function  QuickSort_IndArr
                  (ind   : Pints;    { pole indexov    }
                   arr   : Pptrs;    { pole premennych }
                   comp  : pointer;  { @TBfunc_p2: bool; pre porovnanie }
                   left,
                   right : int       { hranice }
                  ): bool;

    var   i,j,t : int;
          x_val : pointer;
          res,r : bool;

    begin
      QuickSort_IndArr:= false;
      if (ind=nil) or (arr=nil) or (comp=nil) then Exit;

      res:= false;
      if (left<right) then
         begin
           i:= left; j:= right;
           x_val:= arr^[ind^[(left+right) div 2]];
           repeat
             while (i<=right) and ((TBFunc_p2(comp)(arr^[ind^[i]],x_val))) do inc(i);
             while (j>=left ) and ((TBFunc_p2(comp)(x_val,arr^[ind^[j]]))) do dec(j);
             if i<=j then
                begin
                  if i < j then
                     begin
                       t:= ind^[i]; ind^[i]:= ind^[j]; ind^[j]:= t;
                       res:= true
                     end;
                  inc(i); dec(j);
                end
           until i > j;
           if left < j  then res:= QuickSort_IndArr(ind,arr,comp, left,j)  or res;
           if i < right then res:= QuickSort_IndArr(ind,arr,comp, i,right) or res
         end;
      QuickSort_IndArr:= res
    end; { QuickSort }


function  QuickSort_Arr
                   (arr     : pointer;  { pole premennych }
                    comp    : pointer;  { @TBFunc_pi2: bool; pre porovnanie }
                    swap    : pointer;  { @TProc_pi2 pre prehodenie p1 a p2 }
                    left,
                    right   : int;      { hranice }
                    main_en : bool
                   ): bool;

    var   i,j,x_val : int;
          res : bool;

    begin
      QuickSort_Arr:= false;
      if (comp=nil) or (swap=nil) then Exit;

      res:= false;
      if left<right then
         begin
           i:= left; j:= right; x_val:= (left+right) div 2;
           repeat
             while (i<=right) and TBFunc_pi2(comp)(arr, i,x_val) do inc(i);
             while (j>=left ) and TBFunc_pi2(comp)(arr, x_val,j) do dec(j);
             if i <= j then
                begin
                  if i<j then
                     begin
                       Tproc_pi2(swap)(arr, j,i);
                       res:= true
                     end;
                  inc(i); dec(j);
                end
           until i > j;
           if left < j then
              begin
                res:= QuickSort_Arr(arr, comp,swap, left,j,  main_en) or res;
                if main_en then CheckProcesses0
              end;
           if i < right then
              begin
                res:= QuickSort_Arr(arr, comp,swap, i,right, main_en) or res;
                if main_en then CheckProcesses0
              end;
         end;
      QuickSort_Arr:= res
    end; { QuickSort }


function comp_str0(p1,p2: pchar): bool; far;
   begin
     comp_str0:= strpas(p1)<strpas(p2)
   end;

function SortStr0(arr: PPchars; top: int): bool;
   begin
     SortStr0:= QuickSort(pptrs(arr), @comp_str0,nil{,@swap_str0}, 0,top, false)
   end;

end. { Sort }
