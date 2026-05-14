{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TBuffer                                                  €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

constructor TBuffer.Init(_items,_data_size: word; _alloc_en: bool);
      var   i  : word;
            _p : pointer;
      begin
        inherited Init(_items,_data_size);
        alloc_en:= _alloc_en;
        s_save:= false; s_read:= false;
        zac:= 0; kon:= 0;
        pretiekol:= false;
        if not alloc_en then
           begin
             GetMem(_p,data_size);
             FillChar(_p^,data_size,0);
             for i:= 0 to items-1 do ap^[i]:= NewData(_p);
             FreeMem(_p,data_size)
           end;
      end;

destructor TBuffer.Done;
     var   i: word;
     begin
       for i:= 0 to items-1 do Del(i);
       if not alloc_en then for i:= 0 to items-1 do DispData(ap^[i]);
       inherited Done  { -> FreeMem(arr, items*item_size) }
     end;

{
  pri podmienke not alloc_en sa nesmu volat funkcie overlay-ovanych modulov !
}
function TBuffer.Add (p: pointer): int;
   var   _p : pointer;
         r  : bool;
         {l1,l2 : long;}
   begin
     Add:= -1;
     {l1:= zac; l2:= kon;}
     if (s_save) or (items=0) (*or (s_read and (abs(l1-l2)<2))ASI PROBLEM*) then Exit;

     s_save:= true;
     Del(kon);      { odmaze obsah, ak este nebol }
     _p:= nil;

     if ((kon+1) mod items = zac) then
        begin
          Del(zac);
          zac:= (zac+1) mod (items);
          pretiekol:= true
        end;

     if alloc_en then
        begin
          if (data_size{+max_avail} < maxavail) then
             begin
               _p:= NewData(p);
               if _p<>nil then ap^[kon]:= _p
             end
        end
     else begin
            _p:= p;
            move(p^,ap^[kon]^,data_size)
          end;
     if _p <> nil then
        begin
          Add:= kon;
          if items<>0 then kon:= (kon+1) mod (items);
          set_chg
        end;

     s_save:= false
   end;

procedure TBuffer.Del(ind: int);
   begin
     if alloc_en then
        begin
          if ap^[ind]<>nil then DispData(ap^[ind]);
          ap^[ind]:= nil
        end;
     set_chg
   end;

function TBuffer.is: bool;
   begin
     is:= (items>0) and (zac<>kon)
   end;


procedure TBuffer.set_chg;
    var   T: tick_counter;
    begin
      if alloc_en then inherited set_chg
      else is_chg:= true
    end;


procedure TBuffer.save(p: pointer);
    var   ind: int;
    begin
      ind:= Add(p)
    end;

procedure TBuffer._read(p: pointer);
    begin
      if p<>nil then move(ap^[zac]^, p^, data_size)
    end;

function TBuffer.read(p: pointer): bool;
   begin
     if is and (not s_read) then
        begin
          s_read:= true;
          asm cli end;
          _read(p);
          Del(zac);
          if items<>0 then zac:= (zac+1) mod (items);
          asm sti end;
          s_read:= false;
          read:= true
        end
     else read:= false
   end;

function TBuffer.readv(var p: pointer): bool;
   begin
     if is and (not s_read) then
        begin
          s_read:= true;
          asm cli end;
          _read(@p);
          Del(zac);
          if items<>0 then zac:= (zac+1) mod (items);
          asm sti end;
          s_read:= false;
          readv:= true
        end
     else readv:= false
   end;


{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TBuffer0                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

constructor TBuffer0.Init(_items: word);
      begin
        inherited Init(_items,sizeof(pchar),true)
      end;


function TBuffer0.Add (p: pointer): int;
   var   _p : pchar;
   begin
     Add:= -1; _p:= nil;
     _p:= NewData(p);
     if _p <> nil then
        begin
          Del(kon);
          ap^[kon]:= _p;
          if items<>0 then kon:= (kon+1) mod (items);
          set_chg;
          Add:= kon
        end
   end;

function TBuffer0.Add0 (p: pointer; size: word): int;
   var   _p : pointer;
   begin
     if (p<>nil) and (size>0) then
        begin
          if pbytes(p)^[size]<>0 then inc(size);
          GetMem(_p,size);
          Move(p^,_p^,size);
          pbytes(_p)^[size]:= 0;
          Add0:= Add(_p);
          FreeMem(_p,size)
        end

   end;

{
  p musi byt uz pchar !
}
function TBuffer0.NewData(p: pointer): pointer;
   var   _p : pchar;
   begin
     if (maxavail>StrLen(pchar(p))) then _p:= StrNew(pchar(p))
     else _p:= nil;
     NewData:= _p
   end;


procedure TBuffer0.DispData(var p: pointer);
    begin
      if p<>nil then StrDispose(pchar(p));
      p:= nil
    end;


procedure TBuffer0._read(p: pointer);
    begin
      pchar(p^):= StrNew(ap^[zac])
    end;

