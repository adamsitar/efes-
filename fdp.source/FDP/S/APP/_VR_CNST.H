
    type   msData        = ( {msLAM,}
                             msCPL, msEST
                           );


    const  hd_VRL4       : array[msCPL..msEST] of Thead_ICAO =
                           ( 'CPL',
                             'EST'
                           );


    const  VERAn_  = 'VERA';
           VERAcfg = VERAn_+ext_ini;


    const  writeln_VERA  : bool = true;
           archive_VERA  : bool = true;
           utc_VERA      : bool = true;

           cl_VERA             {: byte} = 37;   { clGRa; }
           cl_VERA_system_mess {: byte} = 41;   { clGR7; }
           cl_VERA_err         {: byte} = red;



    const  VERA_BUFFER_SIZE   = 3;
           VERA_PACKET_SIZE   = 1024 + 4 {512};

    type   PVERApkt = ^TVERApkt;
           TVERApkt = record
             poc : word;
             buf : array[0..VERA_PACKET_SIZE-1] of char
           end;

    {$IFDEF PCTCP}
     const UDP_PORT_VERA : TUDP_port = (port   : $5110;
                                        desc   : -1;
                                        flag   : NET_FLG_NONBLOCKING;
                                        asynch : false
                                       );

           VERAadr_ip_s  : TIPname = '';
           VERAadr_ip    : TIPadr  = 0;
    {$ENDIF}
