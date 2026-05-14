     const  fnERR_L4 = 'errors.'+language;      { subor, kde su chybovie hlasky }


     const  a_ICAO = 'ICAO';
            a_L4   = 'L4444';
            a_TLG  = 'TLG';
            a_FUA  = 'FUA';

            a_FDP  = 'FDP';
            a_RTE  = 'RTE';
            a_OPL  = 'OPL';
            a_STA  = 'STA';

            a_PLN  = 'PLN';
            a_RPL  = 'RPL';
            a_FPL4 = 'FPL4';
            a_FPLM = 'FPLM';


     function   l4_err (arrpos,arrspec: string; errpos, errspec: word; var errs: string): word;
     function   l4_errs(arrpos,arrspec: string; errspec: word): string;


     const  err_icao_neznama_sprava               = 1;
            err_icao_iny_format                   = 2;
            err_icao_iny_udaj                     = 3;
            err_icao_ina_dlzka                    = 4;

            err_l4444_nenajdene_udaje             = 20;
            err_l4444_nenajdeny_fpl               = 21;

            err_l4444_neznama_sprava              = 50;
            err_l4444_iny_format                  = 51;
            err_l4444_chybaju_polia               = 52;

            err_l4444_cislo                       = 100;

            err_l4444_time                        = 101;
            err_l4444_date                        = 102;
            err_l4444_date_not_actual             = 103;
            err_l4444_date_duplicite              = 104;

            err_l4444_vyska_chyba                 = 200;
            err_l4444_rych_chyba                  = 250;

            {err_alt_chyba                         = 15;
            err_alt_nepovolena                    = 16;
            err_alt_nespravna                     = 17;}

            err_bod_neznamy                       = 65;
            err_area_vztazny_bod                  = 500;


            err_3_actualized                      = 10;


            err_7a_missing                        = 1;
            err_7a_length                         = 2;
            err_7b_missing                        = 5;

            err_7a_chng1                          = 10;
            err_7a_chng2                          = 11;
            err_7a_chng3                          = 12;

            err_8a                                = 1;
            err_8a_type                           = 11;
            err_8a_route                          = 12;
            err_8b                                = 1;

            err_9b_neznamy                        = 1;
            err_9c_odlisny                        = 1;

            err_10a_nezname                       = 1;
            err_10a_N                             = 2;
            err_10a_kombinacia                    = 3;
            err_10b_nezname                       = 1;
            err_10b_dlzka                         = 2;
            err_10b_popis                         = 3;


            err_13a_neznamy                       = 1;
            err_13b_neznamy                       = 1;
            err_13c_chybny                        = 1;

            err_16a_neznamy                       = 1;
            err_16b_neznamy                       = 1;
            err_16c_chybne                        = 1;

            err_17a_neznamy                       = 1;
            err_17b_neznamy                       = 1;
            err_17c_chybne                        = 1;


            err_14a_neznamy                       = 1;
            err_14b_neznamy                       = 1;
            err_14c_neznamy                       = 1;
            err_14d_neznamy                       = 1;
            err_14e_neznamy                       = 1;


            err_15a_chybne                        = 1;
            err_15a_lo                            = 2;
            err_15a_hi                            = 3;

            err_15b_chybne                        = 1;
            err_15b_lo                            = 2;
            err_15b_hi                            = 3;

            err_15c_chyba_bod                     = 2;
            err_15c_chyba_rych                    = 3;
            err_15c_chyba_vys                     = 4;
            err_15c_chyba_C                       = 5;
            err_15ab_chybne                       = 7;
            err_15c_chybna_rych                   = 8;
            err_15c_chybna_vys                    = 9;

            err_15c_nenajdena_trat_cez_fir        = 11;
            err_15c_nenajdene_zname_body_trate    = 12;
            err_15c_nepovolene_mzp                = 15;

            err_15c_neurceny_priesecnik_trati     = 25;
            err_15c_viac_priesecnikov_trati       = 26;
            err_15c_niet_priesecnikov_trati       = 27;

            err_15c_bod_daleko_od_trate           = 28;
            err_15c_bod_nepatri_na_trat           = 30;

            err_15c_body_roznych_trati_bez_dct    = 31;
            err_15c_ocakavane_dct                 = 32;

            err_15c_trat_daleko_od_dep            = 36;
            err_15c_trat_daleko_od_arr            = 37;
            err_15c_nenajdeny_vstupny_bod_trate   = 38;
            err_15c_nenajdeny_vystupny_bod_trate  = 39;

            err_15c_kolecko                        = 49;
            {err_15c_nenajdeny_vstup_vystup_bod_fir = 50;}
            err_15c_trat_nezacina_vo_fir           = 51;
            err_15c_trat_nekonci_vo_fir            = 52;
            err_15c_nenajdena_trat_pre_let_vo_fir  = 60;

            err_15c_nespravny_casovy_profil        = 80;

            err_15c_firmap_notfound                = 100;


            err_18_date_format                     = 20;
            err_18_date_not_actual                 = 21;

            err_18_vyzaduje_specifikaciu_eet       = 80;
            err_18_chyba_v_specifikacii_eet        = 81;

            err_18_zzzz_vyzaduje_specfikaciu       = 100;
            err_18_zzzz_vyzaduje_specfikaciu_ap    = 101;
            err_18_vyzaduje_specfikaciu_10         = 102;


            err_22_                                = 1;


            err_rte_missing_dep                    = 10;
            err_rte_missing_arr                    = 11;
            err_rte_missing_eet                    = 12;
            err_rte_missing_exi                    = 13;

            err_rte_neuplny_bod                    = 20;
            err_rte_ukonceny_let                   = 34;
