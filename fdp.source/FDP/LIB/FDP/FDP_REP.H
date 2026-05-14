           { IFDEF IS_FDP_REP}
     const  namREP  = 'R';
            extREP  = '.REP';

            reports_FDP : POREP = nil;
           { ENDIF}


           {$IFDEF SSR_MANAGEMENT}
     const  namSSR  = 'E';
            extSSR  = '.SSR';

            reports_SSR : POREP = nil;
           {$ENDIF}


           {$IFDEF SPR}
     const  namSPR  = 'M';
            extSPR  = '.MES';

            reports_SPR : POREP = nil;
           {$ENDIF}
