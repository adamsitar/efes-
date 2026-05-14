{$IFDEF EDD}
  procedure ack_PROP_FPL;
      var   i : int;
      begin
       { prevzatie navrhovanych stripov zaradenych v okne PROPOSED }
        with winPROP^ do while top>=0 do accept(0);
       { Prevzatie navrhovanych stripov, ktore nie su zaradene do PROPOSED,
         pretoze nepatria na sektor, alebo z ineho dovodu tam nie su zaradene.
         Prerobit filozofiu spracovania prop...
       }
        while (PROP_cFPL^.top>=0) do with PROP_cFPL^ do
          begin
            cFPL^.add(ap^[0]);
            del(0)
          end;
      end;

  procedure cnl_PROP_FPL;
      begin
        with winPROP^ do while top>=0 do decline(0);
        with PROP_cFPL^ do while top>=0 do del(0)
      end;

  procedure cnl_ALL_FPL(confirm: bool);
      begin
        if     confirm
           and (Ask2(msgWARNING,' Are you sure you want delete all strips ? ','',White,clBUTTON_COLOR,130)<>ansAno)
               then Exit;

        with cFPL^ do while top>=0 do Del(top);
        with mFPL^ do while top>=0 do Del(top);
       {$IFDEF FPLO}
        with oFPL^ do while top>=0 do Del(top);
       {$ENDIF}
      end;
{$ENDIF}


 constructor TEDDapp.Init;
       var   _btmdx1: int;
       begin
         TABLET_EDD:= true;

        {$IFDEF MAPY}
         PLANZET_MAPA:= false;
         if not TABLET_EDD then GraphMode:= GraphMode_MAPA else;
         set_region(0, dMapaY0, 0, dMapaY1, btcdXY);
         set_region(0, dMapaY0, 0, dMapaY1, btmdXY);
        {$ENDIF}

         GraphMode:= _TIGA;
         {$IFNDEF EDD_20} GraphMode:= _SVGA; {$ELSE} GraphMode:= {$IFNDEF DEBUG}_TIGA{$ELSE}_SVGA{$ENDIF}; {$ENDIF}
         {IFDEF DEBUG GraphMode:= _VESA; ENDIF}
         inherited Init(@Self,@EDDmenu_init, @LOGO,titFDP+' '+titSPC+titVER, titCR);
         EDDgui:= New(P_GUI, Init(@Self));

        {$IFDEF SECTORS}
         proc_sector_chg(SECTORm,false);
        {$ENDIF}

        {$IFDEF SPEA} hlp_dy0:= 250; hlp_dy1:= 100 {$ENDIF}
       end;


 procedure TEDDapp.InitEXT_drivers;
     begin
      {$IFDEF EXTERNAL_NET}
      { ---------------
        EXTERNAL NET
        תתתתתתתתתתתתתתת
      }
       {$IFDEF CONNECT_TO_ASOC}  { Kvoli uz inicializovanemu protokolu NET }
        DEV_ASOC:= New(PO_ASOC,Init);
       {$ENDIF}
      {$ENDIF}
     end;


{$IFDEF MAPY}
  procedure TEDDapp.Draw;
      begin
        if not TABLET_EDD then GraphMode_MAPA:= GraphMode;
        inherited Draw;
        EN_GRAPH_MODE_SWITCH:= PLANZET_MAPA
      end;

  procedure TEDDapp.switch_TABLET;
      var   b,b2 : bool;
            Ev   : TEvent;
            bp : bool; xlm,ylm: int;
      begin
        m_off (bp, xlm,ylm);

        PLANZET_MAPA:= not TABLET_EDD;
        ClrWin(0,MaxY-dY1,MaxX,MaxY, 0);
        ClrWin(0,{y1_winPROP}bar_mnuXY.y1+1, MaxX,y1_winPROP+20, 0);
        if TABLET_EDD then
           begin
             GraphMode_MAPA:= GraphMode;
             {$IFNDEF EDD_20} GraphMode:= _SVGA
             {$ELSE}          GraphMode:= _TIGA
             {$ENDIF}
           end
        else GraphMode:= GraphMode_MAPA;

        EN_GRAPH_MODE_SWITCH:= true;
        SetCommand(Ev,cmGraphModeChanged);
        inherited HandleEvent(Ev);
        EN_GRAPH_MODE_SWITCH:= PLANZET_MAPA;
       {$IFDEF SECTORS}
        S_UPDATE:= absTime;
       {$ENDIF}
        m_on (bp, xlm,ylm);
      end;
{$ENDIF}
