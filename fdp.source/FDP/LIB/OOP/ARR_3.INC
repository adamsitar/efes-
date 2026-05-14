{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TArray                                                   €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TArray.Init(_items,_data_size: word;
                        _new_item,_format_item,_disp_item: pointer;
                        _inEMS: bool
                       );
      var   _items_ : int;
      begin
       {$IFDEF DEBUG}
        if _inEMS and ((_new_item<>nil) or (_disp_item<>nil)) then RunError('TArray.Init');
       {$ENDIF}
        if _inEMS then _items_:= 1 else _items_:= _items;
        inherited Init(_items_,_data_size, _new_item,_format_item,_disp_item);
        items:= _items;
        if _inEMS then E:= New(PEmsStream,Init(1,_items,_data_size))
        else E:= nil;
      end;


destructor TArray.Done;
     begin
       if E<>nil then
          begin
            Dispose(E,Done)
            items:= 1
          end;
       inherited Done
     end;


function TArray.NewData(p: pointer): pointer;
   begin
     if E<>nil then
        begin
!!          move(p^,ap^[0]^,data_size);
          NewData:= nil
        end
     else NewData:= inherited NewData(p)
   end;


procedure TArray.DispData(var p: pointer);
    begin
      if E<>nil then
         begin
         end
      else inherited DispData(p)
      p:= nil
    end;


{
  Novie s musia zaradit vzdy na koniec !
}
function TArray.Add(p: pointer): int;
   var   _p : pointer;
         r  : bool;
   begin
     Add:= -1;
     if (data_size{+max_avail} < maxavail) and (top < items-1) then
        begin
          _p:= NewData(p);
          if _p <> nil then
             begin
               inc(top);
               Add:= top;
               ap^[top]:= _p;
               changed := true
             end
        end
   end;


function TArray.Eq(ind: int; p: pointer): bool;
   var   _p,p2: pointer;
   begin
     if MaxAvail>data_size*2 then
        begin
          _p:= NewData(p);
          if _p<>nil then
             begin
               if ap^[ind]<>nil then
                  begin
                  { Vymenim obsah poloziek, pretoze v pripade, ak sa odkazujem
                    na adresu dat a pri Eq ich odalokujem, a v nejakej sucasne
                    zivej funkcii pracujucej prave stare data+buffer p2 s tymito
                    datami mam - nil - !
                  }
                    GetMem(p2,data_size);
                    Move(ap^[ind]^,p2^,data_size);
                    Move(_p^,ap^[ind]^,data_size);
                    DispData(p2);           { odalokovanie starych ap^[ind] dat a bufera, kam boli preseunute }
                    FreeMem(_p,data_size);  { odalokovanie buffera pre nove data, presunutych do ap^[ind] }
                    _p:= ap^[ind]
                  end
               else ap^[ind]:= _p;
               changed:= true
             end
        end
     else _p:= nil;
     Eq:= _p<>nil
   end;


procedure TArray.Del(ind: int);
   begin
     if (ind<0) or (top<0) then Exit;
     if ap^[ind]<>nil then DispData(ap^[ind]);
     Move(ap^[ind+1],ap^[ind],(top-ind)*sizeof(pointer));
     ap^[top]:= nil;
     changed := true;
     dec(top)
   end;
