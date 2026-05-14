           {
           ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
           €                             €
           € ZAMESTNANIE                 €
           €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
           }

    const  db0_ZAM_RIADKOV   = 1;
           db_ZAM_RIADKOV    = 4;

           db_ZAM_data       = 0;
           db_ZAM_18         = 1;
           db_ZAM_19         = 2;
           db_ZAM_ine        = 3;

           dbchg_ZAM     : bool = false;
           dbchg_ZAM_RPL : bool = false;

           dbattr_ZAM = {$IFDEF DB_BIN} DBtxt{DBbin} {$ELSE} DBtxt {$ENDIF};


    const  dx_ZAM = 350;  { rozmery ZAM }
           dy_ZAM = 68;


    type   PZAM = ^TZAM;
           TZAM = record

             kod    : string[kod_AP]; { zamestnanie je planovane pre }

             zac    : TDatum;         { datum zaciatku }
             kon    : TDatum;         { datum konca    }

             prav   : char;           { pravidla letu:  P-pristroje, V-vid }
             vys    : string[kod_VYS];

             vu     : string[kod_FLO];{ VU - prevadzkovatel }

             ulohy  : pchar;
             typy   : pchar;          { 41 }

             planov : word;           { planovanych letov }
             letov  : word;           { realizovanych letov }

             pozn   : pchar;

             src    : string[kod_AP]; { letisko podania planu }
             dap    : TDatum;         { datum podania/opravy  }

             stat   : string[kod_plan_status];

             {$IFDEF NET}
              rec   : Tplan_rec;
             {$ENDIF}

             poz    : Tpoz
           end;


    const  {$IFDEF DEBUG}  max_ZAM = 100;
           {$ELSE}         max_ZAM = 500;
           {$ENDIF}