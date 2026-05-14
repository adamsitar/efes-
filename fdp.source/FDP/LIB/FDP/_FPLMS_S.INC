{ ----------
   mFPL
  ----------
}

 {$IFDEF KRL}
  function _kridlo_pre_vlastne_letisko (FPL: PDmFPL; s: Pstring): bool; far;
     begin
       _kridlo_pre_vlastne_letisko:=     is_KRL(FPL)
                                     and (
                                                   _plan_pre(FPL^.start.kod)
                                          or (     (cut_(FPL^.start.kod)='')
                                               and (not toto_letisko(FPL^.let))
                                             )
                                         )
     end;

  function _kridlo_pre_ine_letisko (FPL: PDmFPL; s: Pstring): bool; far;
     begin
       _kridlo_pre_ine_letisko:=       is_KRL(FPL)
                                  and (
                                          (not _plan_pre(FPL^.start.kod))
                                       or (     (cut_(FPL^.start.kod)='')
                                            and (toto_letisko(FPL^.let))
                                          )
                                      )
     end;

  function _is_stata_KRL (FPL: PDmFPL; s: Pstring): bool; far;
     begin
       _is_stata_KRL:=  _is_stat(FPL^.stat,s^,false)
     end;
 {$ENDIF}


{ filtre pre pripustenie ku akcii
}

 function _is_stat_FPLm (FPL: PDmFPL; s: Pstring): bool; far;
    begin
      _is_stat_FPLm:=       _FPLM._plan_pre_pracovisko(FPL)
                       and  _is_stat(FPL^.stat,s^,false)
    end;

 function _is_stata_FPLm (FPL: PDmFPL; s: Pstring): bool; far;
    begin
      _is_stata_FPLm:=  _is_stat(FPL^.stat,s^,false)
    end;


 function _is_plan_FPLm (FPL: PDmFPL; s: Pstring): bool; far;
    begin
      _is_plan_FPLm:=      { _FPLM.__plan_pre_pracovisko(FPL,false)}
                       {$IFDEF AIRBASE}
                            (   _plan_pre(FPL^.let)
                             or _plan_pre(FPL^.start.kod)
                            )
                        and
                       {$ENDIF}
                           _is_stata_FPLm (FPL,s)
    end;

 function _is_stat_FPLm_ine (FPL: PDmFPL; s: Pstring): bool; far;
    begin
      _is_stat_FPLm_ine:=  {$IFDEF AIRBASE}
                                  (not (   _plan_pre(FPL^.let)
                                        or _plan_pre(FPL^.start.kod)
                                       )
                                  )
                              and
                           {$ENDIF}
                           _is_stata_FPLm (FPL,s)
                                {(not _FPLM.__plan_pre_pracovisko(FPL,false))
                            and  (pos(cnst_finish,FPL^.stat)=0)}
    end;

 {function _is_stato_FPLm (FPL: PDmFPL; s: Pstring): bool; far;
    begin
      _is_stato_FPLm:=       (not _FPLM._plan_pre_pracovisko(FPL))
                        and  _is_stat(FPL^.stat,s^,false)
    end;

 function _is_stat_FPLo (FPL: PDmFPL; s: Pstring): bool; far;
    begin
      _is_stat_FPLo:= is_oFPL(FPL) and _is_stat_FPLm(FPL,s)
    end;

 function _is_stata_FPLo (FPL: PDmFPL; s: Pstring): bool; far;
    begin
      _is_stata_FPLo:= is_oFPL(FPL) and _is_stata_FPLm(FPL,s)
    end;
 }


 function get_FN_mFPL(p: pointer; i: int): string; far;
    var   FN  : string;
    begin
      FN:= pstring(p)^;
      get_FN_mFPL:= FN;
      if (FN='') or (getstr(pstring(p)^,2,['.'])=ext_KRL) then Exit;
      if (i<>0) and (i<>1) then FN:= ''
      else begin
             FSplit(FN, sDir,sName,sExt);
             if i=0 then sExt:= ext_oFPL
             else if i=1 then sExt:= ext_mFPL;
             FN:= sDir+sName+'.'+sExt
           end;
      get_FN_mFPL:= FN
    end;

 procedure sort_mFPL(p: Pptrs; top: pointer); far;
     begin
       QuickSort(p,@comp_idn_mFPL,nil{@swap_mFPL},0,int(top^),false)
     end;


