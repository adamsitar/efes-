const  it_NTM  = 0;
       it_Q    = 1;   max_Q = 8;
       it_A    = 16;
       it_B    = 17;
       it_C    = 18;
       it_D    = 19;
       it_E    = 22;
       it_F    = 31;
       it_G    = 32;


const  tit_N  =  {$IFDEF SLOVAK}  'S‚ria, ‡¡slo a identifik tor NOTAMu (N, R, C)'; {$ENDIF}
                 {$IFDEF CZECH}   ? {$ENDIF}
                 {$IFDEF ENGLISH} ? {$ENDIF}

       tit_Q1 =  {$IFDEF SLOVAK}  'Q) FIR'; {$ENDIF}
                 {$IFDEF CZECH}   ? {$ENDIF}
                 {$IFDEF ENGLISH} ? {$ENDIF}

       tit_Q2 =  {$IFDEF SLOVAK}  'Q) NOTAM k¢d'; {$ENDIF}
                 {$IFDEF CZECH}   ? {$ENDIF}
                 {$IFDEF ENGLISH} ? {$ENDIF}

       tit_Q3 =  {$IFDEF SLOVAK}  'Q) Prev dzka'; {$ENDIF}
                 {$IFDEF CZECH}   ? {$ENDIF}
                 {$IFDEF ENGLISH} ? {$ENDIF}

       tit_Q4 =  {$IFDEF SLOVAK}  'Q) —‡el'; {$ENDIF}
                 {$IFDEF CZECH}   ? {$ENDIF}
                 {$IFDEF ENGLISH} ? {$ENDIF}

       tit_Q5 =  {$IFDEF SLOVAK}  'Q) Rozsah'; {$ENDIF}
                 {$IFDEF CZECH}   ? {$ENDIF}
                 {$IFDEF ENGLISH} ? {$ENDIF}

       tit_Q6 =  {$IFDEF SLOVAK}  'Q) Doln  hranica'; {$ENDIF}
                 {$IFDEF CZECH}   ? {$ENDIF}
                 {$IFDEF ENGLISH} ? {$ENDIF}

       tit_Q7 =  {$IFDEF SLOVAK}  'Q) Horn  hranica'; {$ENDIF}
                 {$IFDEF CZECH}   ? {$ENDIF}
                 {$IFDEF ENGLISH} ? {$ENDIF}

       tit_Q8 =  {$IFDEF SLOVAK}  'Q) Zemepisn‚ s£radnice/polomer'; {$ENDIF}
                 {$IFDEF CZECH}   ? {$ENDIF}
                 {$IFDEF ENGLISH} ? {$ENDIF}


       tit_A  =  {$IFDEF SLOVAK}  'A) ICAO smerovacia zna‡ka miesta zariadenia, priestoru, podmienok'; {$ENDIF}
                 {$IFDEF CZECH}   ? {$ENDIF}
                 {$IFDEF ENGLISH} ? {$ENDIF}


       tit_B  =  {$IFDEF SLOVAK}  'B) Od (d tum a ‡as) [rrmmddhhmm]'; {$ENDIF}
                 {$IFDEF CZECH}   ? {$ENDIF}
                 {$IFDEF ENGLISH} ? {$ENDIF}

       tit_C  =  {$IFDEF SLOVAK}  'C) Do (PERM alebo d tum a ‡as) [rrmmddhhmm]'; {$ENDIF}
                 {$IFDEF CZECH}   ? {$ENDIF}
                 {$IFDEF ENGLISH} ? {$ENDIF}


       tit_D  =  {$IFDEF SLOVAK}  'D) €asov‚ rozp„tie (ak je vhodn‚)'; {$ENDIF}
                 {$IFDEF CZECH}   ? {$ENDIF}
                 {$IFDEF ENGLISH} ? {$ENDIF}


       tit_E  =  {$IFDEF SLOVAK}  'E) Text NOTAMu v otvorenej re‡i (napr. GBELY (484305N0170725E))'; {$ENDIF}
                 {$IFDEF CZECH}   ? ''; {$ENDIF}
                 {$IFDEF ENGLISH} ? ''; {$ENDIF}


       tit_F  =  {$IFDEF SLOVAK}  'F) Doln  hranica'; {$ENDIF}
                 {$IFDEF CZECH}   ? {$ENDIF}
                 {$IFDEF ENGLISH} ? {$ENDIF}

       tit_G  =  {$IFDEF SLOVAK}  'G) Horn  hranica'; {$ENDIF}
                 {$IFDEF CZECH}   ? {$ENDIF}
                 {$IFDEF ENGLISH} ? {$ENDIF}


