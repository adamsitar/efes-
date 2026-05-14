procedure save_lastREQ(req: TsREQ; fn: string);
    var   f: file of TsREQ;
    begin
      assign(f,fn);
      rewrite(f);
      write(f,req);
      close(f)
    end;

function read_lastREQ(fn: string; var req: TsREQ): bool;
   var   f: file of TsREQ;
   begin
     read_lastREQ:= false;
     fillchar(req,sizeof(req),0);
     if (FExists(fn)<>0) or (_filesize(fn)<>sizeof(TsREQ)) then Exit;
     read_lastREQ:= true;
     assign(f,fn);
     reset(f);
     read(f,req);
     close(f)
   end;


{const SaveMain : TProc = nil;

procedure _check_OPL; far;
    begin
      if @SaveMain<>nil then SaveMain;
      if DEV_OPL<>nil then DEV_OPL^.check
    end;}


constructor O_OPL.Init;
      var   a : bool;
      begin
       {$IFDEF OPL__SAVE_STREAM}
        {save_stream:= false;}
        stream_open:= false;
        stream_fn:= '';
       {$ENDIF}

        a:= false; {$IFDEF OPL_EXT_ASYNC} a:= true; {$ENDIF}

        inherited Init(nil,nil,OPLcfg,strpas(fnOB.fn),
                       OPL_BUFFER_SIZE,a, sizeof(TOPLpkt),OPL_BUFFER_SIZE,false, OPL_BUFFER_SIZE,
                       0,0,0,0,0,0,0,0,0,0,
                       nil,OPL_coor_info,
                       @hd_OPL4, sizeof(hd_OPL4) div sizeof(Thead_ICAO),
                       @hd_OPL_LAM, sizeof(hd_OPL_LAM) div sizeof(Thead_ICAO),
                       @writeln_OPL, @archive_OPL, @writeln_OPL_utc,
                       cl_OPL_send, cl_OPL_rec,
                       path_OPL, path_OPL+spath_ERR, extOPL
                      );

        lam_pred_spracovanim:= true;
        process_all_adr:= true; { eliminuje kontrolu na adresu odosielatela a prijemcu,
                                  komunikacia je obojsmerna s jedinecnymi adresami
                                }
        _l4444m:= true;

        src_type:= opl_ext;
        dst_set := [asta,camus];

        OPLpkt:= ipkt;
        HeartBeat:= SOH+MES+opl_HEARTBEAT+EOT;

        uncomplete_pkt_en:= OPL__UNCOMPLETE_PKT;
        test_int:= false;
        _dct_points := false;

        {SaveMain:= ACheck;
        ACheck:= _check_OPL;}

        poloziek_ESTc_bodov:= 3;

        {$IFDEF PRS}
          max_PRS_pozn_rm:= max_PRS_pozn_r_lo;
        {$ENDIF}

        {$IFDEF OPL_EXT_UDP} {$IFDEF UDP}
         New(UDPpkt); fillchar(UDPpkt^,sizeof(UDPpkt^),0);

         with UDP_PORT_OPL do udp_open_port (UDP_FHOST,port,desc,asynch,true);
         Delay(20);
         OPLadr_ip:= nm_prs_addr(OPLadr_ip_s);
         if (OPLadr_ip<>0) then writeln('OPL initialized on UDP port: '+WordToHex(UDP_PORT_OPL.port)+ '.')
         else {(neterrno<>0) or}
            RunError('Invalid or missing '+cfg_IP_ADR+' ('+OPLadr_ip_s
                      +' '+cstr(neterrno,1)
                      +'/'+cstr(OPLadr_ip,1)+')'
                    );
         Delay(1000);
        {$ENDIF} {$ENDIF}

        p_master_line:= @line_master_OPL
      end;


