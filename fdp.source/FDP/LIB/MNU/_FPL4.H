   {$IFDEF SLOVAK}
    const   FPL4M              = ' ATS-ROUTE ~F~LIGHT PLANs ';
            FPL4D              = ' DA~Y~ FLIGHT PLAN LIST ';

            mnu_FPL4_INAC      = ' ~I~NACTIVATED FPLs ';
            mnu_FPL4_PREA      = ' ~P~REACTIVATED FPLs ';
            mnu_FPL4_PROP      = ' P~R~OPOSED FPLs ';
            mnu_FPL4_COOR      = ' C~O~ORDINATED FPLs ';
            mnu_FPL4_NOTA      = ' ~N~OT ACTIVED FPLs ';
            mnu_FPL4_REAL      = ' REALISE~D~ FPLs ';
            mnu_FPL4_ALL       = ' A~L~L FPLs ';


{           mnu_FPL4_PPL       =
            mnu_FPL4_ARCH      =
            mnu_FPL4D_PPL      =
            mnu_FPL4D_ARCH     =}


            FPL4ERR            = 'ERROR DISPLAY/QEUE ';

            FPL4GET            = 'CHOOSE PLAN BY NAME ';

            FPL4PREDAY         = 'DAILY PREACTIVATING ';
            FPL4PRE            = 'OR TIME LIMITED PREACTIVATING';
            FPL4PRO            = 'DISPLAY PREACTIVATED FPL';
            FPL4COO            = 'PROPOSE FPL ACTIVATION';
            FPL4UNA            = 'CANCEL NOT ACTIVATED FPL';

            FPL4PPLENABLE      = '"PPL" MESSAGE PROCESSING';
            FPL4CHGENABLE      = '"CHG" MESSAGE PROCESSING';
            FPL4DLAENABLE      = '"DLA" MESSAGE PROCESSING';
            FPL4CNLENABLE      = '"CNL" MESSAGE PROCESSING';
            FPL4DEPENABLE      = '"DEP" MESSAGE PROCESSING';
            FPL4ARRENABLE      = '"ARR" MESSAGE PROCESSING';

            FPL4XGENABLE       = '"X"/"G" FPL PROCESSED ';
            ACTORDEP           = 'ACT ON FIR DEPARTUREs';


            FDRGET             = 'CHOOSE CONCRETE DAY PLAN(s) ';

            FPL4L15            = '- NUMBER OF LINES IN FIELD 15 ';
            FPL4L18            = '- NUMBER OF LINES IN FIELD 18 ';

            FPL4SOURCE         = 'FPL SOURCE DISPLAY ';
            FPL4A36YKA         = 'DATA IN CYRILLIC ';

            FPL4SORT           = 'FPL SORTING  ';
            FPL4SORT_7a        = 'BY CALL SIGN';
            FPL4SORT_INP       = 'BY INPUT POINT';
            FPL4SORT_EET       = 'BY EET TIME';
            FPL4SORT_STAT      = 'BY PROCESSING ';
            FPL4SORT_NOT       = 'UNSORTED';

            FPL4REPORTPLAN     = 'REPORT AS TLG/PLAN';
            FPL4CHGREP         = '"CHG" MESSAGE REPORTING';
            FPL4DLAREP         = '"DLA" MESSAGE REPORTING';
            FPL4CNLREP         = '"CNL" MESSAGE REPORTING';
            FPL4DEPREP         = '"DEP" MESSAGE REPORTING';
            FPL4ARRREP         = '"ARR" MESSAGE REPORTING';


            FPL4PRNICAO        = 'ICAO PRINT FORM ';


            FPL49bCHECKICAO    = 'CHECKING 9b FIELD BY ICAO REGISTER ';
            FPL49bCHECKTSGA    = '- ALLOWING 9b CONTENTS BY TSGA REGISTER ';
            FPL49bCHECKZZZZ    = '- ALLOWING 9b CONTENTS BY FORMER ICAO REGISTER ';
            FPL49bCHECKMIL     = '- ALLOWING 9b CONTENTS BY MILITARY REGISTER ';
            FPL49cCHECKICAO    = 'CHECKING 9c FIELD BY ICAO REGISTER ';
            FPL49cCHECKZZZZ    = '- COMPLEMENTING 9c ARRAY BY ICAO REGISTER';

            FPL10aCHECK        = '10a DATA REGULARITY';
            FPL10bCHECK        = '10b DATA REGULARITY';


            FPL415aRANGE       = 'SPEED RANGE CHECKING';
            FPL415bRANGE       = 'ALTITUDE RANGE CHECKING';

            FPL4MZPENABLE      = 'STOPOVER ALLOWED';
            FPL415IOENABLE     = 'ZACIATOK/KONIEC TRATE CEZ OBLAST JE KOD TRATE';
            FPL415RxRENABLE    = 'ROUTE CROSSING ALLOWED ';
            FPL415BxRENABLE    = 'OUT OF ROUTE POINT ALLOWED ';
            FPL415BxRKM        = 'DISTANCE RESTRICTION OF THE OUT ROUTE POINT';
            FPL415XYxR         = '- MAXIMUM DISTANCE VOR-ROUTE              [km] ';
            FPL415BxR          = '- MAXIMUM DISTANCE POINT-ROUTE            [km] ';
            FPL415DCTPOINTS    = 'DCT REQUIRED';
            FPL415ALLENABLE    = 'INCLUDING ALL POINTS OF DECODED ROUTE';

            FPL415UPLNATRAT    = 'ROUTE COMPLETNESS CHECKING';
            FPL415CHECKFDA     = 'ROUTE INTEGRITY OPERATOR CHECKING';

            FPL418CHECKIS      = 'FIELD 18 EXISTENCE CHECKING';
            FPL418CHECK        = 'FIELD CONTENTS CHECKING';
            FPL418TYPECHECK    = '- SPECIFICATION, "TYPE"';
            FPL418DATCHECK     = '- SPECIFICATION, "DAT"';
            FPL418COMNAVCHECK  = '- SPECIFICATION, "NAV","COM"';
            FPL418DEPCHECK     = '- SPECIFICATION, "DEP"';
            FPL418DESTCHECK    = '- SPECIFICATION, "DEST"';
            FPL418ALTNCHECK    = '- SPECIFICATION, "ALTN"';
            {FPL418RALTCHECK    = '- SPECIFICATION "RALT"';}

            APEETEXI           = 'EET/EXI ON FIR AERODROMEs';


            CHG713             = 'EDIT FIELDs 7,13 AT ISSUING CHG';
            FPLCHG1417         = 'EDIT FIELDs 14,17 AT ISSUING FPL,DLA';
            ACTFIELDS          = 'EDIT FIELDs 8..18 AT ISSUING DEP,ACT';

            {$IFDEF ATCA}
             EFIL8             = 'FILL EMPTY FIELD 8 AS "IS"';
             EFIL10            = 'FILL EMPTY FIELD 10 AS "S" WITH FIELD 7b OR "A"';
            {$ELSE}
             EFIL8             = 'FILL EMPTY FIELD 8 AS "IX"';
             EFIL10            = 'FILL EMPTY FIELD 10 AS "S" WITH FIELD 7b OR "N"';
            {$ENDIF}

            EFIL9              = 'FILL FIELD 9 ACCORDING ICAO REGISTER';
            EFIL15ab           = 'FILL EMPTY FIELDs 15a15b ACCORDING FIELD 9b';

   {$ENDIF}

   {$IFDEF CZECH}
    const   FPL4M              = ' ATS-ROUTE ~F~LIGHT PLANs ';
            FPL4D              = ' DA~Y~ FLIGHT PLAN LIST ';

            mnu_FPL4_INAC      = ' ~I~NACTIVATED FPLs ';
            mnu_FPL4_PREA      = ' ~P~REACTIVATED FPLs ';
            mnu_FPL4_PROP      = ' P~R~OPOSED FPLs ';
            mnu_FPL4_COOR      = ' C~O~ORDINATED FPLs ';
            mnu_FPL4_NOTA      = ' ~N~OT ACTIVED FPLs ';
            mnu_FPL4_REAL      = ' REALISE~D~ FPLs ';
            mnu_FPL4_ALL       = ' A~L~L FPLs ';


