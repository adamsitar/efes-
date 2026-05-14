     const { typ protokolu }

             pX25   = '~X25';     { X25 a X25/IPX   }
             pIPX   = '~IPX';
             pBX25  = '~BX25';

             pRTR   = '~RTR';     { RTR nad WAN/IPX }
             pRTI   = '~RTI';     { RTR nad IPX     }
             pRTB   = '~RTB';     { RTR nad X25/IPX }
             pRTU   = '~RTU';     { RTR nad UDP     }

             pCOM   = '~COM';     { FDP cez COM         }

             pUDC   = '~UDP';     { UDP s CISCOm        }
             pUDX   = '~UDX';     { UDP ako X25 pre FDP }

             pTCP   = '~TCP';

             pS     = '~S';       { kratky protokol }
             pL     = '~L';       { dlhy protokol   }
             pNX0   = '~NX';
             pOX    = '~OX';


     const { typ stanice }
             nd_THIS       = '@THIS';

             {nd_FDP0      = '@0FDP';         pre DATA_BIN
             nd_RDP0       = '@0RDP';         pre DATA_BIN }

             nd_FDP        = '@FDP';
             nd_RDP        = '@RDP';
             nd_MET        = '@MET';
             nd_MON        = '@MON';

             nd_SERVER     = '@SERVER';
             nd_BSERVER    = '@BSERVER';

             nd_OPL        = '@OPL';
             nd_IDD        = '@IDD';
             nd_EDD        = '@EDD';
             nd_LIS        = '@LIS';
             nd_PRN        = '@PRN';
             nd_STRIPPRN   = '@STRIPPRN';
             {nd_MAIN      = '@MAIN';}

             nd_ROUTER     = '@ROUTER';
             nd_UROUTER    = '@ROUTER';

             nd_BRIDGE     = '@BRIDGE';
             nd_RBRIDGE    = '@RBRIDGE';
             nd_CBRIDGE    = '@CBRIDGE';


           { pracovisko }
             nd_MASTER     = '-MASTER';
             nd_SLAVE      = '-SLAVE';  { vseobecne informacne podriadne pracovisko }
             nd_INF        = '-INF';

             nd_PVO        = '-PVO';
             nd_RLP        = '-RLP';
             nd_ATC        = '-ATC';

             nd_MACC       = '-MACC';
             nd_AP         = '-AP';
             nd_TWR        = '-TWR';
             nd_RC         = '-RC';
             nd_NS         = '-NS';


             inf_CAS       = '-TIME';
             inf_HeartBeat = '-HEARTBEAT';    { heartbeat     }
             {inf_Init      = '-INIT';          inicializacia }


           { specialne vlastnosti uzla }
             nd_SECTOR     = '@SECTOR';  {  }
             nd_AIRBASE    = '@AIRBASE';
             {nd_DATA       = '@DATA';}
             nd_RLI        = '@DAR';
             nd_FDA        = '@FDA';
             {nd_MIL        = '@MIL';}
           { nd_NODE       = '@NODE';    podriadeny uzol }

             ndp_TIMEOUT   = 'TIMEOUT'; ndp_TIMEOUT_min = 1; ndp_TIMEOUT_max = 20;
             ndp_SECTOR    = 'SECTOR';
             ndp_INITALL   = 'INITALL';
             ndp_NOINIT    = 'NOINIT';



     const { odosielana informacia }
             inf_ALL       = 'ALL';

     type    Tprotocol     = (no_pro  , COM, X25,BX25, RTR,RTI,RTB, RTU,UDC,UDX,UD_, TCP); { stanica komunikuje v protokole }

             Tnd_typ       = (no_typ,  iny_typ, any_typ, FDP,RDP,MET,MON, FDP0,FDP0NX,RDP0,RDP0NX);        { typ stanice  }
             Tnd_sw        = (no_sw,            any_sw,  SERVER,BSERVER,BRIDGE,PRN, FDA,OPL,EDD,IDD,LIS);  { typ sw FDP   }
             Tnd_nd        = (no_nd,            any_nd,  SLAVE, MASTER);                                   { podriadenost }

             Tnd_typ_set   = set of Tnd_typ;
             Tnd_sw_set    = set of Tnd_sw;
             Tnd_nd_set    = set of Tnd_nd;


     const   set_nd_LETVIS : Tnd_typ_set = [FDP..RDP0NX];

             set_nd_EST    : Tnd_sw_set = [SERVER,BSERVER, EDD,IDD, PRN];
             set_nd_OPL    : Tnd_sw_set = [SERVER,BSERVER, FDA,OPL,IDD, LIS];
             set_nd_S      : Tnd_sw_set = [SERVER,BSERVER];

             set_nd_FDP    : Tnd_sw_set = [SERVER..LIS] - [PRN];
             set_nd_NODE   : Tnd_nd_set = [SLAVE,MASTER];
