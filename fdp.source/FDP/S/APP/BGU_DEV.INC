var  SaveExit : pointer;
     SaveMain : TProc;


procedure MPU_check; far;
    const _sec : byte = 60;
    var   i : int;
    begin
      if @SaveMain<>nil then SaveMain;

      if (MPUs<>nil) and (_sec<>sec) and (sec mod MON_STATUS_REFRESH = 0) then
         begin
           writeln_monitoring;
           _sec:= sec
         end
    end;


procedure MPUdone; far;
    var   i : int;
    begin
      if MPUs<>nil then
         begin
           {for i:= lo_MPUadr to hi_MPUadr do if MPUs^[i].bt<>nil then Dispose(MPUs^[i].bt,Done);
            Spravi to MainApp
           }
           Dispose(MPUs);
           MPUs:= nil
         end;
      ExitProc:= SaveExit
    end;


procedure MPUinit;

    procedure detect_BGU_MPU(BGUn: byte; BGUs: string);
        var   i,adr,k : int;
              s : string;
        begin
          if cut_(BGUs)<>'' then
             for i:= 0 to getstritems(BGUs,[',',' ']) do
               begin
                 s:= uni_str(getstr(BGUs,i,[',',' ']));
                 if s[1] in ['A'..'F'] then s:= '$'+s;
                 val(s,adr,k);
                 if (k>0) or (not (adr in [lo_MPUadr..hi_MPUadr])) then RunError(BGUcfg+' - invalid MPU number ('+s+').');
                 MPUs^[adr].bgu:= BGUn
               end
          else MessError('Not defined '+'BGU'+cstr(BGUn,1)+'/MPU interface...',true,true);
        end;

    var   i,hi_ : int;
    begin
      SaveExit:= ExitProc;
      ExitProc:= @MPUdone;

      { Nacitanie BGU.ini
      }
      write('Reading '+BGUcfg+'... ');
      New(MPUs); fillchar(MPUs^,sizeof(MPUs^),0);
      for i:= lo_MPUadr to hi_MPUadr do with MPUs^[i] do bgu := NOBGU;
      for i:= lo_BGUadr to hi_BGUadr do
        begin
          detect_BGU_MPU(i, read_cfg_str_(BGUcfg,'BGU'+cstr(i,1),''))
        end;
      writeln('Done.');

      write('Initializing BGU/MPU interface... ');
      fillchar(test_buff,sizeof(test_buff),' ');
      BGUgril(BGUactive);
      SaveMain:= ACheck;
      ACheck:= MPU_check;
      writeln('Done.')
    end;


procedure MPUcfg_save; far;
    var   f   : text;
          s   : string;
          i,j : int;
    begin
      Assign(f,BGUcfg);
      Rewrite(f);
      writeln(f,'------------------------------------------------');
      writeln(f,' ACC Borispol');
      writeln(f,' Strip printer interface');
      writeln(f,' Configuration of connection to BGU-s and MPU-s');
      writeln(f,'------------------------------------------------');
      writeln(f,'');

      for i:= lo_BGUadr to hi_BGUadr do
        begin
          s:= 'BGU'+cstr(i,1)+' = ';
          for j:= lo_MPUadr to hi_MPUadr do
              if MPUs^[j].bgu=i then s:= s+' '+ByteToHex(j);
          writeln(f,s)
        end;

      Close(f)
    end;


constructor O_BGU.Init(_Owner: PObject);
      begin
        inherited Init(_Owner);
        p_scroll_data:= nil;
        path:= path_BGU;
        ext:= 'BGU'
      end;

destructor O_BGU.Done;
     begin
       inherited Done
     end;


function O_BGU.streamFN: string;
   begin
     if ext[1]<>'.' then ext:= '.'+ext;
     streamFN:=  path + inttostr(month,2,0)+inttostr(day,2,0)+inttostr(hour,2,0)+inttostr(0, 2,0) + ext
   end;


procedure O_BGU.HandleEvent(var _Event: TEvent);
    begin
      if (_Event.What and evMessage) <> 0 then
        case _Event.Command of

           cmPREHLAD_INTERFACE : _info(pathLST+'MPU.DOC', msgINFO);
           cmPRN_TEST          : MPUtest_strip;
           cmPRN_TEST1         : MPUtest_text;
           cmPRN_STATUS        : MPUsstatus;

           else if (_Event.Command>=cmPRN_ERROR) and (_Event.Command<=cmPRN_ERROR+hi_MPUadr) then
                    MPUstatus(_Event.Command-cmPRN_ERROR)

           else if (_Event.Command>=cmBGU_ERROR) and (_Event.Command<=cmBGU_ERROR+hi_BGUadr) then
                    BGUstatus(_Event.Command-cmBGU_ERROR)

         else Exit
        end
      else Exit;

      ClearEvent(_Event)
    end;


procedure O_BGU.writeln_pkt(data: string; prompt,message: string; cl: byte; is_utc,is_nl: bool);
    begin
      {$IFDEF DATA_WRITTEN_IN_APP}
        if (p_scroll_data<>nil) and (p_scroll_data^<>nil) then
           if (length(data)=0) and (prompt='') and (message='') then p_scroll_data^^.fwrite_nl
           else p_scroll_data^^.fwrite_data(@data[1],length(data), prompt,message, is_utc,true{is_tab},is_nl)
      {$ELSE}
        if MainApp<>nil then
           MainApp^.writeln_(@data[1],length(data), cl, prompt, false,true)
      {$ENDIF}
    end;
