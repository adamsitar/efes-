constructor TwinACC.Init(_Owner: PGroup; _miniSTRIP: T_strip);
      var   fn: string;
      begin
        max_rdk:= max_rdkv_[lineSTRIP];
        inherited Init(_Owner, 0,y1_winPROP+{$IFNDEF EDD_20}3{$ELSE}5{$ENDIF},MaxX,MaxY-(y1_winPROP+5));

        fillchar(Tablet,sizeof(Tablet),0); { = nil }
        fillchar(tab_strip2,sizeof(tab_strip2),0);
        fillchar(tab_strip3,sizeof(tab_strip3),0);
        fillchar(tab_strip4,sizeof(tab_strip4),0);

        fillchar(SpecGroups,sizeof(SpecGroups),0);

        miniSTRIP:= _miniSTRIP;
        stlpcov:= _stlpcov(miniSTRIP);
        STablet:= _tab_strip(miniSTRIP);

        act_stl:= -1; act_ind:= -1;

        if FExists(USER_TABLET_CFG)<>0 then fn:= TABLET_CFG else fn:= USER_TABLET_CFG;
        read_tablet_cfg(fn)
      end;

destructor TwinACC.Done;
     var   i: int;
     begin
       save_tablet_cfg(USER_TABLET_CFG);
       zrus_zoznamy;
       inherited Done;

       for i:= 0 to stl_strip2-1 do disp_Stlpec(tab_strip2[i]);
       for i:= 0 to stl_strip3-1 do disp_Stlpec(tab_strip3[i]);
       for i:= 0 to stl_strip4-1 do disp_Stlpec(tab_strip4[i])
     end;


function TwinACC.inView(x,y: int): bool;
   begin
     inView:= (not PLANZET_MAPA) and inherited inView(x,y)
   end;

procedure TwinACC._draw(_miniSTRIP: T_strip);
    var   i,j: int;
    begin
      if PLANZET_MAPA then Exit;
      miniSTRIP:= _miniSTRIP;
      Draw
    end;

procedure TwinACC.Draw;
    var   i,j: int;
          bp,rovnake : bool; xlm,ylm: int;

    { reinicializacia tabletu, treba prepocitat zobrazenie
      planov podla sektorizacie
    }
    procedure add_FPLi(_FPLi: P_OFPL; _top: int {$IFDEF SECTORS}; _S_DISPLAY,_TABLET_REINIT: bool{$ENDIF});
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
              {$ENDIF};
              is:= is and _FPLi^.get_on_board(_FPLi^.ap^[i]);
              if is then Add(_FPLi,i,false)
            end
        end;

    begin
      if PLANZET_MAPA then Exit;

      if ACC_TABLET_REINIT or ma_sa_prekreslit then
         begin
           ACC_TABLET_REINIT:= true;
           {$IFDEF SECTORS}
            S_UPDATE:= absTime;
           {$ENDIF}
         end;

      PIS    := true;   { nad winACC nie je otvorene ziadne ine okno }
      PREPIS := 0;      { winACC bola aktualizovana a PIS bolo false }
      PREPISANE:= absTime;

      APP_GUI_INIT:= true;


      reinit_(rovnake);

      SpecGroups.is_dep := najdi_skupinu(fplDEP,i,j);
      SpecGroups.is_arr := najdi_skupinu(fplARR,i,j);
      SpecGroups.is_west:= najdi_skupinu(fplWEST,i,j);
      SpecGroups.is_east:= najdi_skupinu(fplEAST,i,j);
      SpecGroups.is_tsa := najdi_skupinu(fplTSA,i,j);

      {$IFDEF FPL0}
       add_FPLi(cFPL,cFPL^.top{$IFDEF SECTORS}, S_DISPLAY,ACC_TABLET_REINIT{$ENDIF});
       add_FPLi(mFPL,mFPL^.top{$IFDEF SECTORS}, S_DISPLAY,ACC_TABLET_REINIT{$ENDIF});
       add_FPLi(oFPL,oFPL^.top{$IFDEF SECTORS}, S_DISPLAY,ACC_TABLET_REINIT{$ENDIF});
      {$ENDIF}

      {$IFDEF ZAM} {$IFDEF TABLET_ZAM}
       for i:= 0 to ZAMs^.top do Add(ZAMs,i,false);
      {$ENDIF} {$ENDIF}

      {$IFDEF PRS} {$IFDEF TABLET_PRS}
       for i:= 0 to PRSs^.top do Add(PRSs,i,false);
      {$ENDIF} {$ENDIF}

      ACC_TABLET_REINIT:= false;

      if NET_ENABLED then
         begin
           APP_GUI_INIT:= false;

           if (not rovnake) or IS_REFRESH then
              begin
                m_off (bp, xlm,ylm);
                ClrWin(x0,y0,x1,y1, bgTABLET);
                for i:= 0 to stlpcov do _stlpec_i(i);
                m_on (bp, xlm,ylm);
              end
           else for i:= 0 to stlpcov-1 do zmaz_plochu_nad_zoznammi(nil,i);

           for i:= 0 to stlpcov-1 do
             for j:= 0 to max_skupin-1 do if Tablet[i,j]<>nil then
                begin
                  Tablet[i,j]^.list_sort;
                  Tablet[i,j]^.draw;
                end;
         end;
    end;


