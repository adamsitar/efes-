    procedure str_toDBstr_  (s: string; var buff: TDB_riadok);
    procedure str_toDBstr   (s: string; var buff: TDB_riadok);
    function  DBstr_to_str_ (buff: TDB_riadok): string;
    function  DBstr_to_str  (buff: TDB_riadok): string;


    const  do_item__BREAK = 0;
           do_item__NEXT  = 1;
           do_item__SAVE  = 2;


    { -----------------------------------
       Spracovanie DB
      ----------------------------------
    }

    function  DB_head     (_FN: string; var head: TDB_head): bool;
    function  DB_poloziek (_FN: string; _riadkov: byte): long;

    function  DB_citaj             (_pos: long; _data: pointer; _FN: string; _riadkov: byte; _DATAdecode: pointer): bool;
    function  DB_citaj_kluc        (_pos: long; _FN: string; _riadkov: byte): string;
    function  DB_citaj_riadok_vety (_pos,_rdk: long; _FN: string; _riadkov: byte): string;

    function  DB_najdi_(_data: pointer; _FN: string; _riadkov: byte; _DATAdecode,_KEYcode: pointer;
                        _read: bool; _disp_data: pointer;
                        _p_another_key: PSFunc_s;
                        _title: string
                       ): long;
    function  DB_najdi (_data: pointer; _FN: string; _riadkov: byte; _DATAdecode,_KEYcode: pointer;
                        _read: bool; _disp_data: pointer;
                        _title: string
                       ): long;

    function  DB_najdi_nil  (_FN: string; _riadkov: byte): long;
    function  DB_najdi_data (_data: pointer; _FN: string; _riadkov: byte; _DATAdecode: pointer): long;

    procedure DB_zapis (_data: pointer; _pos: long; _FN: string; _riadkov: byte;
                        _DATAcode,_KEYcode, _DBchg: pointer; _attr: TDB_attr
                       );
    procedure DB_oprav (_data: pointer; _FN: string; _riadkov: byte;
                        _DATAcode,_KEYcode, _DBchg: pointer; _attr: TDB_attr
                       );
    function  DB_oprav_riadok (_oprava,_data: pointer; _kluc: TDB_riadok;
                               _FN: string; _riadkov: byte;
                               _DATAcode,_KEYcode: pointer;
                               _riadok: long; _code: pointer;
                               _attr: TDB_attr
                              ): bool;
    procedure DB_zrus  (_data: pointer; _FN: string; _riadkov: byte;
                        _DATAcode,_KEYcode, _DBchg: pointer
                       );

    function  DB_prehladaj({ a) funkcia pre spracovanie polozky DBF }
                                BFunc_p2    : pointer;    { func(param_item,data_item: pointer): bool }
                                param_item  : pointer;    { ukazovatel na hladanu polozku alebo filter }
                                data_item   : pointer;    { ukazovatel na polozku typu pola ako - funkcia buffera }
                                disp_item   : pointer;    { Tproc_p odalokuje nacitany buffer }
                           { b) parametre pre DBF  }
                                FN          : string;
                                riadkov     : byte;
                                DATAdecode  : pointer;
                                KEYcode     : pointer;
                                RWClose     : bool;       { urcuje, ci otvori a zatvori DB po kazdom pristupe }
                                title       : string
                          ): long;


    { -----------------------------------
       Nacitanie a spracovanie DB
      ----------------------------------
    }

    procedure new_DBarray (pole_adr     : pointer;  { adresa adresy pola <> nil }
                           var max_pole : int;      { maximum overdrive         }
                           size_item    : word      { velkost polozky           }
                          );

    procedure dispose_DBarray (pole_adr  : pointer;  { adresa adresy pola <> nil }
                               max_pole  : int;      { maximum overdrive         }
                               size_item : word      { velkost polozky           }
                              );

    procedure new_DBitems ({ a) parametre pre pole }
                                pole_adr    : pointer;  { adresa adresy pola <> nil           }
                                top_adr     : pointer;  { adresa ukazovatela na vrchol <> nil }
                                top_init    : int;      { -1, inak mozem spajat viacvero poli do seba }
                                max_pole    : word;

                                data_item   : pointer;  { ukazovatel na polozku typu pola ako - funkcia buffera }
                                disp_item   : pointer;  { Tproc_p odalokuje nacitany buffer }

                                data_filter : pointer;  { ukazovatel na podmienku           }
                                filter      : pointer;  { TBfunc_p2: premenna, podmienky    }

                                add_item    : pointer;  { Tproc_p3l alokacia, moze byt nil  }
                                vzostupne   : bool;     { smer nacitavania : true=vzostupne }

                           { b) parametre pre DBF  }
                                FN          : string;
                                riadkov     : byte;
                                DATAdecode  : pointer
                          );

    procedure dispose_DBitems (pole_adr  : pointer;  { adresa adresy pola <> nil }
                               top_adr   : pointer;  { pocet naplnenych poloziek-1 }
                               del_item  : pointer   { Tproc_pl dealokacia, moze byt nil }
                              );


    type  Tfilter_items_DB = TBFunc_p2 {(data_item,data_filter)} ;


    function  do_items_DB ({ a) funkcia pre spracovanie polozky DBF }
                                ByFunc_p2   : pointer;    { TByFunc_p2 <> nil   }
                                param       : pointer;
                           { b) parametre pre polozku }
                                data_item   : pointer;    { ukazovatel na polozku typu pola ako - funkcia buffera }
                                disp_item   : pointer;    { Tproc_p odalokuje nacitany buffer }
                           { c) parametre pre DBF  }
                                FN          : string;     { vrati nazov subora }
                                riadkov     : byte;
                                DATAcode    : pointer;
                                DATAdecode  : pointer;
                                KEYcode     : pointer;
                                DBchg       : pointer
                          ): bool;
