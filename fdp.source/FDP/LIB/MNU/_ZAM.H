      const ctrlZAM = '   Ctrl+F6 ';

      {$IFDEF SLOVAK}
        const  mnu_ZAM_PLAN  = ' PLèN ~Z~AMESTNANIA LETISKA... ';

               ZAMPLAN        = ' PODANIE ~P~LèNU ZAMESTNANIA  F6 ';
               ZAMCHG         = ' OPRAVA/~A~KTUALIZèCIA ';
               ZAMCNL         = ' ~Z~RUõENIE ';
               ZAMDEP         = ' ZA~Ä~ATIE ZAMESTNANIA ';
               ZAMBRK         = ' PRER~U~õENIE ';
               ZAMCNT         = ' PO~K~RAÄOVANIE ';
               ZAMARR         = ' UK~O~NÄENIE ';
               ZAMAKT         = ' AKTUALIZèCIA POÄTU ~L~ETOV ';

               (*{$IFDEF VLASTNE_PLANY}
                ZAM_PLAN_LET  = tit_VLASTNE+PLANY_+' Ctrl+F6 ';
                ZAM_PLAN_ALL  = tit_VSETKY +PLANY_;
               {$ELSE}
                ZAM_PLAN      = ' PLèNY ZAMESTNANã LETãSK  Ctrl+F6 ';
               {$ENDIF}*)
               ZAM_ACT        = ' PREBIEHAJóCE ZAMESTNANIA';
               ZAM_ARR        = ' UKONÄENê ZAMESTNANIA';
               ZAM_ALL        = PLA_ALL;


               ZAMM           = ' PLèNY ~Z~AMESTNANã LETãSK ';
               ZAMREP         = 'HLèSENIE O PRIEBEHU ZAMESTNANã LETãSK ';
               ZAMVAR         = 'UPOZORNENIE NA HLèSENIE -//- ';
               ZAMPRE         = 'PREAKTIVOVANIE PLèNOV ZAMESTNANã';
               ZAMDEL         = 'DEAKTIVOVANIE NEUKONÄENùCH ZAMESTNANã';

               ZAMSTRIP       = '(PRE)AKTIVOVANê PLèNY AKO STRIPY';
      {$ENDIF}


      {$IFDEF CZECH}
       const   ZAMM           = ' PLèNY ~Z~AMâSTNANã LETIõÜ ';
               ZAMREP         = 'HLèõENã O PR¶BâHU ZAMâSTNèNã LETIõÜ ';
               ZAMPRE         = 'PûEAKTIVOVèNã PLèN¶ ZAMâSTNèNã';
               ZAMDEL         = 'DEAKTIVOVèNã NEUKONÄENùCH ZAMâSTNèNã';
      {$ENDIF}