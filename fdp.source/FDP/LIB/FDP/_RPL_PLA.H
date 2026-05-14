
    type   PRPL = ^DRPL;
           DRPL = record
             val  : char;                        { "+" pre plati, "-" pre neplati  }

             zac  : string[kod_DATE];            { zaciatok                        }
             kon  : string[kod_DATE];            { koniec platnosti                }
             dni  : array[1..7] of char;         { platnost v tyzdni               }

             _7a  : string[kod_7a];              { identifikacia letu              }
             _7x  : char;                        { priznak dalsieho planu 'A'..'Z' }
             _9b  : string[kod_9b];              { typ lietadla                    }
             _9c  : string[kod_9c];

             _13a : string[kod_AP];              { letisko odletu a cas odletu     }
             _13b : string[kod_TIME];

             _16a : string[kod_AP];              { letisko urcenia, doba letu      }
             _16b : string[kod_TIME];

             _15  : pchar;                       { trat                            }
             _18  : pchar;                       { ine informacie                  }
           end;


    const {$IFDEF DEBUG} max_RPLs = 300;
          {$ELSE}        max_RPLs = 2000;
          {$ENDIF}

    type  PRPLs = ^DRPLs;
          DRPLs = array[0..MAX_PTRs-1] of PRPL;


    const  db_RPL_RIADKOV    = 3;
           db_rpl_data       = 0;
           db_rpl_15         = 1;
           db_rpl_18         = 2;

           db_RPLF_RIADKOV   = db_RPL_RIADKOV + db_FPL4_RIADKOV;
           dbchg_RPLF : bool = false;
           dbattr_RPLF = DBbin;

    type   PRPLF = ^DRPLF;
           DRPLF = record
             rpl : DRPL;
             fpl : DFPL4;
           end;
