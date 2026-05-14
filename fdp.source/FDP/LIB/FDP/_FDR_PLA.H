    { ----------------------------------
       zdroj planu FPL4
      תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
    }
    const  fplsrc_RPL = 1;            { fdp source ... }
           fplsrc_PLN = 2;
           fplsrc_FPL = 4;
           fplsrc_FDA = 8;

           fplsrcs    = 4;

    type   Tfplsrc    = word;



    { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
       Dekodovane udaje planu
      תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
    }
    type   PFDR = ^DFDR;
           DFDR = record
             idn  : string[kod_7a];
             typ  : string[kod_9b+1+kod_9c];

             dep  : TAP_;
             eet  : TOB_;                        { vypocitany vstup do oblasti }
             vys  : word;
             vys_ : char;
             exi  : TOB_;                        { vypocitany vystup z oblasti }
             arr  : TAP_;

             date : TDate;
             stat : string[kod_HEAD];

             rte  : POBxys;                      { dekodovana trat       }
             bodov: int;                         { pocet bodov trate     }

             fpl  : PFPLC;
             {data : pchar;                        poznamka: RPL,REG,... }

             src  : Tfplsrc;                     { zdroj informacie...    }
             poz  : Tpoz;
           end;


           TFDR_decoded_data = record
             check_en   : bool;

             isDATE     : bool;

             isEET      : bool;
              isEET_14  : bool;
              isEET_18  : bool;
              isEET_DEP : bool;
              isEET_ARR : bool;

             isDEP      : bool;
             isARR      : bool;

             dep,eet,
             exi,arr    : TOBxy;             { pomocne premenne }

             arr2       : string[kod_APb];

             prvy       : int;
           end;


           PFPL4_decoded_data = ^TFPL4_decoded_data;
           TFPL4_decoded_data = record
             fdr  : PFDR;
             cmnd : cm_spracovanie_FPL4;
           end;


    const  poz_est_FDR : Tpozs = [poz_PREACTIVE,poz_PROPOSED,poz_COORDINATED,
                                  poz_START..poz_PATRAT
                                 ];


          {$IFDEF DEBUG}   max_FDRs = 300;
          {$ELSE}
            {$IFDEF _DPMI} max_FDRs = 2000;
            {$ELSE}        max_FDRs = 500;
            {$ENDIF}
          {$ENDIF}

    type   PFDRs = ^TFDRs;
           TFDRs = array[0..MAX_PTRs-1] of PFDR;
