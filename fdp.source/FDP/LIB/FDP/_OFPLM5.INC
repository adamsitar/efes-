{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                          €
€ TmFPL                                    €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
{ kvoli vypoctu a alokovaniue trate
}

 procedure OmFPL.format_data_variables (p: pointer);
      var   FPL : PDmFPL;
            b   : bool;
      begin
        FPL:= PDmFPL(p);
        format_mFPL_trat (FPL);
        with FPL^ do
          begin
            {if (trat_=nil) then decode_trat_FPLM (FPL, trat_,bodov, false,true,false);
            stav_mFPL(p,absTime,b);}
            cl:= get_stat_cl(stat)
          end;
        inherited format_data_variables(p);
      end;


 constructor OmFPL.Init(_items  : word;
                        _en_net : bool;

                        var _p_PRN : bool;

                        {$IFDEF EDD}
                         _accepted : bool;
                         _adrBOARD : PPObject;
                         _cmADD,_cmCHG,_cmDEL,_cmCLR: word;
                        {$ENDIF}

                        {$IFDEF OPL}
                         _p_pre_i, _p_pre_iot,
                         _p_pro_i, _p_pro_iot,
                         _p_coo_i, _p_coo_iot,
                                   _p_act_iot,

                         _p_prop_day, _p_cnl_day : pbool;
                        {$ENDIF}

                        _p_formular : pointer;
                        _p_handler  : pointer
                       );

       begin
         inherited Init(_items,sizeof(DmFPL),
                        @new_mFPL,@format_mFPL_,@disp_mFPL,

                        @eq_mFPL, @idn_mFPL,@ssr_mFPL,@chg_mFPL,@stav_mFPL,@est_mFPL,
                        @distribute_rdp_mFPL,@send_mFPL,_en_net,

                        @sc_mFPL, dx_mFPL,dyf_mFPL,
                        @dx_sc_mFPL,@dy_sc_mFPL,
                        nil,

                        {$IFDEF MAPY}
                          @zobraz_trat_mFPL,
                          @draw_mFPLtrgt,@draw_mFPL_en,
                          cl_mFPL,cl_trat_mFPL,
                        {$ENDIF}

                        {$IFDEF EDD}
                          _accepted,
                          _adrBOARD, _cmADD,_cmCHG,_cmDEL,_cmCLR,
                          @strip_mFPL,
                          fplMIL,
                        {$ENDIF}

                        _p_PRN, {$IFDEF PRN} @print_mFPL {$ELSE} nil {$ENDIF},

                        @save_mFPL,
                        @info_mFPL,
                        _p_formular,
                        @comp_idn_mFPL,
                        _p_handler,

                        @get_fn_mFPL_let, @decodeDB_FPLM,
                        db_mFPL_RIADKOV,
                        @codekey_FPLM,

                        @dt_propose_FPLM,@dT_unactive_FPLM,@dT_deactive_FPLM,
                        {$IFDEF FDP_OPL} true {$ELSE} false {$ENDIF},

                        hlp_PREHLAD_mFPL
                       );


         add_pos:= poz_est_FPLM;
         {$IFDEF FDP_EDD} {$IFNDEF IDD}
           add_pos:= pozACT;
         {$ENDIF} {$ENDIF}

         p_message:= @message_mFPL;
         {p_spracuj:= @_spracuj_mFPL;}

         fn_dir:= path_A; fn_ext:= ext_mFPL;

         {$IFDEF OPL}
          add_pos:= pozACT;

          p_pre_i:= _p_pre_i;  p_pre_iot:= _p_pre_iot;
          p_pro_i:= _p_pro_i;  p_pro_iot:= _p_pro_iot;
          p_coo_i:= _p_coo_i;  p_coo_iot:= _p_coo_iot;
                               p_act_iot:= _p_act_iot;

          p_prop_day:= _p_prop_day; p_cnl_day:= _p_cnl_day;


          pre_i:= get_pbool(p_pre_i,false);  pre_iot:= get_pbool(p_pre_iot,false);
          pro_i:= get_pbool(p_pro_i,false);  pro_iot:= get_pbool(p_pro_iot,false);
          coo_i:= get_pbool(p_coo_i,false);  coo_iot:= get_pbool(p_coo_iot,false);
                                             act_iot:= get_pbool(p_act_iot,false);

          prop_day:= get_pbool(p_prop_day,false);
          cnl_day:= get_pbool(p_cnl_day,false);
         {$ENDIF}
       end;


 procedure OmFPL.plan_added(p: pointer);
    begin
      inherited plan_added(p);
      {$IFDEF REPORT_FPLM_ARW}
        pozri_nevydane_spravy_FPLM_ARR(true)
      {$ENDIF}
    end;

 procedure OmFPL.plan_deleted;
    begin
      inherited plan_deleted;
      {$IFDEF REPORT_FPLM_ARW}
        pozri_nevydane_spravy_FPLM_ARR(true)
      {$ENDIF}
    end;
