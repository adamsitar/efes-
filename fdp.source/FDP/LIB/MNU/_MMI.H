 {$DEFINE DISPLAY_MNU}
 {$IFDEF EDD}
   {$IFDEF MAPY}
     {$DEFINE DISPLAY_MNU_}
   {$ELSE}
     {$UNDEF DISPLAY_MNU}
   {$ENDIF}
 {$ENDIF}

 {$IFDEF SLOVAK}
  const  PROSTREDIE    = ' VLASTNOSTI P~R~OSTREDIA ';
         ZOBRAZENIE    = ' Z~O~BRAZENIE PLèNOV/SPRèV ';
         ZOZNAMY       = ' ~Z~OZNAMY PLèNOV/LETOV ';
         RFSH          = ' PRE~K~RESLENIE        Ctrl+ƒ ';

         DISPLAY       = ' ~D~ISPLAY (ROZLãõENIE)... ';
          DISPLAY_     = 'NASTAVENIE ROZLãõENA';
          _1           = '~1~. EGA  (640x400)  ';
          _2           = '~2~. VGA  (640x480)  ';
          _3           = '~3~. SVGA (800x600)  ';
          _4           = '~4~. SXGA (1024x768) ';
          _5           = '~5~. TIGA (1280x1024)';
 {$ENDIF}

 {$IFDEF CZECH}
  const  PROSTREDIE    = ' V~L~ASTNOSTI PROSTûEDã ';
         ZOBRAZENIE    = ' Z~O~BRAZENã PLèN¶/ZPRèV ';
         RFSH          = ' PûE~K~RESLENã      Ctrl+ƒ ';

         DISPLAY       = ' ~D~ISPLAY (ROZLIõENã)...';
          DISPLAY_     = 'NASTAVENã ROZLãõENã';
          _1           = '~1~. EGA  (640x400)  ';
          _2           = '~2~. VGA  (640x480)  ';
          _3           = '~3~. SVGA (800x600)  ';
          _4           = '~4~. SXGA (1024x768) ';
          _5           = '~5~. TIGA (1280x1024)';

 {$ENDIF}

 {$IFDEF ENGLISH}
  const  PROSTREDIE    = ' ~M~MI ADJUSTMENT ';
         ZOBRAZENIE    = ' DATA PR~E~SENTATION ';
         RFSH          = ' RE~F~RESH         Ctrl+ƒ ';

         DISPLAY       = ' ~D~ISPLAY (RESOLUTION)... ';
          DISPLAY_     = 'DISPLAY RESOLUTION';
          _1           = '~1~. EGA  (640x400)  ';
          _2           = '~2~. VGA  (640x480)  ';
          _3           = '~3~. SVGA (800x600)  ';
          _4           = '~4~. SXGA (1024x768) ';
          _5           = '~5~. TIGA (1280x1024)';
 {$ENDIF}
