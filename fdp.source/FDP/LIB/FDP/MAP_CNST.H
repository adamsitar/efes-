    const  cXvystred = {$IFDEF LZ}   1440678.92729939 {$ENDIF}
                       {$IFDEF LK}   1130678.92729939 {$ENDIF}
                       {$IFDEF UKBB} 2250000.0        {$ENDIF}
                       ;

           cYvystred = {$IFDEF LZ}   5330329.11659767 {$ENDIF}
                       {$IFDEF LK}   5470329.11659767 {$ENDIF}
                       {$IFDEF UKBB} 5480000.00       {$ENDIF}
                       ;

           cRozsah   = {$IFDEF LZ}   503641.7984      {$ENDIF}
                       {$IFDEF LK}   507641.7984      {$ENDIF}
                       {$IFDEF UKBB} 800000.0         {$ENDIF}
                       ;

           MINVOLPAM = {$IFDEF DEBUG} 90 {$ELSE} 120 {$ENDIF} * 1024;  { minimum volnej pamati pre ostatne  }


    const  saveMAPY : bool = {$IFDEF DEBUG} true {$ELSE} true {$ENDIF};
           cursMAPY : bool = true;


    const  kb_mapa_ROZSAH   = kbAlt7;
           kb_mapa_PRIESTOR = kbAlt8;
           kb_mapa_STRED    = kbAlt9;
           kb_mapa_CENTRUJ  = kbAlt0;

           ZOBRAZ_MAPU : bool = false;
           FILLOVAT    : bool = true;


    const  cnst_SCROLL_MAP = [kbLeft,kbRight,kbUp,kbDown,'+','-'];

           kbd_TIME_OUT    = 5;          { limit na zvacsovanie rychlosti +/- }
           min_krok        = 50;
           max_krok        = 5;
           krok : byte     = min_krok;

           MAPY_DRAW_en    : bool = true;