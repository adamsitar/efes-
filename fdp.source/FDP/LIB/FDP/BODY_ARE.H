          { תתתתתתתתתתתתתתתתתתתתת }
          { PRIESTORY             }
          { תתתתתתתתתתתתתתתתתתתתת }

    type    PpArea  = ^TpArea;
            TpArea  = record
              kod   : string [kod_PRS];       { [k1] nazov priestoru }
              vys1  : word;                   { spodna vyska v [S]   }
              vys2  : word;                   { horna                }
              bodi,bodc : string[kod_OB]      { vstupny bod, bod cinnosti }
            end;


    const   max_AREA = MAX_ARRAY_SIZE div sizeof(TpArea);
    type    PpAREAs = ^TpAREAs;
            TpAREAs = array[0..max_AREA-1] of TpArea;
    const   maxAREAs = 300;


    type    PaArea = ^TaArea;
            TaArea = object(TsArray)
            end;


    const  { struktura zapisu priestorov v cfg subore
           }
            pos_AREA_kod   = 1;   { kod priestoru }
            pos_AREA_fl    = 2;   { vykovy rozsah }
            pos_AREA_bodi  = 3;
            pos_AREA_bodo  = 4;
            pos_AREA_flo   = 6;
            pos_AREA_xy    = 7;
            pos_AREA_bodc  = 8;

            odd_AREA_item  = ';';
