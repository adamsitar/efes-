     const ctrlFPLM = '   Ctrl+F5 ';

   {$IFDEF SLOVAK}

     const  mnu_FPLM_PLAN   = ' PLèN LETU ~F~PL... ';

            {$IFDEF VLASTNE_PLANY}
             FPLM_PLAN_     = ' PLèNY LETOV';
             FPLM_PLAN_LET  = tit_VLASTNE+FPLM_PLAN_+'Ctrl+F5 ';
             FPLM_PLAN_ALL  = tit_VSETKY +FPLM_PLAN_;
            {$ELSE}
             FPLM_PLAN      = ' ~P~LèNY LETOV  Ctrl+F5 ';
            {$ENDIF}
            {FPLM_PREHLAD    = ' ~P~REHúAD VOJENSKùCH FPL ';}
            FPLM_ACT        = ' AKTIVOVANê LETY';
            FPLM_ARR        = ' UKONÄENê LETY';


            FPLMM           = ' PLèNY LETOV ~M~IMO TRATã LPS ';

            FPLMFPL         = 'HLèSENIE O SPRACOVANã PODANùCH FPL/LETOV';
            FPLMLET         = 'HLèSENIE O OSTATNùCH FPL/LETOCH';
            FPLMFIL         = 'HLèSENIE O PODANùCH SPRèVACH FPL/LETOV';
            {$IFDEF OPL}
             FPLMPRE        = 'ALEBO PREAKTIVOVANIE PLèNOV LETOV';
            {$ELSE}
            FPLMPRE         = 'PREAKTIVOVANIE PLèNOV LETOV';
            {$ENDIF}
            FPLCNLDAY       = 'ZRUõENIE NEAKTIVOVANùCH PLèNOV PO DNI PLATNOSTI ';
            FPLMCNL         = 'ALEBO ZRUõENIE NEAKTIVOVANùCH PLèNOV PO';

            FPLMARW         = 'UPOZORNENIE NA NEVYDANIE SPRèVY O PRISTèTI';
            FPLMARWC        = '- //- PRE VõETKY/LEN RIADENê LETY';
            FPLMARR         = 'LIMIT PRE VYDANIE SPRèVY O PRISTèTI';
            FPLMDEL         = 'DEAKTIVOVANIE LETOV';

            FPLMINE         = 'ODLãõENIE INùCH OD VOJENSKùCH FPL ';
            FPLMINE9        = '- PODúA TYPU LETó•A ';
            FPLMINEAP       = '- PODúA LETISKA õTARTU/PRISTèTIA ';

            FPLMREGULARITA  = 'REGULARITA ';
            FPLMREGFPLM     = 'KONFLIKT PLèNOV LETOV ';
            FPLMREGFIR      = 'KONFLIKT TRATE LETU A RIADENEJ OBLASTI (õTèTNEJ HRANICE) ';
            FPLMREGFUAPLAN  = 'KONFLIKT TRATE LETU A PODANêHO PLèNU PRIESTORU ';
            FPLMREGFUAACT   = 'KONFLIKT TRATE LETU A VYUíãVANêHO PRIESTORU ';


            FPLML15         = '- POÄET RIADKOV V POLI "TRAÜ"  ';
            FPLML18         = '- POÄET RIADKOV V POLI "POZNèMKA" ';
            FPLMSTRIP       = '(PRE)AKTIVOVANê PLèNY AKO STRIPY ';
            FPLMSTRIP15B    = 'ZOBRAZENE DEKïDOVANEJ TRATE V STRIPE ';

            FPLMPRNICAO     = 'ICAO FORMèT TLAÄE ';

   {$ENDIF}


   {$IFDEF CZECH}

     const  mnu_FPLM_PLAN  = ' PLèN LETU ~F~PL... ';

            FPLM_PLAN      = ' ~P~LèNY LET¶  Ctrl+F5 ';
            FPLM_ACT       = ' AKTIVOVANê LETY';
            FPLM_ARR       = ' UKONÄENê LETY';


            FPLMM          = ' PLèNY LET¶ ~M~IMO TRATã LPS ';

            FPLMFPL        = 'HLèõENã O ZPRACOVèNã PODANùCH FPL/O LETECH';
            FPLMLET        = 'HLèõENã O OSTATNãCH FPL/LETECH';
            FPLMFIL        = 'HLèõENã O PODANùCH ZPRèVACH FPL/O LETECH';
            {$IFDEF OPL}
             FPLMPRE       = 'ANEBO PûEAKTIVOVèNã PLèN¶ LET¶';
            {$ELSE}
             FPLMPRE       = 'PûEAKTIVOVèNã PLèN¶ LET¶';
            {$ENDIF}
            FPLMCNL        = 'ZRUõENã NEAKTIVOVANùCH PLèN¶';
            FPLMARW        = 'UPOZORNâNã NA NEVYDèNã ZPRèVY ARR';
            FPLMARWC       = '- //- PRO VõECHNY/JEN PRO ûãZENê LETY';
            FPLMARR        = 'LIMIT PRO VYDèNã ZPRèVY ARR';
            FPLMDEL        = 'DEAKTIVOVèNã LET¶';

            FPLMINE        = 'ODLãõENã JINùCH OD VOJENSKùCH FPL ';
            FPLMINE9       = '- PODLE TYPU LETOUNU ';
            FPLMINEAP      = '- PODLE LETIõTâ STARTU/PûISTèTã ';

            FPLMREGULARITA = 'REGULARITA ';
            FPLMREGFPLM    = 'KONFLIKT PLèN¶ LET¶ ';
            FPLMREGFIR     = 'KONFLIKT TRATâ LETU A ûãZENê OBLASTI (STèTNI HRANICE) ';
            FPLMREGFUAPLAN = 'KONFLIKT TRATâ LETU A PODANêHO PLèNU PROSTORU ';
            FPLMREGFUAACT  = 'KONFLIKT TRATâ LETU A VYUíãVANêHO PROSTORU ';


            FPLML15        = '- POÄET ûèDKU V POLI "TRAÜ" ';
            FPLML18        = '- POÄET ûèDKU V POLI "POZNèMKA" ';
            FPLMSTRIP      = '(PûE)AKTIVOVèNY PLèNY JAKO STRIPY';
            FPLMSTRIP15B   = 'ZOBRAZENã DEKïDOVANê TRATâ V STRIPU ';


            FPLMPRNICAO    = 'ICAO FORMèT TISKU ';

   {$ENDIF}


   {$IFDEF ENGLISH}

     const  mnu_FPLM_PLAN   = ' MILITARY ~F~LIGHT PLAN... ';

            {FPLM_PREHLAD    = ' ~M~ILITARY FLIGHT PLANs ';}
            FPLM_PLAN       = ' ~F~LIGHT PLANS  Ctrl+F5 ';
            FPLM_ACT        = ' ACTIVATED FLIGHTs';
            FPLM_ARR        = ' REALISED FLIGHTs';


            FPLMM           = ' ~M~ILITARY FLIGHTs/PLANs ';

            (*FPLMFPL         = ' REPORTIE O SPRACOVANã PODANùCH FPL/LETOCH';
            FPLMLET         = ' HLèSENIE O OSTATNùCH FPL/LETOCH';
            FPLMFIL         = ' HLèSENIE O PODANùCH SPRèVACH FPL/LETOV';*)
            FPLPREDAY       = ' DAILY PREACTIVATING ';
            {$IFDEF OPL}
             FPLMPRE        = 'OR TIME LIMITED FPL PREACTIVATING';
            {$ELSE}
             FPLMPRE        = 'TIME LIMITED FPL PREACTIVATING';
            {$ENDIF}
            (*
            FPLCNLDAY       = ' ZRUõENIE NEAKTIVOVANùCH PLèNOV PO DNI PLATNOSTI ';
            FPLMCNL         = ' ALEBO ZRUõENIE NEAKTIVOVANùCH PLèNOV PO             [hod]';
            FPLMARW         = ' UPOZORNENIE NA NEVYDANIE SPRèVY ARR';
            FPLMARWC        = ' - //- PRE VõETKY/LEN RIADENê LETY';
            FPLMARR         = ' LIMIT PRE VYDANIE SPRèVY ARR                        [min]';
            *)

            FPLMDEL         = 'FLIGHTs DEACTIVATING';

            (*FPLMINE         = ' ODLãõENIE INùCH OD VOJENSKùCH FPL ';
            FPLMINE9        = ' - PODúA TYPU LETó•A ';
            FPLMINEAP       = ' - PODúA LETISKA õTARTU/PRISTèTIA ';*)

            (*FPLMREGULARITA  = ' FLIGHT REGULARITY ';
            FPLMREGFPLM     = ' FLIGHT PLANs CONFLICT PROBE ';
            FPLMREGFIR      = ' CONFLICT TRATE LETU A RIADENEJ OBLASTI (õTèTNEJ HRANICE) ';
            FPLMREGFUAPLAN  = ' KONFLIKT TRATE LETU A PODANêHO PLèNU PRIESTORU ';
            FPLMREGFUAACT   = ' KONFLIKT TRATE LETU A VYUíãVANêHO PRIESTORU ';
            *)

            FPLML15         = '- NUMBER OF LINES IN FIELD "ROUTE" ';
            FPLML18         = '- NUMBER OF LINES IN FIELD "NOTE" ';

            FPLMSTRIP       = 'DISPLAY (PRE)ACTIVATED PLAN AS STRIP ';
            FPLMSTRIP15B    = 'DISPLAY DECODED ROUTE IN STRIP ';

            FPLMPRNICAO     = 'ICAO PRINT FORM ';

   {$ENDIF}

