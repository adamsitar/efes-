 function comp_idn_PLN(PLN1,PLN2: PPLN): bool; far;
    var   s1,s2: string;
    begin
      s1:= PLN1^.idn + PLN1^.dep.kod + code_l4_utc(PLN1^.dep.h,PLN1^.dep.m);
      s2:= PLN2^.idn + PLN2^.dep.kod + code_l4_utc(PLN2^.dep.h,PLN2^.dep.m);
      if not RUSSIAN_FPD then
         begin
           s1:= mtks_rus_to_lat(s1);
           s2:= mtks_rus_to_lat(s2);
         end;
      comp_idn_PLN:= s1 < s2
    end;

 procedure sort_PLN(p: Pptrs; top: pointer); far;
     begin
       QuickSort(p,@comp_idn_PLN,nil,0,int(top^),false)
     end;


 procedure spracuj_PLN(FN : string);
     begin
       scroll_DB_FDP(tit_PLN_PREHLAD,
                     false,false,true,nil,
                     max_PLNs,sizeof(DPLN),
                     @new_PLN,nil,@disp_PLN,@eq_PLN,
                     '',nil,
                     nil,nil,nil,nil,nil,                          {_data_filter,_filter,}
                     true, @sort_PLN,nil,
                     _TNull,nil,nil,                               {_handler_type,_handler,_handler_par,}
                     nil,nil,nil, {$IFDEF PRN}@print_PLNs{$ELSE}nil{$ENDIF},nil,

                     FN,nil,nil,                                   {_FNfunc, _FNfunc_p,}
                     db_PLN_RIADKOV,@decodeDB_PLN, @dbchg_PLN,

                     dx_plan_PLN, dy_plan_PLN, @_plan_PLN,
                     nil,hlp_PREHLAD_PLN,
                                                {_info, _hlpXXX}
                     @p_pln_dbscroller
                    )
     end;


 procedure prehlad_PLN(ppl: bool);
     var   FN : string;
     begin
       if ppl then FN:= get_PPL_FN(pathFPL,extPLN,'PLN')
       else FN:= get_DBfn_(day,month,year, pathFPL, extPLN);
       spracuj_PLN(FN)
     end;

 procedure prehlad_PLN_ARCH;
     begin
       spracuj_PLN(get_ARCH_FN(pathARCH_FPL, extPLN, 'PLN ARCHIV'))
     end;


 (*
 { Prehlad PLN a ich pripadne vytlacenie alebo vyhladanie prislusneho FPL

   TBFunc_vEp3(handle_buttons)(_Event,@Self,handler_owner,handler_data)
 }

 procedure init_prehlad_PLN_bt (H: PHelp); far;
     var   bt1 : PTextIcon;
           bt2 : PbtTCancel;
           bt3 : PDialogButton;
           xt,yt, yi,c : int;
     begin
       with H^ do
         begin
          {IFDEF PRN
            yi:= 0;
            Win^.get_btXY(1,yi, xt,yt);
            bt3:= New(PDialogButton,Init(Win, xt,yt, kbAltR,cmPrint,'P~r~int',icKey,icText));
            inc(yi);
          ENDIF}
         end
     end;

 {
  TBFunc_vEp3(handle_buttons)(_Event,@Self,handler_owner,handler_data)
 }
 function  handle_prehlad_PLN (var Ev : TEvent;
                               H : PHelp;
                               O : pointer;
                               p : pointer
                              ): bool; far;
    var    msg: string;
    begin
      handle_prehlad_PLN:= true;
    end;


 procedure prehlad_PLN(ppl: bool);
     var   title, FN : string;
     begin
       title:= titVIEW+'PLN';
       if ppl then FN:= get_PPL_FN(pathFPL,extPLN,title)
       else FN:= get_DBfn_(day,month,year, pathFPL, extPLN);
       _info_(FN,title+' ('+get_plan_date_str(FN)+')',
              0{dbtWIDTH+10},dbtHEIGHT+10,
              @init_prehlad_PLN_bt,@handle_prehlad_PLN,nil
             )
     end;


 procedure prehlad_PLN_ARCH;
     var   title, FN : string;
     begin
       title:= titVIEW_A+'PLN';
       FN:= get_ARCH_FN(pathARCHIV_FPL, extPLN, 'ARCHIV', true,true); {nil,nil,}
       _info_(FN,title+' ('+get_plan_date_str(FN)+')',
              0{dbtWIDTH+10},dbtHEIGHT+10,
              @init_prehlad_PLN_bt,nil,nil
             )
     end;
 *)
