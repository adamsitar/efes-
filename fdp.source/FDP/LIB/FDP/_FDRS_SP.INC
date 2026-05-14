 function comp_idn_FDR(FDR1,FDR2: PFDR): bool; far;
    var   s1,s2: string;
    begin
      with FDR1^ do s1:= idn{+eet.kod+code_l4_utc(eet.h,eet.m)};
      with FDR2^ do s2:= idn{+eet.kod+code_l4_utc(eet.h,eet.m)};
      if not RUSSIAN_FPL then
         begin
           s1:= mtks_rus_to_lat(s1);
           s2:= mtks_rus_to_lat(s2);
         end;
      if s1<>s2 then comp_idn_FDR:= s1<s2
      else begin
             with FDR1^ do s1:= eet.kod+code_l4_utc(eet.h,eet.m);
             with FDR2^ do s2:= eet.kod+code_l4_utc(eet.h,eet.m);
             if not RUSSIAN_FPL then
                begin
                  s1:= mtks_rus_to_lat(s1);
                  s2:= mtks_rus_to_lat(s2);
                end;
             comp_idn_FDR:= s1<s2
           end
    end;

 function comp_eet_FDR(FDR1,FDR2: PFDR): bool; far;
    var   rres: real;
    begin
      if FDR1^.eet.cas<>FDR2^.eet.cas then comp_eet_FDR:= FDR1^.eet.cas<FDR2^.eet.cas
      else comp_eet_FDR:= comp_idn_FDR(FDR1,FDR2)
    end;

 function comp_stt_FDR(FDR1,FDR2: PFDR): bool; far;
    var   res: int;
          r: string;
    begin
      res:=   icao_head_type(FDR1^.stat, r, @hd_ICAO,sizeof(hd_ICAO) div sizeof(Thead_ICAO))
            - icao_head_type(FDR2^.stat, r, @hd_ICAO,sizeof(hd_ICAO) div sizeof(Thead_ICAO));
      if res<>0 then comp_stt_FDR:= res<0
      else comp_stt_FDR:= comp_idn_FDR(FDR1,FDR2)
    end;

 function comp_xxx_FDR(FDR1,FDR2: PFDR): bool;
    begin
      case comp_FPL4 of
        comp_IDN : comp_xxx_FDR:= comp_idn_FDR(FDR1,FDR2);
        comp_EET : comp_xxx_FDR:= comp_eet_FDR(FDR1,FDR2);
        comp_STT : comp_xxx_FDR:= comp_stt_FDR(FDR1,FDR2);
      end
    end;

 procedure sort_FDR(p: Pptrs; top: pointer); far;
     begin
       QuickSort(p,@comp_xxx_FDR,nil,0,int(top^),false)
     end;



