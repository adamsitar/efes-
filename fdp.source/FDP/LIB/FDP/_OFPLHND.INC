{ IFDEF EDD}

{ ------------------------------
   Handler pre spracovanie FPL
  ------------------------------
}

  const {x0View = array[false..true] of int = [0,0];
        y0View = array[false..true] of int = [0,0];}
        x1View : array[false..true] of int = (85,70);
        {y1View = array[false..true] of int = [23,0];}

        {x0Draw = array[false..true] of int = [86,86];
        y0Draw = array[false..true] of int = [0,0];
        x1Draw = array[false..true] of int = [122,122];
        y1Draw = array[false..true] of int = [23,0];}

        x0RTE  : array[false..true,low(T_strip)..high(T_strip)] of int =
                 {$IFNDEF EDD_20} ((166,165,155),
                                   (166,165,155)
                                  )
                 {$ELSE}          ((dx_header+74,200+51,210+51),
                                   (dx_header+74,200+51,210+51)
                                  )
                 {$ENDIF};

        x1RTE  : array[false..true,low(T_strip)..high(T_strip)] of int =
                  ((dx_mstrip,dx_sstrip,dx_fstrip),
                   (dx_mstrip,dx_sstrip,dx_fstrip)
                  );



 procedure alloc_EDD_STRIPmenu_items (iFPL: P_OFPL; FPL: pointer;
                                      var  smnu : TPItems;
                                      var items,nl : int;
                                      vis : bool
                                     );
    var    acpt : TTRG_stat;
           rdp  : word;
           i    : int;
    begin
      if (iFPL=nil) or (FPL=nil) then Exit;

      if iFPL^.get_poz(FPL) < poz_HANGAR then
         begin
          add_newline(nl,items,smnu);

          {$IFDEF RDP_ACCEPT}
            if sector_RDP>-1 then
               begin
                 iFPL^.get_accept(FPL, acpt,rdp);
                 if (rdp=0) and (acpt=_cor) then
                    begin
                      smnu[items]:= Item(mnuACC, cm_PLAN_ACC, nil);
                      inc(items)
                    end
                 else if (rdp=sector_RDP) {or (iFPL^.is_rdp_sector(rdp)<>-1)} then
                      begin
                        smnu[items]:= Item(mnuUNC, cm_PLAN_UNACC, nil);
                        inc(items)
                      end;
               end;
          {$ENDIF}

          if pis_STRIP_COR and (iFPL^.get_cor(FPL)>0) then
             begin
               smnu[items]:= Item(mnuCAC, cm_PLAN_CHGACK, nil);
               inc(items);
             end;

          {$IFDEF EDD}
           if vis then
              begin
                i:= iFPL^.find(FPL);
                if i>=0 then
                   begin
                     if iFPL^.get_on_board(iFPL^.ap^[i]) then smnu[items]:= Item(mnuHIDE, cmPLAN_HIDE, nil)
                     else smnu[items]:= Item(mnuSHOW, cmPLAN_SHOW, nil);
                     inc(items);
                   end;
              end;
          {$ENDIF}

          {$IFDEF ABI_COORDINATION}
           smnu[items]:= Item(mnuABI, cm_PLAN_ABI, nil);
           inc(items);
          {$ENDIF}
         end;
    end;


 procedure alloc_STRIPmenu_items (iFPL: P_OFPL; FPL: pointer;
                                  var  smnu : TPItems;
                                  var items,nl : int;
                                  vis : bool
                                 );

    var    acpt : TTRG_stat;
           rdp  : word;

    begin
      if (iFPL=nil) or (FPL=nil) then Exit;

      if iFPL^.get_poz(FPL) < poz_HANGAR then
         begin
          (*{$IFDEF EDD}
           if    ((iFPL^.typ = fplOTHER) or (iFPL^.typ=fplVFR)      {$IFDEF DISABLED_ETO_FPLc} and false {$ENDIF})
              or (((iFPL^.typ = fplMIL) or ((iFPL^.typ = fplFPL)) {$IFDEF DISABLED_ETO_FPLm} and false {$ENDIF}))
                 then
           {$ENDIF}*)
            begin
              smnu[items]:= Item(mnuETO, cm_PLAN_CHG, nil);
              inc(items);
              smnu[items]:= Item(mnuDEL, cm_PLAN_CNL, nil);
              inc(items);
              smnu[items]:= NewLine2(0,nil);
              inc(items); inc(nl);
            end;

           alloc_EDD_STRIPmenu_items (iFPL,FPL, smnu,items,nl,vis);

           add_newline(nl,items,smnu);
         end;

      {$IFDEF EDD}
       if (iFPL^.skupina=fplOTHER) or (iFPL^.skupina=fplVFR) { civilny strip } then
          begin
            smnu[items]:= Item(mnuFPL,cm_PLAN_VIEW, nil);
            inc(items);
            smnu[items]:= Item(mnuSTR, cm_DATA_VIEW, nil);
            inc(items)
          end
       else begin
              smnu[items]:= Item(tit_VIEW, cm_DATA_VIEW, nil);
              inc(items)
            end;
      {$ENDIF}

      {$IFDEF MAPY}
        if iFPL^.p_kresli<>nil then
           begin
             smnu[items]:= Item(tit_DRAW, cm_PLAN_DRAW, nil);
             inc(items)
           end;
      {$ENDIF}

       if iFPL^.p_typ<>nil then
          begin
            smnu[items]:= Item(tit_TYPE, cm_PLAN_TYPE, nil);
            inc(items)
          end;
      {$IFDEF PRN}
        if iFPL^.p_print<>nil then
           begin
             smnu[items]:= Item(tit_PRINT, cm_PLAN_PRINT, nil);
             inc(items)
           end;
      {$ENDIF}

      {smnu[items]:= Item(' ~L~AM      ', cm_PLAN_LAM, nil);
      inc(items);}

    end;

 function alloc_STRIPmenu (iFPL: P_OFPL; FPL: pointer): PWinMenu;

    var    STRIPmenu  : PWinMenu;
           smnu       : TPItems;
           i,items,nl : int;

           acpt : TTRG_stat;
           rdp  : word;

    begin
      m_set_shape(HODINY);
      STRIPmenu := WinMenu(' '+cut_(iFPL^.get_id(FPL))+' ',hlpmnuACCEPTED_STRIP,nil);
      items:= 0; nl:= 0;
      alloc_STRIPmenu_items (iFPL,FPL, smnu,items,nl,iFPL^.hidding);
      for i:= 0 to items-1 do STRIPmenu^.AddItem(smnu[i]);
      alloc_STRIPmenu:= STRIPmenu;
      m_restore_shape
    end;


