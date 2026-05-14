{ ----------------------------------------------------------------
  zobrazenie
  ----------- }

procedure TlstACC.List;
    var   pg: int;
    begin
      if (not PGroup(Owner)^.PIS) or (APP_GUI_INIT) then Exit;

      inherited List;
      if top=0 then btTitle^.Show;   { vlozenie listy - nie je sucastou inherited list }
      if is_scroll then scroll_st else scroll_cl
    end;

procedure TlstACC.list_reinit;
    var   riadkov,prev_lo,prev_hi: int;
    begin
      if not PGroup(Owner)^.PIS then Exit;

      prev_lo:= lo; prev_hi:= hi;
      riadkov:= sk_riadkov;
      if (lo>0) and (top<hi) then begin dec(hi); dec(lo); pos:= minimum(pos,hi) end
      else if (top < 0) or (top + 1 < riadkov-1) then Mail(Owner,rq_lstACC_zmensi, One,nil,0)
      else if (top + 1 > riadkov-1) then Mail(Owner,rq_lstACC_zvacsi, One,nil,0);

      {if (top + 1 > sk_riadkov-1) then Mail(Owner,rq_lstACC_zvacsi, One,nil,0);
       else if (top < 0) or (top + 1 < sk_riadkov-1) then Mail(Owner,rq_lstACC_zmensi, One,nil,0);
      }
      is_chg:= is_chg or (prev_lo<>lo) or (prev_hi<>hi);

      visible:= (top<>-1) or NDB_NULL;
      List
    end;


procedure TlstACC.reinit_(_page, _rdk: int);
    var   x,y,dy,ry : int;
          b : byte;
    begin
      hi:= Minimum(lo + (_page-1), hi);
      sb^.param(lo,hi,top,pos, false);

      rdk := _rdk;
      MoveRel(stlpec_xi(stl)+dxof_strip-dxof_stlpec-x0,0);
      y1 := MaxY - rdk*(item_dy+medzera);
      y0 := y1 - get_scroller_height(_page, item_dy, dyi, medzera);

      if lineSTRIP then begin dy:= dy_strip div 2 + 4; y:= y1-dy-3 end
      else begin y:= y1-dy_strip; dy:= dy_strip div 2 end;
      btTitle^.XY(x0,y, dx_strip,dy);
      if sb^.visible then sb^.hide;
      sb^.ReInit(sb^.x0,y0,0,btTitle^.y1-y0);

      if is_scroll then scroll_st else scroll_cl
    end;

{
  Zmena velkosti lastACC
}
procedure TlstACC.zmen_rozmer(o,volnych: int);
    var   hi_: int;
    begin
      if o<0 then hi:= Maximum(Maximum(lo,hi+o),0)
      else begin
             hi_:= hi;
             hi:= N(Minimum(Minimum(hi+o,top),hi+volnych));
             if hi<=hi_ then lo:= N(lo-o-(hi_-hi))
           end;
      reinit_(hi-lo+1, rdk)
    end;

{
  Zmena polohy lstACC
}
procedure TlstACC.zmen_polohu(o: int);
    var   r: TRegion;
          bp: bool; xlm,ylm: int;
    begin
      rdk:= Maximum(Minimum(rdk+o,max_rdk-1),0);
      set_region(x0,y0, x1,y1, r);
      reinit_(hi-lo+1, rdk);
      if APP_GUI_INIT then Exit;
      m_off (bp, xlm,ylm);
      if o<0 then
         begin
           if r.y0<y0 then FillWin(x0,r.y1,x1,y1, bg)
           else FillWin(x0,y0,x1,r.y0, bg)
         end;
      {$IFDEF BGI}
       MoveWin(r.x0,r.y0,r.x1,r.y1, x0,y0); { List; }
      {$ELSE}
       CopyView(0, r.x0,r.y0,r.x1,r.y1, 0,x0,y0);
      {$ENDIF}
      if r.y0<y0 then FillWin(x0,r.y0,x1,y0, bg)
      else FillWin(x0,y1,x1,r.y1, bg);
      m_on (bp, xlm,ylm);
    end;


{
  Zmena stlpca a riadku zoznamu
}
function TlstACC.zmen_stlpec: bool;
    var   x0m,y0m,x1m,y1m : int;
          Pxy  : TPoint;
          res  : bool;
    begin
      x0m:= x0; y0m:= y0; x1m:= x1; y1m:= y1 - item_dy div 2;
      _set_rectangle(x0m,y0m,x1m,y1m, mouse_status.stat.x,mouse_status.stat.y);
      res:= _move_by_drag(x0m,y0m,x1m,y1m);
      _restore_rectangle(x0m,y0m,x1m,y1m);
      if res then
         begin
           Pxy.x:= x0m; Pxy.y:= x1m;
           Move(Pxy,MailBox^,SizeOf(Pxy))
         end;
     end;

