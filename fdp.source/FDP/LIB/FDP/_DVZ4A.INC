{ -------------------------------
  handlery
}

function alloc_DVZmenu(DVZ: PDVZ; _plan: bool): PWinMenu;
   const max_items = 20;
   var   DVZmenu   : PWinMenu;
         DVZitems  : array[0..max_items-1] of PItem;
         items,i   : int;
         nl,actual : bool;
         cond      : string;
   begin
      m_set_shape(HODINY);

      DVZmenu:= WinMenu(tit_diverzia+' '+tit_pre+' '+DVZ^.pre+' '+tit_na+' '+DVZ^.kym,nil,nil);
      items:= 0;
      actual:= {(DVZ^.poz<poz_HANGAR) and} (DateToSec(DVZ^.date.r,DVZ^.date.m,DVZ^.date.d)>=DateToSec(year,month,day));

      {$IFDEF PROCESS_DVZ}
       if actual then
          begin
            if _is_CHG(DVZ,nil) then
               begin
                 DVZitems[items]:= Item(DVZPLAN, cmDVZchg, nil);
                 inc(items)
               end;

            if _is_CNL(DVZ,nil) then
               begin
                 DVZitems[items]:= Item(DVZCNL, cmDVZcnl, nil);
                 inc(items)
               end;

            if _is_REQ(DVZ,nil) then
               begin
                 DVZitems[items]:= Item(DVZREQ, cmDVZreq, nil);
                 inc(items)
               end;

            if _is_ACT(DVZ,nil) then
               begin
                 DVZitems[items]:= Item(DVZACT, cmDVZact, nil);
                 inc(items)
               end;

            if _is_END(DVZ,nil) then
               begin
                 DVZitems[items]:= Item(DVZEND, cmDVZend, nil);
                 inc(items)
               end;

            if _is_ACC(DVZ,nil) then
               begin
                 DVZitems[items]:= Item(DVZACC, cmDVZacc, nil);
                 inc(items)
               end;

            if _is_ALR(DVZ,nil) then
               begin
                 DVZitems[items]:= Item(DVZALR, cmDVZalr, nil);
                 inc(items)
               end;

            if _is_CLN(DVZ,nil) then
               begin
                 DVZitems[items]:= Item(DVZCLN, cmDVZcln, nil);
                 inc(items)
               end;

            if _is_ACN(DVZ,nil) then
               begin
                 DVZitems[items]:= Item(DVZACN, cmDVZacn, nil);
                 inc(items)
               end;
          end;
      {$ENDIF}

      nl:= false;
      {$IFDEF PRN}
        if items>0 then
           begin
             DVZitems[items]:= NewLine(nil);
             inc(items);
             nl:= true
           end;
        DVZitems[items]:= Item(tit_PRINT, cmDVZprint, nil);
        inc(items);
      {$ENDIF}

      {$IFDEF PROCESS_DVZ}
        if (not nl) and (items>0) then
           begin
             DVZitems[items]:= NewLine(nil);
             inc(items);
             nl:= true
           end;
        DVZitems[items]:= Item(tit_PLAN_, cmDVZ, nil);
        inc(items);
      {$ENDIF}

      if items=0 then begin Dispose(DVZmenu,Done); DVZmenu:= nil end
      else for i:= 0 to items-1 do DVZmenu^.AddItem(DVZitems[i]);
      alloc_DVZmenu:= DVZmenu;

      m_restore_shape
   end;


function handle_DVZ(sc: PScroller; DVZ: PDVZ): bool; far;
   var   DVZmenu   : PWinMenu;
         E         : TEvent;
         x,y       : int;
         res       : bool;
   begin
     handle_DVZ:= false;

     DVZmenu:= alloc_DVZmenu(DVZ,false);
     if DVZmenu=nil then Exit;
     sc_menu_xy(sc, x,y, 0,0);
     DVZmenu^.MoveRel(x+10-DVZmenu^.x0,y+30-DVZmenu^.y0);
     DVZmenu^.Run(E);
     if ((E.What and evMessage)<>0) then _handle_event_DVZ(E,sc,DVZ);
     Dispose(DVZmenu, Done)
   end;


function handle_DVZ_object(var Ev: TEvent; sc: PScrollInd; DVZ: PDVZ; PLAN: PPLAN): bool; far;
   begin
     handle_DVZ_object:= handle_DVZ(sc, DVZ)
   end;


function handle_DVZ_strip(iFPL: PSTRIP; DVZ: PDVZ; sc: PScroller; var E: TEvent; dx,dy: int): bool; far;
   begin
     handle_DVZ_strip:= false;
     {$IFDEF TABLET_DVZ}
       info_DVZ(DVZ,tit_info_DVZ+' '+DVZ^.let_)
     {$ENDIF}
   end;