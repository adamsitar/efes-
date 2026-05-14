{ -----------------------
   predefinovanie scroll,
   fcie umyselne prazdne pre potlacenie povodnych vlastnosti
}
function TEditors.is_changed: bool;
   begin
     is_changed:= false
   end;

procedure TEditors.renew;
    begin
    end;


{ -----------------------
   vypis...
}
procedure TEditors.item_cl(b: bool; var co,bk: byte);
    begin
      if viewer then begin bk:= bgv; co:= clv end
      else if b then begin bk:= bga; co:= cla end
      else begin bk:= bge; co:= cle end;
    end;


procedure TEditors.item_list(i, x,y: int; b: bool);
    var   co,bk: byte;
    begin
      item_cl(b, co,bk);
      WriteStr(x+dx_ed,y+dy_ed, pstring(r_s(i,0, false))^, co,bk)
    end;


procedure TEditors.List;
    var   bp: bool; co,bk: byte;
          xl,yl: int;
    begin
      item_cl(pos=rdk, co,bk);
      m_off(bp, xl,yl);
      if (not viewer) and (lo_prev=lo) and (hi_prev=hi) then
         hide_cursor(x0+dxi+dxioff,y0+dyi+dyioff, dx_ch,item_dy+medzera, 2,-2,
                     stl,rdk-lo_prev,
                     pchr(r_s(rdk,stl, true))^ {strana^[rdk][stl+1]},
                     co,bk
                    );
      inherited List;
      if (not viewer) then
         begin
           item_list_pos(pos);
           if (lo_prev=lo) and (hi_prev=hi) then
              begin
                item_cl(pos=rdk, co,bk);
                rdk:= N(pos);
                show_cursor(x0+dxi+dxioff, y0+dyi+dyioff,dx_ch, item_dy+medzera, 2,-2,
                            stl,rdk-lo,
                            pchr(r_s(rdk,stl, true))^ {strana^[rdk][stl+1]},
                            ins, co,bk
                           )
              end
         end;
      m_on(bp, xl,yl)
    end;
