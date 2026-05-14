constructor TScrollInd_FDP.Init(_title        : string;

                                _arr_adr      : pointer;
                                _top_adr      : pointer;

                                _top_chg      : pointer;
                                _p_arr_chg    : p_tick_counter; { @premenna o zmene dat <>0 or <>last_tick_counter }
                                _p_arr_init   : pbool;

                                _item_size    : word;
                                _new_item     : pointer;
                                _disp_item    : pointer;

                                _data_filter  : pointer;  { ukazovatel na podmienku }
                                _filter       : pointer;  { TBfunc_p2: premenna, podmienky }
                                _comp         : pointer;  { @TBfunc_p2: bool; pre porovnanie }

                                _handler_type : TScrollAct_handler_type;
                                _handler      : pointer;
                                _handler_par  : pointer;  { adresa objektu dat alebo parametrov }

                                _print        : pointer;

                                _item_dx,_item_dy : int;
                                _item_list : pointer;
                                _page : int;

                                _hlpXXX : Pchar
                               {_arr   : Pptrs;}
                               );
      var   _init_buttons: pointer;
            _dy : int;
            _medzera,_dxi,_dyi,_bg: int;
      begin
        if _hlpXXX=nil then _hlpXXX:= hlp_zoznam;
        {if (_print<>nil) and (_send<>nil) then _init_buttons:= @init_sc_butt2
        else} if (_print<>nil) then _init_buttons:= @init_sc_butt1
             else _init_buttons:= nil;
        if _init_buttons<>nil then _dy:= btHEIGHT+10 else _dy:= 0;

        if _item_dy>10 then begin _medzera:= __medzera; _dxi:= __dxi; _dyi:= __dyi; _bg:= __bg; end
        else begin _medzera:= 2; _dxi:= 2; _dyi:= 4; _bg:= 0; end;
        inherited   Init(nil,_title,
                         _arr_adr,_top_adr,true,
                         _top_chg,_p_arr_chg,_p_arr_init,

                         _item_size,_new_item,_disp_item,
                         _data_filter,_filter,_comp,

                         _item_dx,_item_dy,
                         _dxi,_dyi,_medzera,_bg,
                         _item_list, _page,
                         true,true,true,

                         0,_dy, _init_buttons,nil{_handle_buttons},nil{_handler_owner},
                         _handler_type,_handler,_handler_par,

                         _hlpXXX
                        );

        print:= _print
      end;


procedure TScrollInd_FDP.HandleEvent(var _Event: TEvent);
    var   i: int;
    begin
      inherited HandleEvent(_Event);
      if isCommand(_Event,cmPrint) then
          begin
            if print<>nil then
               if print_head(PortNo, strpas(win^.bttitle^.title)) then
                  begin
                    i:= 0;
                    while (i<=int(p_top_adr^)) and TBFunc_p(print)(arr_adr^[i]) do
                      begin
                        CheckProcesses;
                        inc(i)
                      end
                  end;
            ClearEvent(_Event)
          end
    end;
