    const  aftnSOH = MTK_2_SOT;
           aftnEOT = MTK_2_EOT;

    type   msAFTNdata    = ( msFPL, msCHG, msDLA, msCNL,
                             msDEP, msARR
                           );

    const  hd_AFTN       : array[msFPL..msARR] of Thead_ICAO =

                           ( 'FPL',  { ICAO }
                             'CHG',
                             'DLA',
                             'CNL',

                             'DEP',  { AMA  }
                             'ARR'
                           );


    const  AFTNcfg   = 'AFTN'+ext_ini;
           extAFTN   = 'AFN';
           extAFTNb  = 'AFB';

           cfg_AFTN  = 'AFTN';
           cfg_EST   = 'EST';


    const  AFTN_IBUFF_SIZE   = {$IFDEF DEBUG} 5 {$ELSE}  15  {$ENDIF};
           AFTN_PBUFF_SIZE   = {$IFDEF DEBUG} 30 {$ELSE} 30 {$ENDIF};
           AFTN_MESSAGE_SIZE  = 2048;

    type   PAFTNpkt = ^TAFTNpkt;
           TAFTNpkt = record
             p : word;
             b : array[0..AFTN_MESSAGE_SIZE-1] of char
           end;


    const  writeln_AFTN           : bool = true;
           archive_AFTN           : bool = true;
           archive_AFTN_bin       : bool = false;

           writeln_AFTN_utc       : bool = true;
           writeln_AFTN_HeartBeat : bool = false;

           cl_AFTN_rec            : byte = clGRe;
           cl_AFTN_send           : byte = clGRf;
           cl_AFTN_err            : byte = red;

           cfg_archive_AFTN_bin   = 'AFTN STREAM';
           cfg_ALIAS_NODE         = 'ALIAS NODE';

           cfg_HeartBeat_ID       = 'HEARTBEAT ID';        { obsah hlavicky heartbeatu }
           cfg_HeartBeat_PERIODE  = 'HeartBeat PERIODE';   { }
           cfg_HeartBeat_MIN      = 'HeartBeat MIN';       { }


    const  aftn_MASTER_LINE : bool = true;
           aftn_DUAL_LINE   : bool = true;


    const  power_AFTN : bool = true;
