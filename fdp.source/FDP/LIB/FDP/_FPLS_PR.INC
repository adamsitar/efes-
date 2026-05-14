
 procedure prehlad_mFPL (all: bool; ppl: bool; stat: string);
     var   title, FN : string;
     begin
       title:= titVIEW+' FPL';
       if not all then
          begin
           {$IFDEF AIRBASE} title:= title+'/'+this_airbase
           {$ELSE}          all:= true
           {$ENDIF}
          end;

       spracuj_mFPL(false,find_and_process_data,
                    ppl,false,false,true,
                    {cnl_stat}(stat), _sw_stat_us(all,@_is_stata_FPLm,@_is_plan_FPLm),
                    @handle_plan_FPLm, _TBFunc_vEp2,
                    true,not all,
                    title, nil, hlp_zoznam
                   );

       if all and (not ppl) then isFPLM:= false
     end;


 procedure prehlad_mFPL_ARCH (all: bool);
     begin
       spracuj_mFPL(false,find_and_process_data,
                    false,true,false,true,
                    '',_sw_stat_us(all, @_is_stata_FPLm,@_is_plan_FPLm),
                    {$IFDEF PROCESS_FPLM} @handle_DB_list_2, _TBFunc_p2,
                    {$ELSE} {$IFDEF DISABLED_ETO_FPLm} nil, _TNull,
                    {$ELSE} @handle__spracuj_ukoncene_mFPL, _TBFunc_p,
                    {$ENDIF} {$ENDIF}
                     true,false,
                     tit_arch_mFPL, nil,
                     hlp_zoznam
                    )
     end;


(* procedure prehlad_oFPL_ARCH (all: bool);
     begin
       spracuj_mFPL(false,find_and_process_data,
                    false,true,false,true,
                    '', _sw_stat_us(all, @_is_stata_FPLo,@_is_plan_FPLo),
                    {$IFDEF PROCESS_FPLM} @handle_DB_list_2, _TBFunc_p2,
                    {$ELSE} {$IFDEF DISABLED_ETO_FPLm} nil, _TNull,
                    {$ELSE} @handle__spracuj_ukoncene_mFPL, _TBFunc_p,
                    {$ENDIF} {$ENDIF}
                     true,false,
                     tit_arch_mFPL, nil,
                     hlp_zoznam
                    )
     end;
*)

 procedure prehlad_mFPL_ine;
     begin
       spracuj_mFPL(false,false,
                    false,false,false,true,
                    '', @_is_stat_FPLm_ine,
                    @handle_plan_FPLm, _TBFunc_vEp2,
                    true,false,
                    titVIEW+msg_LET_PLAN,
                    nil,hlp_zoznam
                   )
     end;


 function _is_stat_FPLm_plan (FPL: PDmFPL; ps: Pstring): bool; far;
    var   s: string;
    begin
      s:= {cnst_disk+cnst_sended+cnst_cnl}cnl_stat(cnst_planned_);
      _is_stat_FPLm_plan:=       _is_stat_FPLm(FPL,@s)
                            and  (pos(cnst_finish,FPL^.stat)=0)
    end;

 procedure prehlad_mFPL_plan;
     begin
       spracuj_mFPL(false,false,
                    false,false,false,true,
                    '', @_is_stat_FPLm_plan,
                    @handle_plan_FPLm, _TBFunc_vEp2,
                    true,false,
                    titVIEW+msg_LET_PLAN,
                    nil,hlp_zoznam
                   )
     end;



 procedure prehlad_mFPL_acc;
     begin
       spracuj_mFPL(false,false,
                    false,false,false,true,
                    cnst_prop+cnst_acc+cnst_dec, @_is_stat_FPLm,
                    @handle_plan_FPLm, _TBFunc_vEp2,
                    true,false,
                    titVIEW+msg_LET_PROP,
                    nil,hlp_zoznam
                   )
     end;


 procedure prehlad_mFPL_dep;
     begin
       spracuj_mFPL(false,false,
                    false,false,false,true,
                    cnst_stat_act, @_is_stat_FPLm,
                    @handle_plan_FPLm, _TBFunc_vEp2,
                    true,false,
                    titVIEW+msg_LET_DEP,
                    nil,hlp_zoznam
                   )
     end;


 procedure prehlad_mFPL_arr;
     var   p: pointer;
     begin
       spracuj_mFPL(false,false,{find_and_process_FPLM,find_and_process_FPLM,}
                    false,false,false,true,
                    cnst_stat_arr, @_is_stat_FPLm,
                    @handle_plan_FPLm, _TBFunc_vEp2,
                    true,false,
                    titVIEW+msg_LET_ARR,
                    nil,hlp_zoznam
                   )
     end;


 procedure prehlad_mFPL_vsetky;
     begin
       spracuj_mFPL(false,false,
                    false,false,false,true,
                    '', @_is_stat_FPLm,
                    @handle_plan_FPLm, _TBFunc_vEp2,
                    true,false,
                    titVIEW+msg_LET_PLAN,
                    nil,hlp_zoznam
                   )
     end;
