      {$IFDEF SLOVAK}
        const  NETWORKM = ' U~Z~LY LAN/EXT ';

               S_LETVIS = ' UZLY ~L~ETVIS ';
               S_EXTEN  = ' O~T~VORENIE EXTERNùCH SMEROV ';
               S_EXTOPT = ' ~N~ASTAVENIE EXTERNùCH SMEROV ';
               S_EXTCOM = ' ~K~OMUNIKèCIA S EXTERNùMI SMERMI ';
               S_VYPIS  = ' Z~O~BRAZENIE PAKETOV ';
               S_ARCH   = ' Z~è~LOHOVANIE NAHRèVOK ';

               M_LINEM  = ' Pripojenie ku ~M~ASTER/SLAVE ';

               M_AFTN   = ' ~A~FTN ';
               M_ASTA   = ' ~A~STA ';
               M_ASTA_FDP =  ' - linka FDP';
               M_ASTA_PRN =  ' - linka PRN';
               M_CAMUS  = ' ~E~UROCAT ';
               M_ASOC   = ' A~S~OC ';
               M_OPL    = ' ~O~PL ';
               {$IFDEF ARCHIVE_DAR}
                M_RLIbrc = ' LETVIS ~R~LI ';
                M_FDPnet = ' LETVIS ~F~DP ';
               {$ELSE}
                M_FDPnet = ' ~L~ETVIS ';
               {$ENDIF}
               M_LOG    = ' LO~G~IN ';

               V_PKT    = '~V~ùPIS PAKETOV  Alt(Ctrl)+F11 ';
               V_CAMUS  = '~E~UROCAT pakety ';
               V_ASTA   = '~A~STA pakety ';
               V_ASOC   = 'A~S~OC pakety ';
               V_OPL    = '~O~PL pakety ';
               V_OPLhb  = 'OPL ~h~eartbeat ';
               V_FDPrec = '~P~rijatÇ pakety FDP ';
               V_FDPsen = '~O~doslanÇ pakety FDP ';
               V_FDPdat = '~D~†ta paketu FDP';
               V_FDPack = 'Po~t~vrdenie paketu FDP';
               V_FDPhb  = '~H~eartbeat/áas - zobrazenie';
               V_FDPhba = 'H~e~artbeat/áas - archiv†cia';
               V_MEM    = 'Ve~å~kosü volnej pamÑte';

               A_X25    = '~A~rchiv†cia paketov X25';
      {$ENDIF}

      {$IFDEF CZECH}
        const  NETWORKM = ' U~Z~LY LAN/EXT ';

               S_LETVIS = ' UZLY ~L~ETVIS ';
               S_EXTEN  = ' O~T~EVûENã EXTERNùCH SMâR¶ ';
               S_EXTOPT = ' ~N~ASTAVENã EXTERNùCH SMâR¶ ';
               S_EXTCOM = ' ~K~OMUNIKACE S EXTERNùMI SMâRMI ';
               S_VYPIS  = ' Z~O~BRAZENã PAKET¶ ';
               S_ARCH   = ' Z~è~LOHOVèNã NAHRèVEK ';

               M_LINEM  = ' P©ipojen° ku ~M~ASTER/SLAVE ';

               M_AFTN   = ' ~A~FTN ';
               M_ASTA   = ' ~A~STA ';
               M_CAMUS  = ' ~E~SUP ';
               M_ASOC   = ' A~S~OC ';
               M_OPL    = ' ~O~PL ';
               M_VERA   = ' Vâ~R~A ';
               {$IFDEF ARCHIVE_DAR}
                M_RLIbrc = ' LETVIS ~R~LI ';
                M_FDPnet = ' LETVIS ~F~DP ';
               {$ELSE}
                M_FDPnet = ' ~L~ETVIS ';
               {$ENDIF}
               M_LOG    = ' LO~G~IN ';

               V_PKT    = '~V~ùPIS PAKET¶  Alt(Ctrl)+F11 ';
               V_ASTA   = '~A~STA pakety ';
               V_CAMUS  = '~E~SUP pakety ';
               V_ASOC   = 'A~S~OC pakety ';
               V_VERA   = 'Vâ~R~A pakety ';
               V_OPL    = '~O~PL pakety ';
               V_OPLhb  = 'OPL ~h~eartbeat ';
               V_FDPrec = '~P~©ijatÇ pakety FDP ';
               V_FDPsen = '~O~deslanÇ pakety FDP ';
               V_FDPdat = '~D~ata paketu FDP';
               V_FDPack = 'P~o~tvzen° paketu FDP';
               V_MEM    = 'Ve~l~ikost volnÇ pamàti';

               V_FDPhb  = '~H~eartbeat/áas - zobrazen°';
               V_FDPhba = 'H~e~artbeat/áas - archivace';
      {$ENDIF}

      {$IFDEF ENGLISH}
        const  NETWORKM = ' ~N~ETWORK MANAGEMENT ';

               S_LETVIS = ' ~L~ETVIS NODES ';
               S_EXTEN  = ' ~E~XTERNAL ROUTEs ON/OFF  ';
               S_EXTOPT = ' E~X~TERNAL ROUTEs SETTING ';
               S_EXTCOM = ' E~X~TERNAL ROUTEs COMMANDS ';
               S_VYPIS  = ' PACKETs DISPLA~Y~ ';
               S_ARCH   = ' RECORDs ~B~ACKUP/COPY ';

               M_AFTN   = ' ~A~FTN ';
               M_ASTA   = ' ~A~STA ';
               M_CAMUS  = ' ~C~AMUS ';
               M_ASOC   = ' A~S~OC ';
               M_OPL    = ' ~O~PL ';
               {$IFDEF ARCHIVE_DAR}
                M_RLIbrc = ' LETVIS ~R~LI ';
                M_FDPnet = ' LETVIS ~F~DP ';
               {$ELSE}
                M_FDPnet = ' ~L~ETVIS ';
               {$ENDIF}
               M_LOG    = ' LO~G~IN ';

               V_PKT    = '~V~ùPIS PAKETOV  Alt(Ctrl)+F11 ';
               V_CAMUS  = '~C~AMUS pakety ';
               V_ASTA   = '~A~STA pakety ';
               V_ASOC   = 'A~S~OC pakety ';
               V_OPL    = '~O~PL pakety ';
               V_OPLhb  = 'OPL ~h~eartbeat ';
               V_FDPrec = '~R~eceived FDP packets ';
               V_FDPsen = '~S~ended FDP packets ';
               V_FDPdat = '~D~ata of FDP packet ';
               V_FDPack = '~A~cknowledge of FDP packet ';
               V_FDPhb  = '~H~eartbeat - display ';
               V_FDPhba = 'H~e~artbeat - archivation ';
               {V_MEM    = 'Ve~å~kosü volnej pamÑte';}

               A_X25    = '~A~rchivace paketñ X25';
      {$ENDIF}

