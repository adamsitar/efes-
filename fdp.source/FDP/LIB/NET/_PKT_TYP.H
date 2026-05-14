    { Nove kodovanie pokryva intervaly okrem
      povodneho kodovania

        -  100 - 1500      spravy LPS
        - 2100 - 2200      spravy AFTN
        - 9000 -           diagnostika
        - 9900 - 9999      spravy MET
        - >50000           spravy pre RDP

      nove kodovanie :

        - 0-099, 10000-14999   diagnosticke spravy
        - 15000 - 19999        spravy pre riadenie (maily, komunikacia s RDP, hand-overy)
        - 20000 - 24999        spravy LPS (spracovane plany)
        - 25000 - 29999        -
        - 30000 - 34999        spravy vstupnych externych datovych prudov
        - 35000 - 39999        - (navrhovane spravy NOTAMOV)
        - 40000 - 44999        spravy MET
        - 45000 - 49999        -
        - 50000 - 54999        -
        - 55000 - 59999        spravy SIM
        - 60000 - 65535        -

    }


    const   kod_lo = 0;
            kod_hi = high(word);


            {kod_FDP_lo = 0;
            kod_FDP_hi = 9999;}


    { -----------------------------------------
      0-099, 10000-14999 - diagnosticke spravy
      -----------------------------------------
    }

    const   spr_CAS       = 2;         { casova synchronizacia }
            ack_CAS       = 3;

            spr_CALL      = 4;         { vyzva klienta      }
            ack_CALL      = 5;

            spr_ON        = 6;         { klient sa zapol    }
            ack_ON        = 7;

            spr_OFF       = 8;         { -//- sa vypol      }
            ack_OFF       = 9;

            spr_HEARTBEAT = 10;        { vyzva/oznamenie o funkcnosti }
            ack_HEARTBEAT = 11;


            spr_CONFIG    = 40;        { synchronizacia hlavnych parametrov
                                         spracovania medzi stanicami
                                         v sektore
                                       }
            spr_PASSWORD  = 49;


            spr_ERROR     = 50;        { odoslanie spravy o nestandartnom stave na urcene pracovisko }
                                       { 1.-7.bit - zavaznost chyby 0-127, pricom 127 je najvacsia   }
              mask_ERROR_DIALOG = 128; { 8.       - indikacia zobrazenia dialogoveho okna }
              level_SYSTEM      = 0;
              level_DATA        = 40;
              level_USER        = 80;


            spr_NOLAM     = 60;        { sprava o nepotvrdeni spravy }


            spr_DIAG_BGU  = 9000;      { docasne - specializovana sprava pre UKBB }


     { <100..10000> pokryva povodny interval sprav
     }

            spr_INITIALIZE   = 90;
             ack_INITIALIZE  = 91;

            spr_INITIALIZED  = 92;
             ack_INITIALIZED = 93;

            spr_INIT_FAILED  = 94;
             ack_INIT_FAILED = 95;


      const  spr__FDA_NODES        = 1000;
             spr__FDA_NODES_STATUS = 1002;
             spr__FDA_NODE_MESSAGE = 1004;
             spr__FDA_NODE_TIMEOUT = 1006;



    { ------------------------------------------
      10100 - 10999        spravy systemu meteor - stareho
      ------------------------------------------
    }


    { ------------------------------------------
      15000 - 19999        spravy pre riadenie
      ------------------------------------------
    }
     const
           spr_MESlo      = 15000;
           spr_MEShi      = 15999;


           spr_DATAlo_    = 16000;
           {$IFDEF DATA_BIN} spr_DATAlo   = 100;
           {$ELSE}           spr_DATAlo   = spr_DATAlo_;
           {$ENDIF}
           {spr_DATAhi     = 49999;}


           spr_NUDZA      = 98;
           ack_NUDZA      = 99;


           { maily
           }
            spr_SPR       = 15050;
            ack_SPR       = spr_SPR+1;

            {spr_TLG       = 15052;
            ack_TLG       = spr_TLG+1;}

            spr_SPR_LAM   = 15054;
            {spr_PRECITANE = spr_PRECITANE+1;}


          { komunikacia so supervisorom,
            s RDP,
            hand-overy
          }
            spr_SAY       = 15500;            { textova sprava od programu }

            spr_SECTOR    = 16000;


          { spr_ACCEPT    = 17000;
            ack_ACCEPT    = spr_ACCEPT+1;

            spr_UNACCEPT  = 17002;
            ack_UNACCEPT  = spr_UNACCEPT + 1;

            spr_HANDOVER  = 17004;
            ack_HANDOVER  = spr_HANDOVER + 1;

            spr_UNHANDOVER = 17006;
            ack_UNHANDOVER = spr_UNHANDOVER + 1;

            spr_CNL_STRIP = 19900;
          }


   { ----------------------------------------------------
     20000 - 24999         spravy LPS (spracovane plany)
     ----------------------------------------------------
   }

    const  { Spravy FPL
           }
            spri_FPL_lo    = 22000;
            spri_FPL_hi    = 23999;

            spr_RPL        = 22000;
            ack_RPL        = spr_RPL + 1;

            spr_FPL4       = 22100;
            ack_FPL4       = 22101;

             spr_FPL4_REQ  = 22150;
             spr_FPL4_DATA = 22152;
             spr_FPL4_MES  = 22154;

            spr_PLN        = 22200;
            ack_PLN        = 22201;


            spr_FPLC       = 22700;
            ack_FPLC       = spr_FPLC + 1;

            spr_FPLM       = 22800;
            ack_FPLM       = spr_FPLM + 1;


           { Spravy FPL ku RDP
           }
            spr_ACCEPT     = 22900 {spr0_RDP_A};
            ack_ACCEPT     = spr_ACCEPT+1;

            spr_UNACCEPT   = 22902 {spr0_RDP_UA};
            ack_UNACCEPT   = spr_UNACCEPT + 1;

            spr_HANDOVER   = 22910 {spr0_RDP_H};
            ack_HANDOVER   = spr_HANDOVER + 1;

            spr_UNHANDOVER = 22912 {spr0_RDP_UH};
            ack_UNHANDOVER = spr_UNHANDOVER + 1;

            spr_SSR_ERR    = 22950;
            spr_SSR_COR    = 22958;

            spr_EST_CNL    = 22990 ;
            ack_EST_CNL    = spr_EST_CNL + 1;



           { Vyuzitie vzdusneho priestoru
           }
            spri_ACT_lo   = 24000;
            spri_ACT_hi   = 24999;

            spri_ASM_lo   = 25000;
            spri_ASM_hi   = 29999;

            spr_PRZ       = 25010;             { ziadost o pridelenie vzdusneho priestoru }
            ack_PRZ       = spr_PRZ + 1;

            spr_PRN       = 25030;             { NOTAM o prideleni vzdusneho priestoru }
            ack_PRN       = spr_PRN + 1;

            spr_PRN_VLIS  = 25050;             { nariadnie o prideleni vzdusneho priestoru od VLIS }
            ack_PRN_VLIS  = spr_PRN_VLIS + 1;

            spr_AUP       = 25070;             { sprava UAP }
            ack_AUP       = spr_AUP + 1;

            spr_UUP       = 25072;             { sprava UAP }
            ack_UUP       = spr_UUP + 1;

            spr_PRS       = 25100;             { plan vyuzitia vzdusneho priestoru }
            ack_PRS       = spr_PRS + 1;
            spr_PRS_CNL   = 25190;             {spr0_RDP_PRS_DEL;}



           { Aktivita letisk
           }

            spr_QGO       = 24100;             { schopnosti/obmedzenie letiskovych prostriedkov }
            ack_QGO       = spr_QGO + 1;
            spr_RTZ       = 24110;             { schopnosti/obmedzenie letiskovych prostriedkov }
            ack_RTZ       = spr_RTZ + 1;

            spr_ZAM       = 25200;             { sprava o letiskovom zamestnani }
            ack_ZAM       = spr_ZAM + 1;
            spr_ZAM_CNL   = 25290;

            spr_DVZ       = 24200;             { ziadosti/spracovanie diverzii }
            ack_DVZ       = spr_DVZ + 1;



   { ----------------------------------------------------------------
     30000 - 34999        spravy vstupnych externych datovych prudov
     ----------------------------------------------------------------
   }
     const  spr_AFTN_SEND      = 33000;
            spr_AFTN_NEW       = 33002;
            spr_AFTN_PRD       = 33004;
            spr_AFTN_ED        = 33006;
            spr_AFTN_DEL       = 33008;

            spr_AFTN_ERR       = 33020;
            spr_AFTN_ERR_ED    = 33022;
            spr_AFTN_ERR_DEL   = 33024;

            spr_AFTN_TLG       = 33030;
            spr_AFTN_PLN       = 33032;

            spr_AFTN_DEL_ITEM  = 33050;
            spr_AFTN_DEL_ITEMS = 33052;


     const  spr_ASOC           = 34000;


   { ----------------------------------------------------
     40000 - 44999        spravy MET
     ----------------------------------------------------
   }
     const  spr_SYNOP     = 40100;
            ack_SYNOP     = spr_SYNOP + 1;

            spr_METAR     = 40110;
            ack_METAR     = spr_METAR + 1;

            spr_MRL       = 40112;
            ack_MRL       = spr_MRL + 1;


   { ----------------------------------------------------
     55000 - 59999        spravy SIM
     ----------------------------------------------------
   }
     const  spr_SIMlo     = 50000;
            spr_SIM       = 59999;


   { ----------------------------------------------------
     60000 -              najnizsia priorita
     ----------------------------------------------------
   }
     const  spr_PRN_NET     = 60100;
            spr_PRN_NET_RES = 60102;

