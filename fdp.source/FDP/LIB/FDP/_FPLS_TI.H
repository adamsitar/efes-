       const

            { -------------------------
               SLOVAK
              -------------------------
            }
             {$IFDEF SLOVAK}
               inf_FPL            = 'Letovò pl†n';
               tit_FPL            = 'Letovò pl†n';
               tit_MASKA          = 'ódaje pl†nu/skupiny';


             { spracovanie a prehlad FPL
             }
               msg_FPLc_EST       = 'SPRèVA O LETE PO TRATI LPS';
               msg_FPLc_ACT       = 'AKTIVèCIA LETU PO TRATI LPS';
               msg_FPLc_CHG       = 'OPRAVA SPRèVY O LETE PO TRATI LPS';
               msg_FPLc_CNL       = 'ZRUõENIE SPRèVY O LETE PO TRATI LPS';

               msg_FPLm           = 'PODANIE VOJENSKêHO LETOVêHO PLèNU ';
               msg_FPLm_CHG       = 'OPRAVA VOJENSKêHO LETOVêHO PLèNU ';
               msg_FPLm_CNL       = 'ZRUõENIE VOJENSKêHO LETOVêHO PLèNU';
               ask_fpl_CNL        = 'Naozaj zru®iü letovò pl†n';

               msg_FPL_RPL_CHG    = 'OPRAVA VZORU LETOVêHO PLèNU PRE LET MIMO TRATã LPS';
               ask_FPL_RPL_CNL    = 'Zru®iü vzor letovÇho pl†nu pre';


              {$ifdef airbase}
               msg_FPL_REQ        = 'íIADOSÜ O VYDANIE PRIPOMIENKY';
               msg_FPL_REQ_       = 'íiadosü o vydanie pripomienky pre :';
              {$else}
               msg_FPL_REQ        = 'VYDANIE PRIPOMIENKY K LETU';
               msg_REQdone1       = 'Pripomienka pre';
               msg_REQdone2       = 'bola uë vydan†.';
              {$endif}

               msg_req            = 'Pripomienka pre';
               msg_req_acc        = ': pl†n schv†lenò.';
               msq_req_dec        = ': pl†n neschv†lenò.';
               msq_req_repeat     = 'OpÑtovnÇ vyslanie ëiadosti o pripomienku pre';

               msg_plan_pre       = 'Pl†n pre';
               msg_s_pripomienkou = 'schv†lenò s pripomienkou :';
               msg_opraveny       = 'bol schv†lenò a opravenò (SRLP) :';


               msg_FPL_DEP        = 'õTART LETU';
               ask_not_FPL_ACC    = ' nebol schv†lenò. Od®tartovaü napriek tomu ?';
               msg_cas_DEP        = 'Äas ®tartu ';
               msg_dtcas_DEP      = 'Äas ®tartu sa l°®i o viac ako ';
               ask_REQ            = 'Mus°te vyëiadaü pripomienku.';


               msg_FPL_MZP        = 'MEDZIPRISTèTIE';
               msg_FPL_MZS        = 'õTART PO MEDZIPRISTèTã';

               msg_FPL_RTE        = 'OPRAVA TRATE LETU';


               msg_FPL_ARR        = 'PRISTèTIE LETU';
               msg_FPL_ARRW       = 'OÄAKèVANê SPRèVY O PRISTèTã';
               msg_cas_ARR        = 'Äas prist†tia ';


               msg_LET_PLAN       = ' NAPLèNOVANùCH LETOV';
               msg_LET_PROP       = ' SCHVAúOVANùCH LETOV';
               msg_LET_DEP        = ' ODõTARTOVANùCH LETOV';
               msg_LET_ARR        = ' REALIZOVANùCH LETOV';

               msg_FPL_RPL        = 'VZORY FPL'; {(OPAKUJóCE SA, RPL)}

               tit_RTE            = 'Zobrazenie trate';


               tit_actcFPL_PROP   = 'PrijatÇ spr†vy o letoch po tratiach LPS';

               tit_actcFPL        = 'Prehåad civilnòch letov:';
               tit_actmFPL        = 'Prehåad vojenskòch letov:';
               tit_actoFPL        = 'Prehåad ostatnòch letov: ';

               tit_fnsh_cFPL      = 'UkonáenÇ civilnÇ lety';
               tit_fnsh_mFPL      = 'UkonáenÇ vojenskÇ lety';
               tit_fnsh_oFPL      = 'UkonáenÇ inÇ lety';

               tit_reload_cFPL    = 'Ukonáenò civilnò let';
               tit_reload_mFPL    = 'Ukonáenò vojenskò let';
               tit_reload_oFPL    = 'Ukonáenò inò let';

               tit_arch_cFPL      = 'ArchivovanÇ civilnÇ letovÇ pl†ny';
               tit_arch_mFPL      = 'ArchivovanÇ vojenskÇ letovÇ pl†ny';
               tit_arch_oFPL      = 'ArchivovanÇ ostatnÇ letovÇ pl†ny';
               tit_arch_KRL       = 'ArchivovanÇ pl†ny kr°diel';


              { fpl4
              }
               tit_fpl_copy      = 'COPY OF FPL';
               tit_fpl_chg       = 'CHANGE OF FPL';
               tit_fpl_dla       = 'DEPARTURE DELAY';
               tit_fpl_cnl       = 'CANCELATION OF FPL';
               tit_fpl_dep       = 'DEPARTURE OF FLIGHT';
               tit_fpl_arr       = 'ARRIVAL OF FLIGHT';
               tit_fpl_act       = 'ACTIVATION OF FLIGHT';

               tit_fpl_alr       = 'ALERT ON FLIGHT';
               tit_fpl_rcf       = 'RADIO COMMUNICATION FAILURE';


               tit_fpl_anp       = 'çÄêìòÖçàÖ èéêüÑäÄ àëèéãúáéáÇÄçàü ÇéáÑìòçéÉé èêéëíêÄçëíÇÄ';
               tit_fpl_fla       = 'çÄèêÄÇãÖçàÖ ÇéáÑìòçéÉé ëìÑçÄ çÄ áÄèÄëçéâ Äùêéèéêí';
               tit_fpl_fli       = 'èêéãÖí èìçäíéÇ éÅüáÄíÖãúçõï ÑéçÖëÖçàâ / ÉéëìÑÄêëíÇÖççéâ ÉêÄçàñõ';


               tit_KRL            = 'KRãDLO';
               tit_KRLnase        = 'PREHúAD KRãDEL PRE VLASTNê LETY';
               tit_KRLine         = 'PREHúAD KRãDEL PODANùCH PRE INê LETISKè';
               tit_KRLvsetky      = 'PREHúAD VõETKùCH SPRACOVèVANùCH KRãDEL';

               tit_KRLsprac       = 'KRãDLA SPRACOVèVAnê NA/PRE ';
               tit_KRLpre         = 'KRãDLO PRE';

               msg_KRL_CHG        = 'OPRAVA KRãDLA';
               msg_KRL_CNL        = 'ZRUõENIE KRãDLA';
               ask_krl_CNL        = 'Naozaj zru®iü kr°dlo';
               msg_KRL_FPL        = 'SPRACOVANIE KRãDLA - PODANIE PLèNU LETU';
             {$ENDIF}


            { -------------------------
               CZECH
              -------------------------
            }
             {$IFDEF CZECH}
               inf_FPL            = 'Letovò pl†n';
               tit_FPL            = 'Letovò pl†n';
               tit_MASKA          = 'ódaje pl†nu/skupiny';


             { spracovanie a prehlad KRL
             }
               tit_KRL_oprava  = ' ~O~PRAVA PODANêHO KRãDLA ';
               tit_KRL_zrus    = ' ~Z~RUõENIE PODANêHO KRãDLA ';
               tit_KRL_sprac   = ' ~S~PRACOVANIE PRIJATêHO KRãDLA ';

               tit_KRL_odos_   = ' O~D~OSLANIE NA ';
               tit_KRL_oprava_ = ' ~O~PRAVA KRãDLA ';
               tit_KRL_zrus_   = ' ~Z~RUõENIE KRãDLA ';
               tit_KRL_sprac_  = ' ~S~PRACOVANIE KRãDLA ';

               tit_KRL         = 'KRãDLO';
               tit_KRLpod      = 'PREHúAD PODANùCH KRãDEL Z ';
               tit_KRLpri      = 'PREHúAD KRãDEL PRIJATùCH PRE ';
               tit_KRLsprac    = 'KRãDLA SPRACOVèVAnê NA/PRE ';
               tit_KRLpre      = 'KRãDLO PRE';

               msg_KRL_CHG     = 'OPRAVA PODANêHO KRãDLA';
               msg_KRL_CNL     = 'ZRUõENIE PODANêHO KRãDLA';
               ask_krl_CNL     = 'Naozaj zru®iü kr°dlo';
               msg_KRL_FPL     = 'SPRACOVANIE KRãDLA - PODANIE PLèNU LETU';


             { spracovanie a prehlad FPL
             }
               msg_FPLc_EST    = 'ZPRèVA EST O LETU PO TRATI LPS';
               msg_FPLc_ACT    = 'AKTIVACE LETU PO TRATI LPS';
               msg_FPLc_CHG    = 'OPRAVA ZPRèVY O LETU PO TRATI LPS';
               msg_FPLc_CNL    = 'ZRUõENã ZPRèVY O LETU PO TRATI LPS';

               msg_FPLm        = 'PODèNã VOJENSKêHO LETOVêHO PLèNU';
               msg_FPLm_CHG    = 'OPRAVA VOJENSKêHO LETOVêHO PLèNU';
               msg_FPLm_CNL    = 'ZRUõENã VOJENSKêHO LETOVêHO PLèNU';
               ask_fpl_CNL     = 'Zru®it letovò pl†n';

               msg_FPL_RPL_CHG = 'OPRAVA VZORU LETOVêHO PLèNU PRO LET MIMO TRATã LPS';
               ask_FPL_RPL_CNL = 'Zru®it vzor letovÇho pl†nu pro';

              {$ifdef airbase}
               msg_FPL_REQ     = 'íIADOSÜ O VYDANIE PRIPOMIENKY';
              {$else}
               msg_FPL_REQ     = 'VYDANIE PRIPOMIENKY K LETU';
              {$endif}

               msg_FPL_DEP     = 'õTART LETU';
               ask_not_FPL_ACC = ' nebol schv†lenò. Od®tartovaü napriek tomu ?';
               msg_cas_DEP     = 'Äas ®tartu ';
               msg_dtcas_DEP   = 'Äas ®tartu sa l°®i o viac ako ';
               ask_REQ         = 'Mus°te vyë†dat p©ipom°nku.';

               msg_FPL_MZP     = 'MEDZIPRISTèTIE';
               msg_FPL_MZS     = 'õTART PO MEDZIPRISTèTã';

               msg_FPL_RTE     = 'OPRAVA TRATE LETU';

               msg_FPL_ARR     = 'PRISTèTIE LETU';
               msg_FPL_ARRW    = 'OÄAKèVANê SPRèVY O PRISTèTã';
               msg_cas_ARR     = 'Äas prist†tia ';

               msg_LET_PLAN    = ' NAPLèNOVANùCH LET¶';
               msg_LET_PROP    = ' SCHVALOVANùCH LET¶';
               msg_LET_DEP     = ' ODSTARTOVANùCH LET¶';
               msg_LET_ARR     = ' REALIZOVANùCH LET¶';

               msg_FPL_RPL     = 'VZORY (OPAKUJãCI SE, RPL) FPL';

               tit_RTE           = 'Zobrazenie trate';


               tit_actcFPL_PROP  = 'P©ijatÇ zpr†vy o letech po trat°ch LPS';

                                   {'P©°choz° civiln° lety';}

               tit_actcFPL       = 'P©ehled civiln°ch letñ:';
               tit_actmFPL       = 'P©ehled vojenskòch letñ:';
               tit_actoFPL       = 'P©ehled ostatn°ch letñ: ';

               tit_fnsh_cFPL     = 'UkonáenÇ civiln° lety';
               tit_fnsh_mFPL     = 'UkonáenÇ vojenskÇ lety';
               tit_fnsh_oFPL     = 'UkonáenÇ ostatn° lety';

               tit_reload_cFPL   = 'Ukonáenò civiln° let';
               tit_reload_mFPL   = 'Ukonáenò vojenskò let';
               tit_reload_oFPL   = 'Ukonáenò jinò let';

               tit_arch_cFPL     = 'ArchivovanÇ civiln° letovÇ pl†ny';
               tit_arch_mFPL     = 'ArchivovanÇ vojenskÇ letovÇ pl†ny';
               tit_arch_oFPL     = 'ArchivovanÇ ostatn° letovÇ pl†ny';


              { fpl4
              }
               tit_fpl_copy      = 'COPY OF FPL';
               tit_fpl_chg       = 'CHANGE OF FPL';
               tit_fpl_dla       = 'DEPARTURE DELAY';
               tit_fpl_cnl       = 'CANCELATION OF FPL';
               tit_fpl_dep       = 'DEPARTURE OF FLIGHT';
               tit_fpl_arr       = 'ARRIVAL OF FLIGHT';
               tit_fpl_act       = 'ACTIVATION OF FLIGHT';

               tit_fpl_alr       = 'ALERT ON FLIGHT';
               tit_fpl_rcf       = 'RADIO COMMUNICATION FAILURE';


               tit_fpl_anp       = 'çÄêìòÖçàÖ èéêüÑäÄ àëèéãúáéáÇÄçàü ÇéáÑìòçéÉé èêéëíêÄçëíÇÄ';
               tit_fpl_fla       = 'çÄèêÄÇãÖçàÖ ÇéáÑìòçéÉé ëìÑçÄ çÄ áÄèÄëçéâ Äùêéèéêí';
               tit_fpl_fli       = 'èêéãÖí èìçäíéÇ éÅüáÄíÖãúçõï ÑéçÖëÖçàâ / ÉéëìÑÄêëíÇÖççéâ ÉêÄçàñõ';
             {$ENDIF}


            { -------------------------
               ENGLISH
              -------------------------
            }
             {$IFDEF ENGLISH}

               inf_FPL            = 'FLight plan';
               tit_FPL            = 'FLight plan';
               tit_MASKA          = 'Mask of plan/group';


               msg_FPLc_EST       = 'MESSAGE EST OF ATS-ROUTE FLIGHT';
               msg_FPLc_ACT       = 'ACTIVATION OF ATS-ROUTE FLIGHT';
               msg_FPLc_CHG       = 'CORECTION OF ATS-ROUTE FLIGHT';
               msg_FPLc_CNL       = 'CANCELATION OF ATS-ROUTE FLIGHT';

               msg_FPLm           = 'MILITARY FPL';
               msg_FPLm_CHG       = 'CORECTION OF MILITARY FPL ';
               msg_FPLm_CNL       = 'CANCELATION OF MILITARY FPL';
               ask_fpl_CNL        = 'Really cancel flight plan';

               msg_FPL_RPL_CHG    = 'CORRECTION OF THE MILITARY FPL SAMPLE';
               ask_FPL_RPL_CNL    = 'Really cancel flight plan sample of';


              {$ifdef airbase}
               msg_FPL_REQ        = 'REQUEST FOR FPL APPROVAL';
               msg_FPL_REQ_       = 'Request for approval FPL of ';
              {$else}
               msg_FPL_REQ        = 'APPROVAL THE FLIGHT OF';
               msg_REQdone1       = 'FPL of the';
               msg_REQdone2       = 'was alredy approved.';
              {$endif}

               msg_req            = 'Request for the';
               msg_req_acc        = ': pl†n approved.';
               msq_req_dec        = ': pl†n disabled.';
               msq_req_repeat     = 'Repeat request for approval FPL of ';

               msg_plan_pre       = 'Pl†n for';
               msg_s_pripomienkou = 'approved with the remark :';
               msg_opraveny       = 'was corrected and approved (MACC) :';


               msg_FPL_DEP        = 'FLIGHT DEPARTURE';
               ask_not_FPL_ACC    = ' was not approved. Does flight departure ?';
               msg_cas_DEP        = 'Departure time ';
               msg_dtcas_DEP      = 'Departure time is different from approved for more than ';
               ask_REQ            = 'There is requested flight approval.';


               msg_FPL_MZP        = 'STOPOVER';
               msg_FPL_MZS        = 'DEPARTURE FROM STOPOVER';

               msg_FPL_RTE        = 'ROUTE CORRECTION';


               msg_FPL_ARR        = 'FLIGHT ARRIVAL';
               msg_FPL_ARRW       = 'AWAITED FLIGHT ARRIVAL';
               msg_cas_ARR        = 'Flight arrival ';


              { menu
              }
               msg_LET_PLAN       = ' PLANNED FLIGHTS';
               msg_LET_PROP       = ' APPROVED FLIGHTS';
               msg_LET_DEP        = ' DEPARTURED FLIGHTS';
               msg_LET_ARR        = ' ARRIVED FLIGHTS';

               msg_FPL_RPL       = 'FPL SAMPLES';

               tit_RTE           = 'Route presentation';

               tit_actcFPL_PROP  = 'Received strips with data of ATS-route flights';

               tit_actcFPL       = 'ATS-route flights';
               tit_actmFPL       = 'Military flights';
               tit_actoFPL       = 'Others flights';

               tit_fnsh_cFPL     = 'Finished ATS-route flights';
               tit_fnsh_mFPL     = 'Finished military flights';
               tit_fnsh_oFPL     = 'Finished other flights';

               tit_reload_cFPL   = 'Finished ATS-route flight';
               tit_reload_mFPL   = 'Finished military/other flight';
               tit_reload_oFPL   = 'Finished other flight';

               tit_arch_cFPL     = 'Archived ATS-route flights';
               tit_arch_mFPL     = 'Archived military flights';
               tit_arch_oFPL     = 'Archived other flights';
               tit_arch_KRL      = 'Archived pre-pl†ns';


              { fpl4
              }
               tit_fpl_copy      = 'COPY OF FPL';
               tit_fpl_chg       = 'CHANGE OF FPL';
               tit_fpl_dla       = 'DEPARTURE DELAY';
               tit_fpl_cnl       = 'CANCELATION OF FPL';
               tit_fpl_dep       = 'DEPARTURE OF FLIGHT';
               tit_fpl_arr       = 'ARRIVAL OF FLIGHT';
               tit_fpl_act       = 'ACTIVATION OF FLIGHT';

               tit_fpl_alr       = 'ALERT ON FLIGHT';
               tit_fpl_rcf       = 'RADIO COMMUNICATION FAILURE';


               tit_fpl_anp       = 'çÄêìòÖçàÖ èéêüÑäÄ àëèéãúáéáÇÄçàü ÇéáÑìòçéÉé èêéëíêÄçëíÇÄ';
               tit_fpl_fla       = 'çÄèêÄÇãÖçàÖ ÇéáÑìòçéÉé ëìÑçÄ çÄ áÄèÄëçéâ Äùêéèéêí';
               tit_fpl_fli       = 'èêéãÖí èìçäíéÇ éÅüáÄíÖãúçõï ÑéçÖëÖçàâ / ÉéëìÑÄêëíÇÖççéâ ÉêÄçàñõ';
             {$ENDIF}

