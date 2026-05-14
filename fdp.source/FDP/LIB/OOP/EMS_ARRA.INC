constructor TstreamArray.Init(_max_items,_item_size: word);
      begin
        max_items:= _max_items;
        item_size:= _item_size;
        pocet:= 0;

        getmem(ibuff,item_size);
        fillchar(ibuff^,item_size,0);

        abuff.Init(1,max_items*item_size);
        is_ems:= (abuff.status=0) and (abuff.status=0)
      end;

destructor TstreamArray.Done;
     begin
       abuff.Done;
       freemem(ibuff,item_size)
     end;


procedure TstreamArray.add (var p);
    begin
      if (not is_ems) or (pocet=max_items) then Exit;

      abuff.seek((pocet)*item_size);
      abuff.write(p,item_size);
      inc(pocet)
    end;

procedure TstreamArray.del (ind: int);
    var   i: int;
    begin
      if (not is_ems) or (ind<0) or (ind>pocet) then Exit;

      for i:= ind to pocet-2 do
        begin
          abuff.seek((i+1)*item_size);
          abuff.read(ibuff^,item_size);
          abuff.seek((i)*item_size);
          abuff.write(ibuff^,item_size);
        end;
      dec(pocet);
    end;


procedure TstreamArray.read (ind: long; var p);
    begin
      fillchar(p,item_size,0);
      if (not is_ems) or (ind<0) or (ind>=pocet) then Exit;

      move(ibuff^,p,item_size);
      abuff.seek((ind)*item_size);
      abuff.read(p,item_size);
    end;


procedure TstreamArray.write (ind: long; var p);
    begin
      if (not is_ems) or (ind<0) or (ind>=pocet) then Exit;

      move(p,ibuff^,item_size);
      abuff.seek((ind)*item_size);
      abuff.write(p,item_size);
    end;


function TstreamArray.items: int;
   begin
     items:= pocet
   end;
