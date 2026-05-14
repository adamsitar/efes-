function _handle_event_TLG (var _Event: TEvent; O: PObject; p: pointer): bool;
   begin
     _handle_event_TLG:= false;
     if _Event.what=evNothing then Exit;
     _handle_event_TLG:= true;

     case _Event.What of

       evKeyDown :

         case _Event.Key of

           kbF11 : SetCommand(Pending,nil,cm_TLG);

           else _handle_event_TLG:= false

         end;


       evCommand, evBroadcast:

         case _Event.Command of

           0 : ;

           {$IFDEF TLG}
            {$IFDEF TSGA}
             cm_RTS : formular_RTS;
             cm_RTO : formular_RTO;

             cm_RVM : formular_RVM;
             cm_RVI : formular_RVI;
            {$ENDIF}

            cm_TLG : formular_TLG;
           {$ENDIF}

           {cmPREHLAD_TLG : prehlad_TLGr;}

           else _handle_event_TLG:= false
         end

       else _handle_event_TLG:= false

     end;

   end;