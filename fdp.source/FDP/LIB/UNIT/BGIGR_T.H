
    type    Pcentr = ^Tcentr;
            Tcentr = record      { aby si form zapamatal polohu, i ked ho odalokujem, }
              x,y, m : int;      { ma smernik na posledne umiestnenie na obrazovke;   }
            end;


          { uchovavanie obsahu obrazovky }

    type    PWin = ^TWin;
            TWin = record
               x0,y0, x1,y1: int;  { suradnice okna               }
               {$IFDEF BGI}
                 size : long;      { velkost buffera s adresou p alebo subora }
                 name : PChar;     { subor pre data, ak je heap maly, inak='' }
                 p    : pointer;   { pre ulozenie obrazovky                   }
               {$ENDIF}
               {$IFDEF SPEA}
                 p    : int;       { pre ulozenie obrazovky                   }
               {$ENDIF}
               next : PWin;
            end;


    type    PWinReg = ^TWinReg;
            TWinReg = record
               prev : PWinReg;     { adresa predchadzajuceho zaznamu }
               win  : PWin;

               tmp  : PWinReg;     { pre ucely obnovy podkladu }

               desc : int;         { cislo okna }
            end;

            { Ak tu pridam dalsiu polozku, musim to osetrit
              i v obnov_okno,... !
            }
