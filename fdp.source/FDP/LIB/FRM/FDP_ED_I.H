     const FormLocalMenu : PChar =

           {$IFDEF BGI}
             {$IFDEF SLOVAK}
                ('~F1~ help    ~CtrlF1~ index    ~(Ctrl)'#17#196#217'~ potvrdenie');
             {$ENDIF}
             {$IFDEF CZECH}
                ('~F1~ help    ~CtrlF1~ index    ~(Ctrl)'#17#196#217'~ potvzen¡');
             {$ENDIF}
             {$IFDEF ENGLISH}
                ('~F1~ help    ~CtrlF1~ index    ~(Ctrl)'#17#196#217'~ confirmation');
             {$ENDIF}
           {$ELSE}
             ('~F1~ help    ~CtrlF1~ index    ~Ctrl Enter~  OK');
           {$ENDIF}


           FDPFormLocalMenu : PChar =

            {$IFDEF ODOSLI_ULOZ}
             {$IFDEF SLOVAK}
                  ('~F1~ help   ~Ctrl+ÄÙ~  - potvrdenie planu a jeho spracovanie...');
             {$ENDIF}
             {$IFDEF CZECH}
                  ('~F1~ help   ~Ctrl+ÄÙ~  - potvrzen¡ planu a jeho zpracovan¡...');
             {$ENDIF}
             {$IFDEF ENGLISH}
                  ('~F1~ help    ~Ctrl+ÄÙ~  - plan confirmation and processing...');
             {$ENDIF}
           {$ELSE}
             {$IFDEF SLOVAK}
                 ('~F1~ help   ~AltP~ odoslanie   ~AltU~ ulo‘enie do s£bora   ~Esc~ zru¨enie');
             {$ENDIF}
             {$IFDEF CZECH}
                 ('~F1~ help   ~AltP~ odesl n¡   ~AltU~ ulo‘en¡ do souboru   ~Esc~ zru¨en¡');
             {$ENDIF}
             {$IFDEF ENGLISH}
                 ('~F1~ help    ~AltS~  distribute plan    ~AltA~  add plan    ~Esc~ cancel');
             {$ENDIF}
           {$ENDIF}


           REQLocalMenu : PChar =

           {$IFDEF SLOVAK}
             ('~F1~ help    ~AltP~ povolenie    ~AltU~ povolenie s £pravami    ~AltZ~ zamietnutie   ~AltD~ odlo‘enie');
           {$ENDIF}

           {$IFDEF CZECH}
             ('~F1~ help    ~AltP~ povolenie    ~AltU~ povolenie s £pravami    ~AltZ~ zamietnutie   ~AltD~ odlo‘enie');
           {$ENDIF}

           {$IFDEF ENGLISH}
             ('~F1~ help    ~AltP~ povolenie    ~AltU~ povolenie s £pravami    ~AltZ~ zamietnutie   ~AltD~ odlo‘enie');
           {$ENDIF}

