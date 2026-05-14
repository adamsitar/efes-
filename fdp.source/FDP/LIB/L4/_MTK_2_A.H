    const  { max 9 adries do 6 znakov
             alebo max 7 do 8
           }

           _MTK_CHNL   = 3;

           _MTK_ADR_lo = 6; _MTK_ADR_lo_pocet = 9;
           _MTK_ADR_hi = 8; _MTK_ADR_hi_pocet = 7;
           _MTK_ADR_ar = 56;

           _MTK_ADR_LINEs = 4; { odvodena premenna }


    const  cfg_MTK_ADR_I  = 'INPUT ADDRESS';
           cfg_MTK_ADR_O  = 'OUTPUT ADDRESS';

           cfg_MTK_CHNL_I = 'INPUT CHANNEL';
           cfg_MTK_CHNL_O = 'OUTPUT CHANNEL';


           ADR_O_THIS  : string[_MTK_ADR_hi] = '';



    function _check_mtk_adr (line: string;       { testovany riadok }
                             var adr: string;    { adresy, musia by predinicializovane externe }
                             var znakov: int;    { pocet znakov celkom, musi byt nulovany na zaciatku externe }
                             posledny: bool;     { posledny riadok adresy }
                             max_dlzka: int;     { maximalna dlzka adresy, ignoruje sa, ak je "0" }
                             var res: string     { vysledok }
                            ): int;
