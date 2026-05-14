     { - sledovane udaje pre plany vyuzitia vzdusneho priestoru;
     }
      const  max_PRSsta = 300;

      type   TPRS_nazov = string[kod_PRS];
             TPRS_nazvy = array[0..max_PRSsta-1] of TPRS_nazov;
             PPRS_nazvy = ^TPRS_nazvy;

      const  PRS_nazvy  : PPRS_nazvy = nil;
             poc_PRS_nazvy : word = 0;



      type  { Denny popis priestoru
            }
             PPRS_sta  = ^TPRS_sta;
             TPRS_sta  = record
               key     : string;

               kod     : string[kod_PRS];
               typ     : string[kod_PRS];   { standartne '', pozemny ma GND }
               let     : string[kod_AP];
               nazov   : pchar;

               vyuzity : bool;
             end;


      const  db_riadkov_STA_sta = 1;
             db_sta_STA_prs     = 0;

             max_prs_nazov = 30;


      type  { Suhrnny popis priestoru
              za obdobie

              b) novo uchovavane udaje
                 - priestor moze byt jeden den (...) vyuzivany na :
                   - letecku cinnost : pocita sa pocet planov
                   - ako strelnica   : pocita sa pocet dni z obdobia 1 z 1 (3 z 29);
                                       1 z 1 je zbytocne, ale denny a dlhsi zaznam
                                       pouzivaju rovnake datove struktury
            }
             TPRSi_sum    = record
               planov_l        : word;  { pocet podanych planov na prs ako let. prs za... }
               vyuzitych_l     : word;  {       vyuzitych  -//- }
               letov_l         : word;  { pocet letov v prs }

               planov_s        : word;  { pocet podanych planov na prs ako strelnicu za... }
               vyuzitych_s     : word;  {       vyuzitych  -//- }
               planov_s_dni    : byte;  { pocet dni, za ktore boli plany podavane }
               vyuzitych_s_dni : byte;  {                  -//-          vyuzivane }
             end;
             TPRS_sum    = array[0..max_AIRBASE] of TPRSi_sum;

             PPRSi_sta    = ^TPRSi_sta;
             TPRSi_sta    = record
               kod        : string[kod_PRS];
               nazov      : pchar;
               stai       : TPRS_sum;
             end;

             PPRSs_sta    = ^TPRSs_sta;
             TPRSs_sta    = array[0..max_PRSsta-1] of PPRSi_sta;

             PPRSs_staDen = ^TPRSs_staDen;
             TPRSs_staDen = record
               den    : bool;              { urcenie typu statistiky pre vystupnu tabulku }
               pocet  : int;               { predstavte si, cyklus for i:= 0 to wordovsky pocet-1 -> aritmetic owerflow }
               stad   : TPRSs_sta
             end;


      type   POStatistikaPRS = ^OStatistikaPRS;
             OStatistikaPRS = object(OStaFDP)

               constructor  Init(_cfg_FN: string);
               destructor   Done; virtual;

               procedure    nacitaj_cfg(_cfg_FN: string); virtual;

               procedure    initialize_sta  (data: pointer; _sta: PStaFDP); virtual;

               procedure    aktualizacia_denneho_zaznamu   (_sta,_stap: PStaFDP; _stad: PStadFDPs; reset: bool); virtual;
               procedure    aktualizacia_sumarneho_zaznamu_dnom (_sta_suma, _sta_ciastocny : PStadFDPs); virtual;
             end;


      const sta_PRS : POStatistikaPRS = nil;
