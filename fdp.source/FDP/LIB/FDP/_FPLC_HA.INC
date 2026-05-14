{ -------------------------------
   spracovanie plan letov,
   vo vsetkych stavoch...
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
  function alloc_FPLCmenu (FPL: PDcFPL; oFPL: P_OFPL; _plan: bool; vis: bool): PWinMenu; far;

     var   FPLmenu    : PWinMenu;
           smnu       : TPItems;
           i,items,nl : int;
           actual     : bool;
           enable     : bool;
           title      : string;

           acpt : TTRG_stat;
           rdp  : word;

     begin
       m_set_shape(HODINY);

       FPLmenu:= WinMenu(' '+FPL^.idn+' ',hlpmnuFPLCi,nil);
       items:= 0; nl:= 0;
       actual:= (FPL^.poz<poz_HANGAR) and (DateToSec(FPL^.date.r,FPL^.date.m,FPL^.date.d)>=DateToSec(year,month,day)-secDAY);
       enable:= ENABLE_FPLC;

       if actual then
          begin
            if enable then
               begin
                 smnu[items]:= Item(mnuETO, cmETOc_strip, nil);
                 inc(items);
               end;

            {$IFDEF CNL_FPLC}
             title:= mnuCNL
            {$ELSE}
             title:= mnuDEL
            {$ENDIF};
            smnu[items]:= Item(title, cmCNLc_strip, nil);
            inc(items);

            alloc_EDD_STRIPmenu_items (oFPL,FPL, smnu,items,nl, vis);

            add_newline(nl,items,smnu);
          end;


       if (_plan) or (miniSTRIP <> full_strip) or (@p_info_FPLc<>@info_cFPL) then
         begin
           smnu[items]:= Item(mnuSTR, cmFPLCview, nil);
           inc(items)
         end;

       {$IFDEF FPL4}
         smnu[items]:= Item(mnuFPL, cmFPLC4view, nil);
         inc(items);
       {$ENDIF}

       {$IFDEF MAPY}
         smnu[items]:= Item(tit_DRAW, cmFPLCdraw, nil);
         inc(items);
       {$ENDIF}

       {$IFDEF PRN}
         smnu[items]:= Item(tit_PRINT, cmFPLCprint, nil);
         inc(items);
       {$ENDIF}

       if cut_(FPL^.typ)<>'' then
          begin
            smnu[items]:= Item(tit_TYPE, cmFPLCtype, nil);
            inc(items);
          end;

       if enable then
          begin
            add_newline(nl,items,smnu);
            smnu[items]:= Item(tit_COPY{mnuEST}, cmESTc_strip, nil);
            inc(items);
          end;

       for i:= 0 to items-1 do FPLmenu^.AddItem(smnu[i]);

       alloc_FPLCmenu:= FPLmenu;
       m_restore_shape
     end;


  function _handle_plan_FPLC (var Ev: TEvent; FPLi: PDcFPL; oFPL: P_OFPL; sc: PScrollInd; dx,dy: int; _plan,_vis: bool): bool;

     var   FPLmenu : PWinMenu;
           x,y : int;
           FPL : DcFPL;
           s   : string;

     label E;

     begin
       _handle_plan_FPLC:= false;
       new_cFPL (FPLi,@FPL); { MUSI OSTAT }

       sc_menu_xy(sc, x,y, 0,0);
       FPLmenu:= alloc_FPLCmenu(@FPL,oFPL, _plan or (oFPL<>nil), _vis);
       FPLmenu^.MoveRel(x+dx-FPLmenu^.x0,y+dy-FPLmenu^.y0);
       FPLmenu^.Run(Ev);
       Dispose(FPLmenu, Done);

       if ((Ev.What and evMessage) <> 0) then
          begin
            {s:= codekey_FPLC(@FPL);
            disp_cFPL(@FPL);
            if read_cFPL(s,@FPL)<0 then goto E;}
            if _handle_event_FPL_o_sc (Ev,sc,@FPL,oFPL,sc) then ClearEvent(Ev,nil)
          end;

       E : disp_cFPL(@FPL)
     end;


  function handle_strip_FPLC (var Ev: TEvent; sc: PScrollInd; FPLi: PDcFPL; oFPL: P_OFPL): bool;
     begin
       handle_strip_FPLC:= _handle_plan_FPLC(Ev, FPLi,oFPL, sc,7,20, false,true)
     end;

  function handle_plan_FPLC (var Ev: TEvent; sc: PScrollInd; FPLi: PDcFPL): bool;
     var   dx,dy : int;
     begin
       {if (iFPL=nil) then begin dx:= -123; dy:= -12 end else} begin dx:= 7; dy:= 20 end;
       handle_plan_FPLC:= _handle_plan_FPLC(Ev, FPLi,nil, sc,dx,dy, false,false);
     end;
