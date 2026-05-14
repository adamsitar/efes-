       const  {$IFDEF SLOVAK}
                {rep_schopnost     = 'Hl†senie o stave/schopnosti';}

                tit_diverzia       = 'Diverzia';
                tit_pre            = 'pre';
                tit_na             = 'drëan† na';
                tit_na_u           = 'drëan£ na';
                tit_dna            = 'd§a';
                tit_zac            = 'od';
                tit_kon            = 'do';
                tit_odoslana       = ', vyhl†sen† ';
                tit_vystraha       = ', vòstraha ';

                tit_diverzia_      = 'Diverzia drëan† na       d§a          od         do        , vyhl†sen†        .';

                tit_ziadost        = 'íiadosü';
                tit_odoslanie      = 'Odoslanie';
                tit_zabezpecenie   = {$IFNDEF SPEA}'Zabezpeáenie'{$ELSE}'Z†bezpeka'{$ENDIF};

                tit_dvz_ziadost    = 'Pl†n ëiadosti o diverziu';
                ask_DVZCNL         = 'Zru®iü ëiadost o diveziu';

                tit_dvz_kym        = 'diverzia drëan† kòm';
                tit_dvz_date       = 'd†tum platnosti';
                tit_dvz_od         = 'diverzia drëan† od';
                tit_dvz_do         = 'diverzia drëan† do';
                tit_dvz_vyh        = 'diverzia vyhl†sen† od';
                tit_dvz_poz        = 'poëiadavky na zabezpeáenie diverzie';
                tit_dvz_odo        = 'odoslanie na diverziu';
                tit_dvz_zab        = 'zabezpeáenie diverzie';

                tit_dvz_vyslanie   = 'íiadosü o vyslanie na diverziu od ';
                tit_dvz_schvalenie = 'íiadosü o schv†lenie diverzie pre ';

                tit_dvz_chg        = 'Aktualiz†cia ëiadosti o diverziu';
                tit_dvz_req        = 'Odoslanie ëiadosti o diverziu';
                tit_dvz_cnl        = 'Zru®enie diverzie';
                tit_dvz_end        = 'Ukonáenie diverzie';

                tit_dvz_acc        = 'Spracovanie ëiadosti o zabezpeáenie diverzie';
                tit_dvz_alr        = 'Vòstraha pred zru®en°m diverzie';
                tit_dvz_cln        = 'Zru®enie vòstrahy na diverziu';
                tit_dvz_act        = 'Odoslanie na diverziu';
                tit_dvz_acn        = 'Zru®enie diverzie po vòstrahe';


                rep_na             = ' na ';
                rep_pre            = ' pre ';
                rep_od             = ' od ';
                rep_ku             = ' ku ';

                rep_dvz_for        = ' drëanej pre ';
                rep_dvz_cnl        = 'bola zru®en†';

                rep_dvz_req_acc    = 'bola schv†len†';
                rep_dvz_req_dec    = 'bola zamietnut†';

                rep_dvz_chg        = 'Oprava pl†nu diverzie';
                rep_dvz_req        = 'Poëiadavka na diverziu';

                rep_dvz_pre        = 'Diverzia drëan† pre';
                rep_dvz_pre_act    = 'bola aktivovan†';
                rep_dvz_pre_end    = 'bola ukonáen†';

                rep_dvz_act        = 'Odoslanie na diverziu ku';
                rep_dvz_act_acc    = 'bolo ods£hlasenÇ';
                rep_dvz_act_dec    = 'nebolo povolenÇ';

                rep_dvz_alr        = 'Vòstraha pred zru®en°m diverzie drëanej';
                rep_dvz_cln        = 'Zru®enie vòstrahy na diverziu drëan£';
                rep_dvz_acn        = 'Zru®enie diverzie (po vòstrahe) drëanej';

                tit_dvz_prehlad    = 'Prehåad diverzi°';

                DVZPLAN            = ' PODANIE ~í~IADOSTI O DIVERZIU       F9 ';
                DVZCHG             = ' OPRAVA/~A~KTUALIZèCIA íIADOSTI ';
                DVZCNL             = ' ZRUõENIE íIADOS~T~I ';

                DVZREQ             = ' ODOSLANIE íIADOSTI ~O~ DIVERZIU ';
                DVZACT             = ' ODOSLANIE ~N~A DIVERZIU ';
                DVZEND             = ' UK~O~NÄENIE PLATNOSTI DIVERZIE';

                DVZACC             = ' ~S~PRACOVANIE íIADOSTI ';
                DVZALR             = ' V~ù~STRAHA PRED ZRUõENãM ';
                DVZCLN             = ' ZRUõENIE VùSTRA~H~Y ';
                DVZACN             = ' ~Z~RUõENIE DIVERZIE ';

              {$ENDIF}

              {$IFDEF ENGLISH}
              {$ENDIF}

              {$IFDEF SLOVAK}
               REQLocalMenu: PChar =
               ('~F1~ help    ~AltS~ s£hlas    ~AltZ~ zamietnutie     ~AltO~ oprava');

               REQ_DVZ_LocalMenu: PChar =
               ('~F1~ help    ~AltA~ povolenie    ~AltN~ zamietnutie    ~AltD~ odloëenie');
              {$ENDIF}

              {$IFDEF CZECH}
               REQLocalMenu: PChar =
               ('~F1~ help    ~AltS~ s£hlas    ~AltZ~ zamietnutie     ~AltO~ oprava');

               REQ_DVZ_LocalMenu: PChar =
               ('~F1~ help    ~AltA~ povolenie    ~AltN~ zam°tnut°    ~AltD~ odloëen°');
              {$ENDIF}

              {$IFDEF ENGLISH}
               REQLocalMenu: PChar =
               ('~F1~ help    ~AltS~ s£hlas    ~AltZ~ zamietnutie     ~AltO~ oprava');

               REQ_DVZ_LocalMenu: PChar =
               ('~F1~ help    ~AltA~ povolenie    ~AltN~ zam°tnut°    ~AltD~ odloëen°');
              {$ENDIF}
