    {$IFDEF RUSSIAN}
     const  titn_3   = ' - '+'’ˆ ‘™…ˆŸ';

            titn_5a  = ' - '+'ˆ”Œ€–ˆŸ  €‚€ˆ‰‰ ‘ˆ’“€–ˆˆ';
            titn_5b  = ' - '+'’€‚ˆ’…‹œ ˆ”Œ€–ˆˆ  €‚€ˆ‰‰ ‘ˆ’“€–ˆˆ';
            titn_5c  = ' - '+'’ˆ €‚€ˆ‰‰ ‘ˆ’“€–ˆˆ';

            titn_7a  = ' - '+'‡€‚€’…‹œ›‰ ˆ„…Š‘';
            titn_7b  = ' - '+'…†ˆŒ Š„€ ’‚…’—ˆŠ€';
            titn_7c  = ' - '+'Š„ ’‚…’—ˆŠ€';

            titn_8a  = ' - '+'€‚ˆ‹€ ‹…’‚';
            titn_8b  = ' - '+'’ˆ ‹…’€';

            titn_9a  = ' - '+'Š‹ˆ—…‘’‚ ‘“„‚';
            titn_9b  = ' - '+'’ˆ ‚‡„“˜ƒ ‘“„€';
            titn_9c  = ' - '+'Š€’…ƒˆŸ ’““‹…–ˆˆ ‘‹…„€';

            titn_10a = ' - '+'“„‚€ˆ…';
            titn_10b = ' - '+'’ˆ ’‚…’—ˆŠ€';

            titn_13a = ' - '+'€’ ‚›‹…’€';
            titn_13b = ' - '+'‚…ŒŸ ‚›‹…’€';
            titn_13c = ' - '+'€‘’Ÿ™…… ‚…ŒŸ ‚›‹…’€';

            titn_14a = ' - '+'’—Š€ ‚‹…’€';
            titn_14b = ' - '+'‚…ŒŸ ‚‹…’€';
            titn_14c = ' - '+'€‡…˜…€Ÿ ‚›‘’€ ‹…’€';
            titn_14d = ' - '+'€‘’™€Ÿ ‚›‘’€ ‚‹…’€';
            titn_14e = ' - '+'“‘‹‚ˆŸ ‚›‘’› ‚‹…’€';

            titn_15a = ' - '+'Š…‰‘…‘Š€Ÿ ‘Š‘’œ';
            titn_15b = ' - '+'˜…‹';
            titn_15c = ' - '+'Œ€˜“’';

            titn_16a = ' - '+'€’ €‡€—…ˆŸ';
            titn_16b = ' - '+'€‘—…’… ˆ‘’…Š˜…… ‚…ŒŸ';
            titn_16c = ' - '+'1-›‰ ‡€€‘‰ €’';
            titn_16d = ' - '+'2-‰ ‡€€‘‰ €’';

            titn_17a = ' - '+'€’ ‘€„Šˆ';
            titn_17b = ' - '+'‚…ŒŸ ‘€„Šˆ';
            titn_17c = ' - '+'€‡‚€ˆ… €’€';

            titn_18  = ' - '+'—€Ÿ ˆ”Œ€–ˆŸ';
            titn_19  = ' - '+'„‹ˆ’…‹œ€Ÿ ˆ”Œ€–ˆŸ';
            titn_20  = ' - '+'‘™…ˆ… O ‚…†„…ˆˆ, O “ƒO‡… …‡O€‘O’ˆ';
            titn_21  = ' - '+'’…Ÿ €„ˆ‘‚Ÿ‡ˆ';
    {$ELSE}
      const titn_3   = '';

            titn_5a  = '';
            titn_5b  = '';
            titn_5c  = '';

            titn_7a  = '';
            titn_7b  = '';
            titn_7c  = '';

            titn_8a  = '';
            titn_8b  = '';

            titn_9a  = '';
            titn_9b  = '';
            titn_9c  = '';

            titn_10a = '';
            titn_10b = '';

            titn_13a = '';
            titn_13b = '';
            titn_13c = '';

            titn_14a = '';
            titn_14b = '';
            titn_14c = '';
            titn_14d = '';
            titn_14e = '';

            titn_15a = '';
            titn_15b = '';
            titn_15c = '';

            titn_16a = '';
            titn_16b = '';
            titn_16c = '';
            titn_16d = '';

            titn_17a = '';
            titn_17b = '';
            titn_17c = '';

            titn_18  = '';
            titn_19  = '';
            titn_20  = '';
            titn_21  = '';
    {$ENDIF}


     const  tit_3    = '3 -  MESSAGE TYPE'                           +titn_3   ;

            tit_5a   = '5a - PHASE OF EMERGENCY'                     +titn_5a  ;
            tit_5b   = '5b - ORIGINATOR OF MESSAGE'                  +titn_5b  ;
            tit_5c   = '5c - NATURE OF EMERGENCY'                    +titn_5c  ;


            tit_7a   = {$IFDEF SLOVAK}  '7a - identifik cia letu ' {$IFNDEF ATCA}+'("poradov ")'{$ENDIF} {$ENDIF}
                       {$IFDEF CZECH}   '7a - identifikace  letu ' {$IFNDEF ATCA}+'("po©adov ")'{$ENDIF} {$ENDIF}
                       {$IFDEF ENGLISH} '7a - AIRCRAFT IDENTIFICATION'+titn_7a {$ENDIF}
                       ;

            tit_7b   = {$IFDEF SLOVAK}  '7b - ¨pecifik cia SSR '       {$ENDIF}
                       {$IFDEF CZECH}   '7b - specifikace SSR '        {$ENDIF}
                       {$IFDEF ENGLISH} '7b - SSR RESPONDER CODE MODE'+titn_7b {$ENDIF}
                       ;

            tit_7c0  = {$IFDEF SLOVAK}  'k¢d SSR pred vstupom do riadenej oblasti' {$ENDIF}
                       {$IFDEF CZECH}   'k¢d SSR p©ed vstupem do ©¡zen‚ oblasti'   {$ENDIF}
                       {$IFDEF ENGLISH} 'SSR RESPONDER CODE BEFORE CONTROLED AREA' {$ENDIF}
                       ;

            tit_7c   = {$IFDEF SLOVAK}  '7b - k¢d SSR v riadenej oblasti' {$ENDIF}
                       {$IFDEF CZECH}   '7b - k¢d SSR v ©¡zen‚ oblasti'   {$ENDIF}
                       {$IFDEF ENGLISH} '7c - SSR RESPONDER CODE'+titn_7c {$ENDIF}
                       ;


            tit_8a   = {$IFDEF SLOVAK}  '8a - pravidl  letu'   {$ENDIF}
                       {$IFDEF CZECH}   '8a - pravidl  letu'   {$ENDIF}
                       {$IFDEF ENGLISH} '8a - FLIGHT RULES'+titn_8a {$ENDIF}
                       ;

            tit_8b   = {$IFDEF SLOVAK}  '8b - typ letu' {$ENDIF}
                       {$IFDEF CZECH}   '8b - typ letu' {$ENDIF}
                       {$IFDEF ENGLISH} '8b - TYPE OF FLIGHT'+titn_8b {$ENDIF}
                       ;


            tit_9a   = '9a - NUMBER OF AIRCRAFT'+titn_9a;
            tit_9b   = '9b - TYPE OF AIRCRAFT'  +titn_9b;
            tit_9c   = '9c - WAKE TURBULENCE CAT'+titn_9c;

            tit_9    = {$IFDEF SLOVAK}  '9 - k¢d typu lietadla' {$ENDIF}
                       {$IFDEF CZECH}   '9 - k¢d typu letadla'  {$ENDIF}
                       {$IFDEF ENGLISH} tit_9c  {$ENDIF}
                       ;


            tit_10a  = '10a - EQUIPMENT COM,NAV'+titn_10a ;
            tit_10b  = '10b - EQUIPMENT SSR'    +titn_10b ;



            tit_13a =  {$IFDEF SLOVAK}  '13a - k¢d letiska ¨tartu'  {$ENDIF}
                       {$IFDEF CZECH}   '13a - k¢d leti¨tˆ startu'  {$ENDIF}
                       {$IFDEF ENGLISH} '13a - DEPARTURE AERODROME'+titn_13a {$ENDIF}
                       ;

            tit_13b  = {$IFDEF SLOVAK}  '13b - pl novan˜ ‡as ¨tartu'   {$ENDIF}
                       {$IFDEF CZECH}   '13b - pl novan˜ ‡as ¨tartu'   {$ENDIF}
                       {$IFDEF ENGLISH} '13b - ESTIMATED DEPARTUTE TIME'+titn_13b {$ENDIF}
                       ;

            tit_13c  = {$IFDEF SLOVAK}  '13c - skuto‡n˜ ‡as ¨tartu'  {$ENDIF}
                       {$IFDEF CZECH}   '13c - skute‡n˜ ‡as ¨tartu'  {$ENDIF}
                       {$IFDEF ENGLISH} '13c - REAL DEPARTUTE TIME'+titn_13b {$ENDIF}
                       ;


            tit_16a  = {$IFDEF SLOVAK}  '16a - k¢d letiska prist tia' {$ENDIF}
                       {$IFDEF CZECH}   '16a - k¢d leti¨tˆ p©ist t¡'  {$ENDIF}
                       {$IFDEF ENGLISH} '16a - DESTINATION AERODROME'+titn_16a  {$ENDIF}
                       ;

            tit_16b  = {$IFDEF SLOVAK}  '16b - pl novan˜ ‡as prist tia' {$ENDIF}
                       {$IFDEF CZECH}   '16b - pl novan˜ ‡as p©ist t¡'  {$ENDIF}
                       {$IFDEF ENGLISH} '16b - TIME OF FLIGHT'+titn_16b {$ENDIF}
                       ;

            tit_16c  = '16c - 1st ALTERNATIVE AERODROME'+titn_16c ;
            tit_16d  = '16d - 2nd ALTERNATIVE AERODROME'+titn_16d ;

            tit_17a  = '17a - AERODROME OF ARRIVAL'                  +titn_17a ;
            tit_17b  = '17b - TIME OF ARRIVAL'                       +titn_17b ;
            tit_17c  = '17c - NAME OF AERODROME'                     +titn_17c ;


            tit_14a  = '14a - BOUNDARY POINT'                        +titn_14a ;
            tit_14b  = '14b - ESTIMATED TIME AT BOUNDARY POINT'      +titn_14b ;
            tit_14c  = {$IFDEF SLOVAK}  '14c - v˜¨ka na vstupe do riadenej oblasti'      {$ENDIF}
                       {$IFDEF CZECH}   '14c - v˜¨ka na vstupu do ©¡zen‚ oblasti'        {$ENDIF}
                       {$IFDEF ENGLISH} '14c - CLEARED LEVEL AT BOUNDARY POINT'+titn_14c {$ENDIF}
                       ;
            tit_14d  = '14d - CROSSING LEVEL AT BOUNDARY POINT'      +titn_14d ;
            tit_14e  = '14e - CROSSING CONDITION [A/B]'              +titn_14e ;


            tit_15a_=  {$IFDEF SLOVAK}  '15a - veli‡ina r˜chlosti' {$ENDIF} { 68 }
                       {$IFDEF CZECH}   '15a - veli‡ina r˜chlosti' {$ENDIF} { 68 }
                       {$IFDEF ENGLISH} '15a - CRUISING SPEED QUALIFIER' {$ENDIF}
                       ;

            tit_15a =  {$IFDEF SLOVAK}  '15a - pl novan  traŸov  r˜chlosŸ letu' {$ENDIF} { 68 }
                       {$IFDEF CZECH}   '15a - pl novan  traŸov  rychlost letu' {$ENDIF} { 68 }
                       {$IFDEF ENGLISH} '15a - CRUISING SPEED'+titn_15a  {$ENDIF}
                       ;

            tit_15b =  {$IFDEF SLOVAK}  '15b - pl novan  cestovn  hladina' {$ENDIF}
                       {$IFDEF CZECH}   '15b - pl novan  cestovn¡ hladina' {$ENDIF}
                       {$IFDEF ENGLISH} '15b - REQUESTED FLIGHT LEVEL'+titn_15b {$ENDIF}
                       ;

            tit_15c  = '15c - FLIGHT ROUTE'+titn_15c ;

            tit_18   = '18 - OTHER INFORMATION'                      +titn_18  ;
            tit_19   = '19 - SUPLEMENTARY INFORMATION'               +titn_19  ;
            tit_20   = '20 - ALERTING SEARCH AND RESCUE INFORMATION' +titn_20  ;
            tit_21   = '21 - RADIO FAILURE INFORMATION'              +titn_21  ;

            tit_FREG  = 'REGISTRATION NUMBER';
            tit_FDATE = 'DATE OF FLIGHT';


     const  i_3a  = 0;    a_3   = '3';       { indexy a pocty riadkov jednotlivych poli vo formulari }

                          a_5   = '5';
            i_5a  = 1;    a_5a  = '5a';
            i_5b  = 2;    a_5b  = '5b';
            i_5c  = 3;    a_5c  = '5c';

                          a_7   = '7';
            i_7a  = 4;    a_7a  = '7a';
            i_7b  = 5;    a_7b  = '7b';
            i_7c  = 6;    a_7c  = '7c';

                          a_8   = '8';
            i_8a  = 7;    a_8a  = '8a';
            i_8b  = 8;    a_8b  = '8b';

                          a_9   = '9';
            i_9a  = 9;    a_9a  = '9a';
            i_9b  = 10;   a_9b  = '9b';
            i_9c  = 11;   a_9c  = '9c';

                          a_10  = '10';
            i_10a = 12;   a_10a = '10a';
            i_10b = 13;   a_10b = '10b';

                          a_13  = '13';
            i_13a = 14;   a_13a = '13a';
            i_13b = 15;   a_13b = '13b';
            i_13c = 16;   a_13c = '13c';

                          a_14  = '14';
            i_14a = 17;   a_14a = '14a';
            i_14b = 18;   a_14b = '14b';
            i_14c = 19;   a_14c = '14c';
            i_14d = 20;   a_14d = '14d';
            i_14e = 21;   a_14e = '14e';

                          a_16  = '16';
            i_16a = 22;   a_16a = '16a';
            i_16b = 23;   a_16b = '16b';
            i_16c = 24;   a_16c = '16c';
            i_16d = 25;   a_16d = '16d';

                          a_17  = '17';
            i_17a = 26;   a_17a = '17a';
            i_17b = 27;   a_17b = '17b';
            i_17c = 28;   a_17c = '17c';

                          a_15  = '15';
            i_15a = 29;   a_15a = '15a';
            i_15b = 30;   a_15b = '15b';
            i_15c = 31;   a_15c = '15c'; {is_15c = max_FPL4_15_r;}

            i_18  = 37;   a_18  = '18';  {is_18  = max_FPL4_18_r;}

            i_19  = 41;   a_19  = '19';

            i_20  = 43;   a_20  = '20';

                          a_21  = '21';

                          a_22  = '22';


    const  max_arrayFPL4 = 16;
           arrayFPL4 : array [0..max_arrayFPL4-1] of string[2] =
                     (a_3,a_5,a_7,a_8,a_9,a_10,a_13,a_14,a_15,
                      a_16,a_17,a_18,a_19,a_20,a_21,a_22
                     );
