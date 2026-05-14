          { ------------------------------------------------
            Kategorie sprav letovych prevadzkovych sluzieb :
            ------------------------------------------------
            Prednostna znacka (pri doprave sprav po AFTN, ucastnickej
            sieti TELEX alebo okruhoch pocitac-pocitac.
          }

     const { Poradie prednosti sprav je dane znackou prednosti }
            tlgSS = 'SS';
            tlgDD = 'DD';
            tlgFF = 'FF';
            tlgGG = 'GG';
            tlgKK = 'KK';
            tlgLL = 'LL';

            kod_MTK_2_PRTY = 2;
            max_MTK_2_PRTY = 6;
            MTK_2_PRTY : array[0..max_MTK_2_PRTY-1] of string[kod_MTK_2_PRTY] =

            (tlgSS,  { tiesnove spravy a korespondencia, obdobie neistoty
                     }
             tlgDD,  { havarijne stave, nepredvidane okolnosti, ohranicenia/zrusenie letov,
                       presmerovanie letov na ine letisko
                     }
             tlgFF,  { spravy o pohybe a riadeni lietadiel, nahlych nebezpecnych zmenach pocasia,
                       o startoch, o polohe letov, o ich pripravenosti, odovzdani riadenia,
                       FPL, o zrusenii obmedzeni
                     }
             tlgGG,  { PPL, nakladanie, dostihnutie bodov na trase,, ARR, CNL,
                       dolezite informacie o letiskach, narusenie rezimu pravidiel letov
                       spravy letovych informacii o met. informaciach, cinnosti let. zar.,
                       predpovede pocasia...
                     }
             tlgKK,  { NOTAM, niektore spravy pre zabezpecenie letov,
                       stav a vyuzitie zariadeni pre RLP,
                       o zmene toku letovej prevadzky do 72 hodin...
                     }
             tlgLL   { v "CCCP" - administrativne spravy,...
                     }
            );


     type   prtyTLG  = (prtySS,prtyFF,prtyKK);

     const  sprtyTLG : array[low(prtyTLG)..high(prtyTLG)] of string[kod_MTK_2_PRTY] = (tlgSS,tlgFF,tlgKK);


     function  is_mtkprtyi (s: string): int;
     function  is_mtkprty  (s: string): string;
     function  _prtyTLG    (prty: string): prtyTLG;

     function  mtk_tlg_prty (data: pchars; size: word; var res: string): string;
     function  mtk_tlg_id   (data: pchars; size: word): string;
     function  mtk_tlg_fdp  (typ: word{TNETtyp}): string; { moze sa zlepsit }
