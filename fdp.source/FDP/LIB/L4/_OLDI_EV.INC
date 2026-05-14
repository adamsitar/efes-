{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   nastavenie stavu Local&Remote Nodes, vydanie spravy o tom
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
procedure O_OLDI.chng_OLDI_status(_stat: stat_OLDI; _btstat: bool);
    var   s: string;
    begin
      stat:= _stat;
     {$IFDEF STATUS}
      if btOLDI<>nil then btOLDI^.new_title(mess_stat_OLDI[stat],_btstat);
     {$ENDIF}
      {if _btstat then btOLDI^.Draw;}
      writeln_pkt(nil,0,arch_SYS,'OLDI status set to '+strpas(message_stat_OLDI[stat])+'.',cl_SYS,false,false)
    end;


{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   overenie Call User Data
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   - otestuje, ci prijaty CALL REQUEST obsahuje spravne NSAP adresy ...
}
function O_OLDI.enabled_SVC (adr: TX25name; user_data: pbytes; user_len: byte): bool;
   var   _UDF    : UserDataField;
         i,cl    : int;
         s,res   : string;
         channel : S16BIT;

   label X,E;

   begin
     enabled_SVC:= false;
     if (not power) then Exit;

     s:= '';
     {$IFDEF OLDI_BACKUP}
      if (X25adr_REMOTE_<>'') then
         begin
           if switch_Remote then
              begin
                if (adr=X25adr_MASTER) or (adr=X25adr_BACKUP) then disable_SVC
                else begin
                       res:= 'Calling address '+adr+' is not allowed.';
                       goto E
                     end
              end
           else begin
                  res:= 'Trial to estabilish new connection from '+adr+'.'
                       +' Ignored, communication is in '
                       +' "'+strpas(message_stat_OLDI[stat])+'".';
                  goto E
                end
         end;
     {$ENDIF}

    (*{$IFDEF _X25}
     if is_open_X25channel(adr,channel) then
        begin
          res:= 'Another call request. Connection to '+adr+' has been already estabilished.';
          goto E
        end;
    {$ENDIF}*)

     if (adr=X25adr_MASTER) {$IFDEF OLDI_BACKUP} or (adr=X25adr_BACKUP) {$ENDIF} then
        begin
          X25adr_REMOTE_:= adr;
          {$IFDEF OLDI_BACKUP}
           if (adr=X25adr_MASTER) then OLDI_X25node_:= OLDI_X25nodeA
           else if (adr=X25adr_BACKUP) then OLDI_X25node_:= OLDI_X25nodeB
          {$ELSE}
           OLDI_X25node_:= OLDI_X25nodeA
          {$ENDIF}
        end
     else begin
            res:= 'Calling address '+adr+' is not allowed.';
            goto E
          end;

     Move(user_data^,_UDF,sizeof(_UDF));
     s:= 'Call request (NSAP 0x: '+_UDFstr(_UDF)+')';
     if (user_len<>SizeOf(UDF)) then
        begin
          res:= 'Invalid NSAP size ('+cstr(user_len,1)+').';
          goto X
        end;

     i:= 0; while (i<SizeOf(UDF)) and (_UDF[i]=UDF[i]) do inc(i);
     if (i<>SizeOf(UDF)) then
        begin
          res:= 'Not configured NSAP.';
          goto X
        end;

     enabled_SVC:= true;
     writeln_pkt(@_UDF,0, arch_PKT_REC,s, cl_OLDI_system_mess,false,false);
     writeln_pkt(nil,0,arch_SYS,'VC setup.',cl_SYS,false,false);
    { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }
       handle_OLDI_event(VC_Setup,nil);
    { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }
     Exit;

     X: X25adr_REMOTE_:= '';
        OLDI_X25node_:= -1;

     E: writeln_pkt(pchars(user_data),0, arch_PKT_REC,s+' '+res, cl_ERR,false,false);
        enabled_SVC:= false
   end;


{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   zrusenie spojenia (kanala X.25) medzi aplikaciami
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
procedure O_OLDI.disable_SVC;
    begin
     {$IFDEF _X25}
      if (X25_net<>nil) and (OLDI_X25node_>-1) then
         begin
           send_pkt_(msShutDown,'', nil,0);
           writeln_pkt(nil,0,arch_SYS,
                       'Closing channel '+cstr(X25nodes^.NODE^[OLDI_X25node_]^.CHAN,2),
                       cl_OLDI_system_mess,false,false
                      );
           X25_net^.CLOSE_CHANNEL(X25nodes^.NODE^[OLDI_X25node_]^.CHAN,nil,0,0)
         end;
     {$ENDIF}
     { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }
      chng_OLDI_status(IDLE_STATE,true);

      X25adr_REMOTE_:= '';
      OLDI_X25node_ := -1;

     { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }
      writeln_pkt(nil,0,arch_SYS,'VC clear.',cl_SYS,false,false)
    end;


{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   Stav komunikacie: vlastneho a vzdialeneho uzla
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   - kontrola TimeOut - u a automatickeho prechodu medzi stavmi
}
procedure O_OLDI.handle_OLDI_event(_event: event_OLDI; _ps: p_stat_OLDI);
    begin
      _ps:= nil;
      case stat of

        IDLE_STATE       :
          case _event of
            VC_Setup     : if _ps<>nil then _ps^:= READY_STATE
                           else chng_OLDI_status(READY_STATE,true);
          end;


        READY_STATE      :
          case _event of

            X25_Error,
            VC_Clear     : if _ps<>nil then _ps^:= IDLE_STATE
                           else disable_SVC;

            L_Startup    : if _ps<>nil then _ps^:= CONNECTION_PENDING_STATE
                           else begin
                                  writeln_pkt(nil,0,arch_SYS,tit_oldi_L_Startup,cl_SYS,false,false);
                                  chng_OLDI_status(CONNECTION_PENDING_STATE,true);
                                  Tr_:= 0
                                end;

            R_Startup    : if _ps<>nil then _ps^:= DATA_READY_STATE
                           else begin
                                { Ignore - bolo, ale ak prijmem Startup v tomto
                                  stave, protilahla stanica mi uz nemusi nan
                                  odpovedat, a ja sa ocitnem v slucke ocakavani :
                                  18:02ת24 ‏ OLDI init.
                                  18:02ת24 ‏ OLDI status set to IDLE STATE.
                                  18:02ת57 שÿCALL REQUEST (0x:  84 20 01 C9 06 49 26 01 CB 06 49 26 00 00 00 00)
                                  18:02ת57 ‏ VC setup.
                                  18:02ת57 ‏ OLDI status set to READY STATE.
                                  18:02ת58 שÿH@@@@D@01
                                  18:02ת58 ‏ L_Startup
                                  18:02ת58 ‏ OLDI status set to CONNECTION PENDING STATE.
                                }
                                writeln_pkt(nil,0,arch_SYS,tit_oldi_R_Startup,cl_SYS,false,false);
                                chng_OLDI_status(CONNECTION_PENDING_STATE,true);
                                send_pkt_(msStartUp,'', nil,0);
                                chng_OLDI_status(DATA_READY_STATE,true)
                              end
          end;


        CONNECTION_PENDING_STATE :
          case _event of

            X25_Error,
            VC_Clear     : if _ps<>nil then _ps^:= IDLE_STATE
                           else disable_SVC;

            L_Shutdown   : if _ps<>nil then _ps^:= READY_STATE
                           else begin
                                  writeln_pkt(nil,0,arch_SYS,tit_oldi_L_Shutdown,cl_SYS,false,false);
                                  chng_OLDI_status(READY_STATE,true);
                                 { optionaly can be cleared virtual circuit... }
                                end;

            R_Startup    : if _ps<>nil then _ps^:= DATA_READY_STATE
                           else begin
                                  writeln_pkt(nil,0,arch_SYS,tit_oldi_R_Startup,cl_SYS,false,false);
                                  chng_OLDI_status(DATA_READY_STATE,true);
                                  send_pkt_(msStartUp,'', nil,0)
                                end;

            Tr_Timeout   : if _ps<>nil then
                           else begin
                                  if send_StartUp then send_pkt_(msStartUp,'', nil,0);
                                  Tr_:= AbsTime
                                end
          end;


        DATA_READY_STATE :
          case _event of

            X25_Error,
            VC_Clear     : if _ps<>nil then _ps^:= IDLE_STATE
                           else disable_SVC;

            R_Startup    : { Ignore } ;

            R_Shutdown   : if _ps<>nil then _ps^:= CONNECTION_PENDING_STATE
                           else begin
                                  chng_OLDI_status(CONNECTION_PENDING_STATE,true);
                                  Tr_:= AbsTime;
                                  Ts_:= AbsTime
                                end;

            L_Shutdown   : if _ps<>nil then _ps^:= IDLE_STATE
                           else disable_SVC; {chng_OLDI_status(CONNECTION_PENDING_STATE,true);}

            R_Heartbeat  : if _ps<>nil then
                           else { Ok } Tr_:= AbsTime ;

            R_Data       : if _ps<>nil then
                           else { Ok } Tr_:= AbsTime ;

            L_Data       : if _ps<>nil then
                           else { Ok } Ts_:= AbsTime ;

            Tr_Timeout   : if _ps<>nil then _ps^:= IDLE_STATE
                           else begin
                                  writeln_pkt(nil,0,arch_SYS,tit_oldi_Tr_Timeout,cl_SYS,false,false);
                                  disable_SVC
                                end;

            Ts_Timeout   : if _ps<>nil then
                           else send_pkt_(msHeartBeat,'', nil,0);
          end;
      end
    end;
