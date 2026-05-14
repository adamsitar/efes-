    const { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
             Popis trate

            תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
          }
          { a) zemepisne suradnice : 4905N01920E, 49N019E
          }
            {alt_ZS   = [zsN,zsS];}
            kod_ZS_  = 4;
            kod_ZS   = 2;

            {alt_ZD  = [zdE,zdW];}
            kod_ZD_  = 5;
            kod_ZD   = 3;


          { b) smer od otocneho bodu :  FOJ180040K
          }
            kodl_VOR   =  2;
            kodh_VOR   =  3;
            kod_VOR_AZ =  3;
            kod_VOR_RA =  3;


          { c) bod
          }
            kod_AP   = 4;
             kod_APb  = (KOD_AP+1)*2-1;
             kod_APM  = 3;

            kod_SP   = 11;                                         { vyznacny bod }
             kod_NDB  = 5;                                         { nasledujuce dve hodnoty zrusit... }
             kod_OB   = {$IFDEF _DPMI} kod_SP {$ELSE} 6 {$ENDIF};   { to je len derivovana hodnota, nie podla predpisu }

            kod_RTE  = 7;

            kod_MZP  = kod_AP+kod_TIME+1+kod_TIME;    { medzipristatie }

            kod_IO   = '*';       { nie ICAO, priznak, ze bod je I/O; pouzite v suboroch rte.fir }
            kod_ZSxy = 'XYÿ';


          { d) priestor
          }
            kod_PRS = 8;



    const  MIL_POINT = 'M'; { vsetky vojenske body v oznaceni CAMUSu a OPL maju tento priznak }
           MIL_OB    = 'Z'; { druhy priznak vojenskych otocnych bodov                         }


   { ZemSur
   }
    function   decode_l4_ZemSur (kod: string; var zdst,zdmn,zdse, zsst,zsmn,zsse: byte): bool;
    function   code_l4_ZemSur   (zdst,zdmn,zdse, zsst,zsmn,zsse: byte; short: bool): string;

    function   decode_l4_zs (kod: string; var zd,zs: Tzdzs): bool;
    function   code_l4_zs   (zd,zs: TZdZs; short: bool): string;


   { 15
   }
    function   code_l4_bod      (kod: string; vys: word; vys_: char; ft_od: word; in_VFR: bool; h,m: byte): string;
    function   code_l4_bod_     (kod: string; h,m: byte; vys: word; vys_,vys_a: char;
                                 var vysp: word; var vysp_,vysp_a: char
                                ): string;
    function   decode_l4_bod_   (s: string;
                                 var kod: string; var h,m: byte; var vys: word; var vys_,vys_a: char;
                                 var vysp: word; var vysp_,vysp_a: char
                                ): bool;
