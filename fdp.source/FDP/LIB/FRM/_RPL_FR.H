     {$IFDEF RPL}

       const  setH   : TCharSet = [RPL_ON,RPL_OFF];

              setK1  : TCharSet = ['1','0','X',' '];
              setK2  : TCharSet = ['2','0','X',' '];
              setK3  : TCharSet = ['3','0','X',' '];
              setK4  : TCharSet = ['4','0','X',' '];
              setK5  : TCharSet = ['5','0','X',' '];
              setK6  : TCharSet = ['6','0','X',' '];
              setK7  : TCharSet = ['7','0','X',' '];

       const  size_RPLfrm = 18+max_RPL_15_r_hi+1+max_RPL_18_r_hi+1;

              form_RPL : array [0..size_RPLfrm-1] of TForm =


                (( item : '+'; title : tit_H;
                   lst : nil; pos : 1; legal : @setH; skip : @setNil;
                   dx:10; dy:10; font:0; color: clGRc
                 ),

                 ( item : '     1'; title : tit_I;
                   lst : nil; pos : 1; legal : @setCisl_; skip : @setNil;
                   dx:25; dy:10; font:0; color: clGRc
                 ),

                 ( item : '     2'; title : tit_J;
                   lst : @fn_rplJ; pos : 1; legal : @setABC; skip : @setNil;
                   dx:85; dy:10; font:0; color: clGRc
                 ),

                 ( item : '1'; title : tit_K1;
                   lst : nil; pos : 1; legal : @setK1; skip : @setNil;
                   dx:160; dy:10; font:0; color: clGRc
                 ),

                 ( item : '2'; title : tit_K2;
                   lst : nil; pos : 1; legal : @setK2; skip : @setNil;
                   dx:170; dy:10; font:0; color: clGRc
                 ),

                 ( item : '3'; title : tit_K3;
                   lst : nil; pos : 1; legal : @setK3; skip : @setNil;
                   dx:180; dy:10; font:0; color: clGRc
                 ),

                 ( item : '4'; title : tit_K4;
                   lst : nil; pos : 1; legal : @setK4; skip : @setNil;
                   dx:190; dy:10; font:0; color: clGRc
                 ),

                 ( item : '5'; title : tit_K5;
                   lst : nil; pos : 1; legal : @setK5; skip : @setNil;
                   dx:200; dy:10; font:0; color: clGRc
                 ),

                 ( item : '6'; title : tit_K6;
                   lst : nil; pos : 1; legal : @setK6; skip : @setNil;
                   dx:210; dy:10; font:0; color: clGRc
                 ),

                 ( item : '7'; title : tit_K7;
                   lst : nil; pos : 1; legal : @setK7; skip : @setNil;
                   dx:220; dy:10; font:0; color: clGRc
                 ),


     {_7}        ( {$IFDEF GOST}item : ' 7a     '{$ELSE}item : ' 7a    '{$ENDIF};
                   title : tit_7a;
                   lst : nil; pos : 1; legal : @setABC; skip : @setNil;
                   dx:10; dy:31; font:0; color: white{clGRe}
                 ),

     {_9}        {( item : '91'; title : tit_9a;
                   lst : nil; pos : 1; legal : @setCisl_; skip : @setNil;
                   dx:85; dy:31; font:0; color:0
                 ),}
                 ( item : '92  '; title : tit_9b;
                   lst : @fn_9b; pos : -1; legal : @setABC ; skip : @setNil;
                   dx:103; dy:31; font:0; color:0
                 ),
                 ( item : '/3'; title : tit_9c;
                   lst : @fn_9c; pos : 1; legal : @set_9c; skip : @set_NXT;
                   dx:137; dy:31; font:0; color:0
                 ),


     {_13}       ( item : '13 1'; title : tit_13a;
                   lst : @fn_13a; pos : 1; legal : @setPism_; skip : @setNil;
                   dx:10; dy:52; font:0; color:0
                 ),
                 ( item : '13 2'; title : tit_13b;
                   lst : nil; pos : 1; legal : @setCisl_; skip : @setNil;
                   dx:44; dy:52; font:0; color:0
                 ),


     {_16}       ( item : '16 1'; title : tit_16a;
                   lst : @fn_13a; pos : 1; legal : @setPism_; skip : @setNil;
                   dx:10; dy:65; font:0; color:0
                 ),
                 ( item : '16 2'; title : tit_16b;
                   lst : nil; pos : 1; legal : @setCisl_; skip : @setNil;
                   dx:44; dy:65; font:0; color:0
                 ),


     {_15}       ( item : '15  1'; title : tit_15a;
                   lst : @fn_15a; pos : 1; legal : @setRych; skip : @setNil;
                   dx:10; dy:85; font:0; color:0
                 ),

                 ( item : '15  2'; title : tit_15b;
                   lst : @fnAlt; pos : 1; legal : @setVys; skip : @setNil;
                   dx:53; dy:85; font:0; color:0
                 ),


                 ( item : '15 3                                                     ';
 {!max_RPL_15_r}   title : tit_15c;
                   lst : @fn_15; pos : -1; legal : @set_15; skip : @setNil;
                   dx:106; dy:87; font:0; color:0
                 ),
                 ( item : '15 4                                                                 ';
                   title : tit_15c;
                   lst : @fn_15; pos : -1; legal : @set_15; skip : @setNil;
                   dx:10; dy:97; font:0; color:0
                 ),
                 ( item : '15 5                                                                 ';
                   title : tit_15c;
                   lst : @fn_15; pos : -1; legal : @set_15; skip : @setNil;
                   dx:10; dy:107; font:0; color:0
                 ),
                 ( item : '15 6                                                                 ';
                   title : tit_15c;
                   lst : @fn_15; pos : -1; legal : @set_15; skip : @setNil;
                   dx:10; dy:117; font:0; color:0
                 ),
                 ( item : '15 7                                                                 ';
                   title : tit_15c;
                   lst : @fn_15; pos : -1; legal : @set_15; skip : @setNil;
                   dx:10; dy:127; font:0; color:0
                 ),
                 ( item : '15 8                                                                 ';
                   title : tit_15c;
                   lst : @fn_15; pos : -1; legal : @set_15; skip : @setNil;
                   dx:10; dy:137; font:0; color:0
                 ),


     {_18}       ( item : '18 1                                                                 ';
 {max_RPL_18_r}   title : tit_18;
                   lst : @fn_18; pos : -1; legal : @set_18; skip : @setNil;
                   dx:10; dy:157; font:0; color:0
                 ),
                 ( item : '18 2                                                                 ';
                   title : tit_18;
                   lst : @fn_18; pos : -1; legal : @set_18; skip : @setNil;
                   dx:10; dy:167; font:0; color:0
                 ),
                 ( item : '18 3                                                                 ';
                   title : tit_18;
                   lst : @fn_18; pos : -1; legal : @set_18; skip : @setNil;
                   dx:10; dy:177; font:0; color:0
                 )
                );
     {$ENDIF}