  function alloc_PRZmenu(PRZ: PPRZ; _arch: bool): PWinMenu;
     const max_items = 20;
     var   PRZmenu   : PWinMenu;
           PRZitems  : array[0..max_items-1] of PItem;
           items,i   : int;
           nl : bool;

     begin
       m_set_shape(HODINY);
       PRZmenu:= WinMenu(tit_PRZ_,nil,nil);
       nl:= false;
       items:= 0;
       i:= 0;

      {$IFDEF PRZ_REQUEST}
       if (not _arch) then
          begin
            if _is_SEND (PRZ,nil) then
               begin
                 PRZitems[items]:= Item(tit_SEND, cmPRZsend, nil);
                 inc(items);
               end;

            if _is_CHG (PRZ, nil) then
               begin
                 PRZitems[items]:= Item(PRZCHG, cmPRZ_CHG, nil);
                 inc(items);
               end;

            if _is_CNL (PRZ, nil) then
               begin
                 PRZitems[items]:= Item(PRZCNL, cmPRZ_CNL, nil);
                 inc(items);
               end;

            if items>i then
               begin
                 PRZitems[items]:= NewLine(nil);
                 inc(items);
               end
          end;
       i:= items;
      {$ENDIF}

       if    is_plani___(PRZ^._D, max_NTM_D_r_hi, max_NTM_D_rm, -1)
          or is_plani___(PRZ^._E, max_NTM_E_r_hi, max_NTM_E_rm, -1)
             then
          begin
            PRZitems[items]:= Item(tit_VIEW, cmPRZview, nil);
            inc(items);
          end;

      {IFDEF MAPY
        PRZitems[items]:= Item(tit_DRAW, cm_PLAN_DRAW, nil);
        inc(items);
      ENDIF}

      {$IFDEF PRN}
        PRZitems[items]:= Item(tit_PRINT, cmPRZprint, nil);
        inc(items);
      {$ENDIF}

      {$IFDEF PRZ_REQUEST}
       if items>i then
          begin
            PRZitems[items]:= NewLine(nil);
            inc(items);
          end;
       i:= items;
       PRZitems[items]:= Item(PRZCPY, cmPRZ, nil);
       inc(items);
      {$ENDIF}

       if items>0 then for i:= 0 to items-1 do PRZmenu^.AddItem(PRZitems[i])
       else begin Dispose(PRZmenu,Done); PRZmenu:= nil end;

       alloc_PRZmenu:= PRZmenu;
       m_restore_shape
     end;


 function _handle_PRZ(sc: PScroller; PRZ: PPRZ; _arch: bool): bool; far;
    var   PRZmenu   : PWinMenu;
          E         : TEvent;
          x,y       : int;
          res       : bool;
    begin
      _handle_PRZ:= false;

      PRZmenu:= alloc_PRZmenu(PRZ,_arch);
      if PRZmenu=nil then Exit;
      sc_menu_xy(sc, x,y, 0,0);
      PRZmenu^.MoveRel(x+10-PRZmenu^.x0,y+30-PRZmenu^.y0);
      PRZmenu^.Run(E);
      if ((E.What and evMessage)<>0) then _handle_event_PRZ(E,sc,PRZ);
      Dispose(PRZmenu, Done)
    end;


 function handle_PRZ(sc: PScroller; PRZ: PPRZ): bool; far;
    begin
      handle_PRZ:= _handle_PRZ(sc, PRZ, false)
    end;

 function handle_PRZ_ARCH(sc: PScroller; PRZ: PPRZ): bool; far;
    begin
      handle_PRZ_ARCH:= _handle_PRZ(sc, PRZ, true)
    end;