{ funkcia nedodrziava konvenciu paramterov,
  nie je pouzitelna ako odkaz
}
 function _handle_click_on_strip (var Ev: TEvent; dx,dy: int): bool;
    begin
      _handle_click_on_strip:= true;

      if isCommand(Ev, cmScrollItemEntered) then _handle_click_on_strip:= false
      else if isCommand(Ev, cmScrollItemClicked) then
         begin
           if inRectangle(dx,dy, 0,0,x1View[lineSTRIP],dy_strip_[lineSTRIP] div 2 +4) then SetCommand(Ev,nil,cm_DATA_VIEW)
           {else if inRectangle(dx,dy, x0Draw[lineSTRIP],y0Draw[lineSTRIP],x1Draw[lineSTRIP],y1Draw[lineSTRIP]) then
                    SetCommand(Ev,nil,cm_DATA_VIEW)
           else if inRectangle(dx,dy, x0LAM,y0LAM,x1LAM,y1LAM) then SetCommand(Ev,nil,cm_PLAN_LAM)}
           {$IFDEF MAPY}
            else if inRectangle(dx,dy,
                                x0RTE[lineSTRIP,miniSTRIP],0,
                                dx_strip_[miniSTRIP],dy_strip_[lineSTRIP] div 2 +4
                               ) then SetCommand(Ev,nil,cm_PLAN_DRAW)
            else if inRectangle(dx,dy,
                                x0RTE[lineSTRIP,miniSTRIP],dy_strip_[lineSTRIP] div 2 + 5,
                                dx_strip_[miniSTRIP], dy_strip_[lineSTRIP]
                               ) then SetCommand(Ev,nil,cm_PLAN_CHG)
           {$ELSE}
            else if inRectangle(dx,dy,
                                x0RTE[lineSTRIP,miniSTRIP],0,
                                dx_strip_[miniSTRIP],dy_strip_[lineSTRIP]
                               ) then SetCommand(Ev,nil,cm_PLAN_CHG)
           {$ENDIF}
           else if     (not lineSTRIP)
                   and inRectangle
                               (dx,dy,
                                0,dy_strip_[false] div 2 + 5,
                                kod_9*8, dy_strip_[false]
                               )
                       then SetCommand(Ev,nil,cm_PLAN_TYPE)
           else _handle_click_on_strip:= false
         end
    end;


