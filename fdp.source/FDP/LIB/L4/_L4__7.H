    const  kod_7a   = {$IFDEF GOST} 8 {$ELSE} 7 {$ENDIF};   { maximalny rozsah identifikacie }
           kod_7b   = 1;
           kod_7c_icao = 4;
           kod_7c   = {$IFDEF GOST} 5 {$ELSE} kod_7c_icao {$ENDIF};

           kod_7    = kod_7a+1+kod_7c+1;


    const  mode_A   = 'A';

    const  set_7a   : TCharSet  = [mode_A];
           set_7b   : TCharSet  = ['0'..{$IFDEF GOST}'9'{$ELSE}'7'{$ENDIF},' '];
           set_7c   : TCharSet  = ['0'..{$IFDEF GOST}'9'{$ELSE}'7'{$ENDIF},' '];

          { -BAW902
            -X123/A2311
          }


    function   code_l4_7    (_7a,_7b,_7c: string): string;
    function   code_l4_7c   (_7c: string): string;

    function   decode_l4_7a (_7: string): string;
    procedure  decode_l4_7  (_7: string; var _7a,_7b,_7c: string);

