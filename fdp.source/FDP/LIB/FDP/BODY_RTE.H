          { תתתתתתתתתתתתתתתתתתתתת }
          { TRAT                  }
          { תתתתתתתתתתתתתתתתתתתתת }

    const   {$IFDEF URTE_IGNORE}
             rte_UPPER  = 'U';
            {$ENDIF}
            rte_ALLIAS : bool = true;


    type    TRTE_BOD  = record
              kod : string[kod_OB];
             {io  : pchar    ak je bod vystupny, smeruje na ...
                             redundancia nevznikne, lebo zriedka
                             je bod vystupny na viacero smerov
                            }
            end;

            PRTE_BODY = ^TRTE_BODY;
            TRTE_BODY = array[0..max_BODY-1] of TRTE_BOD;

            PRTE  = ^TRTE;
            TRTE  = record
              kod  : string[kod_RTE];
              kodp : string[kod_RTE];

              rte  : PRTE_BODY;       { smernik na zoznamov bodov trate }
              top  : int;             { pocet bodov }

              typ  : byte
            end;


    const   max_RTE = MAX_ARRAY_SIZE div sizeof(TRTE);
    type    PRTEs = ^TRTEs;
            TRTEs = array[0..max_RTE-1] of TRTE;


    const   hd_RT = 'RT';  { rozhonova trat }
            hd_PT = 'PT';  { priletova a odletova trat do/z TSA PcTSA, kde c je zaciatocny znak kodu letiska }
             kod_PTdep = 2;


           { zapis trati LPS v cfg subore
           }

            sohRTE  = '(';
            eohRTE  = ')';


           { zapis vojenskych trati v cfg subore
           }
            pos_rtem       = 1;   { kod trate + body trate }
            pos_rtem_kod_  = 1;
            pos_rtem_kodp_ = 4;   { starsi kod }
            pos_rtem_bod_  = 2;
            pos_rtem_flo   = 2;   { uzivatel }
            pos_rtem_fl    = 3;   { FL }


            odd_rtem_item     = ';';
            odd_rtem_subitem  = ',';
            odd_rtem_subitems = icao_NXIT;
