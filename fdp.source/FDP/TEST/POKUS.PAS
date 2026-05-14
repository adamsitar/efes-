{$I comp.h}

uses  ovr,bios, typedef, math, str0, crt, msg, io, sets, keyb, mem
      {I unit_net.h,};

var s : string;
    cislo_tmp_packet : long;
    {N: PNET;}
    nd : int;
    pomb : bool;


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
      get_lines_i_:= lines {getPstritems(p,setNL+setNL_)}
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
      get_line_i:= s {getPstr(p,i,setNL+setNL_)}
    end;


 function get_data_lines_i_ (p: pchar): int;
    var   r,i : int;
    begin
      r:= get_lines_i_(p);
      while (r>0) and (cut_(get_line_i(p,r))='') do dec(r);
      get_data_lines_i_:= r
    end;


begin
  clrscr;

  {write(get_lines_i_(nil)); writeln(', "'+get_line_i (nil,1)+'"');

  s:= #0;
  write(get_lines_i_(@s[1])); writeln(', "'+get_line_i (@s[1],1)+'"');

  s:= #13#10#13#10#13#10#0;
  write(get_lines_i_(@s[1])); writeln(', "'+get_line_i (@s[1],1)+'"');}

  s:= '1x'#0;
  write(get_lines_i_(@s[1])); writeln(', "'+get_line_i (@s[1],1)+'"');

  s:= #13#10'2x'#13#10'444'#0;
  write(get_lines_i_(@s[1])); writeln(', "'+get_line_i (@s[1],3)+'"');

  s:= '3x'#13#10' '#0;
  write(get_lines_i_(@s[1])); writeln(', "'+get_line_i (@s[1],2)+'"');

  s:= '4x'#13#10#13#10' mmm '#0;
  write(get_lines_i_(@s[1])); writeln(', "'+get_line_i (@s[1],3)+'"');

  s:= '5x'#13#10'xcccc'#13#10' bb '#13#10' 44'#0;
  write(get_lines_i_(@s[1])); writeln(', "'+get_line_i (@s[1],1)+'"');
  write(get_lines_i_(@s[1])); writeln(', "'+get_line_i (@s[1],2)+'"');
  write(get_lines_i_(@s[1])); writeln(', "'+get_line_i (@s[1],3)+'"');
  write(get_lines_i_(@s[1])); writeln(', "'+get_line_i (@s[1],4)+'"');

  s:= '6X'#13#10#0;
  write(get_lines_i_(@s[1])); writeln(', "'+get_line_i (@s[1],1)+'"');


 {InitBGI; _info ('\xe\d\TMP\sprlam.@@@','');}

 {s:= '\xe\d\prs\aup\27-09-99.aup';

 NET_init (New(PNET,Init));
 NETdistribute_file ([FDP],[],[],spr_AUP,s,inf_FUA,net_flag_SEND,false,true,true);
 NETsend_file ('S2',spr_AUP,s,inf_FUA,net_flag_SEND,false,true,true);
 }
end.

