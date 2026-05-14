    function  is_scroll_key(kbXXXX: char): bool;

    procedure check_hi(vypis_za_posl, vypis_posun: bool; var lo,hi, pos: int; top: int);

    function  set__scroll_pos(var lo,hi, pos: int; top, new_pos: int;
                              vypis_za_posl, vypis_posun: bool
                             ): bool;
    function  set_scroll_par (kbXXXX: char;
                              var lo,hi, pos: int; top: int;
                              var cez: int; { -1,0,1 }
                              pos_en,smer: bool;
                              vypis_za_posl,vypis_posun: bool
                             ): bool;

    procedure receive__scroll_mail(var lo,hi,top,pos: int);

    function  _set_page_size(_page,_top, _item_dy,_medzera,_dy: int): int;
    function  _get_scroller_size  (_item_dx: int; var _dxi: int): word;
    function  _get_scroller_height(_page: int; _item_dy: int; var _dyi: int; _medzera: int): word;


    function  scroll_DB (    _title        : string;   { hlavicka }

                             _find_and_process_data,
                             _msg_not_processed      : bool;

                        { a) parametre pre pole
                        }
                             _items        : int;      { maximum overdrive }
                             _item_size    : word;     { velkost polozky }

                             _new_item     : pointer;  { Tproc_p2 - alokacia polozky }
                             _format_item  : pointer;  { Tproc_p - formatovanie }
                             _disp_item    : pointer;  { Tproc_pl dealokacia, moze byt nil }
                             _eq_items     : pointer;

                             _p_filter     : pointer;     { zaznam s udajmi podmienok pre nacitanie }
                             _p_kluc       : PBFunc_p2;   { porovnanie identifikacnych udajov }
                             _p_stav       : PBFunc_p2;   { porovnanie inych udajov }
                             _p_datadb     : PBFunc_p2;   { kontrola pripustnosti nacitania }
                             _p_dataext    : PBFunc_p2;   { kontrola pripustnosti zaradenia }

                             _vzostupne    : bool;
                             _sort_item    : pointer;  { Tproc_p2 - zotriedenie zoznamu }
                             _comp_item    : pointer;  { alebo priama funkcia pre porovnanie }

                             _handler_type : TScrollAct_handler_type;
                             _handler      : pointer;  { @TBfunc_i  }
                             _handler_par  : pointer;   { adresa objektu dat alebo parametrov }

                        { b) parametre pre DBF
                        }
                             _FN           : string;
                             _FNfunc       : pointer;  { Fcia pre FN, @TSfunc_pi   }
                             _FNfunc_p     : pointer;  { parameter p pre TSFunc_pi }
                             _riadkov      : byte;
                             _DATAdecode   : pointer;
                             _DBchg        : pointer;  { ukazovatel na logicku premennu zapisu do DBF }

                        { c) parametre pre ScrollWin
                        }
                             _item_dx,_item_dy: int;  { velkost polozky }
                             _item_list    : pointer; { vypis polozky }

                             _dxb,_dyb : int;
                             _init_buttons,_handle_buttons : pointer;
                             _handler_owner : PObject;

                             _info,_hlpXXX : Pchar
                        ): bool;



    function  scroll_LST(_title: string;
                         page : int;
                         info,hlpXXX: Pchar;
                         _PATH       : string;
                         _get_item   : pointer;    { @TSfunc         }
                         _sort_item  : pointer;    { @Proc_pib       }
                         _sort_dir   : bool        { smer triedenia  }
                        ): string;


    function  scroll_DIR(_path,_name  : string;
                         _title,_mess : string;

                         _p_filter    : PBFunc_s;
                         _p_decode_fn : pointer;
                         _add_info  : bool;
                         _dx : int;

                         _comp_dir : pointer;  { @TBfunc_p2: bool; pre porovnanie }
                         _comp_by  : byte;     { 0 - dir, 1 - items }
                         _handler  : pointer;  { TIFunc_s }

                         _hlpXXX : Pchar
                        ): string;

