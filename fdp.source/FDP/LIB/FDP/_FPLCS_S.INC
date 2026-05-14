{ ----------
   cFPL
  ----------
}

procedure sort_cFPL(p: Pptrs; top: pointer); far;
    begin
      QuickSort(p,@comp_idn_cFPL,nil{@swap_cFPL},0,int(top^),false)
    end;


function _item_filter_FPLC(FPL: PDcFPL; _item: PFPL_item_filter): bool; far;
   begin
     _item_filter_FPLC:=
           (_item<>nil)
       and (                             eq_str(_item^.key._7a,idn_cFPL(FPL)))
       and ((_item^.key._13a='')     or (eq_str(_item^.key._13a,FPL^.start.kod)))
       and ((_item^.key._D.r=0)      or (eq_date(_item^.key._D,FPL^.date)))
       and ((_item^.prev_filter=nil) or Tfilter_items_DB(_item^.prev_filter)(FPL,_item^.data_filter))
   end;



procedure spracuj_cFPL(_FN: string;
                       _find_and_process_data : bool;
                       _FNfunc: pointer; _FNfunc_p: pointer;
                       _data_filter : pointer; _filter : pointer;
                       _handler : pointer; _handler_type: TScrollAct_handler_type;
                       _title: string; _info: pchar; _hlpXXX : Pchar
                      );

   var    key           : string;
          item          : TFPL_item_filter;
          p_data_filter : pointer;

   begin
     key:= ''; fillchar(item,sizeof(item),0);
     p_data_filter:= @_data_filter;
     if _find_and_process_data then
        begin
          if not formular_key_fpl(tit_FPL, @fn_13aM, true,true,true,false, key) then Exit;
          decodekey_fpl (key, item.key._7a,item.key._13a,item.key._D);
          if cut_(item.key._7a)<>'' then
             begin
               item.data_filter:= @_data_filter;
               item.prev_filter:= _filter;
               p_data_filter:= @item;
               _filter:= @_item_filter_FPLC
             end
          else _find_and_process_data:= false
        end;

     scroll_DB(_title,
               _find_and_process_data,true,

               max_cFPLs, sizeof(DcFPL),
               @new_cFPL,@format_cFPL,@disp_cFPL,@eq_cFPL,
               _data_filter,nil,nil,nil,_filter,
               true, @sort_cFPL, nil, { sort }
               _handler_type,_handler, nil,

               _FN, _FNfunc, _FNfunc_p,
               db_cFPL_RIADKOV,@decodeDB_FPLC, @dbchg_cFPL,
               {$IFDEF EDD} dx_cFPLp, dy_cFPLp, @plan_cFPL,
               {$ELSE}      dx_sc_cFPL, dy_sc_cFPL,
                            @sc_cFPL,
               {$ENDIF}
               0,0,nil,nil,nil,
               _info, _hlpXXX
              )
   end;


