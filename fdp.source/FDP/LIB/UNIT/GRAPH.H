    const  Black        =  0;
           Blue         =  1;
           Green        =  2;
           Cyan         =  3;
           Red          =  4;
           Magenta      =  5;
           Brown        =  6;
           LightGray    =  7;
           DarkGray     =  8;
           LightBlue    =  9;
           LightGreen   = 10;
           LightCyan    = 11;
           LightRed     = 12;
           LightMagenta = 13;
           Yellow       = 14;
           White        = 15;


    const  HorizDir     = 0; { Orient left to right }
           VertDir      = 1; { Orient bottom to top }
           UserCharSize = 0; { User-defined character size }

           CenterText   = 1;
           LeftText     = 0;
           RightText    = 2;
           BottomText   = 0;
           TopText      = 2;

           DefaultFont  = BIT8x8;


    const  NormalPut = 0; { dest = source         }
           OrPut     = 1; {        source or dest }
           AndPut    = 2; {               and     }
           XorPut    = 3;
           NotPut    = 4; {        not source     }
           WhitePut  = 6; {        1              }
           BlackPut  = 7; {        0              }
           nSaDPut   = 8; {        not s and d    }
           nSoDPut   = 9; {        not s or d     }
           nSxDPut   = 10; {       not s xor d    }


    const  grOk             = 0;  { No error }
           grNoInitGraph    = 1;  { BGI graphics not installed }
           grNotDetected    = 2;  { Graphics hardware not detected }
           grFileNotFound   = 3;  { Device driver file not found   }
           grInvalidDriver  = 4;  { Invalid device driver file     }
           grNoLoadMem      = 5;  { Not enough memory to load driver }
           grNoScanMem      = 6;  { Out of memory in scan fill }
           grNoFloodMem     = 7;  { Out of memory in flood fill }
           grFontNotFound   = 8;  { Font file not found }
           grNoFontMem      = 9;  { Not enough memory to load font }
           grInvalidMode    = 10; { Invalid graphics mode for selected driver }
           grError          = 11; { Graphics error (generic error) }
           grIOerror        = 12; { Graphics I/O error }
           grInvalidFont    = 13; { Invalid font file }
           grInvalidFontNum = 14; { Invalid font number }


    const  EmptyFill        = 0;
           SolidFill        = 1;
           LineFill         = 2;
           LtSlashFill      = 3;
           SlashFill        = 4;
           BkSlashFill      = 5;
           LtBkSlashFill    = 6;
           HatchFill        = 7;
           XHatchFill       = 8;
           InterleaveFill   = 9;
           WideDotFill      = 10;
           CloseDotFill     = 11;
           UserFill         = 12;


    const  SolidLn   = $FFFF;
           DottedLn  = $AAAA;
           CenterLn  = $FFFF;
           DashedLn  = $F0F0;
           UserBitLn = $FFFF;


    type   FillSettingsType = record
             Pattern : Word;
             Color   : Word;
           end;


           PointType = record
             X, Y : int
           end;

