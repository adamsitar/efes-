{$IFDEF FPL}

 procedure item_cFPL(p: PDcFPL; x,y: int; b: bool); far;
     var   bk : byte;
     begin
       if b then bk:= itScrollApp else bk:= bkScrollApp;
       if b then BGIgraph.button(x-1,y,x+TextWidth('W')*kod_7a+1,y+TextHeight('H'),bk, btSmall,btOFF)
       else FillWin(x-1,y,x+TextWidth('W')*kod_7a+1,y+TextHeight('H'), bk);
       SetColor(pozCL[p^.poz]);
       OutTextXY(x,y+1,p^.idn)
     end;

 function _handle_plan_FPLc (var Ev: TEvent; sc: PScrollInd; FPLi: PDcFPL; oFPL: P_OFPL): bool; far;
    begin
      _handle_plan_FPLc:= _FPLMs._handle_plan_FPLc(Ev, FPLi,oFPL, sc,-123,-12, true,false)
    end;

 procedure item_iFPL(p: PDmFPL; x,y: int; b: bool); far;
     var   bk : byte;
     begin
       if p^.poz=poz_PATRAT then bk:= bk_PATRAT
       else if b then bk:= itScrollApp
       else bk:= bkScrollApp;
       if b then BGIgraph.button(x-1,y,x+TextWidth('W')*kod_7a+1,y+TextHeight('H'),bk, btSmall,btOFF)
       else FillWin(x-1,y,x+TextWidth('W')*kod_7a+1,y+TextHeight('H'), bk);
       SetColor(p^.cl);
       OutTextXY(x,y+1,idn_mFPL(p))
     end;

 function _handle_plan_FPLm (var Ev: TEvent; sc: PScrollInd; FPLi: PDmFPL; iFPL: P_OFPL): bool; far;
    begin
      _handle_plan_FPLm:= _FPLMs._handle_plan_FPLm(Ev, FPLi,oFPL, sc,-123,-12, true)
    end;

{$ENDIF}


constructor T_GUI.Init(_Owner: PApp);
      begin
        inherited Init(_Owner, 0,btHEIGHT+3, MaxX, MaxY);

        HODINY_init(_Owner {@Self},0,0);
        {$IFDEF STATUS}
         STATUS_init(_Owner {$IFDEF DATA_WRITTEN_IN_APP}{@Self},nil{$ENDIF});
        {$ENDIF}

        {$IFDEF MAPY}
         MAPY_init(@Self,
                   @PLANZET_MAPA,
                   {$IFDEF FPL} @imit_targets, @mapa_handle_target, @mapa_cursor_shape
                   {$ELSE} nil, nil, nil
                   {$ENDIF}
                  );
         sirka_prelety:= 0;
        {$ENDIF}

        {$IFDEF FPL}
         mFPL_prel:= New(PScrollApp,Init(@Self,

                             '~V~ojaci',
                             mFPL^.ap,@mFPL^.top,
                             true,
                             @mFPL^.is_chg,@mFPL^.arr_chg,@mFPL^.s_loadDB,
                             0,nil,nil,

                             nil,nil,nil{@comp_idn_mFPL},

                             4,dy_ScrollApp,
                             tabSIRKA_ITEM,tabVYSKA_ITEM,
                             dxi,dyi, 0,bkScrollApp,
                             @item_iFPL,
                             1, true,true,true,

                             _TBFunc_vEp3, @_handle_plan_FPLm, mFPL,

                             @tab_mFPL,
                             cm_mFPL_scroll,
                             hlp_PREHLAD_mFPL)
                            );
         mFPL^.p_viewer:= mFPL_prel;

         oFPL_prel:= New(PScrollApp,Init(@Self,

                             '~I~n¡',
                             oFPL^.ap,@oFPL^.top,
                             true,
                             @oFPL^.is_chg,@oFPL^.arr_chg,@oFPL^.s_loadDB,
                             0,nil,nil,

                             nil,nil,nil{@comp_idn_mFPL},

                             4,dy_ScrollApp,
                             tabSIRKA_ITEM,tabVYSKA_ITEM,
                             dxi,dyi, 0,bkScrollApp,
                             @item_iFPL,
                             1, true,true,true,

                             _TBFunc_vEp3, @_handle_plan_FPLm, oFPL,

                             @tab_oFPL,
                             cm_oFPL_scroll,
                             hlp_PREHLAD_oFPL)
                            );
         oFPL^.p_viewer:= oFPL_prel;

         cFPL_prel:= New(PScrollApp,Init(@Self,

                             '~L~inky',
                             cFPL^.ap,@cFPL^.top,
                             true,
                             @cFPL^.is_chg,@cFPL^.arr_chg,@cFPL^.s_loadDB,
                             0,nil,nil,

                             nil,nil,@comp_idn_cFPL,

                             4,dy_ScrollApp,
                             tabSIRKA_ITEM,tabVYSKA_ITEM,
                             dxi,dyi, 0,bkScrollApp,
                             @item_cFPL,
                             1, true,true,true,

                             _TBFunc_vEp3, @_handle_plan_FPLc, nil,

                             @tab_cFPL,
                             cm_cFPL_scroll,
                             hlp_PREHLAD_cFPL)
                            );
         cFPL^.p_viewer:= cFPL_prel;
         sirka_prelety:= mFPL_prel^._win_.x1 - mFPL_prel^._win_.x0;
        {$ENDIF}

        {$IFDEF MAPY}
         _4okno:= Mapa; last_active:= _4okno;
         reinit_;
        {$ENDIF}

        {$IFDEF FPL}
         _tab_mFPL:= tab_mFPL; _tab_cFPL:= tab_cFPL; _tab_oFPL:= tab_oFPL;
        {$ENDIF}

        hlpXXX:= hlp_GUI;

        set_region(0, dMapaY0, 0, dMapaY1, btcdXY);
        set_region(0, dMapaY0, 0, dMapaY1, btmdXY);
        sc_dy:= 20
      end;


