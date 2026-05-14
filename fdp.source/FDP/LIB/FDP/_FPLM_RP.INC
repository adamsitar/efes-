{$IFDEF MATCA}

  function _CHG_FPLM_RPL(sc: PScroller; FPL: PDmFPL): bool; far;
     const f : Tcentr = (x: initX; y: initY; m: 1);
     var   E : TEvent;
           form : PmFPLform;
           FPLp,FPLn: DmFPL;

     begin
       new_mFPL(FPL,@FPLp);
       new_mFPL(FPL,@FPLn);
       _CHG_FPLM_RPL:= false;
       form:= New(PmFPLform,Init(f.x,f.y, f.m, msg_FPL_RPL_CHG,
                  @mFPL_init, nil, i_15M,

                  @FPLn, @FPLp, nil,
                  letvis,cnst_disk,false,

                  nil, @save_mFPL_RPL,nil,
                  hlp_mFPL {$IFDEF ODOSLI_ULOZ}, true {$ENDIF}
                  )
                 );
       form^.arch:= false;
       form^.RunLocalFunc(E,nil);
       Dispose(form,Done);
       disp_mFPL(@FPLn);
       disp_mFPL(@FPLp)
     end;


  function _CNL_FPLM_RPL(sc: PScroller; FPL: PDmFPL): bool; far;
     begin
       _CNL_FPLM_RPL:= false;
       if Ask2(msgVERIPHY,ask_FPL_RPL_CNL+' '+code_FPLM_7a(FPL)+' ?',
               titNO,White,clBUTTON_COLOR,waitASK*18
              )<>ansAno then Exit;
       FPL^.stat:= cnst_cnl;
       DB_oprav(FPL, get_fn_mFPL_RPL_let,db_mFPL_RIADKOV,@codeDB_FPLM,@codekey_FPLM,@dbchg_mFPL_RPL, dbattr_FPM)
     end;


  function alloc_FPLm_RPLmenu (FPL: PDmFPL; _plan: bool): PWinMenu; far;
     const max_items = 20;
     var   FPLmenu   : PWinMenu;
           FPLitems  : array[0..max_items-1] of PItem;
           items,i   : int;
           nl        : bool;
           cond      : string;
     begin
       m_set_shape(HODINY);

       FPLmenu:= WinMenu(' '+code_FPLM_7a(FPL)+' ',nil,nil);
       items:= 0; nl:= false;

       FPLitems[items]:= Item(mnu_FPLM_CHG_, cm_FPLM_RPL_CHG, nil);
       inc(items);

       FPLitems[items]:= Item(mnu_FPLM_CNL_, cm_FPLM_RPL_CNL, nil);
       inc(items);

       FPLitems[items]:= NewLine(nil);
       inc(items);

       {$IFDEF MAPY}
         FPLitems[items]:= Item(tit_DRAW, cmFPLMdraw, nil);
         inc(items);
       {$ENDIF}

       {IFFDEF PRN
         FPLitems[items]:= Item(tit_PRINT, cmFPLMprint, nil);
         inc(items);
       ENDIF}

       FPLitems[items]:= NewLine(nil);
       inc(items);

       FPLitems[items]:= Item(mnu_FPLM_, cmFPLm, nil);
       inc(items);

       for i:= 0 to items-1 do FPLmenu^.AddItem(FPLitems[i]);

       alloc_FPLm_RPLmenu:= FPLmenu;
       m_restore_shape
     end;


  function handle_plan_FPLm_RPL (var Ev: TEvent; sc: PScrollInd; FPLi: PDmFPL): bool; far;

     var   FPLmenu : PWinMenu;
           x,y : int;
           _Ev : TEvent;

     label E;

     begin
       handle_plan_FPLm_RPL:= false;

       FPLmenu:= alloc_FPLm_RPLmenu(FPLi, true);
       sc_menu_xy(sc, x,y, 0,0);
       FPLmenu^.MoveRel(x+7-FPLmenu^.x0,y+20-FPLmenu^.y0);
       FPLmenu^.Run(_Ev);
       Dispose(FPLmenu, Done);

       if ((_Ev.What and evMessage) <> 0) then
          begin
            { nepotrebujem kontrolovat existenciu planu,
              pretoze tento nebude zruseny
            }
            _handle_event_FPL_o_sc (_Ev,sc,FPLi,nil,sc)
          end;
     end;


  procedure prehlad_mFPL_RPL;
      var   s: string;
      begin
        s:= cnst_planned;
        if CNL_RPL_VYPIS then s:= s+cnst_cnl;
        spracuj_mFPL(false,false,
                     false,false,true,true,
                     s,@_is_stata_FPLM,
                     @handle_plan_FPLm_RPL, _TBFunc_vEp2,
                     true,false,
                     msg_FPL_RPL,
                     nil,hlp_zoznam
                    )
      end;

{$ENDIF}