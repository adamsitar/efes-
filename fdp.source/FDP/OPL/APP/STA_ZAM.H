     { sledovane udaje ZAM
     }
      type  PZAM_sta = ^TZAM_sta;            { zaznam pre sledovanie vyvoja planu }
            TZAM_sta = record
              key : string;                    { kluc pre urcenie letu }
              let : string[kod_AP];
              sta : TStaSum;                   { sledovane udaje       }
            end;


      type  PZAMs_staDen = ^TZAMs_staDen;    { zaznam pre denny sumar letov }
            TZAMs_staDen = record
              zam : TFPLM_letov;             { letiskove lety }
            end;


      const db_riadkov_ZAM_sta = 1;
            db_sta_ZAM_sta     = 0;


      type  POStatistikaZAM = ^OStatistikaZAM;
            OStatistikaZAM  = object(OStaFDP)

             { inicializacia
             }
              constructor  Init(_cfg_FN: string);

              procedure    initialize_sta (data: pointer; _sta: PStaFDP); virtual;
              procedure    aktualizacia_denneho_zaznamu (_sta,_stap: PStaFDP; _stad: PStadFDPs; reset: bool); virtual;
              procedure    aktualizacia_sumarneho_zaznamu_dnom (_sta_suma, _sta_ciastocny : PStadFDPs); virtual;
            end;


      const sta_ZAM : POStatistikaZAM = nil;