function O_OPL.read_cfg(_cfg_FN: string): bool;
   var   s : string;
         r : real;
   begin
     {$IFDEF OPL_EXT_ASYNC}
      asyncCOM  := 2;
      asyncMODE := 9600;
      asyncBITs := 7;
      asyncSTOP_BITs := 1;
      asyncPARITY := _PARITY(read_cfg_str_(_cfg_FN,cfg_COM_PARITY,'EVEN'),true);
     {$ENDIF}

     {$IFDEF OPL_EXT_UDP} {$IFDEF UDP}
      UDP_PORT_OPL.port:= read_cfg_word(_cfg_FN,cfg_UDP_PORT,UDP_PORT_OPL.port);
      OPLadr_ip_s:= cut_(read_cfg_str_(_cfg_FN,cfg_IP_ADR,''));
     {$ENDIF} {$ENDIF}

     _error_fda:= true;
     read_cfg:= inherited read_cfg(_cfg_FN);

     smphr_AUP:= false;
     {$IFDEF REQUEST_AUP}
      read_lastREQ(fn_AUPupdated,Ts_REQUEST_AUP);
     {$ELSE}
      r:= OPL__REQUEST_AUPi; Ts_REQUEST_AUP:= AbsTime - (r-1)*60;
     {$ENDIF}

     r:= OPL__REQUEST_RTZi; Ts_REQUEST_RTZ:= AbsTime - (r-2)*60;

     {save_stream:= read_cfg_bool(_cfg_FN,cfg_STREAM,false);
     opl_STREAM:= save_stream;}

     alt_FL5min:= read_cfg_word(_cfg_FN,cfg_alt_FL5min,120);
     alt_FL5max:= read_cfg_word(_cfg_FN,cfg_alt_FL5max,130);

    {if _read_cfg(SYSTEMcfg,cfg_CAS_FUA,true)='' then cas_FUA:= read_cfg_bool(_cfg_FN, cfg_CAS_FUA , cas_FUA);}
   end;


destructor O_OPL.Done;
     begin
       inherited Done;
      {$IFDEF OPL__SAVE_STREAM}
       if stream_open then close(stream_file);
       stream_open:= false;
      {$ENDIF}

      {$IFDEF OPL_EXT_UDP} {$IFDEF UDP}
       net_abort(UDP_PORT_OPL.desc);
       Dispose(UDPpkt);
      {$ENDIF} {$ENDIF}
     end;


procedure O_OPL.check;
    const last_min : byte = 60;
    var   h,m,s : byte;
          r : real;
          d : TDate;
    begin
      {if smphr then Exit;}

     {תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
       0. stream file
      תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
     } {check_stream_file;}

     {תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
       1. prijem dat
      תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
     } inherited check; { nacitanie dat, receive a potvrdenie }

     {תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
       2. Testovanie na Tr,Ts
      תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
     } if (Tr_<>0) and (Tr_+TrTimeOut<=absTime) then {handle_OLDI_event(Tr_TimeOut)};
       if (Ts_+TsTimeOut<=absTime) then send_pkt(ord(msHB),NODE_REMOTE, @hd_OPL4[msHB][1],length(hd_OPL4[msHB]));

     {תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
       3. Ziadosti na server OPL
      תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
     }{$IFDEF PRS}
       {$IFDEF REQUEST_AUP}
        if (not smphr_AUP) and (last_min<>min) then
           begin
             r:= aum_last;
             last_min:= min;
             if     (    Ts_REQUEST_AUP.is         { bola odoslana ziadost o AUP a odpoved neprisla v limite }
                     and (absTime>=Ts_REQUEST_AUP.last+r*60)
                    )
                 or (    (not Ts_REQUEST_AUP.is)   { ma byt odoslana automaticka ziadost o AUP...   }
                     and (not Ts_REQUEST_AUP.next)
                     and (absTime>=DTtoSec(Ts_REQUEST_AUP.date.r,Ts_REQUEST_AUP.date.m,Ts_REQUEST_AUP.date.d,
                                           aup_hour,aup_min,0
                                          )
                         )
                    )
                  then
                begin
                  if d.r<>0 then d:= Ts_REQUEST_AUP.date
                  else init_date(d, year,month,day);
                  send_request_AUP(@d);
                end
           end;
       {$ELSE}
         r:= OPL__REQUEST_AUPi;
         if OPL__REQUEST_AUP and (Ts_REQUEST_AUP + r*60 < absTime) then send_request_AUP;
       {$ENDIF}
      {$ENDIF}

      {$IFDEF RTZ}
       r:= OPL__REQUEST_RTZi;
       if OPL__REQUEST_RTZ and (Ts_REQUEST_RTZ + r*60 < absTime) then send_request_RTZ;
      {$ENDIF}
    end;


procedure O_OPL.HandleEvent(var _Event: TEvent);
    var   d: TDate;
    begin
      inherited HandleEvent(_Event);

      if (_Event.What<>evNothing) then
        case _Event.Command of

          cmARCHIV_OPL    : zalohuj_archiv(pathSTREAM,'*.'+fn_ext,msgBCK,msgCOPY,nil);

          cmOPL_ERLINE    : Say2(msgWARNING,'V nastaven‚m limitu nebyla p©ijata ‘ dna zpr va od OPL.');

          {$IFDEF PRS}
           cmZIADOST_AUP  : begin
                              init_date(d,year,month,day);
                              send_request_AUP(@d);
                            end;
          {$ENDIF}

          {$IFDEF RTZ}
           cmZIADOST_RTZ  : send_request_RTZ
          {$ENDIF}

          else Exit
        end
      else Exit;

      ClearEvent(_Event)
    end;
