{ ------
   RPL
  ------
}

 function alloc_RPLmenu(RPL: PRPL; _plan,_decode: bool): PWinMenu;
    var   RPLmenu    : PWinMenu;
          smnu       : TPItems;
          i,items,nl : int;
    begin
      m_set_shape(HODINY);

      RPLmenu:= WinMenu(' '+getstr(RPL^._7a,1,[icao_NXT])+' ',nil,nil);
      items:= 0; nl:= 0;

      {$IFDEF PROCESS_RPL}
       smnu[0]:= Item(mnu_RPL_CHG_,cm_RPLchg,nil);
       if _is_BRK(RPL,nil) then smnu[1]:= Item(mnu_RPL_BRK_, cm_RPLbrk,nil)
       else smnu[1]:= Item(mnu_RPL_CNT_, cm_RPLcnt,nil);
       items:= 2;
       add_newline_(0,nl,items,smnu);
      {$ENDIF}

      if _plan then
        begin
          smnu[items]:= Item(tit_VIEW, cm_RPLview, nil);
          inc(items);
        end;

      {$IFDEF PRN}
       smnu[items]:= Item(tit_PRINT, cm_RPLprint, nil);
       inc(items);
      {$ENDIF}

      smnu[items]:= Item(' ~F~PL ', cm_RPLspracuj, nil);

      inc(items);

      {$IFDEF PROCESS_RPL}
       add_newline_(0,nl,items,smnu);
       smnu[items]:= Item(mnu_FPL4_COPY_, cm_RPL, nil);
       inc(items);
      {$ENDIF}

      for i:= 0 to items-1 do RPLmenu^.AddItem(smnu[i]);

      alloc_RPLmenu:= RPLmenu;
      m_restore_shape
    end;


 function handle_plan_RPL (var Ev: TEvent; sc: PScroller; RPL: PRPL): bool; far;
    var   RPLmenu : PWinMenu;
          x,y,dx,dy : int;
    begin
      RPLmenu:= alloc_RPLmenu(RPL,
                              (    bminiRPL
                                and (    (get_lines_i_(RPL^._15) > max_RPL_15_rm)
                                      or (get_lines_i_(RPL^._18) > max_RPL_18_rm)
                                    )
                              ),
                              false);
      sc^.get_pos_xy(sc^.pos, x,y);
      dx:= 7; dy:= 15;
      RPLmenu^.MoveRel(x+dx-RPLmenu^.x0,y+dy-RPLmenu^.y0);
      RunMenu(RPLmenu,Ev);
      Dispose(RPLmenu,Done);
      _handle_event_RPL_sc (Ev,sc,RPL,sc);
      handle_plan_RPL:= false
    end;

