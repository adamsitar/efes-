    const  pos_kod        = 1;
           pos_zs         = 2;
           pos_typ        = 4;
           pos_ine        = 5;
           pos_sector     = 6;

           odd_body       = [';'];
           prizn_not_kr   = '-';


    const  prizn_CLet     = 'AIP-C';
           prizn_MLet     = 'AIP-M';
           prizn_ALet     = 'AIP-A';

           prizn_OB       = 'OB';

           prizn_NONE     = 'NONE';     { krizik                            }
           prizn_SECTOR   = 'SECTOR';   { krizik                            }
           prizn_REPORT   = 'REPORT';   { krizik                            }
           prizn_REP1     = 'REP1';     { prazdny trojuholnik               }
           prizn_REP2     = 'REP2';     { plny trojuholnik                  }
           prizn_NDB1     = 'NDB1';     { prazdny trojuholnik, kruhy okolo  }
           prizn_NDB2     = 'NDB2';     { plny trojuholnik, kruhy okolo     }
           prizn_VOR      = 'VOR';      { sestuholnik, kruhy okolo          }
           prizn_VOR_DME1 = 'VOR/DME1'; { sest,stvorec,pr troj, kruhy okolo }
           prizn_VOR_DME2 = 'VOR/DME2'; { sest,stvorec,pl troj, kruhy okolo }

           prizn_Rp       = 'R PLAN';
           prizn_Ra       = 'R ACT' ;

           prizn_OUT      = 'OUT';


    type   TSymType       = byte;
           TSetSymType    = set of TSymType;


    const  sym_CLet       = 1;
           sym_MLet       = 2;
           sym_ALet       = 3;

           sym_OB         = 10;

           sym_NONE       = 20;
           sym_SECTOR     = 21;
           sym_REPORT     = 30;
           sym_REP1       = 31;
           sym_REP2       = 32;
           sym_NDB1       = 33;
           sym_NDB2       = 34;
           sym_VOR        = 35;
           sym_VOR_DME1   = 36;
           sym_VOR_DME2   = 37;
