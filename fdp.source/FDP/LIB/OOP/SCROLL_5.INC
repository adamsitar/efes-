{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TScrollInd                                               €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

constructor TScrollInd.Init(_Owner        : PGroup;
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

                            _hlpXXX : Pchar
                           );
      begin
        inherited Init(_Owner, _title,

                       _arr_adr, _top_adr,
                       _top_chg,_p_arr_chg,
                       _item_size, _new_item, _disp_item,

                       _item_dx,_item_dy,
                       _dxi,_dyi, _medzera, _bg,
                       _item_list,
                       _page,
                       _pos_en, _sb_sam, _sb_vzdy,

                       _dxb,_dyb, _init_buttons,_handle_buttons,_handler_owner,

                       _handler_type,_handler,_handler_par,

                       kbNoKey,cmNil, _hlpXXX
                      );
        p_arr_init:= _p_arr_init;
        is_ind:= _is_ind; ind:= nil;
        data_filter:= _data_filter; filter:= _filter;
        pos_en:= true; ind:= nil;  size:= 0;
        comp:= _comp;
        new_data
      end;


destructor TScrollInd.Done;
     begin
       disp_data;
       inherited Done
     end;

procedure TScrollInd.Draw;
    begin
      if QuickSort_IndArr(ind,arr_adr, comp, 0,top) then top_prev:= -1;
      inherited Draw
    end;


function TScrollInd.is_changed: bool;
   var   res: bool;
   begin
     if is_initialized then res:= false
     else begin
             res:=    ( (p_arr_chg<>nil) and ((p_arr_chg^<>0) and (p_arr_chg^<>arr_chg)) )
                   or ( (p_top_chg<>nil)   and bool(p_top_chg^)                              )
                      { ak som pri nacitacni pouzil filter a zobrazeny pocet prvkov je mensi }
                   or ( (filter=nil)     and (p_top_adr<>nil) and (int(p_top_adr^)<>top)     )
                   ;
             if res and ((p_arr_init=nil) or (p_arr_init^=false)) { pole je inicializaovane, nerusat ! } then
                begin
                  if (p_arr_chg<>nil) then arr_chg:= p_arr_chg^;
                  if (p_top_chg<>nil) then bool(p_top_chg^):= false
                end
          end;
     is_changed:= res
   end; { is_changed }


procedure TScrollInd.new_data;
    var   i,t: int;
    begin
      if not is_ind then
         begin
           inherited new_data;
           Exit
         end;

      if ind<>nil then FreeMem(ind,size*sizeof(int));

      TScroller.new_data;
      if (filter<>nil) and (arr_adr<>nil) then
         begin
           t:= 0;
           for i:= 0 to top do if TBFunc_p2(filter)(arr_adr^[i],data_filter) then inc(t);
           top:= t-1
         end;
      size:= top+1;

      GetMem(ind,size*sizeof(int));
      t:= 0;
      for i:= 0 to get_top do
          if (filter<>nil) and (arr_adr<>nil) then
              begin
                if TBFunc_p2(filter)(arr_adr^[i],data_filter) then
                   begin
                     ind^[t]:= i;
                     inc(t)
                   end
              end
          else ind^[i]:= i;

      if (ind<>nil) and (arr_adr<>nil) and (comp<>nil) then
         if QuickSort_IndArr(ind,arr_adr, comp, 0,top) then top_prev:= -1
    end;

procedure TScrollInd.disp_data;
    begin
      if not is_ind then
         begin
           inherited disp_data;
           Exit
         end;

      if (ind<>nil) then FreeMem(ind,size*sizeof(int));
      ind:= nil;
      size:= 0
    end;

{ najde
}
function TScrollInd.get_ind_in_list(i: int): int;
   var   j: int;
   begin
     if is_ind and (ind<>nil) then
        begin
          j:= 0; while (j<=top) and (ind^[j]<>i) do inc(j);
          if j<=top then get_ind_in_list:= j
          else get_ind_in_list:= i
        end
     else get_ind_in_list:= i
   end;

function TScrollInd.get_ind(i: int): int;
   begin
     if is_ind then
        if ind<>nil then get_ind:= ind^[i]
        else get_ind:= 0
     else get_ind:= i
   end;
