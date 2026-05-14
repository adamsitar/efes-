{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                                          Û
Û TScrollDB2                                               Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}

constructor TScrollDB2.Init(     _title     : string;     { hlavicka }

                                 _find_and_process_data,
                                 _msg_not_processed : bool;

                            { a) parametre pre pole }
                                 _items     : int;        { maximum overdrive }
                                 _item_size : word;       { velkost polozky   }

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
                                 _handler_par  : pointer; { adresa objektu dat alebo parametrov }


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

                                 _dxb,_dyb     : int;
                                 _init_buttons,_handle_buttons : pointer;
                                 _handler_owner : PObject;

                                 _hlpXXX       : Pchar
                            );

      var   _medzera,_dxi,_dyi,_bg: int;

      begin
        if _item_dy>10 then begin _medzera:= __medzera; _dxi:= __dxi; _dyi:= __dyi; _bg:= __bg; end
        else begin _medzera:= 2; _dxi:= 4; _dyi:= 4; _bg:= 0; end;

        arr:= New(PDynamic2,Init(_items,_item_size, _new_item,_format_item,_disp_item));
        arr^.p_eq_items:= _eq_items;

        inherited Init(nil, _title,

                       nil, @arr^.top,
                       nil{_DBchg}, nil{@data^.arr_chg},
                       _item_size, _new_item, _disp_item,

                       _item_dx,_item_dy, _dxi,_dyi,_medzera,_bg,
                       _item_list,
                       -1,
                       true,true,true,

                       _dxb,_dyb, _init_buttons,_handle_buttons,_handler_owner,
                       _handler_type,_handler,_handler_par,
                       kbNoKey, cmNil,
                       _hlpXXX
                      );

        arr_adr:= arr^.ap;

        find_and_process_data:= _find_and_process_data;
        msg_not_processed:= _msg_not_processed;
        finded_and_processed_data:= false;
        finded_data:= 0;

      { b) parametre pre pole
      }
        vzostupne:= _vzostupne;
        sort_item:= _sort_item;
        comp_item:= _comp_item;

      { c) parametre pre DB
      }
        FN:= _FN; FNfunc:= _FNfunc; FNfunc_p:= _FNfunc_p;
        riadkov:= _riadkov; DATAdecode:= _DATAdecode;
        DBdone:= nil;

        p_filter:= _p_filter;
        p_kluc:= _p_kluc;
        p_stav:= _p_stav;
        p_datadb:= _p_datadb;
        p_dataext:= _p_dataext;

      { d) kontrola pre opatovne nacitanie
      }
        DBchg:= _DBchg;
        FindFirst(FN, ReadOnly+Archive, DBattr)
      end;


procedure TScrollDB2.InitApp;
    begin
      inherited InitApp;
      { d) nacitanie dat }
      new_data
    end;

procedure TScrollDB2.DoneApp;
    begin
      inherited DoneApp;
      if (DBdone<>nil) then Tproc(DBdone);          { akcia na zaver }
      disp_data;
      Dispose(arr,Done)
    end;


function TScrollDB2.data_found: bool;
   var   _Event : TEvent;
   begin
     pos:= 0;
     finded_and_processed_data:= true;
     call_user_handler(_Event);
     data_found:= false
   end;

function TScrollDB2.data_not_found: bool;
   begin
     if msg_not_processed then Say2(msgMESS,msgDATA_NOT_FOUND);
     finded_and_processed_data:= false;
     data_not_found:= false
   end;

function TScrollDB2.is_to_be_run: bool;
   var   res : bool;
   begin
     res:= true;
     if find_and_process_data and (handler<>nil) then
        begin
          if (top=0) then res:= data_found
          else if top=-1 then res:= data_not_found;
          finded_data:= top+1
        end;
     is_to_be_Run:= res
   end;


function TScrollDB2.is_changed: bool;
   var   attr: SearchRec;
         res: bool;
   begin
     res:= (DBchg<>nil) and bool(DBchg^) and (OpenWins=1);
     if res then
        begin
          FindFirst(FN, ReadOnly+Archive, attr);
          res:= DBattr.time <> attr.time;
          DBattr.time:= attr.time;
          bool(DBchg^):= false
        end;
     is_changed:= res
   end; { is_changed }


procedure TScrollDB2.scroll_new_data(prev_pos: int);
    begin
      if comp_item<>nil then QuickSort(arr^.ap,comp_item,nil,0,arr^.top,false)
      else if sort_item<>nil then TProc_p2(sort_item)(arr^.ap, @arr^.top);
      top_prev:= -1;
      pos:= Limit(prev_pos, lo,N(top), 0);
    end;

procedure TScrollDB2.new_data;
    var   i : int;
          b,b2 : bool;
          prev_pos: int;
          fname,fpname : string;
    begin
      b:= __INFO_DB; __INFO_DB:= true;
      b2:= arr^.is_eq;
      arr^.is_eq:= FNfunc<>nil;
      prev_pos:= pos;
      disp_data;

      fname:= FN; i:= 0;
      repeat
        fpname:= fname;
        if (FNfunc<>nil) then fname:= TSfunc_pi(FNfunc)(FNfunc_p,i);
        arr^.read_DBitems (fname,riadkov,DATAdecode, p_filter,p_kluc,p_stav,p_datadb, vzostupne);
        top:= int(arr^.top);
        inc(i)
      until (FNfunc=nil) or (fname='') or (fpname=fname);

      arr^.is_eq:= b2;
      scroll_new_data(prev_pos);
      __INFO_DB:= b
    end;


procedure TScrollDB2.disp_data;
    var   i: int;
    begin
      arr^.DelAll;
      top:= arr^.top;
     {pos:= imit(pos, lo,N(top), 0)}
    end;


{
procedure TScrollDB2.list_item(i, x,y: int; b: bool);
    begin
      if (item_list<>nil) then TProc_p2i2b(item_list)(@Self, arr^.ap^[i],  x,y, b)
    end;
}

function TScrollDB2.call_user_handler(var _Event: TEvent): bool;
   var   p,item: pointer;
   begin
     if (top>-1) and (handler<>nil) and (item_size<MaxAvail) then
        begin
          p:= arr^.ap^[get_ind(pos)];
          if item_size<>0 then
             begin
               GetMem(item,item_size); FillChar(item^,item_size,0);
               if new_item<>nil then Tproc_p2(new_item)(p,item)
               else Move(p^,item^,item_size)
             end
          else item:= p;

          call_user_handler:= call_user_handler_(_Event, item);

          if item_size<>0 then
             begin
               if disp_item<>nil then Tproc_p(disp_item)(item);
               FreeMem(item,item_size)
             end
        end
     else call_user_handler:= false
   end;