{           mnu_FPL4_PPL       =
            mnu_FPL4_ARCH      =
            mnu_FPL4D_PPL      =
            mnu_FPL4D_ARCH     =}


            FPL4ERR            = 'ERROR DISPLAY/QEUE ';

            FPL4GET            = 'CHOOSE PLAN BY NAME ';

            FPL4PREDAY         = 'DAILY PREACTIVATING ';
            FPL4PRE            = 'OR TIME LIMITED PREACTIVATING';
            FPL4PRO            = 'DISPLAY PREACTIVATED FPL';
            FPL4COO            = 'PROPOSE FPL ACTIVATION';
            FPL4UNA            = 'CANCEL NOT ACTIVATED FPL';

            FPL4PPLENABLE      = '"PPL" MESSAGE PROCESSING';
            FPL4CHGENABLE      = '"CHG" MESSAGE PROCESSING';
            FPL4DLAENABLE      = '"DLA" MESSAGE PROCESSING';
            FPL4CNLENABLE      = '"CNL" MESSAGE PROCESSING';
            FPL4DEPENABLE      = '"DEP" MESSAGE PROCESSING';
            FPL4ARRENABLE      = '"ARR" MESSAGE PROCESSING';

            FPL4XGENABLE       = '"X"/"G" FPL PROCESSED ';
            ACTORDEP           = 'ACT ON FIR DEPARTUREs';


            FDRGET             = 'CHOOSE CONCRETE DAY PLAN(s) ';

            FPL4L15            = '- NUMBER OF LINES IN FIELD 15 ';
            FPL4L18            = '- NUMBER OF LINES IN FIELD 18 ';

            FPL4SOURCE         = 'FPL SOURCE DISPLAY ';
            FPL4A36YKA         = 'DATA IN CYRILLIC ';

            FPL4SORT           = 'FPL SORTING  ';
            FPL4SORT_7a        = 'BY CALL SIGN';
            FPL4SORT_INP       = 'BY INPUT POINT';
            FPL4SORT_EET       = 'BY EET TIME';
            FPL4SORT_STAT      = 'BY PROCESSING ';
            FPL4SORT_NOT       = 'UNSORTED';

            FPL4REPORTPLAN     = 'REPORT AS TLG/PLAN';
            FPL4CHGREP         = '"CHG" MESSAGE REPORTING';
            FPL4DLAREP         = '"DLA" MESSAGE REPORTING';
            FPL4CNLREP         = '"CNL" MESSAGE REPORTING';
            FPL4DEPREP         = '"DEP" MESSAGE REPORTING';
            FPL4ARRREP         = '"ARR" MESSAGE REPORTING';


            FPL4PRNICAO        = 'ICAO PRINT FORM ';


            FPL49bCHECKICAO    = 'CHECKING 9b FIELD BY ICAO REGISTER ';
            FPL49bCHECKTSGA    = '- ALLOWING 9b CONTENTS BY TSGA REGISTER ';
            FPL49bCHECKZZZZ    = '- ALLOWING 9b CONTENTS BY FORMER ICAO REGISTER ';
            FPL49bCHECKMIL     = '- ALLOWING 9b CONTENTS BY MILITARY REGISTER ';
            FPL49cCHECKICAO    = 'CHECKING 9c FIELD BY ICAO REGISTER ';
            FPL49cCHECKZZZZ    = '- COMPLEMENTING 9c ARRAY BY ICAO REGISTER';

            FPL10aCHECK        = '10a DATA REGULARITY';
            FPL10bCHECK        = '10b DATA REGULARITY';


            FPL415aRANGE       = 'SPEED RANGE CHECKING';
            FPL415bRANGE       = 'ALTITUDE RANGE CHECKING';

            FPL4MZPENABLE      = 'STOPOVER ALLOWED';
            FPL415IOENABLE     = 'ZACIATOK/KONIEC TRATE CEZ OBLAST JE KOD TRATE';
            FPL415RxRENABLE    = 'ROUTE CROSSING ALLOWED ';
            FPL415BxRENABLE    = 'OUT OF ROUTE POINT ALLOWED ';
            FPL415BxRKM        = 'DISTANCE RESTRICTION OF THE OUT ROUTE POINT';
            FPL415XYxR         = '- MAXIMUM DISTANCE VOR-ROUTE              [km] ';
            FPL415BxR          = '- MAXIMUM DISTANCE POINT-ROUTE            [km] ';
            FPL415DCTPOINTS    = 'DCT REQUIRED';
            FPL415ALLENABLE    = 'INCLUDING ALL POINTS OF DECODED ROUTE';

            FPL415UPLNATRAT    = 'ROUTE COMPLETNESS CHECKING';
            FPL415CHECKFDA     = 'ROUTE INTEGRITY OPERATOR CHECKING';

            FPL418CHECKIS      = 'FIELD 18 EXISTENCE CHECKING';
            FPL418CHECK        = 'FIELD CONTENTS CHECKING';
            FPL418TYPECHECK    = '- SPECIFICATION, "TYPE"';
            FPL418DATCHECK     = '- SPECIFICATION, "DAT"';
            FPL418COMNAVCHECK  = '- SPECIFICATION, "NAV","COM"';
            FPL418DEPCHECK     = '- SPECIFICATION, "DEP"';
            FPL418DESTCHECK    = '- SPECIFICATION, "DEST"';
            FPL418ALTNCHECK    = '- SPECIFICATION, "ALTN"';
            {FPL418RALTCHECK    = '- SPECIFICATION "RALT"';}

            APEETEXI           = 'EET/EXI ON FIR AERODROMEs';


            CHG713             = 'EDIT FIELDs 7,13 AT ISSUING CHG';
            FPLCHG1417         = 'EDIT FIELDs 14,17 AT ISSUING FPL,DLA';
            ACTFIELDS          = 'EDIT FIELDs 8..18 AT ISSUING DEP,ACT';

            {$IFDEF ATCA}
             EFIL8             = 'FILL EMPTY FIELD 8 AS "IS"';
             EFIL10            = 'FILL EMPTY FIELD 10 AS "S" WITH FIELD 7b OR "A"';
            {$ELSE}
             EFIL8             = 'FILL EMPTY FIELD 8 AS "IX"';
             EFIL10            = 'FILL EMPTY FIELD 10 AS "S" WITH FIELD 7b OR "N"';
            {$ENDIF}

            EFIL9              = 'FILL FIELD 9 ACCORDING ICAO REGISTER';
            EFIL15ab           = 'FILL EMPTY FIELDs 15a15b ACCORDING FIELD 9b';

   {$ENDIF}

   {$IFDEF ENGLISH}

    const   FPL4M              = ' ATS-ROUTE ~F~LIGHT PLANs ';
            FPL4D              = ' DA~Y~ FLIGHT PLAN LIST ';

            mnu_FPL4_INAC      = ' ~I~NACTIVATED FPLs ';
            mnu_FPL4_PREA      = ' ~P~REACTIVATED FPLs ';
            mnu_FPL4_PROP      = ' P~R~OPOSED FPLs ';
            mnu_FPL4_COOR      = ' C~O~ORDINATED FPLs ';
            mnu_FPL4_NOTA      = ' ~N~OT ACTIVED FPLs ';
            mnu_FPL4_REAL      = ' REALISE~D~ FPLs ';
            mnu_FPL4_ALL       = ' A~L~L FPLs ';


