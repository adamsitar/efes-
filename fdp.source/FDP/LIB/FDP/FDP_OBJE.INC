var   b1,b2: bool;


constructor TFDPapp.Init(_Owner: PGroup; _BarMenu,_LOGO: pointer; _VER,_CR: string);
      begin
        NET_ENABLED:= false;
        {$IFDEF EXTERNAL_NET}
         EXT_ENABLED:= false;
        {$ENDIF}

        InitNET;
        InitData;
        data_initialized:= true;

        InitEXT;
        {$IFDEF EXTERNAL_NET} { bola to virtualna fcia volana na zaciatku odvodenenej }
         if NODEpoc+EXTpoc>maxNODEs then RunError('To many network and external nodes.');
        {$ENDIF}

        InitMMI(_Owner, _BarMenu,_LOGO, _VER,_CR);
      end;


procedure TFDPapp.InitMMI(_Owner: PGroup; _BarMenu,_LOGO: pointer; _VER,_CR: string);
    begin
     { ---------------
       APP               ... moze sa odkazovat na NET/DATA
       תתתתתתתתתתתתתתת
     }
      inherited Init(_Owner, _BarMenu,_LOGO, _VER,_CR);
      hlpXXX:= hlp_GUI;
      {$IFDEF EXIT_PASSWORD}
        EXIT_PASSWORD_FDP:= titFOR;
        {$IFNDEF DEBUG} set_password(EXIT_PASSWORD_FDP); {$ENDIF}
      {$ENDIF}
    end;


procedure TFDPapp.InitData;
    begin
    { ---------------
      DATA
      תתתתתתתתתתתתתתת
    }
      PLANY_init;
      (*{$IFDEF SECTORS} SECTOR_init; {$ENDIF}*)
      {$IFDEF RDP_ACCEPT} init_RDP_SECTOR; {$ENDIF}
    end;


procedure TFDPapp.InitNET;
    begin
    { ---------------
      LETVIS NET
      תתתתתתתתתתתתתתת
    }
      b1:= DISTRIBUTE_EN; DISTRIBUTE_EN:= false;
      _INITIALIZE_EN:= INITIALIZE_EN; INITIALIZE_EN:= false;
      _NET_EN := false;

      {$IFDEF NET}
       NET_init(New(PFDP_NET,Init));
       if NET<>nil then NET^.Owner:= @Self;
      {$ENDIF}

      {$IFDEF TRENAZER}
       SIM_init;
      {$ENDIF}
    end;


procedure TFDPapp.InitEXT_drivers;
    begin
     {$IFDEF EXTERNAL_NET}
     { ---------------
       EXTERNAL NET
       תתתתתתתתתתתתתתת
     }
      (*
      {$IFDEF CONNECT_TO_AFTN}
       {$IFDEF TSGA}
        DEV_AFTN:= New(P_AFTN_TSGA,Init);
       {$ELSE}
        DEV_AFTN:= New(P_AFTN,Init('',@hd_AFTN,sizeof(hd_AFTN) div sizeof(Thead_ICAO)));
       {$ENDIF}
      {$ENDIF}

      {$IFDEF CONNECT_TO_CAMUS}
       DEV_CAMUS:= New(PO_CAMUS,Init);
       {$IFDEF CAMUS_OLDI}      { Kvoli uz inicializovanemu protokolu X25 }
        DEV_OLDI:= DEV_CAMUS;
       {$ELSE}
        P_DEV_CAMUS:= @DEV_CAMUS;
       {$ENDIF}
      {$ENDIF}

      {$IFDEF CONNECT_TO_ASOC}  { Kvoli uz inicializovanemu protokolu NET }
       DEV_ASOC:= New(PO_ASOC,Init);
      {$ENDIF}
      *)
     {$ENDIF}
    end;

procedure TFDPapp.InitEXT;
    begin
     {$IFDEF EXTERNAL_NET}
      _EXT.Init_EXT;
      InitEXT_drivers;
     {$ENDIF}
    end;


procedure TFDPapp.InitApp;
    var   gm: TGraphMode;
    begin
      inherited InitApp;
      gm:= GraphMode;
      if not ReadProgramCfg(APP_USER_CFG,false) then
         begin
         {$IFNDEF DEBUG}
           {SetCommand(Pending,cmAboutUpgrade);}
         {$ENDIF}
         end;
      {reinitialize_gm:= gm<>GraphMode}
    end;


