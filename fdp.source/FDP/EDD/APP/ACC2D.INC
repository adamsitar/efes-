function TlstACC.get_x: int;
   begin
     get_x:= x0
   end;

function TlstACC.get_yi(i: int): int;
   begin
     get_yi:= y1 - (i-lo + 2{btTitle})*(item_dy+medzera)
   end;


procedure TlstACC.item_list(i, x,y: int; b: bool);
    begin
      if APP_GUI_INIT then Exit;
      with FPLs^[i]^ do iFPL^.strip(ind, x,y+2, false);
    end;

procedure TlstACC.item_erase(i: int);
    var   od: int;
    begin
      if APP_GUI_INIT then Exit;
      {
      od:= i-1-hi; if od<1 then od:= 1;
      FillWin(x0, y0, x1, y0+(hi-i+1)*dy, bg) FillWin(x0, y1 - od*dy, x1, y1-dy, bg)
      }
    end;


function TlstACC.pl_riadkov: int;
   var   pocet: int;
   begin
     if top<0 then
        if not NDB_NULL then pocet:= 0
        else pocet:= 1
     else pocet:= hi-lo+1 + 1{NDB};
     pl_riadkov:= pocet
   end;

{
  inverzna fcia ku get_scroller_height
}
function TlstACC.sk_riadkov: int;
   var   pocet: int;
   begin
     {
     if (top<0) then
        if not TABLET_NULL then pocet:= 0
        else pocet:= 1
     else}
     if {TABLET_NULL or} visible then pocet:= (y1-y0 - 2*dyi + medzera) div (item_dy+medzera)
     else pocet:= 0;
     sk_riadkov:= pocet
   end;
