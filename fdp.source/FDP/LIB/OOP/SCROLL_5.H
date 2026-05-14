          { --------------------------------------------- }
          { TScrollInd                                    }
          { --------------------------------------------- }
    type    PScrollInd = ^TScrollInd;
            TScrollInd = object(TScrollAct)

              is_ind : bool;
              ind    : Pints;    { pole indexov  }
              size   : int;      { pocet = top+1 }

             {arr    : Pptrs;      pole premennych                   }
              comp   : pointer;  { @TBfunc_p2: bool; pre porovnanie  }

              constructor Init(_Owner        : PGroup;
                               _title        : string;

                               _arr_adr      : pointer;
                               _top_adr      : pointer;
                               _is_ind       : bool;

                               _top_chg      : pointer;
                               _p_arr_chg    : p_tick_counter;
                               _p_arr_init   : pbool;

                               _item_size    : word;
                               _new_item     : pointer;
                               _disp_item    : pointer;

                               _data_filter  : pointer;  { ukazovatel na podmienku }
                               _filter       : pointer;  { TBfunc_p2: premenna, podmienky }
                               _comp         : pointer;  { @TBfunc_p2: bool; pre porovnanie  }

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

                               _hlpXXX : Pchar
                              {_arr   : Pptrs;}
                              );

              destructor Done; virtual;
              procedure  Draw; virtual;

              function   is_changed: bool; virtual;
              procedure  new_data; virtual;
              procedure  disp_data; virtual;

              function   get_ind_in_list(i: int): int; virtual;
              function   get_ind(i: int): int; virtual;
            end;
