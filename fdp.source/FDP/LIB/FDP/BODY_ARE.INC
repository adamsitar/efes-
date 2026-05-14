 function _AREAind_ (kod: string; A: PaArea; var Ai: TpArea): int;
    var   i : int;
    begin
      _AREAind_:= -1;
      kod:= _unique_area_code(kod);
      if (kod='') or (A=nil) then Exit;

      for i:= 0 to A^.pocet-1 do
        begin
          A^.read(i,Ai);
          if (kod=Ai.kod) then
             begin
               _AREAind_:= i;
               Exit
             end
        end
    end;
