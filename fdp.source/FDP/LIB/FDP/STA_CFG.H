      const  cfgSTA     = extSTA+ext_ini;

             cfg_CISLO  = '%';


      const {
             a) Format subora :

                cfg_XX : o,p,s,z,r I o,p,s,z,r o,p,s,z,r o,p,s,z,r o,...

             Denny subor obsahuje len jednu kombinaciu "o,p,s,z,r".
             Ak nie su udaje sledovane, tak namiesto hodnoty "0" obsahuju "-".

             cfg_XX je dekodovany nazov polozky, ak sa pri sumarizacii za mesiac
             zmeni, tak sa vyvori dalsi riadok v subore...


             b) Pre vypis na obrazovke, tlac alebo kopirovanie.

                dna    : 1.        I 2.        3.
                udaje  : o p s z r I
                -------------------------------------------------------
                cfg_XX : o,p,s,z,r I o,p,s,z,r o,p,s,z,r o,p,s,z,r o,...

                Poznamka : o-odoslanych
                           p-...
                           ...

             Hlavicka dna/udaje, polozka "I" sa vsuva medzi dni len pri
             vypise na obrazovku a pri tlaci ("I").
             Sirka kazdej polozky je na "o,p,s,z,r" tri znaky.
            }

             sta_odd_nazov   = ':';
             sta_odd_hodnota = ',';
             sta_odd_den     = ' ';

             sta_nesledovany = '-';


      const  najdlhsi_nazov  : byte   = 0;
             maximalny_najdlhsi_nazov = 30;

             {velkost_udaja rozsah}