procedure TwinACC._stlpec_i(i: int);
    begin
      BGIgraph.button(stlpec_xi(i),y0, stlpec_xi(i)+dx_lista,y1, clTABLET, btNorm, btOFF);
    end;

procedure TwinACC.reinit_(var rovnake: bool);
    var   i,j, rdk : int;
          bp: bool; xlm,ylm: int;
    begin
      vypni; Mail(winPROP,hl_vyp_winACC, one,nil,0);
      zrus_zoznamy;

      max_rdk:= max_rdkv_[lineSTRIP];
      stlpcov:= _stlpcov(miniSTRIP);
      STablet:= _tab_strip(miniSTRIP);

    { inicializacia tabule :  ---------------------------------- }
      rovnake:= (dx_strip=0) or (dx_strip=dx_strip_[miniSTRIP]);

      dx_strip    := dx_strip_   [miniSTRIP];
      dy_strip    := dy_strip_   [lineSTRIP];

      dx_stlpec   := dx_stlpca   [miniSTRIP];
      dxof_stlpec := dxof_stlpca [miniSTRIP];
      dxof_sb     := dxof_sbu    [miniSTRIP];
      {dy_strip := Height[i]; dxx_strip := 27; }

      if rovnake then
         begin
           m_off (bp, xlm,ylm);
           for i:= 0 to stlpcov do _stlpec_i(i);
           m_on (bp, xlm,ylm);
         end;

    { inicializacia stlpcov podla vzoru ------------------------ }
      init_SORT_NDB(SORT_NDBs, pocet_SORT_NDBs);   { nacitanie tabulky s udajmi o spracovani majakov }
      for i:= 0 to stlpcov-1 do
          begin
            j:= 0;
            while (j<max_skupin) and (STablet^[i,j].NDB<>'') do
              begin
                {if TABLET_NULL then rdk:= j else rdk:= 0;} rdk:= j;
                Tablet[i,j]:= New(PlstACC,Init(@Self, STablet^[i,j], i,rdk));
                inc(j)
              end;
          end;
      done_SORT_NDB(SORT_NDBs, pocet_SORT_NDBs)    { odalokovanie tabulky s udajmi o spracovani majakov }
    end; { Reinit }


procedure TwinACC.reinit_tablet(fn: string; _kresli: bool);
    var   s: T_strip;
          i: int;
    begin
      if Exists(fn)<>0 then Exit;
      {CopyFile(fn,TABLET_CFG);}
      zrus_zoznamy;
      for s:= low(T_strip) to high(T_strip) do for i:= 0 to _stlpcov(s)-1 do disp_Stlpec(p_tab_stripi[s]^[i]);
      read_tablet_cfg(fn);
      if _kresli then Draw;
    end;
