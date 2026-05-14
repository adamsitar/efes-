     { Pascal ma jednu "nepeknu" vlastnost...
       prekryva pchar konstanty, ak obsahuju rovnake polia
       Pozor na zmenu, ALR si kopiruje data hore a dole
     }

     {$IFDEF FPL4}

       const size_FPL4frm = 29+max_FPL4_15_r_hi+1+max_FPL4_18_r_hi+1;
             size_FPL4alr = size_FPL4frm+max_FPL4_19_r_hi+max_FPL4_20_r_hi;

             form_FPL4 : array [0..size_FPL4alr-1] of TForm =


    {_3}       (( item : '0  -'; title : tit_3;
                  lst : nil; pos : 1; legal : @setNil; skip : @setNil;
                  dx:10; dy:10; font:0; color: white
                ),

    {_5}        ( item : '5a      ';
                  title : tit_5a;
                  lst : @fn_5a; pos : 1; legal : @set_18; skip : @set_NXT;
                  dx:48; dy:10; font:0; color: 0
                ),

                ( item : {/}'5b       ';
                  title : tit_5b;
                  lst : nil; pos : 1; legal : @set_18; skip : @set_NXT;
                  dx:114; dy:10; font:0; color: 0
                ),

                ( item : {/}'5c                                             ';
                  title : tit_5c;
                  lst : nil; pos : 1; legal : @set_18; skip : @set_NXT;
                  dx:189; dy:10; font:0; color: 0
                ),

    {_7}        ( {$IFDEF GOST}item : '7a      '{$ELSE}item : '7a     '{$ENDIF};
                  title : tit_7a;
                  lst : nil; pos : 1; legal : @setABC; skip : @setNil;
                  dx:48; dy:10; font:0; color: white{clGRe}
                ),
                ( item : '/0'; title : tit_7b;
                  lst : nil; pos : 1; legal : @set_10b; skip : @set_NXT;
                  {$IFDEF GOST}dx:114{$ELSE}dx:106{$ENDIF};dy:10; font:0; color: white{clGRe}
                ),
                 ({$IFDEF GOST} item : '77777' {$ELSE} item : '7777' {$ENDIF};
                  title : tit_7c;
                  lst : nil; pos : 1; legal : @setABC; skip : @setNil;
                  {$IFDEF GOST}dx:131{$ELSE}dx:123{$ENDIF};dy:10; font:0; color: white{clGRe}
                ),


    {_8}        ( item : '1'; title : tit_8a;
                  lst : @fn_8a; pos : 1; legal  : @set_8a; skip : @setNil;
                  {$IFDEF GOST}dx:180{$ELSE}dx:172{$ENDIF};dy:10; font:0; color:0
                ),
                ( item : '2 '; title : tit_8b;
                  lst : @fn_8b; pos : -1; legal : @set_8b; skip : @setNil;
                  {$IFDEF GOST}dx:190{$ELSE}dx:182{$ENDIF};dy:10; font:0; color:0
                ),


    {_9}        ( item : '91'; title : tit_9a;
                  lst : nil; pos : 1; legal : @setCisl_; skip : @setNil;
                  dx:10; dy:25; font:0; color:0
                ),
                ( item : '92  '; title : tit_9b;
                  lst : @fn_9b; pos : 1; legal : @setABC ; skip : @setNil;
                  dx:28; dy:25; font:0; color:0
                ),
                ( item : '/3'; title : tit_9c;
                  lst : @fn_9c; pos : 1; legal : @set_9c; skip : @set_NXT;
                  dx:62; dy:25; font:0; color:0
                ),


    {_10}       ( item : '1234567'; title : tit_10a;
                  lst : @fn_10a; pos : -1; legal : @setPism_; skip : @setNil;
                  dx:106; dy:25; font:0; color:0
                ),
                ( item : '/4 '; title : tit_10b;
                  lst : @fn_10b; pos : -1; legal : @set_10; skip : @set_NXT;
                  dx:165; dy:25; font:0; color:0
                ),


    {_13}       ( item : '13 1'; title : tit_13a;
                  lst : @fn_13a; pos : 1; legal : @setPism_; skip : @setNil;
                  dx:10; dy:45; font:0; color:0
                ),
                ( item : '13 2'; title : tit_13b;
                  lst : nil; pos : 1; legal : @setCisl_; skip : @setNil;
                  dx:44; dy:45; font:0; color:0
                ),
                ( item : '13 3'; title : tit_13c;
                  lst : nil; pos : 1; legal : @setCisl_; skip : @setNil;
                  dx:100; dy:45; font:0; color:0
                ),


    {_14}       ( item : '14 1        /'; title : tit_14a;
                  lst : @fnNDB_I; pos : 1; legal : @setABC;  skip : @set_NXT;
                  dx:230; dy:45; font:0; color:0
                ),
                ( item : '14 2'; title : tit_14b;
                  lst : nil; pos : 1; legal : @setCisl_;   skip : @setNil;
                  dx:337; dy:45; font:0; color:0
                ),
                ( item : '14  3'; title : tit_14c;
                  lst : @fnAlt; pos : 1; legal : @setABC;  skip : @setNil;
                  dx:372; dy:45; font:0; color:0
                ),
                ( item : '14  4'; title : tit_14d;
                  lst : @fnAlt; pos : 1; legal : @setABC;  skip : @setNil;
                  dx:416; dy:45; font:0; color:0
                ),
                ( item : '5';      title : tit_14e;
                  lst : @fnAlt_ab; pos : 1; legal : @set_alt_;  skip : @setNil;
                  dx:459; dy:45; font:0; color:0
                ),


    {_16}       ( item : '16 1'; title : tit_16a;
                  lst : @fn_13a; pos : 1; legal : @setPism_; skip : @setNil;
                  dx:10; dy:60; font:0; color:0
                ),
                ( item : '16 2'; title : tit_16b;
                  lst : nil; pos : 1; legal : @setCisl_; skip : @setNil;
                  dx:44; dy:60; font:0; color:0
                ),

                ( item : '16 3'; title : tit_16c;
                  lst : @fn_13a; pos : 1; legal : @setPism_; skip : @setNil;
                  dx:100; dy:60; font:0; color:0
                ),
                ( item : '16 4'; title : tit_16d;
                  lst : @fn_13a; pos : 1; legal : @setABC; skip : @setNil;
                  dx:138; dy:60; font:0; color:0
                ),


    {_17}       ( item : '17 1'; title : tit_17a;
                  lst : @fn_13a; pos : 1; legal : @setPism_; skip : @setNil;
                  dx:230; dy:60; font:0; color:0
                ),
                ( item : '17 2'; title : tit_17b;
                  lst : @fn_13a; pos : 1; legal : @setCisl;  skip : @setNil;
                  dx:264; dy:60; font:0; color:0
                ),
                ( item : '17            3'; title : tit_17c;
                  lst : @fn_13a; pos : 1; legal : @setABC; skip : @setNil;
                  dx:300; dy:60; font:0; color:0
                ),


    {_15}       ( item : '15  1'; title : tit_15a;
                  lst : @fn_15a; pos : 1; legal : @setRych; skip : @setNil;
                  dx:10; dy:80; font:0; color:0
                ),

                ( item : '15  2'; title : tit_15b;
                  lst : @fnAlt; pos : 1; legal : @setVys; skip : @setNil;
                  dx:53; dy:80; font:0; color:0
                ),


                ( item : '15 3                                                      ';
{max_FPL4_15_r}   title : tit_15c;
                  lst : @fn_15; pos : -1; legal : @set_15; skip : @setNil;
                  dx:98; dy:82; font:0; color:0
                ),
                ( item : '15 4                                                                 ';
                  title : tit_15c;
                  lst : @fn_15; pos : -1; legal : @set_15; skip : @setNil;
                  dx:10; dy: 92; font:0; color:0
                ),
                ( item : '15 5                                                                 ';
                  title : tit_15c;
                  lst : @fn_15; pos : -1; legal : @set_15; skip : @setNil;
                  dx:10; dy:102; font:0; color:0
                ),
                ( item : '15 6                                                                 ';
                  title : tit_15c;
                  lst : @fn_15; pos : -1; legal : @set_15; skip : @setNil;
                  dx:10; dy:112; font:0; color:0
                ),
                ( item : '15 7                                                                 ';
                  title : tit_15c;
                  lst : @fn_15; pos : -1; legal : @set_15; skip : @setNil;
                  dx:10; dy:122; font:0; color:0
                ),
                ( item : '15 8                                                                 ';
                  title : tit_15c;
                  lst : @fn_15; pos : -1; legal : @set_15; skip : @setNil;
                  dx:10; dy:132; font:0; color:0
                ),


    {_18}       ( item : '18 1                                                                 ';
{max_FPL4_18_r}   title : tit_18;
                  lst : @fn_18; pos : -1; legal : @set_18; skip : @setNil;
                  dx:10; dy:152; font:0; color:0
                ),
                ( item : '18 2                                                                 ';
                  title : tit_18;
                  lst : @fn_18; pos : -1; legal : @set_18; skip : @setNil;
                  dx:10; dy:162; font:0; color:0
                ),
                ( item : '18 3                                                                 ';
                  title : tit_18;
                  lst : @fn_18; pos : -1; legal : @set_18; skip : @setNil;
                  dx:10; dy:172; font:0; color:0
                ),
                ( item : '18 4                                                                 ';
                  title : tit_18;
                  lst : @fn_18; pos : -1; legal : @set_18; skip : @setNil;
                  dx:10; dy:182; font:0; color:0
                ),


                ( item : '19 1                                                                 ';
                  title : tit_19;
                  lst : @fn_19; pos : -1; legal : @set_18; skip : @setNil;
                  dx:10; dy:205; font:0; color:0
                ),

                ( item : '19 2                                                                 ';
                  title : tit_19;
                  lst : @fn_19; pos : -1; legal : @set_18; skip : @setNil;
                  dx:10; dy:215; font:0; color:0
                ),


                ( item : '20 1                                                                 ';
                  title : tit_20;
                  lst : @fn_20; pos : -1; legal : @set_18; skip : @setNil;
                  dx:10; dy:229; font:0; color:0
                ),

                ( item : '20 2                                                                 ';
                  title : tit_20;
                  lst : @fn_20; pos : -1; legal : @set_18; skip : @setNil;
                  dx:10; dy:239; font:0; color:0
                ),

                ( item : '20 3                                                                 ';
                  title : tit_20;
                  lst : @fn_20; pos : -1; legal : @set_18; skip : @setNil;
                  dx:10; dy:249; font:0; color:0
                ){,

                ( item : '20 4                                                                 ';
                  title : tit_20;
                  lst : @fn_20; pos : -1; legal : @set_18; skip : @setNil;
                  dx:10; dy:259; font:0; color:0
                )}
               );
     {$ENDIF}