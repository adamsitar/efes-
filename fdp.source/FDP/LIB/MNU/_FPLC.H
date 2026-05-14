   {$IFDEF SLOVAK}

     const  FPLCM    {= ' SPRèVY O LETOCH PO ~T~RATIACH LPS ';}
                     = ' (~C~IVILNê) LETY PO TRATIACH LPS ';

            FPLCCPL    = 'ZARADENIE CPL';
            FPLCCPLSSR = 'ZARADENIE CPL, AK Mè PRIRADENù SSR';

            FPLCARR  = 'PREPOÄET PRISTèTIA (OPRAVA PRIJATEJ SPRèVY)';
            FPLCDEL  = 'DEAKTIVOVANIE LETOV';
            FPLCDELN = 'ZRUõENIE POZNèMOK';
            FPLC15C  = 'KONTROLA SPRèVNOSTI ZèPISU TRATE ';
            FPLCSSR  = 'SSR CODE ASSIGNING ';
            FPLCARCH = 'PREHúAD UKONÄENùCH LETOV ZA POSLEDNùCH';

            FPL_FL   = 'ZOBRAZENIE VùõKY (V STRIPE) VO FL';
            FPL_VFR  = 'ZOBRAZENIE VùõKY (V STRIPE) AKO VFR';
            FPLC_10b = 'ZOBRAZENIE PRèZDNEHO POúA "KïD SSR"';

   {$ENDIF}


   {$IFDEF CZECH}

     const  FPLCM    {= ' PLèNY LET¶ PO ~T~RATãCH LPS ';}
                      = ' ~C~IVILNã LETY (PO TRATãCH LPS) ';

            FPLCCPL  = 'ZAûAZENã CPL';
            FPLCARR  = 'PûEPOÄET PûISTèN°';
            FPLCDEL  = 'DEAKTIVOVèNã LET¶';
            FPLCDELN = 'ZRUõENã POZNèMEK';
            FPLC15C  = 'KONTROLA SPRèVNOSTI ZèPISU TRATâ ';
            FPLCSSR  = 'SSR CODE ASSIGNING ';
            FPLCARCH = 'PûEHLED UKONÄENùCH LET¶ ZA POSLEDNãCH';

            FPL_FL   = 'ZOBRAZENã VùõKY (V STRIPU) VE FL';
            FPL_VFR  = 'ZOBRAZENã VùõKY (V STRIPU) JAKO VFR';
            FPLC_10b = 'ZOBRAZENã PRèZDNEHO POLE "KïD SSR"';
   {$ENDIF}


   {$IFDEF ENGLISH}

     const  FPLCM    = ' ~C~IVILIAN FLIGHTs/MESSAGEs ';
                     {= ' ~C~IVILIAN FLIGHTs';}

            FPLCCPL  = 'PROCESSING CPL';
            ACTASEST = 'ACTIVATION BY EST MESSAGE';
            FPLCARR  = 'ESTIMATE ARRIVAL TIME ';
            FPLCDEL  = 'FLIGHTs DEACTIVATING';
            FPLCDELN = 'NOTEs DEACTIVATING ';
            FPLC15C  = 'CHECK ROUTE POINTS ';
            FPLCARCH = 'REALISED FLIGHTs FOR LAST';

            FPL_FL   = '(STRIP) ALTITUDE AS "FL"';
            FPL_VFR  = '(STRIP) ALTITUDE AS "VFR"';
            FPLC_10b = 'EMPTY "SSR CODE" AS "A"';

            prnFPSFLO= 'PRINT FLIGHT OPERATOR DATA IN STATISTICS';
   {$ENDIF}

