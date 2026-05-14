    const  EXTcfg             = 'EXT'+ext_ini;

           cfg_NODE_THIS      = 'THIS NODE';
           cfg_NODE_REMOTE    = 'REMOTE NODE';
           cfg_PROCESS_ALL    = 'PROCESS-ALL';

           cfg_HEADER_ADR     = 'ADR IN HEADER'; { za identifikator typu spravy vlozi THIS NODE/REMOTE NODE+CISLO SPRA }

           cfg_Ts_TimeOut     = 'TS_TIMEOUT';
           cfg_Tr_TimeOut     = 'TR_TIMEOUT';
           cfg_LAM_TimeOut    = 'LAM_TIMEOUT';
           cfg_HeartBeat      = 'HEARTBEAT';

           cfg_send_VFR_FPL   = 'SEND VFR FPL';
           cfg_FL_from_alt    = 'FL FROM ALTITUDE';

           cfg_TEST           = 'TEST TEXT';
           cfg_STREAM         = 'STREAM SAVE';

           cfg_IP_ADR         = 'IP-ADR';


    const  path_NOT_PROCESSED = 'NOT'#255'PROC\';

           ext_ALR            = 'ALR';

           ext_ERR            = 'ERR';  { subor s prijatou chybovou spravou  }
           ext_ERS            = 'ERS';  { subor s odlozenou chybovou spravou }

           ext_DEL            = 'DEL';  { subor s nazvom odmazanej spravy }


    const  hold_TLG : word    = 24;
           hold_ERR : word    = 24;

           cfg_hold_TLG       = 'LIMIT - TLG CONFIRM';
           cfg_hold_ERR       = 'LIMIT - ERR PROCESS';


    const  NODE_PROMISCUITE   = '*';


    const  TsTimeOut_ {: word}  = 40;
           TrTimeOut_ {: word}  = 80;
           LAM_TimeOut_{: word} = 80;

           icaoEditorPage       = 60;

    type   TPKT_SRC = (src_ext,src_net,src_ed,src_file);

