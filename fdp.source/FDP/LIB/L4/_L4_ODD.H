    const  icao_STD    = '(';
           icao_END    = ')';
           icao_ARR    = '-';
           icao_NXT    = '/';
           icao_NXIT   = ' ';

           odd_ICAO    {: TCharSet} = [icao_STD,icao_ARR,icao_END];
           odd_L4      {: TCharSet} = [icao_STD,icao_ARR,icao_END];
           odd_ICAO_   {: TCharSet} = [icao_ARR,icao_NXT,icao_NXIT];
           odd_L4_     {: TCharSet} = [icao_ARR,icao_NXT,icao_NXIT];

           repl_l4     = '_';