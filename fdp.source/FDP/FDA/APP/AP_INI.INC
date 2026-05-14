constructor TFDAapp.Init;
      begin
        inherited Init(@Self, @FDAmenu_init, @LOGO, titFDP+' '+titSPC, titCR);
      end;


procedure TFDAapp.InitEXT_drivers;
    begin
     {$IFDEF EXTERNAL_NET}
     { ---------------
       EXTERNAL NET
       ˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙
     }
      {$IFDEF CONNECT_TO_AFTN}
       DEV_AFTN:= New(P_AFTN_TSGA,Init);
      {$ENDIF}

     {$ENDIF}
    end;


procedure TFDAapp.InitMMI(_Owner: PGroup; _BarMenu,_LOGO: pointer; _VER,_CR: string);
    begin
      GraphMode:= _VESA;

      inherited InitMMI(_Owner, _BarMenu,_LOGO, _VER,_CR);

      AppGUI:= New(P_FDAmmi,Init(@Self
                 {$IFDEF DATA_WRITTEN_IN_APP}
                   {$IFDEF CONNECT_TO_AFTN}         , @DEV_AFTN ,cl_AFTN_send,cl_AFTN_rec
                   {$ELSE} {$IFDEF CONNECT_TO_BGU}  , @DEV_BGU  ,clGRa,clGRa
                   {$ELSE}                          , nil
                   {$ENDIF}
                   {$ENDIF}
                 {$ENDIF})
                 );

      {$IFDEF DATA_WRITTEN_IN_APP}
       if DEV_AFTN<>nil then DEV_AFTN^.p_scroll_data:= @AppGUI^.AppScroll;
      {$ENDIF}
    end;



(*procedure TFDAapp.InitApp2;
    begin
      {$IFDEF DEBUG}
        ResetIOError;

        {closegraph; MainEnabled:= false;
        read_txt_rpls('\xx\rpl.txt');}

        {$IFDEF AFTN}
          {DEV_AFTN^._test_file(paramstr(1),' ',11);}
          {DEV_AFTN^._test_txt_file(paramstr(1),'çççç',0);}

          {DEV_AFTN^._test_file('.\test\UKBB.afn',' ',11);}
          {DEV_AFTN^._test_txt_file('.\fdpˇdata\ine\test\12012200.afn','@');}
          {DEV_AFTN^._test_bin_file('\fdpˇdata\test\aftn.afb',11);}
          {DEV_AFTN^._test_file('\fdpˇdata\test\aftn.msg','.',2);}
          {DEV_AFTN^._test_file('\fdpˇdata\test\aftn.fpl','.',2);}
        {$ENDIF}

        {DEV_OLDI^.stat:= DATA_READY_STATE;}
        {DEV_OLDI^.test_file(paramstr(1),'',0);}

        {'\fdpˇexe\!\!P\10301900.opl'}
        {testuj('.\INE\test');}
        {net_pkt_test;}
        {asta_fdp_test;}
        {asta_prn_test;}
        (*DEV_OPL^._test_file('.\x\test.opl'{paramstr(1)},'',0);
      {$ENDIF}

      inherited InitApp2
    end;

procedure TFDAapp.DoneApp2;
    begin
      inherited DoneApp2
    end;
*)

