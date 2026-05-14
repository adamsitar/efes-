         { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
            Rychlost
            תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
         }

    const  MileNaut     = 1852;
           MileEngNaut  = 1853.2;
           MileEng      = 1609.3;

           N_K          = MileNaut/1000;  { knotts to km/h }
           M_K          = 1080.0;  { 0.8 }

           dstK   = 'K';         { vzdialenost v km }


    const  spdK     = 'K';
           spdN     = 'N';
           spdM     = 'M';

           kod_RYCH = 5;
           spdK_    = 4;         { ak tu nieco pridame, treba zmenit i funkcie }
           spdN_    = 4;         { pre dekodovanie                             }
           spdM_    = 3;


    const  setRych  : TCharSet  = ['0'..'9',' ', '.',spdK,spdN,spdM];
           setRych_ : TCharSet  = [spdK,spdN,spdM];


   { rychlost
   }
    function   get_rych_kmh (rych: real; rych_: char;
                             vys : word; vys_ : char
                            ): real;

    function   code_l4_rych    (rych: single; rych_: char): string;
    function   code_l4_rychkmh (rych: single; rych_: char; _in_km: bool): string;

    function   code_l4_rych_vys   (rych: single; rych_: char; vys: word; vys_: char; ft_od: word; in_VFR: bool): string;

    function   decode_l4_rych     (s: string; var rych: single; var rych_: char): bool;


    function   decode_l4_rych_vys_ (s: string;
                                    var rych: single; var rych_: char; var sr: string; var rres: bool;
                                    var vys: word;    var vys_: char;  var sv: string; var vres: bool
                                   ): bool;
    function   decode_l4_rych_vys  (s: string; var rych: single; var rych_: char; var vys: word; var vys_: char): bool;


    function   decode_l4_rych_vys2_(s: string;
                                    var rych: single; var rych_: char;   var rres : bool;
                                    var vys: word; var vys_,vys_a: char; var vres : bool;
                                    var vys2: word; var vys2_: char;     var v2res: bool
                                   ): bool;

    function   decode_l4_rych_vys2 (s: string;
                                    var rych: single; var rych_: char;
                                    var vys: word; var vys_,vys_a: char;
                                    var vys2: word; var vys2_: char
                                   ): bool;
