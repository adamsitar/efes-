{
procedure pneterror(s: string);
    begin
      if neterrno > MAX_PCTCP_ERR then write(s,': unknown err (',neterrno,')')
      else write(s,': ',neterr_list[neterrno]);

      if (neterrno<>NET_ERR_NOMEM) and (netsuberrno<>0) and (netsuberrno<MAX_PCTCP_SUBERR) then
        write(': ',netsuberr_list[netsuberrno]);
     writeln;
    end;
}


procedure pctcp_cleanup;
   var    reg: Registers;
   begin
    {$IFDEF DEBUG_EXIT} writeln('PCTCP'); {$ENDIF}
     net_releaseall;
     {
     if _dos_break then
        begin
          reg.ax:=$3301;
          reg.dl:=1;
          intr($21,reg);
        end;
     }
   end;


function vec_search: int;
   var   regs    : Registers;
         vec     : pointer;
         int_vec : ^pointer;
         _seg    : word;
         _off    : word;
         pc      : pchar;
         i       : Integer;

   function check_match(s: pchar): Integer;
      var   ps: array[0..10] of char;
            ss: string;
      begin
        {strlcopy(ps,s,6);
        ss:=strpas(ps);
        if ss=match then check_match:=1
        else check_match:=0}
        ss:= match;
        if memcomp (s,@ss[1],length(match)) then check_match:= 1
        else check_match:= 0
      end;

   begin
     if not initialized then vec_search:= 0
     else vec_search:= int_TCP_IP;
     if initialized then Exit;

     for i:= FIRST_VEC to LAST_VEC do
       begin
         int_vec:= Ptr($0,i SHL 2);
         vec := int_vec^;
         pc:= IncPtr(vec,3);

         if check_match(pc) = 1 then
            begin
              int_TCP_IP:= i;
              vec_search:= i;
              initialized:= true;
              { regs.ax:= $3300;
                intr($21,regs);
                if regs.dl = 1 then
                   begin
                     _dos_break:= TRUE;
                     regs.ax:= $3301;
                     regs.dl:= 0;
                     intr($21,regs);
                end;
              }
              break
            end
         end
   end;


function _find_vec: int;
   var   vecnum: int;
   begin
     vecnum:= vec_search;
     if vecnum<>0 then _find_vec:= vecnum
     else RunError('PCTCP resident module is not installed.')
   end;
