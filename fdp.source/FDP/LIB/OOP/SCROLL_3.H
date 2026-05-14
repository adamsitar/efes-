          { --------------------------------------------- }
          { TScrollWin                                    }
          { --------------------------------------------- }
    type    PScrollWin = ^TScrollWin;
            TScrollWin = object(TScroller)

              win : PWindow;

              dxb,dyb         : int;

              init_buttons    : pointer;
              handler_buttons : pointer;
              handler_owner   : PObject;
              handler_data    : pointer;   { doplnujuce udaje pouzite pri handle_buttons }


              procedure   init_win(_title: string; x,y, dx,dy: int;
                                   _kbHot: char; _cmXXXX: word
                                  ); virtual;

              constructor Init(_Owner: PGroup;
                               _title: string;

                               _arr_adr : pointer;
                               _top_adr : pointer;
                               _top_chg : pointer;
                               _p_arr_chg : p_tick_counter;

                                x,y, _item_dx,_item_dy : int;
                               _dxi,_dyi, _medzera : int; _bg : byte;
                               _item_list : pointer;
                               _page : int;
                               _pos_en,
                               _sb_sam, _sb_vzdy : bool;
                               _dxb,_dyb : int;
                               _init_buttons,
                               _handle_buttons : pointer;       { TBFunc_vEp3 }
                               _handler_owner  : PObject;       { parameter vlastnickeho objektu }

                               _kbHot : char;
                               _cmXXXX: word
                              );


              procedure    initialize_buttons; virtual;

              procedure    Draw;  virtual;
              procedure    Image; virtual;

              procedure    Run(var _Event: TEvent); virtual;

              procedure    handle_buttons (var _Event: TEvent); virtual;
              procedure    HandleEvent (var _Event: TEvent); virtual;

              procedure    Centre; virtual;
              procedure    reinit_(x,y, _page: int);

            end;
