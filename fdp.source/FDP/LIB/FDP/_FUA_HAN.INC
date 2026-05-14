{$IFDEF FUA}

  function _handle_event_FUA (var _Event: TEvent; O: PObject; FUA: pointer): bool;
     begin
       _handle_event_FUA:= false;
       if _Event.what=evNothing then Exit;

       _handle_event_FUA:= true;

       case _Event.What of

         evCommand, evBroadcast:

           case _Event.Command of

             0 : ;

             {$IFDEF PROCESS_FUA}
              cmAUP     : podanie_AUP('');
              cmAUP_CHG : oprava_AUP;

              cmUUP     : podanie_UUP('');
              cmUUP_CHG : oprava_UUP;
             {$ENDIF}

             {$IFDEF FUA_DATA}
              cmPREHLAD_AUP       : prehlad_AUP(false);
              cmPREHLAD_AUP_PPL   : prehlad_AUP(true);
              cmPREHLAD_AUP_ARCH  : prehlad_AUP_ARCH;

              cmPREHLAD_UUP       : prehlad_UUP(false);
              cmPREHLAD_UUP_PPL   : prehlad_UUP(true);
              cmPREHLAD_UUP_ARCH  : prehlad_UUP_ARCH;
             {$ENDIF}

             else _handle_event_FUA:= false
           end

         else _handle_event_FUA:= false
       end
     end;

{$ENDIF}