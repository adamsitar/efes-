 function l4ch(ch: char): char;
    begin
      l4ch:= upcase(cs_ascii_char(mtkch_rus_to_lat(ch)))
    end;

 function l4str(s: string): string;
    begin
      l4str:= uni_str(mtks_rus_to_lat(s))
    end;

 function l4line(p: pchar): pchar;
    var   p_ : pchar;
          i  : int;
    begin
      p_:= ReplChar0 (p,setNL+setNL_,icao_NXIT,true);
      for i:= 0 to strlen(p_)-1 do p_[i]:= l4ch(p_[i]);
      l4line:= p_
    end;


 function  eq_l4_str(s1,s2: string): bool;
    begin
      eq_l4_str:= eq_str (mtks_rus_to_lat(s1),mtks_rus_to_lat(s2))
    end;


 function l4_format_s_(s: string; _nil: string): string;
    begin
      if cut_(s)<>'' then l4_format_s_:= s
      else l4_format_s_:= _nil
    end;


 function l4_format_s(s: string): string;
    begin
      l4_format_s:= l4_format_s_(s,rmk_NIL)
    end;

 function l4_format_p(p: pchar): pchar;
    begin
      if p<>nil then l4_format_p:= p
      else l4_format_p:= rmk_NIL
    end;

 function decode_l4_s(s: string; is_nil: bool): string;
    begin
      if cut_(s)<>rmk_NIL then decode_l4_s:= s
      else if is_nil then decode_l4_s:= ''
      else decode_l4_s:= ' '
    end;

 function decode_l4_p(p: pchar; is_nil: bool): pchar;
    begin
      if (p<>nil) and (strpas(p)<>rmk_NIL) then decode_l4_p:= p
      else if is_nil then decode_l4_p:= nil
      else decode_l4_p:= rmk_NIL
    end;
