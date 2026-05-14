 function  idn_FPL4 (FPL: PFPL4): string;
    begin
      if FPL<>nil then idn_FPL4:= getstr(FPL^._7,1,[icao_NXT])
      else idn_FPL4:= ''
    end;

 function ssr_FPL4(FPL: PFPL4): string;
    begin
      if FPL<>nil then ssr_FPL4:= getstr(FPL^._7,2,[icao_NXT])
      else ssr_FPL4:= ''
    end;

{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   identifikacia / typ planu(letu)
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
 function is_FPL4M (FPL: PFPL4): bool;
    var   _8a,_8b: char;
    begin
      decode_l4_8 (FPL^._8, _8a,_8b);
      is_FPL4M:= _8b in set_8bM
    end;

 function is_FPL4O (FPL: PFPL4): bool;
    var   _8a,_8b: char;
    begin
      decode_l4_8 (FPL^._8, _8a,_8b);
      is_FPL4O:= false {$IFNDEF OPL} or (_FPL4_XG_ENABLE and (_8b in set_8bO)) {$ENDIF}
    end;

 function is_FPL4MIL(FPL: PFPL4): bool;
    begin
      is_FPL4MIL:= (FPL<>nil) and (is_FPL4M(FPL) or is_FPL4O(FPL))
    end;
