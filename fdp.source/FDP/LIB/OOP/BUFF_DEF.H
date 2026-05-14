          { ------------------------------------------- }
          { Kruhovy buffer:                             }
          { ---------------                             }
          { Nie je navrhnuty na pouzitie struktur       }
          { s alokovanymi polozkami, nekosr upravit     }
          { ------------------------------------------- }

     type  PBuffer  = ^TBuffer;
           TBuffer  = object(TDynamic)

             alloc_en  : bool;  { povolene alokacia pamate }
             s_save    : bool;  { zapisovane data !        }
             s_read    : bool;  { nacitavane data !        }
             pretiekol : bool;  { buffer pretiekol !       }

             zac,kon   : word;  { musi byt ten isty typ ako "items" !
                                  inak sa pri pouziti v intr prepise
                                  pamat...
                                }

             constructor Init(_items,_data_size: word; _alloc_en: bool);
             destructor  Done; virtual;

             {protected}
             function    Add(p: pointer): int; virtual;
             procedure   Del(ind: int); virtual;

             procedure   set_chg; virtual;

             public
             function    is : bool;
             procedure   save  (p: pointer);
             procedure   _read (p: pointer); virtual;
             function    read  (p: pointer): bool;
             function    readv (var p: pointer): bool;
           end;


          { ------------------------------------------- }
          { Uspornejsi bfr, ale pole nesmie obsahovat   }
          { znak "0", ani byt pouzite v intr fcii !     }
          { ------------------------------------------- }

     type  PBuffer0  = ^TBuffer0;
           TBuffer0 = object(TBuffer)

             constructor  Init(_items: word);

             function     Add      (p: pointer): int;  virtual;
             function     Add0     (p: pointer; size: word): int;
             function     NewData  (p: pointer): pointer; virtual;
             procedure    DispData (var p: pointer); virtual;

             procedure    _read    (p: pointer); virtual;
           end;
