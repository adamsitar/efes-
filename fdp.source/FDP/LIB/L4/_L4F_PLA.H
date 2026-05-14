
     function  _check_8_by4444  (_8: string; var _8a,_8b: char; var res: string): int;
     function  _check_10_by4444 (_10: string; var _10a,_10b: string; var res: string): int;


     function  _check_13_by4444 (_13: string;
                                 var _13a: string; var h,m,h_,m_: byte;
                                 var res: string
                                ): int;
     function  _check_16_by4444 (_16: string; hs,ms: byte;
                                 var _16a: string; var h,m : byte;
                                 var _16cd: string;
                                 var res: string
                                ): int;
     function  _check_17_by4444 (_17: string;
                                 var kod: string; var h,m: byte;
                                 var name: string;
                                 var res: string
                                ): int;


     function  _check_14_by4444 (_14: string;
                                 typ: string;

                                 var kod1    : string;      { vstupny bod FIR/oblasti}
                                 var h1,m1   : byte;        { vypocitany cas na bode  }
                                 var vys1    : word;        { vyska na bode           }
                                 var vys1_   : char;

                                 is_vysI     : bool;        { dekodovat vysku I ? }
                                 var vysI    : word;        { vyska na hranici do FIR (oblasti) }
                                 var vysI_,
                                     vysI_ab : char;

                                 var res: string
                                ): int;

