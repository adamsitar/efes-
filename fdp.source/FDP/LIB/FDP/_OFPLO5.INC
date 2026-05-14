{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ iny letovy plan                                          €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

{$IFDEF FPLO}

 constructor OaFPL.Init(_items  : word;
                        _en_net : bool;

                        var _p_PRN   : bool;

                        {$IFDEF EDD}
                         _accepted : bool;
                         _adrBOARD : PPObject;
                         _cmADD,_cmCHG,_cmDEL,_cmCLR : word;
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
         inherited Init(_items,_en_net,_p_PRN,

                        {$IFDEF EDD}
                         _accepted,
                         _adrBOARD, _cmADD,_cmCHG,_cmDEL,_cmCLR,
                        {$ENDIF}

                        {$IFDEF OPL}
                         _p_pre_i, _p_pre_iot,
                         _p_pro_i, _p_pro_iot,
                         _p_coo_i, _p_coo_iot,
                                   _p_act_iot,

                         _p_prop_day, _p_cnl_day,
                        {$ENDIF}

                         _p_formular,
                         _p_handler
                       );

         p_est:= @est_oFPL;

         {$IFDEF MAPY}
           draw_trgt:= @draw_oFPLtrgt; ciele_en:= @draw_oFPL_en;
           cl_ciel:= cl_oFPL; cl_trat:= cl_trat_oFPL;
         {$ENDIF}

         {$IFDEF EDD}
           skupina:= fplFPL;
         {$ENDIF}
       end;


 function  OaFPL.is_plan(p: pointer): bool;
    begin
      is_plan:= is_oFPL(PDmFPL(p))
    end;


 {$IFDEF EDD}
   function OaFPL.zarad (ind: int; is: TSpecGroups): string;
      begin
        zarad:= '';
        if PDmFPL(ap^[ind])^.poz<=poz_START then Exit;

        zarad:= fplFPL
      end;

   function OaFPL.smer (ind: int): Ts_dir;
      begin
        smer:= dir_fpo{_dir_mFPL(PDcFPL(ap^[ind])^)}
      end;
 {$ENDIF}

{$ENDIF}

