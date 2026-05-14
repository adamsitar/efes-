function alloc_SPRmenu(SPR: PSPR): PWinMenu;

   const max_items  = 20;

   var   SPRmenu    : PWinMenu;
         SPRitems   : array[0..max_items-1] of PItem;
         items,i,nd : int;
         nl         : bool;
         title      : string;
         limit,rdat : real;
         kod        : word;

   begin
      m_set_shape(HODINY);

      if SPR^.typ=hd_TLG then title:= tit_TLG else title:= tit_MSG;
      SPRmenu:= WinMenu(' '+title+' ',nil,nil);
      items:= 0;

      if (SPR^.ods = NETaddress) {and (not _write_acc(SPR,nd))} then
         begin
           SPRitems[items]:= Item(tit_LAM, cmSPRlam, nil);
           inc(items)
         end;

      if    is_plani___(SPR^.adr,  max_SPR_a_hi,max_SPR_am,-1)
         or is_plani___(SPR^.text, max_SPR_r_hi,max_SPR_rm,-1) then
         begin
           SPRitems[items]:= Item(tit_VIEW2, cmSPRview, nil);
           inc(items)
         end;

      {$IFDEF PRN}
       SPRitems[items]:= Item(tit_PRINT, cmSPRprint, nil);
       inc(items);
      {$ENDIF}

      if (items>0) then
         begin
           SPRitems[items]:= NewLine(nil);
           inc(items);
         end;

      if {get_lines_i_(SPR^.text) <= size_SPRmsg} SPR^.typ=hd_MSG then kod:= cmSPR else kod:= cmTLG;
      SPRitems[items]:= Item(tit_SEND, kod, nil);
      inc(items);

      if items>0 then for i:= 0 to items-1 do SPRmenu^.AddItem(SPRitems[i])
      else begin Dispose(SPRmenu,Done); SPRmenu:= nil end;

      alloc_SPRmenu:= SPRmenu;

      m_restore_shape
   end;


function _handle_SPR(sc: PScroller; SPR: PSPR): bool; far;
   var   M   : PWinMenu;
         _Ev : TEvent;
         x,y : int;
   begin
     _handle_SPR:= false;
     sc_menu_xy(sc, x,y, 0,0);
     M:= alloc_SPRmenu(SPR);
     M^.MoveRel(x+10-M^.x0,y+30-M^.y0);
     M^.Run(_Ev);
     if ((_Ev.What and evMessage)<>0) then _handle_event_SPR(_Ev,sc,SPR);
     Dispose(M,Done)
   end;

function handle_SPR(sc: PScroller; SPR: PSPR): bool;
   begin
     handle_SPR:= _handle_SPR(sc, SPR)
   end;
