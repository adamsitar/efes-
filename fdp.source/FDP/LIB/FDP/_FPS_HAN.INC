{ -------------------
  spracovanie
  -------------------
}
 function _handle_event_STATISTIKA (var _Event: TEvent; O: PObject; p: pointer): bool; far;
    var   date: TDate;
    begin
      _handle_event_STATISTIKA:= false;
      if _Event.what=evNothing then Exit;

      if _p_handle_event_STATISTIKA<>nil then
         begin
           _handle_event_STATISTIKA:= proc_handle_object_event (_p_handle_event_STATISTIKA)(_event,O,p);
           if _Event.what=evNothing then Exit;
         end;

      _handle_event_STATISTIKA:= true;

      case _Event.What of

        evCommand, evBroadcast:

          case _Event.Command of

            0 : ;

            cm_DENNA_STATISTIKA_PRELETOV  : prehlad_FPLS(false);
            cm_ARCHIV_STATISTIKY_PRELETOV : prehlad_FPLS(true);

            else _handle_event_STATISTIKA := false
          end

          else _handle_event_STATISTIKA:= false
        end
      end;

