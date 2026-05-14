    type  PScrollApp_FDP = ^TScrollApp_FDP;
          TScrollApp_FDP = object(TScrollApp)

            p_plan  : PPLAN;
            lst_chg : tick_counter;

            constructor Init
                   (_Owner    : PGroup;
                    _title    : string;

                    _p_plan   : PPLAN;

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

            function   is_changed: bool; virtual;
          end;
