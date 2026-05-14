{ -------------------------------
   spracovanie plan letov,
   vo vsetkych stavoch...
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
  function alloc_FPLMmenu (FPL: PDmFPL; oFPL: P_OFPL; _plan: bool): PWinMenu; far;

     var   FPLmenu    : PWinMenu;
           smnu       : TPItems;
           i,items,nl : int;
           actual     : bool;
           enable     : bool;
           mil        : bool;
           cond       : string;
           cmX        : word;

           acpt : TTRG_stat;
           rdp  : word;

     begin
       m_set_shape(HODINY);

       FPLmenu:= WinMenu(' '+code_FPLM_7a(FPL)+' ',hlpmnuFPLMi,nil);
       items:= 0; nl:= 0;

       actual:= (DateToSec(FPL^.date.r,FPL^.date.m,FPL^.date.d)>=DateToSec(year,month,day));
       enable:= ENABLE_FPLM;
       mil:= is_mFPL(FPL);

       if enable and actual then
          begin

           {$IFDEF PROCESS_FPLM}

           { ------------------------------
              Spracovanie pre FDA
             תתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
           }
             { IFDEF AIRBASE}
               if _is_SEND(FPL,nil) then
                  begin
                    smnu[items]:= Item(tit_SEND, cmFPLMsend, nil);
                    inc(items);
                  end;
             { ENDIF}

             if _is_CHG(FPL,nil) then
                begin
                  smnu[items]:= Item(mnu_FPLM_CHG_, cmCHGm, nil);
                  inc(items)
                end;

             {$IFDEF OPL}
              if _is_REQ(FPL,nil)  then
                 begin
                   smnu[items]:= Item(mnu_FPLM_REQ_, cmREQm, nil);
                   inc(items)
                 end;

              {if _is_REQ2(FPL,nil)  then
                 begin
                   smnu[items]:= Item(mnu_FPLM_REQ2_,cmREQ2m, nil);
                   inc(items)
                 end;}
             {$ENDIF}

             if _is_CNL(FPL,nil)  then
                begin
                  smnu[items]:= Item(mnu_FPLM_CNL_, cmCNLm, nil);
                  inc(items);
                end;

             if _is_DEP(FPL, nil) then
                begin
                  add_newline(nl,items,smnu);
                  smnu[items]:= Item(mnu_FPLM_DEP_, cmDEPm, nil);
                  inc(items);
                end;

             if _is_MZP(FPL, nil) then
                begin
                  {smnu[items]:= SubMenu(' M~Z~P  ', WinMenu(' MZP ',nil,
                                            Item(' ~B~OD   ', cmFPL_FPLmzp_b,
                                            Item(' ~T~RA†  ', cmFPL_FPLmzp_t,
                                            nil) ) ),
                                           nil);}
                  smnu[items]:= Item(mnu_FPLM_MZP_, cmMZPm, nil);
                  inc(items);
                end;

           { ENDIF}

             if _is_RTE(FPL, nil) then
                begin
                  {if (FPL^.bodov>2) then
                     smnu[items]:= SubMenu(' ~R~TE  ', WinMenu(' RTE ',nil,
                                               Item(' ~B~OD   ', cmFPL_FPLrte_b,
                                               Item(' ~T~RA†  ', cmFPL_FPLrte_t,
                                               nil) ) ),
                                              nil)
                  else}
                  smnu[items]:= Item(mnu_FPLM_ETO_, cmETOm, nil);
                  inc(items);

                  alloc_EDD_STRIPmenu_items (oFPL,FPL, smnu,items,nl, false);
                  {add_newline(nl,items,smnu);}
                end;

           { IFDEF PROCESS_FPLM}
             if _is_ARR(FPL,nil) then
                begin
                  smnu[items]:= Item(mnu_FPLM_ARR_, cmARRm, nil);
                  inc(items);
                end;

           {$ELSE}
             if _is_CHG(FPL,nil) then
                begin
                  if mil then cmX:= cmETOm_strip else cmX:= cmETOo_strip;
                  smnu[items]:= Item(mnu_FPLM_CHG_, cmX, nil);
                  inc(items)
                end;

             if mil then cmX:= cmCNLm_strip else cmX:= cmCNLo_strip;
             smnu[items]:= Item(mnuCNL, cmX, nil);
             inc(items);
           {$ENDIF}

          end;

       add_newline(nl,items,smnu);

       if    _plan
          or is_plani___(FPL^.trat, max_mFPL_15_r_hi, max_mFPL_15_rm, -1)
          or is_plani___(FPL^.pozn, max_mFPL_18_r_hi, max_mFPL_18_rm, -1)
             then
          begin
            smnu[items]:= Item(tit_VIEW, cmFPLMview, nil);
            inc(items);
          end;

       if    _plan or (miniSTRIP_mFPL<>full_strip) {$IFDEF EDD} or (miniSTRIP<>full_strip) {$ENDIF}
          or (not pis_STRIP_mFPL)
          or (not pis_STRIP_mFPL_15body)
          or true
             then
          begin
            smnu[items]:= Item(tit_STRIP, cmFPLMview_strip, nil);
            inc(items);
          end;

       {$IFDEF MAPY}
        smnu[items]:= Item(tit_DRAW, cmFPLMdraw, nil);
        inc(items);
       {$ENDIF}

       {$IFDEF PRN}
        smnu[items]:= Item(tit_PRINT, cmFPLMprint, nil);
        inc(items);
       {$ENDIF}

       {smnu[items]:= Item(' ~L~AM      ', cm_PLAN_LAM, nil);
       inc(items);}

       if enable then
          begin
            add_newline(nl,items,smnu);
            smnu[items]:= Item(tit_COPY{mnu_FPLM_}, cmFPLm, nil);
            inc(items);
          end;

       for i:= 0 to items-1 do FPLmenu^.AddItem(smnu[i]);

       alloc_FPLMmenu:= FPLmenu;
       m_restore_shape
     end;


  function _handle_plan_FPLM (var Ev: TEvent; FPLi: PDmFPL; oFPL: P_OFPL; sc: PScrollInd; dx,dy: int; _plan: bool): bool;
     var   FPLmenu : PWinMenu;
           x,y : int;
           FPL : DmFPL;
           s   : string;
     label E;
     begin
       _handle_plan_FPLM:= false;
       new_mFPL (FPLi,@FPL); { MUSI OSTAT }

       sc_menu_xy(sc, x,y, 0,0);
       FPLmenu:= alloc_FPLMmenu(@FPL,oFPL, _plan or ((oFPL<>nil) and pis_STRIP_mFPL));
       FPLmenu^.MoveRel(x+dx-FPLmenu^.x0,y+dy-FPLmenu^.y0);
       FPLmenu^.Run(Ev);
       Dispose(FPLmenu, Done);

       if ((Ev.What and evMessage) <> 0) {and (not zmeneny_mFPL(@FPL,true))} then
          if _handle_event_FPL_o_sc (Ev,sc,@FPL,oFPL,sc) then ClearEvent(Ev,nil);

       E : disp_mFPL(@FPL)
     end;


  function handle_strip_FPLm (var Ev: TEvent; sc: PScrollInd; FPLi: PDmFPL; oFPL: P_OFPL): bool;
     begin
       handle_strip_FPLm:= _handle_plan_FPLM (Ev,FPLi,oFPL,sc,7,20,false)
     end;

  function handle_plan_FPLm (var Ev: TEvent; sc: PScrollInd; FPLi: PDmFPL): bool;
     var   dx,dy : int;
     begin
       {if (iFPL=nil) then begin dx:= -123; dy:= -12 end else} begin dx:= 7; dy:= 20 end;
       handle_plan_FPLm:= _handle_plan_FPLM (Ev,FPLi,nil,sc,dx,dy,false);
     end;



{ -------------------------------
   spracovanie planovanych letov,
   vsetky su v stave "plan"...
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
  function handle_inactive_FPLm(sc: PScroller; FPLi: PDmFPL; typ: byte): bool;
     var   FPL      : DmFPL;
           FPLmenu  : PWinMenu;
           smnu : array[0..20] of PItem;
           items,i  : int;
           _Ev      : TEvent;
           x,y      : int;
           s        : string;
     label E;
     begin
       handle_inactive_FPLm:= false;
       new_mFPL(FPLi,@FPL);

       FPLmenu:= WinMenu(' '+code_FPLM_7a(@FPL)+' ',nil,nil);
       items:= 0;

       if {$IFDEF AIRBASE} ((typ=3) and (not _plan_pre(FPL.let)))
          {$ELSE}           (typ=3)
          {$ENDIF}
          {$IFNDEF PROCESS_FPLM} or true {$ENDIF}
          then typ:= 2;

       {$IFDEF PROCESS_FPLM}
         if (typ=3) and _is_CHG(FPLi,nil) then
            begin
              smnu[items]:= Item(tit_COPY{mnu_FPLM_}, cmFPLm, nil);
              inc(items)
            end;

         if (typ=3) and _is_CNL(FPLi,nil)  then
            begin
              smnu[items]:= Item(mnu_FPLM_CNL_, cmCNLm, nil);
              inc(items);
            end;

       {$ENDIF}

        if items>0 then
           begin
             smnu[items]:= NewLine(nil);
             inc(items)
           end;

        if    pis_STRIP_mFPL
           or is_plani___(FPL.trat, max_mFPL_15_r_hi, max_mFPL_15_rm, -1)
           or is_plani___(FPL.pozn, max_mFPL_18_r_hi, max_mFPL_18_rm, -1)
              then
           begin
             smnu[items]:= Item(tit_VIEW, cmFPLMview, nil);
             inc(items);
           end;

        smnu[items]:= Item(tit_STRIP, cmFPLMview_strip, nil);
        inc(items);

        {$IFDEF MAPY}
          smnu[items]:= Item(tit_DRAW, cmFPLMdraw, nil);
          inc(items);
        {$ENDIF}

        {$IFDEF PRN}
          smnu[items]:= Item(tit_PRINT, cmFPLMprint, nil);
          inc(items);
        {$ENDIF}

       {$IFDEF PROCESS_FPLM}
         smnu[items]:= NewLine(nil);
         inc(items);

         {$IFDEF AIRBASE}
           if (typ=3) and _is_SEND(FPLi,nil) then
              begin
                smnu[items]:= Item(tit_SEND, cmFPLMsend, nil);
                inc(items);
              end;
         {$ENDIF}

         smnu[items]:= Item(tit_COPY{mnu_FPLM_}, cmFPLm, nil);
         inc(items);
       {$ENDIF}

       for i:= 0 to items-1 do FPLmenu^.AddItem(smnu[i]);
       sc_menu_xy(sc, x,y, 0,0);
       FPLmenu^.MoveRel(x+10-FPLmenu^.x0,y+30-FPLmenu^.y0);
       FPLmenu^.Run(_Ev);
       Dispose(FPLmenu, Done);

       if ((_Ev.What and evMessage) <> 0) {and (not zmeneny_mFPL(@FPL,true))} then
          if _handle_event_FPL_o_sc (_Ev,sc,@FPL,nil,sc) then ClearEvent(_Ev,nil);

       E : disp_mFPL(@FPL)
     end;

  function handle_DB_list_2(sc: PScroller; FPLi: PDmFPL): bool; far;
     var   res : bool;
     begin
       res:= {$IFDEF OPL} handle_inactive_FPLm(sc,FPLi,2) {$ELSE} false {$ENDIF};
       handle_DB_list_2:= res
     end;

  function handle_DB_list_3(sc: PScroller; FPLi: PDmFPL): bool; far;
     var   res : bool;
     begin
       res:= {$IFDEF OPL} handle_inactive_FPLm(sc,FPLi,3) {$ELSE} false {$ENDIF};
       handle_DB_list_3:= res
     end;