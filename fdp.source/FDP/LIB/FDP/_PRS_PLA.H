     const  db0_PRS_RIADKOV = 1;
            db_PRS_RIADKOV  = 4;

            db_PRS_data     = 0;
            db_PRS_18       = 1;
            db_PRS_19       = 2;
            db_PRS_ine      = 3;

            dbchg_PRS       : bool  = false;
            dbchg_PRS_RPL   : bool  = false;

            dbattr_PRS = {$IFDEF DB_BIN} DBbin {$ELSE} DBtxt {$ENDIF};


     type   PPRS = ^TPRS;
            TPRS = record

             { definicia priestoru
             }
              kod   : string [kod_PRS];       { [k1] nazov priestoru            }
              typ   : char;                   { typ priestoru }

              vys1  : string [kod_VYS];       { spodna vyuzivana vyska [_PRS.h] }
              vys2  : string [kod_VYS];       { horna -//-                      }

              zac   : TDatum;                 { datum zaciatku 9603281230       }
              kon   : TDatum;                 { -//- ukoncenia                  }

              unt   : string [kod_AP];        { responsible unit                }

              pozn  : pchar;

             {IFDEF FUA}
             { schvalene parametre,
               udrziavaju sa kvoli kontrole spravnosti spracovania planu,
               pretoze ich povodne schvaleny rozsah sa moze znizit,
               ale pri naslednom spracovani opat zvysit (
               napr. F350->F300->F310->F350)
             }
              vys1p    : string [kod_VYS];    { maximalne schvalene hodnoty }
              vys2p    : string [kod_VYS];
              zacp     : TDatum;
              konp     : TDatum;

              vys1_aup : string [kod_VYS];    { hodnoty uvedene v plane aup }
              vys2_aup : string [kod_VYS];
              zac_aup  : TDatum;
              kon_aup  : TDatum;
             {ENDIF}

             { vypoctove premenne FDP
             }
              stat  : string [kod_plan_status];
              let   : string [kod_AP];        { [k2] letisko podania planu     }
              dap   : TDatum;                 { [k3] datum podania             }
              das   : TDate;                  { [k4] datum schvalenia, urcuje sa datum subora }

              poz   : Tpoz;

             { ulozenie udajov o potvrdeni spravy
             }
              {$IFDEF NET}
               rec   : Tplan_rec;
              {$ENDIF}

             { vypoctove premenne
             }
               f_map : byte;

             { ukazovatel na udaje miestne spracovavene,
               aby mohli byt prenesene do standartnych funkcii,
               kde sa s dalsim ukazovatelom nerata
             }
              ine : pointer;
              oprava : bool;
            end;
