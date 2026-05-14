{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TScrollAct                                               €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

constructor TScrollAct.Init(_Owner  : PGroup;
                            _title  : string;

                            _arr_adr : pointer;
                            _top_adr : pointer;

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
      begin
        if _page<=0 then _page:= _set_page_size(_page,int(_top_adr^),_item_dy, __medzera, _dyb);
        if _dxi<0 then _dxi:= __dxi;
        if _dyi<0 then _dyi:= __dyi;
        if _medzera<0 then _medzera:= __medzera;

        inherited Init(_Owner,
                       _title,

                       _arr_adr, _top_adr,
                       _top_chg, _p_arr_chg,

                       btmdXY.x0,btmdXY.y0,
                       _item_dx,_item_dy, _dxi,_dyi, _medzera, _bg,
                       _item_list,
                       _page,
                       _handler<>nil, _sb_sam,_sb_vzdy,

                       _dxb,_dyb, _init_buttons,_handle_buttons,_handler_owner,

                       _kbHot, _cmXXXX
                       );

        item_size:= _item_size;
        new_item := _new_item;
        disp_item:= _disp_item;

        print_plan:= nil;
        send_plan:= nil;

        handler:= _handler;
        handler_par:= _handler_par;
        handler_type:= _handler_type;

        data_filter:= nil;
        filter:= nil;

        hlpXXX:= _hlpXXX;
        Centre;

        if (_handler<>nil) and (win<>nil) then win^.btTitle^.stat:= btOFF
      end; { TScrollAct.Init }


procedure TScrollAct.HandleEvent(var _Event: TEvent);
    begin
      inherited HandleEvent(_Event);
      if     (handler<>nil)
         and (   isCommand(_Event,cmScrollItemEntered)
              or isCommand(_Event,cmScrollItemClicked)
              or (win<>nil) and (win^.btTitle^.isClicked(_Event))
             ) then
         begin
           if (win<>nil) then with win^.btTitle^ do OnOff(TbtStat(not bool(stat)));
           if (top>=0) and (pos>=0) and call_user_handler(_Event) then SetCommand(_Event,cmClose)
           else ClearEvent(_Event);
           Wait(1,nil);
           if (win<>nil) then with win^.btTitle^ do OnOff(TbtStat(not bool(stat)))
         end;
    end; { TScrollAct.HandleEvent }


function TScrollAct.call_user_handler_(var _Event: TEvent; item: pointer): bool;
   begin
     case handler_type of

       _TBFunc_p    : if handler_par<>nil then
                           call_user_handler_:= TBFunc_p2  (handler)(item, handler_par)
                      else call_user_handler_:= TBFunc_p   (handler)(item);

       _TBFunc_p2   : if handler_par<>nil then
                           call_user_handler_:= TBFunc_p3  (handler)(@Self, item, handler_par)
                      else call_user_handler_:= TBFunc_p2  (handler)(@Self, item);

       _TBFunc_vEp2 : if handler_par<>nil then
                           call_user_handler_:= TBFunc_vEp3(handler)(_Event, @Self, item, handler_par)
                      else call_user_handler_:= TBFunc_vEp2(handler)(_Event, @Self, item);

       _TBFunc_vEp3 :      call_user_handler_:= TBFunc_vEp3(handler)(_Event, @Self, item, handler_par)

       else call_user_handler_:= false
     end;
   end;

function TScrollAct.call_user_handler(var _Event: TEvent): bool;
   var   p,item : pointer;
   begin
     if (top>-1) and (handler<>nil) and (MaxAvail>item_size) then
        begin
          p:= arr_adr^[get_ind(pos)];
          if item_size<>0 then
             begin
               GetMem(item,item_size); FillChar(item^,item_size,0);
               if new_item<>nil then Tproc_p2(new_item)(p,item)
               else Move(p^,item^,item_size)
             end
          else item:= p;

          case handler_type of
            _TBFunc_i    : call_user_handler:= TBFunc_i   (handler)(get_ind(pos));
            _TBFunc_pi   : call_user_handler:= TBFunc_pi  (handler)(@Self, get_ind(pos));
            _TBFunc_vEpi : call_user_handler:= TBFunc_vEpi(handler)(_Event, @Self, get_ind(pos))
            else call_user_handler:= call_user_handler_(_Event, item)
          end;

          if item_size<>0 then
             begin
               if disp_item<>nil then Tproc_p(disp_item)(item);
               FreeMem(item,item_size)
             end
        end
     else call_user_handler:= false
   end;

function TScrollAct.get_ind(i: int): int;
   begin
     get_ind:= i
   end;
