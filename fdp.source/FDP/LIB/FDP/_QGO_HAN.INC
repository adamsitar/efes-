{$IFDEF QGO}

  function _handle_event_QGO (var _Event: TEvent; O: PObject; QGO: pointer): bool;
     begin
       _handle_event_QGO:= false;
       if _Event.what=evNothing then Exit;

       _handle_event_QGO:= true;

       case _Event.What of

         evKeyDown:
          case _Event.Key of

            {$IFDEF PROCESS_QGO}
             kbF8     : SetCommand(Pending,O,cmQGO);
            {$ENDIF}

             kbAltF8  : SetCommand(Pending,O,cmPREHLAD_QGO);
             kbCtrlF8 : SetCommand(Pending,O,cmPREHLAD_QGO_plan);

            else _handle_event_QGO:= false
          end;

         evCommand, evBroadcast:

           case _Event.Command of

             0 : ;

             {$IFDEF PROCESS_QGO}
              cmQGO      : formular_QGO(nil, true,false);

              cmQGOsend  : if QGO<>nil then say_data_sended(_SEND_QGO(QGO));
              cmQGOakt   : if QGO<>nil then _QGO_CHG(QGO) else QGO_oprava(false);
              cmQGOzru   : if QGO<>nil then _QGO_CNL(QGO) else QGO_zrusenie;

              cm_QGO_RPL_CHG     : if QGO<>nil then _CHG_QGO_RPL(PScroller(O),QGO);
              cm_QGO_RPL_CNL     : if QGO<>nil then _CNL_QGO_RPL(PScroller(O),QGO);

              cmPREHLAD_QGO_RPL  : prehlad_QGO_RPL;
             {$ENDIF}

             {$IFDEF PRN}
               cmQGOprint : if QGO<>nil then print_QGO(QGO);
             {$ENDIF}

             cmPRIJATE_QGO       : prehlad_QGO(false);

             cmPREHLAD_QGO       : prehlad_QGO(false);
             cmPREHLAD_QGO_PPL   : prehlad_QGO_PPL;
             cmPREHLAD_QGO_plan  : prehlad_QGO(false);
             cmPREHLAD_QGO_ARCH  : prehlad_QGO_ARCH;

             else _handle_event_QGO:= false
           end

         else _handle_event_QGO:= false
       end
     end;

{$ENDIF}