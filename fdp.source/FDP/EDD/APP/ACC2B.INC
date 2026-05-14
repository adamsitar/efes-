function TlstACC.is_scroll: bool;
   begin
     is_scroll:= (lo>0) or (hi<top) {or pom}
   end;


procedure TlstACC.scroll_cl;
    begin
      if not visible then Exit;

      btTitle^.scroll_cl;
      if active then PwinACC(Owner)^.vypni
    end;

procedure TlstACC.scroll_st;
    begin
      if not visible then Exit;

      btTitle^.scroll_st;
      if active then sb^.show
    end;
