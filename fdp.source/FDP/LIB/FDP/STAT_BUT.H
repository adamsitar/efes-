
       const   cbtREP     = '~.~..';
               btREP      : PTButton = nil;


               {cbtFDPBCK  = '~F~DP 2 ';
               btFDPBCK   : PFButton = nil;
               }


              {$IFDEF DATA_WRITTEN_IN_APP}
               cbtAPPsc   = '~P~';
               btAPPsc    : PIButton = nil;
              {$ENDIF}

               cbtDBis    = 'DB';
               btDBis     : PFButton = nil;
               cntrDB     : int = 0;

               cbtNETis   = 'NET';
               btNETis    : PFButton = nil;
               cntrNET    : int = 0;

               cbtEXTis   = {$IFDEF AFTN} 'AFTN' {$ELSE} 'EXT' {$ENDIF};
               btEXTis    : PFButton = nil;
               cntrEXT    : int = 0;


              {$IFDEF MASTER}
               cbtBCK     = '~2~nd';
               btBCK      : PIButton = nil;
              {$ENDIF}

              {$IFDEF BACKUP}
               cbtMAS     = '~1~st';
               btMAS      : PIButton = nil;
              {$ENDIF}


              {$IFDEF ALR}
               cbtALR     = '~A~LR';
               btALR      : PIButton = nil;
              {$ENDIF}


              {$IFDEF ERR}
               cbtERS     = '~E~RR';
               btERS      : PIButton = nil;
              {$ENDIF}


              {$IFDEF TLG}
               cbtSS      = '~S~S/DD';
               cbtFF      = 'FF/~G~G';
               cbtKK      = '~K~K/LL';

               btSS       : PSButton = nil;
               btFF       : PSButton = nil;
               btKK       : PSButton = nil;
              {$ENDIF}


              {$IFDEF AFTN}
               cbtAFTN    = 'AFTN~!~';
               btAFTN     : PIButton = nil;

               cbtAFTN2   = 'AFTN~2~';
               bt2AFTN2   : PIButton = nil;
              {$ENDIF}

              {$IFDEF CONNECT_TO_OPL_EXT}
               cbtOPL     = 'OPL~!~';
               btOPL      : PTimeOutExtButton = nil;
              {$ENDIF}


              {$IFDEF OLDI}
               cbtOLDI    = '~O~LDI';
               btOLDI     : PTButton = nil;

               cbtOLDIBCK = '~O~LDI2';
               btOLDIBCK  : PFButton = nil;
              {$ENDIF}


              {$IFDEF RPL}
               cbtRPL  = '~R~PL';
               btRPL   : PIButton = nil;
              {$ENDIF}

              {$IFDEF PLN}
               cbtPLN  = 'PL~N~';
               btPLN   : PIButton = nil;
              {$ENDIF}


              {$IFDEF FPL0}
               {$IFDEF KRL}
                cbtKRL  = '~K~RL';
                btKRL   : PTButton = nil;
               {$ENDIF}

               cbtFPL   = '~F~PL';
               btFPL    : PTButton = nil;

               {$IFDEF REPORT_FPLM_ARW}
                cbtARR  = '~A~RR';
                btARR   : PIButton = nil;
               {$ENDIF}

              {$ENDIF}

              {$IFDEF FLI_COORDINATION}
               cbtFLI  = '~F~LI';
               btFLI   : PIButton = nil;
              {$ENDIF}

              {$IFDEF MATCA}
               cbtREQ  = '~R~EQ';
               btREQ   : PIButton = nil;
              {$ENDIF}


              {$IFDEF ZAM}
               cbtZAM   = '~Z~AM';
               btZAM    : PTButton = nil;
              {$ENDIF}

              {$IFDEF DVZ}
               cbtDVZ   = '~D~VZ';
               btDVZ   : PTButton = nil;
              {$ENDIF}

              {$IFDEF QGO}
               cbtQGO   = '~Q~GO';
               btQGO   : PTButton = nil;
              {$ENDIF}

              {$IFDEF PRS}
               cbtPRS   = '~P~RS';
               btPRS   : PTButton = nil;
              {$ENDIF}

              {$IFDEF SPR}
               cbtMES  = '~M~SG';
               btMES   : PTButton = nil;
              {$ENDIF}
