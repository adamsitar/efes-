
    type   msData        = (
                             msLAM,
                             msFPL, msCHG, msCNL, msDLA,
                             msABI, msACT, msPAC, msREV,
                             msDEP, msARR, msCPL, msEST
                           );


    const  hd_CAL4       : array[msLAM..msEST] of Thead_ICAO =

                           (
                             'LAM',

                             'FPL',  { ICAO }
                             'CHG',
                             'CNL',
                             'DLA',

                             'ABI',  { OLDI }
                             'ACT',
                             'PAC',
                             'REV',

                             'DEP',
                             'ARR',
                             'CPL',
                             'EST'
                           );


    const  hd_CALAM      : array[msEST..msEST] of Thead_ICAO =
                           (
                             'EST'
                           );


    const  CAMUScfg = 'CAMUS'+ext_ini;

           CAMUS_15a     : bool = true;
           cfg_CAMUS_15a = '15a';

           ASTA_src      : bool = false;
           cfg_ASTA_src  = 'ASTA-INTERFACE';

           cfg_EXC_NDB   = 'EXCLUDE-POINTS';
           max_EXC_NDB   = 20;


    const  writeln_CAMUS  : bool = true;
           archive_CAMUS  : bool = true;
           utc_CAMUS      : bool = true;

           cl_CAMUS             {: byte} = 39;   { clGRa; }
           cl_CAMUS_system_mess {: byte} = 41;   { clGR7; }
           cl_CAMUS_err         {: byte} = red;


    const  CAMUS_coor_info = ''
                             {$IFDEF LKPR_MACC} +', '+inf_FPLM+{', '+inf_FPLO+}', '+inf_PRS {$ENDIF}
                             {$IFDEF LZIB_MACC} {+', '+inf_FPLM+', '+inf_FPLO }           {$ENDIF}
                             ;


    {$IFDEF CONNECT_TO_FDPOX} {$IFDEF PCTCP}
     const UDP_PORT_FDPOX : TUDP_port = (port   : $5111;
                                         desc   : -1;
                                         flag   : NET_FLG_NONBLOCKING {NET_FLG_};
                                         asynch : false
                                        );

           FDPOXadr_ip_s : TIPname = '';
           FDPOXadr_ip   : TIPadr  = 0;
    {$ENDIF} {$ENDIF}

