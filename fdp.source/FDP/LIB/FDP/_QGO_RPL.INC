  function _CHG_QGO_RPL(sc: PScroller; QGO: PQGO): bool; far;
     const f : Tcentr = (x: initX; y: initY; m: 1);
     var   E : TEvent;
           form : PFDP_AForm;
           QGOp,QGOn: TQGO;

     begin
       new_QGO(QGO,@QGOp);
       new_QGO(QGO,@QGOn);
       _CHG_QGO_RPL:= false;
       form:= New(PFDP_AForm,Init(f.x,f.y, f.m, msg_QGO_RPL_CHG,
                  @Form_QGO,SIZE_frm_QGO,
                  0,1, 0,0, 0,0,

                  @_QGO_init,@_QGO_image,@_QGO_check, nil,
                  @QGOn, @QGOp, nil, letvis, QGOn.stat,
                  false, sizeof(TQGO),nil,nil,nil,nil,
                  nil, @save_QGO_RPL, nil, @disp_QGO,

                  true, false, true
                  {$IFDEF ODOSLI_ULOZ}, true {$ENDIF}
                  {$IFDEF SKRY_OKNA}, false {$ENDIF}
                  {$IFDEF STATISTIKA_OPL}, nil {$ENDIF}
                  ));
       form^.arch:= false;
       form^.RunLocalFunc(E,nil);
       Dispose(form,Done);
       disp_QGO(@QGOn);
       disp_QGO(@QGOp)
     end;


  function _CNL_QGO_RPL(sc: PScroller; QGO: PQGO): bool; far;
     begin
       _CNL_QGO_RPL:= false;
       if Ask2(msgVERIPHY,ask_QGO_RPL_CNL+' ('+QGO^.kod+') ?',
               titNO,White,clBUTTON_COLOR,waitASK*18
              )<>ansAno then Exit;
       QGO^.stat:= cnst_cnl;
       DB_oprav(QGO, get_dbQGO_RPLfn,db_QGO_RIADKOV,@codeDB_QGO,@codekey_QGO_RPL,@dbchg_QGO_RPL, dbattr_QGO)
     end;


  function alloc_QGO_RPLmenu (QGO: PQGO; _plan: bool): PWinMenu; far;
     const max_items = 20;
     var   QGOenu   : PWinMenu;
           QGOitems  : array[0..max_items-1] of PItem;
           items,i   : int;
           nl        : bool;
           cond      : string;
     begin
       m_set_shape(HODINY);

       QGOenu:= WinMenu(' '+QGO^.kod+' ',nil,nil);
       items:= 0; nl:= false;

       QGOitems[items]:= Item(tit_CHG_, cm_QGO_RPL_CHG, nil);
       inc(items);

       QGOitems[items]:= Item(tit_CNL_, cm_QGO_RPL_CNL, nil);
       inc(items);

       QGOitems[items]:= NewLine(nil);
       inc(items);

       {IFDEF PRN
         QGOitems[items]:= Item(tit_PRINT, cmQGOprint, nil);
         inc(items);
       ENDIF}

       QGOitems[items]:= NewLine(nil);
       inc(items);

       QGOitems[items]:= Item(tit_PLAN_, cmQGO, nil);
       inc(items);

       for i:= 0 to items-1 do QGOenu^.AddItem(QGOitems[i]);

       alloc_QGO_RPLmenu:= QGOenu;
       m_restore_shape
     end;


  function handle_plan_QGO_RPL (var Ev: TEvent; sc: PScrollInd; QGOi: PQGO): bool; far;

     var   QGOenu : PWinMenu;
           x,y : int;
           _Ev : TEvent;

     label E;

     begin
       handle_plan_QGO_RPL:= false;

       sc_menu_xy(sc, x,y, 0,0);
       QGOenu:= alloc_QGO_RPLmenu(QGOi, true);
       QGOenu^.MoveRel(x+7-QGOenu^.x0,y+20-QGOenu^.y0);
       QGOenu^.Run(_Ev);
       Dispose(QGOenu, Done);

       if ((_Ev.What and evMessage) <> 0) then
          begin
            { nepotrebujem kontrolovat existenciu planu,
              pretoze tento nebude zruseny
            }
            _handle_event_QGO (_Ev,sc,QGOi)
          end;
     end;


  procedure prehlad_QGO_RPL;
      var   s: string;
      begin
        s:= cnst_planned;
        if CNL_RPL_VYPIS then s:= s+cnst_cnl;
        spracuj_QGO(get_dbQGO_RPLfn,@dbchg_QGO_RPL,
                    s,@_is_stata_QGO,
                    @handle_plan_QGO_RPL, _TBFunc_vEp2,
                    true,
                    tit_PLAN_RPL,nil
                   )
      end;
