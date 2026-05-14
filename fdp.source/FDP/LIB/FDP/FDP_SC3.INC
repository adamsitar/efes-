 constructor TScrollApp_FDP.Init
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

       begin
         p_plan:= _p_plan;
         lst_chg:= 0;
         inherited Init(_Owner,_title,
                        p_plan^.ap,@p_plan^.top,true,

                        nil,nil,nil,
                        0,nil,nil,

                        _data_filter,_filter,_comp,
                        x,y, _item_dx,_item_dy,
                        _dxi,_dyi, _medzera, _bg,
                        _item_list, _page, _pos_en, _sb_sam, _sb_vzdy,

                        _handler_type, _handler, _handler_par,

                        _p_visible, _cmXXXX, _hlpXXX
                       );

         p_arr_init  := @p_plan^.s_loadDB;
         p_arr_check := @p_plan^.s_pocitam;
       end;


 function TScrollApp_FDP.is_changed: bool;
    var   res: bool;
    begin
      is_changed:= false;
      if APP_GUI_INIT then Exit;
      if (p_plan=nil) or (p_plan^.s_pocitam) or (p_plan^.s_loadDB) or is_initialized then Exit;
      res:=  (arr_chg <> p_plan^.arr_chg);
      arr_chg:= p_plan^.arr_chg;
      is_changed:= res
    end;

