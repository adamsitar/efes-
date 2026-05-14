     { sledovane udaje FPLC
     }
      type  PFPLC_sta = ^TFPLC_sta;            { zaznam pre sledovanie vyvoja planu }
            TFPLC_sta = record
              key : string;                    { kluc pre urcenie letu }
              sta : TStaPlan;                  { sledovane udaje       }
              vfr : bool;
              fl  : word;                      { najvyssia fl na trati ako "S" }
            end;


      type  PFPLCs_staDen = ^TFPLCs_staDen;    { zaznam pre denny sumar letov }
            TFPLCs_staDen = record
              sta : TStaSum;                   { sledovane udaje }
              fl  : word;                      { pocet vysok > ako sledovana hodnota }
              fl_ : word;                      { udaj sledovanej vysky v "m" pre pripad zmeny a nasledneho prepoctu }
              vfr : word;
            end;


      const db_riadkov_FPLC_sta = 1;
            db_sta_FPLC_sta     = 0;


      type  POStatistikaFPLC = ^OStatistikaFPLC;
            OStatistikaFPLC  = object(OStaFDP)

             { inicializacia
             }
              constructor  Init(_cfg_FN: string);

              procedure    nacitaj_cfg(_cfg_FN: string); virtual;
              function     najdi_najdlhsi_nazov: byte; virtual;

              procedure    initialize_sta  (data: pointer; _sta: PStaFDP); virtual;
              procedure    initialize_stad (_stad: PStadFDPs); virtual;


             { zapis
             }
              function     zapisat_polozku (date: TDate; data: pointer): bool; virtual;
              procedure    aktualizacia_denneho_zaznamu (_sta,_stap: PStaFDP; _stad: PStadFDPs; reset: bool); virtual;
              procedure    aktualizacia_sumarneho_zaznamu_dnom (_sta_suma, _sta_ciastocny : PStadFDPs); virtual;
              function     zmenene_parametre_statistiky (_stad : PStadFDPs): bool; virtual;


             { spracovanie - uzatvorenie, zobrazenie,tlac,kopirovanie...
             }
              {function     nazov_polozky (polozka: int): string; virtual;
              function     hodnoty_polozky_za_den (polozka: int; _stad: PStadFDPs): string; virtual;}

              function     zapis_hlavicku_za_          (var fT: text;
                                                        p_stad: PStadFDPs; date: TDate; externy: bool
                                                       ): bool; virtual;
              function     zapis_riadok_za_            (var fT: text; riadok: int;
                                                        p_stad: PStadFDPs; date: TDate; externy: bool
                                                       ): bool; virtual;
            end;


      const sta_FPLC : POStatistikaFPLC = nil;
