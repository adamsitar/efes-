      const  cfg_soh1_PLN = 'PLN SOH1';
             cfg_soh2_PLN = 'PLN SOH2';
             cfg_eoh_PLN  = 'PLN EOH';
             cfg_adr_PLN  = 'PLN ADR';

             soh1_PLN : string  =       { idenitfikator zaciatku }
                {$IFDEF UKBB}
                  '‹€ ';            { UKBZ';}
                {$ELSE}
                  '‹€ ';            { UKBZ';}
                {$ENDIF}

             soh2_PLN : string  =       { druhy riadok }
                {$IFDEF UKBB}
                  ' … ‰ ‘  ’ˆ  ‚›‹…’    ‚•„      ‚›•„     ‘€„Š€  Œ… €‡';
                {$ELSE}
                  ' … ‰ ‘  ’ˆ  ‚›‹…’    ‚•„      ‚›•„     ‘€„Š€  Œ… €‡';
                {$ENDIF}

             eoh_PLN : string   =       { ukoncenie textu }
                {$IFDEF UKBB}
                   'Š…–';
                {$ELSE}
                   'Š…–';
                {$ENDIF}

             adr_PLN : string   =
                {$IFDEF UKBB}
                   'UKBZ';
                {$ELSE}
                   '';
                {$ENDIF}

             pln_idn  = ' … ‰ ‘';
             pln_typ  = '’ˆ';
             pln_dep  = '‚›‹…’';
             pln_eet  = '‚•„';
             pln_exi  = '‚›•„';
             pln_arr  = '‘€„Š€';
             pln_src  = 'Œ… €‡';

             ipln_idn : byte = 1;
             ipln_typ : byte = 10;
             ipln_dep : byte = 15;
             ipln_eet : byte = 24;
             ipln_exi : byte = 34;
             ipln_arr : byte = 44;
             ipln_src : byte = 53;


