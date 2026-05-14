    type   msAF_TSGAdata  = ( msALR, msRCF,
                              msFPL, msCHG, msDLA, msCNL,
                              msDEP, msARR,
                              msPLN,
                              msPPL (*, msPCH,
                              msSRQ, msFLA, msSLT,
                              msFPM*)
                            );


    const  hd_AF_TSGA     : array[msALR..msPPL] of Thead_ICAO =

                           ( 'ALR',  { ICAO }
                             'RCF',

                             'FPL',
                             'CHG',
                             'DLA',
                             'CNL',

                             'DEP',  { AMA  }
                             'ARR',

                             'PLN',

                             'PPL'   (*
                             'PCH',  { GHG/PPL }

                             'SRQ',
                             'FLA',
                             'SLT',

                             '((('   { FPL/MIL }*)
                           );


    const  cfg_AFTN_TEST   = 'TEST';
           cfg_AFTN_STREAM = 'STREAM';

           test_AFTN_TSGA  : string = '›››››››››››››››››››››››››››››››››';