const  size_frm_PRZ = 34 {7 + max_PRZ_pozn_r_hi + max_PRZ_sur_r_hi};

       frm_PRZ: array [0..size_frm_PRZ-1] of TForm =
            (

 {NTM}       ( item : '  0431 97       '; title: tit_N; {C 0431/97 NOTAMN}
               lst : nil; pos: 1; legal: {$IFDEF VLIS} @set_DATA {$ELSE} nil {$ENDIF}; skip : @setNil;
               dx:10; dy:10; font:0; color: 0
             ),

 {Q}         ( item : ' 1  '; title: tit_Q1;
               lst : nil; pos: 1; legal: @set_15; skip : @setNil;
               dx:10; dy:24; font:0; color: 0
             ),
             ( item : '/'; title: '';
               lst : nil; pos: 1; legal: @setNil; skip : @setNil;
               dx:44; dy:24; font:0; color: clGRb
             ),

             ( item : 'Q   3'; title: tit_Q2;
               lst : nil; pos: 1; legal: @set_15; skip : @setNil;
               dx:54; dy:24; font:0; color: 0
             ),
             ( item : '/'; title: '';
               lst : nil; pos: 1; legal: @setNil; skip : @setNil;
               dx:96; dy:24; font:0; color: clGRb
             ),

             ( item : ' 5 '; title: tit_Q3;
               lst : nil; pos: 1; legal: @set_15; skip : @setNil;
               dx:106; dy:24; font:0; color: 0
             ),
             ( item : '/'; title: '';
               lst : nil; pos: 1; legal: @setNil; skip : @setNil;
               dx:132; dy:24; font:0; color: clGRb
             ),

             ( item : ' 7 '; title: tit_Q4;
               lst : nil; pos: 1; legal: @set_15; skip : @setNil;
               dx:142; dy:24; font:0; color: 0
             ),
             ( item : '/'; title: '';
               lst : nil; pos: 1; legal: @setNil; skip : @setNil;
               dx:168; dy:24; font:0; color: clGRb
             ),

             ( item : ' 9 '; title: tit_Q5;
               lst : nil; pos: 1; legal: @set_15; skip : @setNil;
               dx:178; dy:24; font:0; color: 0
             ),
             ( item : '/'; title: '';
               lst : nil; pos: 1; legal: @setNil; skip : @setNil;
               dx:204; dy:24; font:0; color: clGRb
             ),

             ( item : ' 11'; title: tit_Q6;
               lst : nil; pos: 1; legal: @set_15; skip : @setNil;
               dx:214; dy:24; font:0; color: 0
             ),
             ( item : '/'; title: '';
               lst : nil; pos: 1; legal: @setNil; skip : @setNil;
               dx:240; dy:24; font:0; color: clGRb
             ),

             ( item : ' 13'; title: tit_Q7;
               lst : nil; pos: 1; legal: @set_15; skip : @setNil;
               dx:250; dy:24; font:0; color: 0
             ),
             ( item : '/'; title: '';
               lst : nil; pos: 1; legal: @setNil; skip : @setNil;
               dx:274; dy:24; font:0; color: clGRb
             ),

             ( item : ' 15           '; title: tit_Q8;
               lst : nil; pos: 1; legal: @set_15; skip : @setNil;
               dx:284; dy:24; font:0; color: 0
             ),


 {A}         ( item : ' 16 ';
               title: tit_A;
               lst : @fnR; pos: 1; legal: @setABC; skip : @setNil;
               dx:10; dy:59; font:0; color: 0
             ),


 {B}         ( item : '   17     ';
               title: tit_B;
               lst  : nil; pos: 0; legal: @setCisl; skip : @setDatum;
               dx:86; dy:45; font:0; color: 0
             ),
 {C}         ( item : '   18        ';
               title: tit_C;
               lst  : @fnDate; pos: -1; legal: @setABC; skip : @setDatum;
               dx:86; dy:59; font:0; color: 0
             ),


 {D}         ( item : ' 19                                                                  ';
               title: tit_D; lst : nil; pos: 1; legal: @set_15; skip : @setNil;
               dx:10; dy:80; font:0; color: 0
             ),
             ( item : ' 20                                                                  ';
               title: tit_D; lst : nil; pos: 1; legal: @set_15; skip : @setNil;
               dx:10; dy:90; font:0; color: 0
             ),
             ( item : ' 21                                                                  ';
               title: tit_D; lst : nil; pos: 1; legal: @set_15; skip : @setNil;
               dx:10; dy:100; font:0; color: 0
             ),


 {E}         ( item : ' 22                                                                  ';
               title: tit_E; lst : nil; pos: 1; legal: @set_18; skip : @setNil;
               dx:10; dy:120; font:0; color: 0
             ),
             ( item : ' 23                                                                  ';
               title: tit_E; lst : nil; pos: 1; legal: @set_18; skip : @setNil;
               dx:10; dy:130; font:0; color: 0
             ),
             ( item : ' 24                                                                  ';
               title: tit_E; lst : nil; pos: 1; legal: @set_18; skip : @setNil;
               dx:10; dy:140; font:0; color: 0
             ),
             ( item : ' 25                                                                  ';
               title: tit_E; lst : nil; pos: 1; legal: @set_18; skip : @setNil;
               dx:10; dy:150; font:0; color: 0
             ),
             ( item : ' 26                                                                  ';
               title: tit_E; lst : nil; pos: 1; legal: @set_18; skip : @setNil;
               dx:10; dy:160; font:0; color: 0
             ),
             ( item : ' 27                                                                  ';
               title: tit_E; lst : nil; pos: 1; legal: @set_18; skip : @setNil;
               dx:10; dy:170; font:0; color: 0
             ),
             ( item : ' 28                                                                  ';
               title: tit_E; lst : nil; pos: 1; legal: @set_18; skip : @setNil;
               dx:10; dy:180; font:0; color: 0
             ),
             ( item : ' 29                                                                  ';
               title: tit_E; lst : nil; pos: 1; legal: @set_18; skip : @setNil;
               dx:10; dy:190; font:0; color: 0
             ),
             ( item : ' 30                                                                  ';
               title: tit_E; lst : nil; pos: 1; legal: @set_18; skip : @setNil;
               dx:10; dy:200; font:0; color: 0
             ),


             ( item : '  31 ';
               title: tit_F;
               lst : @fnAlt_L; pos: -1; legal: @setABC; skip : @setNil;
               dx:10; dy:220; font:0; color: 0
               {dx:206; dy:45; font:0; color: 0}
             ),
             ( item : '  32 ';
               title: tit_G;
               lst : @fnAlt_H; pos: -1; legal: @setABC; skip : @setNil;
               dx:10; dy:234; font:0; color: 0
               {dx:252; dy:45; font:0; color: 0}
             )

             ,( item : '* ‡o sa nehod¡, pre‡iarknite'; title: '';
               lst : nil; pos: 1; legal: @setNil; skip : @setNil;
               dx:338; dy:230; font:$0; color: clGR9
             )
            );


