  function _CHG_PRS_RPL(sc: PScroller; PRS: PPRS): bool; far;
     const f : Tcentr = (x: initX; y: initY; m: 1);
     var   E : TEvent;
           form : PFDP_AForm;
           PRSp,PRSn: TPRS;

     begin
       new_PRS(PRS,@PRSp);
       new_PRS(PRS,@PRSn);
       _CHG_PRS_RPL:= false;
       form:= New(PFDP_AForm,Init(f.x,f.y, f.m, msg_PRS_RPL_CHG,
                  @frm_PRS,SIZE_frm_PRS,
                  0,1, 0,0, 0,0,

                  @_PRS_init,@_PRS_image,@_PRS_check, nil,
                  @PRSn, @PRSp, nil, letvis, PRSn.stat,
                  false, sizeof(TPRS),nil,nil,@existuje_PRS,@zmeneny_PRS,

                  nil, @save_PRS_RPL, nil, @disp_PRS,
                  true, false, true
                  {$IFDEF ODOSLI_ULOZ}, true {$ENDIF}
                  {$IFDEF SKRY_OKNA}, false {$ENDIF}
                  {$IFDEF STATISTIKA_OPL}, nil {$ENDIF}
                  ));
       form^.arch:= false;
       form^.RunLocalFunc(E,nil);
       Dispose(form,Done);
       disp_PRS(@PRSn);
       disp_PRS(@PRSp)
     end;


  function _CNL_PRS_RPL(sc: PScroller; PRS: PPRS): bool; far;
     begin
       _CNL_PRS_RPL:= false;
       if Ask2(msgVERIPHY,ask_PRS_RPL_CNL+' ('+PRS^.kod+') ?',
               titNO,White,clBUTTON_COLOR,waitASK*18
              )<>ansAno then Exit;
       PRS^.stat:= cnst_cnl;
       DB_oprav(PRS, get_dbPRS_RPLfn,db_PRS_RIADKOV,@codeDB_PRS,@codekey_PRS_RPL,@dbchg_PRS_RPL, dbattr_PRS)
     end;


  function alloc_PRS_RPLmenu (PRS: PPRS; _plan: bool): PWinMenu; far;
     const max_items = 20;
     var   PRSenu   : PWinMenu;
           PRSitems  : array[0..max_items-1] of PItem;
           items,i   : int;
           nl        : bool;
           cond      : string;
     begin
       m_set_shape(HODINY);

       PRSenu:= WinMenu(' '+PRS^.kod+' ',nil,nil);
       items:= 0; nl:= false;

       PRSitems[items]:= Item(tit_CHG_, cm_PRS_RPL_CHG, nil);
       inc(items);

       PRSitems[items]:= Item(tit_CNL_, cm_PRS_RPL_CNL, nil);
       inc(items);

       PRSitems[items]:= NewLine(nil);
       inc(items);

       {IFDEF PRN
         PRSitems[items]:= Item(tit_PRINT, cmPRSprint, nil);
         inc(items);
       ENDIF}

       PRSitems[items]:= NewLine(nil);
       inc(items);

       PRSitems[items]:= Item(tit_PLAN_, cmPRS, nil);
       inc(items);

       for i:= 0 to items-1 do PRSenu^.AddItem(PRSitems[i]);

       alloc_PRS_RPLmenu:= PRSenu;
       m_restore_shape
     end;


  function handle_plan_PRS_RPL (var Ev: TEvent; sc: PScrollInd; PRSi: PPRS): bool; far;

     var   PRSenu : PWinMenu;
           x,y : int;
           _Ev : TEvent;

     label E;

     begin
       handle_plan_PRS_RPL:= false;

       sc_menu_xy(sc, x,y, 0,0);
       PRSenu:= alloc_PRS_RPLmenu(PRSi, true);
       PRSenu^.MoveRel(x+7-PRSenu^.x0,y+20-PRSenu^.y0);
       PRSenu^.Run(_Ev);
       Dispose(PRSenu, Done);

       if ((_Ev.What and evMessage) <> 0) then
          begin
            { nepotrebujem kontrolovat existenciu planu,
              pretoze tento nebude zruseny
            }
            _handle_event_PRS (_Ev,sc,PRSi)
          end;
     end;


  procedure prehlad_PRS_RPL;
      var   s: string;
      begin
        s:= cnst_planned;
        if CNL_RPL_VYPIS then s:= s+cnst_cnl;
        spracuj_PRS(false,false,
                    false,false,true,
                    s,@_is_stata_PRS,
                    @handle_plan_PRS_RPL, _TBFunc_vEp2,
                    true,false,
                    tit_PLAN_RPL,nil,nil
                   )
      end;
