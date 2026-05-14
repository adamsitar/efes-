     const  err_MAP_NOT_FOUND      = 50;
            err_MAP_FPL_NOT_FOUND  = 51;


     const  {$IFDEF SLOVAK}
              UNKN_AP           = 'Nezn†me letisko.';
              UNKN_OB           = 'Nezn†my bod na trati.';
              UNKN_LDM          = 'Nezn†my ®tvorec.';
              BAD_LDM           = 'Zle k¢dovanò ®tvorec.';
              UNKM_MES          = 'Message is not complete.';
              ANTHR_ICAO_NXIT   = 'There are another message array (beginnig by "-").';
              MISS_ICAO_NXIT    = 'There are missing arrays in message.';
            {$ENDIF}
            {$IFDEF CZECH}
              UNKN_AP           = 'Nezn†mÇ leti®tà.';
              UNKN_OB           = 'Nezn†mò bod na trati.';
              UNKN_LDM          = 'Nezn†mò átverec.';
              BAD_LDM           = 'õpatnà k¢dovanò átverec.';
              UNKM_MES          = 'Zpr†va nen° kompletn°.';
              ANTHR_ICAO_NXIT   = 'Ve zpr†và je dal®° pole (zaá°n† se "-").';
              MISS_ICAO_NXIT    = 'Ve zpr†và chyb° pole.';
            {$ENDIF}
            {$IFDEF ENGLISH}
              UNKN_AP           = 'Unknown aiport.';
              UNKN_OB           = 'Unknown point of route.';
              UNKN_LDM          = 'Unknown square.';
              BAD_LDM           = 'Error in square code.';
              UNKM_MES          = 'Message is not complete.';
              ANTHR_ICAO_NXIT   = 'There are another message array ("-").';
              MISS_ICAO_NXIT    = 'There are missing arrays in message ("-").';
            {$ENDIF}


            {$IFDEF SLOVAK}
             inf_plan          = 'Pl†n';
             inf_vzor          = 'Vzor';
             inf_na_den        = 'na de§';
             inf_exist         = 'uë existuje.';

             ask_rozoslat      = 'a rozoslaü spr†vu o tom';

             tit_zmeneny_plan     = 'Pl†n bol medziáasom spracovanò.';
             tit_dekoduje_plan    = 'Pl†n je dek¢dovanò.';
             tit_dekodovany_plan_ = 'Dek¢dovanò pl†n ';

            {$ENDIF}

            {$IFDEF CZECH}
             inf_plan          = 'Pl†n';
             inf_vzor          = 'Vzor';
             inf_na_den        = 'na den';
             inf_exist         = 'jië existuje.';

             ask_rozoslat      = 'a rozeslat zpr†vu o tom';

             tit_zmeneny_plan     = 'Pl†n byl medziáasem spracov†n.';
             tit_dekoduje_plan    = 'Pl†n je dek¢dovan.';
             tit_dekodovany_plan_ = 'Dek¢dovan pl†n ';
            {$ENDIF}

            {$IFDEF ENGLISH}
             inf_plan          = 'The plan';
             inf_vzor          = 'The sample';
             inf_na_den        = 'on day';
             inf_exist         = 'exists already.';

             ask_rozoslat      = 'and distribute message about';

             tit_zmeneny_plan     = 'Plan has been aready processed.';
             tit_dekoduje_plan    = 'Plan is been decoded.';
             tit_dekodovany_plan_ = 'Decoded plan of ';
            {$ENDIF}


            {tit_FPL           = 'FLIGHT PLAN';
            tit_STRIP         = ' ~S~TRIP    ';
            tit_DATA          = ' DA~T~A     ';
            tit_DECODE        = ' DA~T~A     ';}

            {$IFDEF SLOVAK}
              tit_PLAN_         = ' ~P~LèN ';
              tit_CHG_          = ' ~O~PRAVA ';
              tit_CNL_          = ' ~Z~RUõENIE ';
              tit_DEP_          = ' ZA~Ä~ATIE ';
              tit_BRK_          = ' PR~E~RUõENIE ';
              tit_CNT_          = ' PO~K~RAÄOVANIE ';
              tit_ARR_          = ' UK~O~NÄENIE ';

              tit_ACC_          = ' ~S~CHVèLENIE ';
              tit_DEC_          = ' ~Z~AMIETNUTIE ';

              tit_SEND          = ' PO~õ~LI ';
              tit_COPY          = ' ~K~ïPIA PLèNU ';
              tit_PRINT         = ' T~L~AÄ ';
              tit_TYPE          = ' T~Y~P  ';

              tit_LAM           = ' ~L~AM ';
              tit_DATA          = ' DèTA~.~ ';
              tit_VIEW          = ' ~P~LèN ';
              tit_VIEW2         = ' ~Z~OBRAZ ';
              tit_STRIP         = ' ~S~TRIP ';
              tit_DRAW          = ' ~T~RAÜ ';
              tit_TRACK         = ' RDP~.~';

              tit_PLAN_RPL      = 'VZORY PLèNOV';

              tit_Letisko       = 'Letisko';
              tit_KONIEC        = 'Ukonáenie o';

              tit_MNU_INIT      = 'Inicializ†cia poloëiek menu...';
              tit_SYM_UPD       = 'Aktualiz†cia symbolov...';
            {$ENDIF}

            {$IFDEF CZECH}
              tit_PLAN_         = ' ~P~LèN ';
              tit_CHG_          = ' ~O~PRAVA ';
              tit_CNL_          = ' ~Z~RUõENã ';
              tit_DEP_          = ' ZA~Ä~ATEK ';
              tit_BRK_          = ' PR~E~RUõENã ';
              tit_CNT_          = ' PO~K~RAÄOVèNã ';
              tit_ARR_          = ' UK~O~NÄENã ';

              tit_ACC_          = ' ~S~CHVèLENã ';
              tit_DEC_          = ' ~Z~AMãTNUTã ';

              tit_SEND          = ' ODE~õ~LI ';
              tit_COPY          = ' ~K~OPIE PLèNU ';
              tit_PRINT         = ' T~I~SK   ';
              tit_TYPE          = ' T~Y~P  ';

              tit_LAM           = ' ~L~AM ';
              tit_DATA          = ' DATA~.~ ';
              tit_VIEW          = ' ~P~LèN ';
              tit_VIEW2         = ' ~Z~OBRAZ ';
              tit_STRIP         = ' ~S~TRIP ';
              tit_DRAW          = ' T~R~AÜ ';
              tit_TRACK         = ' RDP~.~ ';

              tit_PLAN_RPL      = 'VZORY PLèN¶';

              tit_Letisko       = 'Leti®tà';
              tit_KONIEC        = 'Ukonáen° v';

              tit_MNU_INIT      = 'Inicializace poloëek menu...';
              tit_SYM_UPD       = 'Aktualizace symbolñ...';
            {$ENDIF}

            {$IFDEF ENGLISH}
              tit_PLAN_         = ' ~P~LAN ';
              tit_CHG_          = ' ~C~HANGE ';
              tit_CNL_          = ' CA~N~CEL ';
              tit_DEP_          = ' B~E~GINNING ';
              tit_BRK_          = ' INTER~R~UPTION ';
              tit_CNT_          = ' C~O~NTINUE ';
              tit_ARR_          = ' ~E~ND ';

              tit_ACC_          = ' ~A~CCEPT ';
              tit_DEC_          = ' ~D~ECLINE ';

              tit_SEND          = ' ~S~END  ';
              tit_COPY          = ' COP~Y~ OF PLAN ';
              tit_PRINT         = ' P~R~INT ';
              tit_TYPE          = ' T~Y~PE  ';

              tit_LAM           = ' ~L~AM ';
              tit_DATA          = ' DATA~.~ ';
              tit_VIEW          = ' ~P~LAN ';
              tit_VIEW2         = ' ~V~IEW ';
              tit_STRIP         = ' ~S~TRIP ';
              tit_DRAW          = ' RO~U~TE ';
              tit_TRACK         = ' ~T~RACK ';

              tit_PLAN_RPL      = 'REPETITIVE PLANS';

              tit_Letisko       = 'Airport/Airbase';
              tit_KONIEC        = 'Finished at';

              tit_MNU_INIT      = 'Inicializing menu items...';
              tit_SYM_UPD       = 'Updating of symbols...';
            {$ENDIF}


            {$IFDEF SLOVAK}
              tit_decoded_FPL4  = 'Decoded FPL of ';
              tit_activate_FPL4 = 'Flight to activate ';

              tit_dayPLAN       = 'Pl†n na de§';

              tit_regRTE        = '~T~rate LPS';       hk_regRTE = kbAltT;
              tit_insNDB        = '~V~loë bod';        hk_insNDB = kbAltV;
              tit_delNDB        = 'Zm~a~ë bod';        hk_delNDB = kbAltA;
            {$ENDIF}

            {$IFDEF CZECH}
              tit_decoded_FPL4  = 'Decoded FPL of ';
              tit_activate_FPL4 = 'Flight to activate ';

              tit_dayPLAN       = 'Pl†n na den';

              tit_regRTE        = '~T~ratà LPS';       hk_regRTE = kbAltT;
              tit_insNDB        = '~V~loë bod';        hk_insNDB = kbAltV;
              tit_delNDB        = '~S~maë bod';        hk_delNDB = kbAltS;
            {$ENDIF}

            {$IFDEF ENGLISH}
              tit_decoded_FPL4  = 'Decoded FPL of ';
              tit_activate_FPL4 = 'Flight to activate ';

              tit_dayPLAN       = 'Plan for day';

              tit_regRTE        = '~R~egular routes';  hk_regRTE = kbAltR;
              tit_insNDB        = '~I~nsert point';    hk_insNDB = kbAltI;
              tit_delNDB        = '~D~elete point';    hk_delNDB = kbAltD;
            {$ENDIF}


            {$IFDEF SLOVAK}
               tit_PLANvzor     = 'Pouë°vanÇ pl†ny alebo vzory';
               tit_FPLvzor      = 'Pouë°vanÇ FPL alebo ich vzory';

               tit_ETA          = 'Uráenie áasu prist†tia (ETA)';
               ask_ETA          = 'Prepoá°taü áas prist†tia podåa ròchlosti a profilu trate ?';
               tit_TERMINATE    = 'Ukonáenie o';
            {$ENDIF}

            {$IFDEF CZECH}
               tit_PLANvzor     = 'Pouë°vanÇ pl†ny nebo jejich vzory';
               tit_FPLvzor      = 'Pouë°vanÇ FPL nebo jejich vzory';

               tit_ETA          = 'Uráen° áasu p©ist†n° (ETA)';
               ask_ETA          = 'P©epoá°st áas p©ist†n° podle rychlosti a profilu tratà ?';
               tit_TERMINATE    = 'Ukonáen° v';
            {$ENDIF}

            {$IFDEF ENGLISH}
               tit_PLANvzor     = 'Used plans';
               tit_FPLvzor      = 'Used FPLs';

               tit_ETA          = 'ETA';
               ask_ETA          = 'Estimate arrival time according to speed and route profile ?';
               tit_TERMINATE    = 'Termination on';
            {$ENDIF}



            {$IFDEF SLOVAK}
              tit_SEND_TO_MACC  = 'Poslat pl†n na StrRLP ?';
              tit_CLOSE_ARCHIVE = 'Äak†m na uzatvorenie archivaánÇho s£bora.';
              tit_WAIT_READ     = 'Poákajte, pros°m, naá°tavam pl†ny.';
              ask_CORRECT_IDN   = 'Spr†vna identifik†cia ?';
              tit_EXCEPTION     = 'Je to inò pr°pad ?';

              tit_ESTIMATED_ARR = 'Prist†tie vypoá°tanÇ na ';
              ask_REALIZED_PLAN = 'Realizovanò pl†n ?';
              ask_NEW_MESSAGE   = 'Proceed as a new message ?';
            {$ENDIF}

            {$IFDEF CZECH}
              tit_SEND_TO_MACC  = 'Poslat pl†n na MACC ?';
              tit_CLOSE_ARCHIVE = 'Äek†m na uzav©en° archivaán°ho souboru.';
              tit_WAIT_READ     = 'Poákejte, pros°m, átu data.';
              ask_CORRECT_IDN   = 'Spr†vn† identifikace ?';
              tit_EXCEPTION     = 'Je to jinò p©°pad ?';

              tit_ESTIMATED_ARR = 'P©ist†t° vypoáteno na ';
              ask_REALIZED_PLAN = 'Realizovanò pl†n ?';
              ask_NEW_MESSAGE   = 'Proceed as a new message ?';
            {$ENDIF}

            {$IFDEF ENGLISH}
              tit_SEND_TO_MACC  = 'Is FPL to be sent to the MACC ?';
              tit_CLOSE_ARCHIVE = 'Waiting to close archive file.';
              tit_WAIT_READ     = 'Wait please for reading data.';
              ask_CORRECT_IDN   = 'Correct call sign ?';
              tit_EXCEPTION     = 'Another case ?';

              tit_ESTIMATED_ARR = 'Arrival estimated on ';
              ask_REALIZED_PLAN = 'Realized plan ?';
              ask_NEW_MESSAGE   = 'Proceed as a new message ?';
            {$ENDIF}


            {$IFDEF SLOVAK}
              err_UNREG_PRG     = 'Program nebude korektne fungovat !';
              err_UNKNOWN_AREA  = 'Nezn†my priestor.';
              err_UNKNOWN_XY    = 'Nezn†me s£radnice.';

              err_ERR_CODE      = 'Chyba pri k¢dovan°.';
            {$ENDIF}

            {$IFDEF CZECH}
              err_UNREG_PRG     = 'Program nemus° pracovat korektnà.';
              err_UNKNOWN_AREA  = 'Nezn†mò prostor.';
              err_UNKNOWN_XY    = 'Nezn†mÇ sou©adnice.';

              err_ERR_CODE      = 'Chyba p©i k¢dov†n°.';
            {$ENDIF}

            {$IFDEF ENGLISH}
              err_UNREG_PRG     = 'Program won''t work properly !';
              err_UNKNOWN_AREA  = 'Unknown area.';
              err_UNKNOWN_XY    = 'Unknown coordinates.';

              err_ERR_CODE      = 'Code error.';
            {$ENDIF}
