   { values for set_option() and get_option() system calls.}

    const NET_OPT_NONBLOCKING	  =$01;	{ don't block on system calls;
                                          When on, cause read and write calls to return
                                          immedially with an error if they would block.
                                          Use for asynchronous application.
                                        }
          NET_OPT_TIMEOUT	  =$02;	{ timeout [ms] to wait for system call completion
                                          before returning or signalin a timeout condition
                                          Use for asynchronous application.
                                        }
          NET_OPT_HINT		  =$03;	{ set a user-supplied "hint"
                                        }
          NET_OPT_BUFSIZE	  =$04;	{ set the window (STREAM)
                                          or buffer size in datagrams
                                        }
          NET_OPT_NETASCII	  =$05;	{ do netascii xlation - not impl.
                                        }
          NET_OPT_KEEPALIVE	  =$06;	{ do TCP keepalives
                                        }
          NET_OPT_DEBUG		  =$07;	{ enable debugging - not impl. }
          NET_OPT_DONTROUTE	  =$08;	{ "don't route" - not impl. }
          NET_OPT_PRECEDENCE	  =$09;	{ set IP precedence }
          NET_OPT_TOS		  =$0A;	{ set IP type of service }
          NET_OPT_PRIV		  =$0B;	{ make lcl socket number be < 1K}
          NET_OPT_WAITFLUSH	  =$0C;	{ Honor NET_FLG_PUSH on this nd, only for STREAM
                                        }
          NET_OPT_TTL		  =$0D;	{ Set TTL for each connection }
          NET_OPT_NO_LOOPBACK	  =$0E;	{ Don't loopback Multicast packets }
          NET_OPT_BSD_URG	  =$0F;	{ Use BSD (RFC 793) urgent pointers }


   { precedence values}

    const IP_PREC_MASK		  =$E0;
          IP_PREC_ROUTINE	  =$0;
          IP_PREC_PRIORITY	  =$20;
          IP_PREC_IMMEDIATE	  =$40;
          IP_PREC_FLASH		  =$60;
          IP_PREC_FLASH_OVERRIDE  =$80;
          IP_PREC_CRITICECP	  =$A0;
          IP_PREC_INET_CONTROL	  =$C0;
          IP_PREC_NET_CONTROL	  =$E0;


   { Some IP option values, sorted by 'number'}

    const IPOPT_EOL	          =$00;	{ End of option list }
          IPOPT_NOP	          =$01;	{ No operation }
          IPOPT_BAS_SEC	          =$82;	{ Basic Security }
          IPOPT_LSRR	          =$83;	{ Loose Source & Record Route }
          IPOPT_TS	          =$44;	{ Timestamp }
          IPOPT_EXT_SEC	          =$85;	{ Extended Security }
          IPOPT_RR	          =$07;	{ Record Route }
          IPOPT_SID	          =$08;	{ Stream ID (obsolete) }
          IPOPT_SSRR	          =$89;	{ Strict Source & Record Route }


   { type of service values - | them together}

    const IP_TOS_MASK		  =$1E;
          IP_TOS_LOW_COST	  =$02;
          IP_TOS_HIGH_RELIABILITY =$04;
          IP_TOS_HIGH_THROUGHPUT  =$08;
          IP_TOS_LOW_DELAY	  =$10;
