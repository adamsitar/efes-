
    const  set_NXT  : TCharSet  = [icao_NXT];

           set_alt  : TCharSet  = [altG,altA,altH,altM,altS,altFL];
           set_alt_ : TCharSet  = [altAbove,altBellow,' '];

           setVys   : TCharSet  = ['0'..'9',' ',
                                   altG,altA,altH,altM,altS,altFL,
                                   'V','F','R', 'G','N','D', 'U','N','L'
                                  ];
           setVysAB : TCharSet  = ['0'..'9',' ',
                                   altG,altA,altH,altM,altS,altFL,
                                   'V','F','R', 'G','N','D', 'U','N','L',
                                   altAbove,altBellow
                                  ];

           {kod_rbs_SSR = 4;   set_rbs_SSR : TCharSet = ['0'..'7'];
           kod_uvd_BN  = 5;   set_uvd_BN  : TCharSet = ['0'..'9'];}

           set_15   : TCharSet  = ['0'..'9', 'a'..'z','A'..'Z', ' ',
                                   ',','.','?','/','+'
                                  ];

           set_18   : TCharSet  = ['0'..'9', 'a'..'z','A'..'Z', ' ','-',
                                   ',','.','?','/','+'
                                  ];

           set_POZN : TCharSet  = ['0'..'9', 'a'..'z','A'..'Z',' ',
                                   {'(',')',}'-','\','{','}','[',']',
                                   ':',';','"','''','<','>',
                                   ',','.','?','/','+'
                                  ];

           set_19   : TCharSet  = ['0'..'9', 'a'..'z','A'..'Z',' ',
                                   {'(',')',}'\','{','}','[',']',
                                   ':',';','"','''','<','>',
                                   ',','.','?','/','+'
                                  ];
