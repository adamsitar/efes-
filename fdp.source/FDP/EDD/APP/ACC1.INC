constructor TtitACC.Init(_Owner: PGroup; x,y, dx,dy: int; _title: string);
      begin
        inherited Init(_Owner, x,y,dx,dy, kbNoKey,cmDefault,_title,1,clItem,clItem);
        kbAct := kbEnter;
        local_ev := false;
        is_scrollable := false;
        sort_by := sort_imp
      end;


procedure TtitACC.HandleEvent(var _Event: TEvent);
    var   x0t,x1t : int;
    begin
      if not visible then Exit;

      cmXXXX:= cmDefault;
      if isClicked(_Event) then
         begin
           x0t:= x0+Centruj(x1-x0, StrLen(title)*dx_ch);
           x1t:= x0t+StrLen(title)*dx_ch;
          {$IFNDEF VER_3.0}
           if inRectangle(_Event.M.x+(-Moff[_Event.M.curs].x),_Event.M.y+(-Moff[_Event.M.curs].y), x0t,y0,x1t,y1)
                then cmXXXX:= cm_NDB_move
           else if inRectangle(_Event.M.x+(-Moff[_Event.M.curs].x),_Event.M.y+(-Moff[_Event.M.curs].y),
                               x1-dx_mnu_zozstrip,y0,x1,y1
                              )
                then cmXXXX:= cm_NDB_set
           else
          {$ENDIF}
                if is_scrollable then cmXXXX:= cm_NDB_view
         end;
      inherited HandleEvent(_Event); { prepusti command ....}
    end;


procedure TtitACC.Draw;
    var   x : word;
          s : string;
          c : byte;
          bp: bool; xlm,ylm: int;
    begin
      if APP_GUI_INIT or (not visible) then Exit;

      m_off (bp, xlm,ylm);
      Button;
      {on_off(x0,y0+2,x1,y1-2, b1,b2,  thick: byte; on: TbtStat);}
      if not lineSTRIP then bgigraph.button(x0+1,y0+2,x1{-1},y1-2, grBUTTON_COLOR[btON], btSmall,btON);
      {$IFDEF SPEA} if stat=btON then SetBkColor(grBUTTON_COLOR[btON]) else SetBkColor(clBUTTON_COLOR); {$ENDIF}
      if (Owner<>nil) and (PView(Owner)^.Active) then c:= clLstAct
      else if is_scrollable then  c:= clLstSc
      else c:= clLstItem;
      WriteCentr(x0,x1,y0,y1, StrPas(title), c);
      {$IFNDEF VER_3.0}
       if (sort_by<>sort_imp) and (sort_by<>STRIP_SORT) then
          WriteStr(x1-20, (y1+y0+dy_bt) shr 1, Text_sort_strip[sort_by],clBUTTON_COLOR+5,grBUTTON_COLOR[btON]);
      {$ENDIF}
      m_on (bp, xlm,ylm);
    end;  { TButton.Draw }


procedure TtitACC.scroll_cl;
    var   s: string;
          i: int;
    begin
      is_scrollable:= false;
      s:= cut_(strpas(title));
      i:= pos(moreFPL,s);
      if i>0 then
         begin
           new_title(copy(s,1,i-1),true);
           {Draw}
         end
    end;

procedure TtitACC.scroll_st;
    var   s: string;
          i: int;
    begin
      is_scrollable:= true;
      s:= strpas(title);
      if pos(moreFPL,s)=0 then
         begin
           new_title('   '+ s + moreFPL,true);
           {Draw}
         end
    end;