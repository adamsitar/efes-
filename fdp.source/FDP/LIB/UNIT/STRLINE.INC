{ Funkcie pre spracovanie riadkov stringu nepouzivaju
  standartne fcie str0, pretoze tu ak nasleduju oddelovace
  za sebou, znamena to dalsie pole a nie oddelovac
  v takomto tvare, ako v uvedenom pripade (napr. csa--233-3-);

  ! V novom projekte OX uz pouzit tento algoritmus pre vsetky
    polia, stary zahodit...
}

{ vrati pocet riadkov
}
 function get_lines_i_ (p: pchar): int;
    var   pi,p1,p2 : pchar;
          lines : word;
    begin
      lines:= 0;
      pi:= p;
      while pi<>nil do
        begin
          inc(lines);
          p1:= strpos(pi,kbNL); p2:= strpos(pi,kbNL_);
          if (p1<>nil) and ((p1<p2) or (p2=nil)) then begin pi:= p1; incptr(pointer(pi),length(kbNL)) end
          else if (p2<>nil) then begin pi:= p2; incptr(pointer(pi),length(kbNL_)) end
          else begin
                 if strlen(pi)=0 then dec(lines);
                 break
               end
        end;
      get_lines_i_:= lines
    end;

 function get_data_lines_i_ (p: pchar): int;
    var   r,i : int;
    begin
      r:= get_lines_i_(p);
      while (r>0) and (cut_(get_line_i(p,r))='') do dec(r);
      get_data_lines_i_:= r
    end;


{ ukaze na zaciatok riadku
}
 function find_line_i (p: pchar; line: int): pchar;
    var   p0,pi,p1,p2 : pchar;
          i,riadok : int;
          s : string;
    begin
      s:= '';
      riadok:= 0; pi:= p; p0:= pi;
      while (pi<>nil) and (riadok<line) do
        begin
          inc(riadok);
          p0:= pi; p1:= strpos(pi,kbNL); p2:= strpos(pi,kbNL_);
          if (p1<>nil) and ((p1<p2) or (p2=nil)) then begin pi:= p1; incptr(pointer(pi),length(kbNL)) end
          else if (p2<>nil) then begin pi:= p2; incptr(pointer(pi),length(kbNL_)) end
          else begin
                 if strlen(pi)=0 then dec(riadok);
                 break
               end
        end;
      if riadok=line then find_line_i:= p0
      else find_line_i:= nil
    end;

{ vrati riadok c...
}
 function get_line_i (p: pchar; line: int): string;
    var   p1,p2, p11,p12 : pchar;
          i : int;
          s : string;
    begin
      s:= '';
      p1:= find_line_i(p, line);
      p11:= strpos(p1,kbNL); p12:= strpos(p1,kbNL_);
      if (p11<>nil) and ((p11<p12) or (p12=nil)) then p2:= p11
      else if (p12<>nil) then p2:= p12
      else p2:= nil;
      if p1<>nil then
         begin
           if p2<>nil then i:= p2-p1
           else i:= strlen(p1);
           i:= minimum(i,sizeof(s)-1); s[0]:= chr(i);
           move(p1^,s[1],i)
         end;
      get_line_i:= s
    end;

 {function get_lines_i_ (p: pchar): int;
    var   i : int;
    begin
      get_lines_i_:= getPstritems(p,setNL+setNL_)
    end;

 function get_data_lines_i_ (p: pchar): int;
    var   r,i : int;
    begin
      r:= get_lines_i_(p);
      while (r>0) and (cut_(get_line_i(p,r))='') do dec(r);
      get_data_lines_i_:= r
    end;

 function get_line_i (p: pchar; i: int): string;
    begin
      get_line_i:= getPstr(p,i,setNL+setNL_)
    end;
 }

 function code_line_i_ (p: pchar; od,po: int; odd: string): string;
    var   i : int;
          s : string;
    begin
      po:= minimum(get_lines_i_(p),po);
      s:= ''; for i:= od to po do s:= s + get_line_i(p,i) + odd;
      code_line_i_:= format_s_(s)
    end;

{ function code_line_i_nl (p: pchar; i: int; odd: string): string;
    var   s : string;
    begin
      s:= getPstr(p,i,setNL+setNL_);
      if i>1 then s:= odd+s;
      code_line_i_nl:= s
    end;
}
 function code_line_i (p: pchar; od,po: int): string;
    begin
      code_line_i:= code_line_i_ (p, od,po, kbNL_);
    end;


 {function decode_line_i_ (p: pchar): pchar;
    var   pi: pchar;
    begin
      pi:= p;
      repeat
        pi:= strpos(pi,kbNL_);
        if pi<>nil then
           begin
             pi^:= #13;
             incptr(pointer(pi),1);
             pi^:= #10;
             incptr(pointer(pi),1)
           end;
      until pi=nil;
      decode_line_i_:= p
    end;}

 function decode_line_i (s: string; p: pchar; odd: TCharSet): pchar;
    var   d: pchar;
    begin
      {odd:= odd+setNL+setNL_;
      k:= getstritems(s,odd);
      for i:= 1 to k do p:= StrNPCopy(p, getstr(s,i,odd)+kbNL, true,true);}
      {s:= s+NULL; d:= @s[1];
      d:= decode_line_i_(d);
      p:= StrNCopy(p,d,true,false);}
      p:= StrNPCopy(p,s,true,true);
      decode_line_i:= p
    end;

 function decode_line_ip (d: pchar; p: pchar; odd: TCharSet): pchar;
    begin
      {odd:= odd+setNL+setNL_;
      k:= getPstritems(d,odd);
      for i:= 1 to k do p:= StrNPCopy(p, getPstr(d,i,odd)+kbNL, true,true);}
      {d:= decode_line_i_(d);}
      p:= StrNCopy(p,d,true,false);
      decode_line_ip:= p
    end;



 {function code_lines_array(var dst,src: pchar; odd: string): pchar;
    var   r,i : int;
    begin
      dst:= StrNPCopy(dst,icao_ARR,true,true);
      r:= get_data_lines_i_(src);
      if r>0 then for i:= 1 to r do pch:= StrNPCopy(pch,code_line_i_nl(src,i,kbNL),true,true)
      else pch:= StrNPCopy(pch,icao_NXIT, true,true);
      code_lines_array:= src
    end;}


 function eq_lines(p1,p2: pchar): bool;
    var   i,r: int;
    begin
      eq_lines:= false;
      r:= get_data_lines_i_(p1);
      if r<>get_data_lines_i_(p2) then Exit;
      i:= 1; while (i<=r) and (get_line_i(p1,i)=get_line_i(p2,i)) do inc(i);
      eq_lines:= i>r
    end;
