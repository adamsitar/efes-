    { ----------------------------------
       Letovy plan podla ICAO/Doc.4444
      תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
    }

    const  db0_FPL4_RIADKOV = 7;
           db_FPL4_RIADKOV  = 8;

           db_fpl4_data     = 0;
           db_fpl4_15_1     = 1;
           db_fpl4_15_2     = 2;
           db_fpl4_18_1     = 3;
           db_fpl4_18_2     = 4;
           db_fpl4_19       = 5;
           db_fpl4_20       = 6;
           db_fpl4_ine      = 7;

           dbchg_FPL4       : bool = false;
           dbchg_FPL4_RPL   : bool = false;

           dbattr_FPL4 = {$IFDEF DB_BIN} DBbin {$ELSE} DBtxt {$ENDIF};


    type   PFPL4 = ^DFPL4;
           DFPL4 = record

            { -----------------------
              polozky podla Doc.4444
              -----------------------
            }
             _3   : string[kod_3];               { druh, cislo spravy a odkazovacie udaje                          }
             _5   : pchar;                       { popis nudze                                                     }
             _7   : string[kod_7];               { identifikacia lietadla, mod a kod SSR                           }
             _8   : string[kod_8];               { pravidla a druh letu                                            }
             _9   : string[kod_9];               { pocet, typ lietadla, kategoria turbulencie v uplave             }
             _10  : string[kod_10];              { vybavenie                                                       }
             _13  : string[kod_13];              { letisko odletu a cas odletu + upresneny cas odletu              }
             _14  : string[kod_14];              { vypocitany cas preletu                              }
             _15  : pchar;                       { trat                                                            }
             _16  : string[kod_16];              { letisko urcenia, celkova vypocitana doba letu, nahradne letiska }
             _17  : pchar;                       { skutocne letisko pristatia a cas, pripadne jeho plny nazov      }
             _18  : pchar;                       { ine informacie                                                  }
             _19  : pchar;                       { doplnujuce informacie                                           }
             _20  : pchar;                       { pohotovostne informacie pre patranie a zachranu                 }
             _21  : pchar;                       { informacie o strate spojenia                                    }
             _22  : pchar;                       { zmena, napr 13/DEP...                                           }


            { -------------------
              vypoctove premenne
              -------------------
            }
             date : TDate;                       { datum realizacie planu }
             stat : string[kod_HEAD];
             eet  : TOB_;                        { vypocitany vstup do oblasti }
             vys  : word;
             vys_ : char;
             exi  : TOB_;                        { vypocitany vystup z oblasti }

             src  : Tfplsrc;                     { zdroj informacie...    }
             {$IFDEF NET}
              rec : Tplan_rec;
             {$ENDIF}

             data : PFPL4_decoded_data;
           end;


    const {$IFDEF DEBUG} max_FPL4s = 300;
          {$ELSE}        max_FPL4s = 2000;
          {$ENDIF}

    type  PFPL4s = ^TFPL4s;
          TFPL4s = array[0..MAX_PTRs-1] of PFPL4;
