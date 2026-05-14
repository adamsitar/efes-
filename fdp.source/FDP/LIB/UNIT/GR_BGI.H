      const
            {SetWriteMode selection commands}
            LineMode          = $00;  {line drawing write style}
            PixelMode         = $20;  {pixel drawing write style}
            FillMode          = $40;  {fill write style}
            FloodFillType     = $60;  {floodfill option selection}
            TextMode          = $80;  {bitmapped text write style}
            GetImageMode      = $C0;  {GetImage write style}
            MiscCommand       = $E0;  {misc BGI driver commands}

            {Write mode functions}
            MoveWrite         = 0;    {foreground and background drawing}
            XorWrite          = 1;
            OrWrite           = 2;
            AndWrite          = 3;
            NotMoveWrite      = 4;
            NotXorWrite       = 5;
            NotOrWrite        = 6;
            NotAndWrite       = 7;

            ForeMoveWrite     = 8;    {foreground only drawing}
            ForeXorWrite      = 9;
            ForeOrWrite       = 10;
            ForeAndWrite      = 11;
            ForeNotMoveWrite  = 12;
            ForeNotXorWrite   = 13;
            ForeNotOrWrite    = 14;
            ForeNotAndWrite   = 15;

            BackMoveWrite     = 16;   {background only drawing}
            BackXorWrite      = 17;
            BackOrWrite       = 18;
            BackAndWrite      = 19;
            BackNotMoveWrite  = 20;
            BackNotXorWrite   = 21;
            BackNotOrWrite    = 22;
            BackNotAndWrite   = 23;

            SetBackColor      = 24;   {set the background color for draw method}
            GetWriteMode      = 30;   {return selected write mode on GetMaxMode call}
            GetBackColor      = 31;   {return background color on GetMaxMode call}

            {FloodFillType functions}
            BorderFill        = 0;  {use border floodfill method - default}
            SeedFill          = 1;  {use seed floodfill method}
            AutoFill          = 8;  {auto-select simplex or complex fill - default}
            ComplexFill       = 9;  {force complex floodfill always}
            FillCompressOff   = 10; {use standard floodfill stack - default}
            FillCompressOn    = 11; {use compressed floodfill stack}
            FillDelayOff      = 12; {fill area while searching - default}
            FillDelayOn       = 13; {delay fill to after search, not active in simplex}
            FillTracerOff     = 14; {no tracing of search path - default}
            FillTracerOn      = 15; {show search path as it is processed}
            GetFloodFillOpt   = 31; {ret FF option flags in next GetMaxMode call}

            {Misc Command functions}
            SetGetPixelReadOnly  = 0;  {set GetPixel to read monly mode}
            SetGetPixelReadWrite = 1;  {set GetPixel to write after read mode}
            SetGetImageReadOnly  = 2;  {set GetImage to read only mode}
            SetGetImageReadWrite = 3;  {set GetImage to write after read mode}
            SetPutImgBackColor   = 24; {set new putimage background color}

            {These misc cmd functions modify return value of next GetMaxMode call}
            GetCurrentMode     = 25; {ret actual graph mode in use}
            GetXYStackPeak     = 26; {ret last peak val of fill XYstack}
            GetXYStackFree     = 27; {ret last val of free XYstack space}
            GetPutImgWriteMode = 30; {ret last write mode used by PutImage}
            GetPutImgBackColor = 31; {ret background color used by PutImage}
