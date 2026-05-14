     { Nastavenie parametrov spracovania
     }

      const   dT_propose_FPLM  : int   = 60; {'}  { preaktivovany plan }
                 dT_propose_FPLM_lo    = 5;       { if FPL^.prist.cas + cas_DEL_ACT_FPL*60 <= absTime then z:= poz_HANGAR; }
                 dT_propose_FPLM_hi    = {$IFDEF OPL} 1440 {$ELSE} 120 {$ENDIF};


              dT_unactive_FPLM : int   = 2; {hod} { neaktivovany plan :
                                                    if absTime > DateToSec(date.r,date.m,date.d)+secDAY+dT_unactived_FPLM*60
                                                    then z:= poz_HANGAR
                                                  }
                 dT_unactive_FPLM_lo   = 1;       { if FPL^.prist.cas + cas_DEL_ACT_FPL*60 <= absTime then z:= poz_HANGAR; }
                 dT_unactive_FPLM_hi   = 12;


              cfg_WARNING_FPLM  = 'WARNING FPLM ARR';
              dT_arr_warn_FPLM : int   = 30; {'}  { po tomto limite sa : }
                 dT_arr_warn_FPLM_lo   =  1;      {   - vyhlasi patranie po vojenskom lete (OPL), }
                 dT_arr_warn_FPLM_hi   = 60;      {   - odmaze vojensky let (EDD), ak nie je dovolena vystraha na pristatie }


              cfg_DEACTIVE_FPLM = 'DEACTIVE FPLM';

              dT_deactive_FPLM  : int  = 10; {'}  { cas po ktorom odmaze aktivovany FPL, na ktory nebola vydana sprava ARR }
                 dT_deactive_FPLM_lo   =  1;      { if FPL^.prist.cas + cas_DEL_ACT_FPL*60 <= absTime then z:= poz_HANGAR; }
                 dT_deactive_FPLM_hi   = 60;


              dT_propose_FPLM_REQ : int  =  5; {'}   { prestih ponuky pripomienky }
                 dT_propose_FPLM_REQ_lo  =  5;
                 dT_propose_FPLM_REQ_hi  = 60;

              dT_deactive_FPLM_REQ : int =  5; {'}   { zrusenie pripomienky, ak presiahla limit po starte  }
                 dT_deactive_FPLM_REQ_lo =  3;
                 dT_deactive_FPLM_REQ_hi = 10;



      const   poz_est_FPLM : Tpozs = [poz_PREACTIVE..poz_SEDI];


     { IFDEF OPL}

              _propose_dayFPLM  {$IFDEF OPL}     : bool = true
                                {$ELSE}                 = false
                                {$ENDIF};
                                                  { plany sa preaktivuju na cely den,
                                                    nie casovy limit vopred...
                                                  }

              _unactive_dayFPLM {$IFDEF OPL}     : bool = true
                                {$ELSE}                 = false
                                {$ENDIF};
                                                  { plany sa deaktivuju az na koniec dna,
                                                    nie casovy limit po...
                                                  }

      const   _preactived_FPLM       : bool = true;  { plany letov na dany den, az po limit platnosti }
              _preactived_FPLO       : bool = true;
                _preactived_FPLM_ot  : bool = true;
                _preactived_FPLO_ot  : bool = true;

              _proposed_FPLM         : bool = true;  { vyziadane pripomienky }
              _proposed_FPLO         : bool = true;
                _proposed_FPLM_ot    : bool = true;
                _proposed_FPLO_ot    : bool = true;

              _coordinated_FPLM      : bool = true;  { schvalene pripomienky }
              _coordinated_FPLO      : bool = true;
                _coordinated_FPLM_ot : bool = true;
                _coordinated_FPLO_ot : bool = true;

                _activated_FPLM_ot   : bool = true;
                _activated_FPLO_ot   : bool = true;



      const   cfg_FPLM_INE    = 'FPLO';
              FPLM_INE          : bool = true;       { odlisenie inych vojenskych planov }

              cfg_FPLM_INE_9  = 'FPLO-9';
              FPLM_INE_9        : bool = true;       {  - podla letiska statu/pristatia, }

              cfg_FPLM_INE_AP = 'FPLO-AP';
              FPLM_INE_AP       : bool = true;       {  - podla typu                     }


      const   KRL_FPLM_CNL      : bool = true;       { po aktivovani sa plan kridla zrusi }

              FPLM_REQ_WARN     : bool = false;
              FPLM_DEP_WARN     : bool = false;

             { upozornenie na nevydanie spravy ARR }
              FPLM_ARR_WARN     : bool = {$IFDEF REPORT_FPLM_ARW} true {$ELSE} false {$ENDIF};
              FPLM_ARR_WARN_ALL : bool = true; { pre vsetky/vlastne }


      const   FPLM_REGULARITA_FPLM       : bool = {$IFDEF FPLM_REGULARITA} true {$ELSE} false {$ENDIF};
              FPLM_REGULARITA_P          : bool = {$IFDEF FPLM_REGULARITA} true {$ELSE} false {$ENDIF};
              FPLM_REGULARITA_FUA_PLAN   : bool = {$IFDEF FPLM_REGULARITA} true {$ELSE} false {$ENDIF};
              FPLM_REGULARITA_FUA_ACT    : bool = {$IFDEF FPLM_REGULARITA} true {$ELSE} false {$ENDIF};

              FPLM_REGULARITA_FIR        : bool = {$IFDEF FPLM_REGULARITA} true {$ELSE} false {$ENDIF};
              FPLM_REGULARITA_FIR_FN     : string[8] = FIR;
              cfg_FPLM_REGULARITA_FIR_FN = 'FPLM-AREA';


      const   cfg_ENABLE_FPLM  = 'EDIT FPLM';
              ENABLE_FPLM      : bool = {$IFDEF MATCA}
                                           true
                                        {$ELSE}
                                          {$IFDEF PROCESS_FPLM}
                                            true
                                          {$ELSE}
                                            false
                                          {$ENDIF}
                                        {$ENDIF};


     { ENDIF}


     { Nastavenie parametrov zobrazenia
     }
      const   {$IFDEF FPLM_L}
                dlz_rdk_FPLm           = 59 {MTK_2_LINE};

                max_mFPL_15_rm : int   = 2;
                max_mFPL_15_r_lo       = 0;
                max_mFPL_15_r_hi       = 4; { nemenit bez uprav kodovania }

                max_mFPL_18_rm : int   = 1;
                max_mFPL_18_r_lo       = 0;
                max_mFPL_18_r_hi       = 3;
              {$ELSE}
                dlz_rdk_FPLm           = 56;
                rdk_trat_FPLm          = 2;
                rdk_pozn_FPLm          = 2;

                max_mFPL_15_rm : int   = 2;
                max_mFPL_18_rm : int   = 1;

                max_mFPL_15_r_hi       = 2;
                max_mFPL_18_r_hi       = 1;
              {$ENDIF}


      const   find_and_process_FPLM    : bool = true;

      const   bminimFPL                : bool = true;
              pis_STRIP_mFPL           : bool = false; { aktivne plany ako stripy }
              pis_STRIP_mFPL_15body    : bool = true;  { a vypis dekodovanej trate }
              miniSTRIP_mFPL           : T_strip = {$IFDEF EDD} full_strip {$ELSE} full_strip {$ENDIF};


      const   hlas_vlastne_FPLM        : bool = true;  { zobrazenie informacii o vlastnych FPL }
              hlas_riadene_FPLM        : bool = true;  { zobrazenie informacii o vlastnych FPL }
              varovanie_FPLM           : bool = {$IFDEF OPL_LET} true {$ELSE} false {$ENDIF};
              hlas_vsetky_FPLM         : bool = true;  { -//- o ostatnych }


     { Nastavenie parametrov tlace
     }
      const   prn_FPLM_ICAO            : bool = false;



     { Pomocne vypoctove premenne
     }
      const  isFPLM : bool = false;              { sprava nebola precitana }


             {$IFDEF PROCESS_FPLM}
      const   {$IFDEF KRL}
                isKRL          : bool = false;
              {$ENDIF}

              {$IFDEF AIRBASE}
                isFPLM_ACC     : bool = false;    { priznak o oprave alebo pripomienke tu podaneho planu }
              {$ENDIF}

              {$IFDEF MACC}
                isFPLM_REQ     : bool = false;    { prisla poziadavka na vydanie pripomienky k letu, vyvola spracovanie }
                isFPLM_REQ_DLA : bool = false;    { odlozena na disku... }
              {$ENDIF}

              isFPLM_PROC      : bool = false;    { povolenie spracovania prijatych FPL }
              isFPLM_SAVED     : bool = false;    { indikuje, ze bol spracovany FPL }
             {$ENDIF}

              isFPLM_ARW       : bool = false;


      const  hd_ASC = 'ASC';
             hd_DES = 'DES';
