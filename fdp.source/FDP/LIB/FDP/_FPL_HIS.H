          { --------------------------- }
          { Dekodovana trat letu        }
          { --------------------------- }


    const   max_his = 3;              { HISTORIA LETU ...   }
                                      { ------------------- }
    type    This_xy = record
              x,y: real
            end;
            Phistory = ^Thistory;
            Thistory = array[0..max_his-1] of This_xy;


    type    Psur = ^Tsur;             { SURADNICE CIELA ... }
            Tsur = record             { ------------------- }
              x ,y  : real;           { suradnice v danom case absTime, vypocet po jednej OBNOVENIE_CIELOV }

              xl,yl : real;           { posledne vypocitane a zobrazene suradnice     }
              xh,yh : real;           { preposledne suradnice pre zobrazenie historie }
              his   : Thistory;

             {$IFDEF MAPY}
              is      : bool;
              Lp      : byte;         { premenna urcujuca poziciu labelu      }
              Lx,Ly   : int;          { posledne suradnice                    }
              xl_,yl_ : int           { suradnice pre vyhladanie ciela myskou }
             {$ENDIF}
            end;


