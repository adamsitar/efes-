{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                                          Û
Û TStatic                                                  Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}
constructor TStatic.Init(_items,_item_size: word);
      begin
        top:= -1; items:= _items; item_size:= _item_size;
        GetMem(arr, items*item_size);
        FillChar(arr^, items*item_size,0);
        is_eq:= true;
        p_eq_items:= nil;
        format_item:= nil;
        is_chg:= false;
        arr_chg:= 0;
      end;

destructor  TStatic.Done;
     begin
       FreeMem(arr, items*item_size)
     end;


function TStatic.Add(p: pointer): int;
   var   ind: int;
   begin
     ind:= add_item(p, arr, top, items, item_size);
    {if ind>-1 then format_data()}
     Add:= ind;
     set_chg
   end;

function TStatic.Add2(p: pointer): int;
   begin
     if not (top < items-1) then Del(0);
     Add2:= Add(p)
   end;

procedure TStatic.Del(ind: int);
    begin
      if (ind<0) or (ind>top) or (top<0) then Exit;
      del_item(arr, ind, top, item_size);
      set_chg
    end;


procedure TStatic.Get (ind: long; var p);
    var   pi: pchars;
    begin
      fillchar(p,item_size,0);
      if (ind<0) or (ind>top) then Exit;
      pi:= arr; incptr(pointer(pi),item_size*ind);
      move(pi^,p,item_size);
    end;

procedure TStatic.Put (ind: long; var p);
    var   pi: pchars;
    begin
      if (ind<0) or (ind>top) then Exit;
      pi:= arr; incptr(pointer(pi),item_size*ind);
      move(p,pi^,item_size);
    end;


function TStatic.eq_data(pi, p: pointer): bool;
   begin
     if (p_eq_items<>nil) and (pi<>nil) and (p<>nil) then eq_data:= TBFunc_p2(p_eq_items)(pi, p)
     else eq_data:= false
   end;

procedure TStatic.format_data(p: pointer);
   begin
     if (format_item<>nil) then TProc_p(format_item)(p)
   end;

function TStatic.is_data: bool;
   begin
     is_data:= top>-1
   end;


procedure set_chg_ticks (var Tchg: tick_counter);
    var   T: tick_counter;
    begin
      T:= GetTicks;
      if T=Tchg then inc(Tchg) else Tchg:= T
    end;

procedure TStatic.set_chg;
    begin
      is_chg:= true;
      set_chg_ticks(arr_chg)
    end;


function TStatic.get_items: int;
   begin
     get_items:= top+1
   end;


{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                                          Û
Û TDynamic                                                 Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}
constructor TDynamic.Init(_items,_data_size: word{; _max_avail: long});
      begin
        inherited Init(_items,sizeof(pointer)); { item_size = SizeOf(pointer) }
        fillchar(arr^,item_size*items,0);       { vsetky = nil }
        data_size:= _data_size;
        ap:= arr;
        {max_avail:= _max_avail}
      end;

destructor TDynamic.Done;
     begin
       DelAll;
       inherited Done {FreeMem(arr, items*item_size)}
     end;


{ AK ITEM OBSAHUJE DALSIE POINTRE (PCHAR,...),
  POTOM MUSIA BYT PREDEFINOVANE
  NewData a DispData
}
function TDynamic.NewData(p: pointer): pointer;
   var   _p: pointer;
   begin
     _p:= nil;
     if (maxavail>data_size) then
        begin
          GetMem(_p,data_size);
          Move(p^,_p^,data_size);
          format_data(_p)
        end;
     NewData:= _p
   end;


procedure TDynamic.DispData(var p: pointer);
    begin
      if p<>nil then FreeMem(p,data_size);
      p:= nil
    end;


function TDynamic.find_data(p: pointer): int;
   var   i : int;
   begin
     find_data:= -1;
     if (p<>nil) then
        begin
          i:= 0; while (i<=top) and (not (eq_data(ap^[i],p))) do inc(i);
          if i<=top then find_data:= i
        end
   end;

procedure TDynamic.format_data_variables (p: pointer);
   begin
   end;

{ Nove sa musia zaradit vzdy na koniec
}
function TDynamic.Add(p: pointer): int;
   var   _p : pointer;
         i  : int;
         r  : bool;
   begin
     Add:= -1;

     if is_eq then i:= find_data(p)
     else i:= -1;

     if i>=0 then Eq(i,p)
     else if (data_size{+max_avail}<maxavail) and (top<items-1) then
        begin
          _p:= NewData(p);
          if _p<>nil then
             begin
               inc(top);
               Add:= top;
               ap^[top]:= _p;
               format_data_variables(ap^[top]);
               set_chg
             end
        end
   end;


function TDynamic.Eq(ind: int; p: pointer): bool;
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
               format_data_variables(ap^[ind]);
               set_chg
             end
        end
     else _p:= nil;
     Eq:= _p<>nil
   end;


procedure TDynamic.Del(ind: int);
   begin
     if (ind<0) or (top<0) then Exit;
     if ap^[ind]<>nil then DispData(ap^[ind]);
     Move(ap^[ind+1],ap^[ind],(top-ind)*sizeof(pointer));
     ap^[top]:= nil;
     set_chg;
     dec(top)
   end;


procedure TDynamic.DelAll;
   var    i: int;
   begin
     for i:= top downto 0 do Del(i)
   end;
