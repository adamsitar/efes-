{$IFDEF PRN}
 function TPLAN.get_printed (p: pointer): bool;
    begin
      get_printed:= false
    end;

 procedure TPLAN.set_printed (p: pointer; was: bool);
    begin
      if (p_PRN=nil) or (p_PRN^) then uloz(p)
    end;


 function TPLAN.tlac_en: bool;
    begin
      {$IFDEF PRN} tlac_en:= (is_PRN and ((p_PRN=nil) or (p_PRN^)))
      {$ELSE}      tlac_en:= false
      {$ENDIF}
    end;

 function TPLAN.tlac(p: pointer; vzdy: bool): bool;
    var   bres: bool;
    begin
      bres:= false;
      {$IFDEF PRN}
        if vzdy or tlac_en then
           begin
             bres:= TBFunc_p(p_print)(p)
           end;
       { IFDEF SECTORS}
        if bres then set_printed(p,true)
       { ENDIF};
      {$ENDIF}
      tlac:= bres
    end;
{$ENDIF}
