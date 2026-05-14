  const  VER = '4.21';

         {$IFDEF MC68K}
          ! nemoze byt.
            MAX_LINE_VAL    =  3;
            NUM_LINES       =  (MAX_LINE_VAL + 1);

            MAX_CHAN_VAL    =  128;
            NUM_CHANS       =  (MAX_CHAN_VAL + 1);
            TOTAL_CHANS     =  (512 + NUM_LINES);

            MAX_X25_LCI     =  255;
            MAX_PACKET_SIZE =  $0400;
        {$ELSE}
            MAX_LINE_VAL    =  1;
            NUM_LINES       =  (MAX_LINE_VAL + 1);

            MAX_CHAN_VAL    =  256;
            NUM_CHANS       =  (MAX_CHAN_VAL + 1);
            TOTAL_CHANS     =  (256 + NUM_LINES);

            MAX_X25_LCI     =  4095;
            MAX_PACKET_SIZE =  X25_PACKET_SIZE;
        {$ENDIF}


        { Level id's for the command field }

          L4ID         =     4;
          L3ID         =     3;
          L2ID         =     2;

          L2_BAD_ARG   =   $90;

          L3S_SIGNAL   =   $20;
          L3S_ERROR    =   $21;


        { signals from level 2 }

          SIG_ALLOC1    =  160;     { 'severe' warning ... overload }
          SIG_RSRCERR1  =  159;     { crash error }
          SIG_RSRCERR2  =  158;     { crash error }
          SIG_WRONG_STATE= 157;     { wrong state for lev-III command }


        { command status return values from level 2 }

          LINK_CTL_DOWN   = 132;     { control signals were forced off }
	                             { (due to second 'end' command) }
          WRONG_STATE     = 156;     { 'init' or 'end' in wrong state }
          VAL_DCE_DTE     = 155;
          VAL_MODULO      = 154;
          VAL_WINDOW_SIZE = 153;
          VAL_FRAME_SIZE  = 152;
          VAL_TX_SPEED    = 151;
          VAL_CLOCK_RATE  = 150;


          DCE             = 3;
          DTE             = 1;


         { CCITT defined Packet Types }

          CALL_REQUEST    = $0b;
          CALL_ACCEPTED   = $0f;
          CLEAR_REQUEST   = $13;
          CLEAR_CONFIRM   = $17;
          DATA            = $00;
          INTERUPT        = $23;
          INTR_CONFIRM    = $27;
          RR              = $01;
          RNR             = $05;  {Remote not ready}
          REJ             = $09;
          RESET_REQUEST   = $1b;
          RESET_CONFIRM   = $1f;
          RESTART_REQUEST = $fb;
          RESTART_CONFIRM = $ff;
          DIAGNOSTIC      = $f1;
          REG_REQUEST     = $f3;
          REG_CONFIRM     = $f7;



        { -- Status returned by L3 command completes -- }

        { General good status }
          GOOD              =      $00;

        { General bad status }
          BAD_CMD           =      255;
          BAD_ARG           =      254;
          BAD_LINE          =      253;
          BAD_GO            =      252;
          BAD_LCI           =      251;
          BAD_INTERNAL      =      250;
          BAD_PACKET        =      249;
          BAD_ADDRESS       =      248;
          BAD_FACILITY      =      247;
          BAD_USERDATA      =      246;

        { status for INIT }
          INIT_BAD          =      245;
          INIT_NO_CHANS     =      244;
          INIT_NOT_PVC      =      243;
          INIT_BAD_CHANNEL  =      242;
          INIT_TERMTYPE     =      241;
          INIT_NETWORK      =      240;
          INIT_MODULO       =      238;
          INIT_TX_WDW_ERR   =      237;
          INIT_RX_WDW_ERR   =      236;
          INIT_TX_PKT_ERR   =      235;
          INIT_RX_PKT_ERR   =      234;
          INIT_TX_TPUT_ERR  =      233;
          INIT_RX_TPUT_ERR  =      232;
          INIT_NUMPVC       =      231;
          INIT_LIC          =      230;
          INIT_HIC          =      229;
          INIT_LTC          =      228;
          INIT_HTC          =      227;
          INIT_LOC          =      226;
          INIT_HOC          =      225;
          INIT_FACILITY     =      223;

        { status for GO }

        { status for Call REQ  }
          CHANNEL_AVAIL         =  222;
          NO_CHANNEL_AVAIL      =  221;
          FACILITY_VIOLATION    =  220;
          REG_IN_PROGRESS       =  219;

        { status for Call ACPT }

        { status for WRITE }
          TX_QUE_NOT_FULL       =  218;
          TX_QUE_FULL           =  217;
          TX_QUE_EXCEEDED       =  216;
          PKT_TOO_BIG           =  215;
          NOT_ENOUGH_BUF        =  214;

        { status for CLEAR }
          CLEAR_WAITING         =  213;
          CLEAR_COMPLETE        =  212;

        { status for Registration REQ }
          BAD_REGISTRATION      =  211;
          REG_INVALID_VC        =  210;

        { status for RESET }

        { status for END }

        { status for INTerrupt }
          INT_NOT_READY         =  209;
          BAD_INTERRUPT         =  208;

        { status for STATistics }

        { L3S_ commands }
        { status for L3S_ERROR command }

        { status for L3S_SIGNAL command }
        { Level 3 signals }
          LINE_RESTART          =  207;
          R20_COUNTOUT          =  206;
          R22_COUNTOUT          =  205;
          R23_COUNTOUT          =  204;
          R28_COUNTOUT          =  203;
          CRASH                 =  202;
          DISCONNECTED          =  201;
          LINK_ERROR            =  200;
          LINK_ERR_CTL          =  130;
          LINK_ERR_TXCLK        =  131;

        { Errors returned from Bus Interface software }
          NO_ICHAN              =  199;   { Not enough channels to init. }
          NO_IBUF               =  198;   { Not enough buffers to init. }
          NO_FMEM               =  197;   { Not enough memory for pool. }
          NO_X25BUF             =  196;   { No X.25 buffer for command. }
          NO_BIBUF              =  195;   { No BI buffers for command. }
          NO_BICHAN_AVAIL       =  194;   { No BI channels for call. }
          BI_PKT_TOO_LONG       =  193;   { Data passed to BI too long. }
          BI_BAD_CHAN           =  192;   { X.25 passed a bad channel. }
          BI_NOCHAN             =  191;   { CALL REQEUST but no bi chans. }
          BI_CHAN_CLOSED        =  190;   { BI_READ on closed channel. }

        {$IFDEF	ENOTCONN}
          {$UNDEF ENOTCONN}
        {$ENDIF}

	  ENOTCONN              =  BI_CHAN_CLOSED;
	  BI_CHAN_EMPTY         =  189;   { BI_READ on empty channel. }


        { CRASH Errors returned from X.25 }
          ERR_PKT_ERROR  = 188;    { Error in pkt variable }
          ERR_L2         = 187;    { Error from level 2 }
          ERR_TIMERT20   = 186;    { Timeout error }
          ERR_TIMERT21   = 185;    { Timeout error }
          ERR_TIMERT22   = 184;    { Timeout error }
          ERR_TIMERT23   = 183;    { Timeout error }
          ERR_TIMERT24   = 182;    { Timeout error }
          ERR_TIMERT25   = 181;    { Timeout error }
          ERR_TIMERT26   = 180;    { Timeout error }
          ERR_TIMERT27   = 179;    { Timeout error }
          ERR_TIMERT28   = 178;    { Timeout error }
          ERR_TIMER      = 177;    { General timer error }
          ERR_BAD_STATE  = 176;    { Channel in wrong state, crash }
          ERR_LMALLOC    = 175;    { Lmalloc returned a NULL pointer }
          ERR_NULLPTR    = 174;    { A NULL pointer caused crash }
          ERR_NULLPTR2   = 129;    { A NULL pointer caused crash }
          ERR_PKTTIMER   = 173;    { Error starting timer }
          ERR_ENCODE     = 172;    { Error in packet encoder }

        { Driver Errors		}

   	  ENOTINIT	 = 171;	   { X.25 is not initialized.           }
  	  EACTIVE	 = 170;	   { Command already in progress.       }
  	  ENOTACTIVE	 = 169;	   { No command in progress or issued.  }
  	  EBADARG	 = 168;	   { Passed a bad argument to driver.   }
  	  ENOCOMMAND	 = 167;	   { Nothing in global or channel fifo. }

        {$IFDEF EWOULDBLOCK}
          {$UNDEF EWOULDBLOCK}
        {$ENDIF}

  	  EWOULDBLOCK    = 165;    { Network busy, command would block. }
  	  EBUFSMALL 	 = 164;	   { Buffer too small for data. }
          EXNTO		 = 163;	   { Board timed out on command. }

          QMASK	         = $80;    { Mask to set/test the Q bit. }
          DMASK	         = $40;	   { Mask to set/test the D bit. }
          MMASK          = $10;    { Mask to set/test the M bit. }


 	  X_INIT	 = $01;
 	  X_PVCINIT	 = $02;
 	  X_GO		 = $03;
 	  X_GCMD	 = $04;
 	  X_READCH	 = $05;
 	  X_OPEN	 = $06;
 	  X_ACPT	 = $07;
 	  X_CLOSE	 = $08;
 	  X_WRITE	 = $09;
 	  X_INT		 = $0a;
 	  X_RESET	 = $0b;
 	  X_END		 = $0c;
 	  X_STATUS	 = $0d;
          X_BISTATUS     = $0e;
          RESET2I        = $0f;
