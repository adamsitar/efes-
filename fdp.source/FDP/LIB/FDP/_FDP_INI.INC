procedure PLANY_init;
    begin

     {$IFDEF FDR}
      oFDR:= New(POFDR,Init(max_FDRs));
     {$ENDIF}

     {$IFDEF FPL0}
      cFPL:= New(PcFPL, Init(max_cFPLs,true,{$IFDEF PRN_STRIP} PRN_cFPL {$ELSE} c_false {$ENDIF},
                             {$IFDEF EDD}
                               true, @winACC,
                               cm_add_ACC_PLAN, cm_chg_ACC_PLAN, cm_del_ACC_PLAN, cm_clr_ACC_PLAN,
                             {$ENDIF}

                             @formular_cFPL_,
                             @handle_strip_FPLc {@handle_strip_FPLc_BvEp3,@edd_handle_strip_FPL_BvEp3}
                             )
                            );

     {$IFNDEF FPLM_DISABLED}
      mFPL:= New(PmFPL, Init(max_mFPLs,true,{$IFDEF PRN_STRIP} PRN_mFPL {$ELSE} c_false {$ENDIF},
                             {$IFDEF EDD}
                               true, @winACC,
                               cm_add_ACC_PLAN, cm_chg_ACC_PLAN, cm_del_ACC_PLAN, cm_clr_ACC_PLAN,
                             {$ENDIF}

                             {$IFDEF OPL}
                               @_preactived_FPLM,  @_preactived_FPLM_ot,
                               @_proposed_FPLM,    @_proposed_FPLM_ot,
                               @_coordinated_FPLM, @_coordinated_FPLM_ot,
                                                   @_activated_FPLM_ot,

                               @_propose_dayFPLM, @_unactive_dayFPLM,
                             {$ENDIF}

                             @formular_mFPL_,
                             @handle_strip_FPLm
                             )
                            );

       {$IFDEF FPLO}
        oFPL:= New(PaFPL, Init(max_oFPLs,true,{$IFDEF PRN_STRIP} PRN_oFPL {$ELSE} c_false {$ENDIF},

                               {$IFDEF EDD}
                                 true, @winACC,
                                 cm_add_ACC_PLAN, cm_chg_ACC_PLAN, cm_del_ACC_PLAN, cm_clr_ACC_PLAN,
                               {$ENDIF}

                               {$IFDEF OPL}
                                 @_preactived_FPLO,  @_preactived_FPLO_ot,
                                 @_proposed_FPLO,    @_proposed_FPLO_ot,
                                 @_coordinated_FPLO, @_coordinated_FPLO_ot,
                                                     @_activated_FPLO_ot,

                                 @_propose_dayFPLM,  @_unactive_dayFPLM,
                               {$ENDIF}

                               @formular_mFPL_,
                               @handle_strip_FPLm
                               )
                              );
        {$ENDIF}
        {$ENDIF}

        {$IFDEF EDD}
         PROP_cFPL:= New(PcFPL, Init(max_PROP_cFPLs,false,c_false,
                                     false, @winPROP,
                                     cm_add_PROP_PLAN, cm_chg_PROP_PLAN, cm_del_PROP_PLAN, cm_clr_PROP_PLAN,
                                     nil,nil{@formular_cFPL_})
                                    );
         PROP_cFPL^.p_strip_draw:= @prop_strip_cFPL;
         PROP_cFPL^.p_PRN2:= @c_false;

         PROP_mFPL:= New(PmFPL, Init(max_PROP_mFPLs,false,c_false,
                                     false, @winPROP,
                                     cm_add_PROP_PLAN, cm_chg_PROP_PLAN, cm_del_PROP_PLAN, cm_clr_PROP_PLAN,
                                     nil,nil{@formular_mFPL_})
                                    );
         PROP_mFPL^.p_strip_draw:= @prop_strip_mFPL;
         PROP_mFPL^.p_PRN2:= @c_false;

        {$IFDEF FPLO}
         PROP_oFPL:= New(PaFPL, Init(max_PROP_oFPLs,false,c_false,
                                     false, @winPROP,
                                     cm_add_PROP_PLAN, cm_chg_PROP_PLAN, cm_del_PROP_PLAN, cm_clr_PROP_PLAN,
                                     nil,nil{@formular_mFPL_})
                                    );
         PROP_oFPL^.p_strip_draw:= @prop_strip_mFPL;
         PROP_oFPL^.p_PRN2:= @c_false;
        {$ENDIF}
       {$ENDIF}

      {$ENDIF}

      {$IFDEF ZAM}
       ZAMs:= New(POZAM, Init({$IFDEF EDD} {$IFDEF TABLET_ZAM}
                                @winACC, cm_add_ACC_PLAN, cm_chg_ACC_PLAN, cm_del_ACC_PLAN, cm_clr_ACC_PLAN,
                               {$ENDIF} {$ENDIF}
                               nil
                              )
                  );
      {$ENDIF}

      {$IFDEF PRS}
       PRSs:= New(POPRS, Init({$IFDEF EDD} {$IFDEF TABLET_PRS}
                                @winACC, cm_add_ACC_PLAN, cm_chg_ACC_PLAN, cm_del_ACC_PLAN, cm_clr_ACC_PLAN,
                               {$ENDIF} {$ENDIF}
                               nil
                              )
                  );
      {$ENDIF}

      SaveMainA:= ACheckProcessesA;
      ACheckProcessesA:= checkA_FDP;

      SaveMainD:= ACheckProcessesD;
      ACheckProcessesD:= checkD_FDP
    end;


