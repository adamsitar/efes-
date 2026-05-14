    const { Oznacenie zmien v poli trate letu }

            rte_VFR = 'VFR'; { zmena rezimu letu }
            rte_IFR = 'IFR';

            rte_DCT = 'DCT'; { Ak let ku dalsiemu bodu bude vykonany mimo
                               stanovenu trat, s vynimkou, ak su oba body
                               vyjadrene zem sur alebo azimutom
                             }

                             { vyjadrenie cinnosti v priestore
                             }
            rte_OAT = 'OAT'; { dalsi text az po GAT je ignorovany }
            rte_GAT = 'GAT'; { napriklad MZ231/C10  ML342/TMA alebo LKR ... }


            rte_T   = 'T';   { ak je popis trate nad predchadzajucim bodom
                               preruseny a a zvysok sa nachadza uz v skor
                               vyslanej sprave FPL alebo v inych udajoch;
                               musi uzatvarat popis trate
                             }

            rte_C   = 'C';   { C/"bod, v ktorom sa predpoklada, ze bude cestovne
                               stupanie zapocate, vyjadrene presne podla bodu
                               c3 vpredu"/"rychlost pocas cestovneho stupania
                               podla a) vpredu nasledovanou dvoma hladinami,
                               urcujucimi vrstvu, ktora bude obsadena pocas
                               stupania, kazda hladina je vyjadrena podla b)
                               alebo hladinou, nad ktoru je cestovne stupanie
                               planovane, nasledovane slovom PLUS bez medzery"
                             }

            {rte_ATS = 'ATS';  bod, kde je planovana zmena rychlosti alebo
                               hladiny, zmena trate ATS alebo pravidiel letu +
                               dalsia cast trate LPS i ked je rovnaka s predchadzajucou
                               castou alebo DCT, ak ku dalsiemu bodu sa poleti mimo
                               stanovenu trat \ZemSur
                             }


            max_rte_DESC = 7;
            rte_DESC :   array[0..max_rte_DESC-1] of string[3]
                       = (rte_VFR,rte_IFR, rte_DCT,
                          rte_OAT,rte_GAT,
                          rte_T,rte_C {,rte_ATS}
                         );



   { specializovane vojesnke identifikatory
   }
    const   fpl_MZP   = 'MZP';
            fpl_DEP   = 'DEP';
            fpl_ARR   = 'ARR';
            fpl_TIME  = 'T';

            fpl_ACT   = 'C';
            fpl_DLA   = 'L';
            fpl_RYCH  = 'V';


