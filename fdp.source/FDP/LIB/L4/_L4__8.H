    const  kod_8   = 2;

           set_7Ma2  : TCharSet  = ['A'..'Z','1'..'9',' '];


    const { Pravidla letu "8a" :
          }
           IFR_let = 'I';
           VFR_let = 'V';
           IFR_prv = 'Y';
           VFR_prv = 'Z';

           mil_VFR = 'V';
           mil_IFR = 'P';

           set_VFR = [VFR_let,mil_VFR];


    const { Druh letu "8b" :
          }
           PRAV_DOPRAVNY_LET = 'S'; { ....... pravidelny dopravny let   }
           NEPR_DOPRAVNY_LET = 'N'; { ....... nepravidelny dopravny let }

           VSEOBECNY_LET     = 'G'; { ....... let vseobecneho letectva  }
           INY_LET           = 'X'; { ....... inaksi let                }

           VOJENSKY_LET_GAT  = 'M'; { medzinarodne vojenske lety po tratiach ATS pod civ RLP }


          {IFDEF L4444M}
           VOJENSKY_LET_OAT  = 'F'; { mimoletiskove lety a prelety pod riadenim voj RLP  }
           VOJENSKY_LET_AP   = 'L'; { vojensky let v priestore zodpovednosti letiskovych
                                      organov zodpovednosti, pripadne navadzacich alebo
                                      velitelskych stanovisk
                                    }
          {ENDIF}


    const  set_8a   : TCharSet  = [IFR_let,VFR_let,IFR_prv,VFR_prv];

           set_8aM  : TCharSet  = [IFR_let,VFR_let,IFR_prv,VFR_prv
                                  {$IFDEF SK} {$IFDEF MATCA}, mil_VFR, mil_IFR {$ENDIF} {$ENDIF}
                                  ];


           set_8b   : TCharSet  = [PRAV_DOPRAVNY_LET,
                                   NEPR_DOPRAVNY_LET,

                                   VOJENSKY_LET_GAT,

                                   VSEOBECNY_LET,
                                   INY_LET
                                  ];


           set_8bM  : TCharSet  = [{IFDEF L4444M}
                                    VOJENSKY_LET_OAT, VOJENSKY_LET_AP
                                   {ENDIF}
                                  ];

           set_8bO  : TCharSet  = [VSEOBECNY_LET,INY_LET];


          { Existuje konflikt v typoch planov letov.
            I civilne lety, i vojenske sa mozu oznacit ako
            "X" a asi i "G".

            Konflikt sa riesi tak, ze lety sa odlisia podla
            zdroja spracovania, podla letisk startu a pristatia
            (civiln<->vojenske).
          }

          { -V
            -IS
          }


    const  _AFIL_8 : bool = true;  { spinac automaticke doplnenie chybajucich hodnot }


    function   code_l4_8    (_8a,_8b: char; _L4444M: bool): string;
    procedure  decode_l4_8  (_8: string; var _8a,_8b: char);