{ funkcia nedodrziava konvenciu paramterov,
  nie je pouzitelna ako odkaz
}
 function _handle_event_on_strip (var Ev: TEvent; FPL: pointer; iFPL: P_OFPL; dx,dy: int): bool;
    var   typ: string;
    begin
      _handle_event_on_strip:= true;

      if (iFPL<>nil) and (FPL<>nil) and ((Ev.What and evMessage) <> 0) then
         case Ev.Command of

           cm_PLAN_CHG    : iFPL^.oprav (FPL,hd_EST);
           cm_PLAN_CNL    : iFPL^.zrus  (FPL,true);

           {$IFDEF RDP_ACCEPT}
            cm_PLAN_ACC   : P_OFPL(iFPL)^.FPL_accept(FPL);
            cm_PLAN_UNACC : P_OFPL(iFPL)^.FPL_unaccept(FPL);
           {$ENDIF}

           {$IFDEF ABI_COORDINATION}
            cm_PLAN_ABI   : iFPL^.coordinate_ABI (FPL);
           {$ENDIF}

           cm_PLAN_CHGACK : iFPL^.cl_cor (FPL);
           cm_PLAN_TRACK  : iFPL^.rozosli(FPL,@c_true);
           cm_PLAN_SEND   : iFPL^.posli  (FPL,SERVERaddress,false);
           {cm_PLAN_LAM   : iFPL^.LAM    (FPL);}

           cm_DATA_VIEW   : iFPL^.zobraz(FPL);
           cm_PLAN_VIEW   : iFPL^.plan  (FPL);

           {$IFDEF MAPY}
            cm_PLAN_DRAW  : iFPL^.vykresli_plan_na_mape(FPL);
           {$ENDIF}

           cm_PLAN_TYPE   : begin
                              typ:= iFPL^.get_typ(FPL);
                              if cut_(typ)<>'' then _info_TYP(typ, dx,dy);
                            end

           {$IFDEF PRN};
             cm_PLAN_PRINT : iFPL^.tlac (FPL,true)
           {$ENDIF}

           else begin
                  _handle_event_on_strip:= false;
                  Exit
                end
         end;

      ClearEvent(Ev,iFPL);
    end;

{ ENDIF}


{ typ _Bp3vEi2
}
 function _edd_board_strip_handler(iFPL: P_OFPL; FPL: pointer; sc: PScroller; var Ev: TEvent; dx,dy: int): bool; far;

    var   STRIPmenu  : PWinMenu;
          key : string;
          ind : int;
          bres: bool;
          x,y : int;
          E   : TEvent;

    label L;

    begin
      _edd_board_strip_handler:= false;

      key:= iFPL^.get_key(FPL);
      ind:= iFPL^.find_key(key);

      L: if not _handle_click_on_strip (Ev, dx,dy) then
            if iFPL^.p_plan_handler<>nil then
               begin
                 _edd_board_strip_handler:= TBFunc_vEp3(iFPL^.p_plan_handler)(Ev,sc,FPL,iFPL)
               end
            else begin
                  {$IFDEF EDD}
                    STRIPmenu:= alloc_STRIPmenu (iFPL,FPL);
                    RunMenu(STRIPmenu,Ev);
                    Dispose(STRIPmenu, Done);
                  {$ELSE}
                    ClearEvent(Ev,nil);
                    Exit;
                  {$ENDIF}
                 end;

      { nezmenilo sa spracovanie/poradie planov;
        nie je to dokonale...
       if (ind>iFPL^.top) then ClearEvent(Ev,nil)
       else if (key<>iFPL^.get_key(iFPL^.ap^[ind])) then goto L;}

       if ((Ev.What and evMessage) <> 0) then
          begin
           { bol vydany prikaz cez vlastnemenu alebo zvysil prikaz
             z externeho menu
           }
            Move(MailBox^,E,SizeOf(TEvent));
            x:= (E.M.x + dx);
            y:= (E.M.y + dy);
            _edd_board_strip_handler:= _handle_event_on_strip (Ev, FPL, iFPL, x,y)
         end
       else _edd_board_strip_handler:= false
    end;

{ ENDIF}

{ typ _BvEp3
}
 function _strip_handler (var Ev: TEvent; sc: PScrollInd; FPL: pointer; iFPL: P_OFPL): bool; far;
    var   dx,dy: int;
          E: TEvent;
    begin
      if sc<>nil then with sc^ do
        begin
          Move(MailBox^,E,SizeOf(TEvent));
          dx:= (E.M.x - x0-dxi);
          dy:= (E.M.y - y0-dyi-pos*(item_dy+medzera))
        end
      else begin
             dx:= 0; dy:= 0;
           end;
      {IFDEF EDD}
        _edd_board_strip_handler(iFPL, FPL, sc,Ev, dx,dy);
      {ELSE
        TBFunc_vEp3(iFPL^.p_handler)(Ev,sc,FPL,iFPL);
      ENDIF}
      _strip_handler:= false;                       { zamerne }
    end;

{ ENDIF}