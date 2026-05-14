constructor TsArray.Init(_max_items,_item_size: word; _is_eq: bool);
      begin
        ear.Init(_max_items,_item_size);
        sar:= nil;
        if ear.is_ems then _max_items:= 0
        else sar:= New(PStatic,Init(_max_items,_item_size));
        is_eq:= _is_eq;
        is_chg:= false;
        arr_chg:= 0;
      end;

destructor TsArray.Done;
     begin
       if sar<>nil then Dispose(sar,Done);
       sar:= nil;
       ear.Done;
     end;


procedure TsArray.set_chg;
    begin
      is_chg:= true;
      set_chg_ticks (arr_chg)
    end;


procedure TsArray.add (var p);
    begin
      if ear.is_ems then ear.add(p)
      else if sar<>nil then sar^.add(@p);
      set_chg
    end;

procedure TsArray.del (ind: int);
    begin
      if ind<0 then Exit;
      if ear.is_ems then ear.del(ind)
      else if sar<>nil then sar^.del(ind);
      set_chg
    end;


procedure TsArray.read (ind: long; var p);
    begin
      if ind<0 then Exit;
      if ear.is_ems then ear.read(ind,p)
      else if sar<>nil then sar^.get(ind,p)
    end;

procedure TsArray.write (ind: long; var p);
    begin
      if ind<0 then Exit;
      if ear.is_ems then ear.write(ind,p)
      else if sar<>nil then sar^.put(ind,p)
    end;


function TsArray.pocet: int;
   begin
     if ear.is_ems then pocet:= ear.items
     else if sar<>nil then pocet:= sar^.get_items
     else pocet:= 0;
   end;
