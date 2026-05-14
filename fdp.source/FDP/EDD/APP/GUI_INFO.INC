procedure T_GUI.edd_status;

    const {$IFNDEF EDD_20}
            dxt = 535; dxv = 645;

            dyt_SEC  = 55;
            dyt_PROP = 75;
            dyt_ACC  = 85;
            dyt_ORG  = 100;
            dyt_SORT = 110;

            dyt_S1   = 125;
            dyt_H    = 135;
            {dyt_SYNC = 130;}
          {$ELSE}
            dxt = 700; dxv = 825;

            dyt_SEC  = 70;
            dyt_PROP = 100;
            dyt_ACC  = 110;
            dyt_ORG  = 130;
            dyt_SORT = 140;

            dyt_S1   = 170;
            dyt_H    = 180;
            {dyt_SYNC = 145;}
          {$ENDIF}

            t_FPLc = ' En-R, ';
            t_FPLm = ' MIL, ';
            t_FPLo = ' FPL    ';


    var   i,j,h,dyt, font: int;
          s,t,sec : string;
          TempWinReg : PWinReg;

    function snmb_on_board(FPLi: P_OFPL): string;
       var   p1,p2: int;
       begin
         snmb_on_board:= '';
         if FPLi=nil then Exit;
         {$IFDEF SECTORS}
           p1:= FPLi^.nmb_on_board;
           p2:= FPLi^.top-p1+1;
           snmb_on_board:= cstr(p1,1){+'/'+cstr(p2,1)}
         {$ELSE}
           snmb_on_board:= cstr(FPLi^.top+1,1)
         {$ENDIF}
       end;

    begin
      if (MainApp=nil) or (not PFDPapp(MainApp)^.data_initialized) or PLANZET_MAPA then Exit;

      if not vypis_do_okna(dxt+15,dyt_PROP,dxv+Clock^.x0-5{950},winPROP^.reg.y1, TempWinReg,-1,ScreenDesc) then
         begin
           PREPIS:= absTime;
           Exit
         end;

      font:= SPfont; {$IFDEF SPEA}SetBkColor(clBUTTON_COLOR);{$ENDIF}
      {SetTextStyle(COND8x16, 0,0);}

      s:= '';
     {$IFDEF SECTORS}
       for i:= 0 to nsec-1 do
           if SECTORs^[i]^.is then
              begin
                if s<>'' then s:= s+',';
                s:= s+strpas(SECTORs^[i]^.meno)
              end;
       if s<>'' then s:= ' - '+s;
     {$ENDIF}
      t:= strpas(NODEname);
      if length(t+s)>40 then t:= getstr(t,1,[icao_NXT]);
      s:= t+s; if length(s)>40 then s:= copy(s,1,37)+'...';
      s:= inschar(s, 40,' ',1);
      WriteStr(dxt, dyt_SEC, s, clGRe,clBUTTON_COLOR);

      SetColor(clGRb);
      OutTextXY(dxt,dyt_PROP, strpas(_prop));
      OutTextXY(dxt,dyt_ACC,  strpas(_acc));

      OutTextXY(dxt,dyt_ORG,  strpas(_org_by));
      OutTextXY(dxt,dyt_SORT, strpas(_sort_by));

      {$IFDEF SECTORS}
       OutTextXY(dxt,dyt_S1,   strpas(_sect_by));
       dyt:= dyt_H;
      {$ELSE}
       dyt:= dyt_S1;
      {$ENDIF}

      OutTextXY(dxt,dyt,    strpas(_hidden));
      {OutTextXY(750,145,'TIMESynchronize  : ');}

      WriteStr (dxv, dyt_PROP, snmb_on_board(PROP_cFPL)+t_FPLc
                              +snmb_on_board(PROP_mFPL)+t_FPLm
                              +snmb_on_board(PROP_oFPL)+t_FPLo,
                clGRa,clBUTTON_COLOR
               );
      WriteStr (dxv, dyt_ACC,  snmb_on_board(cFPL)+t_FPLc
                              +snmb_on_board(mFPL)+t_FPLm
                              +snmb_on_board(oFPL)+t_FPLo,
                clGRa,clBUTTON_COLOR
               );

      s:= strpas(_org [NDB_INP]);
      {$IFDEF SECTORS}
        if NDB_INP then s:= s+' '+strpas(_seci[S_IN]);
      {$ENDIF}
      s:= inschar(s,25,' ',1);
      WriteStr (dxv,dyt_ORG,  s, clGRb,clBUTTON_COLOR);
      WriteStr (dxv,dyt_SORT, strpas(_sort[STRIP_SORT]),clGRb,clBUTTON_COLOR);

      {$IFDEF SECTORS}
       s:= ''; s:= inschar(s,25,' ',1); WriteStr(dxv,dyt_S1,s,clGRb,clBUTTON_COLOR);
       if (not S_DISPLAY) then s:= _OFF
       else s:= strpas(_sec[S_D_IN_THROUGH]);
       OutTextXY(dxv,dyt_S1,s);
      {$ENDIF}

      if (cFPL<>nil) then
         begin
           h:= 0; for i:= 0 to cFPL^.top do if not cFPL^.get_on_board(cFPL^.ap^[i]) then inc(h);
           s:= inschar('',25,' ',1); WriteStr(dxv,dyt,s,clGRb,clBUTTON_COLOR);
           WriteStr (dxv,dyt,  cstr(h,1), clGRb,clBUTTON_COLOR);
         end;

      obnov_okna(TempWinReg,true)
    end;
