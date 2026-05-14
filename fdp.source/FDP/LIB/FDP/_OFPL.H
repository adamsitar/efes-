    const   _MAX_mFPLs = MAX_PTRs;

    type    PmFPLs = ^TmFPLs;
            TmFPLs = array[0.._MAX_mFPLs-1] of PDmFPL;


    const {$IFDEF FDP_OPL}
            {$IFDEF DEBUG}
              max_mFPLs = 100;
              max_oFPLs = 100;
            {$ELSE}
              max_mFPLs = 100;
              max_oFPLs = 100;
            {$ENDIF}
          {$ELSE}
            {$IFDEF DEBUG}
             {$IFDEF EDD}
              max_PROP_mFPLs = 30;
              max_PROP_oFPLs = 30;
             {$ENDIF}

              max_mFPLs      = 50;
              max_oFPLs      = 50;
            {$ELSE}
             {$IFDEF EDD}
              max_PROP_mFPLs = 100;
              max_PROP_oFPLs = 100;
             {$ENDIF}

              max_mFPLs      = 300;
              max_oFPLs      = 300;
            {$ENDIF}
          {$ENDIF}


          {$IFDEF EDD}
           PROP_mFPL : PmFPL = nil;
          {$ENDIF}
           mFPL      : PmFPL = nil;


          {$IFDEF FPLO}
           {$IFDEF EDD}
            PROP_oFPL : PaFPL = nil;
           {$ENDIF}
            oFPL      : PaFPL = nil;
          {$ENDIF}
