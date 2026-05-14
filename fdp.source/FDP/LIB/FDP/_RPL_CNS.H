    const  RPL_ON    = '+';              { RPL plan je platny     }
           RPL_OFF   = '-';              { RPL plan neplati       }
           RPL_UFN   = 'UFN';            { posledny datum prevadzkovania letu nie je znamy }

           RPL_DATE  : TDate = (d:1; m:1; r:1999);


    const  rpl_hour : int       = 21;               { cas generovania planov }
           rpl_min  : int       = 10;

           cfg_RPL_hour         = 'H-RPL';
           cfg_RPL_min          = 'M-RPL';

           rpl_PND  : bool      = false;
           rpl_ERR  : bool      = false;

           rpl_assign_15 : bool = false;  { snazi sa priradit trat z mnoziny standartnych,
                                            ak su uvedene len vstupny a vystupny bod
                                          }

           {RPL_IGNORE_EXPIRY_DATE}


    const  bminiRPL  : bool     = true;

           max_RPL_15_rm : int  = 2;
           max_RPL_15_r_lo      = 0;
           max_RPL_15_r_hi      = 6;

           max_RPL_18_rm : int  = 1;
           max_RPL_18_r_lo      = 0;
           max_RPL_18_r_hi      = 2;

           RUSSIAN_RPL  : bool  = true;

           prn_RPL_IFPS : bool  = false;


    const  is_RPL      : bool = false;
           is_RPLDB    : bool = false;
           is_RPLDBERR : bool = false;


    const  cm_zarad_RPL         =    $1;
           cm_check_RPL_KEY     =   $20;
           cm_decode_RPL_FPL4   =   $40;
