
          { ------------------------------------------- }
          { Pole v EMS :                                }
          { ------------                                }
          { Pole je statickej velkosti                  }
          {                                             }
          {                                             }
          {                                             }
          { ------------------------------------------- }

     type  PArray = ^TArray;
           TArray = object(TDynamic2)
           end;


     type  PsArray = ^TSArray;
           TsArray = object

             private
             ear : TstreamArray;
             sar : PStatic;

             public
             is_eq   : bool;          { povolenie pre viacnasobne ulozenie premennej }
             is_chg  : bool;          { zmena stavu, prepisana alebo nova polozka }
             arr_chg : tick_counter;  { stav citaca pri zmene }


             constructor Init(_max_items,_item_size: word; _is_eq: bool);
             destructor  Done; virtual;

             procedure   set_chg;

             procedure   add  (var p);
             procedure   del  (ind: int);
             procedure   read (ind: long; var p);
             procedure   write (ind: long; var p);

             function    pocet: int;
           end;
