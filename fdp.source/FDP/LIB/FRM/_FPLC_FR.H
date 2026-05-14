     const SIZE_frm_cFPL = 16 + max_bod_FPLC*3 {$IFDEF FPLC_ION} + 2 {$ENDIF};

           tit_15_1 = {$IFDEF SLOVAK}  '15 - bode trate LPS'  {$ENDIF}
                      {$IFDEF CZECH}   '15 - bode tratˆ LPS'  {$ENDIF}
                      {$IFDEF ENGLISH} '15 - ATS ROUTE POINT' {$ENDIF}
                      ;

           tit_15_2 = {$IFDEF SLOVAK}  '15 - vypo‡¡tan˜ ‡as dosiahnutia bodu' {$ENDIF}
                      {$IFDEF CZECH}   '15 - vypo‡¡tan˜ ‡as na bodu'          {$ENDIF}
                      {$IFDEF ENGLISH} '15 - ESTIMATED TIME ON THE POINT'     {$ENDIF}
                      ;

           tit_15_3 = {$IFDEF SLOVAK}  '15 - v˜¨ka na bode [S][A/B], ak je in  ako predch dza'    {$ENDIF}
                      {$IFDEF CZECH}   '15 - v˜¨ka na bodu [S][A/B], kdy‘ je jin  od p©redchoz¡'  {$ENDIF}
                      {$IFDEF ENGLISH} '15 - ALTITUDE ON THE POINT [S][A/B], if different previous' {$ENDIF}
                      ;

           tit_18   = {$IFDEF SLOVAK}  '18 - pozn mky a doplnkov‚ £daje' {$ENDIF}
                      {$IFDEF CZECH}   '18 - pozn mky a doplnkov‚ £daje' {$ENDIF}
                      {$IFDEF ENGLISH} '18 - SIGNIFICANT NOTE'  {$ENDIF}
                      ;

           tit_EXIo = {$IFDEF SLOVAK}  'EXI - v˜¨ka na v˜stupe z riadenej oblasti [A/B]' {$ENDIF}
                      {$IFDEF CZECH}   'EXI - v˜¨ka na v˜stupu z ©¡zen‚ oblasti [A/B]'   {$ENDIF}
                      {$IFDEF ENGLISH} 'EXI - EXITING FLIGHT LEVEL FROM CONTROLED AREA [A/B]' {$ENDIF}
                      ;

           tit_EXIh = {$IFDEF SLOVAK}  'EXI - cieŒov  v˜¨ka v nasleduj£cej oblasti'; {$ENDIF}
                      {$IFDEF CZECH}   'EXI - c¡lov  v˜¨ka v nasleduj¡ci oblasti';   {$ENDIF}
                      {$IFDEF ENGLISH} 'EXI - HEADING FLIGHT LEVEL IN THE NEXT CONTROLED AREA'; {$ENDIF}


           i_7_FDR    = 0;
           i_18_FDR   = 1;

           i_7b_FDR   = 2;
           i_7b0_FDR  = 3;

           i_8a_FDR   = 4;
           i_8b_FDR   = 5;

           i_9_FDR    = 6;

           i_15a_FDR_ = 7;
           i_15a_FDR  = 8;

           i_13a_FDR  = 9;
           i_13b_FDR  = 10;
           i_13c_FDR  = 11;

           i_16a_FDR  = 12;
           i_16b_FDR  = 13;

           i_15b_FDR  = 14;
           i_14c_FDR  = 15;

           i_15c_FDR  = 16;

          {$IFDEF FPLC_ION}
           i_EXIo     = i_15c_FDR+max_bod_FPLC*3;
           i_EXIh     = i_EXIo + 1;
          {$ENDIF}

           form_cFPL: array [0..SIZE_frm_cFPL-1] of TForm =
                 (
                  { -------------------------------------------- }
                  { identifikacia a popis letu                   }
                  { -------------------------------------------- }
                  (
                   {$IFNDEF GOST} item : '0     6';
                   {$ELSE}        item : '0      7';
                   {$ENDIF}       title: tit_7a;
                    lst : nil; pos: 1; legal: @setABC; skip : @setNil;
                    dx:10; dy:07; font:0; color: white
                  ),

                  ( item : '1      8'; title: tit_18;
                    lst : nil; pos: 1; legal: @setABC; skip : @setNil;
                    dx:10; dy:19; font:0; color: white
                  ),

                  {$IFNDEF GOST}
                    ( item : '2ÿ  ';  title: tit_7c;
                      lst : nil; pos: 1; legal: @set_7c {set_rbs_SSR}; skip : @setNil;
                      dx:80{116}; dy:07; font:0; color: 0
                    ),
                  {$ELSE}
                    ( item : '2ÿ   ';  title: tit_7c;
                      lst : nil; pos: 1; legal: @set_7c {set_uvd_BN}; skip : @setNil;
                      dx:80{112}; dy:07; font:0; color: 0
                    ),
                  {$ENDIF}
                  {$IFNDEF GOST}
                    ( item : '3ÿ  ';  title: tit_7c0;
                      lst : nil; pos: 1; legal: @set_7c {set_rbs_SSR}; skip : @setNil;
                      dx:80{116}; dy:19; font:0; color: 0
                    ),
                  {$ELSE}
                    ( item : '3ÿ   ';  title: tit_7c0;
                      lst : nil; pos: 1; legal: @set_7c {set_uvd_BN}; skip : @setNil;
                      dx:80{112}; dy:19; font:0; color: 0
                    ),
                  {$ENDIF}


      {_8}        ( item : '4'; title : tit_8a;
                    lst : @fn_8a; pos : 1; legal  : @set_8a; skip : @setNil;
                    dx:135;dy:07; font:0; color:0
                  ),
                  ( item : '5'; title : tit_8b;
                    lst : @fn_8b; pos : -1; legal : @set_8b; skip : @setNil;
                    dx:145;dy:07; font:0; color:0
                  ),


      {_9}        ( item : '6       '; title: tit_9;
                    lst : @fn_9b; pos: 1; legal: @setABC_; skip : @setNil;
                    dx:10 ; dy:31; font:0; color: 0
                  ),


      {_15a}      ( item : 'K';    title: tit_15a_; { 57 }
                    lst : @fn_15a; pos: 1; legal: @setRych_; skip : @setNil;
                    dx:80; dy:31; font:0; color: 0
                  ),
                  ( item : '8  ÿ'; title: tit_15a; { 68 }
                    lst : nil; pos: 1; legal: @setCisl{Rych}; skip : @setNil;
                    dx:90; dy:31; font:0; color: 0
                  ),

                  ( item : '9   '; title: tit_13a;
                    lst : @fn_13a; pos: 1; legal: @setABC; skip : @setNil;
                    dx:167; dy:10; font:0; color: 0
                  ),
                  ( item : '10:  '; title: tit_13b;
                    lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                    dx:202; dy:10; font:0; color: 0
                  ),
                  ( item : '11:  '; title: tit_13c;
                    lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                    dx:250; dy:10; font:0; color: 0
                  ),


      {_16a}      ( item : '12  ';  title: tit_16a;
                    lst : @fn_13a; pos: 1; legal: @setABC; skip : @setNil;
                    dx:167; dy:25; font:0; color: 0
                  ),
                  ( item : '13:  '; title: tit_16b;
                    lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                    dx:202; dy:25; font:0; color: 0
                  ),


      {_15b}      ( item : 'S14  '; title: tit_15b;
                    lst : @fnAlt; pos: 1; legal: @setVys; skip : @setNil;
                    dx:306 ; dy:10; font:0; color: 0
                  ),
      {_14a}      ( item : 'S15   '; title: tit_14c+'[A/B]';
                    lst : @fnAlt; pos: 1; legal: @setVysAB; skip : @setNil;
                    dx:306 ; dy:25; font:0; color: 0
                  ),


                  { -------------------------------------------- }
                  { body na trati                                }
                  { -------------------------------------------- }
      {_15c}      ( item : '16   ';  title: tit_15_1;
                    lst : @fnNDB; pos: 1; legal: @setABC; skip : @setNil;
                    dx:10 ; dy:50; font:0; color: 0
                  ),
                  ( item : '17:  '; title: tit_15_2;
                    lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                    dx:10 ; dy:61; font:0; color: 0
                  ),
                  ( item : '18   '; title: tit_15_3;
                    lst : @fnAlt; pos: 1; legal: @setVysAB; skip : @setNil;
                    dx:10  ; dy:73; font:0; color: 0
                  ),

                  ( item : '19   ';  title: tit_15_1;
                    lst : @fnNDB; pos: 1; legal: @setABC; skip : @setNil;
                    dx:60 ; dy:50; font:0; color: 0
                  ),
                  ( item : '20:  '; title: tit_15_2;
                    lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                    dx:60 ; dy:61; font:0; color: 0
                  ),
                  ( item : '21   '; title: tit_15_3;
                    lst : @fnAlt; pos: 1; legal: @setVysAB; skip : @setNil;
                    dx:60  ; dy:73; font:0; color: 0
                  ),

                  ( item : '22   ';  title: tit_15_1;
                    lst : @fnNDB; pos: 1; legal: @setABC; skip : @setNil;
                    dx:110; dy:50; font:0; color: 0
                  ),
                  ( item : '23:  '; title: tit_15_2;
                    lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                    dx:110; dy:61; font:0; color: 0
                  ),
                  ( item : '24   '; title: tit_15_3;
                    lst : @fnAlt; pos: 1; legal: @setVysAB; skip : @setNil;
                    dx:110 ; dy:73; font:0; color: 0
                  ),

                  ( item : '25   ';  title: tit_15_1;
                    lst : @fnNDB; pos: 1; legal: @setABC; skip : @setNil;
                    dx:160; dy:50; font:0; color: 0
                  ),
                  ( item : '26:  '; title: tit_15_2;
                    lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                    dx:160; dy:61; font:0; color: 0
                  ),
                  ( item : '27   '; title: tit_15_3;
                    lst : @fnAlt; pos: 1; legal: @setVysAB; skip : @setNil;
                    dx:160 ; dy:73; font:0; color: 0
                  ),

                  ( item : '28   ';  title: tit_15_1;
                    lst : @fnNDB; pos: 1; legal: @setABC; skip : @setNil;
                    dx:210; dy:50; font:0; color: 0
                  ),
                  ( item : '29:  '; title: tit_15_2;
                    lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                    dx:210; dy:61; font:0; color: 0
                  ),
                  ( item : '30   '; title: tit_15_3;
                    lst : @fnAlt; pos: 1; legal: @setVysAB; skip : @setNil;
                    dx:210 ; dy:73; font:0; color: 0
                  ),

                  ( item : '31   ';  title: tit_15_1;
                    lst : @fnNDB; pos: 1; legal: @setABC; skip : @setNil;
                    dx:260; dy:50; font:0; color: 0
                  ),
                  ( item : '32:  '; title: tit_15_2;
                    lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                    dx:260; dy:61; font:0; color: 0
                  ),
                  ( item : '33   '; title: tit_15_3;
                    lst : @fnAlt; pos: 1; legal: @setVysAB; skip : @setNil;
                    dx:260 ; dy:73; font:0; color: 0
                  ),

                  ( item : '34   ';  title: tit_15_1;
                    lst : @fnNDB; pos: 1; legal: @setABC; skip : @setNil;
                    dx:310; dy:50; font:0; color: 0
                  ),
                  ( item : '35:  '; title: tit_15_2;
                    lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                    dx:310; dy:61; font:0; color: 0
                  ),
                  ( item : '36   '; title: tit_15_3;
                    lst : @fnAlt; pos: 1; legal: @setVysAB; skip : @setNil;
                    dx:310 ; dy:73; font:0; color: 0
                  ),

                  ( item : '37   ';  title: tit_15_1;
                    lst : @fnNDB; pos: 1; legal: @setABC; skip : @setNil;
                    dx:360; dy:50; font:0; color: 0
                  ),
                  ( item : '38:  '; title: tit_15_2;
                    lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                    dx:360; dy:61; font:0; color: 0
                  ),
                  ( item : '39   '; title: tit_15_3;
                    lst : @fnAlt; pos: 1; legal: @setVysAB; skip : @setNil;
                    dx:360 ; dy:73; font:0; color: 0
                  )

                 {$IFDEF FPLC_L},
                  ( item : '40   ';  title: tit_15_1;
                    lst : @fnNDB; pos: 1; legal: @setABC; skip : @setNil;
                    dx:410; dy:50; font:0; color: 0
                  ),
                  ( item : '41:  '; title: tit_15_2;
                    lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                    dx:410; dy:61; font:0; color: 0
                  ),
                  ( item : '42   '; title: tit_15_3;
                    lst : @fnAlt; pos: 1; legal: @setVysAB; skip : @setNil;
                    dx:410 ; dy:73; font:0; color: 0
                  ),

                  ( item : '43   ';  title: tit_15_1;
                    lst : @fnNDB; pos: 1; legal: @setABC; skip : @setNil;
                    dx:460; dy:50; font:0; color: 0
                  ),
                  ( item : '44:  '; title: tit_15_2;
                    lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                    dx:460; dy:61; font:0; color: 0
                  ),
                  ( item : '45   '; title: tit_15_3;
                    lst : @fnAlt; pos: 1; legal: @setVysAB; skip : @setNil;
                    dx:460 ; dy:73; font:0; color: 0
                  ),

                  ( item : '46   ';  title: tit_15_1;
                    lst : @fnNDB; pos: 1; legal: @setABC; skip : @setNil;
                    dx:510; dy:50; font:0; color: 0
                  ),
                  ( item : '47:  '; title: tit_15_2;
                    lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                    dx:510; dy:61; font:0; color: 0
                  ),
                  ( item : '48   '; title: tit_15_3;
                    lst : @fnAlt; pos: 1; legal: @setVysAB; skip : @setNil;
                    dx:510 ; dy:73; font:0; color: 0
                  ),

                  ( item : '49   ';  title: tit_15_1;
                    lst : @fnNDB; pos: 1; legal: @setABC; skip : @setNil;
                    dx:560; dy:50; font:0; color: 0
                  ),
                  ( item : '50:  '; title: tit_15_2;
                    lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                    dx:560; dy:61; font:0; color: 0
                  ),
                  ( item : '51   '; title: tit_15_3;
                    lst : @fnAlt; pos: 1; legal: @setVysAB; skip : @setNil;
                    dx:560 ; dy:73; font:0; color: 0
                  )
                 {$ENDIF}

                  { -------------------------------------------- }
                  { vystupne vysky                               }
                  { -------------------------------------------- }

                 {$IFDEF FPLC_ION},
                  ( item : '52    '; title: tit_EXIo;
                    lst : @fnAlt; pos: 1; legal: @setVysAB; skip : @setNil;
                    dx:350 ; dy:10; font:0; color: 0
                  ),
                  ( item : '53   '; title: tit_EXIh;
                    lst : @fnAlt; pos: 1; legal: @setVysAB; skip : @setNil;
                    dx:358 ; dy:25; font:0; color: 0
                  )
                  {$ENDIF}
                 );


      const  pos_frm_FPLC: int = -1;