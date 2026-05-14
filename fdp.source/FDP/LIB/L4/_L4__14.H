    const   kod_14 = kod_SP+1+kod_TIME+kod_VYS*2+1;


    function code_l4_14   ( kod1 : string; h1,m1 : byte; vys1: word; vys1_: char;
                            vysI : word; vysI_,vysI_ab : char
                          ): string;


    function decode_l4_14_ (_14 : string;

                            var kod1    : string;      { vstupny bod FIR/oblasti}
                            var h1,m1   : byte;        { vypocitany cas na bode  }
                            var vys1    : word;        { vyska na bode           }
                            var vys1_   : char;

                            is_vysI     : bool;        { dekodovat vysku I ? }
                            var vysI    : word;        { vyska na hranici do FIR (oblasti) }
                            var vysI_,
                                vysI_ab : char;

                            var b14a,b14b,b14c,b14de : bool;
                            var _14b,_14c,_14d,_14e : string
                           ): bool;

    function decode_l4_14 (_14         : string;

                           var kod1    : string;      { vstupny bod FIR/oblasti }
                           var h1,m1   : byte;        { vypocitany cas na bode  }
                           var vys1    : word;        { vyska na bode           }
                           var vys1_   : char;

                           is_vysI     : bool;        { dekodovat vysku }
                           var vysI    : word;        { vyska na hranici do FIR (oblasti) }
                           var vysI_,
                               vysI_ab : char
                          ): bool;



    function code_l4_EXI (kodL : string; hL,mL : byte; vysL: word; vysL_: char;
                          vysO : word; vysO_,vysO_ab : char;
                          vysH : word; vysH_ : char
                         ): string;

    function decode_l4_EXI (_EXI        : string;

                            var kodL    : string;      { vystupny bod FIR/oblasti }
                            var hL,mL   : byte;        { vypocitany cas na bode   }
                            var vysL    : word;        { vyska na bode }
                            var vysL_   : char;

                            var vysO    : word;        { vyska na hranici z FIR (oblasti) }
                            var vysO_,
                                vysO_ab : char;

                            var vysH    : word;        { nasledujuca vyska }
                            var vysH_   : char
                           ): bool;

