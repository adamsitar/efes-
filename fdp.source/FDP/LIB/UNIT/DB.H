         { ------------------------------------
           DB
           ------------------------------------
           Sekvencna DB s klucom pre rychlejsie
           vyhladanie polozky, moze sa doprogramovat
           indexovy subor name.ext -> iname.ext...
         }

    const  DB_znakov  = $100;
           DB_riadok  = DB_znakov-4;
           DB_riadkov = 100;

           ZAC_KEY    = #2;
           KON_KEY    = #3;
           ODD_KEY    = #4;

           DB_NIL     = 'NIL';

    const  __INFO_DB  : bool = true;   { povolenie zobrazovat okno info }


         { ------------------------------------
           Hlavicka DB
           ------------------------------------
         }

    const  DB_copyright = 'DB FDP, Copyright by ALES';

    const  DB0   = 0;
           DBbin = 1;
           DBtxt = 2;

    type   TDB_attr = word;

           PDB_head = ^TDB_head;
           TDB_head = record
             cprght   : array[0..length(DB_copyright)-1] of byte;
             dlz_head : word; { velkost hlavicky }
             znakov   : word;
             riadkov  : byte;
             attr     : TDB_attr;
             reserved : array[0..DB_znakov
                                 - (  length(DB_copyright)
                                    + sizeof(word)
                                    + sizeof(word)
                                    + sizeof(byte)
                                    + sizeof(TDB_attr)
                                   )
                                 -1] of byte
           end;


         { ------------------------------------
           Riadok DB
           ------------------------------------
         }

    type   PDB_riadok = ^TDB_riadok;
           TDB_riadok = string; {array[0..sizeof(string)] of char;} { posledne 2 znaky z 256 sa prepisu ma 0xD a 0xA }

           PDB_buff   = ^TDB_buff;
           TDB_buff   = array[0..DB_riadkov-1] of TDB_riadok;

           TDBcode_proc   = procedure(p: pointer; buff: PDB_buff; head: PDB_head);
           TDBdecode_proc = procedure(buff: PDB_buff; p: pointer; head: PDB_head);
           TDBkey_func    = function (key_to_find, key_item: pointer): bool;


         { ------------------------------------
           Objekt TDB
           ------------------------------------
         }

    type   PDB = ^TDB;
           TDB = object
             {protected}
             FN         : string;
             DBf        : file;
             {Attr      : word;}

             head       : TDB_head;

             FNExist    : bool;     { existuje subor }
             RWClose    : bool;     { urcuje, ci otvori a zatvori DB po kazdom pristupe }

             buff_size  : long;     { velkost buffera }
             buff       : PDB_buff;

             DATAcode   : pointer;  { @TDBcode_proc   }
             DATAdecode : pointer;  { @TDBdecode_proc }

             KEYcode    : pointer;  { @TDBcode_proc   }
            {KEYdecode  : pointer;    @TDBdecode_proc
             isKEY      : pointer;    @TDBkey_func -> <> nil kontroluje }
             p_another_key : PSFunc_s;

             DBchg      : pointer;  { @bool           }
             semaphor   : bool;

             public
             constructor Init(_FN : string; _RWClose : bool;

                              _riadkov    : byte;

                              _DATAcode   : pointer; { @TDBcode_proc   }
                              _DATAdecode : pointer; { @TDBdecode_proc }
                              _KEYcode    : pointer; { @TDBcode_proc   }
                             {_KEYdecode  : pointer;   @TDBdecode_proc
                              _isKEY      : pointer;   @TDBkey_func    }

                              _DBchg  : pointer;  { @bool }
                              _attr   : TDB_attr
                             );
             destructor  Done;

             function    poloziek: long;

             function    citaj (_pos : long; _data: pointer): bool;
             function    najdi (_data: pointer; _read: bool; _disp_data: pointer): long;

             function    najdi_nil: long;
             function    najdi_data: long;

             procedure   zapis (_data: pointer; _pos: long; _ins: bool);
             procedure   oprav (_data: pointer);
             procedure   zrus  (_data: pointer);
             function    oprav_riadok (_kluc: TDB_riadok; _data: pointer; _riadok: long; _code: pointer): bool;


             {protected}
             procedure   koduj_vetu  (p: pointer); { p :  -> data   }
             procedure   dekoduj_vetu(p: pointer); { data -> DBbuff }
             function    vyhladaj_kluc (_kluc: TDB_riadok): long;
             function    vyhladaj_data (_data: pointer): long;

             function    citaj_kluc (_pos: long): string;
             function    citaj_vetu (_pos: long): bool;
             procedure   zapis_vetu (_pos: long; _ins: bool); { ins zatial nefunguje }
           end;
