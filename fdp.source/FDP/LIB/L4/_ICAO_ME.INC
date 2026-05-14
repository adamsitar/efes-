{$IFDEF FPL4}
 function  O_EXT.send_FPL  (var FPL: DFPL4): bool;
    begin
      send_FPL:= true
    end;

 function  O_EXT.send_CHG  (var FPL: DFPL4): bool;
    begin
      send_CHG:= true
    end;

 function  O_EXT.send_DLA  (var FPL: DFPL4): bool;
    begin
      send_DLA:= true
    end;

 function  O_EXT.send_CNL  (var FPL: DFPL4): bool;
    begin
      send_CNL:= true
    end;

 function  O_EXT.send_ACT  (var FPL: DFPL4): bool;
    begin
      send_ACT:= true
    end;

 function  O_EXT.send_EST  (var FPL: DFPL4): bool;
    begin
      send_EST:= true
    end;

 function  O_EXT.send_ALR  (var FPL: DFPL4; adr: string): bool;
    begin
      send_ALR:= true
    end;
{$ENDIF}
