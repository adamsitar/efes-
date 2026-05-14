          {
          ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
          Û                                                Û
          Û  GUI                                           Û
          ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
          }

          {
           ÜÜÜÜÜÜÜÜÜÜ
           Û        Û
           Û  MAPA  Û
           ÛÜÜÜÜÜÜÜÜÛ
          }
    const   cmMAPA_INIT             = 50000;     { prekreslit mapu }
            cmMAPA_ROZSAH           = 50010;
            cmMAPA_CENTRUJ          = 50020;
            cmMAPA_STRED            = 50030;     { povel z menu                }
            cmMAPA_VYSTRED          = 50031;     { interny povel v objekte map }
            cmMAPA_PRIESTOR         = 50032;

            cmMAPA_FONT             = 50033;
            cmMAPA_HISTORY          = 50034;

            cmMAPA_PREKRESLI        = 50040;

            cmNSMxxx                = 50100;     { zaciatok  }
            cmNSMmax                = 50109;     { koniec -1 }
            cmNSMtop: word          = cmNSMxxx;  { ukazovatel }

            cmNSMdx = cmNSMmax-cmNSMxxx + 1; { posun cmXXXX pre potvrdenie zmien v SYM }


            cm_mapa_scroll          = 50900;


          {
           ÜÜÜÜÜÜÜÜÜÜ
           Û        Û
           Û  EDIT  Û
           ÛÜÜÜÜÜÜÜÜÛ
          }

            cmODOSLI_PLAN           = 51000;
            cmULOZ_PLAN             = 51001;
            cmULOZ_RPL              = 51002;

            cmVLOZ_VZOR             = 51003;
            cmULOZ_VZOR             = 51004;


            cm_OB                   = 51010;
            cm_NDB                  = 51011;
            cm_ATS                  = 51013;
            cm_RTE                  = 51014;

            cm_SSR                  = 51019;
            cm_ACTIVITY             = 51020;
            cm_RMK                  = 51021;
            cm_ABC                  = 51022;

            cm_DECODE_TRAT          = 51023;
            cm_KRESLI_TRAT          = 51024;
            cm_REGULAR_TRATE        = 51025;

            cmVLOZ_BOD              = 51050;
            cmVLOZ_TRAT             = 51051;
            cmVLOZ_TRAT_NAOPAK      = 51052;


          {
           ÜÜÜÜÜÜÜÜÜÜ
           Û        Û
           Û  AIP   Û
           ÛÜÜÜÜÜÜÜÜÛ
          }

            cm_xDATA            = 52000;

            cmPREHLAD_SLNKO     = 52001;
            cmSLNKO_NA_DEN      = 52002;

            cmPREHLAD_TYPY_ICAO = 52011;
            cmPREHLAD_TYPY_ZZZZ = 52012;
            cmPREHLAD_TYPY_TSGA = 52013;
            cmPREHLAD_TYPY_MIL  = 52014;
            cmPREHLAD_TYP_DATA  = 52015;

            cmPREHLAD_POUZ      = 52021;
            cmPREHLAD_POUZM     = 52023;
            cmPREHLAD_ULOHYM    = 52024;

            cmPREHLAD_RTE       = 52031;
            cmPREHLAD_RTES      = 52032;
            cmPREHLAD_RTEM      = 52035;
            cmPREHLAD_NDB       = 52041;
            cmPREHLAD_OB        = 52042;

            cmPREHLAD_DAIPORTS  = 52051;
            cmPREHLAD_FAIPORTS  = 52052;

            cmPREHLAD_TSA       = 52061;
            cmPREHLAD_R         = 52062;

            cmPREHLAD_ABC       = 52080;
            cmPREHLAD_ABC_      = 52081;

            cmPREHLAD_FL        = 52090;

            {cmPREHLAD_INTERFACE = 52099;}



          {
           ÜÜÜÜÜÜÜÜÜ
           Û       Û
           Û  OPL  Û
           ÛÜÜÜÜÜÜÜÛ
          }

            cm_mFPL_scroll    = 53001;
            cm_cFPL_scroll    = 53002;
            cm_oFPL_scroll    = 53003;
            cmZOZNAM_FPL      = 53004;



          {
           ÜÜÜÜÜÜÜÜÜ
           Û       Û
           Û  EDD  Û
           ÛÜÜÜÜÜÜÜÛ
          }

            cmEDD_STRIP       = 53110;
            cmEDD_TABLET      = 53111;
            cmEDD_SECTOR      = 53112;

            cmEDD_SHORT_STRIP = 53113;
            cmEDD_MINI_STRIP  = 53114;
            cmEDD_FULL_STRIP  = 53115;


            cmPROP_SETT       = 53121;
            cmACC_SETT        = 53122;
            cmACC_PREM        = 53123;
            cmACC_NDB         = 53124;
            cmACC_ALT         = 53125;

            cmACC_DEFAULT     = 53200;
            cmACC_USER        = 53201;
            cmACC_DEFAULT_lo  = 53202;
            cmACC_DEFAULT_hi  = 53242;  {20101+ord('z')-ord('a')+1; -> nemam winmenu_s }

            cmEDD_STATUS      = 53145;  { vypise stav EDD: pocet planov, nastavnie EDD... }
            cmPRN_SETT        = 53146;

            cmPREHLAD_OTHER   = 53147;

            cmSEARCH_SSR      = 53150;
            cmSEARCH_SSR_     = 53151;
            cmSEARCH_CODE     = 53152;
            cmSEARCH_CODE_    = 53153;


          { --------------------------}
          { komunikacia v module ACC  }
          { --------------------------}

          { komunikacia Data->ACC : prikazy pre vypisovanie FPL }

            cm_add_PROP_PLAN  = 53500;
            cm_chg_PROP_PLAN  = 53501;
            cm_clr_PROP_PLAN  = 53502;
            cm_del_PROP_PLAN  = 53503;

            cm_add_ACC_PLAN   = 53505;
            cm_chg_ACC_PLAN   = 53506;
            cm_clr_ACC_PLAN   = 53507;
            cm_del_ACC_PLAN   = 53508;

          { a) Prepinanie medzi lstACC }

            cm_PROP_clicked  = 53520;
            hl_vyp_winPROP   = 53521;  { sprava pre GUI, ze PROP sa vypina => zapne ACC    }
            hl_zap_winPROP   = 53522;  { sprava pre GUI, ze PROP sa zapina => vypne ACC    }

            cm_NDB_slct      = 53533;  { prepnutie na skupinu            }
            cm_NDB_view      = 53534;  { zobrazenie obsahu celej skupiny }
            cm_NDB_move      = 53535;  { presun skupiny na iny stlpec    }
            cm_NDB_set       = 53536;  { presun skupiny na iny stlpec    }

          { b) Zmena velkosti a polohy lstACC }

            rq_lstACC_move   = 53550;  { ziadost pre winACC, ze lstACC chce byt presunuta  }
            rq_lstACC_zapni  = 53551;  { ziadost pre winACC, ze lstACC chce byt aktivovane }

            hl_vyp_winACC    = 53552;  { sprava pre GUI, ze ACC sa vypina => zapne PROP    }
            hl_zap_winACC    = 53553;  { sprava pre GUI, ze ACC sa zapina => vypne PROP    }

            rq_lstACC_zvacsi = 53554;  { ziadost od lstACC, ze ma malo miesta a potreboval by zvacsit }
            rq_lstACC_zmensi = 53555;  { ziadost od lstACC, ze by zahodno zmensit bolo                }


          { c) Spracovanie PROP planov }

            cm_PROP_ACC      = 53570;
            cm_PROP_DEC      = 53571;


          { STRIP
          }
            cmACK_PROP_PLANs = 53580;
            cmCNL_PROP_PLANs = 53581;
            cmCNL_ALL_PLANs  = 53582;
            cmCNL_ALL_PLANs_ = 53583;

