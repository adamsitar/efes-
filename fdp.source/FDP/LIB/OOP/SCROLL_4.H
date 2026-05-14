          { --------------------------------------------- }
          { TScrollAct                                    }
          { --------------------------------------------- }
    type    PScrollAct = ^TScrollAct;
            TScrollAct = object(TScrollWin)

              handler_type : TScrollAct_handler_type;
              handler      : pointer;
              handler_par  : pointer;  { adresa objektu dat alebo parametrov }

              data_filter  : pointer;  { ukazovatel na podmienku }
              filter       : pointer;  { TBfunc_p2: premenna, podmienky }

              item_size    : word;     { velkost polozky }
              new_item     : pointer;  { Tproc_p2 - alokacia polozky }
              disp_item    : pointer;  { Tproc_pl dealokacia, moze byt nil }

              print_plan   : pointer;
              send_plan    : pointer;

              constructor Init(_Owner     : PGroup;
                               _title     : string;

                               _arr_adr   : pointer;
                               _top_adr   : pointer;

                               _top_chg   : pointer;
                               _p_arr_chg : p_tick_counter;

                               _item_size    : word;
                               _new_item     : pointer;
                               _disp_item    : pointer;

                               _item_dx,_item_dy : int;
                               _dxi,_dyi, _medzera : int; _bg : byte;
                               _item_list : pointer;
                               _page : int;
                               _pos_en, _sb_sam, _sb_vzdy : bool;

                               _dxb,_dyb : int;
                               _init_buttons,_handle_buttons : pointer;
                               _handler_owner : PObject;

                               _handler_type : TScrollAct_handler_type;
                               _handler      : pointer;
                               _handler_par  : pointer;   { adresa objektu dat alebo parametrov }

                               _kbHot: char; _cmXXXX: word;
                               _hlpXXX : Pchar
                              );

              procedure   HandleEvent (var _Event: TEvent); virtual;
              function    call_user_handler_ (var _Event: TEvent; item: pointer): bool; virtual;
              function    call_user_handler  (var _Event: TEvent): bool; virtual;
              function    get_ind (i: int): int; virtual;
            end;
