function _handle_event_FDP (var _Event: TEvent; O: PObject; p: pointer): bool;
   var   i : int;
   begin
     if _Event.what=evNothing then Exit;
     _handle_event_FDP:= true;

     case _Event.What of
       evCommand, evBroadcast:
         case _Event.Command of
           0  : {Default};
           else _handle_event_FDP:= false
         end
         else _handle_event_FDP:= false
       end;

     {$IFDEF EXTERNAL_NET}
      for i:= 0 to EXT_DEVICESpoc-1 do if (_Event.what<>evNothing) then EXT_DEVICES[i]^.HandleEvent(_Event);
     {$ENDIF}
   end;
