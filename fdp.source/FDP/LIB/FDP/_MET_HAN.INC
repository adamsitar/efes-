{$IFDEF MET}

  function _handle_event_MET (var _Event: TEvent; O: PObject; MET: pointer): bool;
     begin
       _handle_event_MET:= false;
       if _Event.what=evNothing then Exit;

       _handle_event_MET:= true;

       case _Event.What of

         evKeyDown:
          case _Event.Key of

            kbAltF11   : SetCommand(Pending,O,cmPREHLAD_SYN);

            else _handle_event_MET:= false
          end;

         evCommand, evBroadcast:

           case _Event.Command of

             0 : ;

             cmPREHLAD_SYN       : prehlad_SYN;
             cmPREHLAD_SYN_ARCH  : prehlad_SYN_ARCH;

             {cmPREHLAD_MET      : prehlad_MET;
              cmPREHLAD_MET_ARCH : prehlad_MET_ARCH;
             }

             {$IFDEF MET_RLI}
              {cmPREHLAD_MRL_ARCH : prehlad_MRL;
              cmPREHLAD_MRL_ARCH : prehlad_MRL_ARCH;}

              cmARCHIV_MRL       : zalohuj_archiv(pathMRL,'*.'+extMRL,msgBCK,msgCOPY,nil);
             {$ENDIF}

             else _handle_event_MET:= false
           end

         else _handle_event_MET:= false
       end
     end;

{$ENDIF}