          { תתתתתתתתתתתתתתתתתתתתת }
          { BOD TRATE: NDB,OB     }
          { תתתתתתתתתתתתתתתתתתתתת }

    type    {TBOD_  = record
              kod  : string[KOD_OB];
              kod_ : string[KOD_OB]
            end;}

            TIOBOD = record
              kod  : string[KOD_OB];
              io   : pchar;
              pozn : pchar;
            end;


    const   max_BODy = MAX_ARRAY_SIZE div sizeof(TsBod);

    type    PBODy    = ^TsBody;
            TsBody    = array[0..max_BODy-1] of TsBod;

            {PBODy_   = ^TsBody_;
            TsBody_   = array[0..max_BODy-1] of TsBod_;}

            PIOBODy  = ^TIOBODy;
            TIOBODy  = array[0..max_BODy-1] of TIOBOD;


    type    PaBody = ^TaBody;
            TaBody = object(TsArray)
              { Objekt sa inicializuje do hornej pamate,
                preto to nie je obycajna struktura
              }
              function _OBind(kod: string; var Bi: TsBod): int;
            end;


