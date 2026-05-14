   { connection types for net_connect() and net_listen()}

    const RAW_NET	   = 1;                 { NO PROTOCOL, len pre ziskanie informacii }
          RAW_IP	   = 2;                 { IP   }
          DGRAM		   = 3;                 { UDP  }
          STREAM	   = 4;                 { TCP  }
          RAW_ICMP	   = 5;                 { ICMP }


   { flags for net_read(), net_readfrom(), net_recv(), net_recvfrom(),
     net_write(), net_writeto(), net_send(), net_sendto()
   }

    const NET_FLG_              = $0000;
          NET_FLG_OOB		= $0001;	{ out of band data }
          NET_FLG_PEEK		= $0002;	{ don't dequeue data }
          NET_FLG_DRAIN		= $0004;	{ don't copy data }
          NET_FLG_REROUTE	= $0008;	{ request re-routing }
          NET_FLG_PUSH		= $0010;	{ reserved }
          NET_FLG_DONTTRUNCATE	= $0020;	{ Don't truncate oversized dgram }
          NET_FLG_NONBLOCKING	= $0040;	{ don't block }
          NET_FLG_BROADCAST	= $0080;	{ broadcast data }
          NET_FLG_OVERSIZE	= $0100;	{ outgoing IP fragmentation }
          NET_FLG_APPEND	= $0200;	{ Don't write the packet to driver }
					        { until this flag is NOT set }

   { syscalls }

    const _NET_DEBUG	   = $00;
          _NET_CONFIG	   = $01;
          _GET_KERNEL_INFO = $02;
          _TRACE_INFO	   = $03;
          _SET_TRACE	   = $04;
          _GET_ADDR	   = $05;
          _NET_INFO	   = $06;
          _NET_GLOBALIZE   = $07;
          _NET_RELEASE	   = $08;
          _NET_RELEASEALL  = $09;
          _NET_SEND	   = $0a;
          _NET_SENDTO	   = $0b;
          _NET_STAT	   = $0c;
          _IS_NETND	   = $0d;
          _NET_SELECT	   = $0e;
          _GET_NETVERSION  = $0f;
          _NET_SUTDOWN	   = $10;
          _DISABLE_ASYNCH  = $11;
          _ENABLE_ASYNCH   = $12;
          _NET_CONNECT	   = $13;
          _NET_RECV	   = $14;
          _NET_RECVFROM	   = $15;
          _GET_PEER	   = $16;
          _NET_RECONFIG	   = $17;
          _NET_EOF	   = $18;
          _NET_ABORT	   = $19;
          _NET_WRITE	   = $1a;
          _NET_READ	   = $1b;
          _NET_WRITETO	   = $1c;
          _NET_READFROM	   = $1d;
          _NET_FLUS	   = $1e;
          _NET_ASYNCH	   = $1f;
          _SET_OPTION	   = $20;
          _GET_OPTION	   = $21;
          _NET_GETDESC	   = $22;
          _NET_LISTEN	   = $23;
          _NET_ABORTALL	   = $24;
          _AD_RES_NAME	   = $25;
          _AD_TABLE	   = $26;
          _AD_DOMAIN	   = $27;
          _NET_SWAP	   = $28;
          _NET_GETGLOBDESC = $29;
          _NET_GET_K_CONF  = $2A;
          _NET_ALARM	   = $2B;
          _ICMP_PING	   = $30;
          _IS_KERNEL_BUSY  = $32;	{; undocumented - irina}

          _NM_PRS_ADDR	   = $50;
          _NM_TABLE	   = $51;
          _NM_DOMAIN	   = $52;
          _NM_IEN116	   = $53;
          _NM_RES_NAME	   = $54;
          _NET_DEBUGVXD    = $57;

          MAX_PCTCP_FUNC   = $57;


