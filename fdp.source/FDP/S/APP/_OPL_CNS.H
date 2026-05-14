    type   msOPLdata    = ( msHB,
                            msLAM,

                            msFPL, msCHG, msCNL, msDLA, msCLR,
                            msABI, msACT,
                            msDEP, msARR, msCPL, msEST,

                            msAUP, msAUM, msASM,
                            msRTZ
                          );


    const  hd_OPL4      : array[msHB..msRTZ] of Thead_ICAO =

                          ( opl_HEARTBEAT,

                            'LAM',

                            'FPL',  { ICAO }
                            'CHG',
                            'CNL',

                            'DLA',
                            'CLR',

                            'ABI',  { OLDI }
                            'ACT',

                            'DEP',  { AMA  }
                            'ARR',
                            'CPL',
                            'EST',

                            'AUP','AUM','ASM',
                            'RTZ'
                          );


    const  hd_OPL_LAM   : array[msFPL..msRTZ] of Thead_ICAO =

                          ( 'FPL',  { ICAO }
                            'CHG',
                            'CNL',

                            'DLA',
                            'CLR',

                            'ABI',  { OLDI }
                            'ACT',

                            'DEP',  { AMA  }
                            'ARR',
                            'CPL',
                            'EST',

                            'AUP','AUM','ASM',
                            'RTZ'
                          );


    const  OPLcfg   = 'OPL'+ext_ini;

           cfg_STREAM = 'STREAM';

           OPL__SAVE_STREAM    : bool = true;
           OPL__LAM_NOT_FOUND  : bool = false;
           OPL__UNCOMPLETE_PKT : bool = true;


           OPL__PROCESS_AUP    : bool = true;
           OPL__REQUEST_AUP    : bool = true;
           OPL__REQUEST_AUPi   : int  = 30;
           OPL__REQUEST_AUP_lo        = {$IFDEF DEBUG} 1 {$ELSE} 5 {$ENDIF};
           OPL__REQUEST_AUP_hi        = 60;

           OPL__UPDATE_CNL_PRS : bool = true;


           OPL__PROCESS_RTZ    : bool = true;
           OPL__REQUEST_RTZ    : bool = true;
           OPL__REQUEST_RTZi   : int  = 30;
           OPL__REQUEST_RTZ_lo        = {$IFDEF DEBUG} 1 {$ELSE} 5 {$ENDIF};
           OPL__REQUEST_RTZ_hi        = 60;

           {OPL__LAM_NOT_FOUND  : bool = true;}

           OPL__PROCESS_ASM    : bool = true;
           OPL__PROCESS_ASMfda : bool = true;



    const  writeln_OPL           : bool = true;
           archive_OPL           : bool = true;
           writeln_OPL_utc       : bool = true;
           writeln_OPL_HeartBeat : bool = true;

           cl_OPL_rec            : byte = 51;
           cl_OPL_send           : byte = 47;
           cl_OPL_err            : byte = red;




    {$IFDEF OPL_EXT_UDP} {$IFDEF PCTCP}
     const UDP_PORT_OPL : TUDP_port = (port   : $5109;
                                       desc   : -1;
                                       flag   : NET_FLG_NONBLOCKING {NET_FLG_};
                                       asynch : false
                                      );

           OPLadr_ip_s : TIPname = '';
           OPLadr_ip   : TIPadr  = 0;
    {$ENDIF} {$ENDIF}



    const  aup_hour : int       = 04;           { cas vyziadania planov }
           aup_min  : int       = 05;
           aum_last : int       = 3;            { limit pre vyhodnotenie nedorucenia celej spravy AUM/AUP }

           cfg_PRS_hour         = 'H-RPL';
           cfg_PRS_min          = 'M-RPL';

           cfg_alt_FL5min       = 'FL5-MIN';
           cfg_alt_FL5max       = 'FL5-MAX';


    type   TsREQ = record
             date : TDate;  { datum poslednej vybavenej ziadosti }
             is   : bool;   { bola odoslana ziadost o AUP, caka sa na spracovanie }
             next : bool;   { ma prist dalsi paket }
             last : real;   { cas, kedy bol prijaty posledny paket }
           end;


    const  OPL_coor_info = hd_CPL+', '+hd_EST+', '+inf_FPLC;
