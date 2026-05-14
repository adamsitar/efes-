{ --------------------------
   TstreamPackedStrings
  --------------------------
}
constructor TstreamPackedStrings.Init;
      begin
        items:= 0;
        {$IFDEF NOEMS}
         poc:= 100;
         AllocMem(pointer(strm),SizeOf(PChar)*(poc));
        {$ELSE}
         strs.Init(1,1);
         offs.Init(1,1);
         is_ems:= (strs.is) and (offs.is)
        {$ENDIF}
      end;

destructor TstreamPackedStrings.Done;
     var   i : int;
     begin
      {$IFDEF NOEMS}
        if strm<>nil then
           begin
             for i:= 0 to poc-1 do strdispose(strm^[i]);
             DeallocMem (pointer(strm),SizeOf(PChar)*(poc));
             strm:= nil;
           end;
      {$ELSE}
       strs.Done;
       offs.Done
      {$ENDIF}
     end;


{procedure TstreamPackedStrings.seek_ind (ind: long);
    var   ioffs,ioffs1 : long;
          s : string;
    begin
     if is_ems and (ind<items) then
        begin
          if ind>0 then
             begin
               offs.seek((ind-1)*sizeof(long));
               offs.read(ioffs,sizeof(ioffs))
             end
          else ioffs:= 0;
          offs.seek(ind*sizeof(long));

          strs.seek(ioffs);
          ioffs1:= ioffs1-ioffs;
          strs.read(s[1],ioffs1);
          s[0]:= chr(byte(ioffs1))
        end;
     read:= s
   end;
}

function  TstreamPackedStrings.add (s: string): bool;
   var    ioffs,_ioffs : long;
          e,i: int;
   begin
     add:= false;

     {$IFDEF NOEMS}

      if (items<poc) and (MaxAvail>length(s)+1) then
         begin
           strm^[items]:= strpasnew(s);
           inc(items);
           add:= true;
         end;

     {$ELSE}

      if not is_ems then Exit;

      offs.reset;
      strs.reset;

      if items>0 then
         begin
          { zistenie offsetu, kde sa zapise string
          }
           offs.seek((items-1)*sizeof(long));
           offs.read(ioffs,sizeof(ioffs));
         end
      else ioffs:= 0;
      _ioffs:= ioffs;
      inc(items);

     { ulozenie velkosti
     }
      inc(ioffs,length(s));
      offs.seek((items-1)*sizeof(long));
      offs.write(ioffs,sizeof(ioffs));

     { ulozenie stringu;
       pretoze sa stava, ze prva polozka zoznamu sa neulozi spravne,
       kontroluje sa spravnost ulozenia a pripadne sa opakuje sa zapis;
       zatial som neprisiel na to preco
     }
      e:= 1;
      repeat
        strs.seek(_ioffs);
        strs.write(s[1],length(s));
        inc(e)
      until (e>3) or (read(items-1)=s);

      add:= true
     {$ENDIF}
   end;


function TstreamPackedStrings.read (ind: long): string;
   var   ioffs,ioffs1 : long;
         s : string;
   begin
     read:= '';

     {$IFDEF NOEMS}

      if (strm=nil) or (ind>=items) then Exit;
      read:= strpas(strm^[ind]);

     {$ELSE}

      if (not is_ems) or (ind>=items) then Exit;

      offs.reset;
      strs.reset;

      if ind>0 then
         begin
           offs.seek((ind-1)*sizeof(long));
           offs.read(ioffs,sizeof(ioffs))
         end
      else ioffs:= 0;

      offs.seek(ind*sizeof(long));
      offs.read(ioffs1,sizeof(ioffs1));

      strs.seek(ioffs);
      ioffs1:= N(minimum(ioffs1-ioffs,sizeof(string)-1));
      strs.read(s[1],ioffs1);
      s[0]:= chr(trunc(ioffs1));

      read:= s

     {$ENDIF}
   end;


procedure TstreamPackedStrings.truncate(ind: long);
    var   i,ioffs: long;
    begin
     {$IFDEF NOEMS}

      if (strm=nil) or (ind>=items) then Exit;
      for i:= ind to items-1 do strdispose(strm^[i]);
      items:= N(ind-1)

     {$ELSE}

      if (not is_ems) or (ind>=items) then Exit;

      offs.reset;
      strs.reset;

      if ind>0 then
         begin
           offs.seek((ind-1)*sizeof(long));
           offs.read(ioffs,sizeof(ioffs))
         end
      else ioffs:= 0;

      strs.seek(Maximum(1,ioffs));
      strs.truncate;
      strs.seek(Maximum(1,ioffs));

      offs.seek(Maximum(1,ind));
      offs.truncate;
      offs.seek(Maximum(1,ind));

      items:= N(ind-1)

     {$ENDIF}
    end;
