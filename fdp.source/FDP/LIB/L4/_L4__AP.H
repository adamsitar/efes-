    const   kod_13 = kod_AP+kod_TIME*2+1;
            kod_16 = kod_AP*3+kod_TIME+2;


    function   code_l4_13a   (kod: string; _L4444M: bool): string;
    function   code_l4_13    (kod: string; h,m, h_,m_: byte; _L4444M: bool): string;

    function   decode_l4_13a (_13: string): string;
    function   decode_l4_13_ (_13: string;
                              var _13a: string; var h,m, h_,m_: byte;
                              var _13b,_13c: string;
                              var r13a,r13b,r13c: bool
                             ): bool;
    function   decode_l4_13  (_13: string;
                              var kod: string; var h,m, h_,m_: byte
                             ): bool;


    function   code_l4_16a   (kod: string; _L4444M: bool): string;
    function   code_l4_16    (kod: string; h,m: byte; kodb: string; hs,ms: byte; _L4444M: bool): string;

    function   decode_l4_16a (_16: string): string;
    function   decode_l4_16_ (_16: string; hs,ms: byte;
                              var _16a: string;
                              var _16b: string; var h,m, hl,ml: byte; { absolutny a relativny cas pristati }
                              var _16c: string;
                              var r16a,r16b,r16c: bool
                             ): bool;
    function   decode_l4_16  (_16: string; hs,ms: byte;
                              var kod: string; var h,m, hl,ml: byte; { absolutny a relativny cas pristati }
                              var kodb: string
                             ): bool;


    function   decode_l4_17_ (_17: string;
                              var _17a,_17b: string; var h,m: byte; { absolutny a relativny cas pristati }
                              var _17c: string;
                              var r17a,r17b,r17c: bool
                             ): bool;
    function   decode_l4_17  (_17: string; var kod: string; var h,m: byte; var name: string): bool;
