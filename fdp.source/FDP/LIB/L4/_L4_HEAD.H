    const  kod_ICAO    = 4;
           kod_HEAD    = 3;
           kod_ID      = 2;  { identifikacia uzla v hlavicke : MI, PR }
           kod_SQN     = 3;

           kod_3       = kod_HEAD + kod_ID+1+kod_ID + kod_SQN;


    type   Thead_ICAO  = string[kod_HEAD];
           Theads_ICAO = array [0..MAX_ARRAY_SIZE div sizeof(Thead_ICAO) - 1] of Thead_ICAO;
           Pheads_ICAO = ^Theads_ICAO;


    const { ICAO, Doc.4444 }

           hd_RQP = 'RQP';
           hd_RQS = 'RQS';
           hd_SPL = 'SPL';

           hd_FPL = 'FPL';
           hd_CHG = 'CHG';
           hd_DLA = 'DLA';
           hd_CNL = 'CNL';

           hd_ABI = 'ABI';
           hd_ACT = 'ACT';
           hd_PAC = 'PAC';
           hd_REV = 'REV';

           hd_DEP = 'DEP';
           hd_ARR = 'ARR';

           hd_CPL = 'CPL';
           hd_EST = 'EST';

           hd_ALR = 'ALR';
           hd_RCF = 'RCF';

           hd_LAM = 'LAM';


         { Ine }

           hd_RPL = 'RPL';
           hd_PLN = 'PLN';
           hd_PPL = 'PPL';
           hd_KRL = 'KRL';


         { Airspace Management }

           hd_PRS = 'ASM';
           hd_AUP = 'AUP';
           hd_UUP = 'UUP';
           hd_AUM = 'AUM';


           hd_ZAM = 'AAC';
           hd_RTZ = 'RTZ';
           hd_QGO = 'QGO';
           hd_DVZ = 'DVZ';

         { OPL }

           hd_CLR = 'CLR';


         { Telegramy }

           ht_ANP = 'ANP';

           ht_FLA = 'FLA';
           ht_FLI = 'FLI';

           ht_RTS = 'RTS';
           ht_RTO = 'RTO';

           ht_RVM = 'RVM';
           ht_RVI = 'RVI';

           hd_MSG = 'MSG';
           hd_TLG = 'TLG';


         { ine }

           hd_NIL = 'NIL';
           hd_NLM = 'NLM'; { NOLAM }




    type   ms_ICAO = ( msLAM,

                       msRQP, msRQS, msSPL,

                       msFPL, msCHG, msDLA, msCNL,          { ICAO }
                       msABI, msACT, msPAC, msREV,          { OLDI }
                       msCPL, msEST,                        { AMA  }
                       msDEP, msARR, {msFLA,}

                       msALR, msRCF                         { ICAO }
                     );

           set_msICAO   = set of ms_ICAO;
           p_set_msICAO = ^set_msICAO;

    const  ms_ICAOplan = [msRQP..msDLA];
           ms_ICAOact  = [msABI..msDEP,msCPL..msRCF];
           ms_ICAOest  = [msDEP,msABI,msACT,msCPL,msEST];
           ms_ICAOarr  = [msARR{, msFLA}];
           ms_ICAOcnl  = [msCNL{, msARR, msFLA}];


    const  hd_ICAO : array[msLAM..msRCF] of Thead_ICAO =

                     ( hd_LAM,

                       hd_RQP,
                       hd_RQS,
                       hd_SPL,

                       hd_FPL,
                       hd_CHG,
                       hd_DLA,
                       hd_CNL,

                       hd_ABI,   { na poradi prvkov zalezi }
                       hd_ACT,
                       hd_PAC,
                       hd_REV,

                       hd_CPL,
                       hd_EST,

                       hd_DEP,
                       hd_ARR,
                       {hd_FLA,}

                       hd_ALR,
                       hd_RCF
                     );

    function  icao_head_type (head: string; var res: string; p_heads: Pheads_ICAO; heads: word): int;
    function  in_icao_head   (head: string; iset: set_msICAO; var unkn: bool): bool;

    { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
       Implementacia L4444 spracovava nasledujuce druhy sprav  :
      תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

    type   ms_L4   = ( mlALR, mlRCF,
                       mlFPL, mlCHG, mlCNL, mlDLA, mlDEP, mlARR,
                       mlCPL, mlEST, mlLAM,
                       mlSPL
                     );

    const  hd_L4   : array[mlALR..mlSPL] of Thead_ICAO =

                        ( 'ALR',
                          'RCF',

                          'FPL',
                          'CHG',
                          'CNL',
                          'DLA',
                          'DEP',
                          'ARR',

                          'CPL',
                          'EST',
                          'LAM',

                          'SPL'
                        );

    }
