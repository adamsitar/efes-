{$IFDEF RTZ}

  function _handle_event_RTZ (var _Event: TEvent; O: PObject; RTZ: pointer): bool;
     begin
       _handle_event_RTZ:= false;
       if _Event.what=evNothing then Exit;

       _handle_event_RTZ:= true;

       case _Event.What of

         evKeyDown:
          case _Event.Key of
             NULL      : ;
             {kbAltF8  : SetCommand(Pending,O,cmPREHLAD_RTZ);
             kbCtrlF8 : SetCommand(Pending,O,cmPREHLAD_RTZ_plan);
             }
            else _handle_event_RTZ:= false
          end;

         evCommand, evBroadcast:

           case _Event.Command of

             0 : ;

             {$IFDEF PROCESS_RTZ}
              cmRTZ      : formular_RTZ(nil, true,false);

              cmRTZsend  : if RTZ<>nil then say_data_sended(_SEND_RTZ(RTZ));
              cmRTZakt   : if RTZ<>nil then _RTZ_CHG(RTZ) else RTZ_oprava(false);
              cmRTZzru   : if RTZ<>nil then _RTZ_CNL(RTZ) else RTZ_zrusenie;

              cm_RTZ_RPL_CHG     : if RTZ<>nil then _CHG_RTZ_RPL(PScroller(O),RTZ);
              cm_RTZ_RPL_CNL     : if RTZ<>nil then _CNL_RTZ_RPL(PScroller(O),RTZ);

              cmPREHLAD_RTZ_RPL  : prehlad_RTZ_RPL;
             {$ENDIF}

             {$IFDEF PRN}
               cmRTZprint : if RTZ<>nil then print_RTZ(RTZ);
             {$ENDIF}

             cmPREHLAD_RTZ       : prehlad_RTZ(false);
             cmPREHLAD_RTZ_PPL   : prehlad_RTZ(true);
             cmPREHLAD_RTZ_ARCH  : prehlad_RTZ_ARCH;

             else _handle_event_RTZ:= false
           end

         else _handle_event_RTZ:= false
       end
     end;

{$ENDIF}