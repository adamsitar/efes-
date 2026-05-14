      const  cfgSTA  = 'STA.ini';

             sta_SOH = #2;            { zaciatok a koniec hlavicky }
             sta_EOH = #2;
             sta_EOT = #3;            { koniec dokumentu           }


      const { ------------------------------------
              hlavicka pre SRLP
            }
             cfg_HEADER_MACC    = 'HEADER-MACC';


            { ------------------------------------
              hlavicka pre LSRLP
            }
             cfg_HEADER_AIRBASE = 'HEADER-AIRBASE';


            { ------------------------------------
              nazvy sledovanych udajov
            }
             cfg_SUMA           = 'TITLE-SUMA';
             cfg_AIRBASES       = 'TITLE-AIRBASES';
             cfg_AIRBASE        = 'TITLE-AIRBASE';


            { sledovane udaje a nazvy pre lety
            }
             cfg_FPLC_FL_   = 'FPLC-FL';
             FPLC_FL: long  = 7450; FPLC_FL_ : string[kod_VYS] = 'M7450';

             cfg_FPLM_FL_   = 'FPLM-FL';
             FPLM_FL : long = 7450; FPLM_FL_ : string[kod_VYS] = 'M7450';

             cfg_FPLO_FL_   = 'FPLO-FL';
             FPLO_FL: long  = 7450; FPLO_FL_ : string[kod_VYS] = 'M300';


            { nazvy pre SRLP
            }
             cfg_REALIZED_FLIGHTS = 'TITLE-REALIZED-FLIGHTS';
             cfg_MILITARY_FLIGHTS = 'TITLE-MILITARY-FLIGHTS';
             cfg_CIVILIAN_FLIGHTS = 'TITLE-CIVILIAN-FLIGHTS';

             cfg_FPLM             = 'TITLE-FPLM';
             cfg_FPLM_FL          = 'TITLE-FPLM-FL';

             cfg_FPLM_VFR         = 'TITLE-FPLM-VFR';
             cfg_FPLM_IFR         = 'TITLE-FPLM-IFR';
             cfg_FPLM_TSA         = 'TITLE-FPLM-TSA';

             cfg_FPLO             = 'TITLE-FPLO';

             cfg_FPLC_VFR         = 'TITLE-FPLC-VFR';
             cfg_FPLC_IFR         = 'TITLE-FPLC-IFR';
             cfg_FPLC_FL          = 'TITLE-FPLC-FL';


            { nazvy pre LSRLP
            }
             cfg_REALIZED_FLIGHTS_A = 'TITLE-REALIZED-FLIGHTS-A';
             cfg_TOTAL_FLIGHTS_A    = 'TITLE-TOTAL-FLIGHTS-A';

             cfg_FLIGHT_TYPE_A    = 'TITLE-FLIGHT-TYPE-A';

             cfg_FPLM_A           = 'TITLE-FPLM-A';
             cfg_FPLM_FL_A        = 'TITLE-FPLM-FL-A';

             cfg_FPLM_IFR_A       = 'TITLE-FPLM-IFR-A';
             cfg_FPLM_VFR_A       = 'TITLE-FPLM-VFR-A';
             cfg_FPLM_TSA_A       = 'TITLE-FPLM-TSA-A';
             cfg_FPLM_ZAM_A       = 'TITLE-FPLM-ZAM-A';

             cfg_FPLO_A           = 'TITLE-FPLO-A';

             cfg_FPLC_A           = 'TITLE-FPLC-A';
             cfg_FPLC_FL_A        = 'TITLE-FPLC-FL-A';

             cfg_PLANNED          = 'TITLE-PLANNED';
             cfg_REALIZED         = 'TITLE-REALIZED';
             cfg_CONTROLLED       = 'TITLE-CONTROLLED';

            { nazvy pre priestory
            }

             cfg_TITLE_R_TSA  = 'TITLE-TSA-AREA';
             cfg_TITLE_GND    = 'TITLE-GND-AREA';

             cfg_TITLE_AREA   = 'TITLE-AREA';
             cfg_LINE_AREA    = 'LINE-AREA';

             cfg_TSA_RESERVED = 'TITLE-TSA-RESERVED';
             cfg_TSA_USED     = 'TITLE-TSA-USED';
             cfg_TSA_FLIGHTS  = 'TITLE-TSA-FLIGHTS';

             cfg_GND_RESERVED = 'TITLE-GND-RESERVED';
             cfg_GND_USED     = 'TITLE-GND-USED';


      type   POStaOPL = ^OStaOPL;
             OStaOPL  = object (OStaAPP)
               {iFPC,iFPM,iZAM,iPRS,iPRZ,iQGO,iDVZ,iSYN,iSPR : int;}


              {constructor Init(_cfg_STA,_kod_STA: string);}


               procedure   read_cfg(_cfg_STA: string); virtual;
               procedure   inicializacia_modulov; virtual;


              { spracovanie
              }
               procedure   uzatvor_statistiku_za_den    (date: TDate); virtual;
               procedure   uzatvor_statistiku_za_mesiac (date: TDate); virtual;


              { vytvorenie textovej tabulky statistiky
              }
               procedure   vytvor_tabulku_statistiku_za_ (date: TDate; externy: bool;
                                                          spolocny_subor: string; datove_subory: PPChars
                                                         ); virtual;

               function    vytvor_externu_tabulku (fn: string): string;


              { formatovanie vystupnych zostav
              }
               procedure   zapis_odstavec (var f: text; key: string; zaciatok: bool);
               procedure   zapis_riadok   (var f: text; riadok: string; nl: bool);
               procedure   zapis_udaje    (var f: text; zac,udaj,kon: string; sirka: byte; fill: char; nl: bool);
               procedure   zapis_hlavicku_pracoviska
                                          (var f: text; date: TDate;
                                           cfg_pracovisko,cfg_nazov,adr: string;
                                           sirka: int
                                          );

               procedure   statistika_LSRLP      (var f: text; date: TDate; let: int);
               procedure   statistika_letov      (var f: text; date: TDate; let: int);
               procedure   statistika_priestorov (var f: text; date: TDate; let: int);

               {$IFDEF MACC}
                procedure  statistika_letov_letisk  (var f: text; date: TDate);
                procedure  statistika_letov_sumarna (var f: text; date: TDate);
                procedure  statistika_SRLP (var f: text; date: TDate);
               {$ENDIF}


              { zobrazenie textovej tabulky statistiky
              }
               procedure   zobraz_subor_statistiky_ (fn,title: string; den,uzatvorena: bool); virtual;
             end;

