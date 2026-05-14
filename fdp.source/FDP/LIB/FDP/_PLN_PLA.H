    const  db0_PLN_RIADKOV  = 1;
           db_PLN_RIADKOV   = 1;
           dbchg_PLN : bool = false;

           dbattr_PLN  = {$IFDEF DB_BIN} DBbin {$ELSE} 0 {$ENDIF};
           db_PLN_data = 0;

           sizeof_PLNpozn   = 14;
           sizeof_PLNbod    = kod_NDB+kod_TIME;


    type   PPLN = ^DPLN;
           DPLN = record
             idn  : string[kod_7a];
             typ  : string[kod_9b];

             dep  : TAP_;   {string[sizeof_PLNbod];}
             eet  : TNDB;   {string[sizeof_PLNbod];}
             exi  : TNDB;   {string[sizeof_PLNbod];}
             arr  : TAP_;   {string[sizeof_PLNbod];}

             src  : pchar;  {string[sizeof_PLNpozn];}

             date : TDate;

             {$IFDEF NET}
              rec  : Tplan_rec;
             {$ENDIF}
           end;

    const  {$IFDEF DEBUG} max_PLNs = 500;
           {$ELSE}        max_PLNs = 2000;
           {$ENDIF}

    type   PPLNs = ^TPLNs;
           TPLNs = array[0..MAX_PTRs-1] of PPLN;