procedure PLANY_done;
    begin
     {$IFDEF PRS}
      if PRSs<>nil then begin Dispose(PRSs,Done); PRSs:= nil; end;
     {$ENDIF}

     {$IFDEF ZAM}
      if ZAMs<>nil then begin Dispose(ZAMs,Done); ZAMs:= nil; end;
     {$ENDIF}

     {$IFDEF FPL0}
       if cFPL<>nil then begin Dispose(cFPL,Done); cFPL:= nil; end;
      {$IFNDEF FPLM_DISABLED}
       if mFPL<>nil then begin Dispose(mFPL,Done); mFPL:= nil; end;
       {$IFDEF FPLO}
        if oFPL<>nil then begin Dispose(oFPL,Done); oFPL:= nil; end;
       {$ENDIF}
      {$ENDIF}

      {$IFDEF EDD}
       if PROP_cFPL<>nil then begin Dispose(PROP_cFPL,Done); PROP_cFPL:= nil; end;
       if PROP_mFPL<>nil then begin Dispose(PROP_mFPL,Done); PROP_mFPL:= nil; end;
       {$IFDEF FPLO}
        if PROP_oFPL<>nil then begin Dispose(PROP_oFPL,Done); PROP_oFPL:= nil; end;
       {$ENDIF}
      {$ENDIF}
     {$ENDIF}

     {$IFDEF FDR}
       if oFDR<>nil then begin Dispose(oFDR,Done); oFDR:= nil end;
     {$ENDIF}
    end;


{$IFDEF TRENAZER} {$DEFINE NO_ARCHIV} {$ENDIF}

{ Spolocne nacitanie planov, az po
  inicializacii vsetkych struktur
  programu
}

 procedure PLANY_load;

     const semaphor  : bool = false;
           den       : byte = 0;

     var   fn_1,fn_2 : string;
           b1,b3 : bool;
           {$IFDEF FPL0}
            iPc,iPm,iPo : P_OFPL;
           {$ENDIF}
           i : int;
           b : byte;

     begin
       if semaphor then Exit;
       semaphor:= true;

       {$IFDEF DEMO}
        if initialize_fdp_records then den:= 0;
        initialize_fdp_records:= false;
       {$ENDIF}


       {$IFDEF MAPY}
        b3:= MAPY_DRAW_en; MAPY_DRAW_en:= false;
       {$ENDIF}
       b1:= __INFO_DB; __INFO_DB:= true;

       {$IFNDEF NO_ARCHIV}
         if den=0 then
            begin

            {$IFDEF FDR}
              if not oFDR^.preaktivovanie then {LoadDB(load_FDR(get_fn_FPL4,)};
            {$ENDIF}

            {$IFDEF FPL0}
              iPc:= cFPL;
              {$IFNDEF FPLM_DISABLED}
               iPm:= mFPL;
              {$IFDEF FPLO} iPo:= oFPL; {$ELSE} iPo:= nil; {$ENDIF}
              {$ENDIF}
              {$IFDEF EDD}
               if (den=0) and (is_ParamStr(psLOAD_PROPOSED)<>'') then
                  begin
                    iPc:= PROP_cFPL;
                    {$IFNDEF FPLM_DISABLED}
                     iPm:= PROP_mFPL;
                     {$IFDEF FPLO} iPo:= PROP_oFPL; {$ELSE} iPo:= nil; {$ENDIF}
                    {$ENDIF}
                  end;
              {$ENDIF}

              archiv_HODfn:= get_PLANhod(day,month,year, hour);
              fn_1:= get_prev_HODfn(archiv_HODfn);
              fn_2:= get_prev_HODfn(fn_1);

              iPc^.LoadDB(pathFPL_C+fn_2, false,true{false},iPc^.tit_preactivate);
              iPc^.LoadDB(pathFPL_C+fn_1, false,true,iPc^.tit_preactivate);
              { IFNDEF DEMO}
               iPc^.LoadDB(pathFPL_C+archiv_HODfn,false,true,iPc^.tit_preactivate);
              { ENDIF}

              {$IFNDEF FPLM_DISABLED}
               if not mFPL^.preaktivovanie then load_mFPL(get_fn_mFPL_let, iPm,iPo);
              {$ENDIF}
             {$ENDIF}
            end;
       {$ENDIF}

       {$IFDEF MAPY}
        MAPY_DRAW_en:= b3;
        if b3 then OBNOV_MAPU:= true;
       {$ENDIF}
       __INFO_DB:= b1;

       {if den=0 then INITIALIZE_EN:= read_cfg_bool(SYSTEMcfg,cfg_INITIALIZE_EN,true);
       den:= day;}

      { nacitanie preaktivucich sa planov
      }
       pozri_spracovanie_planov_;

       semaphor:= false
     end;

{$UNDEF NO_ARCHIV}