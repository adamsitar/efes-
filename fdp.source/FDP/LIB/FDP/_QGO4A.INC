{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                                          Û
Û prehlad QGO                                              Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}

  function alloc_QGOmenu(QGO: PQGO; _plan: bool): PWinMenu;
     const max_items = 20;
     var   QGOmenu   : PWinMenu;
           QGOitems  : array[0..max_items-1] of PItem;
           items,i   : int;
           nl,actual : bool;
           cond      : string;

     begin
       m_set_shape(HODINY);

       alloc_QGOmenu:= nil;
       QGOmenu:= WinMenu(tit_schopnost,nil,nil);
       actual:= DateToSec(QGO^.date.r,QGO^.date.m,QGO^.date.d)>=DateToSec(year,month,day);
       items:= 0;

       {$IFDEF FDP_OPL} {$IFDEF PROCESS_QGO}
        if actual and _plan_pre_pracovisko(QGO) then
          begin
            if _is_SEND(QGO,nil) then
               begin
                 QGOitems[items]:= Item(tit_SEND, cmQGOsend, nil);
                 inc(items);
               end;

            QGOitems[items]:= Item(tit_CHG_, cmQGOakt, nil);
            inc(items);

            QGOitems[items]:= Item(tit_CNL_, cmQGOzru, nil);
            inc(items);
          end;
       {$ENDIF} {$ENDIF}

       nl:= false;
       {$IFDEF PRN}
         if items>0 then
            begin
              QGOitems[items]:= NewLine2(0,nil);
              inc(items);
              nl:= true
            end;
         QGOitems[items]:= Item(tit_PRINT, cmQGOprint, nil);
         inc(items);
       {$ENDIF}

       {$IFDEF FDP_OPL} {$IFDEF PROCESS_QGO}
        if (not nl) and (items>0) then
           begin
             QGOitems[items]:= NewLine(nil);
             inc(items);
             nl:= true
           end;
        QGOitems[items]:= Item(tit_PLAN_, cmQGO, nil);
        inc(items);
       {$ENDIF} {$ENDIF}

       if items=0 then begin Dispose(QGOmenu,Done); QGOmenu:= nil end
       else for i:= 0 to items-1 do QGOmenu^.AddItem(QGOitems[i]);
       alloc_QGOmenu:= QGOmenu;
       m_restore_shape
     end;


  function handle_QGO(sc: PScroller; QGO: PQGO): bool; far;
     var   QGOmenu : PWinMenu;
           E : TEvent;
           x,y : int;
     begin
       handle_QGO:= false;

       QGOmenu:= alloc_QGOmenu(QGO,false);
       if QGOmenu=nil then Exit;
       sc_menu_xy(sc, x,y, 0,0);
       QGOmenu^.MoveRel(x+10-QGOmenu^.x0,y+30-QGOmenu^.x0);
       QGOmenu^.Run(E);
       if ((E.What and evMessage)<>0) then _handle_event_QGO(E,sc,QGO);
       Dispose(QGOmenu, Done)
     end;

