procedure init_sc_butt1(sc: PScrollWin);
    var   bt1   : PDialogButton;
          xt,yt : int;
          _kbHot : char;
    begin
     {$IFDEF PRN}
       sc^.Win^.get_btXY(1,0, xt,yt);
       bt1:= New(PDialogButton,Init(sc^.Win, xt,yt,GetAltCode(get_HotKey(_kbHot,titPRINT)),cmPrint,titPRINT,icKey,icText));
     {$ENDIF}
    end;

procedure init_sc_butt2(sc: PScrollWin);
    var   bt1   : PDialogButton;
          xt,yt : int;
          _kbHot : char;
    begin
     {$IFDEF PRN} xt:= 1; init_sc_butt1(sc);
     {$ELSE}      xt:= 0;
     {$ENDIF}
      sc^.Win^.get_btXY(1,xt, xt,yt);
      bt1:= New(PDialogButton,Init(sc^.Win, xt,yt,GetAltCode(get_HotKey(_kbHot,titSEND)),cmSend,titSEND,icKey,icText));
    end;

{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TScrollWin                                               €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
procedure TScrollWin.init_win(_title: string; x,y, dx,dy: int;
                              _kbHot: char; _cmXXXX: word
                             );
    begin
      win:= New(PWindow,Init(@Self, x,y, dx,dyb, _kbHot, _cmXXXX, _title, true));
      win^.own_img:= true; win^.btSize:= btNorm;
      reinit_(x,y,hi-lo+1);
      Active:= true;
    end;


constructor TScrollWin.Init(_Owner     : PGroup;
                            _title     : string;

                            _arr_adr   : pointer;
                            _top_adr   : pointer;

                            _top_chg   : pointer;
                            _p_arr_chg : p_tick_counter; { ukazovatel na premennu o zmene dat <>0 or <>last_tick_counter }

                            x,y, _item_dx,_item_dy : int;
                            _dxi,_dyi, _medzera : int; _bg : byte;
                            _item_list : pointer;
                            _page  : int;
                            _pos_en, _sb_sam, _sb_vzdy : bool;

                            _dxb,_dyb : int;
                            _init_buttons,_handle_buttons : pointer;
                            _handler_owner : PObject;
                            _kbHot : char; _cmXXXX : word
                           );
      var   dx,pg: int;
      begin
        dxb:= _dxb; dyb:= _dyb;
        init_buttons:= _init_buttons;

        handler_buttons:= _handle_buttons;
        handler_owner:= _handler_owner;
        handler_data:= nil{_handler_data};

        if _item_dx + 2 <length(_title) shl 3 then _title:= copy(_title,1,_item_dx shr 3 - 5)+'...';
        dx:= 10 + get_scroller_size(_item_dx,_dxi) + 10;
        pg:= (MaxY-(2*winHEIGHT+dyb+2*_dyi+btmdXY.y0+btmdXY.y1)) div (_item_dy+_medzera);
        if _page>-1 then _page:= Minimum(_page,pg) else _page:= pg;
        if _sb_vzdy or ((_top_adr<>nil) and (int(_top_adr^)>=_page)) then
           inc(dx,MEDZERA__SCROLLER__SCROLL_BAR+SCROLL_BAR__SIRKA);
        dx:= Maximum(GetWindowSize(_title),dx)+_dxb;

        inherited Init(_Owner, _page, x+10, y+winHEIGHT-2,
                       _item_dx,_item_dy,
                       _dxi,_dyi, _medzera, _bg,
                       _pos_en, _sb_sam,
                       _item_list,
                       _arr_adr, _top_adr,
                       _top_chg, _p_arr_chg
                      );
        cmXXXX:= _cmXXXX;

        win:= nil;
        init_win(_title, x,y, dx,winHEIGHT+_dyb, _kbHot,_cmXXXX);
        initialize_buttons
      end;



procedure TScrollWin.initialize_buttons;
    begin
      if init_buttons<>nil then TProc_p(init_buttons)(@Self)
    end;


procedure TScrollWin.Draw;
    var   bp: bool; xl,yl : int;
    begin
      if not visible then Exit;
      m_off(bp, xl,yl);
      {win^.Draw;
      Image;}
      TScroller.Draw;
      sb^.Draw;
      m_on(bp, xl,yl);
    end;


procedure TScrollWin.Image;
    begin
    end;


procedure TScrollWin.Run(var _Event: TEvent);
    var   b: bool;
    begin
      {$IFDEF SKRY_OKNA} b:= SKRYVANIE; SKRYVANIE:= false; {$ENDIF}
      inherited Run(_Event);
      {$IFDEF SKRY_OKNA} SKRYVANIE:= b {$ENDIF}
    end;


procedure TScrollWin.handle_buttons(var _Event: TEvent);
    begin
      if     (handler_buttons<>nil)
         and (_Event.what<>evNothing) then
              TBFunc_vEp3(handler_buttons)(_Event,@Self,handler_owner,handler_data)
    end;

procedure TScrollWin.HandleEvent(var _Event: TEvent);
    begin
      {if not visible then Exit; -> kvoli EDD }
      inherited HandleEvent(_Event);
      if (_Event.what<>evNothing) and (win<>nil) then win^.HandleEvent(_Event);
      if (_Event.what<>evNothing) then handle_buttons(_Event)
    end;


procedure TScrollWin.centre;
    var   x,y: int;
    begin
      if win=nil then Exit;

      x:= Win^.x0;  y:= Win^.y0;
      Win^.Centre;
      TView.MoveRel(Win^.x0 - x, Win^.y0 - y);
      sb^.MoveRel(Win^.x0 - x, Win^.y0 - y)
    end;


procedure TScrollWin.reinit_(x,y,_page: int);
    var   dx,dy: int;
    begin
      if win=nil then Exit;

      with win^ do
         begin
           dx:= x1-x0;
           dy:= winHEIGHT+dyb + get_scroller_height(_page, item_dy, dyi, medzera) + 6;
           {inc(dx,dxb); inc(dy,dyb);}
           MoveRel(x-x0,y-y0); XY(x,y,dx,dy)
         end;
      inherited reinit_(win^.x0+10,win^.y0+winHEIGHT-4,_page)
    end;
