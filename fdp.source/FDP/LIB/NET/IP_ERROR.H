  { definitions of error codes that pc/tcp system calls can return }

    const NET_NOERR		      =	0;
          NET_ERR_INUSE		      =	1;
          NET_DOS_ERR		      =	2;
          NET_ERR_NOMEM		      = 3;
          NET_ERR_NOTNETCONN	      =	4;
          NET_ERR_ILLEGALOP	      =	5;
          NET_ERR_BADPKT	      =	6;
          NET_ERR_NOHOST	      =	7;
          NET_ERR_CANTOPEN	      =	8;
          NET_ERR_NET_UNREACHABLE     =	9;
          NET_ERR_HOST_UNREACHABLE    = 10;

          NET_SUB_NO_ERROR	      = 0;	{ no error }
          NET_SUB_ICMP_UNR            = 1;	{ icmp dest. unreachable }
          NET_SUB_ARP		      = 2;	{ direct arp failed }
          NET_SUB_IF_FAILURE	      = 3;	{ hardware failure }
          NET_SUB_IF_UNR	      = 4;	{ hardware link failure }
          NET_SUB_NOROUTE	      = 5;	{ no route }
          NET_SUB_GW		      = 6;	{ first hop gateway down }
          NET_ERR_PROT_UNREACHABLE    = 11;
          NET_ERR_PORT_UNREACHABLE    = 12;
          NET_ERR_TIMEOUT             =	13;
          NET_ERR_HOSTUNKNOWN	      =	14;
          NET_ERR_NOSERVERS	      =	15;
          NET_ERR_SERVER_ERR	      =	16;
          NET_ERR_BADFORMAT	      =	17;
          NET_ERR_BADARG	      =	18;
          NET_ERR_EOF		      =	19;
          NET_ERR_RESET		      =	20;
          NET_ERR_WOULD_BLOCK	      =	21;
          NET_ERR_UNBOUND	      =	22;
          NET_ERR_NODESC	      =	23;
          NET_ERR_BADSYSCALL	      = 24;
          NET_ERR_CANTBROADCAST	      =	25;
          NET_ERR_NOTESTAB	      =	26;
          NET_ERR_REENTRY	      =	27;
          NET_ERR_ICMPMSG	      =	28;	{ Other ICMP }

          NET_SUB_ICMP_UNREC	      = 7;	{ Unknown other ICMP }
          NET_SUB_CANTFRAG	      = 8;	{ DESTIN: code 4 }
          NET_SUB_SRCR_FAIL	      = 9;	{ DESTIN: code 5 }
          NET_SUB_SORCEQ	      = 10;	{ Source Quench }
          NET_SUB_TIMEX		      = 11;	{ Time Exceeded }
          NET_SUB_PARAM		      = 12;	{ Parameter Problem }
          NET_SUB_ADMIN_PROHIB	      = 13;	{ Communication Prohibited }

          NET_ERR_TERMINATING	      =	29;	{ Kernel unloading }
          NET_ERR_TAG_LOCKED	      =	30;	{ Can't set this tag }
          NET_ERR_BAD_INTERFACE	      =	31;	{ No such device! }
          NET_ERR_BADCONFIG	      =	32;	{ Kernel can't run yet... }
          NET_ERR_EMM		      =	33;      { EMM manager complains ...}
          NET_ERR_CANT_SHUTDOWN	      =	34;      { In a multi-tasker }
          NET_ERR_PARKED_IN	      =	35;	{ Someone else has INT2F }
          NET_ERR_NOQIOS	      =	36;	{ No qios left }
          NET_ERR_WOULD_TRUNCATE      =	37;	{ Your datagram's too big }
          NET_ERR_APPENDED	      =	38;	{ We've appended but didn't }
                                	          {   write yet... }
          NET_ERR_DOSEXT	       = 39;	{ DOS-extender error }
          NET_ERR_NO_ARP	       = 40;	{ Kernel doesn't support ARP }
          NET_ERR_ARP_ENTRY_NOT_FOUND  = 41;	{ No such ARP or IP address }
          NET_ERR_ARP_ENTRY_WRONG_SIZE = 42;	{ Wrong entry size }

          MAX_PCTCP_ERR		       = 42;	{ Highest numbered error }
          MAX_PCTCP_SUBERR	       = 13;	{ Highest sub-error code }

          NET_ERR_NOACCESS  = (MAX_PCTCP_ERR + 1); { Kernel access failed }


    const max_neterr_list = 42;
          neterr_list: array[0..max_neterr_list] of pchar =
                 (
	          'Error...' {'No error'},                {  0 }
	          'Address in use',			  {  1 }
	          ''{DOS error'},			  {  2 }
	          'Out of resources (memory/connections)',{  3 }
	          'Not a network descriptor',		  {  4 }
	          'Illegal operation',			  {  5 }
	          'Bad packet buffer',			  {  6 }
	          'No address for descriptor',		  {  7 }
	          'Can not open DOS file',		  {  8 }
	          'Network unreachable',		  {  9 }
	          'Host unreachable',			  { 10 }
	          'Protocol not active in host',	  { 11 }
	          'No process listening on socket',	  { 12 }
	          'Timeout',				  { 13 }
	          'Host unknown',			  { 14 }
	          'No servers configured',		  { 15 }
	          'Bad response from server',		  { 16 }
	          'Bad format',				  { 17 }
	          'Bad argument to system call',	  { 18 }
	          'End of receive',			  { 19 }
	          'Connection reset',			  { 20 }
	          'Operation would block',		  { 21 }
	          'No address bound to descriptor',	  { 22 }
	          'Can not allocate descriptor',	  { 23 }
	          'Bad system call',			  { 24 }
	          'Can not broadcast',			  { 25 }
	          'Connection not established',		  { 26 }
	          'Kernel re-entered',			  { 27 }
	          'got ICMP error',			  { 28 }
                  'Kernel unloading',			  { 29 }
	          'Configuration tag locked',		  { 30 }
	          'Bad interface number',		  { 31 }
	          'Configuration incomplete',		  { 32 }
                  'Expanded memory error',		  { 33 }
                  'Can not unload kernel under a multitasker', { 34 }
	          'Can not release INT2F - not last on chain', { 35 }
	          'No free QIOs',			  { 36 }
	          'Datagram would be truncated',	  { 37 }
	          'Data appended, packet being held',	  { 38 }
	          'DOS Extender error',			  { 39 }
	          'Kernel does not support ARP',	  { 40 }
	          'ARP entry not found',		  { 41 }
	          'ARP entry is the wrong size'		  { 42 }
	         );

    const max_netsuberr_list = 13;
          netsuberr_list: array[0..max_netsuberr_list] of pchar =
                 (
	          'No error',		 		  {  0 }
	          'Dest. Unreachable',			  {  1 }
	          'ARP failed',				  {  2 }
	          'Hardware error',			  {  3 }
	          'Link failure',			  {  4 }
	          'No route',				  {  5 }
	          'Gateway down',			  {  6 }
	          'Unknown ICMP msg',			  {  7 }
	          'Could not fragment',			  {  8 }
	          'Source Route failed',		  {  9 }
	          'Source Quench',			  { 10 }
	          'Time to Live exceeded',		  { 11 }
	          'Parameter Problem',			  { 12 }
	          'Communication Prohibited'		  { 13 }
                 );


    const err_ip_cfg = 'Error in pctcp.ini configuration.';