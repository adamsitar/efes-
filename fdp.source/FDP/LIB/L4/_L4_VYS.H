         { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
            Vyska
           תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

            Fxxx    ........  letova hladina   [stovky stop]
            Sxxxx   ........  desiatky metrov  [desiatky metrov]

            Axxx    ........  vyska nad morom  [stovky stop]
            Mxxxx   ........  vyska nad morom  [desiatky metrov]

            G0xx    ........  lety do 300m     [desiatky metrov]
         }


    const  m_ft      = 0.3048;
           m_S       = 10;


    const  kod_VYS   = 5;

           altG_     = 3;
           altA_     = 3;
           altS_     = 4;
           altM_     = 4;
           altFL_    = 3;


    const  altG      = 'G';
           altA      = 'A';
           altH      = 'H';
           altS      = 'S';
           altM      = 'M';
           altFL     = 'F';

           hd_FL     = 'FL';

           altAbove  = 'A';
           altBellow = 'B';
           altPLUS   = 'PLUS';


    const  vys_GND   = 'GND';
           vys_VFR   = 'VFR';
           vys_UNL   = 'UNL';


           alt_GND     = 0;
           alt_UNL     : long = high(word);
           alt_VFR     : word = {$IFDEF LZ} 1500
                                {$ELSE}     300
                                {$ENDIF};          { [m] }
           cfg_alt_VFR = 'FL VFR';     { do akej vysky je VFR ?           }
           cfg_lo_FL   = 'FL LOW';     { ktora je spodna letova hladina ? }


           vysOB      = altS;        { zatial sa uvazuje vsetky vysky stripu v "S" }
           vysOB_     = altS_;


    const  alt_VFR_sym : bool = false; { povolenie vypisu VFR vysky ako VFR }
           alt_VFR_G   : bool = true;  { povolenie vypisu VFR vysky ako G }
           in_FL       : bool = false;                                   { vypis vysky vo FL }
           in_km       : bool = {$IFDEF UA} true {$ELSE} false {$ENDIF}; { vypis rychlosti v km/h }
           lo_FL       : word = 50;    {  A050, FL60 }


           alt_FL5min  : word = 0;
           alt_FL5max  : word = 0;


    {const  nil_hm = 0;}


    function   FLtoM  (FL: long): long;
    function   MtoS   (M: long): long;
    function   StoM   (S: long): long;
    function   MtoFL  (M: long): long;

    function   get_altM    (vys_: char; vys: long): long;

    function   _vys_OB     (vys: word; vys_: char): word;

    function   alt_ab_     (ab: char): char;
    function   alt_to_str_ (vys: word; vyska_, ab: str3; in_FL,in_VFR,in_EDD: bool): string;
    function   alt_to_str  (vys: word; vyska_, ab: str3; in_FL,in_VFR: bool): string;

    function   check_alt_  (vys: word; vys_: char): char;



    function   code_l4_vys        (vys: word; vys_: char): string;
    function   decode_l4_vys      (s: string; var vys: word; var vys_: char): bool;

    function   code_l4_vyss       (vys: long; vys_: char): string;
    function   decode_l4_vyss     (vyss: string; var vys: word; var vys_: char; vys_ab: pchar): bool;

    function   code_l4_vys_       (vys: word; vys_: char; ft_od: word; in_VFR: bool): string;
    function   code_l4_vyss_      (vys: long; vys_: char; ab: str3; in_FL,in_VFR,in_EDD: bool): string;

    function   decode_l4_vys_     (s: string; var vys: word; var vys_: char; vys_a: pchar; var dlzka: int; range: bool): bool;
    function   decode_l4_vys2     (s: string;
                                   var vys: word; var vys_,vys_a: char;
                                   var vys2: word; var vys2_,vys2_a: char
                                  ): bool;


    function   decode_l4_vys_M    (s: string): word;
    function   decode_l4_vys_OB   (s: string; var vys: word; var vys_a: char): bool;

