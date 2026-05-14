constructor TSERVERapp.Init;
      begin
        inherited Init(@Self, @SERVERmenu_init, @LOGO, titFDP+' '+titSPC, titCR);
      end;


procedure TSERVERapp.InitMMI(_Owner: PGroup; _BarMenu,_LOGO: pointer; _VER,_CR: string);
    begin
      GraphMode:= {$IFDEF _800x600} _VESA {$ELSE} _VGA {$ENDIF};

      inherited InitMMI(_Owner, _BarMenu,_LOGO, _VER,_CR);

      AppGUI:= New(P_Smmi,Init(@Self
                 {$IFDEF DATA_WRITTEN_IN_APP}
                   {$IFDEF CONNECT_TO_BGU}          , ???
                   {$ELSE}                          , nil
                   {$ENDIF}
                 {$ENDIF})
                 );

      {$IFDEF DATA_WRITTEN_IN_APP}
       if DEV_AFTN<>nil then DEV_AFTN^.p_scroll_data:= @AppGUI^.AppScroll;
      {$ENDIF}
    end;


procedure TSERVERapp.InitEXT_drivers;
    begin
     {$IFDEF EXTERNAL_NET}
     { ---------------
       EXTERNAL NET
       ˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙
     }
      (*{$IFDEF CONNECT_TO_AFTN}
       {$IFDEF TSGA}
        DEV_AFTN:= New(P_AFTN_TSGA,Init);
       {$ELSE}
        DEV_AFTN:= New(P_AFTN,Init('',@hd_AFTN,sizeof(hd_AFTN) div sizeof(Thead_ICAO)));
       {$ENDIF}
      {$ENDIF}*)


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

      {$IFDEF CONNECT_TO_VERA}
       DEV_VERA:= New(PO_VERA,Init);
      {$ENDIF}

      {$IFDEF CONNECT_TO_OPL_EXT}
        DEV_OPL:= New(PO_OPL,Init);
        IBUFF_OPL_ASYNC:= @DEV_OPL;
      {$ENDIF}


      {$IFDEF UKBB_PRN}
        DEV_BGU:= New(P_BGU,Init(@Self));
        {$IFDEF DATA_WRITTEN_IN_APP}
          DEV_BGU^.p_scroll_data:= @AppGUI^.AppScroll;
        {$ENDIF}
      {$ENDIF}

     {$ENDIF}
    end;


(*procedure TSERVERapp.InitApp2;
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

procedure TSERVERapp.DoneApp2;
    begin
      inherited DoneApp2
    end;
*)

procedure TSERVERapp.DoneEXT;
    begin
      {$IFDEF CONNECT_TO_OPL_EXT}
       IBUFF_OPL_ASYNC:= nil;
      {$ENDIF}

      inherited DoneEXT;

      {$IFDEF CONNECT_TO_OPL_EXT}
       DEV_OPL:= nil;
      {$ENDIF}

      {$IFDEF CONNECT_TO_BGU}
       {$IFNDEF DATA_WRITTEN_IN_APP}
         Dispose(DEV_BGU,Done);
       {$ENDIF}
        DEV_BGU:= nil;
      {$ENDIF}
    end;
