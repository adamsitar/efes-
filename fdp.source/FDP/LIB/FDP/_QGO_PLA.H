    {
    ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
    €                             €
    € SCHOPNOSTI                  €
    €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
    }

    const KOD_QGO  = 10;

          db0_QGO_RIADKOV = 2;
          db_QGO_RIADKOV  = 5;
          db_QGO_stav     = 0;
          db_QGO_tqgo     = 1;
          db_QGO_mqgo     = 2;
          db_QGO_19       = 3;
          db_QGO_ine      = 4;

          dbchg_QGO     : bool  = false;
          dbchg_QGO_RPL : bool  = false;

          dbattr_QGO = {$IFDEF DB_BIN} DBtxt{DBbin} {$ELSE} DBtxt {$ENDIF};

          dx_QGO  = 490; {390;}  { rozmery QGO }
          dy_QGO  =  77;



    type  PQGO = ^TQGO;
          TQGO = record
            kod   : string[KOD_AP];

            stav  : pchar;     { stav prostriedkov }

            TQGO  : string[KOD_QGO];
            TQGO_ : pchar;
            TQGOc : string[kod_TIME];

            MQGO  : string[KOD_QGO];
            MQGO_ : pchar;
            MQGOc : string[kod_TIME];

            date  : TDate;
            stat  : string[kod_plan_status];

            dap   : TDatum;

            {$IFDEF NET}
             rec  : Tplan_rec
            {$ENDIF}
          end;



    const  MAX_QGOs = MAX_PTRs;

    type   PQGOs = ^TQGOs;
           TQGOs = array[0..MAX_QGOs-1] of PQGO;

    const {$IFDEF DEBUG} max_QGO = 100;
          {$ELSE}        max_QGO = 500;
          {$ENDIF}
