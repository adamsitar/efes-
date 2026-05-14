{
 item       - polozka pre vlozenie
 arr        - pole pre polozku
 top        - posledna polozka
 items      - max.pocet poloziek
 item_size  - velkost polozky
}
function add_item(item, arr: pointer; var top: int; items, item_size: word): int;
   var   dst: pointer;
   begin
     if (top < items-1) then
        begin
          inc(top);
          add_item:= top;
          dst:= arr; IncPtr(dst, (top * item_size)); { src -> arr[ind+1] }
          Move(item^,dst^,item_size)
        end
     else add_item:= -1
   end;

{
 arr        - pole pre polozku
 ind        - index polozky pre zmazanie
 top        - posledna polozka
 item_size  - velkost polozky
}
procedure del_item(arr: pointer; ind: int; var top: int; item_size: word);
    var   src,dst: pointer;
    begin
      if (ind<0) or (ind>top) or (top<0) then Exit;
      dst:= arr; IncPtr(dst, ind * item_size); { dst -> arr[ind]   }
      src:= dst; IncPtr(src, item_size);       { src -> arr[ind+1] }
      Move(src^,dst^, item_size * (top-ind));
      Dec(top)
    end;

