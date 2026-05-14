(*-------------------------------------------------------------------*)
(* Sets   1.0                                                        *)
(* 1993                                                              *)
(*-------------------------------------------------------------------*)
{$I comp.h}

unit Sets;


interface


     uses  TypeDef,
           keyb;


    { nedoplnat ani nevypustat nicego bez dokladnej analyzy,
      bo daktore kontroly nebudu chodzic !
    }
     const setNil   : TCharSet = [];
           set_     : TCharSet = [' '];
           setHex   : TCharSet = ['$','a'..'f','A'..'F','0'..'9',' '];
           setPism  : TCharSet = ['a'..'z','A'..'Z'];
           setPism_ : TCharSet = ['a'..'z','A'..'Z',' '];
           setDig   : TCharSet = ['0'..'9'];
           setCisl  : TCharSet = ['0'..'9',' ']; { kym vyberiem ' ', najprv pohladat vsetky odkazy }
           setCisl_ : TCharSet = ['0'..'9',' '];
           setABC   : TCharSet = ['a'..'z','A'..'Z',' ','0'..'9','.'];
           setABC_  : TCharSet = ['a'..'z','A'..'Z',' ','0'..'9','.',',','/'];
           setABCcs : TCharSet = ['0'..'9',
                                  'a'..'z','A'..'Z',
                                  '†','è','á','Ä','É','Ö','Ç','ê','à','â',
                                  '°','ã','ç','ä','å','ú','§','•','¢','ï',
                                  'ì','ß','™','´','©','û','®','õ','ü','Ü',
                                  '£','ó','ñ','¶','ò','ù','ë','í'];
           setABCcs_: TCharSet = ['0'..'9',
                                  'a'..'z','A'..'Z',
                                  '†','è','á','Ä','É','Ö','Ç','ê','à','â',
                                  '°','ã','ç','ä','å','ú','§','•','¢','ï',
                                  'ì','ß','™','´','©','û','®','õ','ü','Ü',
                                  '£','ó','ñ','¶','ò','ù','ë','í',
                                  '!','@','#','$','%','^','&','*','(',')',
                                  '-','_','+','=','\','|','{','}','[',']',
                                  ':',';','"','''','<','>',',','.','?','!',
                                  '/',
                                  ' '];

           setASCII : TCharSet = ['0'..#255];
           setFN    : TCharSet = [' '..#255];


           setCas   : TCharSet = [':','˙'];
           setDatum : TCharSet = ['.','˙'];
           setWAN   : TCharSet = ['a'..'z','A'..'Z',' ','0'..'9',','];

           setNL    = [kbLF,kbCR];
           setNL_   = [kbLF_,kbCR_,kbCRLF];

           setSCROLL : TCharSet = [kbUp,kbDown, kbPgUp,kbPgDn, kbHome,kbCtrlPgUp,kbEnd,kbCtrlPgDn, kbCtrlHome,kbCtrlEnd];
           setNOKEY  : TCharSet = [#0..#31,'∞'..'ﬂ','˙'..#255];


implementation
end.