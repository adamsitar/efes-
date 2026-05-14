    const  rngDEP           : int  =  5; {' tolerancia pre cas startu mFPL }
           casPRED          : int  =  5; {'}
           casPRIST         : int  =  3;

           FPL0_DOUBLE_POINTS : bool = false;

          { program kontroluje duplicitu SSR code
          }
           FPLC_SSR  : bool = {$IFDEF SSR_MANAGEMENT} true {$ELSE} false {$ENDIF};  
           FPLM_SSR  : bool = {$IFDEF SSR_MANAGEMENT} true {$ELSE} false {$ENDIF};
