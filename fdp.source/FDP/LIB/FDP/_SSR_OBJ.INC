 constructor O_SSRs.Init;
       begin
         inherited Init (max_ssr_records,sizeof(t_ssr_record),@new_SSR,nil,@disp_SSR);
         p_eq_items:= @eq_SSR;
         ssr_a:= p_ssr_records(ap)
       end;


 function O_SSRs.najdi(code: string): int;
    var   ssr : t_ssr_record;
    begin
      fillchar(ssr,sizeof(ssr),0);
      ssr.code:= code;
      najdi:= find_data(@ssr);
    end;
