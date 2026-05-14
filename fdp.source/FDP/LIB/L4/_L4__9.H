     const  kod_9a   = 2;
            kod_9b   = 4;
            {$IFDEF LZ}
             kod_9bM = 2;
            {$ENDIF}
            kod_9c   = 1;

            kod_9    = kod_9a+kod_9b+1+kod_9c;  { 02SU22/M }


     const { Typy lietadiel "9b" su v cfg. subore _9b.lst
           }
            INY_TYP = 'ZZZZ'; {  .... viac typov alebo bez pridelenia oznacenia }


           { Turbulencia v uplave "9c"
           }
     const  trbl_L  = 'L';
            trbl_M  = 'M';
            trbl_H  = 'H';


     const  set_9c   : TCharSet  = [trbl_L,trbl_M,trbl_H];


          { -DC3/M
            -B707/M
            -2FK27/M
            -3ZZZZ/L
          }


     const  _AFIL_9 : bool = true;  { spinac automaticke doplnenie chybajucich hodnot }

     function  code_l4_9_    (_9a,_9b,_9c: string): string;
     function  code_l4_9     (_9: string; _L4: bool): string;
     function  decode_l4_9   (_9 : string; var _9a,_9b,_9c : string): bool;

