     function   add_item(item, arr: pointer; var top: int; items, item_size: word): int;
     procedure  del_item(arr: pointer; ind: int; var top: int; item_size: word);


          { ------------------------------------------ }
          { Staticke pole:                             }
          { ---------------                            }
          { TArray = array[0..items-1] of item         }
          { ------------------------------------------ }

     type  PStatic = ^TStatic;
           TStatic = object

             arr : pointer;

             item_size   : word;
             items       : word;          { musi ostat word }
             top         : int;

             is_eq       : bool;          { kontrolovat na zhodu }
             p_eq_items  : pointer;
             format_item : pointer;

             is_chg      : bool;          { zmena stavu, prepisana alebo nova polozka }
             arr_chg     : tick_counter;  { stav citaca pri zmene }


             constructor Init(_items,_item_size: word);
             destructor  Done; virtual;

             function    Add  (p: pointer): int; virtual;
             function    Add2 (p: pointer): int; virtual;
             procedure   Del  (ind: int); virtual;

             procedure   Get (ind: long; var p); virtual;
             procedure   Put (ind: long; var p); virtual;

             function    eq_data(pi, p: pointer): bool; virtual;
             procedure   format_data(p: pointer); virtual;

             procedure   set_chg; virtual;
             function    is_data: bool;

             function    get_items: int;
           end;


          { ------------------------------------------- }
          { Dynamicke pole:                             }
          { ---------------                             }
          { TPtrArray = array[0..items-1] of pointer    }
          { Ak item obsahuje dalsie pointre (PCHAR,...) }
          { potom sa musia predefinovat NewData a       }
          { DispData !!!                                }
          { ------------------------------------------- }

     type  PDynamic = ^TDynamic;
           TDynamic = object(TStatic)

             { Zdedene:
               arr   = Dynamic[0]
               items = max. pocet poloziek pola
               item_size = SizeOf(pointer)
               top   = aktualny --//--
             }
             {private}
             ap         : Pptrs; { smernik na pole smernikov na data, alokuju sa za s existenciou dat }
             data_size  : word;  { velkost dat na ktore ukazuje arr^[i]  }


             { Navrhovane :
               max_avail  : long;  min velkost pamate, pod ktoru uz nejde
             }

             public

             constructor Init (_items,_data_size: word{; _max_avail: long});
             destructor  Done; virtual;

             function    NewData  (p: pointer): pointer; virtual;
             procedure   DispData (var p: pointer); virtual;

             function    find_data (p: pointer): int; virtual;
             procedure   format_data_variables (p: pointer); virtual;

             function    Add (p: pointer): int; virtual;
             function    Eq  (ind: int; p: pointer): bool; virtual;
             procedure   Del (ind: int); virtual;

             procedure   DelAll;
           end;

