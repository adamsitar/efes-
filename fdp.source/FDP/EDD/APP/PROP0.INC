procedure TPropButton._do_it(var _Event: TEvent);
    begin
      {$IFDEF MAPY}
        if PLANZET_MAPA then Exit;
      {$ENDIF}
      inherited _do_it(_Event)
    end;


constructor TwinPROP.Init(_Owner: PGroup);
      const {$IFNDEF EDD_20} _dy1 = 34; _dxi = 4; _dyi = 5; _mdz = 5; _dyt = 9;
            {$ELSE}          _dy1 = 40; _dxi = 8; _dyi = 8; _mdz = 8; _dyt = 14;
            {$ENDIF}
      begin
        set_region(0,y0_winPROP, MaxX,y1_winPROP, reg);
        inherited Init(_Owner,2{2}, reg.x0+11,reg.y0+_dy1, dx_PROP,dy_PROP, _dxi,_dyi,_mdz, black, true,true,
                       nil {_item_list: Pproc_i3b},
                       nil, @is_chg{nil}, nil
                      );
        in_frame:= false;
        sb_left;
        btTitle:= New(PButton,Init(@Self,
                      (x1-x0-textwidth(tit_PRO)) div 2, reg.y0 + _dyt,textwidth(tit_PRO)+10{dbtWIDTH},dbtHEIGHT,
                      kbNoKey, cm_PROP_clicked,tit_PRO,1,clKey,clItem)
                     );
        btTitle^.kbAct:= kbEnter; btTitle^.local_ev:= false;
        PIS := true;

        is_to_ack:= false;
        prop_cFPL_top:= -1; prop_mFPL_top:= -1; prop_oFPL_top:= -1;
      end;


procedure TwinPROP.Draw;

   { reinicializacia tabletu, treba prepocitat zobrazenie
     planov podla sektorizacie
   }
   procedure add_FPLi(_FPLi: P_OFPL; _top: int{$IFDEF SECTORS}; _S_DISPLAY,_TABLET_REINIT: bool{$ENDIF});
       var   bres,is : bool;
             i : int;
       begin
         for i:= 0 to _top do
           begin
             is:= true;
             {$IFDEF SECTORS}
              if not _S_DISPLAY then is:= true
              else if _TABLET_REINIT then is:= _FPLi^.is_to_addS(_FPLi^.ap^[i])
              else is:= _FPLi^.get_on_sector(_FPLi^.ap^[i]);
              _FPLi^.set_on_sector(_FPLi^.ap^[i],is);
             {$ENDIF}
             if is then Add(_FPLi,i)
           end
       end;

    begin
      if PLANZET_MAPA then Exit;

      if PROP_TABLET_REINIT then
         begin
          {$IFDEF SECTORS}
            S_UPDATE:= absTime;
          {$ENDIF}
         end;

      PIS := true;
      with reg do bgigraph.button(x0,y0, x1,y1, clPROP_TABLET, btNorm, btOFF);
      list_disp;
      inherited Draw;

      {$IFDEF FPL0}
       add_FPLi(PROP_cFPL,PROP_cFPL^.top{$IFDEF SECTORS}, S_DISPLAY,PROP_TABLET_REINIT{$ENDIF});
       add_FPLi(PROP_mFPL,PROP_mFPL^.top{$IFDEF SECTORS}, S_DISPLAY,PROP_TABLET_REINIT{$ENDIF});
       add_FPLi(PROP_oFPL,PROP_oFPL^.top{$IFDEF SECTORS}, S_DISPLAY,PROP_TABLET_REINIT{$ENDIF});
      {$ENDIF}

      PROP_TABLET_REINIT:= false
    end;


procedure TwinPROP.reinit_;
    begin
      is_to_ack:= true;
    end;


procedure TwinPROP.item_list(i, x,y: int; b: bool);
    var   _miniSTRIP: T_strip;
          _pis_STRIP_mFPL,_STRIP_DIR: bool;
    begin
      _miniSTRIP:= miniSTRIP; _pis_STRIP_mFPL:= pis_STRIP_mFPL; _STRIP_DIR:= STRIP_DIR;
      miniSTRIP:= full_strip; pis_STRIP_mFPL:= false; STRIP_DIR:= false;
      with FPLs^[i]^ do iFPL^.strip(ind, x,y+2, b);
      miniSTRIP:= _miniSTRIP; pis_STRIP_mFPL:= _pis_STRIP_mFPL; STRIP_DIR:= _STRIP_DIR
    end;