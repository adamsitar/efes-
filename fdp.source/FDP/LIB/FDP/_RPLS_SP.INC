{ ----------------------
   Triedenie RPL planov
  תתתתתתתתתתתתתתתתתתתתתת
}
 function comp_idn_RPL(RPL1,RPL2: PRPL): bool; far;
    var   s1,s2: string;
    begin
      with RPL1^ do s1:= _7a+_13a+_13b+_16a+_16b;
      with RPL2^ do s2:= _7a+_13a+_13b+_16a+_16b;
      if not RUSSIAN_RPL then
         begin
           s1:= mtks_rus_to_lat(s1);
           s2:= mtks_rus_to_lat(s2);
         end;
      comp_idn_RPL:= s1 < s2
    end;

 function comp_xxx_RPL(RPL1,RPL2: PRPL): bool; far;
    begin
      {case comp_RPL of
        comp_IDN :} comp_xxx_RPL:= comp_idn_RPL(RPL1,RPL2);
        {comp_EET : comp_xxx_RPL:= comp_eet_RPL(RPL1,RPL2);
        comp_STT : comp_xxx_RPL:= comp_stt_RPL(RPL1,RPL2);
      end}
    end;

 procedure sort_RPL(p: Pptrs; top: pointer); far;
     begin
       QuickSort(p,@comp_xxx_RPL,nil,0,int(top^),false)
     end;


{ Nacitanie a spracovanie ziadaneho planu
  alebo skupiny planov

}
 type  PRPL_item_filter = ^TRPL_item_filter;
       TRPL_item_filter = record
         key : Tkey_fpl;

         data_filter : pointer;
         prev_filter : pointer;
       end;


 function _kluc_RPL (kluc: pstring; _item: PRPL_item_filter): bool; far;
    var   bres : bool;
          s    : string;
    begin
      _kluc_RPL:= false;
      if (_item=nil) then Exit; { nemozeme nacitat vsetky plany, mame malo pamate }

      if _item^.key._7a<>'' then
         begin
           s:= getstr(kluc^,1,[icao_ARR]);
           bres:= pos(_item^.key._7a,s)=1
         end
      else bres:= true;
      if not bres then Exit;

      if _item^.key._13a<>'' then
         begin
           s:= getstr(kluc^,3,[icao_ARR]);
           bres:= pos(_item^.key._13a,s)=1
         end;
      if not bres then Exit;

     _kluc_RPL:= true
   end;

 function _data_RPL (RPL: PRPL; _item: PRPL_item_filter): bool; far;
    var   bres : bool;
    begin
      _data_RPL:= false;
      if (_item=nil) then Exit;

      with _item^.key do
        _data_RPL:=          (   (_7a='')
                                  or (eq_str (_7a, RPL^._7a)
                                  or ((_7a<>'') and (eq_str (_7a,copy(RPL^._7a,1,length(_7a))))))
                                 )
                             and ((_13a='') or (eq_str (_13a,copy(RPL^._13a,1,length(_13a)))))

                             and (   (_item^.prev_filter=nil)
                                  or Tfilter_items_DB(_item^.prev_filter)(RPL,_item^.data_filter)
                                 )
    end;


 procedure _spracuj_RPL (_find_data,_process_data : bool;

                         _data_filter  : Pkey_fpl;
                         _filter       : pointer;

                         _handler_type : TScrollAct_handler_type;
                         _handler      : pointer;
                         _handler_par  : pointer;

                         _title  : string;
                         _hlpXXX : Pchar
                        );

    var    key : string;
           p_filter : pointer;
           item : TRPL_item_filter;
           pomb: bool;
           ch : char;
           d : TDate;

    label  L;

    begin
      if _title='' then _title:= tit_RPL_PREHLAD;
      if _hlpXXX=nil then _hlpXXX:= hlp_PREHLAD_RPL;

     { urcenie dat na vyhladanie...
     }
      L:

      p_filter:= nil;
      fillchar(item,sizeof(item),0);
      if _data_filter<>nil then item.key:= _data_filter^;
      item.data_filter := _data_filter;
      item.prev_filter := _filter;

      key:= '';
      if _find_data or _process_data then
         begin
           {if _data_filter<>nil then item.key:= _data_filter^;}
           while (cut_(item.key._7a)='') do
             begin
               if not formular_key_fpl (tit_MASKA, @fn_13a, true,false,false,false, key) then Exit;
               decodekey_fpl (key, item.key._7a,item.key._13a,d);
             end;
           p_filter:= @item;
         end;


     { nacitanie...
     }
      scroll_DB_FDP(_title,
                    _process_data,false,true,nil,

                    max_RPLs, sizeof(DRPL),
                    @new_RPL,nil,@disp_RPL,@eq_RPL,

                    '',nil,

                    p_filter,@_kluc_RPL,nil,nil,@_data_RPL,
                    true, @sort_RPL, nil,
                    _handler_type,_handler,_handler_par,
                    nil,nil,nil,{$IFDEF PRN}@print_RPLs{$ELSE}nil{$ENDIF},nil,

                    get_RPLfn_(item.key._7a), nil,nil,
                    db_RPLF_RIADKOV,@decodeDB_RPLF_rpl, nil{@dbchg_RPL},

                    dxi_RPL, dyi_RPL, @plan_RPL,

                    nil,_hlpXXX,

                    @p_rpl_dbscroller
                   );
    end;
