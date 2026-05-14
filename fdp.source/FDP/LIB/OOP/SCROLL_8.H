          { --------------------------------------------- }
          { TScrollDB2                                    }
          { --------------------------------------------- }

    type  PScrollDB2 = ^TScrollDB2;
          TScrollDB2 = object(TScrollAct)

            find_and_process_data, msg_not_processed : bool;
            finded_data : int;


          { a) pole }
            arr         : PDynamic2;
            data_item   : pointer;  { ukazovatel na polozku typu pola ako - funkcia buffera }

            vzostupne   : bool;
            sort_item   : pointer;  { Tproc_p2 - zotriedenie zoznamu   }
            comp_item   : pointer;  { alebo priama funkcia pre porovnanie }

          { b) DBF  }
            FN          : string;
            FNfunc      : pointer;
            FNfunc_p    : pointer;

            riadkov     : byte;
            DATAdecode  : pointer;

            p_filter    : pointer;   { zaznam s udajmi podmienok pre nacitanie }
            p_kluc      : PBFunc_p2; { porovnanie identifikacnych udajov }
            p_stav      : PBFunc_p2; { porovnanie inych udajov }
            p_datadb    : PBFunc_p2; { kontrola pripustnosti nacitania }
            p_dataext   : PBFunc_p2; { kontrola pripustnosti zaradenia }

            DBchg       : pointer;   { ukazovatel na logicku premennu zapisu do DBF }
            DBattr      : SearchRec;

            DBdone      : pointer;

            constructor Init(     _title     : string;     { hlavicka }
                                  _find_and_process_data,
                                  _msg_not_processed : bool;

                             { a) parametre pre pole }
                                  _items     : int;      { maximum overdrive }
                                  _item_size : word;     { velkost polozky }

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
                                  _handler_par  : pointer;  { adresa objektu dat alebo parametrov }

                             { b) parametre pre DBF  }
                                  _FN          : string;
                                  _FNfunc      : pointer;  { Fcia pre FN, @TSfunc_pi   }
                                  _FNfunc_p    : pointer;  { parameter p pre TSFunc_pi }
                                  _riadkov     : byte;
                                  _DATAdecode  : pointer;
                                  _DBchg       : pointer;  { ukazovatel na logicku premennu zapisu do DBF }

                             { c) parametre pre ScrollWin }
                                  _item_dx,_item_dy : int; { velkost polozky }
                                  _item_list    : pointer; { vypis polozky }

                                  _dxb,_dyb     : int;

                                  _init_buttons,_handle_buttons : pointer;
                                  _handler_owner : PObject;

                                  _hlpXXX       : Pchar
                             );

            function    data_found: bool; virtual;
            function    data_not_found: bool; virtual;
            function    is_to_be_run: bool; virtual;

            procedure   InitApp; virtual;
            procedure   DoneApp; virtual;

            procedure   scroll_new_data(prev_pos: int); virtual;
            procedure   new_data;  virtual;
            procedure   disp_data; virtual;
            function    is_changed: bool; virtual;


            function    call_user_handler(var _Event: TEvent): bool; virtual;
          end;
