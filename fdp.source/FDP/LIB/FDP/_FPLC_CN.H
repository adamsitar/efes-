     const   hd_ULP = 'ULP';

     const   cfg_DEACTIVE_FPLC = 'DEACTIVE EST';
             dT_deactive_FPLC      : int  =  {$IFDEF SERVER} 10 {$ELSE} 5 {$ENDIF}; {'}  { po tomto limite sa zmaze EST }
                dT_deactive_FPLC_lo       =  1;      { lo - spodna hranica pre nastavenie casoveho limitu }
                dT_deactive_FPLC_hi       = 25;      { hi - horna    -//-                                 }


             cfg_DEACTIVE_NOPL = 'DEACTIVE NOPL';
             dT_deactive_NOPL     : int  = 15; {'}  { po tomto limite sa zmaze NOPL }
                dT_deactive_NOPL_lo      =  1;      { lo - spodna hranica pre nastavenie casoveho limitu }
                dT_deactive_NOPL_hi      = 60;      { hi - horna    -//-                                 }


     const   { ak v danych int od ext pridu stripy,
               upravi sa datum namiesto implicitne
               nastaveneho datumu prijatia spravy :
             }
              est_dT_pred   : int = 6; { 18-24.oo a cas na prvom bode >24.oo -> next_date    }
              est_dT_po     : int = 2; { 24.oo-02.oo a cas na prvom bode <24.oo -> prev_date }


     const   poz_est_FPLC : Tpozs = [poz_PREACTIVE,poz_PROPOSED,poz_COORDINATED,
                                     poz_COORDINATED,
                                     poz_START,
                                     poz_LETI,poz_DALSI,poz_STOJI,poz_MZP,
                                     poz_PRIST, poz_PATRAT,
                                     poz_SEDI
                                    ];


     const   cfg_ENABLE_CPL    = 'CPL ENABLE';
             FPLC_CPL          : bool = false;
             cfg_ENABLE_CPL_SSR  = 'CPL-SSR ENABLE';
             FPLC_CPL_SSR      : bool = {$IFDEF LZIB_MACC} true {$ELSE} false {$ENDIF};

             cfg_EST_ARR       = 'ESTIMATE ARR';
             FPLC_ARR           : bool = true;                     { prepocitat cas pristatia po prijati stripu ?       }

             cfg_ENABLE_FPLC   = 'EDIT FPLC';
             ENABLE_FPLC       : bool = {$IFDEF ATCA}
                                           true
                                        {$ELSE}
                                          {$IFDEF PROCESS_FPLC}
                                            true
                                          {$ELSE}
                                            false
                                          {$ENDIF}
                                        {$ENDIF};

             FPLC_CHECK_15     : bool = true;                       { kontrola bodov v stripe }
             FPLC_15_MIL_OB    : bool = {$IFDEF ATCA} false {$ELSE} true {$ENDIF};


             cfg_prehlad_arch_fn_cFPL   = 'SEARCH IN FPLC ARCHIVE'; { na kolko hodin spat sa prehliadaju archivy s planmi FPLc}
             prehlad_arch_fn_cFPL: byte = 2;
               prehlad_arch_fn_cFPL_lo  = 1;
               prehlad_arch_fn_cFPL_hi  = 6;


     const   find_and_process_FPLC : bool = {$IFDEF OPL} false {$ELSE} true {$ENDIF};


     const   pis_STRIP_cFPL : bool    = {$IFDEF EDD} false {$ELSE} true {$ENDIF};
             miniSTRIP_cFPL : T_strip = {$IFDEF EDD} full_strip {$ELSE} full_strip {$ENDIF};



     {$IFDEF FLI_COORDINATION}
      const  display_FLI_ERR : bool = true;
             is_FLI_ERR      : bool = false;   { vypoctova premenna }
             send_FLI        : bool = true;

             limit_FLI : int = 1;   limit_FLI_lo = 0; limit_FLI_hi = 120;

             update_FPLC_by_FLI : bool = {$IFDEF DEBUG} true {$ELSE} false {$ENDIF};
             delete_FPLC_by_FLI : bool = {$IFDEF DEBUG} true {$ELSE} false {$ENDIF};
     {$ENDIF}


