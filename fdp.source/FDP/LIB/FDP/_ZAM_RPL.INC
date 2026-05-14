  function _CHG_ZAM_RPL(sc: PScroller; ZAM: PZAM): bool; far;
     const f : Tcentr = (x: initX; y: initY; m: 1);
     var   E : TEvent;
           form : PFDP_AForm;
           ZAMp,ZAMn: TZAM;

     begin
       new_ZAM(ZAM,@ZAMp);
       new_ZAM(ZAM,@ZAMn);
       _CHG_ZAM_RPL:= false;
       form:= New(PFDP_AForm,Init(f.x,f.y, f.m, msg_ZAM_RPL_CHG,
                  @frm_ZAM,SIZE_frm_ZAM,
                  0,1, 0,0, 0,0,

                  @_ZAM_init,@_ZAM_image,@_ZAM_check, nil,
                  @ZAMp, @ZAMn, nil, letvis, ZAMn.stat,

                  false, sizeof(TZAM),nil,nil,nil,nil,
                  nil, @save_ZAM_RPL, nil,@disp_ZAM,

                  true, false, true
                  {$IFDEF ODOSLI_ULOZ}, true {$ENDIF}
                  {$IFDEF SKRY_OKNA}, false {$ENDIF}
                  {$IFDEF STATISTIKA_OPL}, nil {$ENDIF}
                  ));
       form^.arch:= false;
       form^.RunLocalFunc(E,nil);
       Dispose(form,Done);
       disp_ZAM(@ZAMn);
       disp_ZAM(@ZAMp)
     end;


  function _CNL_ZAM_RPL(sc: PScroller; ZAM: PZAM): bool; far;
     begin
       _CNL_ZAM_RPL:= false;
       if Ask2(msgVERIPHY,ask_ZAM_RPL_CNL+' ('+ZAM^.kod+') ?',
               titNO,White,clBUTTON_COLOR,waitASK*18
              )<>ansAno then Exit;
       ZAM^.stat:= cnst_cnl;
       DB_oprav(ZAM, get_dbZAM_RPLfn,db_ZAM_RIADKOV,@codeDB_ZAM,@codekey_ZAM_RPL,@dbchg_ZAM_RPL, dbattr_ZAM)
     end;


  function alloc_ZAM_RPLmenu (ZAM: PZAM; _plan: bool): PWinMenu; far;
     const max_items = 20;
     var   ZAMenu   : PWinMenu;
           ZAMitems  : array[0..max_items-1] of PItem;
           items,i   : int;
           nl        : bool;
           cond      : string;
     begin
       m_set_shape(HODINY);

       ZAMenu:= WinMenu(' '+ZAM^.kod+' ',nil,nil);
       items:= 0; nl:= false;

       ZAMitems[items]:= Item(tit_CHG_, cm_ZAM_RPL_CHG, nil);
       inc(items);

       ZAMitems[items]:= Item(tit_CNL_, cm_ZAM_RPL_CNL, nil);
       inc(items);

       ZAMitems[items]:= NewLine(nil);
       inc(items);

       {IFDEF PRN
         ZAMitems[items]:= Item(tit_PRINT, cmZAMprint, nil);
         inc(items);
       ENDIF}

       ZAMitems[items]:= NewLine(nil);
       inc(items);

       ZAMitems[items]:= Item(tit_PLAN_, cmZAM, nil);
       inc(items);

       for i:= 0 to items-1 do ZAMenu^.AddItem(ZAMitems[i]);

       alloc_ZAM_RPLmenu:= ZAMenu;
       m_restore_shape
     end;


  function handle_plan_ZAM_RPL (var Ev: TEvent; sc: PScrollInd; ZAMi: PZAM): bool; far;

     var   ZAMenu : PWinMenu;
           x,y : int;
           _Ev : TEvent;

     label E;

     begin
       handle_plan_ZAM_RPL:= false;

       sc_menu_xy(sc, x,y, 0,0);
       ZAMenu:= alloc_ZAM_RPLmenu(ZAMi, true);
       ZAMenu^.MoveRel(x+7-ZAMenu^.x0,y+20-ZAMenu^.y0);
       ZAMenu^.Run(_Ev);
       Dispose(ZAMenu, Done);

       if ((_Ev.What and evMessage) <> 0) then
          begin
            { nepotrebujem kontrolovat existenciu planu,
              pretoze tento nebude zruseny
            }
            _handle_event_ZAM (_Ev,sc,ZAMi)
          end;
     end;


  procedure prehlad_ZAM_RPL;
      var   s: string;
      begin
        s:= cnst_planned;
        if CNL_RPL_VYPIS then s:= s+cnst_cnl;
        spracuj_ZAM(get_dbZAM_RPLfn,@dbchg_ZAM_RPL,
                    s,@_is_stata_ZAM,
                    @handle_plan_ZAM_RPL, _TBFunc_vEp2,
                    true,false,
                    tit_PLAN_RPL
                   )
      end;
