    {
    ‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
    €                             €
    € SCHOPNOSTI                  €
    €‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
    }

    const KOD_RTZ  = 10;

          db_RTZ_RIADKOV  = 4;
          db_RTZ_id       = 0;
          db_RTZ_data1    = 1;
          db_RTZ_data2    = 2;
          db_RTZ_ine      = 3;

          dbchg_RTZ  : bool  = false;
          dbattr_RTZ = DBbin;

          dx_RTZ  = 580;
          dy_RTZ  = 150;


    const kod_id  = 15;


    type  PRTZ = ^TRTZ;
          TRTZ = record
            id    : string[kod_id];
            data  : pchar;
            date  : TDate;

            {$IFDEF NET}
             rec  : Tplan_rec
            {$ENDIF}
          end;


    const  rtz_ID    = 'ID';
           rtz_DIR   = 'DIR';
           rtz_CR    = 'CR';
           rtz_VPD   = 'VPD';
           rtz_ALS   = 'ALS';
           rtz_DMK   = 'DMK';
           rtz_BMK   = 'BMK';
           rtz_W_    = 'W';
           rtz_QB    = 'QB';
           rtz_T     = 'T';
           rtz_QNH   = 'QNH';
           rtz_QFE   = 'QFE';
           rtz_TREND = 'TREND';


    const  MAX_RTZs = MAX_PTRs;

    type   PRTZs = ^TRTZs;
           TRTZs = array[0..MAX_RTZs-1] of PRTZ;

    const {$IFDEF DEBUG} max_RTZ = 10;
          {$ELSE}        max_RTZ = 100;
          {$ENDIF}
