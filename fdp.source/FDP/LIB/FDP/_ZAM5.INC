{function _formular_ZAM(p: pointer; tit: string): bool; far;
   begin
     _formular_ZAM:= formular_ZAM(p, true, false, '', tit)
   end;}


constructor TOZAM.Init({$IFDEF EDD} {$IFDEF TABLET_ZAM}
                        _adrBOARD : PPObject; _cmADD,_cmCHG,_cmDEL,_cmCLR : word;
                       {$ENDIF} {$ENDIF}
                       nic: pointer
                      );
      begin
        inherited Init(max_ZAM,SizeOf(TZAM),
                       @new_ZAM,nil,@disp_ZAM,

                       @eq_ZAM,@idn_ZAM,@chg_ZAM,@stav_ZAM,@est_ZAM,
                       nil{@distribute_rdp_ZAM},@send_ZAM,true,

                       @sc_ZAM,    dx_ZAM,dy_ZAM,
                       @dx_sc_ZAM, @dy_sc_ZAM,
                       {@plan_ZAM, dx_ZAM,dy_ZAM,
                       nil,nil,}
                       nil,

                       {$IFDEF MAPY} nil, {$ENDIF}

                       {$IFDEF EDD}
                        {$IFDEF TABLET_ZAM}
                         _adrBOARD, _cmADD,_cmCHG,_cmDEL,_cmCLR,
                          fplZAM, @strip_ZAM, @handle_ZAM_strip
                        {$ELSE}
                          nil, _cmADD,_cmCHG,_cmDEL,_cmCLR,
                          '', nil, nil
                        {$ENDIF},
                       {$ENDIF}

                       c_false, {$IFDEF PRN} @print_ZAM {$ELSE} nil {$ENDIF},

                       @save_ZAM,
                       @info_ZAM,
                       nil{@_formular_ZAM},
                       @comp_ZAM,
                       @handle_ZAM_object,

                       @get_dbZAMfn, @decodeDB_ZAM,
                       db_ZAM_RIADKOV,
                       @codekey_ZAM,

                       @dt_propose_ZAM,@dt_unactive_ZAM,@dt_deactive_ZAM,
                       true,

                       nil);

        add_pos:= poz_est_ZAM;
        p_message:= @message_ZAM;

        fn_dir:= path_A; fn_ext:= extZAM;

       {$IFDEF MAPY} {$IFNDEF MAPY_1.0}
        {p_id_map:= @id_map_ZAM;}
        p_GrOb:= @new_GP_ZAM;
        tit_GrOb:= err_TMA_NOT_FOUND+cstr(polomer_ZAM,1)+' km.';
        typ_mapy:= map_ZAMp;
       {$ENDIF} {$ENDIF}

        tit_preactivate:= tit_ZAMprea
      end;


{function  TOZAM.get_flag (p: pointer; group: byte): byte; virtual;
    begin
      get_flag:= 0
    end;


procedure TOZAM.set_flag (p: pointer; group,flag: byte); virtual;
    begin
     if group = gr_map then f_map:= flag
    end;
}
 function TOZAM.get_poz(p: pointer): Tpoz;
    begin
      get_poz:= TZAM(p^).poz
    end;

 {$IFDEF NET}
  function TOZAM.get_rec(p: pointer): Pplan_rec;
     begin
       get_rec:= @TZAM(p^).rec
     end;
 {$ENDIF}
