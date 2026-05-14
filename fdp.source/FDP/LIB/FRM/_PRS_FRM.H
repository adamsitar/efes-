  const  it_KOD   = 0;
         it_LET   = 1;
         it_DAT   = 2;
         it_ZAC   = 3;
         it_KON   = 4;
         it_VYS1  = 5;
         it_VYS2  = 6;
         it_TYP   = 7;
         it_UNT   = 8;
         it_POZN  = 9;

         size_frm_PRS = 9 + max_PRS_pozn_r_hi;


  const  frm_PRS: array [0..size_frm_PRS-1] of TForm =
              (
               ( item : '0       '; title: tit_prs_kod;
                 lst : @fnAREA; pos: 1; legal: @setABC; skip : @setNil;
                 dx:10; dy:10; font:0; color: 0
               ),
               ( item : '1   '; title: tit_prs_let;
                 lst : @fnMLet; pos: 1; legal: @setABC; skip : @setNil;
                 dx:10; dy:23; font:0; color: 0
               ),
               ( item : '2     '; title: tit_prs_dat;
                 lst  : nil; pos: 0; legal: @setCisl; skip : @setDatum;
                 dx:86; dy:10; font:0; color: 0
               ),
               ( item : '3   '; title: tit_prs_zac;
                 lst : nil; pos: 0; legal: @setCisl; skip : @setCas;
                 dx:140; dy:10; font:0; color: 0
               ),
               ( item : '4   '; title: tit_prs_kon;
                 lst : nil; pos: 0; legal: @setCisl; skip : @setCas;
                 dx:140; dy:23; font:0; color: 0
               ),
               ( item : '5    '; title: tit_prs_vys1;
                 lst : @fnAlt_L; pos: 1; legal: @setABC; skip : @setNil;
                 dx:186; dy:10; font:0; color: 0
               ),
               ( item : '6    '; title: tit_prs_vys2;
                 lst : @fnAlt_H; pos: 1; legal: @setABC; skip : @setNil;
                 dx:232; dy:10; font:0; color: 0
               ),
               ( item  : '7'; title: tit_prs_typ;
                 lst : @fnR_TYPE; pos: 1; legal: @set_R_TYPE; skip : @setNil;
                 dx:285; dy:10; font:0; color: white
               ),
               ( item : '8   '; title: tit_prs_unt;
                 lst : @fnPrevM; pos: 1; legal: @setABC; skip : @setNil;
                 dx:299; dy:10; font:0; color: 0
               ),
               ( item : '                                       10';
                 title: tit_prs_pozn;
                 lst : @fn_18M; pos: -1; legal: @set_18; skip : @setNil;
                 dx:10 ; dy:45; font:0; color: 0
               ),
               ( item : '                                       11';
                 title: tit_prs_pozn;
                 lst : @fn_18M; pos: -1; legal: @set_18; skip : @setNil;
                 dx:10 ; dy:55; font:0; color: 0
               ),
               ( item : '                                       12';
                 title: tit_prs_pozn;
                 lst : @fn_18M; pos: -1; legal: @set_18; skip : @setNil;
                 dx:10 ; dy:65; font:0; color: 0
               )
              );

