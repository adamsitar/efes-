
 procedure init_FPS_buttons (sc: PScrollWin); far;
     var   bt1   : PDialogButton;
           xt,yt : int;
           _kbHot : char;
     begin
       {$IFDEF PRN} xt:= 1; init_sc_butt1(sc);
       {$ELSE}      xt:= 0;
       {$ENDIF}
        sc^.Win^.get_btXY(1,xt, xt,yt);
        bt1:= New(PDialogButton,Init(sc^.Win,
                  xt,yt,GetAltCode(get_HotKey(_kbHot,titEXPORT)),
                  cm_FPS_EXPORT,titEXPORT,icKey,icText)
                 );
     end;


 function handle_FPS_buttons (var Ev: TEvent; sc: PScrollDB_FDP; handler_owner,handler_data: pointer): bool; far;
    var   FPL  : DFPL4;
          ires : int;
    begin
      handle_FPS_buttons:= false;
      if not isCommand(Ev,cm_FPS_EXPORT) then Exit;
      {$IFDEF DB_DBASE}
       m_set_shape(HODINY);
       export_FPLS(sc^.fn,PFPSs(sc^.arr^.ap),sc^.arr^.top);
       m_restore_shape;
      {$ENDIF}
      ClearEvent(Ev,sc)
    end;


 function handle_FPS_list (var Ev: TEvent; sc: PScroller; FPS: PFPS): bool; far;
    var   FPL  : DFPL4;
          ires : int;
    begin
      m_set_shape(HODINY);
      ires:= read_FPL4(codekey_FPS(FPS),@FPL);
      m_restore_shape;
      if ires>=0 then
         begin
           info_FPL4(@FPL,'');
           disp_FPL4(@FPL);
         end;
      handle_FPS_list:= false;
      ClearEvent(Ev,sc)
    end;
