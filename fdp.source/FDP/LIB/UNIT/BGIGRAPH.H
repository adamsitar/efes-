    const {$IFDEF DEBUG}
             minSaveWin__heap_size = 200; { kB } { velkost heapu, pod ktoru sa obrazovky ukladaju na disk }
          {$ELSE}
             minSaveWin__heap_size = 350; { kB } { velkost heapu, pod ktoru sa obrazovky ukladaju na disk }
          {$ENDIF}


    const   driveSaveWin : byte = 0;

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
            clHOT_KEY   = Yellow;
            clINFO      = clGRc;

            cl_DATA     = clGRa;
            cl_SYS      = clGRe;
            cl_MESS     = White;
            cl_ERR      = Red;


          { Parametre pre proceduru Button }
            btSmall = 0;
            btNorm  = 1;
            btLarge = 2;


          { velkost tiena }
            Xtien = 5;
            Ytien = 5;

            initX = 50;
            initY = 50;

