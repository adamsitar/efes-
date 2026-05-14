         { -----------------
            Riadiace znaky
           .................
         }


    const
         { a) ohranicenie paketu
         }
           MTK_2_SOT        = 'ZCZC';   { zaciatok tlgr spravy   }
           MTK_2_SOT_R      = 'áñáñ';

           MTK_2_EOT        = 'NNNN';   { koniec tlgr spravy     }
           MTK_2_EOT_R      = 'çççç';   { dalsie riadiace kody su uveden nizsie }


         { b) prepinanie medzi abecedami
         }
           MTK_2_A36UKA = ''; M2_A = MTK_2_A36UKA;
           MTK_2_LATIN  = ''; M2_L = MTK_2_LATIN;
           MTK_2_DIGITS = ''; M2_D = MTK_2_DIGITS;


         { c) formatovanie textu
         }
           MTK_2_SPACE  = #26; M2_S = MTK_2_SPACE;   { ' '}
           MTK_2_CR     = '<'; M2_C = MTK_2_CR;      { CR }
           MTK_2_LF     = ''; M2_F = MTK_2_LF;      { FF }

           MTK_2_WHO    = ''; M2_W = MTK_2_WHO;     { Kto je tam ? }
           MTK_2_BELL   = 'û';



         { ----------------
            Tabulka MTK-2
           ................
         }

    const  max_MTK_2_znk = 32;
           max_MTK_2_abc = 3;

           { Poznamka: "4" sluzi ako "ó", lebo sa v azbuke podobaju.
                       "ö" nie je vyuzite
                       MTK_2_DIGITSû.....û  znamenaju zvoncek(y)
           }

           MTK_2: array[0..max_MTK_2_abc-1] of pchar {string[max_MTK_2_znk]} =
                  ((M2_A+'í'+M2_C+'é'+M2_S+'ïçå'+M2_F+'ãêÉàèñÜÖáÑÅëõîúÄÇâ'+M2_D+'ìüä'+M2_L),
                   (M2_A+'T'+M2_C+'O'+M2_S+'HNM'+M2_F+'LRGIPCVEZDBSYFXAWJ'+M2_D+'UQK'+M2_L),
                   (M2_A+'5'+M2_C+'9'+M2_S+'ô,.'+M2_F+')4ò80:=3+'+MTK_2_WHO+
                                                                '?,6ù/-2û'+M2_D+'71('+M2_L)
                  );

           MTK_2_CONTROL = [M2_A,M2_C,M2_S,M2_F,MTK_2_WHO,M2_D,M2_L];


           rdk_MTK_2_A36 = 0;
           rdk_MTK_2_LAT = 1;
           rdk_MTK_2_DIG = 2;

           iM2_A= 0;
           iM2_C= 2;
           iM2_S= 4;
           iM2_F= 8;
           iM2_D= 27;
           iM2_L= 31;



         { ----------
            Signaly,  niektore slova sa nesmu vyskytnut v texte, vid "Zakazene slova v telegrame"
           ..........
         }

    const  MTK_2_EOT_     = MTK_2_LF+MTK_2_LF+MTK_2_LF+MTK_2_LF+MTK_2_LF+MTK_2_LF+MTK_2_LF
                            +MTK_2_EOT
                            +M2_L+M2_L+M2_L+M2_L+M2_L+M2_L+M2_L+M2_L+M2_L+M2_L+M2_L+M2_L
                            ;

           MTK_2_INT_     = M2_S+M2_S+M2_S+M2_S+M2_S        { interval medzin        }
                            +M2_L;
           {MTK_2_INT_R    = M2_S+M2_S+M2_S+M2_S+M2_S         interval rusky
                            +M2_A;}

           MTK_2_NL_      = M2_C+M2_C+M2_F;                 { koniec riadku          }

           {MTK_2_ET_R     = M2_A+M2_C+M2_C+M2_F;             koniec textu ruskeho   }
           MTK_2_ET_      = M2_L+M2_C+M2_C+M2_F;            { koniec textu           }

           MTK_2_NMPS_    = M2_F+M2_F+M2_F+M2_F+M2_F+M2_F   { rozdelenie tlgr sprav  }
                            +M2_F;                          { na roli papiera        }
           MTK_2_NMPP_    = M2_L+M2_L+M2_L+M2_L             { rozdelenie tlgr sprav  }
                            +M2_L+M2_L+M2_L+M2_L            { na pocitacovom papieri }
                            +M2_L+M2_L+M2_L+M2_L;

           {MTK_2_WAY_R    = 'ÜÜÜ'                            'obchadzka'
                            +M2_S+M2_S+M2_S+M2_S+M2_S
                            +M2_A;}
           MTK_2_WAY_     = 'VVV'
                            +M2_S+M2_S+M2_S+M2_S+M2_S
                            +M2_L;

           MTK_2_ERROR_   = M2_S+'E'+M2_S+'E'+M2_S+'E'+M2_S; { chyba }

           {MTK_2_IGNORE_R = M2_C+M2_C+M2_F                    ignoruj
                            +M2_D+'ô'+M2_A+'íÄ'+M2_S
                            +M2_D+'ô'+M2_A+'íÄï'
                            +M2_C+M2_C+M2_F;}
           MTK_2_IGNORE_  = M2_C+M2_C+M2_F
                            +'QTA'+M2_S+'QTA'
                            +M2_L+M2_C+M2_C+M2_F;

           {MTK_2_WARNING_R  = 'ûûûûû';}
           MTK_2_WARNING_   = 'JJJJJ';

           {MTK_2_CH_R       = 'ñï';}
           MTK_2_CH         = 'CH';


    const  ITA2_CHANNEL_SIZE = 3;

