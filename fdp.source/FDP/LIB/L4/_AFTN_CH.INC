 procedure O_AFTN.check;
     begin
       inherited check;
       manage_tlg;
     end;


 function  O_AFTN.manage_archiv: bool;
    begin
      if inherited manage_archiv then
         begin
           zmaz_stare_subory(pathTLG+path_NOT_PROCESSED, allfiles, 24*ArchDays);
           archivuj_subory(pathTLG, allfiles, pathTLG+path_NOT_PROCESSED, false,by_hours{hold_TLG});
           initialize_TLG(true);
           manage_archiv:= true
         end
      else manage_archiv:= false
    end;


 const  {CISLO_SPRAVY : word = 0;
        AFTN_kod = 'AFTN'+ext_kod;}
        LOCAL_TIME_OFFSET: int = { naschval prazdne, aby hlasil chybu pri implementacii pre iny FIR }
                                 {$IFDEF LZ}   +1 {$ENDIF}
                                 {$IFDEF LK}   +1 {$ENDIF}
                                 {$IFDEF UK}   +3 {$ENDIF};


 function  O_AFTN.manage_connection: bool;
     var   imin,ihbmin: int;
     const lm : byte = 60;
           lh : byte = 24;
     begin
       manage_connection:= inherited manage_connection;

       if (TrTimeOut<>0) and (Tr_+TrTimeOut<AbsTime) then {Tr_:= AbsTime};   { ignorujem timeout }

       if (not COMsemaphor[asyncCOM]) and (last_HeartBeat<>min) then
          begin
            imin:= min; ihbmin:= HeartBeat_MIN;
            if ((Abs(imin-ihbmin) div HeartBeat_PERIODE) * HeartBeat_PERIODE + ihbmin = imin) then
              begin
                { Ts_+TsTimeOut<AbsTime then}
                _send_HeartBeat
              end
          end;

      { Citac by sa mal kazdu polnoc ku moskovskemu casu vygumovat
      }
       if (lh<>hour) or (lm<>min) then
          begin
            if (hour=0) and (min=0) then
               begin
                 CISLO_SPRAVY:= 0;
                 save_cislo(CISLO_SPRAVYcfg,CISLO_SPRAVY);
               end;
            lh:= hour;
            lm:= min
          end;
     end;


{ nacitanie tlg
}
 procedure O_AFTN.manage_tlg;
     const S_TLG  : bool = false;
           L_TLG  : byte = 24;
     var   prty : string[kod_MTK_2_PRTY];
     begin
       if (not S_TLG) and ((is_SS and tlg_SS) or (is_FF and tlg_FF) or (is_KK and tlg_KK)) then
          begin
            S_TLG:= true;
            if is_SS and tlg_SS then prty:= tlgSS
            else if is_FF and tlg_FF then prty:= tlgFF
            else prty:= tlgKK;
            read_tlg(prty);
            S_TLG:= false
          end;
     end;
