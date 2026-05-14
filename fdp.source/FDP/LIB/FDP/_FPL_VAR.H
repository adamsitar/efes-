    const   pis_STRIP_EST        : bool = false;   { indikacia EST,CPL }
            pis_STRIP_COR        : bool = {$IFDEF EDD} true {$ELSE} false {$ENDIF};   {  -//- COR         }
            pis_STRIP_ACK        : bool = {$IFDEF PVO} true {$ELSE} false {$ENDIF};   { vypis ACK na stripe }
            pis_STRIP_10b        : bool = {$IFDEF PVO} false {$ELSE} true {$ENDIF};   { vypis ACK na stripe }
            (*pis_STRIP_SSN      : bool = {$IFDEF PVO} true {$ELSE} false {$ENDIF};   { vypis CASU/SSN      }*)

           {$IFDEF EDD}
            PROP_WARN            : bool = false;
            PROP_SCROLL          : bool = false;
            PROP_PRN             : bool = false;
            REC_PROP_PRN         : bool = false;

            NDB_NULL             : bool = false; { zobrazenie i prazdneho zoznamu na NDB }
            NDB_INP              : bool = {$IFDEF PVO} true {$ELSE} true {$ENDIF};
                                                 { zobrazenie stripov na vstupnych majakoch }

            NDB_OTHERS           : bool = true;
            NDB_XY               : bool = false; { priradenie bodu do skupiny, ak sa jeho suradnice zhoduju
                                                   s niektorym jej bodom
                                                 }
           {$ENDIF}


            PRN_REC              : bool = true;
            PRN_CHG              : bool = false;

            NDB_SL               : bool = {$IFDEF SK} true {$ELSE} false {$ENDIF};
                                                { i male pismena bodov na trati }