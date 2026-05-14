       {$IFDEF DEBUG}
         if poc>=max_items_debug then
            begin
              Assign(f,fname); Reset(f); p:= ''; i:= -1;
              repeat
                ReadLn(f,s); s:= ReplChar(s, [#0..#31], ' '); p:= s; u:= s; s:= cut_(s);
                if (s[1] in setKomen) or ((i=-1) and (s='')) or (not is_to_add(s)) then continue;
                inc(i);
                if pos=lst_cely_riadok then u:= cut_(delchar(u,setTitle))
                else if pos=lst_cely_riadok_ then u:= u
                else u:= delchar(cut_(GetStr(u,1, setKomen)),setTitle);
              until Eof(f) or (i=ind);
              if i=ind then get:= u else get:= '';
              Close(f)
            end
         else
       {$ENDIF}

max_items_debug
begin
       {$IFDEF DEBUG}
         if poc>=max_items_debug then
            begin
              Assign(f,fname); Reset(f); p:= ''; i:= -1;
              repeat
                ReadLn(f,s); s:= ReplChar(s, [#0..#31], ' '); p:= s; u:= s; s:= cut_(s);
                if (s[1] in setKomen) or ((i=-1) and (s='')) or (not is_to_add(s)) then continue;
                inc(i);
                if pos=lst_cely_riadok then u:= cut_(delchar(u,setTitle))
                else if pos=lst_cely_riadok_ then u:= u
                else u:= delchar(cut_(GetStr(u,1, setKomen)),setTitle);
              until Eof(f) or (i=ind);
              if i=ind then get:= u else get:= '';
              Close(f)
            end
         else
       {$ENDIF}
 const max_items_debug = 100;

             {$IFDEF DEBUG} {$IFDEF NOEMS}
              if poc>=max_items_debug then begin s:= ''; u:= '' end;
             {$ENDIF} {$ENDIF}
      {$IFDEF DEBUG} {$IFDEF NOEMS}
       if poc<max_items_debug then
      {$ENDIF} {$ENDIF}
      {$IFDEF DEBUG} {$IFDEF NOEMS}
       if poc<max_items_debug then
      {$ENDIF} {$ENDIF}
