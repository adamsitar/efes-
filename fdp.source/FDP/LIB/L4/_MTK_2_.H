    const  MTK_2_BITes      = 5;        { Sirka slova                      }
           MTK_2_LINE       = 69;       { Maximalna dlzka riadku spravy    }
           MTK_2_PAGE       = 65;       { Maximalna dlzka strany           }
           MTK_2_WORD       = 200;      { Maximalny pocet slov v telegrame }

           MTK_2_Tr_TimeOut = 20;
           MTK_2_Ts_TimeOut = 30;       { Po tomto timeoute sa pred spravou vysiela
                                          spustaci impulz MTK_2_L + 1.5 s pauza
                                        }

    const  set_MTK_2abc : TCharSet = [' ','0'..'9',
                                      'A'..'Z',
                                      '€'..#255,
                                      '-','?',':','(',')','.',',','=','/','+','"'
                                     ];

           set_MTK_2adr : TCharSet = [' ','A'..'Z','€'..'Ÿ'];
           set_MTK_2tlg : TCharSet = ['S','D','F','G','K','L'];



    const  MTK_2_MOD_CISLA_SPRAVY      = 1000;
           kod_MTK_2_MOD_CISLA_SPRAVY  = 3;

    function INC_CISLO_SPRAVY(var CISLO_SPRAVY: word; fn: string): word;
