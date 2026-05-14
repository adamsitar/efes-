 function THelp.items : word;
    begin
      items:= top+1
    end;

 function THelp.put (riadok: string; ind: int): bool;
    begin
      put:= false;
      if   {$IFDEF HELP_NOEMS} (strm=nil)
           {$ELSE}        ((stre=nil) or (not stre^.is_ems))
           {$ENDIF}
        or (ind>=riadkov) then Exit;

      {$IFDEF HELP_NOEMS}
       strm^[ind]:= StrPasNew(riadok);
       put:= true;
      {$ELSE}
       stre^.items:= ind;
       stre^.add(riadok);
       put:= true;
      {$ENDIF}
    end;

 function THelp.get (ind: int): string;
    begin
      get:= '';
      if   {$IFDEF HELP_NOEMS} (strm=nil)
           {$ELSE}        ((stre=nil) or (not stre^.is_ems))
           {$ENDIF}
        or (ind<0) or (ind>=riadkov) then Exit;

      {$IFDEF HELP_NOEMS}
       get:= strpas(strm^[ind]);
      {$ELSE}
       get:= stre^.read(ind);
      {$ENDIF}
    end;


 function  THelp.key_find  (var f: text; key: string; _title: pstring): bool;
    var    s: string;
    begin
     { najdenie ostavca pre key
     }
      key_find:= true;
      ResetIOError;
      Reset(f);
      if key<>'' then
         begin
           s:= ''; key:= cs_ascii_str(key);
           while (not Eof(f)) and (system.pos(SOH+key+EOH,s)=0) do readln(f,s);
           if Eof(f) then key_find:= false
           else if _title<>nil then _title^:= getstr(s,2,[EOH])
         end;
    end;

 function  THelp.key_alloc (var f: text; key: string): bool;
    var    s,t : string;
           res : bool;
    begin
      riadkov:= 0; res:= false;
      s:= '';
      while     (not Eof(f))
            and ((SOH=NULL) or (system.pos(SOH,s)=0))
            and ((EOT=NULL) or (system.pos(EOT,s)=0))
      do begin
           {$IFDEF HELP_NOEMS} {$IFNDEF _DPMI}
             if (riadkov>=hlp_max_lines) then break;
            {$ENDIF} {$ENDIF}
            t:= cut_(s);
            if not ((not comment_en) {and (t<>'')} and (t[1]=';')) then inc(riadkov);
            readln(f,s);
         end;

      if (riadkov>0) then
         begin
           top:= riadkov-1;
           {$IFDEF HELP_NOEMS}
            res:= AllocMem(pointer(strm),SizeOf(PChar)*(top+1));
            if res then fillchar(pbytes(strm)^,SizeOf(PChar)*(top+1),0);
           {$ELSE}
            stre:= New(PstreamPackedStrings,Init);
            res:= stre^.is_ems;
           {$ENDIF}
         end;

      key_alloc:= res;
    end;

 procedure THelp.key_read  (key: string; var _title: string);
     var   f : text;
           j,p,_top : int;
           s,t : string;
           res : bool;
     begin
       if top>-1 then key_release;
       if FExists(fn)<>0 then Exit;

       InfoCakaj('Help', msgREAD);
       ResetIOError;
       Assign(f,fn); Reset(f);

       if key_find(f,key,@_title) and key_alloc(f,key) then
          begin
            key_find (f,key,nil);

            s:= ''; _top:= -1;
            while (not Eof(f)) and (_top<top) do
              begin
                readln(f,s); t:= cut_(s);
                if (not comment_en) {and (t<>'')} and (t[1]=';') then continue;
                if    ((SOH<>NULL) and (system.pos(SOH,s)<>0))
                   or ((EOT<>NULL) and (system.pos(EOT,s)<>0))
                   then break;

               { nacitanie a konverzia prislusnej casti riadku
               }
                 p:= system.pos(hlp_sipka_vpravo,s);
                 if p<>0 then s[p]:= chr($1A);
                 if not is_comment then
                    begin
                      s:= getstr(s,1,setKomen);
                      if (is_comment0) and (t<>'') and (t[1]=';') then s:= ';'+s;
                    end;

                 inc(_top);
                 {$IFDEF HELP_NOEMS}
                  if _top=hlp_max_lines-1 then s:= 'Continued...';
                 {$ENDIF}
                 j:= 1; while put(s,_top) and (s<>get(_top)) and (j<=3) do inc(j);
               end;
           end;

       Close(f);
       ResetIOError;
       InfoCakaj_zatvor
     end;

 procedure THelp.key_release;
     var   i : int;
     begin
      {$IFDEF HELP_NOEMS}
       if strm<>nil then
          begin
            for i:= 0 to top do strdispose(strm^[i]);
            DeallocMem (pointer(strm),SizeOf(PChar)*(top+1));
            strm:= nil;
          end;
      {$ELSE}
       if stre<>nil then Dispose(stre,Done);
       stre:= nil;
      {$ENDIF}
      riadkov:= 0;
      top:= -1;
     end;
