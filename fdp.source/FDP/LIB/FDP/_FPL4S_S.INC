 function comp_idn_FPL4(FPL1,FPL2: PFPL4): bool; far;
    var   s1,s2: string;
    begin
      s1:= decode_l4_7a(FPL1^._7){+FPL1^._13};
      s2:= decode_l4_7a(FPL2^._7){+FPL2^._13};
      if not RUSSIAN_FPL then
         begin
           s1:= mtks_rus_to_lat(s1);
           s2:= mtks_rus_to_lat(s2);
         end;
      if s1<>s2 then comp_idn_FPL4:= s1<s2
      else begin
             if RUSSIAN_FPL then
                begin
                  s1:= FPL1^._13;
                  s2:= FPL1^._13;
                end
             else begin
                    s1:= mtks_rus_to_lat(FPL1^._13);
                    s2:= mtks_rus_to_lat(FPL1^._13);
                  end;
             comp_idn_FPL4:= s1<s2
           end
    end;

 function comp_inp_FPL4(FPL1,FPL2: PFPL4): bool; far;
    var   s1,s2: string;
    begin
      with FPL1^.eet do s1:= kod+code_l4_utc(h,m)+decode_l4_7a(FPL1^._7);
      with FPL2^.eet do s2:= kod+code_l4_utc(h,m)+decode_l4_7a(FPL2^._7);
      if not RUSSIAN_FPL then
         begin
           s1:= mtks_rus_to_lat(s1);
           s2:= mtks_rus_to_lat(s2);
         end;
      comp_inp_FPL4:= s1<s2
    end;

 function comp_eet_FPL4(FPL1,FPL2: PFPL4): bool; far;
    var   s1,s2: string;
    begin
      with FPL1^.eet do s1:= code_l4_utc(h,m)+kod+decode_l4_7a(FPL1^._7);
      with FPL2^.eet do s2:= code_l4_utc(h,m)+kod+decode_l4_7a(FPL2^._7);
      if not RUSSIAN_FPL then
         begin
           s1:= mtks_rus_to_lat(s1);
           s2:= mtks_rus_to_lat(s2);
         end;
      comp_eet_FPL4:= s1<s2
    end;

 function comp_stt_FPL4(FPL1,FPL2: PFPL4): bool; far;
    var   res: int;
          r: string;
    begin
      res:=   icao_head_type(FPL1^.stat, r, @hd_ICAO,sizeof(hd_ICAO) div sizeof(Thead_ICAO))
            - icao_head_type(FPL2^.stat, r, @hd_ICAO,sizeof(hd_ICAO) div sizeof(Thead_ICAO));
      if res<>0 then comp_stt_FPL4:= res<0
      else comp_stt_FPL4:= comp_idn_FPL4(FPL1,FPL2)
    end;

 function comp_xxx_FPL4(FPL1,FPL2: PFPL4): bool; far;
    begin
      case comp_FPL4 of
        comp_IDN : comp_xxx_FPL4:= comp_idn_FPL4(FPL1,FPL2);
        comp_INP : comp_xxx_FPL4:= comp_inp_FPL4(FPL1,FPL2);
        comp_EET : comp_xxx_FPL4:= comp_eet_FPL4(FPL1,FPL2);
        comp_STT : comp_xxx_FPL4:= comp_stt_FPL4(FPL1,FPL2);
      end
    end;


 procedure sort_FPL4(p: Pptrs; top: pointer); far;
     begin
       QuickSort(p,@comp_xxx_FPL4,nil,0,int(top^),false)
     end;


{ -----------------------
  Spracovanie FPL4
  -----------------------
}
{ Moze zadat lubovolny let vyhovujuci kriteriam
  alebo len podmnozinu letov dodefinovanych
  podla "select"
}

 type  PFPL4_item_filter = ^TFPL4_item_filter;
       TFPL4_item_filter = record
         key   : Tkey_fpl;
         stt   : p_set_msICAO;
         p_ext : PBFunc_p2;
       end;

 function _filter_cnl_arr (stat: string): bool;
    var   unkn: bool;
    begin
      _filter_cnl_arr:=    (CNL_VYPIS and ((stat=hd_CNL)))
                        or (ARR_VYPIS and (in_icao_head (stat,ms_ICAOact,unkn) or (stat=ht_FLA)))
    end;


 function _kluc_FPL4 (kluc: pstring; _item: PFPL4_item_filter): bool; far;
    var   bres : bool;
          s    : string;
    begin
      _kluc_FPL4:= false;
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
     _kluc_FPL4:= true
   end;


