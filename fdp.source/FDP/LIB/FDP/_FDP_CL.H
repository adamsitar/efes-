    const   cl_DISK   = clGRa;
            cl_SEND   = clGRb;
            cl_PROP   = yellow;
            cl_ACC    = white;

            cl_START  = clGRe;
            cl_LETI   = clON;
            cl_STOJI  = cyan;  {33; clGRc;}
            cl_MZP    = cyan;  {33; cyan;}
            cl_PRIST  = clOFF;
            cl_SEDI   = clGR9; {7}
            cl_HANGAR = clGR9; {a}

            cl_ACTIVE = yellow;
            cl_DATA   = clGRc;

            cl_PATRAT = white;
            bk_PATRAT = red;


          {
            Kodovanie planov s tymito spravami :
             - pri prijme, musi byt za KON_SPR priznak isTRG :
               KON_SPR + isTRGODD_SPR + stat+0021 + KON_SPR
             - pri archivovani sa koduje rovnako
          }


          { --------------------------- }
          { Farby vo vypise letov       }
          { --------------------------- }

    const   bkPLAN     = {$IFDEF SPEA} clGR5 {$ELSE} clGR6 {$ENDIF};
            bkPLAN_    : array[false..true] of byte = (bkPLAN-1,bkPLAN+1);

            bkPLAN_HID = bkPLAN + 2;
            clPLAN_HID = black;

    const   pozCL : array[low(Tpoz)..high(Tpoz)] of byte =
                    (cl_DISK,

                     cl_DISK,
                     cl_PROP,
                     cl_ACC,

                     cl_START,
                     cl_LETI,
                     cl_LETI,
                     cl_STOJI,
                     cl_MZP,
                     cl_PRIST,
                     cl_PATRAT,

                     cl_SEDI,
                     cl_HANGAR,
                     cl_HANGAR,

                     cl_HANGAR,
                     cl_HANGAR,
                     cl_HANGAR
                    );


          { --------------------------- }
          { Farby stripu                }
          { --------------------------- }

    const   cstrip    = bkPLAN;
            ccall     = cl_ACTIVE;
            cinfo     = 159;
            clast     = clOFF;    {cl_SEDI;}
            cnext     = clON;     {cl_START;}
            citem     = cl_DATA;

            clchg     = clGR2;
