 function _is_stata_PRN (PRN: PPRN; s: Pstring): bool; far;
    begin
      _is_stata_PRN:= (cut_(PRN^.stt)='') or __is_stat(PRN^.stt, s^)
    end;

