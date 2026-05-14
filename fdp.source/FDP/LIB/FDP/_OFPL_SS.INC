
{ najde plan podla identifikacie

function O_FPL.find_ssr(ssr: string): int;
   var   i,r : int;
   begin
     find_ssr:= -1;
     ssr:= uni_str(ssr);
     if (ssr='') or (ssr='N') or (p_ssr=nil) then exit;
     i:= 0; r:= -1;
     while (i<=top) do
       begin
         if (ssr = uni_str(TSFunc_p(p_ssr)(ap^[i]))) then
            if r<>-1 then begin r:= -2; break end
            else r:= i;
         inc(i)
       end;
     find_ssr:= r
   end;
}

function O_FPL.get_ssr(p: pointer): string;
   begin
     if (p_ssr<>nil) then get_ssr:= TSFunc_p(p_ssr)(p)
     else get_ssr:= ''
   end;


function O_FPL.is_ssr(ind: int; ssr: string): bool;
   var   ci,c,c0 : long;
         i : int;
         s : string;
   begin
     val(ssr,ci,i);
     if (p_ssr<>nil)  then
        begin
          s:= TSFunc_p(p_ssr)(ap^[ind]); s:= cut_(s);
          val(s,c,i)  
        end
     else c:= 0;
     if (p_ssr0<>nil) then
        begin
          s:= TSFunc_p(p_ssr0)(ap^[ind]); s:= cut_(s);
          val(s,c0,i)
        end
     else c0:= 0;
     is_ssr:=  ((c<>0) and (ci=c)) or ((c0<>0) and (ci=c0))
   end;


function O_FPL.ssr_in_use(idn,ssr: string): string;
   var   i  : int;
         is : bool;
   begin
     i:= 0; while (i<=top) do
      begin
        is:= (idn<>get_id(ap^[i])) and is_ssr(i,ssr);
        if is then break;
        inc(i)
      end;
     if i<=top then ssr_in_use:= get_id(ap^[i])
     else ssr_in_use:= ''
   end;
