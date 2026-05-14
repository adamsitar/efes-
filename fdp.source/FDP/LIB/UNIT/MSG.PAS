(*-------------------------------------------------------------------*)
(* LETVIS FDP - texty                                                *)
(* (c) Ales Kosice 1995  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}


unit Msg;


interface


     uses   TypeDef,
            keyb;


     const  titA36     = '~Ä~ß°„™†';
            titLAT     = 'L~A~TIN';
            titLARGE   = '... ';
            titOK      = 'O~k~    ';

           {$IFDEF SLOVAK}
            titYES     = '~è~no   ';
            titNO      = '~N~ie   ';
            titCANCEL  = '~Z~ru®  ';
            titIGNORE  = '~I~gnoruj';
            titPOTVRD  = '~P~otvrÉ';
            titSPRACUJ = '~S~pracuj';

            titPREV    = '~<~ pred';
            titNEXT    = 'nasl ~>~';

            titDLA     = 'O~d~loë ';
            titACK     = 'S£~h~las';
            titCOR     = '~O~prava';
            titDCL     = '~Z~ru®  ';
            titDIS     = '~Z~amietni';
            titDEL     = 'Z~m~aë  ';

            titSEND    = '~P~o®li ';
            titSAVE    = '~U~loë  ';
            titEDIT    = '~O~prav ';

            titSAVErpl = '> V~Z~OR ';
            titSAVEas  = 'Uloë ako';
            titPRINT   = '~T~laá  ';
            titEXPORT  = 'E~x~port';
            titBACKUP  = '~Z~†~loha';
            titARCHIV  = 'A~r~ch°v';
            titZOBRAZ  = '~Z~obraz';
            titNAJDI   = '~N~†jdi ';
            titVSETKY  = '~V~®etky';

            titVZOR    = '~V~ZOR  ';
            titRPL     = '~R~PL   ';

            titSTATIS  = 'õta.~k~a';

            titBOD     = '~B~ody';
            titNDB     = '~N~DB/VOR';
            titRTEM    = '~T~rate';
            titABC     = 'Abe~c~eda';
            titACT     = 'Popi~s~';
            titTRAT    = 'Tr~a~ü';
            titREG     = 'Re~g~ular';

            {titTOOLS   = 'P~o~moc ';    hkTOOLS = kbAltO;}
            titVIEW    = 'PREHúAD';
            titVIEW_A  = 'ARCHãVOVANê óDAJE';

            msgABOUT   = 'O systÇme:';
            msgINFO    = 'Info...';
            msgERR     = 'Chyba...';
            msgMESS    = 'Oznam';
            msgWARNING = 'Varovanie';
            msgSORRY   = 'úutujem';
            msgWAITING = 'Äakajte, pros°m';
            msgVERIPHY = 'Overenie';
            msgACCEPT  = 'Potvrdenie';
            msgBCK     = 'Z†lohovanie';
            msgFSELECT = 'Vòber s£bora ';
            msgFINDING = 'Vyhåad†va sa...';
            msgCOPY    = 'Kop°rujem, aë sa pr†®i...';
            msgSEND    = 'Vysielanie';
            msgEXCEPT  = 'Poru®iü pravidlo ?';
            msgCORRECT = 'Opraviü ?';
            msgISCORRECT = 'Je spr†vny ?';
            msgCONTINUE  = 'Pokraáovaü';

            askAPPROVED  = 'Je schv†len† ?';
            ask_prepisat = 'Prep°saü ?';

            msgSYSINFO = ' SystÇmovÇ inform†cie: ';
            msgLAST    = ' Poslednò stav uzlov ';
            msgEXIT    = ' Ukonáenie programu ?! ';

            msgSEARCH  = 'Prehåadanie ';
            msgREAD    = 'Naá°tanie ';
            msgINIT    = 'Inicializ†cia ';

            msgFADTE   = ' z '{o d§a '};
            msgOD      = ' od ';

            msgDATA            = 'ódaje';
            msgMEMORY          = 'M†lo pamÑte pre ';
            msgNOT_FOUND       = 'nen†jdenÇ';
            msgNOT_PROCESSED   = 'was not processed';

            msgDATA_SAVED      = 'D†ta boli uloëenÇ.';
            msgDATA_SENDED     = 'D†ta boli odoslanÇ.';
            msgDATA_NOT_SENDED = 'D†ta neboli odoslanÇ.';
            msgDATA_CHANGED    = 'D†ta boli opravenÇ.';
            msgDATA_DELETED    = 'D†ta boli zru®enÇ.';
            msgDATA_NOT_FOUND  = 'D†ta ëiadanÇho typu neboli n†jdenÇ.';
            msgFILES_NOT_FOUND = 'S£bor nen†jdenò.';
            msgF_INVALID_FORMAT= 'S£bor neobsahuje £daje v oáak†vanom tvare.';
            msgARCH_EMPTY      = 'V arch°ve sa nenach†dzaj£ ëiadne s£bory';

            msgCONFIG_IGNORE   = 'In† verzia programu, skontrolujte konfigur†ciu, pros°m.';

            ask_PrintContinue  = 'Opakovaü tlaá ?';
            ask_CancelProc     = 'Zru®iü oper†ciu ?';
            msg_CancelProc     = 'Oper†cia zru®en†.';

            ask_CNL            = 'Naozaj zru®iü ';
            askNotActual       = 'Je pl†n podanò na nasleduj£ci de§ ?';

            ask_SUHLAS         = 'S£hlasite ?';

            tit_na             = 'na';
            tit_dna            = 'd§a';

            tit_hod            = 'hod';
            tit_min            = 'min';
            tit_sec            = 'sek';
           {$ENDIF}


           {$IFDEF CZECH}
            titYES     = '~A~no   ';
            titNO      = '~N~e    ';
            titIGNORE  = '~I~gnoruj';
            titCANCEL  = '~Z~ru®  ';
            titPOTVRD  = '~P~otvrÉ';
            titSPRACUJ = '~S~pracuj';

            titPREV    = '~<~ pred';
            titNEXT    = 'masl ~>~';

            titDLA     = 'O~d~loë ';
            titACK     = 'Sou~h~las';
            titCOR     = '~O~prava';
            titDCL     = 'Za~k~aë ';
            titDEL     = 'S~m~aë  ';

            titSEND    = '~P~o®li ';
            titSAVE    = '~U~loë  ';
            titEDIT    = '~O~prav ';

            titSAVErpl = '> V~Z~OR';
            titSAVEas  = 'Uloë jako';
            titPRINT   = '~T~isk  ';
            titEXPORT  = 'E~x~port';
            titBACKUP  = '~Z~†~loha';
            titARCHIV  = 'A~r~chiv';
            titZOBRAZ  = '~Z~obraz';
            titNAJDI   = '~N~†jdi ';
            titVSETKY  = '~V~®echny';

            titVZOR    = '~V~zor  ';
            titRPL     = '~R~PL   ';

            titSTATIS  = 'õt~a~tis';

            titBOD     = '~B~ody';
            titNDB     = '~N~DB/VOR';
            titRTEM    = '~T~rate';
            titABC     = 'Abe~c~eda';
            titACT     = 'Popi~s~';
            titTRAT    = 'Tr~a~ü';
            titREG     = 'Re~g~ular';

            {titTOOLS   = 'P~o~moc ';    hkTOOLS = kbAltO;}
            titVIEW    = 'P©ehled ';
            titVIEW_A  = 'P©ehled archivu ';

            msgABOUT   = 'O systÇmu:';
            msgINFO    = 'Info...';
            msgERR     = 'Chyba...';
            msgMESS    = 'Oznam';
            msgSORRY   = 'Lituji';
            msgWARNING = 'Varov†n°';
            msgWAITING = 'Äekejte, pros°m';
            msgVERIPHY = 'Ovà©en°';
            msgACCEPT  = 'Potvrzen°';
            msgBCK     = 'Z†lohov†n°';
            msgFSELECT = 'Vòber s£bora';
            msgFINDING = 'Vyhled†va se...';
            msgCOPY    = 'Kop°ruji, aë se pr†®i...';
            msgSEND    = 'Vys°l†n°';
            msgEXCEPT  = 'Poru®it pravidlo ?';
            msgCORRECT = 'Opravit ?';
            msgISCORRECT = 'Je spr†vny ?';
            msgCONTINUE  = 'Pokraáovat';
            askAPPROVED  = 'Je schv†len† ?';
            ask_prepisat = 'P©epsat ?';

            msgSYSINFO = 'SystÇmovÇ informace:';
            msgLAST    = 'Posledn° stav uzlÅ';
            msgEXIT    = ' Ukonáen° programu ?! ';

            msgSEARCH  = 'Hled†n° ';
            msgREAD    = 'Naáten° ';
            msgINIT    = 'Inicializace ';

            msgFADTE   = ' ze dne ';
            msgOD      = ' ode ';

            msgDATA            = 'ódaje';
            msgMEMORY          = 'M†lo pamàti pro ';
            msgNOT_FOUND       = 'nenanalezeny';
            msgNOT_PROCESSED   = 'was not processed';

            msgDATA_SAVED      = 'Data byli uloëeny.';
            msgDATA_SENDED     = 'Data byli odeslany.';
            msgDATA_NOT_SENDED = 'Data nebyli odeslany.';
            msgDATA_CHANGED    = 'Data byli opraveny.';
            msgDATA_DELETED    = 'Data byli zru®eny.';
            msgDATA_NOT_FOUND  = 'Data poëadovanÇho typu nenanalezena.';
            msgFILES_NOT_FOUND = 'Soubor nenalezen.';
            msgF_INVALID_FORMAT= 'Soubor neobsahuje £daje v oáek†vanem tvaru.';
            msgARCH_EMPTY      = 'V arch°vu se nenach†z° ë†dnÇ soubory';

            msgCONFIG_IGNORE   = 'Jin† verze programu, zkontrolujte si konfiguraci, pros°m.';

            ask_PrintContinue  = 'Opakovat tisk ?';
            ask_CancelProc     = 'Zru®it operaci ?';
            msg_CancelProc     = 'Operace zru®ena.';

            ask_CNL            = 'Naozaj zru®it ';
            askNotActual       = 'Je pl†n pod†n na n†sleduj°ci den ?';

            ask_SUHLAS         = 'Souhlas°te ?';

            tit_na             = 'na';
            tit_dna            = 'dne';

            tit_hod            = 'hod';
            tit_min            = 'min';
            tit_sec            = 'sek';
           {$ENDIF}


           {$IFDEF ENGLISH}
            titYES     = '~Y~es  ';
            titNO      = '~N~o   ';
            titCANCEL  = '~C~ancel';
            titIGNORE  = '~I~gnore ';
            titPOTVRD  = 'Con~f~irm';
            titSPRACUJ = 'P~r~ocess';

            titPREV    = '~<~ prev';
            titNEXT    = 'next ~>~';

            titDLA     = '~P~end ';
            titACK     = '~A~pproval';
            titCOR     = 'C~o~rrect';
            titDCL     = '~C~ancel';
            titDEL     = '~D~elete';

            titSEND    = '~S~end  ';
            titSAVE    = 'S~a~ve  ';
            titEDIT    = '~E~dit  ';

            titSAVErpl = '>Samp~l~';
            titSAVEas  = 'Save as';
            titPRINT   = 'Pri~n~t ';
            titEXPORT  = 'E~x~port';
            titBACKUP  = '~B~a~ckup';
            titARCHIV  = 'A~r~chive';
            titZOBRAZ  = 'S~h~ow  ';
            titNAJDI   = '~F~ind  ';
            titVSETKY  = 'A~l~l   ';

            titVZOR    = 'Samp~l~e';
            titRPL     = '~R~PL   ';

            titSTATIS  = '~S~tatis';

            titBOD     = '~P~oints';
            titNDB     = '~N~DB/VOR';
            titRTEM    = 'R~o~utes';
            titABC     = 'A~B~C';
            titACT     = 'A~c~tvity';
            titTRAT    = 'Ro~u~te';
            titREG     = 'Re~g~ular';

            {titTOOLS   = 'T~o~ols ';    hkTOOLS = kbAltO;}
            titVIEW    = 'List of ';
            titVIEW_A  = 'List of archived ';

            msgABOUT   = 'About:';
            msgINFO    = 'Info...';
            msgERR     = 'Error...';
            msgMESS    = 'Message';
            msgSORRY   = 'Sorry';
            msgWARNING = 'Warning';
            msgWAITING = 'Wait, please';
            msgVERIPHY = 'Veriphy';
            msgACCEPT  = 'Accept';
            msgBCK     = 'Backup';
            msgFSELECT = 'Select file';
            msgFINDING = 'Searching...';
            msgCOPY    = 'Copying file.';
            msgSEND    = 'Sending';
            msgEXCEPT  = 'Exception ?';
            msgCORRECT = 'Make a correction ?';
            msgISCORRECT = 'It is correct ?';
            msgCONTINUE  = 'Continue';
            askAPPROVED  = 'Is approved ?';
            ask_prepisat = 'Overwrite ?';

            msgSYSINFO = 'System information:';
            msgLAST    = 'Last nodes status';
            msgEXIT    = ' End of the program ?! ';

            msgSEARCH  = 'Searching ';
            msgREAD    = 'Reading from ';
            msgINIT    = 'Initialization ';

            msgFADTE   = ' from '; { day }
            msgOD      = ' from ';

            msgDATA            = 'Data of';
            msgMEMORY          = 'Not enough memory for ';
            msgNOT_FOUND       = 'not found';
            msgNOT_PROCESSED   = 'was not processed';

            msgDATA_SAVED      = 'Data has been saved.';
            msgDATA_SENDED     = 'D†ta has been sended.';
            msgDATA_NOT_SENDED = 'D†ta has not been sended.';
            msgDATA_CHANGED    = 'Data has been changed.';
            msgDATA_DELETED    = 'Data has been canceled.';
            msgDATA_NOT_FOUND  = 'Requested data not found.';
            msgF_INVALID_FORMAT= 'File data doesn''t match expected format.';
            msgARCH_EMPTY      = 'There are no archived files';
            msgFILES_NOT_FOUND = 'File not found.';

            msgCONFIG_IGNORE   = 'Another version of the program, check user configuration, please.';

            ask_PrintContinue  = 'Continue in printing ?';
            ask_CancelProc     = 'User interrupt. Cancel operation ?';
            msg_CancelProc     = 'Operation has been cancelled.';

            ask_CNL            = 'Realy cancel ';
            askNotActual       = 'Is the plan valididity for next day ?';

            ask_SUHLAS         = 'Do you agree?';

            tit_na            = 'on';
            tit_dna           = 'on';

            tit_hod            = 'hrs';
            tit_min            = 'min';
            tit_sec            = 'sec';
           {$ENDIF}


           {$IFDEF SLOVAK}
             msg_ARCHIV_CHECK = 'Checking archived files... ';
           {$ENDIF}

           {$IFDEF CZECH}
             msg_ARCHIV_CHECK = 'Kontroluji archivn° soubory... ';
           {$ENDIF}

           {$IFDEF ENGLISH}
             msg_ARCHIV_CHECK = 'Checking archived files... ';
           {$ENDIF}

    const  {$IFDEF SLOVAK}
             MISS_             = 'Chòba ';
             IS_MISSING        = ' chyba';
           {$ENDIF}

           {$IFDEF CZECH}
             MISS_             = 'Chòb° ';
             IS_MISSING        = ' chyba';
           {$ENDIF}

           {$IFDEF ENGLISH}
             MISS_             = 'Missing ';
             IS_MISSING        = ' is missing';
           {$ENDIF}


    const  pripona_podla_rodu :
              array[0..2] of string[1] = {$IFDEF SLOVAK}  ('ò','†','Ç')
                                         {$ENDIF}
                                         {$IFDEF CZECH}   ('', '†','o')
                                         {$ENDIF}
                                         {$IFDEF ENGLISH} ('', '', '')
                                         {$ENDIF}
                                         ;

implementation

end.