    const  { vypocty }
            RADIUS = 4;

            POCITAJ__POLOHY      : bool = false; { nemohol --//-- planzet                 }
            {PREPIS__VYPIS_PLANOV : bool = false;  nemohol byt aktualizovany vypis planov }
            ZDROJ_PLANU          : bool = true;
            STAV_PLANU           : bool = true;
            HLASENIA             : bool = true;
            HLAS_NENAJDENA_MAPA  : bool = true;


    const  { Ak doplnim dalsie "VYPIS", mal by som zmenit i v objekte TScrollDB_FDP...
           }
            CNL_RPL_VYPIS : bool = {$IFDEF SERVER} true {$ELSE} false {$ENDIF};         { vypis zmazanych planov }
            CNL_VYPIS     : bool = {$IFDEF SERVER} true {$ELSE} false {$ENDIF};         { vypis zmazanych planov }
            DEC_VYPIS     : bool = {$IFDEF SERVER} true {$ELSE} false {$ENDIF};         { vypis nepovolenych planov }
            ARR_VYPIS     : bool = {$IFDEF SERVER} true {$ELSE} false {$ENDIF};         { vypis ukoncenych planov }


            PLANZET_MAPA  {$IFDEF MAPY}: bool {$ENDIF} = {$IFDEF OPL} true {$ELSE} false {$ENDIF};

            {$IFDEF MAPY}
             draw_FONT    : byte = 0;     { velkost fontu }
             { pomocne
             } OBNOV_MAPU : bool = false; { nemohol --//-- planzet                 }
            {$ENDIF}


    const   PRN_HIDDEN_PLAN : bool = false;