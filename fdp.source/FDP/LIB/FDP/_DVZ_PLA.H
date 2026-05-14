    {
    ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
    €                             €
    € DIVERZIE                    €
    €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
    }

    const  {KOD_DVZ  = 60;}

           db0_DVZ_RIADKOV     = 2;

           db_DVZ_RIADKOV      = 6;
           db_DVZ_data         = 0;
           db_DVZ_poziadavka   = 1;
           db_DVZ_odoslanie    = 2;
           db_DVZ_zabezpecenie = 3;
           db_DVZ_19           = 4;
           db_DVZ_ine          = 5;

           dbchg_DVZ : bool = false;
           dbattr_DVZ = {$IFDEF DB_BIN} DBtxt{DBbin} {$ELSE} DBtxt {$ENDIF};


           dx_DVZ = 572;
           dy_DVZ = 114;


    type   PDVZ = ^TDVZ;
           TDVZ = record

             pre  : string[KOD_AP];            { diverzia pre koho - letisko podania }
             kym  : string[KOD_AP];            {   -//-   drzana kym  }

             date : TDate;
             zac  : string[kod_TIME];          { zaciatok     }
             kon  : string[kod_TIME];          { koniec       }
             od   : string[kod_TIME];          { vyhlasenie   }

             vystraha : string[kod_TIME];      { cas podania vystrahy }

             poziadavka   : pchar;             { poziadavka   }
             odoslanie    : pchar;             { odoslanie    }
             zabezpecenie : pchar;             { zabezpecenie }

             stat : string[kod_plan_status];

             dap  : TDatum;                    { datum podania planu, moze byt viac diverzii }
             {$IFDEF NET}
               rec : Tplan_rec
             {$ENDIF}
           end;



    const  MAX_DVZs = MAX_PTRs;

    type   PDVZs = ^TDVZs;
           TDVZs = array[0..MAX_DVZs-1] of PDVZ;


    const  {$IFDEF DEBUG} max_DVZ = 100;
           {$ELSE}        max_DVZ = 500;
           {$ENDIF}
