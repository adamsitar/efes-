constructor O_VERA.Init;
      begin
        inherited Init(nil,@power_VERA,VERAcfg,strpas(fnOB.fn),
                       0,false,
                       VERA_PACKET_SIZE,VERA_BUFFER_SIZE,true,VERA_BUFFER_SIZE,
                       0,0,0,0,0,0,0,0,0,0,
                       nil,VERA_coor_info,
                       @hd_VRL4,0 {sizeof(hd_ASL4) div sizeof(Thead_ICAO)},
                       nil,0,
                       @writeln_VERA, @archive_VERA, @utc_VERA,
                       cl_VERA, cl_VERA_system_mess,
                       path_VERA, path_VERA+spath_ERR, extVERA
                      );

        src_type:= _FDP_DEF.vera;
        dst_set := [];

        est_alt_:= altFL;

        _mil_sys:= false; { aby rozobral trat FPLM do bodov }
        _dct_points:= false;
        _oat_exclude:= true;

        {$IFDEF UDP}
         New(UDPpkt); fillchar(UDPpkt^,sizeof(UDPpkt^),0);

         with UDP_PORT_VERA do udp_open_port (UDP_FHOST,port,desc,asynch,true);
         Delay(20);
         VERAadr_ip:= nm_prs_addr(VERAadr_ip_s);
         if (VERAadr_ip<>0) then writeln('VERA initialized on UDP port: '+WordToHex(UDP_PORT_VERA.port)+ '.')
         else {(neterrno<>0) or}
            RunError('Invalid or missing '+cfg_IP_ADR+' ('+VERAadr_ip_s
                      +' '+cstr(neterrno,1)
                      +'/'+cstr(VERAadr_ip,1)+')'
                    );
         Delay(1000)
        {$ENDIF}
      end;


destructor O_VERA.Done;
     begin
       inherited Done;

       {$IFDEF UDP}
        net_abort(UDP_PORT_VERA.desc);
        Dispose(UDPpkt);
       {$ENDIF}
     end;


function O_VERA.read_cfg(_cfg_FN: string): bool;
   var   res: string;
   label E,X;
   begin
     res:= '';

     {$IFDEF UDP}
      UDP_PORT_VERA.port:= read_cfg_word(_cfg_FN,cfg_UDP_PORT,UDP_PORT_VERA.port);
      VERAadr_ip_s:= cut_(read_cfg_str_(_cfg_FN,cfg_IP_ADR,''));
     {$ENDIF}

     read_cfg:= inherited read_cfg(_cfg_FN);

     X: if res<>'' then res:= _cfg_FN+' '+res+'.';
     E: if res<>'' then RunError(res);
     read_cfg:= res=''
   end;


procedure O_VERA.HandleEvent(var _Event: TEvent);
    var   i : int;
    begin
      inherited HandleEvent(_Event);

      if (_Event.What<>evNothing) then
        case _Event.Command of

          cmARCHIV_VERA    : zalohuj_archiv(pathSTREAM,'*.'+fn_ext,msgBCK,msgCOPY,nil);

          else Exit

        end
      else Exit;

      ClearEvent(_Event)
    end;