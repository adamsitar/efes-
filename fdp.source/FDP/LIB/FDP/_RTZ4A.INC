{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                                          Û
Û prehlad RTZ                                              Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}
  function alloc_RTZmenu(RTZ: PRTZ; _plan: bool): PWinMenu;
     const max_items = 20;
     var   RTZmenu   : PWinMenu;
           RTZitems  : array[0..max_items-1] of PItem;
           items,i   : int;
           nl,actual : bool;
           cond      : string;

     begin
       m_set_shape(HODINY);

       alloc_RTZmenu:= nil;
       RTZmenu:= WinMenu(tit_RTZ,nil,nil);
       actual:= DateToSec(RTZ^.date.r,RTZ^.date.m,RTZ^.date.d)>=DateToSec(year,month,day);
       items:= 0;

       {$IFDEF FDP_OPL} {$IFDEF PROCESS_RTZ}
        if actual and _plan_pre_pracovisko(RTZ) then
          begin
            if _is_SEND(RTZ,nil) then
               begin
                 RTZitems[items]:= Item(tit_SEND, cmRTZsend, nil);
                 inc(items);
               end;

            RTZitems[items]:= Item(tit_CHG_, cmRTZakt, nil);
            inc(items);

            RTZitems[items]:= Item(tit_CNL_, cmRTZzru, nil);
            inc(items);
          end;
       {$ENDIF} {$ENDIF}

       nl:= false;
       {$IFDEF PRN}
         if items>0 then
            begin
              RTZitems[items]:= NewLine2(0,nil);
              inc(items);
              nl:= true
            end;
         RTZitems[items]:= Item(tit_PRINT, cmRTZprint, nil);
         inc(items);
       {$ENDIF}

       {$IFDEF FDP_OPL} {$IFDEF PROCESS_RTZ}
        if (not nl) and (items>0) then
           begin
             RTZitems[items]:= NewLine(nil);
             inc(items);
             nl:= true
           end;
        RTZitems[items]:= Item(tit_PLAN_, cmRTZ, nil);
        inc(items);
       {$ENDIF} {$ENDIF}

       if items=0 then begin Dispose(RTZmenu,Done); RTZmenu:= nil end
       else for i:= 0 to items-1 do RTZmenu^.AddItem(RTZitems[i]);
       alloc_RTZmenu:= RTZmenu;
       m_restore_shape
     end;


  function handle_RTZ(sc: PScroller; RTZ: PRTZ): bool; far;
     var   RTZmenu : PWinMenu;
           E : TEvent;
           x,y : int;
     begin
       handle_RTZ:= false;

       RTZmenu:= alloc_RTZmenu(RTZ,false);
       if RTZmenu=nil then Exit;
       sc_menu_xy(sc, x,y, 0,0);
       RTZmenu^.MoveRel(x+10-RTZmenu^.x0,y+30-RTZmenu^.x0);
       RTZmenu^.Run(E);
       if ((E.What and evMessage)<>0) then _handle_event_RTZ(E,sc,RTZ);
       Dispose(RTZmenu, Done)
     end;

