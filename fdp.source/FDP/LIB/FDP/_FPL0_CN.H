    const  {$IFDEF DEBUG}
            DATA_ALLOC_TO = $AFFF;
           {$ELSE}
            DATA_ALLOC_TO = $1FFFF;
           {$ENDIF}


    const   fpl_EST = 'E';
            fpl_CPL = 'C';
            s_ARR   = 'ARR';
            NO_PL   = 'NOPL';


    const   {$IFDEF FPL}
              KOD_MIDN = 7;
            {$ELSE}
              KOD_MIDN = 5;
            {$ENDIF}

            RYCH_C         = 1;              { cela cast rychlosti }
            RYCH_D         = 2;              { desatinna }

            odd_BODOV = [icao_NXIT,kbCRLF,kbCR,kbLF,kbCR_,kbLF_];  { oddelovac v polozke trate medzi bodami }
            odd_BODU  = [icao_NXT,','];                 { -//- medzi cinnostami na bode }


    const   strip_max_bod   = 8;              { maximalny pocet bodov v stripe }
            strip_max_bod_p = 4;