     const  TFLAG_INITED	= $01;  { Tag has been initialized? }
            TFLAG_LOCKED	= $02;  { Tag is unmodifiable? }
            TFLAG_MULTI	        = $04;	{ Multiple values supported? }
            TFLAG_FUNC	        = $08;  { We need to call a function }
            TFLAG_LATCH	        = $10;	{ Lock after initialization }
            TFLAG_REQUIRED 	= $20;	{ Necessary for kernel to start }
            TFLAG_STRING	= $40;	{ This is a string value }
            TFLAG_LAST	        = $80;	{ Marker for last tag in array }

          { Kernel configuration values }

            TAG_SMALL_PKTS	= $01;  { # of small packets, (size = 2 }
            TAG_LARGE_PKTS	= $02;  { # of large packets, (size = 2 }

          { Sump'n for IP }

            TAG_TCPCONS	        = $04; { # of TCP connects,  (size = 2 }
            TAG_UDPCONS	        = $05; { # of UDP connects,  (size = 2 }
            TAG_DOMAIN	        = $07; { Def domain <string>, }
	                               { (size < DOMAIN_STRLEN }
            TAG_HOSTTABLE	= $08; { Host table <string>, }
			               { (size < HTABLE_STRLEN }
            TAG_DNS_SRVS	= $09; { Domain servers <IP addr array>, }
				       { (size <= MAX_DNS_SRVS * 4 }
            TAG_DEF_WINDOW	= $0A; { Def TCP window size, (size = 2 }
            TAG_DEF_LOWWIN	= $0B; { TCP low-water mark, (size = 2 }
            TAG_IP_TOS	        = $0C; { IP Type-of-service, (size = 1 }
            TAG_SM_PKT_SIZ	= $0D; { Small buffer size,  (size = 2 }
            TAG_IP_EXT_SEC	= $0E; { IP extended security, (size = 1 }
            TAG_IP_BAS_SEC	= $0F; { IP basic security,	 (size = 1 }
            TAG_IP_OPTIONS	= $10; { IP options <byte array>, }
				       { (size <= IP_OPT_MAXLEN }
            TAG_DEBUG_FLAGS	= $11; { Debugging flags,	 (size = 2 }
            TAG_OPT_FLAGS	= $12; { IP option flags,	 (size = 1 }
            TAG_USE_EMM         = $13; { Expanded mem toggle,  (size = 1 }
            TAG_SERIAL_NUM	= $14; { Serial number,	 (size = 6 }
            TAG_IPSO_PORTS	= $15; { IP security ports }
				       { <struct opt_port array>, }
				       { (size <= MAX_PORT * 6 }
            TAG_IP_TTL	        = $16; { Default IP TTL,	 (size = 2 }
            TAG_IP_MTU	        = $18; { IP MTU,		 (size = 2 }
            TAG_ODI_PKTS	= $1F; { Packets to give ODI,  (size = 2 }
            TAG_HOST_DS	        = $20; { Host DS (for VxD,	 (size = 2 }
            TAG_VxD_0	        = $21; { VxD tag			    }
            TAG_VxD_1	        = $22; { VxD tag	reserved	    }
            TAG_VxD_2	        = $23; { VxD tag	reserved	    }
            TAG_VxD_3	        = $24; { VxD tag	reserved	    }
            TAG_VxD_4	        = $25; { VxD tag	reserved	    }
            TAG_VxD_5	        = $26; { VxD tag	reserved	    }
            TAG_VxD_6	        = $27; { VxD tag	reserved	    }
            TAG_VxD_7	        = $28; { VxD tag	reserved	    }
            TAG_VxD_8	        = $29; { VxD tag	reserved	    }
            TAG_VxD_9	        = $2A; { VxD tag	reserved	    }
            TAG_VxD_A	        = $2B; { VxD tag	reserved	    }
            TAG_VxD_B	        = $2C; { VxD tag	reserved	    }
            TAG_VxD_C	        = $2D; { VxD tag	reserved	    }
            TAG_VxD_D	        = $2E; { VxD tag	reserved	    }
            TAG_VMID	        = $30; { Debugging }
            TAG_DNS_CMPS	= $31; { DNS completion list }
				       { <fixed len string array>, }
		                       { (size <= COMP_DOMAIN_STRLEN * MAX_DNS_CMPS  }

            TAG_RTT_MLT	        = $32; { TCP round-trip time multiplier }
            TAG_EPHEMERAL	= $33; { Discovered routers }
            TAG_MCASTLIST	= $34; { Active multicast groups }

            TAG_ARP_CACHE_LEN   = $35; { Length of ARP cache entry }
            TAG_ARP_CACHE	= $36; { Copy ARP cache to user buffer }
            TAG_ARP_ENTRY	= $37; { Set cache entry }
            TAG_ARP_TMO	        = $38; { ARP timeout }
            TAG_OVERSIZE_PKTS   = $39; { # of packets for IP reassembly }
					    {    of 'mobygrams'...	      }
            TAG_HG_PKT_SIZE	= $3a; { and how big ?		      }

            TAG_KERNEL_INFO     = $3b; { Kernel info (size = 2 }

            TAG_INTERFACE_TYPE  = $3c; { Interface type (size = 2 }
            TAG_FRAME_TYPE 	= $3d; { Frame type (size = 2 }
            TAG_MAC_MTU	        = $3e; { MAC mtu (size = 2 }
            TAG_IP_MRU	        = $3f; { IP mru (size = 2 }
            TAG_DNS_TIMEOUT	= $40; { dns timeout (size = 2 }


          { Device specific values }

            TAG_PER_DEV	        = $80;

            TAG_DEVICE_ID	= $80;	{ IF_INFO interface ID for card, }
					{ (size = 2 }
            TAG_MAC_ADDR	= $81;	{ MAC address for this interface }
            TAG_IP_ADDR	        = $82;	{ This interface's IP address, }
					{ (size = 4 }
            TAG_GATEWAY	        = $83;	{ Gateways, <IP addr array>, }
					{ (size <= MAX_DEF_GWS * 4 }
            TAG_BCAST_ADDR	= $84;	{ Broadcast address, (size = 4 }
            TAG_SUBNET_MSK	= $85;	{ Subnet mask, (size = 4 }
            TAG_DEV_FLAGS	= $86;	{ Flags <FL_ bits>, (size = 2 }
            TAG_BSERVER	        = $87;	{ Banyan server programme, }
					{ (size = 6 }
            TAG_INFO_FLAGS	= $88;	{ if_info flags <IFF_ bits>, }
					{ (size = 4 }
            TAG_VJCOMP	        = $89;	{ VJ Compression config parameters }
 					{ size = sizeof(struct vj_config }
            TAG_IPCP_LADDR	= $8A;	{ IPCP layer local IP address }
 					{ size = sizeof(in_name }
            TAG_IPCP_RADDR	= $8B;	{ IPCP layer remote IP address }
 					{ size = sizeof(in_name }

            TAG_DRIVER_VER	= $8F;	{ Driver version (not implemented }

            TAG_PKDRV_CLASS	= $90;	{ Packet driver class (size = 2 }

          { Hardware configuration }

            TAG_INT_VEC	        = $A0;	{ HW interrupt vector, (size = 2 }
					{ or chain vector }
            TAG_BASE_IO	        = $A1;	{ Base IO address, (size = 2 }
            TAG_XMT_DMA	        = $A2;	{ Transmit dma channel, (size = 2 }
            TAG_RCV_DMA	        = $A3;	{ Receive dma channel, (size = 2 }
            TAG_MEMORY_BASE	= $A4;	{ Base memory address, (size = 2 }
            TAG_MEMORY_SIZE	= $A5;	{ Shared memory size, (size = 2 }
            TAG_ROM_ADDR	= $A6;	{ On-board ROM addr, }
            TAG_ROM_SIZE	= $A7;
            TAG_BAUDRATE	= $A8;	{ Serial line speed, (size = 2  }
            TAG_PORT	        = $A9;	{ "Port" value (should be specific}
					{ (size = 2 }
          { Statistics }

            TAG_IPCP_ESTATS	= $B1;	{ IPCP event stats for PPPDRV }
            TAG_IPCP_PSTATS	= $B2;	{ IPCP packet stats for PPPDRV }
            TAG_IPCP_PARAMS	= $B3;	{ IPCP params for PPPDRV }

          { IPCP parameters }

            TAG_IPCP_MAX_FAILURE   = $B4;	{ IPCP params for PPPDRV }
            TAG_IPCP_MAX_CONFIGURE = $B5;	{ IPCP params for PPPDRV }
            TAG_IPCP_MAX_TERMINATE = $B6;	{ IPCP params for PPPDRV }
            TAG_IPCP_RESTART_TIMER = $B7;	{ IPCP params for PPPDRV }

          { IPCP trace data, for PPP only }

            TAG_IPCP_TB_READ    = $D0; { IPCP trace buffer read ptr }
            TAG_IPCP_TB_WRITE   = $D1; { IPCP trace buffer write ptr }
            TAG_IPCP_TB_CURSZ   = $D2; { IPCP trace buf current size }
            TAG_IPCP_TB_LRSZ    = $D3; { IPCP trace buf last read size }
            TAG_IPCP_TB_BUFP    = $D4; { IPCP trace buffer itself }

          { Special statistics for particular boards }
          { all the flags in TAG_DEV_FLAGS }

            FL_DOWN		= 0001;		{ interface is "turned off" }
            FL_RARP		= 0002;		{ choose ip address via RARP }
            FL_ARP		= 0004;		{ use ARP }
            FL_DMA		= 0008;		{ use DMA }
            FL_NOSETIP	        = 0010;		{ user can't set IP address }
            FL_1822		= 0020;		{ select 1822 }
            FL_X25standard	= 0040;		{ select X.25 standard }
            FL_X25basic	        = 0080;		{ select X.25 basic }
            FL_DCE		= 0100;		{ be DCE instead of DTE }
            FL_ADDR		= 0200;		{ local net address is set }


          { ------------- DECLARATIONS FOR CONFIGURABLE GLOBALS ----------------- }

     const  TSRPCTCP	        = 1; 	{ TSR PCTCP kernel }
            VXDPCTCP	        = 2; 	{ VXDPCTCP kernel }

            NUM_DEVICES         = 1;	{ No multi-homed support yet }
            MAX_DEF_GWS	        = 3;
            MAX_CFG_GWS	        = 4;
            MAX_IGMP	        = 8;	{ Max. # of multicast addresses }

            IP_OPT_MAXLEN       = 40;
            MAX_PORT            = 25;   { max number of ports }

            IP_PREC_STRICT      = $1;	{ Strict precedence checking }
            IP_SEC_STRICT       = $2;	{ Strict security checking }
            IP_SEC_BAS	        = $4;	{ Basic (RFC 1038 security }
            IP_SEC_EXT	        = $8;	{ Extended IP security }

            MAX_DNS_SRVS        = 3;
            MAX_DNS_CMPS        = 3;

            DOMAIN_STRLEN       = 64;
            HTABLE_STRLEN       = 66;

            COMP_DOMAIN_STRLEN	= 32;

