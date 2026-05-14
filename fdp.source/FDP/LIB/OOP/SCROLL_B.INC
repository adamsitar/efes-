const  dx_Ti = 6;
       dy_Ti = 8;

procedure TScrollApp.init_win(_title: string; x,y, dx,dy: int;
                              _kbHot : char; _cmXXXX: word
                             );
    begin
      win:= nil
    end;

constructor TScrollApp.Init(_Owner        : PGroup;
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

                            _p_visible    : pointer;
                            _cmXXXX       : word;
                            _hlpXXX       : Pchar
                           );
      var   dx: int;
      begin
        inherited Init(_Owner, _title,

                       _arr_adr,_top_adr,
                       _is_ind,
                       _top_chg,_p_arr_chg,
                       _p_arr_init,

                       _item_size,_new_item,_disp_item,
                       _data_filter,_filter,_comp,

                       _item_dx,_item_dy,
                       _dxi,_dyi, _medzera, _bg,
                       _item_list,
                       {_dxi,_dyi, _medzera, _bg,
                       _pos_en, _sb_sam, _sb_vzdy,}
                       _page,
                       _pos_en, _sb_sam, _sb_vzdy,

                       0,0, nil,nil,nil,
                       _handler_type, _handler, _handler_par,

                       _hlpXXX
                      );

        ObjectType:= obj_view_active;
        prepis_en:= true;
        in_frame:= false;
        p_visible:= _p_visible;
        cmXXXX:= _cmXXXX;

        dx:= 4+_item_dx+dxi*2+2+SCROLL_BAR__SIRKA+4;
        _win_.Init(nil, x,y,dx,y1-y0+dy_ScrollApp+4);
        btTitle:= New(PButton, Init(@Self, x+dx_Ti,y+dy_Ti,dx-dx_Ti shl 1,15,
                      kbNoKey, _cmXXXX, _title, 0, clKey,clItem)
                     );
        btTitle^.btSize:= btSmall;
        btTitle^.kbHot:= GetAltCode(btTitle^.kbHot);
        btTitle^.kbAltHot:= GetAltCode(btTitle^.kbHot);
        reinit_(x,y, 1);
        Active:= false
      end;


destructor TScrollApp.Done;
     begin
       inherited Done;
       _win_.Done
     end;


procedure TScrollApp.Draw;
    var   bp: bool; xlm,ylm: int;
    begin
      if QuickSort_IndArr(ind,arr_adr, comp, 0,top) then top_prev:= -1;
      if not visible then Exit;
      m_off (bp, xlm,ylm);
      with _win_ do
        begin
          BGIgraph.button (x0,y0,x1,y1,clBUTTON_COLOR,btNorm,btOFF);
          fillwin (x0+4,y0+5,x1-4,y0+dy_ScrollApp-5,clBUTTON_COLOR);
          on_off  (x0+4,y0+5,x1-4,y0+dy_ScrollApp-5,clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT, btSmall, btON)
        end;
      btTitle^.Draw;
      TScroller.Draw;
      m_on (bp, xlm,ylm)
    end;



procedure TScrollApp.ActiveOn;
    begin
      active:= true; btTitle^.OnOff(btON)
    end;

procedure TScrollApp.ActiveOff;
    begin
      active:= false; btTitle^.OnOff(btOFF)
    end;


procedure TScrollApp.reinit_(x,y, _page: int);
    var   dx,dy: int;
    begin
      if p_visible<>nil then visible:= bool(p_visible^);
      _win_.y1:= _win_.y0 + get_scroller_height(_page, item_dy, dyi, medzera) + dy_ScrollApp + 4;
      with _win_ do MoveRel(x-x0,y-y0);
      x:= _win_.x0; y:= _win_.y0;   { ak okno nie je pustene za hranice }

      lo_prev:= -1; hi_prev:= -1; lo:= 0; hi:= _page-1; pos:= 0;
      dy:= get_scroller_height(_page, item_dy, dyi, medzera);
      XY(x+4,y+dy_ScrollApp, x1-x0,dy);

      with btTitle^ do MoveRel(x-x0+dx_Ti,y-y0+6);
      sb^.ReInit(x1+2,y0,x-x0+dx_Ti,y1-y0)
    end;


procedure TScrollApp.hide;
    var   bp : bool; xl,yl : int;
    begin
      m_off(bp, xl,yl);
      with _win_ do ClrWin (x0,y0,x1,y1, bk0);
      m_on(bp, xl,yl);
      visible:= false
    end;
