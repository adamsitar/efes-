
function mtkch_rus_to_lat(ch: char): char;
   var   i,r : int;
   begin
     {ch:= upcase(ch);}
     if ch in ['€'..'Ÿ'] then
        begin
          r:= rdk_MTK_2_A36; i:= 0; while (i<max_MTK_2_znk) and (MTK_2[r,i]<>ch) do inc(i);
          if i>=max_MTK_2_znk then
             begin
               r:= rdk_MTK_2_DIG; i:= 0; while (i<max_MTK_2_znk) and (MTK_2[r,i]<>ch) do inc(i)
             end;
          if i<max_MTK_2_znk then ch:= MTK_2[rdk_MTK_2_LAT,i]
        end;
     mtkch_rus_to_lat:= upcase(ch)
   end;

function mtks_rus_to_lat(s: string): string;
   var   i : int;
   begin
     for i:= 1 to length(s) do s[i]:= mtkch_rus_to_lat(s[i]);
     mtks_rus_to_lat:= s
   end;

function mtkp_rus_to_lat(p: pchar; alloc: bool): pchar;
   var   lp  : pchar;
         i   : int;
   begin
     if alloc then lp:= strnew(p) else lp:= p;
     if lp<>nil then for i:= 0 to strlen(lp)-1 do lp[i]:= mtkch_rus_to_lat(lp[i]);
     mtkp_rus_to_lat:= lp
   end;

