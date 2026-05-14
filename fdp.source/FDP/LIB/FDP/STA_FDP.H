      { denna/mesacna statistika;
        ! nepocita sa s tym, ze polozka mesacnej statistiky
          ma dynamicku velkost
      }
       type  PStaFDP     = pointer;         { abstraktny typ na zaznam o polozke statistiky daneho typu }
             PStadFDPs   = pointer;         { abstraktny typ na zaznam o dennej polozke statistiky daneho typu }

             PStaMesFDPs = ^TStaMesFDPs;    { mesacny sumar abstraktnych typov -//- }
             TStaMesFDPs = array[1..31] of PStadFDPs;


       type  T_zapis_sumarneho_zaznamu     = procedure (fn: string; _stad: PStadFDPs);
             T_nacitanie_sumarneho_zaznamu = function  (fn: string; _stad: PStadFDPs): bool;


      { objekt spoloznych vlastnosti vsetkych spracovavanych statisickych typov,
      }
       type  POStaFDP = ^OStaFDP;
             OStaFDP  = object {(TObject)}

               najdlhsi_nazov       : byte; { najdlsi nazov polozky               }
               sledovanych_poloziek : byte;
               prepocitavat_pri_uzatvarani: bool;

               data_ext       : string[4];  { rozsirenie specifikujuce typ subora }
               sta_size       : word;       { velkost statistickej polozky        }
               p_new_sta,
               p_disp_sta     : pointer;    { odalokovanie }

               db_sta_code    : pointer;    { @TDBcode_proc                       }
               db_sta_decode  : pointer;    { @TDBdecode_proc                     }
               db_key_code    : pointer;    { @TDBcode_proc                       }
               db_sta_riadkov : byte;

               stad_size        : word;     { velkost denneho zaznamu             }
               p_new_stad,
               p_disp_stad      : pointer;  { odalokovanie }
               p_zapis_stad,
               p_nacitanie_stad : pointer;
               {p_stad        : PStadFDPs;   denna_statistika                    }


              { inicializacia
              }
               constructor  Init(_data_ext : string;

                                 _sta_size   : word;
                                 _p_new_sta, _p_disp_sta : pointer;

                                 _db_sta_code    : pointer;
                                 _db_sta_decode  : pointer;
                                 _db_key_code    : pointer;
                                 _db_sta_riadkov : byte;

                                 _stad_size  : word;
                                 _p_new_stad, _p_disp_stad : pointer;
                                 _p_zapis_stad, _p_nacitanie_stad : pointer;

                                 _sledovanych_poloziek : byte;

                                 _cfg_STA : string
                                );
               destructor   Done; virtual;

               procedure    nacitaj_cfg(_cfg_STA: string); virtual;
               function     najdi_najdlhsi_nazov: byte; virtual;

               procedure    initialize_sta  (data: pointer; _sta: PStaFDP); virtual;
               procedure    new_sta   (_stap: PStaFDP; var _sta: PStaFDP);

               procedure    disp_sta  (var _sta: PStaFDP);

               procedure    initialize_stad (_stad: PStadFDPs); virtual;
               procedure    new_stad  (_stap: PStadFDPs; var _stad: PStadFDPs);
               procedure    disp_stad_(_stad: PStadFDPs);
               procedure    disp_stad (var _stad: PStadFDPs);


              { zapis
              }
               { subor so sledovanym stavom kazdej polozky
               }
                function     zapisat_polozku (date: TDate; data: pointer): bool; virtual;
                procedure    zapis_polozky   (date: TDate; data: pointer);

               { pracovny binarny subor so sledovanym celkovym stavom za den
               }
                function     zmenene_parametre_statistiky (_stad : PStadFDPs): bool; virtual;
                procedure    zapis_sumarneho_zaznamu      (date: TDate; _stad: PStadFDPs); virtual;
                function     nacitanie_sumarneho_zaznamu  (date: TDate; _stad: PStadFDPs): bool; virtual;

                procedure    aktualizacia_denneho_zaznamu (_sta,_stap: PStaFDP; _stad: PStadFDPs; reset: bool); virtual;
                procedure    nacitanie_denneho_sumarneho_zaznamu
                                                          (date: TDate; _stad: PStadFDPs;
                                                           nacitaj,uloz,uzatvor: bool;
                                                           var zmena: bool
                                                          );

                procedure    aktualizacia_sumarneho_zaznamu_dnom (_sta_suma, _sta_ciastocny : PStadFDPs); virtual;
                procedure    nacitanie_mesacneho_sumarneho_zaznamu
                                                          (date: TDate; _stam: PStadFDPs;
                                                           nacitaj,uloz,uzatvor: bool;
                                                           var zmena: bool
                                                          );
                procedure    vytvorenie_mesacneho_sumarneho_zaznamu (date: TDate);


              { spracovanie - uzatvorenie, zobrazenie,tlac,kopirovanie...
              }
               { zatial nepouzite spracovanie
               function     nazov_polozky (polozka: int): string; virtual;
               function     hodnoty_polozky_za_den (polozka: int; _stad: PStadFDPs): string; virtual;
               procedure    zapis_riadok_statistiky   (fn: string; p: pchar);
               function     zapis_poloziek_statistiky (fn: string; _stam: PStaMesFDPs; _dni: int): bool; virtual;
               function     vytvor_tabulku_statistiky (date: TDate): string;
               }

               function     zapis_hlavicku_za_          (var fT: text;
                                                         p_stad: PStadFDPs; date: TDate; externy: bool
                                                        ): bool; virtual;
               function     zapis_riadok_za_            (var fT: text; riadok: int;
                                                         p_stad: PStadFDPs; date: TDate; externy: bool
                                                        ): bool; virtual;
               function     napln_zaznam_statistiky_za_ (fn: string;
                                                         p_stad: PStadFDPs; date: TDate; externy: bool
                                                        ): string; virtual;

               function     vytvor_zaznam_statistiky_za_den (date: TDate; uzatvor,vytvor_subor,externy: bool): string;
               function     vytvor_zaznam_statistiky_za_mesiac (date: TDate; uzatvor,vytvor_subor,externy: bool): string;

               {procedure    zobraz_priebeznu_statistiku_za_(den: bool);}
             end;
