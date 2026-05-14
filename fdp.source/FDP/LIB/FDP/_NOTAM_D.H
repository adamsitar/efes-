    const NTM_LINE        = MTK_2_LINE;

          kod_NTM_ID      = 1+4+1+2;     { C0413/97 }
          kod_NTM_DATE    = 13;


    const db_NTM_RIADKOV  = 7;        { kodovanie je natvrdo }

          db_NTM_data     = 0;
          db_NTM_D        = 1;
          db_NTM_E1       = 2;
          db_NTM_E2       = 3;
          db_NTM_E3       = 4;
          db_NTM_19       = 5;
          db_NTM_ine      = 6;

          dbchg_NTM       : bool  = false;
          dbchg_NTM_RPL   : bool  = false;

          dbattr_NTM = {$IFDEF DB_BIN} 0{DBbin} {$ELSE} 0 {$ENDIF};


    type  PNTM = ^TNTM;
          TNTM = record
           { definicia priestoru
           }
            _NTM  : pchar;                    { [MTK_2_LINE] notam - cislo     }
            _Q    : pchar;                    { [MTK_2_LINE] systemova polozka }

            _A    : string [kod_AP];          { responsible unit          }
            _B    : string [kod_NTM_DATE];    { datum zaciatku 9603281230 }
            _C    : string [kod_NTM_DATE];    { -//- ukoncenia            }

            _D    : pchar;                    { [MTK_2_LINE]x cas,pozn    }
            _E    : pchar;                    { [MTK_2_LINE]y suradnice   }

            _F,_G : string [kod_VYS];         { vyuzivane vysky           }


           { vypoctove premenne              - > kluc polozky
           }
            dav   : TDate;                    { datum platnosti           }
            dap   : TDatum;                   { datum podania             }
            let   : string [kod_AP];          { pracovisko podania planu  }

            stt   : string [kod_plan_status]; { len lokalna premenna      }

            {$IFDEF NET}
             rec  : Tplan_rec;
            {$ENDIF}
          end;
