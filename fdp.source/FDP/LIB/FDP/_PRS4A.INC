 function alloc_PRSmenu(PRS: PPRS; _arch : bool): PWinMenu;
    const max_items = 20;
    var   PRSmenu   : PWinMenu;
          PRSitems  : array[0..max_items-1] of PItem;
          items,i   : int;
          nl,cond   : bool;
    begin
      m_set_shape(HODINY);

      PRSmenu:= WinMenu(' '+PRS^.kod+' ',hlpmnuPRSi,nil);

      {actual:= (PRS^.poz<poz_HANGAR) and (DateToSec(PRS^.zac.rok,PRS^.zac.mes,PRS^.zac.den)>=DateToSec(year,month,day));}
      items:= 0;
      i:= 0;
      nl:= false;

     {$IFDEF PROCESS_PRS}
      cond:= (not _arch) and (PRS^.poz<poz_HANGAR) {and (limit>=rdat)};

      if cond then
         begin

           if _is_SEND (PRS,nil) then
              begin
                PRSitems[items]:= Item(tit_SEND, cmPRSsend, nil);
                inc(items)
              end;

           if _is_CHG (PRS,nil) then
              begin
                PRSitems[items]:= Item(mnu_PRS_CHG, cmPRSchg, nil);
                inc(items);
              end;

           if _is_CNL (PRS,nil) then
              begin
                PRSitems[items]:= Item(mnu_PRS_CNL, cmPRScnl, nil);
                inc(items);
              end;

           {$IFDEF AMC}
             if _is_ACC (PRS,nil) then
                begin
                  PRSitems[items]:= Item(mnu_PRS_ACC, cmPRSacc, nil);
                  inc(items);
                end;

             if _is_DEC (PRS,nil) then
                begin
                  PRSitems[items]:= Item(mnu_PRS_DEC, cmPRSdec, nil);
                  inc(items);
                end;
           {$ENDIF}

           if items>i then
              begin
                PRSitems[items]:= NewLine2(0,nil);
                inc(items);
              end;
           i:= items;

           if _is_DEP (PRS,nil) then
              begin
                PRSitems[items]:= Item(mnu_PRS_DEP, cmPRSdep, nil);
                inc(items);
              end;

           if _is_ACT (PRS,nil) then
              begin
                PRSitems[items]:= Item(mnu_PRS_ACT, cmPRSact, nil);
                inc(items);
              end;

           if _is_BRK (PRS,nil) then
              begin
                PRSitems[items]:= Item(mnu_PRS_BRK, cmPRSbrk, nil);
                inc(items);
              end;

           if _is_CNT (PRS,nil) then
              begin
                PRSitems[items]:= Item(mnu_PRS_CNT, cmPRScnt, nil);
                inc(items);
              end;

           if _is_ARR (PRS,nil) then
              begin
                PRSitems[items]:= Item(mnu_PRS_ARR, cmPRSarr, nil);
                inc(items);
              end;
         end;
      {$ENDIF}

      if items>i then
         begin
           PRSitems[items]:= NewLine2(0,nil);
           inc(items);
         end;
      i:= items;

      if is_plani___(PRS^.pozn, max_PRS_pozn_r_hi,max_PRS_pozn_rm,-1) or pis_STRIP_PRS then
         begin
           PRSitems[items]:= Item(tit_VIEW, cmPRSview, nil);
           inc(items);
         end;

      {IFDEF MAPY
        PRSitems[items]:= Item(tit_DRAW, cm_PLAN_DRAW, nil);
        inc(items);
      ENDIF}

      {$IFDEF PRN} {IFNDEF PRN_SERVER}
        PRSitems[items]:= Item(tit_PRINT, cmPRSprint, nil);
        inc(items);
      {$ENDIF} {ENDIF}

      {$IFDEF PROCESS_PRS}
       if items>i then
          begin
            PRSitems[items]:= NewLine(nil);
            inc(items);
          end;
       i:= items;

       if not is_P(PRS^.kod) then
          begin
            PRSitems[items]:= Item(tit_COPY, cmPRS, nil);
            inc(items)
          end;
      {$ENDIF}

      if items>0 then for i:= 0 to items-1 do PRSmenu^.AddItem(PRSitems[i])
      else begin Dispose(PRSmenu,Done); PRSmenu:= nil end;

      alloc_PRSmenu:= PRSmenu;
      m_restore_shape
    end;


 function _handle_PRS(sc: PScroller; PRS: PPRS; _arch: bool): bool; far;
    var   PRSmenu   : PWinMenu;
          E         : TEvent;
          x,y       : int;
          res       : bool;
    begin
      _handle_PRS:= false;

      PRSmenu:= alloc_PRSmenu(PRS,_arch);
      if PRSmenu=nil then Exit;
      sc_menu_xy(sc, x,y, 0,0);
      PRSmenu^.MoveRel(x+10-PRSmenu^.x0,y+30-PRSmenu^.y0);
      PRSmenu^.Run(E);
      if ((E.What and evMessage)<>0) then _handle_event_PRS(E,sc,PRS);
      Dispose(PRSmenu, Done)
    end;


 function handle_PRS(sc: PScroller; PRS: PPRS): bool; far;
    begin
      handle_PRS:= _handle_PRS(sc, PRS, false)
    end;

 function handle_PRS_ARCH(sc: PScroller; PRS: PPRS): bool; far;
    begin
      handle_PRS_ARCH:= _handle_PRS(sc, PRS, true)
    end;


 function handle_PRS_object(var Ev: TEvent; sc: PScrollInd; PRS: PPRS; PLAN: PPLAN): bool; far;
    begin
      handle_PRS_object:= _handle_PRS(sc, PRS, false)
    end;


 function handle_PRS_strip(iFPL: PSTRIP; PRS: PPRS; sc: PScroller; var E: TEvent; dx,dy: int): bool; far;
    begin
      handle_PRS_strip:= false;
      {$IFDEF TABLET_PRS}
        info_PRS(PRS,'')
      {$ENDIF}
    end;