function T_GUI.next_active(P: PView): PView;
   begin
     P:= GetView( NextObjectReg(GetObjectReg(P)) );
     if not set_Active(P) then P:= next_active(P); { ! rekurzia }
     next_active:= P
   end;

function T_GUI.prev_active(P: PView): PView;
   begin
     P:= GetView( PrevObjectReg(GetObjectReg(P)) );
     if not set_Active(P) then P:= prev_active(P); { ! rekurzia }
     prev_active:= P
   end;

function T_GUI.set_active(P: PView): bool;
   begin
     set_active:= P^.visible;
     if not (P^.visible) then exit;
     if last_active=P then P:= _4okno;
     last_active^.ActiveOff;
     P^.ActiveOn;
     last_active:= P
   end;


function T_GUI.reinit_: int;
   var   x, dy, y0m,y0c,y0a, page, pocet: int;
   begin
     Clock^.ReInit(0,0,MaxX,MaxY);
    {$IFDEF STATUS}
     STATUS_reinit;
    {$ENDIF}

     x1:= MaxX;
     y0:= btmdXY.y0; y1:= MaxY-btmdXY.y1;
     x := x1 - sirka_prelety;

     {$IFDEF FPL}
      pocet:= (ord(tab_mFPL) and 1) + (ord(tab_cFPL) and 1) + (ord(tab_oFPL) and 1);
      if pocet<>0 then
         begin
           dy  := (MaxY - (btmdXY.y0+3+btmdXY.y1)) div pocet;     { vyska pre tabulky preletov }
           y0m := y0;                                             { pozicia vojakov }
           y0a := y0m + dy * (ord(tab_mFPL) and 1);               { pozicia civilov }
           y0c := y0m + dy * ((ord(tab_mFPL) and 1) + (ord(tab_oFPL) and 1)); { pozicia ostatnych }
           page:= (dy-winHEIGHT-6) div (tabVYSKA_ITEM + mFPL_prel^.medzera);
           mFPL_prel^.reinit_(x,y0m,page);
           oFPL_prel^.reinit_(x,y0a,page);
           cFPL_prel^.reinit_(x,y0c,page);
           {$IFDEF MAPY}
            set_region(0,btmdXY.y0,MaxX-x+4,btmdXY.y1, btMapydXY)
           {$ENDIF}
         end
      else begin
             mFPL_prel^.hide;
             oFPL_prel^.hide;
             cFPL_prel^.hide;
             {$IFDEF MAPY}
              set_region(0,btmdXY.y0,0, btmdXY.y1, btMapydXY)
             {$ENDIF}
           end;
     {$ELSE}
      {$IFDEF MAPY}
       set_region(0,btmdXY.y0,0, btmdXY.y1, btMapydXY);
      {$ENDIF}
     {$ENDIF}

     reinit_:= pocet
   end;


procedure T_GUI.reorganize(_draw: bool);

    {$IFDEF FPL}
     procedure reorg_tab_iFPL(iFPL_prel: PScrollApp; tab_iFPL: bool; var _tab_iFPL: bool);
         begin
           iFPL_prel^.Draw;
           _tab_iFPL:= tab_iFPL
         end;
    {$ENDIF}

    var   bp: bool;
          xl,yl: int;

    begin
      m_off(bp, xl,yl);
      if reinit_ = 0 then
         begin
          {$IFDEF MAPY}
           if Mapa^.x1 < MaxX then
              begin
                ClrWin(MaxX-sirka_prelety-3,y0,x1,y1, 0);
                Mapa^.Kresli(true)
              end
          {$ENDIF}
         end
      else begin
             {$IFDEF FPL}
              mFPL^.sort;
              oFPL^.sort;
              if _draw then {if (_tab_mFPL<>tab_mFPL) or (_tab_cFPL<>tab_cFPL) or (_tab_aFPL<>tab_aFPL) then}
                 begin
                   ClrWin(MaxX-sirka_prelety-3,y0,x1,y1, 0);
                   reorg_tab_iFPL(mFPL_prel, tab_mFPL, _tab_mFPL);
                   reorg_tab_iFPL(oFPL_prel, tab_oFPL, _tab_oFPL);
                   reorg_tab_iFPL(cFPL_prel, tab_cFPL, _tab_cFPL);
                 end;
             {$ENDIF}
             {$IFDEF MAPY}
              if _draw and (Mapa^.x1 = MaxX) then Mapa^.Kresli(true);
             {$ENDIF}
           end;
      m_on(bp, xl,yl)
    end;