{ "_decodeDBB_FPL4_XY", identifikator/poznamka nesmie byt zrusena
}
 function _stav_FPL4 (buff: PDB_buff; _item: PFPL4_item_filter): bool; far;
    var   FPL: DFPL4;
          s : string;
          p : pchars;
          bres : bool;
    begin
      _stav_FPL4:= false;
      if (_item=nil) then Exit;
      fillchar(FPL,sizeof(FPL),0);

      if (_item^.stt=nil) or (_item^.stt^=[]) then bres:= true
      else begin
             s:= DBstr_to_str_ (buff^[db_fpl4_ine]); p:= @s[1];
             with FPL do incptr(pointer(p), sizeof(rec)+sizeof(date));
             get_s(p, @FPL.stat, sizeof(FPL.stat));
             bres:=    in_icao_head (FPL.stat,_item^.stt^,bres)
                    or _filter_cnl_arr(FPL.stat)
           end;
      if not bres then Exit;

      if (_item^.p_ext<>nil) then
         begin
           s:= DBstr_to_str_ (buff^[db_fpl4_data]); p:= @s[1];
           with FPL do incptr(pointer(p), sizeof(_7)+sizeof(_8)+sizeof(_9)+sizeof(_10));
           get_s(p, @FPL._13[0],sizeof(FPL._13));
           with FPL do incptr(pointer(p), sizeof(_14));
           get_s(p, @FPL._16[0],sizeof(FPL._16));
           bres:= Tfilter_items_DB(_item^.p_ext)(@FPL,_item{^.data_filter})
         end;
      if not bres then Exit;

      _stav_FPL4:= true
    end;


 function _data_FPL4 (FPL: PFPL4; _item: PFPL4_item_filter): bool; far;
    var   F7a,F13a : string;
          bres : bool;
    begin
      _data_FPL4:= false;
      if (_item=nil) then Exit;

      F7a := decode_l4_7a  (FPL^._7);
      F13a:= decode_l4_13a (FPL^._13);

      with _item^.key do
        _data_FPL4:=      ((_7a='')  or (pos(_7a,F7a)=1))
                      and ((_13a='') or (pos(_13a,F13a)=1))
                      and ((_D.r=0)  or (eq_date(_D,FPL^.date)))

                      and (   (   (_item^.stt=nil)
                               or (_item^.stt^=[])
                               or in_icao_head (FPL^.stat,_item^.stt^,bres)
                              )
                           or _filter_cnl_arr(FPL^.stat)
                          )

                      and (   (_item^.p_ext=nil)
                           or Tfilter_items_DB(_item^.p_ext)(FPL,_item{^.data_filter})
                          )
    end;


 function  _spracuj_FPL (_find_data,
                         _process_data,
                         _find_cnl_data,
                         _process_no_data,
                         _ppl,_arch : bool;

                         _key : pstring;
                         _finded_data : pint;

                         _p_ext    : PBFunc_p2;
                         _setfpl   : set_msICAO;
                         _stat     : string;

                         _handler_type : TScrollAct_handler_type;
                         _handler      : pointer;
                         {_handler_par  : pointer;}

                         _title  : string;
                         _hlpXXX : Pchar
                        ): bool;

    var    fn, key : string;
           p_filter : pointer;
           item : TFPL4_item_filter;
           pomb : bool;
           r1,r2 : real;

    label  L;

    begin
      _spracuj_FPL:= false;
      if _finded_data<>nil then _finded_data^:= 1;
      if _key<>nil then _key^:= '';

      if _title='' then _title:= tit_FPL4_PREHLAD;
      if _hlpXXX=nil then _hlpXXX:= hlp_PREHLAD_FPL4;

     { urcenie dat na vyhladanie...
     }
      L:

      p_filter:= nil;
      fillchar(item,sizeof(item),0);
      item.p_ext := _p_ext;
      item.stt   := @_setfpl;

      key:= ''; fn:= '';
      if _find_data or _process_data then
         begin
           {$IFDEF _DPMI} pomb:= true {$ELSE} pomb:= false {$ENDIF};
           if not formular_key_fpl(tit_MASKA, @fn_13a, true,true,pomb,_arch, key) then Exit;
           if _key<>nil then _key^:= key;
           decodekey_fpl (key, item.key._7a,item.key._13a,item.key._D);
           if (cut_(item.key._7a)<>'') or (cut_(item.key._13a)<>'') then
              begin
                p_filter:= @item;
                {_filter:= @_item_filter_FPL4}
              end
           else begin
                  if (_process_no_data) and (_handler_type=_TBFunc_p)
                     then begin
                            TBFunc_p(_handler)(nil);
                            Exit
                          end
                  else {$IFDEF _DPMI} _process_data:= false
                       {$ELSE}        Exit
                       {$ENDIF}
                end
         end;

     { urcenie subora, kde sa ma vyhladavat...
     }
      if (item.key._D.r<>0) then
         begin
           if CheckDate(item.key._D.r,item.key._D.m,item.key._D.d, false) then
              begin
                r1:= DateToSec(year,month,day);
                r2:= DateToSec(item.key._D.r,item.key._D.m,item.key._D.d);
                if (_arch and (r1<=r2)) or ((not _arch) and (r2<r1)) then goto L;
                fn:= get_dbfn(item.key._D, pathFPL,extFPL)
              end
           else goto L
         end
      else begin
             if _ppl then fn:= get_PPL_FN(pathFPL,extFPL,_title)
             else if _arch then fn:= get_ARCH_FN(pathARCH_FPL,extFPL,_title)
             else fn:= get_fn_FPL4;
          end;

     { nacitanie...
     }
      _spracuj_FPL:= scroll_DB_FDP
                          (_title,
                           _process_data,_find_cnl_data,true,
                           _finded_data,

                           max_FPL4s, sizeof(DFPL4),
                           @new_FPL4,nil,@disp_FPL4,@eq_FPL4,

                           key, @read_FPL4,

                           p_filter,
                           @_kluc_FPL4,
                           @_stav_FPL4,
                           nil,
                           @_data_FPL4,

                           true, @sort_FPL4, nil,
                           _handler_type,_handler,nil{_handler_par},
                           nil,nil,nil, {$IFDEF PRN}@print_FPL4s{$ELSE}nil{$ENDIF},nil,

                           fn, nil,nil,
                           db_FPL4_RIADKOV,@decodeDB_FPL4, nil{@dbchg_FPL4},

                           dxi_FPL4, dyi_FPL4, @plan_FPL4,

                           nil,_hlpXXX,

                           @p_fpl4_dbscroller
                          );
    end;
