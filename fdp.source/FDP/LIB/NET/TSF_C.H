    const{ X25-NB structure dependent definitions }
           MAX_NAMES     = 52;
           MAX_SESSIONS  = 14;

           NAME_SIZE     = 16;  { = X25_ADR_SIZE } { name size in NCB     }
           DATAMAX       = X25_PACKET_SIZE;        { maximum size of NPDU }


    const  STDMODE                    =  0;   { service mode required }
           X25MODE                    =  1;

         { NETBIOS commands - wait variants are -$80 }
           NCB_ADD_NAME               = $B0;
           NCB_ADD_GROUP_NAME         = $B6;
           NCB_DELETE_NAME            = $B1;
           NCB_DELETE_NAME_WAIT       = $31;
           NCB_CALL                   = $90;
           NCB_LISTEN                 = $91;
           NCB_HANGUP                 = $92;
           NCB_HANGUP_WAIT            = $12;
           NCB_SEND                   = $94;
           NCB_CHAIN_SEND             = $97;
           NCB_RECEIVE                = $95;
           NCB_RECEIVE_ANY            = $96;
           NCB_STATUS                 = $B3;
           NCB_SESSION_STATUS         = $B4;
           NCB_CANCEL                 = $B5;
           NCB_RESET                  = $B2;
           NCB_UNLINK_WAIT            = $70;

         { NETBIOS X25 command calls }
           NCB_ADD_REMOTE_NAME        = $C0;  { add remote name             }
           NCB_ADD_SPECIAL_NAME       = $C1;  { special = NAME_AND_ADDRESS  }
           NCB_ADD_SPECIAL_NAME_WAIT  = $41;
           NCB_ADD_EXTENDED_NAME      = $4E;  { extended Name/NUA + /CUD or /XNAD }
           NCB_ADD_EXTENDED_NAME_WAIT = $CE;

           NCB_X25LISTEN              = $C2;  { extended listen recommended }
           NCB_X25CALL                = $C3;  { extended call recommended   }
           NCB_X25_ECALL              = $C5;  { extended call               }
           NCB_X25_ELISTEN            = $C6;  { extended listen             }
           NCB_X25_RESET_COMMS        = $C7;  { reset communications        }
           NCB_X25_SES_STATUS         = $C8;  { session status              }
           NCB_X25_RESET_CHAN         = $CA;  { reset channel               }
           NCB_SEND_NO_ACK            = $F1;
           NCB_GATHER_STATS           = $C9;

           NCB_X25_EHANGUP            = $4B;  { extended hangup   }
           NCB_NOTIFY_CALL            = $4C;  { notify call       }
           NCB_ACCEPT_CALL            = $4D;  { accept call       }
           NCB_X25_EADD_NAME          = $4E;  { add extended name }
           NCB_SEND2_NO_ACK           = $72;  {                   }

         { Standard NCB return codes - immediate }
           NCB_RET_GOOD               = $00;  { good }
           NCB_RET_BADCOMMAND         = $03;  { invalid command }
           NCB_RET_MSG_INCOMPLETE     = $06;
           NCB_RET_INTBUSY            = $21;  { interface busy }
           NCB_RET_TOOMANY            = $22;  { too many commands outstanding }
           NCB_RET_BADNUM             = $23;  { invalid number in NCB_LANA_NUM field }
           NCB_RET_CANCMPLT           = $24;  { tried to cancel nonexistent command }
           NCB_RET_NOCAN              = $26;  { command not valid to cancel }
           NCB_RET_X25BADPARM         = $27;
           NCB_RET_ZEROERROR          = $28;
           NCB_RET_BADNUA             = $29;
           NCB_RET_UNUSUAL_START      = $40;  { unusual network condition }
           NCB_RET_UNUSUAL_END        = $4F;
           NCB_RET_MALFUNCTION_START  = $50;  { adapter malfunction }
           NCB_RET_MALFUNCTION_END    = $5E;

         { Standard NCB completion codes - final }
           NCB_ERR_LENGTH             = $01;  { illegal buffer length }
           NCB_ERR_CMD                = $03;  { invalid command }
           NCB_ERR_TIMEOUT            = $05;  { command timed out }
           NCB_ERR_INCOMPLETE         = $06;  { message incomplete }
           NCB_ERR_ILLEGAL            = $08;  { illegal local session number }
           NCB_ERR_NO_RESOURCE        = $09;  { no resource available }
           NCB_ERR_CLOSED             = $0A;  { session closed }
           NCB_ERR_CANCEL             = $0B;  { command cancelled }
           NCB_ERR_DUPL_NAME          = $0D;  { duplicate name in local name table }
           NCB_ERR_NAME_FULL          = $0E;  { name table is full }
           NCB_ERR_DEREG              = $0F;  { command complete, name deregistered }
           NCB_ERR_LOCAL_TAB_FULL     = $11;  { local session table full }
           NCB_ERR_REJECTED           = $12;  { session open rejected }
           NCB_ERR_BADNAME            = $13;  { illegal name number }
           NCB_ERR_NO_ANSWER          = $14;  { no remote name or no answer }
           NCB_ERR_NO_NAME            = $15;  { name not found }
           NCB_ERR_NAME_USED          = $16;  { name in use }
           NCB_ERR_DELETED            = $17;  { name deleted }
           NCB_ERR_ABNORMAL           = $18;  { session ended abnormally }
           NCB_ERR_NAME_CONF          = $19;  { name conflict }
           NCB_ERR_INCOMPATIBLE       = $1A;  { incompatible remote device }
           NCB_ERR_PENDING            = $FF;  { command not finished }
