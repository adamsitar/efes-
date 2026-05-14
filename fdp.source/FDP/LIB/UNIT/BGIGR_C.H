    const   {$IFDEF DEBUG}
             minSaveWin__heap_size = 200; { kB } { velkost heapu, pod ktoru sa obrazovky ukladaju na disk }
            {$ELSE}
             minSaveWin__heap_size = 400; { kB } { velkost heapu, pod ktoru sa obrazovky ukladaju na disk }
            {$ENDIF}

            minWinHeap = {$IFDEF DEBUG} $10000 {$ELSE} $12000 {$ENDIF};


    const   driveSaveWin : byte = 0;
            SaveWinMem   : bool = false;     { povolenie nahravat okna do pamate }

            pathSaveWin  : PathStr = '';
            nameSaveWin  = 'w';
            extSaveWin   = 'win';

            maxPOLY      = 50;

    const { Farba pre standartny button   }
            clBUTTON_COLOR =  clGR6;
            clBUTTON_LIGHT =   3;
            clBUTTON_DARK  =  -4;

          { Farby pre sipky               }
            clARR_COLOR = clGR6;
            clARR_LIGHT = clGRb;
            clARR_DARK  = clGR2;

          { Farby pre info riadok         }
            clHOT_KEY   = 14;
            clINFO      = 15;

            cl_DATA     = clGRb;
            cl_SYS      = clGRe;
            cl_MESS     = 15;
            cl_ERR      = 4;


          { Parametre pre proceduru Button }
            btSmall = 0;
            btNorm  = 1;
            btLarge = 2;


          { velkost tiena }
            Xtien = 5;
            Ytien = 5;

            initX = 50;
            initY = 50;


    const  {$IFDEF SKRY_OKNA}
             SKRYVANIE : bool = false;   { ak sa aktualizuje display, skryje sa okno }
           {$ELSE}
             SKRYVANIE : bool = false;
           {$ENDIF}
