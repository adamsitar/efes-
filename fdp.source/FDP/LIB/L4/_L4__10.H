    const   kod_10a  = 10;
            kod_10b  = 2;

            kod_10   = 12;


    const { "10a" Radiove, spojovacie, navigacne a priblizovacie vybavenie
          }
            eqp_NONE = 'N'; { No COM/NAV carried or unserrviceable }
            eqp_STD  = 'S'; { Standard - // -                      }

            eqp_A    = 'A'; { Not allocated          }
            eqp_B    = 'B'; { Not allocated          }
            eqp_C    = 'C'; { LORAN C                }
            eqp_D    = 'D'; { DME                    }
            eqp_E    = 'E'; { Not allocated          }
            eqp_F    = 'G'; { ADF                    }
            eqp_G    = 'G'; { (GNSS)                 }
            eqp_H    = 'H'; { HF RTF                 }
            eqp_I    = 'I'; { Inertial Naviagation   }
            eqp_J    = 'J'; { (Data link)...         }
            eqp_K    = 'K'; { (MLS)                  }
            eqp_L    = 'L'; { ILS                    }
            eqp_M    = 'M'; { Omega                  }
            eqp_O    = 'O'; { VOR                    }
            eqp_P    = 'P'; { Not allocated          }
            eqp_Q    = 'Q'; { Not allocated          }
            eqp_R    = 'R'; { RNP type certification }
            eqp_T    = 'T'; { TACAN                  }
            eqp_U    = 'U'; { UHF RTF                }
            eqp_V    = 'V'; { VHF RTF                }
            eqp_W    = 'W'; { RWSM }
            eqp_X    = 'X'; { When prescribed by ATS }
            eqp_Y    = 'Y'; { When prescribed by ATS }
            eqp_Z    = 'Z'; { Other equipment carried }


          { "10b" Vybavenie sekundarnym radarom
          }
            mod_N    = 'N';  { bez }
            mod_A    = 'A';  { 4 cislice, 4096 kodov }
            mod_C    = 'C';  {  - //- + mod C        }
            mod_X    = 'X';  { mod S bez vysielania identifikacie a udajov barometrickej vysky }
            mod_P    = 'P';  { mod S s -//- ale bez identifikacie lietadla }
            mod_I    = 'I';  { mod S bez -//- a s -//- }
            mod_S    = 'S';  { vsetko }

            mod_D    = 'D';  { ADS capability }


          { -S/A
            -SCHJ/CD
            -SAFJ/SD
          }


    const  set_10aN : TCharSet  = [eqp_NONE];
           set_10aS : TCharSet  = [eqp_STD,
                                   eqp_A..eqp_M,
                                   eqp_O..eqp_R,
                                   eqp_T..eqp_Z
                                  ];

           set_10b  : TCharSet  = [mod_N,
                                   mod_A,mod_C,mod_X,mod_P,mod_I,
                                   mod_S
                                  ];
           set_10b_ : TCharSet  = [mod_D,' '];

           set_10   : TCharSet  = [mod_N,
                                   mod_A,mod_C,mod_X,mod_P,mod_I,mod_S,
                                   mod_D,' '
                                  ];


    const  _AFIL_10 : bool = true;  { spinac automaticke doplnenie chybajucich hodnot }


    function   code_l4_10_ (_10a,_10b: string; _7b10b: char): string;
    function   code_l4_10  (_10a,_10b: string): string;

    procedure  decode_l4_10 (_10: string; var _10a,_10b: string);

