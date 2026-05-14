    procedure ARCHIV_reload;

    procedure prehlad_mFPL_sicke;
    procedure prehlad_mFPL_nase;
    procedure prehlad_mFPL_ine;

    procedure prehlad_mFPL_PPL;
    procedure prehlad_mFPL_ARCH;


    {$IFDEF OPL}

      procedure imit_trg(mapa_init: bool); far;
      function  handle_mFPL_list0(_sl: pointer; pos: int): bool; far;
      function  handle_aFPL_list0(_sl: pointer; pos: int): bool; far;

      {$IFDEF AIRBASE}
        procedure prehlad_KRL_pri;
        procedure prehlad_KRL_pod;

        procedure prehlad_KRL_PPL;
        procedure prehlad_KRL_ARCH;

        procedure mFPL_REQ;
        procedure mFPL_CHG;

        procedure mFPL_posli;
        procedure mFPL_posli_vsetky;

        procedure KRL_sprac;

        procedure KRL_posli;
        procedure KRL_posli_vsetky;
      {$ENDIF}

      {$IFDEF MACC}
        procedure mFPL_CHG;
        procedure mFPL_REQ;
      {$ENDIF}

      procedure mFPL_DEP;
      procedure mFPL_ARR;
      procedure mFPL_ARR_WARN;
      procedure mFPL_CNL;

      procedure mFPL_DLA;
      procedure mFPL_MZP;
      procedure mFPL_RTE;

    {$ENDIF}

