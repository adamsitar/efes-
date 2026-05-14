{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ ZAMESTNANIE LETISKA                                      €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
const  Form_ZAM: array [0..SIZE_frm_ZAM-1] of TForm =
            (( item : '  0';
               {$IFDEF SLOVAK}  title: 'k¢d letiska';  {$ENDIF}
               {$IFDEF CZECH}   title: 'k¢d leti®tà';  {$ENDIF}
               {$IFDEF ENGLISH} title: 'airport code'; {$ENDIF}
               lst  : @fnAMLet; pos: 1; legal: @setCisl; skip : @setNil;
               dx:14; dy:10; font:0; color: 0
             ),
             ( item : '  : 0';
               {$IFDEF SLOVAK}  title: 'pl†novanò zaáiatok'; {$ENDIF}
               {$IFDEF CZECH}   title: 'pl†novanò zaá†tek';  {$ENDIF}
               {$IFDEF ENGLISH} title: 'planned start';      {$ENDIF}
               lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
               dx:60 ; dy:10; font:0; color: 0
             ),
             ( item : 'ˇ : 1';
               {$IFDEF SLOVAK}  title: 'pl†novanò koniec'; {$ENDIF}
               {$IFDEF CZECH}   title: 'pl†novanò konec';  {$ENDIF}
               {$IFDEF ENGLISH} title: 'planned end';      {$ENDIF}
               lst : nil; pos: 1; legal: @setCisl; skip : @setCas;
               dx:110; dy:10; font:0; color: 0
             ),
             ( item : '2';
               {$IFDEF SLOVAK}  title: 'pravidl† letu'; {$ENDIF}
               {$IFDEF CZECH}   title: 'pravidla letu'; {$ENDIF}
               {$IFDEF ENGLISH} title: 'flight rules';  {$ENDIF}
               lst : @fn_8a; pos: 1; legal: @set_8aM; skip : @setNil;
               dx:170 ; dy:10; font:0; color: 0
             ),
             {
             ( item : 'G'; title: 'veliáina vò®ky';
               lst : @fnAlt_; pos: 1; legal: @setVys_; skip : @setNil;
               dx:185; dy:10; font:0; color: 0
             ),
             }
             ( item : '      ';
               {$IFDEF SLOVAK}  title:'horn† vò®ka';    {$ENDIF}
               {$IFDEF CZECH}   title:'horn° vò®ka';    {$ENDIF}
               {$IFDEF ENGLISH} title:'upper altitude'; {$ENDIF}
               lst : @fnAlt ; pos: 1; legal: @setVys; skip : @setNil;
               dx:185; dy:10; font:0; color: 0
             ),
             ( item : ' 5';
               {$IFDEF SLOVAK}  title: 'prev†dzkovateå';  {$ENDIF}
               {$IFDEF CZECH}   title: 'provozovatel';    {$ENDIF}
               {$IFDEF ENGLISH} title: 'flight operator'; {$ENDIF}
               lst : @fnPrevM; pos: 1; legal: @setCisl; skip : @setNil;
               dx:14; dy:30; font:0; color: 0      { 245,10 }
             ),
             ( item : '                                      ';
               {$IFDEF SLOVAK}  title: '£lohy';     {$ENDIF}
               {$IFDEF CZECH}   title: '£koly';     {$ENDIF}
               {$IFDEF ENGLISH} title: 'tasks';     {$ENDIF}
               lst : @fnUlohyM; pos: -1; legal: @setCisl; skip : @setNil;
               dx:37 ; dy:30; font:0; color: 0
             ),
             ( item : '                                       19';
               {$IFDEF SLOVAK}  title: 'typy lietadiel'; {$ENDIF}
               {$IFDEF CZECH}   title: 'typy letadel';   {$ENDIF}
               {$IFDEF ENGLISH} title: 'aircraft types'; {$ENDIF}
               lst : @fn_9bM; pos: -1; legal: @setABC_; skip : @setNil;
               dx:14 ; dy:44; font:0; color: 0
             ),
             ( item : '                                       20';
               {$IFDEF SLOVAK}  title: 'pozn†mky a doplnkovÇ £daje'; {$ENDIF}
               {$IFDEF CZECH}   title: 'pozn†mky a doplnkovÇ £daje'; {$ENDIF}
               {$IFDEF ENGLISH} title: 'remarks';                    {$ENDIF}
               lst : @fn_18M; pos: -1; legal: @setABCcs_; skip : @setNil;
               dx:14 ; dy:67; font:0; color: 0
             ),
             ( item : '                                       21';
               {$IFDEF SLOVAK}  title: 'pozn†mky a doplnkovÇ £daje'; {$ENDIF}
               {$IFDEF CZECH}   title: 'pozn†mky a doplnkovÇ £daje'; {$ENDIF}
               {$IFDEF ENGLISH} title: 'remarks';                    {$ENDIF}
               lst : @fn_18M; pos: -1; legal: @setABCcs_; skip : @setNil;
               dx:14 ; dy:77; font:0; color: 0
             )
            );
