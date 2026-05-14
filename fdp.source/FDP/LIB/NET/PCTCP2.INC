{
  Parses a character string Internet address into numeric Internet address
}
function nm_prs_addr(_str: string): in_name;
   var   regs : registers;
         li   : in_name;
   begin
     _str:= _str+NULL;
     regs.ds:= seg(_str[1]);
     regs.dx:= ofs(_str[1]);
     regs.ah:= _NM_PRS_ADDR;
     if net_call(regs)<>-1 then
        begin
          li:= regs.dx;
          li:= (li shl 16) + (regs.ax);
          nm_prs_addr:= li { navrat. h. v dx:ax }
        end
     else nm_prs_addr:= 0
   end;


{
  Takes an Internet address structure and returns an ASCII string
  representing the address in dot notation
}
function inet_ntoa(_in: in_name): string;
   var   i   : int;
         a,p : string;
         b   : array [0..sizeof(in_name)-1] of byte;
   begin
     move(_in,b[0],sizeof(in_name));
     a:= '';
     for i:= 0 to sizeof(in_name)-1 do
       begin
         str(b[i],p);
         a:= a + p;
         if i < sizeof(in_name)-1 then a:= a + '.'
       end;
     inet_ntoa:= a
   end;
