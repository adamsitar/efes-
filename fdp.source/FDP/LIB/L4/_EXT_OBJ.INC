 function get_icao_streamFN(path,ext: string; den,mes,rok, hod,min: word): string;
    begin
      if ext[1]<>'.' then ext:= '.'+ext;
      get_icao_streamFN:= path + inttostr(mes,2,0)+inttostr(den,2,0)+inttostr(hod,2,0)+inttostr(0,2,0) + ext
    end;

 function O_EXT.streamFN: string;
    begin
      streamFN:= get_icao_streamFN(pathSTREAM,fn_ext, day,month,year, hour,min)
    end;


 procedure O_EXT.HandleEvent(var _Event: TEvent);
     begin
       inherited HandleEvent(_Event);

       if (_Event.What<>evNothing) then
         case _Event.Command of

           cmICAO_INI : _info(cfg_FN,tit_ini);

           cmICAO_STREAM_ARCHIVE : zalohuj_archiv(pathSTREAM,'*.'+fn_ext,msgBCK,msgCOPY,nil);

           {$IFDEF ALR}
            cmICAO_ALR  : ;
           {$ENDIF}

           {$IFDEF ERR}
            cmICAO_ERS  : _read_ERR(ext_ERS,@init_icao_editor_ers,@handle_icao_editor_ers,nil{hlp_AFTNERS},is_ERS);
           {$ENDIF}

           else Exit
         end
       else Exit;

       ClearEvent(_Event)
     end;
