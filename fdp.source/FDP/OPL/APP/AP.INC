constructor TOPLapp.Init;
      var   _btmdx1: int;
      begin
        inherited Init(@Self, @OPLmenu_init, @LOGO,titFDP+' '+titSPC, titCR);
        OPLgui:= New(P_GUI, Init(@Self));
        AppGUI:= OPLgui;
        {$IFDEF AIRBASE} {$IFNDEF DEBUG}
          if not eq_airbase(NETadr_wan(NETaddress),this_airbase) then
             RunError('Nejednoznacna konfiguracia adresy letiska.')
             {RunError('Unambigious configuration of the airbase code/address.')}
        {$ENDIF} {$ENDIF}
      end;

procedure TOPLapp.InitEXT_drivers;
    begin
     {$IFDEF EXTERNAL_NET}
     { ---------------
       EXTERNAL NET
       תתתתתתתתתתתתתתת
     }
      {$IFDEF CONNECT_TO_AFTN}
       DEV_AFTN:= New(P_AFTN,Init('', nil,AMC_coor_info, nil,0));
      {$ENDIF}
     {$ENDIF}
    end;

procedure TOPLapp.InitApp;
    begin
      inherited InitApp;
      __INFO_DB:= true;
     {$IFDEF PROCESS_FPLM}
      isFPLM_PROC:= true;
     {$ENDIF}
      PROC_DVZ:= true;
    end;


function  TOPLapp.change_gm(gm: TGraphMode; _init,_draw: bool): bool;
    var   bres: bool;
    begin
      bres:= inherited change_gm(gm,_init,false);
      {if bres then} OPLgui^.reinit_;
      if bres and _draw then Draw;
      change_gm:= bres
    end;
