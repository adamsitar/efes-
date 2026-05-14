{const SaveMain : TProc = nil;

procedure _check_CAMUS; far;
    begin
      if @SaveMain<>nil then SaveMain;
      if DEV_CAMUS<>nil then DEV_CAMUS^.check
    end;
}

constructor O_CAMUS.Init;
      begin
       {$IFNDEF CAMUS_OLDI} {LZIB_ACC}
        inherited Init(nil,@power_CAMUS,
                       CAMUScfg,strpas(fnOB.fn),
                       0, true,
                       CAMUS_PACKET_SIZE,CAMUS_BUFFER_SIZE, false, CAMUS_BUFFER_SIZE,
                       0,0,0,0,0,0,0,0,0,0,
                       nil,CAMUS_coor_info,
                       @hd_CAL4, sizeof(hd_CAL4) div sizeof(Thead_ICAO),
                       nil,0,{@hd_CALAM, sizeof(hd_CALAM) div sizeof(Thead_ICAO),}
                       @writeln_CAMUS, @archive_CAMUS, @utc_CAMUS,
                       cl_CAMUS, cl_CAMUS_system_mess,
                       path_CAMUS,path_CAMUS+spath_ERR, extCAMUS
                      );
        CAMUSpkt:= ipkt;
        process_all_msg:= true;
       {$ELSE}
        inherited Init(@power_CAMUS,
                       CAMUScfg,strpas(fnOB.fn),
                       {$IFDEF LKPR_MACC} CAMUS_BUFFER_SIZE {$ELSE} 0 {$ENDIF},
                       CAMUS_PACKET_SIZE,CAMUS_BUFFER_SIZE,true,
                       nil,CAMUS_coor_info,
                       @hd_CAL4, sizeof(hd_CAL4) div sizeof(Thead_ICAO),
                       @hd_CALAM, sizeof(hd_CALAM) div sizeof(Thead_ICAO),
                       @writeln_CAMUS, @archive_CAMUS, @utc_CAMUS,
                       cl_CAMUS, cl_CAMUS_system_mess,
                       path_CAMUS, extCAMUS
                      );
       {$ENDIF}

        src_type:= _FDP_DEF.camus;
        okamzite_spracovanie:= true;
        {LAM_pred_spracovanim:= true;}
        poloziek_ESTc_bodov:= 3;

        {$IFDEF LKPR_MACC}
          dst_set:= [opl_ext];

          {$IFDEF CONNECT_TO_FDPOX} {$IFDEF UDP}
           with UDP_PORT_FDPOX do udp_open_port (UDP_FHOST,port,desc,asynch,true);
           Delay(20);
           FDPOXadr_ip:= nm_prs_addr(FDPOXadr_ip_s);
           if (FDPOXadr_ip<>0) then writeln('FDPOX initialized on UDP port: '+WordToHex(UDP_PORT_FDPOX.port)+ '.')
           else {(neterrno<>0) or}
              RunError('Invalid or missing '+cfg_IP_ADR+' ('+FDPOXadr_ip_s
                        +' '+cstr(neterrno,1)
                        +'/'+cstr(FDPOXadr_ip,1)+')'
                      );
           Delay(1000);
          {$ENDIF} {$ENDIF}
          _l4444m:= true;
        {$ENDIF};

        est_alt_:= altFL;
        _dct_points:= false;
        _oat_exclude:= true;
        _mil_sys:= false;
      end;


destructor O_CAMUS.Done;
     var   i : int;
     begin
       if poc_EXC_NDB>0 then
          begin
            for i:= 0 to poc_EXC_NDB-1 do StrDispose(EXC_NDB^[i]);
            DeallocMem (pointer(EXC_NDB), poc_EXC_NDB*sizeof(pchar));
            poc_EXC_NDB:= 0;
          end;

       {$IFDEF CONNECT_TO_FDPOX} {$IFDEF UDP}
        net_abort(UDP_PORT_FDPOX.desc);
       {$ENDIF} {$ENDIF}

       inherited Done;
     end;


function O_CAMUS.read_cfg(_cfg_FN: string): bool;
    var  s : string;
         i : int;
    begin
      EXC_NDB:= nil;
      poc_EXC_NDB:= 0;

      s:= '';
      while     (poc_EXC_NDB<max_EXC_NDB)
            and (__read_cfg_line(_cfg_FN,cfg_EXC_NDB,poc_EXC_NDB+1,2)<>'')
      do inc(poc_EXC_NDB);
      if (poc_EXC_NDB>0) and AllocMem(pointer(EXC_NDB),poc_EXC_NDB*sizeof(pchar)) then
          begin
            i:= 0; while (i<poc_EXC_NDB) do
              begin
                EXC_NDB^[i]:= strpasnew(cut_(getstr(__read_cfg_line(_cfg_FN,cfg_EXC_NDB,i+1,2),2,odd_cfg)));
                inc(i);
              end;
          end;


     {$IFNDEF CAMUS_OLDI}
      asyncCOM       := 2;
      asyncMODE      := 19200;
      asyncBITs      := 8;
      asyncSTOP_BITs := 0;
      asyncPARITY    := _PARITY(read_cfg_str_(_cfg_FN,cfg_COM_PARITY,'NONE'),true);
     {$ENDIF}


     {$IFDEF LKPR_MACC}
      {$IFDEF CONNECT_TO_FDPOX} {$IFDEF UDP}
       UDP_PORT_FDPOX.port:= read_cfg_word(_cfg_FN,cfg_UDP_PORT,UDP_PORT_FDPOX.port);
       FDPOXadr_ip_s:= cut_(read_cfg_str_(_cfg_FN,cfg_IP_ADR,''));
      {$ENDIF} {$ENDIF}

      _error_fda:= true;
      _nolam_fda:= true;

      poloziek_ESTc_bodov:= 3;
     {$ENDIF};

      read_cfg:= inherited read_cfg(_cfg_FN);
      CAMUS_15a:= read_cfg_bool(_cfg_FN, cfg_CAMUS_15a, CAMUS_15a);
      ASTA_src := read_cfg_bool(_cfg_FN, cfg_ASTA_src, ASTA_src);

      _9b_CHECK_MIL:= true;

      read_cfg:= true
    end;


procedure O_CAMUS.HandleEvent(var _Event: TEvent);
    begin
      inherited HandleEvent(_Event);

      if (_Event.What<>evNothing) then
        case _Event.Command of

          cmARCHIV_CAMUS  : zalohuj_archiv(pathSTREAM,'*.'+fn_ext,msgBCK,msgCOPY,nil);

          cmOLDI_TEST_FPL : test_OLDI_FPL;
          cmOLDI_TEST_CHG : test_OLDI_CHG;
          cmOLDI_TEST_DLA : test_OLDI_DLA;
          cmOLDI_TEST_CNL : test_OLDI_CNL;
          cmOLDI_TEST_ACT : test_OLDI_ACT;
          cmOLDI_TEST_REV : test_OLDI_REV;
          cmOLDI_TEST_ERR : test_OLDI_ERR;

          else Exit
        end
      else Exit;

      ClearEvent(_Event)
    end;
