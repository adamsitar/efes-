      const tit_7Ma  = {$IFDEF SLOVAK}  'identifik†cia letu ("poradov†")'; {$ENDIF}
                       {$IFDEF CZECH}   'identifikace  letu ("po©adov†")'; {$ENDIF}
                       {$IFDEF ENGLISH} 'call sign' ;                      {$ENDIF}

            tit_7Ma2 = {$IFDEF SLOVAK}  'oznaáenie pri hromadnom lete/poradovÇ á°slo letu do TSA'; {$ENDIF}
                       {$IFDEF CZECH}   'oznaáen° p©i hromadnem letu';  {$ENDIF}
                       {$IFDEF ENGLISH} 'additional call sign' ;        {$ENDIF}

            tit_7Mb  = {$IFDEF SLOVAK}  '®pecifik†cia SSR ';     {$ENDIF}
                       {$IFDEF CZECH}   'specifikace SSR ';      {$ENDIF}
                       {$IFDEF ENGLISH} 'SSR code describtion' ; {$ENDIF}

            tit_7Mc  = {$IFDEF SLOVAK}  'pl†novanò/pouëitò k¢d SSR'; {$ENDIF}
                       {$IFDEF CZECH}   'k¢d SSR';                   {$ENDIF}
                       {$IFDEF ENGLISH} 'SSR code' ;                 {$ENDIF}

            tit_8Ma  = {$IFDEF SLOVAK}  'pravidl† letu';  {$ENDIF}
                       {$IFDEF CZECH}   'pravidla letu';  {$ENDIF}
                       {$IFDEF ENGLISH} 'flight rules' ;  {$ENDIF}

            tit_8Mb  = {$IFDEF SLOVAK}  'typ letu';      {$ENDIF}
                       {$IFDEF CZECH}   'typ letu';      {$ENDIF}
                       {$IFDEF ENGLISH} 'flight type' ;  {$ENDIF}

            tit_9Mb  = {$IFDEF SLOVAK}  'k¢d typu lietadla';    {$ENDIF}
                       {$IFDEF CZECH}   'k¢d typu letadla';     {$ENDIF}
                       {$IFDEF ENGLISH} 'aircraft type code' ;  {$ENDIF}


            tit_9Me  = {$IFDEF SLOVAK}  'Éal®° typ';   {$ENDIF}
                       {$IFDEF CZECH}   'dal®° typ';   {$ENDIF}
                       {$IFDEF ENGLISH} 'next type' ;  {$ENDIF}

            tit_13Ma = {$IFDEF SLOVAK}  'k¢d letiska ®tartu';      {$ENDIF}
                       {$IFDEF CZECH}   'k¢d leti®tà startu';      {$ENDIF}
                       {$IFDEF ENGLISH} 'departure airbase code' ; {$ENDIF}

            tit_13Mb = {$IFDEF SLOVAK}  'áas ®tartu';      {$ENDIF}
                       {$IFDEF CZECH}   'áas ®tartu';      {$ENDIF}
                       {$IFDEF ENGLISH} 'departure time' ; {$ENDIF}

            tit_16Ma = {$IFDEF SLOVAK}  'k¢d letiska prist†tia'; {$ENDIF}
                       {$IFDEF CZECH}   'k¢d leti®tà p©ist†n°';  {$ENDIF}
                       {$IFDEF ENGLISH} 'arrival airbase code' ; {$ENDIF}

            tit_16Mb = {$IFDEF SLOVAK}  'áas prist†tia'; {$ENDIF}
                       {$IFDEF CZECH}   'áas p©ist†t°';  {$ENDIF}
                       {$IFDEF ENGLISH} 'arrival time' ; {$ENDIF}

            tit_15Ma_= {$IFDEF SLOVAK}  'veliáina ròchlosti'; {$ENDIF} { 68 }
                       {$IFDEF CZECH}   'veliáina ròchlosti'; {$ENDIF} { 68 }
                       {$IFDEF ENGLISH} 'speed quantity'   ;  {$ENDIF}

            tit_15Ma = {$IFDEF SLOVAK}  'pl†novan† ròchlosü letu'; {$ENDIF} { 68 }
                       {$IFDEF CZECH}   'pl†novan† rychlost letu'; {$ENDIF} { 68 }
                       {$IFDEF ENGLISH} 'speed'   ; {$ENDIF}

            tit_15Mb1= {$IFDEF SLOVAK}  'pl†novan† vò®ka (vrchn† hladina)'; {$ENDIF}
                       {$IFDEF CZECH}   'vò®ka (vrchn° hladina)'; {$ENDIF}
                       {$IFDEF ENGLISH} 'flight level (top)' ;    {$ENDIF}

            tit_15Mb2= {$IFDEF SLOVAK}  'in† vò®ka (spodn† hladina)';     {$ENDIF}
                       {$IFDEF CZECH}   'jin† vò®ka (spodn° hladina)';    {$ENDIF}
                       {$IFDEF ENGLISH} 'another flight level (bottom)' ; {$ENDIF}

            tit_OPM  = {$IFDEF SLOVAK}  'prev†dzkovateå';   {$ENDIF}
                       {$IFDEF CZECH}   'provozovatel';     {$ENDIF}
                       {$IFDEF ENGLISH} 'flight operator' ; {$ENDIF}

            tit_TSKM = {$IFDEF SLOVAK}  '£lohy letu';       {$ENDIF}
                       {$IFDEF CZECH}   '£koly letu';       {$ENDIF}
                       {$IFDEF ENGLISH} 'flight tasks' ;    {$ENDIF}

            tit_15Mc = {$IFDEF SLOVAK}  'traü letu';        {$ENDIF}
                       {$IFDEF CZECH}   'traü letu';        {$ENDIF}
                       {$IFDEF ENGLISH} 'route of flight' ; {$ENDIF}

            tit_18M  = {$IFDEF SLOVAK}  'pozn†mky a doplnkovÇ £daje'; {$ENDIF}
                       {$IFDEF CZECH}   'pozn†mky a doplnkovÇ £daje'; {$ENDIF}
                       {$IFDEF ENGLISH} 'notes and additional data' ; {$ENDIF}


            {$IFDEF L4444M}

              i_7Ma   = 0;
              i_7Mb   = 1;
              i_7Mc   = 2;

              i_8Ma   = 3;
              i_8Mb   = 4;

              i_9Mb   = 5;
              i_9Me   = 6;

              i_15Ma_ = 7;
              i_15Ma  = 8;

              i_13Ma  = 9;
              i_13Mb  = 10;
              i_16Ma  = 11;
              i_16Mb  = 12;

              i_15Mb1 = 13;
              i_15Mb2 = 14;

              i_OPM   = 15;
              i_TSKM  = 16;

             {$IFDEF FPLM_L}
              i_15M   = 17;
              i_18M   = i_15M+max_mFPL_15_r_hi+1;
             {$ELSE}
              i_15M   = 17;
              i_18M   = 19;
             {$ENDIF}

            {$ELSE}

              i_7Ma   = 0;
              i_7Ma2  = 1;
              i_7Mb   = 2;
              i_7Mc   = 3;

              i_8Ma   = 4;

              i_9Mb   = 5;
              i_9Me   = 6;

              i_15Ma_ = 7;
              i_15Ma  = 8;

              i_13Ma  = 9;
              i_13Mb  = 10;
              i_16Ma  = 11;
              i_16Mb  = 12;

              i_15Mb1 = 13;
              i_15Mb2 = 14;

              i_OPM   = 15;
              i_TSKM  = 16;

             {$IFDEF FPLM_L}
              i_15M   = 17;
              i_18M   = i_15M+max_mFPL_15_r_hi;
             {$ELSE}
              i_15M   = 17;
              i_18M   = 19;
             {$ENDIF}

            {$ENDIF}


            {$IFDEF FPLM_L} {$I _FPLm_fL.h}
            {$ELSE}         {$I _FPLm_fS.h}
            {$ENDIF}
