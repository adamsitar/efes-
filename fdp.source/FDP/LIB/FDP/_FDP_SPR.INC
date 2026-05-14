procedure pozri_spracovanie_planov_;

    const semaphor: bool = false;
          T: real = 0;
          m: byte = 1;

    var   is,isl,is0 : bool;

    begin
      if semaphor then Exit;
      semaphor:= true;

      is0:= T=0;
      is:= (T<>absTime) and (m<>min);
      if is then begin T:= absTime; m:= min end;
      isl:= is {$IFDEF MAPY} or (PLANZET_MAPA and OBNOV_CIELE) {$ENDIF};


      {$IFDEF RPL}
        check_RPL;
      {$ENDIF}


      {$IFDEF FDR}
        if oFDR<>nil then oFDR^.check(is);
      {$ENDIF}


      {$IFDEF FPL0}

       {$IFDEF EDD}
        PROP_cFPL^.nastavenie_platnosti(isl);
        PROP_mFPL^.nastavenie_platnosti(isl);
        {$IFDEF FPLO}
         PROP_oFPL^.nastavenie_platnosti(isl);
        {$ENDIF}
       {$ENDIF}

       cFPL^.check(isl);
       {$IFNDEF FPLM_DISABLED}
        mFPL^.check(isl);
        {$IFDEF FPLO}
         oFPL^.check(isl);
        {$ENDIF}

       {$IFDEF REPORT_FPLM_ARW}
        pozri_nevydane_spravy_FPLM_ARR (is);
       {$ENDIF}
       {$ENDIF}
      {$ENDIF}

      {$IFDEF ZAM}
       ZAMs^.check(is);
      {$ENDIF}

      {$IFDEF PRS}
       PRSs^.check(is);
      {$ENDIF}

      if is0 then INITIALIZE_EN:= _INITIALIZE_EN;

      semaphor:= false
    end;


procedure pozri_spracovanie_planov_so_semaformi;
    begin
      {$IFDEF FDR}
      {$ENDIF}

      {$IFDEF FPL0}
       {$IFDEF PROCESS_FPLM} {$IFDEF OPL}
        spracuj_pripomienky_ku_FPLM;
       {$ENDIF} {$ENDIF}
      {$ENDIF}

      {$IFDEF DVZ}
       {$IFDEF PROCESS_DVZ}
         spracuj_ziadosti_o_DVZ;
       {$ENDIF}
      {$ENDIF}

      {$IFDEF QGO}
       spracuj_hlasenia_o_QGO;
      {$ENDIF}
    end;
