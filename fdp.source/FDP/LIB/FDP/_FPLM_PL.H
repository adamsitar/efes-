    {
    ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
    Û                             Û
    Û vojensky FPL                Û
    ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
    }

    const                 db_mFPL_RIADKOV   = 6;
          {$IFDEF FPLM_L} db0_mFPL_RIADKOV  = 5;
          {$ELSE}         db0_mFPL_RIADKOV  = 2;
          {$ENDIF}

          db_mFPL_data     = 0;
          db_mFPL_15_1     = 1;
          db_mFPL_15_2     = 2;
          db_mFPL_18       = 3;
          db_mFPL_19       = 4;
          db_mFPL_ine      = 5;


          rte_RT  = 'RT';
          rych_RT = 900; {km/h}


    const dbchg_mFPL     : bool = false;
          dbchg_mFPL_RPL : bool = false;
          dbchg_KRL      : bool = false;

          dbattr_FPM = {$IFDEF DB_BIN} DBbin {$ELSE} DBtxt {$ENDIF};

          kod_FPLMkey = 50;


    const kod_MTSK  = 2;
          max_ulohy_FPLM = 6;

    type  Tuloha_FPLM = string[kod_MTSK];
          Tulohy_FPLM = array [0..max_ulohy_FPLm-1] of Tuloha_FPLM;


    type  PDmFPL = ^DmFPL;
          DmFPL  = record

          { plan ------------------------------------------------
                 ak je DB_BIN, potom pozor na zmenu
                               struktury a DB zapisu
          }
            idn   : string[kod_MIDN];  { identifikacia      }
            { IFNDEF L4444M}
             idn_ : char;     { priznak hromadneho letu     }
            { ENDIF}
            ssr   : string[kod_7c];  { SSR kod              }

            _8a   : char;     { pravidla letu:  P-pristroje, V-vid }
            _8b   : char;     { typ planu podla ICAO        }

            com_  : string[kod_10a]; { vybavenie            }
            ssr_  : string[kod_10b]; { priznak SSR: A-ano, N-nie   }

            typ   : string[kod_9];   { typ -> kodom alebo znackou  }
            typ2  : string[kod_9];   { typ -> kodom alebo znackou  }

            rych  : single;   { rychlost                    }
            rych_ : char;     { velicina rychlosti          }

            vys   : word;     { vyska - spodna hladina      }
            vys_  : char;     { velicina vysky              }

            vys2  : word;     { vyska - horna hladina       }
            vys2_ : char;     { velicina vysky              }

            start : TAP;      { letisko startu              }
            prist : TAP;      { letisko pristatia           }
            prist_: string[kod_APb]; { zalozne -//-         }

            vu    : string[kod_FLO]; { VU - prevadzkovatel  }
            ulohy : Tulohy_FPLM;

            trat  : Pchar;
            pozn  : Pchar;


          { parametre platnosti
          }
            date  : TDate;                   { datum realizacie planu }
            dap   : TDatum;                  { datum podania/opravy   }
            let   : string[kod_AP];          { letisko podania planu  }
            stat  : string[kod_plan_status];


          { vypoctove premenne
          }
            cor_  : byte;      { oprava : kolkokrat ?        }

            trat_ : POBxys;
            bodov : int;       { pocet bodov na trati }
	    na_bod: byte;      { bod, na ktory leti   }

            poz   : Tpoz;
            sur   : Tsur;
            cl    : byte       { farba, akou sa vypisuje plan, aby sa nezdrziavalo jej urcenim }

            {$IFDEF MAPY};
              mapa : PMapData
            {$ENDIF}

            {IFDEF RDP};            { FDP_EDD musi byt vo vsetkych prepojenych staniciach FDP }
              TRG : TTRG_stat;
              RDP : TRTRadr;        { accept na RDP stanici }
              LAM : word            { Tplan_rec }
            {ENDIF}

            {IFDEF NET};
              rec  : Tplan_rec
            {ENDIF}
          end;

          DFPLM  = DmFPL;
          PFPLM  = PDmFPL;
