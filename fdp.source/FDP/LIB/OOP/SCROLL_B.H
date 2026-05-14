    const  dy_ScrollApp = btHEIGHT+13;
           bkScrollApp  = clGR0;
           itScrollApp  = clBUTTON_COLOR;


    type   PScrollApp = ^TScrollApp;
           TScrollApp = object(TScrollInd)

             btTitle   : PButton;
             _win_     : TView;   { suradnice podkladu }
             p_visible : pointer;

             procedure   init_win(_title: string; x,y, dx,dy: int;
                                  _kbHot: char; _cmXXXX: word
                                 ); virtual;
             constructor Init(_Owner     : PGroup;
                              _title     : string;

                              _arr_adr   : pointer;
                              _top_adr   : pointer;
                              _is_ind    : bool;

                              _top_chg    : pointer;
                              _p_arr_chg  : p_tick_counter;
                              _p_arr_init : pbool;

                              _item_size    : word;
                              _new_item     : pointer;
                              _disp_item    : pointer;

                              _data_filter  : pointer;  { ukazovatel na podmienku           }
                              _filter       : pointer;  { TBfunc_p2: premenna, podmienky    }
                              _comp         : pointer;  { @TBfunc_p2: bool; pre porovnanie  }

                              x,y, _item_dx,_item_dy : int;
                              _dxi,_dyi, _medzera : int; _bg : byte;
                              _item_list : pointer;
                              _page : int;
                              _pos_en, _sb_sam, _sb_vzdy : bool;

                              _handler_type : TScrollAct_handler_type;
                              _handler      : pointer;
                              _handler_par  : pointer;

                              _p_visible : pointer;
                              _cmXXXX : word;
                              _hlpXXX : Pchar
                             );
             destructor  Done; virtual;
             procedure   Draw; virtual;

             procedure   reinit_(x,y, _page: int);
             procedure   hide; virtual;

             procedure   ActiveOn; virtual;
             procedure   ActiveOff; virtual;
           end;

