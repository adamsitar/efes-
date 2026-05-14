          { Zbytocne tu mam dvakrat skoro ten isty objekt,
            ale teraz to uz name zmysel prerabat,
            lepsie je to vyriesit cez
                print_plan   : pointer;
                send_plan    : pointer

          }


    type  PScrollInd_FDP = ^TScrollInd_FDP;
          TScrollInd_FDP = object(TScrollInd)

            print : pointer;
            send  : pointer;

            constructor Init(_title : string;

                             _arr_adr  : pointer;
                             _top_adr  : pointer;

                             _top_chg    : pointer;
                             _p_arr_chg  : p_tick_counter; { ukazovatel na premennu o zmene dat <>0 or <>last_tick_counter }
                             _p_arr_init : pbool;

                             _item_size    : word;
                             _new_item     : pointer;
                             _disp_item    : pointer;

                             _data_filter  : pointer;  { ukazovatel na podmienku }
                             _filter       : pointer;  { TBfunc_p2: premenna, podmienky }
                             _comp         : pointer;  { @TBfunc_p2: bool; pre porovnanie  }

                             _handler_type : TScrollAct_handler_type;
                             _handler      : pointer;
                             _handler_par  : pointer;   { adresa objektu dat alebo parametrov }

                             _print        : pointer;

                             _item_dx,_item_dy : int;
                             _item_list : pointer;
                             _page : int;

                             _hlpXXX : Pchar
                            {_arr   : Pptrs;}
                            );

            procedure  HandleEvent(var _Event: TEvent); virtual;
          end;


    type  pPScrollDB_FDP = ^PScrollDB_FDP;
          PScrollDB_FDP  = ^TScrollDB_FDP;
          TScrollDB_FDP  = object(TScrollDB2)

            print : pointer;
            send  : pointer;

            find_cnl_data : bool;

            constructor Init(     _title        : string;   { hlavicka }

                                  _find_and_process_data,
                                  _find_cnl_data,
                                  _msg_not_processed      : bool;

                             { a) parametre pre pole }
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

                                  _init_buttons   : pointer;
                                  _handle_buttons : pointer;
                                  _handler_data   : pointer;

                                  _print        : pointer;
                                  _send         : pointer;

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

                                  _hlpXXX       : Pchar
                             );


            function   data_not_found: bool; virtual;
            function   ma_sa_prekreslit: bool; virtual;
            procedure  data_update (item: pointer);

            procedure  HandleEvent(var _Event: TEvent); virtual;

            (*{$IFDEF DEBUG}
              function  call_user_handler_(var _Event: TEvent; item: pointer): bool; virtual;
              function  call_user_handler(var _Event: TEvent): bool; virtual;
            {$ENDIF}*)
          end;


