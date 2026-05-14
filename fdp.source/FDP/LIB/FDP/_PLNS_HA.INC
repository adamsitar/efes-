function _handle_event_PLN (var _Event: TEvent; O: PObject; PLN: PPLN): bool;
   begin
     _handle_event_PLN:= false;
     if _Event.what=evNothing then Exit;
     _handle_event_PLN:= true;

     case _Event.What of

       {evKey :}

       evCommand, evBroadcast:

         case _Event.Command of

             0 : ;

             {$IFDEF PLN}
              cmPREHLAD_PLN      : prehlad_PLN(false);
              cmPREHLAD_PLN_PPL  : prehlad_PLN(true);
              cmPREHLAD_PLN_ARCH : prehlad_PLN_ARCH;
             {$ENDIF}

             else _handle_event_PLN:= false
           end

         else _handle_event_PLN:= false
       end
     end;
