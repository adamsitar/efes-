const  i_kod    = 0;
       i_dat    = 1;
       i_zac    = 2;
       i_kon    = 3;
       i_prav   = 4;
       i_vys    = 5;
       i_vu     = 6;
       i_ulohy  = 7;
       i_typy   = 8;
       i_planov = 9;
       i_lomka  = 10;
       i_letov  = 11;
       i_pozn0  = 12;
       i_pozn1  = 13;

       SIZE_frm_ZAM  = 14;


const  {$IFDEF SLOVAK}
         tit_zam_let       = 'k¢d letiska';
         tit_zam_den       = 'd tum platnosti';
         tit_zam_zac       = 'pl novan˜ za‡iatok';
         tit_zam_kon       = 'pl novan˜ koniec';
         tit_zam_prav      = 'pravidl  letu';
         tit_zam_vys_hi    = 'horn  v˜¨ka';
         tit_zam_prev      = 'prev dzkovateŒ';
         tit_zam_ulohy     = '£lohy';
         tit_zam_typy      = 'typy lietadiel';
         tit_zam_planov    = 'pl novan˜ po‡et vzletov';
         tit_zam_letov     = 'realizovan˜ po‡et vzletov';
         tit_zam_pozn      = 'pozn mky a doplnkov‚ £daje';
       {$ENDIF}

       {$IFDEF CZECH}
         tit_zam_let       = 'k¢d leti¨tˆ';
         tit_zam_den       = 'd tum platnosti';
         tit_zam_zac       = 'pl novan˜ za‡ tek';
         tit_zam_kon       = 'pl novan˜ konec';
         tit_zam_prav      = 'pravidla letu';
         tit_zam_vys_hi    = 'horn¡ v˜¨ka';
         tit_zam_prev      = 'provozovatel';
         tit_zam_ulohy     = '£kohy';
         tit_zam_planov    = 'pl novan˜ po‡et vzlet–';
         tit_zam_letov     = 'realizovan˜ po‡et vzlet–';
         tit_zam_typy      = 'typy letadel';
         tit_zam_pozn      = 'pozn mky a doplnkov‚ £daje';
       {$ENDIF}

       {$IFDEF ENGLISH}
         tit_zam_let       = 'airport code';
         tit_zam_den       = 'plan validity';
         tit_zam_zac       = 'planned beginning';
         tit_zam_kon       = 'planned end';
         tit_zam_prav      = 'flight rules';
         tit_zam_vys_hi    = 'upper altitude';
         tit_zam_prev      = 'flight operator';
         tit_zam_ulohy     = 'tasks';
         tit_zam_planov    = 'planned flights';
         tit_zam_letov     = 'realized flights';
         tit_zam_typy      = 'aircraft types';
         tit_zam_pozn      = 'remarks';
       {$ENDIF}


const  frm_ZAM: array [0..SIZE_frm_ZAM-1] of TForm =
            (( item : '   0';
               title: tit_zam_let;
               lst  : @fn_13aM; pos: 1; legal: @setABC; skip : @setNil;
               dx:14; dy:10; font:0; color: 0
             ),
             ( item : '     1';
               title: tit_zam_den;
               lst : nil; pos: -1; legal: @setCisl; skip : @setNil;
               dx:62; dy:10; font:0; color: 0
             ),
             ( item : '  : 0';
               title: tit_zam_zac;
               lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
               dx:120 ; dy:10; font:0; color: 0
             ),
             ( item : 'ÿ : 1';
               title: tit_zam_kon;
               lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
               dx:170; dy:10; font:0; color: 0
             ),
             ( item : '2';
               title: tit_zam_prav;
               lst : @fn_8a; pos: 1; legal: @set_8aM; skip : @setNil;
               dx:230 ; dy:10; font:0; color: 0
             ),
             {
             ( item : 'G'; title: 'veli‡ina v˜¨ky';
               lst : @fnAlt_; pos: 1; legal: @setVys_; skip : @setNil;
               dx:185; dy:10; font:0; color: 0
             ),
             }
             ( item : '     ';
               title: tit_zam_vys_hi;
               lst : @fnAlt_H; pos: -1; legal: @setABC; skip : @setNil;
               dx:245; dy:10; font:0; color: 0
             ),
             ( item : '  5';
               title: tit_zam_prev;
               lst : @fnPrevM; pos: 1; legal: @setCisl; skip : @setNil;
               dx:14; dy:30; font:0; color: 0      { 245,10 }
             ),
             ( item : '                                        ';
               title: tit_zam_ulohy;
               lst : @fnUlohyM; pos: -1; legal: @setCisl; skip : @setNil;
               dx:46 ; dy:30; font:0; color: 0
             ),
             ( item : '01 02 03 04 05';
               title: tit_zam_typy;
               lst : @fn_9bMIL; pos: -1; legal: @setABC; skip : @setNil;
               dx:14 ; dy:44; font:0; color: 0
             ),
             ( item : ' 20';
               title: tit_zam_planov;
               lst : nil; pos: -1; legal: @setCisl; skip : @setNil;
               dx:135 ; dy:44; font:0; color: 0
             ),
             ( item : '/';
               title: '';
               lst : nil; pos: -1; legal: @setNil; skip : @setNil;
               dx:160 ; dy:44; font:0; color: 0
             ),
             ( item : ' 21';
               title: tit_zam_letov;
               lst : nil; pos: -1; legal: @setCisl; skip : @setNil;
               dx:170 ; dy:44; font:0; color: 0
             ),
             ( item : '                                          22';
               title: tit_zam_pozn;
               lst : @fn_18M; pos: -1; legal: @set_POZN; skip : @setNil;
               dx:14 ; dy:67; font:0; color: 0
             ),
             ( item : '                                          23';
               title: tit_zam_pozn;
               lst : @fn_18M; pos: -1; legal: @set_POZN; skip : @setNil;
               dx:14 ; dy:77; font:0; color: 0
             )
            );

