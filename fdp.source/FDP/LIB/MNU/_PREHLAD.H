      {$IFDEF SLOVAK}

        const  PREHLADPLA_ = ' ~P~REHúAD SPRACOVèVANùCH PLèNOV ';
               PREHLADREQ_ = ' ~P~REHúAD SPRACOVèVANùCH íIADOSTã ';
               PLANY_      = 'PLèNY ';

               PLA_        = ' PODANê ';
               PLA_PLA     = ' PODANê PLèNY ';
               PLA_INE     = ' PLèNY PRE INê LSRLP ';
               PLA_SCH     = ' SCHVAúOVANê PLèNY ';
               PLA_ACT     = ' VYUíãVANê PLèNY ';
               PLA_ARR     = ' UKONÄENê PLèNY ';
               PLA_ALL     = ' VõETKY PLèNY DNES SPRACOVèVANê ';

               PLA_CPY     = ' ~K~ïPIA PLèNU ';


        const PLANY_NA_DEN  = {$IFDEF PPL} ' DENNê/PR~E~DBEíNê PLèNY/SPRèVY/NOTAMY... ';
                              {$ELSE}      ' PLèNY NA D~E~•...  ';
                              {$ENDIF}
               PLANY_NA_DEN_= ' PLèNY NA DE•...  ';

              PLANY_ARCHIV  = ' A~R~CHIVOVANê PLèNY/SPRèVY/NOTAMY... ';
               PLANY_ARCHIV_= 'ARCHãV PLèN¶/SPRèV...';


        const PrRPL      = ' ~R~PL      REPETITIVE PLANs ';

              PrPLN      = ' PL~N~      FLIGHT CLEARANCEs ';

              PrFPL4     = ' ~F~PL      ATS-ROUTE FLIGHTs ';
              PrFPL4D    = ' FPL/DA~Y~  DAY FLIGHT PLAN LIST ';


              PrFPLM     = ' ~V~OJENSKê a INê FPL ';

              PrKRL      = ' ~K~RãDLA... ';
               PrKRL_    = 'KRãDLA';

              PrZAM      = ' ~Z~AMESTNANIA LETãSK ';

              PrDVZ      = ' ~D~IVERZIE ';

              PrQGO      = ' ~S~TAV LETãSK ';
              PrRTZ      = ' ~S~TAV PROSTûEDK¶ LETIõÜ ';

              PrPRZ      = ' í~I~ADOSTI PRE VLIS ';
               PrPRZR    = ' NARIADENIA ~V~LIS ';
               PrPRN     = ' ~N~OTAMY VLIS ';

              PrPRS      = ' PLèNY ~P~RIESTOROV ';

              PrAUP      = ' NOTAMY ~A~UP ';
              PrUUP      = ' NOTAMY ~U~UP ';

              PrSYN      = ' SPRèVY ~M~ETEOR ';
              PrMRL      = ' METEOR ~R~ADAR';

              PrSPR      = ' SPRèV~Y~ ';



        const ArFPLc     = ' ~C~IVILNê LETY ';
               ArFPLc_   = ' ARCHãV ';
               ArFPLc24L = ' ZA POSLEDNùCH ~2~4 HODãN ';
               ArFPLc24M = ' STARõIE AKO 2~4~ HODãN ';

              ArFPLmo    = ' ~V~OJENSKê a INê LETY/FPL ';

             { ostatne tituly sa daju zopakovat }


        const AFPLc      = ' ~C~IVILNê LETY (PO TRATIACH LPS)                  Alt+F4 ';
              AFPLm      = ' ~V~OJENSKê LETY (MIMO TRATã LPS)                  Alt+F5 ';
              AFPLo      = ' ~I~Nê      LETY (MIMO TRATã LPS)                  Alt+F3 ';

              AZAM       = ' ~Z~AMESTNANIA LETãSK                              Alt+F6 ';
              ADVZ       = ' SCHVèLENê A DRíANê ~D~IVERZIE                     Alt+F9 ';
              AQGO       = ' ~S~TAV LETãSK A PROSTRIEDKOV                      Alt+F8 ';
              ARTZ       = ' STAV PR~O~STûEDK¶ LETIõÜ ';

              APRZR      = ' NARIADENIE ~V~LIS PRE VYUíITIE VZDUõNêHO PRIESTORU ';
              APRN       = ' ~N~OTAMY VLIS O VYUíITã VZDUõNêHO PRIESTORU';
              AAUP       = ' NOTAM ~A~UP - PLèN VYUíITIA VZDUõNêHO PRIESTORU ';
              AUUP       = ' NOTAM ~U~UP - DOPLNOK PLèNU VYUíITIA VZDUõNêHO PRIESTORU ';
              APRS       = ' VYUíãVANê ~P~RIESTORY                             Alt+F7 ';

              ASYN       = ' HODINOVê SPRèVY ~M~ETEOR                         Alt+F11 ';
              AMRL       = ' METEOR ~R~ADAR';

              ASPR       = ' DORUÄENê SPRèV~Y~                                Alt+F10 ';

      {$ENDIF}


      {$IFDEF CZECH}

        const  PREHLADPLA_ = ' ~P~ûEHLED ZPRACOVèVANùCH PLèN¶ ';
               PREHLADREQ_ = ' ~P~ûEHLED ZPRACOVèVANùCH íèDOSTã ';

               PLA_        = ' PODANê ';
               PLA_PLA     = ' PODANê PLèNY ';
               PLA_SCH     = ' SCHVALOVANê PLèNY ';
               PLA_ACT     = ' VYUíãVANê PLèNY ';
               PLA_ARR     = ' UKONÄENê PLèNY ';
               PLA_ALL     = ' VõECHNY PLèNY DNES SPRACOVèVANê ';
               PLA_INE     = ' PLèNY PRO JINê LSRLP ';

               PLA_CPY     = ' ~K~OPIE PLèNU ';


        const PLANY_NA_DEN = {$IFDEF PPL} ' DENNã/Pû~E~DBâíNê PLèNY/ZPRèVY/NOTAMY... ';
                             {$ELSE}      ' PLèNY NA D~E~N...  ';
                             {$ENDIF}
              PLANY_NA_DEN_= ' PLèNY NA DEN...  ';

              PLANY_ARCHIV = ' A~R~CHIVOVANê PLèNY/ZPRèVY/NOTAMY... ';
              PLANY_ARCHIV_= 'ARCHIV PLèN¶/ZPRèV...';



        const PrRPL      = ' ~R~PL      REPETITIVE PLANs ';

              PrPLN      = ' PL~N~      FLIGHT CLEARANCEs ';

              PrFPL4     = ' ~F~PL      ATS-ROUTE FLIGHTs ';
              PrFPL4D    = ' FPL/DA~Y~  DAY FLIGHT PLAN LIST ';


              PrFPLM     = ' ~V~OJENSKê a JINê FPL ';

              PrKRL      = ' ~K~ûãDLA... ';
               PrKRL_    = 'KûãDLA';

              PrZAM      = ' ~Z~AMâSTNèNã LETIõÜ ';

              PrDVZ      = ' ~D~IVERZE ';

              PrQGO      = ' ~S~TAV LETIõÜ ';
              PrRTZ      = ' STAV PR~O~STûEDK¶ LETIõÜ ';

              PrPRZ      = ' í~è~DOSTI PRO VLIS ';
               PrPRZR    = ' NAûãZENã ~V~LIS ';
               PrPRN     = ' ~N~OTAMY VLIS ';

              PrPRS      = ' PLèNY ~P~ROSTOR¶ ';

              PrAUP      = ' NOTAMY ~A~UP ';
              PrUUP      = ' NOTAMY ~U~UP ';

              PrSYN      = ' ZPRèVY ~M~ETEOR ';
              PrMRL      = ' METEOR ~R~ADAR';

              PrSPR      = ' ZPRèV~Y~ ';



        const ArFPLc     = ' ~C~IVILNã LETY ';
               ArFPLc_   = ' ARCHIV ';
               ArFPLc24L = ' ZA POSLEDNãCH ~2~4 HODIN ';
               ArFPLc24M = ' STARõã NEí 2~4~ HODIN ';

              ArFPLmo    = ' ~V~OJENSKê a JINê LETY/FPL ';

             { ostatne tituly sa daju zopakovat }


        const AFPLc      = ' ~C~IVILNã LETY (PO TRATãCH LPS)     Alt+F4 ';
              AFPLm      = ' ~V~OJENSKê LETY (MIMO TRATã LPS)    Alt+F5 ';
              AFPLo      = ' J~I~Nê     LETY (MIMO TRATã LPS)    Alt+F3 ';

              AZAM       = ' ~Z~AMESTNèNã LETãõÜ    Alt+F6 ';
              ADVZ       = ' ~D~IVERZE íèDANê A DRíENê MEZI LETIõTI   Alt+F9 ';
              AQGO       = ' ~S~TAV LETãõÜ A PROSTûEDK¶          Alt+F8 ';
              ARTZ       = ' STAV PR~O~STûEDK¶ LETIõÜ ';

              APRZR      = ' NAûãZENã ~V~LIS PRO VYUíITã VZDUõNãHO PROSTORU ';
              APRN       = ' ~N~OTAMY VLIS O VYUíITã VZDUõNãHO PROSTORU';
              AAUP       = ' NOTAM ~A~UP - PLèN VYUíITã VZDUõNãHO PROSTORU ';
              AUUP       = ' NOTAM ~U~UP - DOPLNEK PLèNU VYUíITã VZDUõNãHO PROSTORU   ';
              APRS       = ' VYUíãVANê ~P~ROSTORY                Alt+F7 ';

              ASYN       = ' HODINOVê ZPRèVY ~M~ETEOR            Alt+F11 ';
              AMRL       = ' METEOR ~R~ADAR';
              ASPR       = ' DORUÄENê ZPRèV~Y~                   Alt+F10 ';

      {$ENDIF}


      {$IFDEF ENGLISH}

        const PREHLADPLA_  = ' PROCESSED PLANS ~L~IST ';
              PREHLADREQ_  = ' PROCESSED REQUESTS ~L~IST ';

              PLA_         = ' FILLED ';
              PLA_PLA      = ' FILLED-IN PLANs ';
              PLA_SCH      = ' APPROVED PLANs ';
              PLA_ACT      = ' PLANs IN USE ';
              PLA_ARR      = ' REALISED PLANs ';
              PLA_ALL      = ' ALL PLANs PROCESSED ';
              {PLA_INE     = ' ~6.~ PLèNY PRE INê LSRLP ';}

              PLA_CPY      = ' PLAN ~C~OPY ';


        const PLANY_NA_DEN  = {$IFDEF PPL} ' C~U~RRENT/PRELIMINARY PLANs... ';
                              {$ELSE}      ' C~U~RRENT PLANS... ';
                              {$ENDIF}
               PLANY_NA_DEN_= ' CURRENT DATA...  ';

              PLANY_ARCHIV  = ' ~A~RCHIVED PLANs... ';
               PLANY_ARCHIV_= ' ARCHIVED PLANs...';


        const PrRPL      = ' ~R~PL      REPETITIVE PLANs ';

              PrPLN      = ' PL~N~      FLIGHT CLEARANCEs ';

              PrFPL4     = ' ~F~PL      ATS-ROUTE FLIGHTs ';
              PrFPL4D    = ' FPL/DA~Y~  DAY FLIGHT PLAN LIST ';


              PrFPLM     = ' ~M~ILITARY (OTHER) FPLs ';

              PrKRL      = ' ~K~RãDLA... ';
               PrKRL_    = 'KRãDLA';

              PrZAM      = ' ~Z~AMESTNANIA LETãSK ';

              PrDVZ      = ' ~D~IVERZIE ';

              PrQGO      = ' ~S~TAV LETãSK ';
              PrRTZ      = ' ~S~TAV PROSTûEDK¶ LETIõÜ ';

              PrPRZ      = ' í~I~ADOSTI PRE VLIS ';
               PrPRZR    = ' NARIADENIA ~V~LIS ';
               PrPRN     = ' ~N~OTAMY VLIS ';

              PrPRS      = ' ~A~REA PLANs ';

              PrAUP      = ' NOTAMY ~A~UP ';
              PrUUP      = ' NOTAMY ~U~UP ';

              PrSYN      = ' METEOR M~E~SSAGES';
              PrMRL      = ' METEOR ~R~ADAR';

              PrSPR      = ' LETVIS ~M~ESSAGES ';

              PrTLG      = ' TE~L~EGRAMMS ';



        const ArFPLc     = ' ~C~IVILIAN FLIGHTs ';
               ArFPLc_   = ' ARCHIV ';
               ArFPLc24L = ' RECENT ~2~4 HOURS ';
               ArFPLc24M = ' OLDER THAN 2~4~ HOURS ';

              ArFPLmo    = ' ~M~ILITARY (OTHER) FLIGHTs ';

             { ostatne tituly sa daju zopakovat }


        const AFPLc      = ' ~C~IVILIAN FLIGHTs   Alt+F4 ';
              AFPLm      = ' ~M~ILITARY FLIGHTs   Alt+F5 ';
              AFPLo      = ' ~O~THER FLIGHTs      Alt+F3 ';

              AZAM       = ' ~Z~AMESTNANIA LETãSK                              Alt+F6 ';
              ADVZ       = ' ~D~IVERZIE íIADANê A DRíANê MEDZI LETISKAMI       Alt+F9 ';
              AQGO       = ' ~S~TAV LETãSK A PROSTRIEDKOV                      Alt+F8 ';
              ARTZ       = ' STAV PR~O~STûEDK¶ LETIõÜ ';

              APRZR      = ' NARIADENIE ~V~LIS PRE VYUíITIE VZDUõNêHO PRIESTORU ';
              APRN       = ' ~N~OTAMY VLIS O VYUíITã VZDUõNêHO PRIESTORU';
              AAUP       = ' NOTAM ~A~UP - PLèN VYUíITIA VZDUõNêHO PRIESTORU ';
              AUUP       = ' NOTAM ~U~UP - DOPLNOK PLèNU VYUíITIA VZDUõNêHO PRIESTORU ';
              APRS       = ' ~A~REAs IN USE       Alt+F7 ';

              ASYN       = ' METEOR M~E~SSAGES                                Alt+F11 ';
              AMRL       = ' METEOR ~R~ADAR';

              ASPR       = ' LETVIS ~M~ESSAGES    Alt+F10 ';

      {$ENDIF}
