
    type   msData        = ( {msLAM,}
                             msFPL, msCHG, msCNL, msDLA,
                             msDEP, msARR, msCPL, msEST,
                             msABI, msACT, msPAC, msREV
                           );


    const  hd_ASL4       : array[msFPL..msREV] of Thead_ICAO =

                           ( {'LAM',}

                             'FPL',  { ICAO }
                             'CHG',
                             'CNL',
                             'DLA',

                             'DEP',
                             'ARR',
                             'CPL',
                             'EST',

                             'ABI',  { OLDI }
                             'ACT',
                             'PAC',
                             'REV'
                           );


    const  nd_ASOC = '@ASOC';

           ASOCn_  = 'ASOC';
           ASOCcfg = ASOCn_+ext_ini;

           ASOC_PACKET_SIZE = 4096;
           ASOC_BUFFER_SIZE = 3;


    const  writeln_ASOC  : bool = {$IFDEF SERVER} true {$ELSE} false {$ENDIF};
           archive_ASOC  : bool = true;
           utc_ASOC      : bool = true;

           cl_ASOC             {: byte} = 37;   { clGRa; }
           cl_ASOC_system_mess {: byte} = 41;   { clGR7; }
           cl_ASOC_err         {: byte} = red;


    const  cfg_IA5             = 'IA-5';          { koduje ITA-2 spravu do binarnej podoby - inverzneho patbitoveho kodu }
           cfg_ITA2_ASCII      = 'ITA-2 ASCII';   { koduje ICAO spravy v textovom formate bez ITA2 oddelovacov a NL }
           cfg_ITA2_BIN        = 'ITA-2 BIN';     { koduje ITA-2 spravu do binarnej podoby - inverzneho patbitoveho kodu }
