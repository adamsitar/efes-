    { OLDI definuje nasledujuce druhy sprav

        AFTN      -   SOH + TransmisionIdentification + Address + OriginLine + STX + OperationalMessages + AF + VT + ETX
        METEOR    -
        FREE TEXT -

        OLDI      -   STX + LENG + ADEST + DEST + AEMM + EMM + TYP + ADR + Message text + ETX
                      - OLDI sa dalej rozlisuju typom, vid nizsie

        AMA       -     - // -
        ICAO      -     - // -
    }


    const  _SOH                  = #1;


         { struktura OLDI, AMA, ICAO }

           _STX                  = #2;
           _LENGTH               = chr($48);
           _ADEST                = chr($40);
           _DEST                 = chr($40);
           _AEMM                 = chr($40);
           _EMM                  = chr($40);
           _TYP_operational_mess = chr($41);
           _TYP_operator_mess    = chr($42);
           _TYP_system_mess      = chr($44);
           _TYP_status_mess      = chr($45);
           _ADR                  = chr($40);
           _ETX                  = #3;


           _subHead      =  _LENGTH+_ADEST+_DEST+_AEMM+_EMM;

           _subStartUp   =  chr($30)+chr($31);
           _subHeartBeat =  chr($30)+chr($33);
           _subShutDown  =  chr($30)+chr($30);

           messStartUp   =  _STX + _subHead + _TYP_system_mess      + _ADR + _subStartUp   + _ETX;
           messHeartBeat =  _STX + _subHead + _TYP_system_mess      + _ADR + _subHeartBeat + _ETX;
           messShutDown  =  _STX + _subHead + _TYP_system_mess      + _ADR + _subShutDown  + _ETX;

           messData_     =  _STX + _subHead + _TYP_operational_mess + _ADR;
           messUser_     =  _STX + _subHead + _TYP_operator_mess    + _ADR;
           messStat_     =  _STX + _subHead + _TYP_status_mess      + _ADR;


    type   msSystem      = ( msOther,
                             msStartUp,msHeartBeat,msShutDown,
                             hdData,
                             hdUser,
                             hdStat
                           );

    const  headSystem    : array[msStartUp..hdUser] of pchar =

                           ( messStartUp, messHeartBeat, messShutDown,
                             messData_,
                             messUser_
                           );


    function  code_OLDI_pkt (header: string; data: pchars; size: word; var pkt: pchars; var dlz: word): bool;
