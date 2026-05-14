function _handle_event_STATISTIKA (var _Event: TEvent; O: PObject; FPL: pointer): bool; far;
   var   date: TDate;
   begin
     _handle_event_STATISTIKA:= false;
     if _Event.what=evNothing then Exit;

     if _p_handle_event_STATISTIKA<>nil then
        begin
          _handle_event_STATISTIKA:= proc_handle_object_event (_p_handle_event_STATISTIKA)(_event,O,FPL);
          if _Event.what=evNothing then Exit;
        end;

     _handle_event_STATISTIKA:= true;
     case _Event.What of

       {evKeyDown:}

       evCommand, evBroadcast:

         case _Event.Command of

           0 : ;

           cm_PRIEBEZNA_DENNA_STATISTIKA    : if StatistikaAPP<>nil then StatistikaAPP^.zobraz_priebeznu_statistiku_(true);
           cm_PRIEBEZNA_MESACNA_STATISTIKA  : if StatistikaAPP<>nil then StatistikaAPP^.zobraz_priebeznu_statistiku_(false);

           cm_UZATVORENA_DENNA_STATISTIKA   : if StatistikaAPP<>nil then StatistikaAPP^.zobraz_uzatvorenu_statistiku_(true);
           cm_UZATVORENA_MESACNA_STATISTIKA : if StatistikaAPP<>nil then StatistikaAPP^.zobraz_uzatvorenu_statistiku_(false);

          {$IFDEF DEBUG}
           cm_STATISTIKA_TEST : if StatistikaAPP<>nil then with StatistikaAPP^ do uzatvor_statistiku_za_den (posledna_sta);
          {$ENDIF}

           else _handle_event_STATISTIKA:= false
         end

         else _handle_event_STATISTIKA:= false
       end
     end;