{           mnu_FPL4_PPL       =
            mnu_FPL4_ARCH      =
            mnu_FPL4D_PPL      =
            mnu_FPL4D_ARCH     =}


            FPL4ERR            = 'ERROR DISPLAY/QEUE ';

            FPL4GET            = 'CHOOSE PLAN BY NAME ';

            FPL4PREDAY         = 'DAILY PREACTIVATING ';
            FPL4PRE            = 'OR TIME LIMITED PREACTIVATING';
            FPL4PRO            = 'DISPLAY PREACTIVATED FPL';
            FPL4COO            = 'PROPOSE FPL ACTIVATION';
            FPL4UNA            = 'CANCEL NOT ACTIVATED FPL';

            FPL4PPLENABLE      = '"PPL" MESSAGE PROCESSING';
            FPL4CHGENABLE      = '"CHG" MESSAGE PROCESSING';
            FPL4DLAENABLE      = '"DLA" MESSAGE PROCESSING';
            FPL4CNLENABLE      = '"CNL" MESSAGE PROCESSING';
            FPL4DEPENABLE      = '"DEP" MESSAGE PROCESSING';
            FPL4ARRENABLE      = '"ARR" MESSAGE PROCESSING';

            FPL4XGENABLE       = '"X"/"G" FPL PROCESSED ';
            ACTORDEP           = 'ACT ON FIR DEPARTUREs';

            FDRGET             = 'CHOOSE CONCRETE DAY PLAN(s) ';

            FPL4L15            = '- NUMBER OF LINES IN FIELD 15 ';
            FPL4L18            = '- NUMBER OF LINES IN FIELD 18 ';

            FPL4SOURCE         = 'FPL SOURCE DISPLAY ';
            FPL4A36YKA         = 'DATA IN CYRILLIC ';

            FPL4SORT           = 'FPL SORTING  ';
            FPL4SORT_7a        = 'BY CALL SIGN';
            FPL4SORT_INP       = 'BY INPUT POINT';
            FPL4SORT_EET       = 'BY EET TIME';
            FPL4SORT_STAT      = 'BY PROCESSING ';
            FPL4SORT_NOT       = 'UNSORTED';

            FPL4REPORTPLAN     = 'REPORT AS TLG/PLAN';
            FPL4CHGREP         = '"CHG" MESSAGE REPORTING';
            FPL4DLAREP         = '"DLA" MESSAGE REPORTING';
            FPL4CNLREP         = '"CNL" MESSAGE REPORTING';
            FPL4DEPREP         = '"DEP" MESSAGE REPORTING';
            FPL4ARRREP         = '"ARR" MESSAGE REPORTING';


            FPL4PRNICAO        = 'ICAO PRINT FORM ';


            FPL49bCHECKICAO    = 'CHECKING 9b FIELD BY ICAO REGISTER ';
            FPL49bCHECKTSGA    = '- ALLOWING 9b CONTENTS BY TSGA REGISTER ';
            FPL49bCHECKZZZZ    = '- ALLOWING 9b CONTENTS BY FORMER ICAO REGISTER ';
            FPL49bCHECKMIL     = '- ALLOWING 9b CONTENTS BY MILITARY REGISTER ';
            FPL49cCHECKICAO    = 'CHECKING 9c FIELD BY ICAO REGISTER ';
            FPL49cCHECKZZZZ    = '- COMPLEMENTING 9c ARRAY BY ICAO REGISTER';

            FPL10aCHECK        = '10a DATA REGULARITY';
            FPL10bCHECK        = '10b DATA REGULARITY';


            FPL415aRANGE       = 'SPEED RANGE CHECKING';
            FPL415bRANGE       = 'ALTITUDE RANGE CHECKING';

            FPL4MZPENABLE      = 'STOPOVER ALLOWED';
            FPL415IOENABLE     = 'ZACIATOK/KONIEC TRATE CEZ OBLAST JE KOD TRATE';
            FPL415RxRENABLE    = 'ROUTE CROSSING ALLOWED ';
            FPL415BxRENABLE    = 'OUT OF ROUTE POINT ALLOWED ';
            FPL415BxRKM        = 'DISTANCE RESTRICTION OF THE OUT ROUTE POINT';
            FPL415XYxR         = '- MAXIMUM DISTANCE VOR-ROUTE ';
            FPL415BxR          = '- MAXIMUM DISTANCE POINT-ROUTE ';
            FPL415DCTPOINTS    = 'DCT REQUIRED';
            FPL415ALLENABLE    = 'INCLUDING ALL POINTS OF DECODED ROUTE';

            FPL415UPLNATRAT    = 'ROUTE COMPLETNESS CHECKING';
            FPL415CHECKFDA     = 'ROUTE INTEGRITY OPERATOR CHECKING';

            FPL418CHECKIS      = 'FIELD 18 EXISTENCE CHECKING';
            FPL418CHECK        = 'FIELD CONTENTS CHECKING';
            FPL418TYPECHECK    = '- SPECIFICATION, "TYPE"';
            FPL418DATCHECK     = '- SPECIFICATION, "DAT"';
            FPL418COMNAVCHECK  = '- SPECIFICATION, "NAV","COM"';
            FPL418DEPCHECK     = '- SPECIFICATION, "DEP"';
            FPL418DESTCHECK    = '- SPECIFICATION, "DEST"';
            FPL418ALTNCHECK    = '- SPECIFICATION, "ALTN"';
            {FPL418RALTCHECK    = '- SPECIFICATION "RALT"';}

            APEETEXI           = 'EET/EXI ON FIR AERODROMEs';


            CHG713             = 'EDIT FIELDs 7,13 AT ISSUING CHG';
            FPLCHG1417         = 'EDIT FIELDs 14,17 AT ISSUING FPL,DLA';
            ACTFIELDS          = 'EDIT FIELDs 8..18 AT ISSUING DEP,ACT';

            {$IFDEF ATCA}
             EFIL8             = 'FILL EMPTY FIELD 8 AS "IS"';
             EFIL10            = 'FILL EMPTY FIELD 10 AS "S" WITH FIELD 7b OR "A"';
            {$ELSE}
             EFIL8             = 'FILL EMPTY FIELD 8 AS "IX"';
             EFIL10            = 'FILL EMPTY FIELD 10 AS "S" WITH FIELD 7b OR "N"';
            {$ENDIF}

            EFIL9              = 'FILL FIELD 9 ACCORDING ICAO REGISTER';
            EFIL15ab           = 'FILL EMPTY FIELDs 15a15b ACCORDING FIELD 9b';

   {$ENDIF}
