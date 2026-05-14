      const { BGI:                 }
            { standartne  0 -  15  }
            { seda       16 -  31  }
            { modra2     32 -  47  }
            { modra1     48 -  63  }
            { modra      64 -  79  }
            { zelena1    80 -  95  }
            { zelena     96 - 111  }
            { fialova   112 - 127  }
            { cervena   128 - 143  }
            { orandzova 144 - 159  }
            { seda      239 - 254  }
            { biela     255        }


            { OPL:                 }
            { standartne  0 -  15  }
            { seda       16 -  31  }
            { modra1     32 -  41  }
            { zelena1    42 -  51  }
            { modra      52 -  55  }
            { fialova    56 -  59  }
            { z84              60  }
            { z?               61  }
            { clOFF            62  }
            { clON             63  }


             {$IFDEF EGAVGA}
               clGR0 = darkgray; clGR1 = darkgray; clGR2 = darkgray; clGR3 = darkgray; clGR4 = darkgray;
               clGR5 = darkgray; clGR6 = darkgray; clGR7 = darkgray; clGR8 = lightgray; clGR9 = lightgray;
               clGRa = lightgray; clGRb = lightgray; clGRc = lightgray; clGRd = white; clGRe = white;
               clGRf = white;
             {$ELSE}
               clGR0 =  16; clGR1 =  17; clGR2 =  18; clGR3 =  19; clGR4 =  20;
               clGR5 =  21; clGR6 =  22; clGR7 =  23; clGR8 =  24; clGR9 =  25;
               clGRa =  26; clGRb =  27; clGRc =  28; clGRd =  29; clGRe =  30;
               clGRf =  31;
             {$ENDIF}


             clWHITE = 15;  { white;      }
             clOFF   = { IFDEF EGAVGA}      Green (*{$ELSE} 62 {$ENDIF};  { green;      }*);
             clON    = { IFDEF EGAVGA} LightGreen (*{$ELSE} 63 {$ENDIF};  { lightgreen; }*);


      const {$IFDEF CZ}
             R60: byte = 250;
             G60: byte = 140;
             B60: byte = 140;

             R61: byte =   0;
             G61: byte = 180;
             B61: byte = 180;
            {$ELSE}
             R60: byte = 0;
             G60: byte = 180;
             B60: byte = 180;

             R61: byte = 255;
             G61: byte = 255;
             B61: byte = 255;
            {$ENDIF}