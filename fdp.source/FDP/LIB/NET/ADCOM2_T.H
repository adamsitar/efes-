    type  U8BIT_15    = TX25adr;   { array[0..14]  of U8BIT; }
          U8BIT_32    = array[0..31]  of U8BIT;


          P_U8BIT     = ^U8BIT;    { ALL MUST BE FAR !!!! }

          P_U8BIT_15  = ^U8BIT_15;
          P_U8BIT_32  = ^U8BIT_32;


          U8BIT_107 = array[0..106] of U8BIT;
          U8BIT_109 = array[0..108] of U8BIT;
          U8BIT_128 = array[0..127] of U8BIT;
          U8BIT_300 = array[0..299] of U8BIT;
          U8BIT_512 = array[0..511] of U8BIT;
          U8BIT_528 = array[0..527] of U8BIT;
          U16BIT_53 = array[0..52]  of U16BIT;
          U32BIT_26 = array[0..25]  of U32BIT;

          READ_DATA = array[0..MAX_PACKET_SIZE-1] of U8BIT;

         { X25_PACKET_512  = array[0..511] of U8BIT; }


          {$IFDEF MC68K}
            ACPTR  =  U32BIT;
          {$ELSE}   { USR_STRUCT }
            ACPTR  =  U16BIT;    { Size of a pointer on the adapter card }
          {$ENDIF}  { USR_STRUCT }


          P_U8BIT_107   = ^U8BIT_107;       { MUST BE FAR !!!! }
          P_U8BIT_109   = ^U8BIT_109;
          P_U8BIT_128   = ^U8BIT_128;
          P_U16BIT_53   = ^U16BIT_53;
          P_U32BIT_26   = ^U32BIT_26;

          P_INIT_GLOB   = ^INIT_GLOB;
          P_PVCINIT     = ^PVCINIT;
          P_DATA_DESC   = ^DATA_DESC;
          P_STATUS_DESC = ^STATUS_DESC;
          P_CALL_DESC   = ^CALL_DESC;


          BISTATS = record
            pcmd    : ACPTR;
            bf      : ACPTR;
            cf      : ACPTR;
            bi_pool : ACPTR;
            cindex  : ACPTR;
            bi_lines: U16BIT;
            bmps    : U16BIT;
            mc      : U16BIT;
            mcpl    : U16BIT;
            bw      : U16BIT;
            nbc     : U16BIT;
            nff     : U16BIT;
            fcnt    : U16BIT;
            bp      : ACPTR;
            bph     : ACPTR;
            ubt     : U16BIT;
            lbt     : U16BIT;
            bcnt    : U16BIT;
          end;


          CMDINTFC = record
	    a,b,c,d: U32BIT;
          end;


          { --------------------------------
            INITIALIZATION TABLE FOR LEVEL 2
            תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
          }

          INITAB_L2 = record

	    max_frame_size ,        {  'max_frame_size' includes
				       anything the upper levels
				       would expect from L2

				       For example, with a packet
				       (level 3 X.25) size of 128,
				       'max_frame_size' should be
				       set to 131 or 132               }

	    clock_rate    ,         {  Baud rate generator clock rate
				       in KiloHertz (KHz).
                                       For some versions of the
				       AdCom 2-I (older versions)
				       this value is the frequency
				       delivered to the card through
				       the expansion bus.  For a
				       normal, everyday, 8-MHz IBM AT
				       this value should be 8000; for
				       those older 'PC' types it
				       should be 4770.                 }

	    t1_time   ,             {  retransmission timer value --
				       20 ticks per second

				       Generally set to
				       60 ticks = 3 seconds.           }

	    t2_time   ,             {  Acnkowledgement timer value --
				       20 ticks per second

				       Generally set to
				       2 ticks = 0.1 seconds.
				       It must be less than 't1_time'
				       but should be no less than 2

				       See below: 'max_unack'          }

	    t3_time   ,             {  Link idle timer --
				       20 ticks per second

				       Currently implemented as a
				       simple polling timer during
				       data transfer state. The
				       purpose of the timer is to
				       ensure that the link is active.

				       Generally set to
				       150 ticks = 7.5 seconds.
				       It should be greater than
				       't1_time'.
				       A value of 0 (zero) disables
				       this feature.       }

            res_16_1,               {  Reserved;  Must be set to 0.    }
	    res_16_2,               {  Reserved;  Must be set to 0.    }
	    res_16_3 : U16BIT;      {  Reserved;  Must be set to 0.    }

	    n2_cnt,                 {  retransmission count
				       ... used in conjunction with
				       't1_timer'

				       May be set to 20 for
				       some PDNs ... or 3 or 4 if
				       you're impatient about
				       the link. }

	    frame_modulo,           {  8 or 128
                                       Normally 8 ...
				       128 is called 'extended' }

	    frm_window_size,        {  1 .. modulo - 1
                                       Normally about 4, but 7
				       will give the best results,
				       especially with large
				       frame sizes. }

	    max_unack,              {  0 .. frm_window_size
				       maximum frames unacknowledged
				       at any given time

				       0 .. always send ack's
				       1 .. if 1 frame is received,
				       use 't2_timer' to send ack ...
				       if another frame is received
				       before ack is sent, send ack
				       immediately
				       (and so on)
				       frm_window_size .. always let
				       't2_timer' acknowledge frames }

	    tx_speed,               {  1 .. 19
				       This is an encoded value:
				       '18' is 64K bps,
				       '17' is 56K bps,
				       '10' is 1200 bps, etc. }

	    term_mode,              {  1 : DTE / 3 : DCE
				       Normally 1;  3 would
				       be used on one side of the
				       link if two DTEs were
				       to be linked together }

	    con_mode,               {  BITS:  ( 0 means low bit )
				       bit 0 : start sabm
				       bit 1 : accept sabm

	        The above two bits should be set together. It is
	     recommended that both be set 'on' (1).
	        With both at '1', frame level will send SABMs when a
	     'go' command is issued, as well as in other link-resetup
	     situations.  With both at '0', frame level will send SABMs
	     only under resetup situations -- but simply wait patiently
	     when the 'go' command is issued.  This mode could be used
	     when one side is initialized and sent the 'go' before the
	     other side is initialized.  Between initialization and the
	     'go' command, link level will consider itself disconnected,
	     and send the DM response to any SABMs it may receive.
	        Other use of these bits is a subject for further study.

				       bit 2 : check link resetup
					       (do SABM)
					       when DISConnect
					       received, etc.

	        Networks like Telenet would like this bit to be set.
	     Networks like the DDN would not.

				       bit 3 : transmit delay
					       0 = fast
					       1 = slower

	        For highest performance, set this bit to 0;  if,
	     however, the receiving software can't keep up (if there
	     are many 'rejects' or some 'frame rejects'), then the
	     slower mode should be used.


				       Typical values: 3 or 7
                                    }

	    res_8_1,                {   Reserved;  Must be set to 0.    }
	    res_8_2,                {   Reserved;  Must be set to 0.    }
	    res_8_3,                {   Reserved;  Must be set to 0.    }
	    res_8_4,                {   Reserved;  Must be set to 0.    }
	    res_8_5,                {   Reserved;  Must be set to 0.    }
	    res_8_6,                {   Reserved;  Must be set to 0.    }
	    res_8_7,                {   Reserved;  Must be set to 0.    }
	    res_8_8,                {   Reserved;  Must be set to 0.    }
	    res_8_9  : U8BIT;       {   Reserved;  Must be set to 0.    }

          end; { INITAB_L2 }


          { --------------------------------
            INITIALIZATION TABLE FOR LEVEL 3
            תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
          }

          INITAB_L3 = record

            line,                   { line number }
            term_type,              { terminal type, DTE or DCE }
            network,                { type of network to comply with }
            passive,                { indicate passive restart }
            modulo,                 { modulo for this line }
            mbit,                   { enable m bit }
            mbitmode,               { m-bit mode parameter }
            qbit,                   { enable q bit }
            dbit,                   { enable d bit }
            flow:  U8BIT;           { indicate flow control param }

            sdu,                    { maximum tx/rx service data unit }
            tx_max_packet_size,     { max tx packet size for FCP neg. }
            rx_max_packet_size,     { max rx packet size for FCP neg. }
            tx_packet_size,         { default tx packet size }
            rx_packet_size: U16BIT; { default rx packet size }
            tx_max_pkt_window,      { max tx window size for FCP neg. }
            rx_max_pkt_window,      { max rx window size for FCP neg. }
            tx_packet_window,       { default tx window size }
            rx_packet_window,       { default rx window size }
            tx_thruput_class,       { default tx throughput class }
	    rx_thruput_class,       { default rx throughput class }
	    tx_min_thruput_class,   { minimum tx throughput class }
	    rx_min_thruput_class,   { minimum rx throughput class }
	    tx_max_thruput_class,   { maximum tx throughput class }
	    rx_max_thruput_class    { maximum rx throughput class }
                : U8BIT;

	    num_pvc,                { number of pvc's }
	    lic,                    { lowest incoming 1-way svc }
	    hic,                    { highest incoming 1-way svc }
	    ltc,                    { lowest 2-way svc }
	    htc,                    { highest 2-way svc }
	    loc,                    { lowest outgoing 1-way svc }
	    hoc,                    { highest outgoing 1-way svc }
	    t20_time,               { length of t20 timer }
	    t21_time,               { length of t21 timer }
	    t22_time,               { length of t22 timer }
	    t23_time,               { length of t23 timer }
	    t24_time,               { length of t24 timer }
	    t25_time,               { length of t25 timer }
	    t26_time,               { length of t26 timer }
	    t27_time,               { length of t27 timer }
	    t28_time:U16BIT;        { length of t28 timer }
	    r20_count,              { t20 retransmission count }
	    r22_count,              { t22 retransmission count }
	    r23_count,              { t23 retransmission count }
	    r25_count,              { t25 retransmission count }
	    r27_count,              { t27 retransmission count }
	    r28_count,              { t28 retransmission count }

         { facilities }

         { facilities inserted in call packets by X.25 for all calls }
            fcp_negotiate,           { insert flow control parameters }
	    fast_select,             { insert fast select }
	    reverse_charging,        { insert reverse charging }
	    ddnstand,                { insert ddn standard service }

         { facilities agreed to for a period of time }
	    pkt_retran: U8BIT;       { enable packet retransmission }

         { reserved }
	    res_16_1: U16BIT;        { reserved }
	    res_8_1,                 { reserved }
	    res_8_2,                 { reserved }
	    res_8_3,                 { reserved }
	    res_8_4,                 { reserved }

	    res_8_5: U8BIT;          { reserved }
          end;{ INITAB_L3 }


          INIT_GLOB = record
	    Init_L2 : INITAB_L2;
	    Init_L3 : INITAB_L3;
	  end;


          PVCINIT = record
            tx_wdw_size,         { modified tx window size for this channel }
            rx_wdw_size:U8BIT;   { modified rx window size for this channel }
            tx_pkt_size,         { modified tx packet size for this channel }
            rx_pkt_size:U16BIT;  { modified rx packet size for this channel }
            tx_tput_class,       { modified tx thruput class for this chan }
            rx_tput_class:U8BIT; { modified rx thruput class for this chan }
            net_lci,
            pvc_res_1:U16BIT;
          end;


          INFO_STRUCT = record
            reserved,             { for 32-bit alignment}
	    length       : U16BIT;
	    packet_type,
  	    qmd_bits,
	    cause,
	    diag         : U8BIT;
	  end;


          DATA_DESC = record
            line,
	    chan : U16BIT;
	    info : INFO_STRUCT;    { Information about type and size of packet}
	    data : P_U8BIT;        { data }
	  end;


          LNSTATS = record
	    num_call_req,          { number of call requests made }
	    num_inc_calls,         { number of incoming calls received }
	    num_diag,              { number of diagnostic packets received }
	    res_16_1:U16BIT;       { reserved }
          end;


          CHSTATS = record
	    num_data_tx,           { number of data packets transmitted }
	    num_data_rx,           { number of data packets received }
	    num_cntl_tx,           { number of control packets transmitted }
	    num_cntl_rx,           { number of control packets received }
	    tx_wdw_max_cnt,        { number of times tx window max'd out }
	    rx_wdw_max_cnt,        { number of times rx window max'd out }
	    num_rej_tx,            { number of reject packets transmitted }
	    net_lci:  U16BIT;      { network lci }
          end;


          L3CSTATS = CHSTATS;

          L3LSTATS = LNSTATS;

          STATS = record
	    cstat : L3CSTATS;	   { channel information }
	    lstat : L3LSTATS;      { line information    }
	    l2    : U8BIT_128;     { level 2 data        }
          end;


          CALL_DESC = record
            callg_len : U8BIT;     { Calling address length      }
            calld_len : U8BIT;     { Called address length       }
            callg_adr : U8BIT_15;  { Calling address             }
            calld_adr : U8BIT_15;  { Called address              }
            fac_len   : U8BIT;     { Length of facility data     }
            usr_len   : U8BIT;     { Length of user data         }
            fac_data  : U8BIT_109; { Facilities Data             }
            usr_data  : U8BIT_128  { User data                   }
          end;

          STATUS_DESC = record
            line,		   { line want information on    }
	    chan,	 	   { channel want information on }
            level : U16BIT;        { number of bytes of data     }
            ustat : STATS;
          end;


          FACILITIES = record

           { CCITT 1980 defined facilities }

             fcp_packet_rx: U16BIT;
             fcp_packet_tx: U16BIT;
    		      { 0 = use default receive/transmit packet sizes from
		       *	   the l3 initialization table
		       * 16, 32, 64, 128, 256, 512, 1024 (for CCITT 1980) and
		       * 2048, 4096 (for CCITT 1984) bytes (octets) in decimal
		       }
             fcp_window_rx: U8BIT;
             fcp_window_tx: U8BIT;
    		      { 0 = use default receive/transmit window sizes from
		       *     the l3 initialization table
		       * 1-7 (for modulo 8),  1-127 (for modulo 128) in decimal
		       }
             throughput_rx: U8BIT;
             throughput_tx: U8BIT;
    		      { 0 = use default receive/transmit throughput from
		       *     the l3 initialization table
		       * 3 = 75        8 = 2400
		       * 4 = 150       9 = 4800
		       * 5 = 300      10 = 9600
		       * 6 = 600	    11 = 19200
		       * 7 = 1200     12 = 48000  bits per second in decimal
		       }
             cug_req  : U8BIT;
             cug_index: U16BIT;
    		      { cug_req = 0, no closed user group
		       * cug_req = 1, use closed user group in cug_index
		       * cug_req = 2, use extended closed user group in cug_index
		       * closed user group in BCD:
		       * $00-$99 (for CCITT 1980 and 1984 basic format )
		       * $0000-$9999 (for CCITT 1984 extended format)
		      }
             bcug_req: U8BIT;
             bcug_index: U16BIT;
    		      { bcug_req = 0, no bilateral closed user group
		       * bcug_req = 1, use bilateral closed user group in
				       bcug_index
		       * $0000-$9999 bilateral closed user group in BCD
		      }
             reverse_charge: U8BIT;
    		      { 0 = don't request/allow reverse charging
		       * 1 = reverse charging requested/allowed
		      }
             fast_select: U8BIT;
    		      { 0 = don't use fast select
		       * 1 = use fast select, response restriction (clear only)
		       * 2 = use fast select, no restriction (clear or call
			     accept)
		      }
             rpoa_req    : U8BIT;
             rpoa_length : U16BIT;
             rpoa        :U16BIT_53;
    		      { rpoa_req = 0, no recognized private operating agencies
		       * rpoa_req = 1, use basic format for RPOA
		       * rpoa_req = 2, use extended format for RPOA
		       * for basic format (CCITT 1980 and 1984)
		       *   rpoa_length holds the rpoa transit group
		       *   $0000-$9999 (RPOA transit group in BCD)
		       * for extened format (CCITT 1984)
		       *   rpoa_length is the length in bytes (octets) and has
		       *   the value n X 2, where n is the number of RPOA transit
		       *   networks
		       *   rpoa contains the RPOA transit networks in the order
		       *   they should be traversed
		       *   $0000-$9999 (RPOA transit group in BCD)
		       }


           { CCITT 1984 defined facilities }
             cugoas_req: U8BIT;
             cugoas_index: U16BIT;
    		      { cugoas_req = 0, no closed user group with outgoing
		       *                 access selection
		       * cugoas_req = 1, use cugoas in cugoas_index
		       * cugoas_req = 2, use extended cugoas in cugoas_index
		       * closed user group in BCD:
		       * $00-$99 (for CCITT 1980 and 1984 basic format )
		       * $0000-$9999 (for CCITT 1984 extended format)
		       }
             network_user_id: U8BIT;
             nui_length: U8BIT;
             nui_data:U8BIT_107;
    		      { network_user_id = 0, don't use network user id
		       * network_user_id = 1, use network user id that follows
		       * nui_length is the length in bytes (octets) of the
		       *     network user identification
		       * nui_data holds the network user identification
		       }
             charging_info_req: U8BIT;
             ci_monetary: U8BIT;
             ci_monetary_info:U8BIT_107;
             ci_segcount: U8BIT;
             ci_segcount_info:U32BIT_26;
             ci_duration: U8BIT;
             ci_duration_info :U32BIT_26;
    		      { charging_info_req = 0, don't request charging info
		       * charging_info_req = 1, request charging information
		       * for receiving charging information (in clear request
		       * or clear confirm)
		       *     ci_monetary is the length in bytes (octets) of the
		       *         monetary info
		       *     ci_monetary_info is the charging information
		       *     ci_segcount is the length in bytes (octets) and has
		       *         the value n X 8, where n is the number of
		       *         different tariff periods
		       *     ci_segcount_info is the number of segments received
		       *         and sent by the DTE for each tariff period
		       *         $00000000-$99999999 received in BCD
		       *         $00000000-$99999999 sent in BCD
		       *     ci_duration is the length in bytes (octets) and has
		       *         the value n X 4, where n is the number of
		       *         different tariff periods
		       *     ci_duration_info is the number of days, hours,
		       *         minutes and seconds for each tariff period
		       *         $00-$99 days in BCD
		       *         $00-$99 hours in BCD
		       *         $00-$99 minutes in BCD
		       *         $00-$99 seconds in BCD
		       }
             clamn: U8BIT;
             clamn_code: U8BIT;
    		      { clamn = 0, don't use called line address modified
                       *            notification
    		       * clamn = 1, use called line address modified notification
    		       * for sending, clamn_code indicates the DTE originated
		       *     value and has the range 128-255 decimal
		       * for receiving, clamn_code gives a reason and has the
		       *     values:  7 decimal, hunt group
		       *              1 decimal, busy
		       *              9 decimal, out of order
		       *             15 decimal, systematic redirection
		       }
             crn : U8BIT;
             crn_reason: U8BIT;
             crn_addrlen: U8BIT;
             crn_address:U8BIT_15;
    		      { crn, call redirection notification is the length in
		       *      bytes (octets) and has a value of n + 2, where n
		       *      is the number of bytes (octets) to hold the
		       *      originally called DTE address
		       * crn_reason is the reason for the call redirection and
		       *      has the value:  1 decimal, busy
		       *                      9 decimal, out of order
		       *                     15 decimal, systematic redirection
		       * crn_addrlen is the address length of the originally
		       *     called DTE and has the range: 0-15 decimal
		       * crn_address is the originally called DTE address in
		       *     ASCII
		       }
             transit_delay: U8BIT;
             td_time: U16BIT;
    		      {* transit_delay = 0, no transit delay
		       * transit_delay = 1, transit delay indicated in td_time
		       * td_time indicates the transit delay in milliseconds and
		       * has the range: $0000-$9999 in BCD
		       }

           { Non-X.25 facilities }
       	     ddn_standard: U8BIT;
		      {* ddn_standard = 0, no ddn standard service
		       * ddn_standard = 1, ddn standard service requested
		       }
    	     ddn_precedence: U8BIT;
    	     ddn_precedence_type: U8BIT;
		      {* ddn_precedence = 0, no ddn precedence
		       * ddn_precedence = 1, ddn precedence indicated in
		       *                     ddn_precedence_type
		       * ddn_precedence_type indicates the type of precedence
		       * for the call and has the range 0-3
		       }

           { CCITT-specified DTE facilities to support OSI network service }
    	     cgae: U8BIT;
    	     cgae_len: U8BIT;
    	     cgae_addr:U8BIT_32;
		      {* cgae = 0, no calling address extension
		       * cgae = 1, calling address extension
		       * cgae_len indicates the length of the address in bytes
		       *     (octets)
		       * cgae contains the address in ASCII
		       }
    	     cdae: U8BIT;
    	     cdae_len: U8BIT;
    	     cdae_addr:U8BIT_32;
		      {* cdae = 0, no called address extension
		       * cdae = 1, called address extension
		       * cdae_len indicates the length of the address in bytes
		       *     (octets)
		       * cdae contains the address in ASCII
		       }
    	     qos_mtc: U8BIT;
    	     qos_mtc_called: U8BIT;
    	     qos_mtc_calling: U8BIT;
		      {* qos_mtc = 0, no quality of service negotiation- minimum
		       *    throughput class
		       * qos_mtc = 1, quality of service negotiation- minimum
		       *    throughput class in qos_mtc_called, qos_mtc_calling
		       * qos_mtc_called contains the called throughput class,
		       * qos_mtc_calling contains the calling throughput class
		       * 3 = 75        8 = 2400
		       * 4 = 150       9 = 4800
		       * 5 = 300      10 = 9600
		       * 6 = 600	    11 = 19200
		       * 7 = 1200     12 = 48000  bits per second in decimal
		       }
    	     qos_etetd: U8BIT;
    	     qos_etetd_cum: U16BIT;
    	     qos_etetd_req: U16BIT;
    	     qos_etetd_max: U16BIT;
		      {* qos_etetd = 0, no quality of service negotiation-
		       *    end-to-end transit delay
		       * qos_etetd = 1, quality of service negotiation-
		       *    end-to-end transit delay, cumulative
		       * qos_etetd = 2, quality of service negotiation-
		       *    end-to-end transit delay, optional requested etetd
		       * qos_etetd = 3, quality of service negotiation-
		       *    end-to-end transit delay, optional max accpt etetd
		       * $0000-$9999 cumulative transit delay in BCD
		       * $0000-$9999 requested end-to-end transit delay in BCD
		       * $0000-$9999 maximum acceptable end-to-end transit
		       *     delay in BCD
		       }
    	     edn: U8BIT;
		      {* edn = 0, no expedited data negotiation
		       * edn = 1, expedited data negotiation
		       }
          end;


 (*
          TVS = record
            STAT : U16BIT;
            MESS : STRING;
          end;

          PTVS = array[0..14] of TVS;

          PTVC = array[0..15] of TVS;

          CHARDIGITS = set of '0'..'9';

          RECFUNCTYPE = FUNCTION(CHAN:S16BIT):S16BIT;

          Send_DESC = record
               callg_len : U8BIT;
               calld_len : U8BIT;
              callg_padr : U8BIT_15;
              calld_padr : U8BIT_15;
                data_len : U16BIT;
                    data : P_U8BIT;          {PACKET_ARRAY;}
             end;

          DATA_BUFPTR = ^DATA_BUFFER;
          DATA_BUFFER = record
                  CALLG_PADR : str15;
                  CALLD_PADR : str15;
                        SIZE : WORD;
                        DATA : P_U8BIT;
                       VALID : BOOLEAN;
                        NEXT : DATA_BUFPTR;
                end;
 *)

