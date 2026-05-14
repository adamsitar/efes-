 constructor TScrollDB_FDP.Init(     _title     : string;     { hlavicka }

                                     _find_and_process_data,
                                     _find_cnl_data,
                                     _msg_not_processed : bool;

                                { a) parametre pre pole }
                                     _items     : int;      { maximum overdrive }
                                     _item_size : word;     { velkost polozky }

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
                                     _handler      : pointer; { @TBfunc_i  }
                                     _handler_par  : pointer;   { adresa objektu dat alebo parametrov }

                                     _init_buttons   : pointer;
                                     _handle_buttons : pointer;
                                     _handler_data   : pointer;

                                     _print        : pointer;
                                     _send         : pointer;

                                { b) parametre pre DBF  }
                                     _FN           : string;
                                     _FNfunc       : pointer;  { Fcia pre FN, @TSfunc_pi   }
                                     _FNfunc_p     : pointer;  { parameter p pre TSFunc_pi }
                                     _riadkov      : byte;
                                     _DATAdecode   : pointer;
                                     _DBchg        : pointer;  { ukazovatel na logicku premennu zapisu do DBF }

                                { c) parametre pre ScrollWin }
                                     _item_dx,_item_dy: int;  { velkost polozky }
                                     _item_list    : pointer; { vypis polozky }

                                     _hlpXXX       : Pchar
                                );
       var   _dy : int;
       begin
         if _hlpXXX=nil then _hlpXXX:= hlp_zoznam;
         if _init_buttons=nil then
            begin
              if (_print<>nil) and (_send<>nil) then _init_buttons:= @init_sc_butt2
              else if (_print<>nil) then _init_buttons:= @init_sc_butt1
              else _init_buttons:= nil;
            end;
         if _init_buttons<>nil then _dy:= btHEIGHT+10 else _dy:= 0;

         inherited Init(_title,

                        _find_and_process_data,
                        _msg_not_processed,

                        _items,_item_size,

                        _new_item,_format_item,_disp_item,_eq_items,
                        _p_filter,_p_kluc,_p_stav,_p_datadb,_p_dataext,

                        _vzostupne,_sort_item, _comp_item,
                        _handler_type,_handler,_handler_par,

                        _FN, _FNfunc,_FNfunc_p,_riadkov,
                        _DATAdecode,_DBchg,

                        _item_dx,_item_dy, _item_list,
                        0,_dy, _init_buttons,_handle_buttons,nil{_handler_owner},

                        _hlpXXX
                       );

         find_cnl_data := _find_cnl_data;
         handler_buttons := _handle_buttons;
         handler_data := _handler_data;
         print := _print;
         send := _send
       end;


 (*{$IFDEF DEBUG}
   function TScrollDB_FDP.call_user_handler_(var _Event: TEvent; item: pointer): bool;
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

   function TScrollDB_FDP.call_user_handler(var _Event: TEvent): bool;
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
 {$ENDIF}*)


 function TScrollDB_FDP.ma_sa_prekreslit: bool;
    var   bres: bool;
    begin
      bres:= inherited ma_sa_prekreslit and (OpenWins=ScreenDesc+1);
      ma_sa_prekreslit:= bres
    end;


 procedure TScrollDB_FDP.data_update(item: pointer);
     var   zarad : bool;
           nasli,i,prev_pos : int;
     begin
       if not on_board then Exit;

      { a) zistenie, ci data maju byt zaradene v zozname
      }
        zarad:= arr^.include_DBitem(item,p_filter{data_filter},p_dataext{filter});

      { b) vyhladanie, ci data uz existuju v zozname
      }
        nasli:= arr^.find_data(item);

      { c) spracovanie novych udajov
      }
        prev_pos:= pos;

        if nasli>-1 then
           if zarad then arr^.Eq(nasli,item)
           else arr^.Del(nasli)
        else if zarad then arr^.Add(item)
             else Exit;

      { d) zobrazenie
      }
       top:= get_top;
       scroll_new_data(prev_pos);
       if OpenWins>ScreenDesc+1 then PREPIS:= absTime
       else List
     end;

 function TScrollDB_FDP.data_not_found;
    var   res, cnl,dec,ari : bool;
    begin
      if     find_cnl_data
         and (not (CNL_VYPIS and DEC_VYPIS and ARR_VYPIS))
         and (Ask2(msgVERIPHY,tit_READ_CNL,'',White,clBUTTON_COLOR,waitASK*18) = ansAno)
             then
         begin
           cnl:= CNL_VYPIS; CNL_VYPIS:= true;
           dec:= DEC_VYPIS; DEC_VYPIS:= true;
           ari:= ARR_VYPIS; ARR_VYPIS:= true;
           new_data;
           CNL_VYPIS:= cnl;
           DEC_VYPIS:= dec;
           ARR_VYPIS:= ari;
         end;
      if (top=0) then res:= inherited data_found
      else if top=-1 then res:= inherited data_not_found
      else res:= true;
      data_not_found:= res
    end;


 procedure TScrollDB_FDP.HandleEvent(var _Event: TEvent);
     begin
       inherited HandleEvent(_Event);
       if ((_Event.What and evMessage) <> 0)
            and (   (_Event.Command = cmPrint {cm_PLAN_PRINT})
                 or (_Event.Command = cmSend  {cm_PLAN_SEND})
                ) then
           begin
             case _Event.Command of
               cmPrint, cm_PLAN_PRINT : if print<>nil then TProc_p2s(print)(arr^.ap,@arr^.top,strpas(win^.bttitle^.title));
               cmSend,  cm_PLAN_SEND  : if print<>nil then TProc_p2 (send) (arr^.ap,@arr^.top)
             end;
             ClearEvent(_Event)
           end
     end;


 function scroll_DB_FDP (    _title        : string;   { hlavicka }

                             _find_and_process_data,
                             _find_cnl_data,
                             _msg_not_processed : bool;

                             _finded_data : pint;

                        { a) parametre pre pole }
                             _items        : int;      { maximum overdrive }
                             _item_size    : word;     { velkost polozky }

                             _new_item     : pointer;  { Tproc_p2 - alokacia polozky }
                             _format_item  : pointer;  { Tproc_p - formatovanie }
                             _disp_item    : pointer;  { Tproc_p - dealokacia, moze byt nil }
                             _eq_items     : pointer;

                             _kluc         : string;
                             _p_read       : PIFunc_sp;

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
                             _handler_par  : pointer;

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
                             _item_dx,_item_dy: int;  { velkost polozky }
                             _item_list : pointer;    { vypis polozky }

                             _info,_hlpXXX : Pchar;

                        { d) parameter pre program
                        }
                             p_dbscroller : pPScrollDB_FDP
                        ): bool;

     var   sc : PScrollDB_FDP;
           Ev : TEvent;
           d  : Tdate;
           s  : string;
           is : bool;
           item : pointer;
           bres : bool;
     begin
       scroll_DB_FDP:= false;
       if (_kluc<>'') and (_p_read<>nil) and (_handler<>nil) and (_handler_type=_TBFunc_p) then
          begin
            getmem(item,_item_size);
            fillchar(item^,_item_size,0);
            if TIFunc_sp(_p_read)(_kluc,item)>-1 then
               begin
                 if _handler_par<>nil then TBFunc_p2 (_handler)(item, _handler_par)
                 else TBFunc_p (_handler)(item);
                 bres:= true;
               end
            else bres:= false;
            if _disp_item<>nil then TProc_p(_disp_item)(item);
            freemem(item,_item_size);
            scroll_DB_FDP:= bres;
            if bres then Exit;
          end;

       if (_FN='') and (_FNfunc=nil) then Exit;
       if _info=nil then _info:= SCROLL_SEL;
       InfoCakaj(msgREAD,tit_WAIT_READ);
       get_plan_date(d, _FN);
       s:= decode_date_fn(_FN);
       sc:= New(PScrollDB_FDP,Init(_title+' ('+cut_(s)+')',{msgFADTE+DateToStr2(d.d,d.m,0),}

                                   _find_and_process_data,
                                   _find_cnl_data,
                                   _msg_not_processed,

                                   _items,_item_size,
                                   _new_item,_format_item,_disp_item,_eq_items,

                                   _p_filter,_p_kluc,_p_stav,_p_datadb,_p_dataext,
                                   _vzostupne,_sort_item,_comp_item,

                                   _handler_type,_handler,_handler_par,

                                   _init_buttons,
                                   _handle_buttons,
                                   _handler_data,
                                   _print,_send,

                                   _FN,_FNfunc,_FNfunc_p,
                                   _riadkov,_DATAdecode,_DBchg,

                                   _item_dx,_item_dy,
                                   _item_list,

                                   _hlpXXX)
                                  );
       InfoCakaj_zatvor;
       if p_dbscroller<>nil then
          begin
            is:= p_dbscroller^=nil;
            if is then p_dbscroller^:= sc;
          end
       else is:= false;
       sc^.RunLocalFunc(Ev,_info);
       if _finded_data<>nil then  _finded_data^:= sc^.finded_data;
       if is then p_dbscroller^:= nil;
       scroll_DB_FDP:= sc^.finded_and_processed_data;
       Dispose(sc,Done)
     end;
