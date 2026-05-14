     { Metodika vyhodnotenia poctu planovanych a realizovanych
       vojenskych/inych letov :

       1. Tratove lety (prelety)
          ----------------------------
          Pocita sa ako jeden plan/let pre :
          - SRLP  : kazdy "podany"/"realizovany" plan letu (kazda poradova).
          - LSRLP : ak je vzlet z LSRLP tak "podany"/"realizovany",
                    inak ak vleti do riadenej oblasti TMA/CTR ineho letiska,
                    ako letiska startu, tak je "riadeny".

       2. Lety do TSA
          ------------
          Pocitaju sa ako tratove lety, ale okrem toho sa eviduje,
          v ktorych priestoroch bola planovana cinnost.


       3. Letiskove lety
          ---------------
          Zvlastny typ letov, kde sa eviduje pocet letov realizovanych
          v ramci zamestnania letiska.

     }

      type { ----------------------------
             Zaznam o jednom plane letu
             typu Tratovy/TSA
             ---------------------------
           }
           { Tratovy/TSA let - data o podanom plane
           }
             TFPLM_plan = record
              key : string[kod_FPLMkey];
              dep : string[kod_AP];
              src : string[kod_AP];

              rte : bool;                    { tratovy let  }
              mil : bool;                    { vojensky/iny }
              ifr : bool;

              tsa : bool;

              let : bool;                    { bol realizovany ? }
              fl  : word;                    { najvyssia planovana fl }
             end;

             TFPLM_par  = record
              flm,flo : word;                { sledovana vyska }
             end;

           { Tratovy let - data o riadenom lete,
             niektore udaje su uvedene vyssie
           }
             TFPLM_lsrlp_ = record
              riadeny : bool;                { bol riadeny danym pracoviskom ? }
             end;
                                             { zaznam o riadeni letu na jednotlivych stanovistiach }
             TFPLM_lsrlp  = array[0..max_AIRBASE] of TFPLM_lsrlp_;
             PFPLM_lsrlp  = ^TFPLM_lsrlp;


           { Udaje o Tratovom/TSA plane a lete
           }
             PFPLM_sta  = ^TFPLM_sta;
             TFPLM_sta  = record
              par   : TFPLM_par;
              plan  : TFPLM_plan;
              lsrlp : TFPLM_lsrlp;
              r_tsa : pchar;                 { zoznam priestorov, kde vykonaval cinnost }
             end;


           { ------------------------------
             Sumarna statistika o planoch
             letov za obdobie
             ------------------------------
           }

           { Sumarne udaje o typoch letov
           }
           { Sumarne udaje o priestoroch cinnosti
           }
      {type   TTSA_lety_   = record
              kod   : string[kod_PRS];
              lety  : TFPLM_letov;
             end;
             PTSA_lety_   = ^TTSA_lety_;

      const  max_TSAlety  = MAX_ARRAY_SIZE div sizeof(TTSA_lety_);
      type   TTSA_lety    = array[0..max_TSAlety-1] of TTSA_lety_;
             PTSA_lety    = ^TTSA_lety;

             TTSA_letov   = record
              pocet : int;
              tsa   : PTSA_lety;
             end;}
             TTSA_letov  = array[0..max_AIRBASE] of pchar;


           { Denna statistika
           }
      type   PFPLMs_staDen = ^TFPLMs_staDen; { zaznam pre sledovanie vyvoja planu }
             TFPLMs_staDen = record
               par     : TFPLM_par;

               mil     : TFPLM_letov;         { tratove vojenske lety   }
               mil_ifr : TFPLM_letov;
               mil_fl  : TFPLM_letov;
               ine     : TFPLM_letov;         { tratove ine lety   }

               zam     : TFPLM_letov;         { letiskove lety }

               tsa     : TFPLM_letov;         { pocet letov do vycvikovych priestorov za kazde letisko }
               r_tsa   : TTSA_letov;          { vyuzivane priestory }
             end;


      const  db_riadkov_FPLM_sta = 2;
             db_sta_FPLM_sta     = 0;
             db_sta_FPLM_tsa     = 1;


      type   POStatistikaFPLM = ^OStatistikaFPLM;
             OStatistikaFPLM = object(OStaFDP)

               constructor  Init(_cfg_FN: string);

               procedure    nacitaj_cfg(_cfg_FN: string); virtual;
               function     najdi_najdlhsi_nazov: byte; virtual;

               procedure    initialize_sta  (data: pointer; _sta: PStaFDP); virtual;
               function     zapisat_polozku (date: TDate; data: pointer): bool; virtual;

               procedure    initialize_stad (_stad: PStadFDPs); virtual;
               procedure    aktualizacia_denneho_zaznamu (_sta,_stap: PStaFDP; _stad: PStadFDPs; reset: bool); virtual;
               procedure    aktualizacia_sumarneho_zaznamu_dnom (_sta_suma, _sta_ciastocny : PStadFDPs); virtual;
               function     zmenene_parametre_statistiky (_stad: PStadFDPs): bool; virtual;

               function     nazov_polozky (polozka: int): string; virtual;
               function     hodnoty_polozky_za_den (polozka: int; _stad: PFPLMs_staDen): string; virtual;
             end;


      const  sta_FPLM : POStatistikaFPLM = nil;