{ -----------------------
  Spracovanie FDR
  -----------------------
}
 type  PFDR_item_filter = ^TFDR_item_filter;
       TFDR_item_filter = record
         key : Tkey_fpl;
         poz : Tpozs;

         p_ext : PBFunc_p2;
       end;


 function _kluc_FDR (kluc: pstring; _item: PFDR_item_filter): bool; far;
    var   bres : bool;
          s    : string;
    begin
      _kluc_FDR:= false;
      if (_item=nil) then Exit; { nemozeme nacitat vsetky plany, mame malo pamate }

      if _item^.key._7a<>'' then
         begin
           s:= getstr(kluc^,pos_key_7a,[icao_ARR]);
           bres:= pos(_item^.key._7a,s)=1
         end
      else bres:= true;
      if not bres then Exit;

      if _item^.key._13a<>'' then
         begin
           s:= getstr(kluc^,pos_key_13a,[icao_ARR]);
           bres:= pos(_item^.key._13a,s)=1
         end;
      if not bres then Exit;

      { datum sa nekontrolute, pretoze plany su nacitavane
        z planu na dany den
        (_D.r=0)  or (eq_date(_D,FPL^.date)
      }
     _kluc_FDR:= true
   end;


{ "_decodeDBB_FDR_XY", identifikator/poznamka nesmie byt zrusena
}
 function _stav_FDR (buff: PDB_buff; _item: PFDR_item_filter): bool; far;
    var   FDR: DFDR;
          s : string;
          p : pchars;
          bres : bool;
    begin
      _stav_FDR:= true;
      if (_item=nil) then Exit;
      _stav_FDR:= false;
      fillchar(FDR,sizeof(FDR),0);

      if (_item^.poz=[]) then bres:= true
      else begin
             s:= DBstr_to_str_ (buff^[db_fpl4_ine]); p:= @s[1];
             with FDR do
               begin
                 get_s(p, @stat, sizeof(stat));
                 get_s(p, @date, sizeof(date));
                 get_s(p, @eet,  sizeof(eet));
                 get_s(p, @exi,  sizeof(exi));
               end;
             stav_FDR (@FDR,absTime,bres);
             bres:= FDR.poz in _item^.poz
           end;
      if not bres then Exit;

      _stav_FDR:= true
    end;

 function _data_FDR (FDR: PFDR; _item: PFDR_item_filter): bool; far;
    var   bres : bool;
    begin
      _data_FDR:= true;
      if (_item=nil) then Exit;
      _data_FDR:= false;

      with _item^.key do
        _data_FDR:=       ((_7a='')  or (pos(_7a,FDR^.idn)=1))
                      and ((_13a='') or (pos(_13a,FDR^.dep.kod)=1))
                      and ((_D.r=0)  or (eq_date(_D,FDR^.date)))

                      and (   (_item^.poz=[]) or (FDR^.poz in _item^.poz)
                           {or  _filter_cnl_arr(FDR^.stat)}
                          )

                      {and (   (_item^.prev_filter=nil)
                           or Tfilter_items_DB(_item^.prev_filter)(FDR,_item^.data_filter)
                          )}
    end;


 procedure _spracuj_FDR(_find_data,_process_data,
                        _ppl,_arch : bool;

                        _p_ext    : PBFunc_p2;
                        _poz      : Tpozs;
                        _stat     : string;

                        _handler_type : TScrollAct_handler_type;
                        _handler      : pointer;
                        {_handler_par  : pointer;}

                        _title  : string;
                        _hlpXXX : Pchar
                       );

     var   fn,key : string;

           p_filter : pointer;
           item : TFDR_item_filter;

           b1,b2 : bool;
           r1,r2 : real;

     label L;

     begin
       if _title='' then _title:= tit_FPL4_PREHLAD;
       if _hlpXXX=nil then _hlpXXX:= hlp_PREHLAD_FPL4;

       b1:=     (poz_CANCELLED in _poz)
             or (poz_NOT_APPROVED in _poz)
             or (poz_NOT_ACTUAL in _poz)
             or (poz_HANGAR in _poz)
             or (poz_CANCELLED in _poz)
             or (poz_NOT_APPROVED in _poz)
             or (poz_NOT_ACTUAL in _poz)
            ;
       b2:= (poz_PLAN in _poz) and (not _propose_dayFPL4);

     L :

       fillchar(item,sizeof(item),0);
       item.poz:= _poz;
       p_filter:= @item;

       key:= ''; fn:= '';

       {$IFDEF PROCESS_FPL4}
        if (oFDR=nil) or b1 or b2 or _arch or (_poz=[]) then
       {$ENDIF}
          begin
            if _find_data or _process_data then
               begin
                 if not formular_key_fpl(tit_MASKA, @fn_13a, true,true,true,_arch, key) then Exit;
                 decodekey_fpl (key, item.key._7a,item.key._13a,item.key._D);
                 if (item.key._D.r<>0) then
                    begin
                      if (CheckDate(item.key._D.r,item.key._D.m,item.key._D.d, false)) then
                         begin
                           r1:= DateToSec(year,month,day);
                           r2:= DateToSec(item.key._D.r,item.key._D.m,item.key._D.d);
                           if (_arch and (r1<=r2)) or (b1 and (r1<r2)) {or (b2 and (r1>r2))} then goto L;
                           fn:= get_dbfn(item.key._D, pathFPL,extFPL)
                         end
                      else goto L
                    end
               end;

            if fn='' then
               begin
                 if _ppl then fn:= get_PPL_FN(pathFPL,extFPL,_title)
                 else if _arch then fn:= get_ARCH_FN(pathARCH_FPL,extFPL,_title)
                 else fn:= get_fn_FPL4;
               end;
          end;

       if fn<>'' then
        { z db }
         scroll_DB_FDP(_title,
                       _process_data,
                       false,true,
                       nil,

                       max_FDRs, sizeof(DFDR),
                       @new_FDR,nil,@disp_FDR,@eq_FDR,

                       '',nil,

                       p_filter,
                       @_kluc_FDR,
                       @_stav_FDR,
                       nil,
                       @_data_FDR,

                       true, @sort_FDR,nil{@comp_xxx_FDR},
                       _handler_type,_handler,nil{_handler_par},
                       nil,nil,nil, {$IFDEF PRN}@print_FDRs{$ELSE}nil{$ENDIF},nil,

                       FN, nil,nil,
                       db_FPL4_RIADKOV,@decodeDB_FDR,nil{@dbchg_FPL4},

                       dx_FDR_plan,dy_FDR_plan, @plan_FDR,

                       nil,_hlpXXX,

                       @p_fdr_dbscroller
                      )

      {$IFDEF PROCESS_FPL4}
      { z pamate }
        else if oFDR<>nil then
           oFDR^.Spracovanie(_title, @item,@_data_FDR,
                            _handler_type,_handler,nil{_handler_par},
                            {$IFDEF PRN}@print_FDRs{$ELSE}nil{$ENDIF}
                            {$IFDEF MATCA},nil {$ENDIF},
                            _hlpXXX
                           );
      {$ENDIF}
     end;