{ Moze zadat lubovolny let vyhovujuci kriteriam
  alebo len podmnozinu letov dodefinovanych
  podla "select"
}
 function _item_filter_FPLM(FPL: PDmFPL; _item: PFPL_item_filter): bool; far;
    var   F7a,F13a: string;
          bres: bool;
    begin
      _item_filter_FPLM:= false;
      if (_item=nil) then Exit;

      F7a := code_FPLM_7a (FPL);
      F13a:= FPL^.start.kod;

      with _item^.key do
        _item_filter_FPLM:=      (   (_7a='')
                                  or (eq_str (_7a, F7a)
                                  or ((_7a<>'') and (eq_str (_7a, copy(F7a,1,length(_7a))))))
                                 )
                             and ((_13a='') or (eq_str (_13a,copy(F13a,1,length(_13a)))))
                             and ((_D.r=0)  or (eq_date(_D,FPL^.date)))

                             and (   (_item^.prev_filter=nil)
                                  or Tfilter_items_DB(_item^.prev_filter)(FPL,_item^.data_filter)
                                 )

    end;


 procedure spracuj_mFPL(_find_and_process_data,
                        _find_cnl_data,
                        _ppl,_arch,_rpl,_fpl : bool;

                        _data_filter : string;
                        _filter : pointer;

                        _handler : pointer;
                        _handler_type : TScrollAct_handler_type;

                        _print,
                        _send : bool;

                        _title: string;
                        _info: pchar;
                        _hlpXXX : Pchar
                       );

    var    _FN           : string;
           _FNfunc       : pointer;
           _FNfunc_p     : pointer;
           _dbchg        : pointer;

           iFPL          : PmFPL;
           print, send   : pointer;

           key           : string;
           item          : TFPL_item_filter;
           p_data_filter : pointer;

           h             : byte;

    begin

     { urcenie dat na vyhladanie...
     }
      fillchar(item,sizeof(item),0);
      key:= '';

      p_data_filter:= @_data_filter;

      item.data_filter:= @_data_filter;
      p_data_filter:= @item;
      item.prev_filter:= _filter;
      _filter:= @_item_filter_FPLM;

      if _find_and_process_data then
         begin
           if not formular_key_fpl(tit_MASKA, @fn_13aM, true,true,true,_arch, key) then Exit;
           decodekey_fpl (key, item.key._7a,item.key._13a,item.key._D);
           if (cut_(item.key._7a)<>'') or (cut_(item.key._13a)<>'') then
              begin
                {item.data_filter:= @_data_filter;
                p_data_filter:= @item;
                item.prev_filter:= _filter;
                _filter:= @_item_filter_FPLM}
              end
           else _find_and_process_data:= false
         end;


     { urcenie subora, kde sa ma vyhladavat...
     }
       _FNfunc   := nil;
       _FNfunc_p := nil;
       _dbchg    := nil;

       if _fpl then
          begin
            if _rpl then _FN:= get_fn_mFPL_RPL_let

            else if     (item.key._D.r<>0)
                    and (CheckDate(item.key._D.r,item.key._D.m,item.key._D.d, false))
                        then _FN:= get_dbfn(item.key._D, pathFPL_M,ext_mFPL)

            else begin
                   if _ppl then _FN:= get_PPL_FN(pathFPL_M,ext_mFPL,_title)
                   else if _arch then _FN:= get_ARCH_FN(pathARCH_FPL_M,ext_mFPL,_title)
                   else _FN:= get_fn_mFPL_let;

                  {$IFDEF OPL}
                    if _FN ='' then Exit;
                    _FNfunc   := @get_FN_mFPL;
                    _FNfunc_p := @_FN[0];
                  {$ENDIF}

                  decode_archived_date (_FN,true, item.key._D.r,item.key._D.m,item.key._D.d,h);
                end;

            if _rpl then _dbchg:= @dbchg_mFPL_RPL {else _dbchg:= @dbchg_mFPL}
          end
       else begin
             {$IFDEF KRL}
               if _ppl then _FN:= get_PPL_FN(pathFPL_M,ext_KRL, _title)
               else if _arch then _FN:= get_ARCH_FN(pathARCH_FPL_M,ext_KRL,_title{tit_arch_KRL})
               else _FN:= get_DBfn_(day,month,year, pathFPL_M,ext_KRL);
               _dbchg:= @dbchg_KRL
             {$ELSE}
               Exit;
             {$ENDIF}
            end;

     { parametre pre tlac, odoslanie...
     }
       print := nil;
       send  := nil;

       {$IFDEF ODOSLI_ULOZ}
         if _send then
           {$IFDEF KRL}
             if not _fpl then send:= @send_KRLs
             else
           {$ENDIF}
                  send:= @send_FPLs;
       {$ENDIF}

       {$IFDEF PRN}
         if _print then
           {$IFDEF KRL}
             if not _fpl then print:= @print_KRLs
             else
           {$ENDIF}
                  print:= @print_mFPLs;
       {$ENDIF}


     { vyhladavanie...
     }
      scroll_DB_FDP(_title,
                    _find_and_process_data,_find_cnl_data,true,
                    nil,

                    max_mFPLs, sizeof(DmFPL),
                    @new_mFPL,@format_mFPL_,@disp_mFPL,@eq_mFPL,

                    key,@read_mFPL,
                    p_data_filter,nil,nil,_filter,_filter,

                    true, @sort_mFPL, nil,
                    _handler_type,_handler,nil,
                    nil,nil,nil, print,send,

                    _FN, _FNfunc, _FNfunc_p,
                    db_mFPL_RIADKOV,@decodeDB_FPLM, _dbchg,

                    dxi_mFPL, dyi_mFPL, @plan_mFPL,
                    _info, _hlpXXX,

                    @p_fplm_dbscroller
                   );
    end;
