      const  SIZE_frm_mFPL = i_TSKM+1 + max_mFPL_15_r_hi + max_mFPL_18_r_hi;

     {$IFDEF L4444M}
             form_mFPL: array [0..SIZE_frm_mFPL-1] of TForm =
                   (( item : {$IFDEF FPL} '1234567' {$ELSE} '100 ÿ' {$ENDIF};
                      title: tit_7Ma;
                      lst : nil; pos: 1; legal: @setABC; skip : @setNil;
                      dx:10; dy:10; font:0; color: white
                    ),
                    ( item : 'N';
                      title: tit_7Mb;
                      lst : @fn_10b; pos: 1; legal: @set_10b; skip : @setNil;
                      dx:77 ; dy:10; font:0; color: white
                    ),
                    ( {$IFDEF GOST} item : '77777' {$ELSE} item : '7777' {$ENDIF};
                      title: tit_7Mc;
                      lst : @fn_7bM; pos: 1; legal: @set_7c; skip : @setNil;
                      dx:88; dy:10; font:0; color: white
                    ),
                    ( item : '3';
                      title: tit_8Ma;
                      lst : @fn_8a; pos: 1; legal: @set_8aM; skip : @setNil;
                      dx:134; dy:10; font:0; color: white
                    ),
                    ( item  : '4';
                      title: tit_8Mb;
                      lst : @fn_8bM; pos: 1; legal: @set_8bM; skip : @setNil;
                      dx:144; dy:10; font:0; color: white
                    ),
                    ( item : '5    ÿ';
                      title: tit_9Mb;
                      lst : @fn_9bMIL; pos: -1; legal: @setABC_; skip : @setNil;
                      dx:10 ; dy:23; font:0; color: 0
                    ),
                    ( item : '6     ';
                      title: tit_9Me;
                      lst : @fn_9bMIL; pos: -1; legal: @setABC_; skip : @setNil;
                      dx:62 ; dy:23; font:0; color: 0
                    ),
                    ( item : 'K';
                      title: tit_15Ma_;
                      lst : @fn_15a; pos: 1; legal: @setRych; skip : @setNil;
                      dx:120; dy:23; font:0; color: 0
                    ),
                    ( item : '7   ';
                      title: tit_15Ma;
                      lst : nil;       { tu by mohla by fcia pre vratenie standartnej rychlosti
                                         alebo sa zapise sama pri nacitani z frm
                                       }
                      pos: 1; legal: @setCisl; skip : @setNil;
                      dx:130; dy:23; font:0; color: 0
                    ),
                    ( item : '8   ';
                      title: tit_13Ma; lst : @fn_13aM;
                      pos: 1; legal: @setABC; skip : @setNil;
                      dx:179; dy:10; font:0; color: 0
                    ),
                    ( item : ' 9:  ';
                      title: tit_13Mb;
                      lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                      dx:218; dy:10; font:0; color: 0
                    ),
                    ( item : '10  ';
                      title: tit_16Ma; lst : @fn_16aM;
                      pos: 1; legal: @setABC; skip : @setNil;
                      dx:179; dy:23; font:0; color: 0
                    ),
                    ( item : '11:  ';
                      title: tit_16Mb;
                      lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                      dx:218; dy:23; font:0; color: 0
                    ),
                    (*
                    ( item : 'S';   title:
                      {$IFDEF SLOVAK} 'veli‡ina v˜¨ky'; {$ENDIF}
                      {$IFDEF CZECH}  'veli‡ina v˜¨ky'; {$ENDIF}
                      {$IFDEF ENGLISH} 'flight level quantity' ; {$ENDIF}
                      lst : @fnAlt_; pos: 1; legal: @setVys_; skip : @setNil;
                      dx:246 ; dy:10; font:0; color: 0
                    ),
                    *)
                    ( item : '12   ';
                      title: tit_15Mb1;
                      lst : @fnAlt; pos: 1; legal: @setVys; skip : @setNil;
                      dx:275 ; dy:10; font:0; color: 0
                    ),
                    (*
                    ( item : '0';   title:
                      {$IFDEF SLOVAK}  'veli‡ina v˜¨ky'; {$ENDIF}
                      {$IFDEF CZECH}   'veli‡ina v˜¨ky'; {$ENDIF}
                      {$IFDEF ENGLISH} 'flight level quantity' ; {$ENDIF}
                      lst : @fnAlt_; pos: 1; legal: @setVys_; skip : @setNil;
                      dx:246 ; dy:23; font:0; color: 0
                    ),
                    *)
                    ( item : '13   ';
                      title: tit_15Mb2;
                      lst : @fnAlt; pos: 1; legal: @setVys; skip : @setNil;
                      dx:275 ; dy:23; font:0; color: 0
                    ),
                    ( item : '14 ';
                      title: tit_OPM;
                      lst : @fnPrevM; pos: 1; legal: @setABC; skip : @setNil;
                      dx:346 ; dy:15; font:0; color: 0
                    ),
                    ( item : '  ';
                      title: tit_TSKM;
                      lst : @fnUlohyM; pos: -1; legal: @setNil; skip : @setNil;
                      dx:396 ; dy:15; font:0; color: 0
                    ),

                    { -------------------------------------------- }
                    { body na trati                                }
                    { -------------------------------------------- }
                    ( item : '16                                                         ';
                      title: tit_15Mc;
                      lst : @fn_15M; pos: -1; legal: @set_15; skip : @setNil;
                      dx:10; dy:42; font:0; color: 0
                    ),
                    ( item : '17                                                         ';
                      title: tit_15Mc;
                      lst : @fn_15M; pos: -1; legal: @set_15; skip : @setNil;
                      dx:10; dy:52; font:0; color: 0
                    ),
                    ( item : '18                                                         ';
                      title: tit_15Mc;
                      lst : @fn_15M; pos: -1; legal: @set_15; skip : @setNil;
                      dx:10; dy:62; font:0; color: 0
                    ),
                    ( item : '20                                                         ';
                      title: tit_15Mc;
                      lst : @fn_15M; pos: -1; legal: @set_15; skip : @setNil;
                      dx:10; dy:72; font:0; color: 0
                    ),

                    { -------------------------------------------- }
                    { poznamka                                     }
                    { -------------------------------------------- }
                    ( item : '21                                                         ';
                      title: tit_18M;
                      lst : @fn_18M; pos: -1; legal: @set_18; skip : @setNil;
                      dx:10 ; dy: 92; font:0; color: 0
                    ),
                    ( item : '22                                                         ';
                      title: tit_18M;
                      lst : @fn_18M; pos: -1; legal: @set_18; skip : @setNil;
                      dx:10 ; dy:102; font:0; color: 0
                    ),
                    ( item : '23                                                         ';
                      title: tit_18M;
                      lst : @fn_18M; pos: -1; legal: @set_18; skip : @setNil;
                      dx:10 ; dy:112; font:0; color: 0
                    )
                   );
     {$ELSE}
             form_mFPL: array [0..SIZE_frm_mFPL-1] of TForm =
                   (( item : '100 ÿ';
                      title: tit_7Ma;
                      lst : nil; pos: 1; legal: @setABC; skip : @setNil;
                      dx:10; dy:10; font:0; color: yellow
                    ),
                    ( item : '1';
                      title: tit_7Ma2;
                      lst : @fn_7xM; pos: 1;
                      legal: {$IFDEF L4444M} @setNil {$ELSE} @set_7Ma2 {$ENDIF};
                      skip : @setNil;
                      dx: 53; dy:10; font:0; color: yellow
                    ),
                    ( item : 'N';
                      title: tit_7Mb;
                      lst : @set_10b; pos: 1; legal: @set_10b; skip : @setNil;
                      dx:66; dy:10; font:0; color: 0
                    ),
                    ( {$IFDEF GOST} item : '77777' {$ELSE} item : '7777' {$ENDIF};
                      title: tit_7Mc;
                      lst : @fn_7bM; pos: 1; legal: @set_7c; skip : @setNil;
                      dx:77; dy:10; font:0; color: 0
                    ),
                    ( item : '4';
                      title: tit_8Ma;
                      lst : @fn_8a; pos: 1; legal: @set_8aM; skip : @setNil;
                      dx:120 ; dy:10; font:0; color: 0
                    ),
                    ( item : '5  ÿ';
                      title: tit_9Mb;
                      lst : @fn_9bMIL; pos: -1; legal: @setABC_; skip : @setNil;
                      dx:10 ; dy:23; font:0; color: 0
                    ),
                    ( item : '6   ';
                      title: tit_9Me;
                      lst : @fn_9bMIL; pos: -1; legal: @setABC_; skip : @setNil;
                      dx:46 ; dy:23; font:0; color: 0
                    ),
                    ( item : 'K';
                      title: tit_15Ma_;
                      lst : @fn_15a; pos: 1; legal: @setRych; skip : @setNil;
                      dx:91; dy:23; font:0; color: 0
                    ),
                    ( item : '7   ';
                      title: tit_15Ma;
                      lst : nil;       { tu by mohla by fcia pre vratenie standartnej rychlosti
                                         alebo sa zapise sama pri nacitani z frm
                                       }
                      pos: 1; legal: @setCisl; skip : @setNil;
                      dx:101; dy:23; font:0; color: 0
                    ),
                    (*
                    ( item : 'k';    title:
                      {$IFDEF SLOVAK} 'veli‡ina r˜chlosti'; {$ENDIF} { 57 }
                      {$IFDEF CZECH}  'veli‡ina r˜chlosti'; {$ENDIF} { 57 }
                      {$IFDEF ENGLISH} 'speed quantity' ; {$ENDIF}
                      lst : @fn_9a; pos: 1; legal: @setKN; skip : @setNil;
                      dx:125; dy:23; font:0; color: 0
                    ),
                    *)
                    ( item : '8   ';
                      title: tit_13Ma; lst : @fn_13aM;
                      pos: 1; legal: @setABC; skip : @setNil;
                      dx:147; dy:10; font:0; color: 0
                    ),
                    ( item : ' 9:  ';
                      title: tit_13Mb;
                      lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                      dx:186; dy:10; font:0; color: 0
                    ),
                    ( item : '10  ';
                      title: tit_16Ma; lst : @fn_16aM;
                      pos: 1; legal: @setABC; skip: @setNil;
                      dx:147; dy:23; font:0; color: 0
                    ),
                    ( item : '11:  ';
                      title: tit_16Mb;
                      lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
                      dx:186; dy:23; font:0; color: 0
                    ),
                    (*
                    ( item : 'S';   title:
                      {$IFDEF SLOVAK} 'veli‡ina v˜¨ky'; {$ENDIF}
                      {$IFDEF CZECH}  'veli‡ina v˜¨ky'; {$ENDIF}
                      {$IFDEF ENGLISH} 'flight level quantity' ; {$ENDIF}
                      lst : @fnAlt_; pos: 1; legal: @setVys_; skip : @setNil;
                      dx:246 ; dy:10; font:0; color: 0
                    ),
                    *)
                    ( item : '12   ';
                      title: tit_15Mb1;
                      lst : @fnAlt; pos: 1; legal: @setVys; skip : @setNil;
                      dx:242 ; dy:10; font:0; color: 0
                    ),
                    (*
                    ( item : '0';   title:
                      {$IFDEF SLOVAK}  'veli‡ina v˜¨ky'; {$ENDIF}
                      {$IFDEF CZECH}   'veli‡ina v˜¨ky'; {$ENDIF}
                      {$IFDEF ENGLISH} 'flight level quantity' ; {$ENDIF}
                      lst : @fnAlt_; pos: 1; legal: @setVys_; skip : @setNil;
                      dx:246 ; dy:23; font:0; color: 0
                    ),
                    *)
                    ( item : '13   ';
                      title: tit_15Mb2;
                      lst : @fnAlt; pos: 1; legal: @setVys; skip : @setNil;
                      dx:242 ; dy:23; font:0; color: 0
                    ),
                    ( item : '14 ';
                      title: tit_OPM;
                      lst : @fnPrevM; pos: 1; legal: @setCisl; skip : @setNil;
                      dx:313 ; dy:15; font:0; color: 0
                    ),
                    ( item : '15               ';
                      title: tit_TSKM;
                      lst : @fnUlohyM; pos: -1; legal: @setCisl; skip : @setNil;
                      dx:344 ; dy:15; font:0; color: 0
                    ),

                    { -------------------------------------------- }
                    { body na trati                                }
                    { -------------------------------------------- }
                    ( item : '16                                                         ';
                      title: tit_15Mc;
                      lst : @fn_15M; pos: -1; legal: @set_15; skip : @setNil;
                      dx:10; dy:42; font:0; color: 0
                    ),
                    ( item : '17                                                         ';
                      title: tit_15Mc;
                      lst : @fn_15M; pos: -1; legal: @set_15; skip : @setNil;
                      dx:10; dy:52; font:0; color: 0
                    ),
                    ( item : '18                                                         ';
                      title: tit_15Mc;
                      lst : @fn_15M; pos: -1; legal: @set_15; skip : @setNil;
                      dx:10; dy:62; font:0; color: 0
                    ),
                    ( item : '20                                                         ';
                      title: tit_15Mc;
                      lst : @fn_15M; pos: -1; legal: @set_15; skip : @setNil;
                      dx:10; dy:72; font:0; color: 0
                    ),

                    { -------------------------------------------- }
                    { poznamka                                     }
                    { -------------------------------------------- }
                    ( item : '21                                                         ';
                      title: tit_18M;
                      lst : @fn_18M; pos: -1; legal: @set_18; skip : @setNil;
                      dx:10 ; dy: 92; font:0; color: 0
                    ),
                    ( item : '22                                                         ';
                      title: tit_18M;
                      lst : @fn_18M; pos: -1; legal: @set_18; skip : @setNil;
                      dx:10 ; dy:102; font:0; color: 0
                    ),
                    ( item : '23                                                         ';
                      title: tit_18M;
                      lst : @fn_18M; pos: -1; legal: @set_18; skip : @setNil;
                      dx:10 ; dy:112; font:0; color: 0
                    )
                   );
     {$ENDIF}