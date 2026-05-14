  function alloc_PRNmenu(PRN: PPRN; _arch: bool): PWinMenu;
     const max_items = 20;
     var   PRNmenu   : PWinMenu;
           PRNitems  : array[0..max_items-1] of PItem;
           items,i   : int;
           nl : bool;

     begin
       m_set_shape(HODINY);
       PRNmenu:= WinMenu('',nil,nil);
       nl:= false;
       items:= 0;
       i:= 0;

       if    is_plani___(PRN^._D, max_NTM_D_r_hi, max_NTM_D_rm, -1)
          or is_plani___(PRN^._E, max_NTM_E_r_hi, max_NTM_E_rm, -1)
             then
          begin
            PRNitems[items]:= Item(tit_VIEW, cmPRNview, nil);
            inc(items);
          end;

       {$IFDEF PRN}
         PRNitems[items]:= Item(tit_PRINT, cmPRNprint, nil);
         inc(items);
       {$ENDIF}

       if items>0 then for i:= 0 to items-1 do PRNmenu^.AddItem(PRNitems[i])
       else begin Dispose(PRNmenu,Done); PRNmenu:= nil end;

       alloc_PRNmenu:= PRNmenu;
       m_restore_shape
     end;


 function _handle_PRN(sc: PScroller; PRN: PPRN; _arch: bool): bool; far;
    var   PRNmenu   : PWinMenu;
          E         : TEvent;
          x,y       : int;
          res       : bool;
    begin
      _handle_PRN:= false;

      PRNmenu:= alloc_PRNmenu(PRN,_arch);
      if PRNmenu=nil then Exit;
      sc_menu_xy(sc, x,y, 0,0);
      PRNmenu^.MoveRel(x+10-PRNmenu^.x0,y+30-PRNmenu^.y0);
      PRNmenu^.Run(E);
      if ((E.What and evMessage)<>0) then _handle_event_PRZ(E,sc,PRN);
      Dispose(PRNmenu, Done)
    end;


 function handle_PRN(sc: PScroller; PRN: PPRN): bool; far;
    begin
      handle_PRN:= _handle_PRN(sc, PRN, false)
    end;

 function handle_PRN_ARCH(sc: PScroller; PRN: PPRN): bool; far;
    begin
      handle_PRN_ARCH:= _handle_PRN(sc, PRN, true)
    end;