{$IFDEF ARCHIVE_DAR}
  { pri otvarani noveho suboru ulozi don vsetky platne stripy
  }
  procedure DAR_save_plans; far;
      var   i: int;
      begin
        for i:= 0 to cFPL^.top do save_FDP(spr0_RDP_cFPL, cFPL^.ap^[i], @code0_cFPL_RDP);
        {$IFNDEF FPLM_DISABLED}
         for i:= 0 to mFPL^.top do save_FDP(spr0_RDP_mFPL, mFPL^.ap^[i], @code0_mFPL_RDP);
         {$IFDEF FPLO}
          for i:= 0 to oFPL^.top do save_FDP(spr0_RDP_mFPL, oFPL^.ap^[i], @code0_mFPL_RDP);
         {$ENDIF}
        {$ENDIF}
      end;
{$ENDIF}


procedure TFDPapp.InitApp2;
    var   gm: TGraphMode;
          b: bool;
    begin
      gm:= GraphMode;
      change_gm(GraphMode,true,true);
      inherited InitApp2;

      ochrana_programu;  { neskor, kvoli vynervovaniu -  }

     { ---------------
       INICIALIZACIA DAT
       תתתתתתתתתתתתתתת
     }
      APP_GUI_INIT:= true;
      PLANY_load;
      NET_ENABLED:= true;
      {$IFDEF EXTERNAL_NET}
       EXT_ENABLED:= true;
      {$ENDIF}
      Draw;
      APP_GUI_INIT:= false;


     { ---------------
       NET
       תתתתתתתתתתתתתתת
     }
      _NET_EN:= true;

      Sprava_o_zapnuti;

      {$IFDEF BACKUP} {IFNDEF DEBUG}
        if SERVERnode>-1 then
           begin
             InfoCakaj(msgINIT,'Checking master status...');
             b:= INITIALIZE_EN; INITIALIZE_EN:= false;
             repeat
               CheckProcesses0;
               NET_checkA;
               NET_checkD;
             until    ((not SERVERstatus) and (not NODEs^[SERVERnode].stat.TrasaOK))
                   or (SERVERstatus and NODEs^[SERVERnode].stat.TrasaOK);
             INITIALIZE_EN:= b;
             InfoCakaj_zatvor
           end
        else SERVERstatus:= false;
      {$ENDIF} {ENDIF}

      {$IFDEF MASTER} {IFNDEF DEBUG}
        if BACKUPnode>-1 then
           begin
             InfoCakaj(msgINIT,'Checking slave status...');
             b:= INITIALIZE_EN; INITIALIZE_EN:= false;
             repeat
               CheckProcesses0;
               NET_checkA;
               NET_checkD;
             until    ((not BACKUPstatus) and (not NODEs^[BACKUPnode].stat.TrasaOK))
                   or (BACKUPstatus and NODEs^[BACKUPnode].stat.TrasaOK);
             INITIALIZE_EN:= b;
             InfoCakaj_zatvor
           end
        else BACKUPstatus:= false;
      {$ENDIF} {ENDIF}

      Sprava_o_zapnuti;
      DISTRIBUTE_EN:= b1;

      {$IFDEF ARCHIVE_DAR}
       init_DAR(@DAR_save_plans);
      {$ENDIF}

      _EXT_EN:= true;
    end;


procedure TFDPapp.DoneEXT;
    var   i: int;
    begin
     {$IFDEF EXTERNAL_NET}
      {$IFDEF CONNECT_TO_CAMUS}
       {$IFDEF CAMUS_OLDI}
        DEV_OLDI:= nil;
       {$ELSE}
        P_DEV_CAMUS:= nil;
       {$ENDIF}
      {$ENDIF}

      _EXT.Done_EXT;
     {$ENDIF}
    end;

destructor TFDPapp.Done;
     begin
       Sprava_o_vypnuti;
       _NET_EN := false;
       NET_ENABLED:= false;
       {$IFDEF EXTERNAL_NET}
        EXT_ENABLED:= false;
       {$ENDIF}
       APP_GUI_INIT:= true;
       SaveProgramCfg(USER_CFG); { ulozenie posledneho aktivneho konfiguraku }
       DoneEXT;
       PLANY_done;
       data_initialized:= false;
       inherited Done
     end;



function  TFDPapp.change_gm(_gm: TGraphMode; _init,_draw: bool): bool;
    begin
      change_gm:= false;
      if    (not EN_GRAPH_MODE_SWITCH)
         {or (    {(not _init)
             and (_gm=GraphMode) and (MaxX=GetMaxX) and (MaxY=GetMaxY)
            )}
            then Exit;

      change_gm:= true;
      set_GrMode(_gm);
      XY(0,0,MaxX,MaxY);
      riadok:= 0;
      ReInit(0,0,MaxX,MaxY);

      {$IFDEF STATUS} STATUS_reinit; {$ENDIF}

      if _draw then Draw
    end;
