     const   X25_INIT_TIME_OUT : word =
                {$IFDEF DEBUG}
                   {$IFDEF X25} 5*17 {$ELSE} 5*17 {$ENDIF}
                {$ELSE}
                   {$IFDEF _X25_CONNECT_TIME_OUT}
                      60*17
                   {$ELSE}
                      10*17
                   {$ENDIF}
                {$ENDIF};


             X25_RESEND_TIME_OUT   : word = 3*18; { max.pocet tickov pre neuspesne opakovane vysielania paketu do siete }

             X25_COMPLETE_TIME_OUT : word = 1*18;
             X25_CALL_TIME_OUT     : word = 1*18;
             X25_LISTEN_TIME_OUT   : word = 1*18;
