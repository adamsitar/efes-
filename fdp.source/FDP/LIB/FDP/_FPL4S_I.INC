{ ------
   FPL4
  ------
}

 function alloc_FPLmenu(_7a,_13a,_16a,_16c : string;
                        stat : string; poz : TPoz;
                        dat : TDate;
                        _eet,_exi : TOB_;
                        _data,_plan,_decode: bool;
                        FPL: PFPL4
                       ): PWinMenu;

    var   FPLmenu    : PWinMenu;
          smnu       : TPItems;
          i,items,nl : int;
          actual,ppl : bool;
          enable     : bool;
          mil        : bool;
          cond       : string;
          r1,r2,r    : real;
          unkn       : bool;
          B          : TsBod;

    begin
      m_set_shape(HODINY);

      FPLmenu:= WinMenu(_7a,hlpmnuFPL4i,nil);
      i:= 0;items:= 0; nl:= 0;

      r:= dT_deactive_FPLC*60;
      r1:= datetosec(year,month,day);
      with FPL^.date do r2:= datetosec(r,m,d);
      actual:= (r1=r2) or (absTime<=_exi.cas+r);
      ppl:= r1<r2;

      {$IFDEF PROCESS_FPL4}
       if     (actual or (r1=r2) or ppl)
          and (   ((poz<>poz_unkn) and (poz<poz_HANGAR))
               or (not in_icao_head (stat, ms_ICAOarr, unkn) or (stat<>ht_FLA)
              )) then
          begin
            i:= 0;

            if in_icao_head (stat, ms_ICAOplan, unkn) or unkn then
              begin
                smnu[items]:= Item(mnu_FPL4_CHG_, cm_CHG, nil);
                inc(items);
                if _filter_FPL_DEP(FPL,nil) then
                   begin
                     smnu[items]:= Item(mnu_FPL4_DLA_, cm_DLA, nil);
                     inc(items)
                   end;
              end;

            if in_icao_head (stat, ms_ICAOplan+ms_ICAOact, unkn) or unkn then
              begin
                smnu[items]:= Item(mnu_FPL4_CNL_, cm_CNL, nil);
                inc(items);
              end;

            if in_icao_head (stat, ms_ICAOplan, unkn) or unkn then
              begin
                {pomr:= dT_preactive_FPL4*60;
                if (absTime >= _eet.cas+pomr) then}
                  begin
                    if _filter_FPL_DEP(FPL,nil) then
                       begin
                         smnu[items]:= Item(mnu_FPL4_DEP_, cm_DEP, nil);
                         inc(items)
                       end;
                    if _filter_FPL_ACT(FPL,nil) then
                       begin
                         smnu[items]:= Item(mnu_FPL4_ACT_, cm_ACT, nil);
                         inc(items)
                       end;
                  end
               end;

            if actual and in_icao_head (stat, ms_ICAOact, unkn) then
               begin
                if (items>i) then begin add_newline_(0,nl,items,smnu); i:= items; end;

                (*{$IFDEF FLI_COORDINATION}
                 smnu[items]:= Item(mnu_FPL4_FLI_, cm_FLA, nil);
                 inc(items);
                {$ENDIF}

                 smnu[items]:= Item(mnu_FPL4_ETO_, cm_ETO, nil);
                 inc(items);
                 *)

                 if    (is_OB(_16a,B,false) and (B.ine.podriadene))
                    or (is_OB(_16c,B,false) and (B.ine.podriadene))
                    then
                    begin
                      smnu[items]:= Item(mnu_FPL4_ARR_, cm_ARR, nil);
                      inc(items)
                    end;

                {$IFDEF TSGA}
                 smnu[items]:= Item(mnu_FPL4_FLA_, cm_FLA, nil);
                 inc(items);
                {$ENDIF}
               end;

            if (items>i) then begin add_newline_(0,nl,items,smnu); i:= items; end;
          end;
      {$ENDIF}

      if _data then
         begin
           smnu[items]:= Item(tit_DATA, cm_DATA_VIEW, nil);
           inc(items);
         end;

      if _plan then
         begin
           smnu[items]:= Item(tit_VIEW, cmFPL4view, nil);
           inc(items);
         end;

      {$IFDEF PROCESS_FPL4}
       if _decode then
         begin
           smnu[items]:= Item(tit_STRIP, cmFPL4view_strip, nil);
           inc(items);
         end;

       {$IFDEF MAPY}
        smnu[items]:= Item(tit_DRAW, cmFPL4draw, nil);
        inc(items);
       {$ENDIF}
      {$ENDIF}

      {$IFDEF PRN}
       smnu[items]:= Item(tit_PRINT, cmFPL4print, nil);
       inc(items);
      {$ENDIF}

      {$IFDEF PROCESS_FPL4}
       if i<items then add_newline_(0,nl,items,smnu);
       smnu[items]:= Item(mnu_FPL4_COPY_, cm_FPL, nil);
       inc(items);
      {$ENDIF}

      for i:= 0 to items-1 do FPLmenu^.AddItem(smnu[i]);

      alloc_FPLmenu:= FPLmenu;
      m_restore_shape
    end;


 function _handle_o_FPL4_list (var Ev : TEvent;
                               sc   : PScroller;
                               FPLi : PFPL4;
                               _data,_plan,_decode: bool;
                               dx,dy: int
                              ): bool;
    var   FPLmenu  : PWinMenu;
          FPL : DFPL4;
          x,y, ires : int;
          s : string;

          hs,ms: byte;
          kod: string;
          h,m, hl,ml: byte;
          kodb: string;

    begin
      _handle_o_FPL4_list:= false;

      new_FPL4 (FPLi,@FPL);
      {FPL.data:= FPLi.data;}
      decode_l4_16 (FPL._16, hs,ms,kod,h,m,hl,ml,kodb);

      FPLmenu:= alloc_FPLmenu(decode_l4_7a(FPL._7),
                              decode_l4_13a(FPL._13),
                              kod,kodb,

                              FPL.stat,poz_UNKN,FPL.date,
                              FPL.eet,FPL.exi,
                              _data,
                              _plan or
                              (    bminiFPL4
                                and (    (get_lines_i_(FPLi^._15) > max_FPL4_15_rm)
                                      or (get_lines_i_(FPLi^._18) > max_FPL4_18_rm)
                                    )
                              ),
                              _decode,
                              @FPL
                             );
      sc_menu_xy(sc, x,y, 0,0);
      FPLmenu^.MoveRel(x+dx-FPLmenu^.x0,y+dy-FPLmenu^.y0);
      RunMenu(FPLmenu, Ev);
      Dispose(FPLmenu, Done);

      if ((Ev.What and evMessage) <> 0) then
         begin
           (*s:= codekey_FPL4(@FPL);    { ak bol medzitym spracovany }
           disp_FPL4(@FPL);
           if read_FPL4(s,@FPL)>=0 then*)
           _handle_event_FPL4_sc (Ev,sc,@FPL,sc)
         end;

      {FPL.data:= nil;}
      disp_FPL4(@FPL);
    end;


 function handle_plan_FPL4 (var Ev: TEvent; sc: PScroller; FPL: PFPL4): bool; far;
    begin
     { handler pre db }
      handle_plan_FPL4:= _handle_o_FPL4_list (Ev,sc,FPL,false,false,true,7,13)
    end;


{ ------
   FDR
  ------
}
 function _handle_o_FDR_list (var Ev: TEvent; sc: PScroller; FDR: PFDR; dx,dy: int): bool;
    var   FPL  : DFPL4;
          ires : int;
    begin
      m_set_shape(HODINY);
      ires:= read_FPL4(codekey_FDR(FDR),@FPL);
      m_restore_shape;
      if ires>=0 then
         begin
           _handle_o_FDR_list:= _handle_o_FPL4_list (Ev,sc,@FPL,dx=-123,true,true,dx,dy);
           if isCommand(Ev,cm_DATA_VIEW) then
              begin
                info_FDR(FDR,'');
                ClearEvent(Ev,sc)
              end;
           disp_FPL4(@FPL)
         end
      else _handle_o_FDR_list:= false;
    end;


 function handle_plan_FDR (var Ev: TEvent; sc: PScroller; FDR: PFDR): bool;
    begin
     { handler pre db }
      handle_plan_FDR:= _handle_o_FDR_list(Ev,sc,FDR,7,13);
    end;
