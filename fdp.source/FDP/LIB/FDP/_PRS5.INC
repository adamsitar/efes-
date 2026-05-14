{ ----------------------------------------------
   OBJEKT PRE PRE(AKTIV(OVA)NE PLANY PRIESTOROV
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

constructor TOPRS.Init({$IFDEF EDD} {$IFDEF TABLET_PRS}
                        _adrBOARD : PPObject; _cmADD,_cmCHG,_cmDEL,_cmCLR : word;
                       {$ENDIF} {$ENDIF}
                       nic: pointer
                      );
      begin
        inherited Init(max_PRS,SizeOf(TPRS),
                       @new_PRS,nil,@disp_PRS,

                       @eq_PRS,@idn_PRS,@chg_PRS,@stav_PRS,@est_PRS,
                       @distribute_rdp_PRS,@send_PRS,true,

                       @sc_PRS,    dxf_PRS,dyf_PRS,
                       @dx_sc_PRS, @dy_sc_PRS,
                       nil,

                       {$IFDEF MAPY} nil, {$ENDIF}

                       {$IFDEF EDD}
                        {$IFDEF TABLET_PRS}
                         _adrBOARD, _cmADD,_cmCHG,_cmDEL,_cmCLR,
                          fplPRS, @strip_PRS, @handle_PRS_strip,
                        {$ELSE}
                          nil, _cmADD,_cmCHG,_cmDEL,_cmCLR,
                          '', nil,nil,
                        {$ENDIF}
                       {$ENDIF}

                       c_false, {$IFDEF PRN} @print_PRS {$ELSE} nil {$ENDIF},

                       @save_PRS,
                       @info_PRS,
                       nil,
                       @comp_PRS,
                       @handle_PRS_object,

                       @get_dbPRSfn, @decodeDB_PRS,
                       db_PRS_RIADKOV,
                       @codekey_PRS,

                       @dt_propose_PRS,@dt_unactive_PRS,@dt_deactive_PRS,
                       true,

                       nil
                      );

        add_pos:= poz_est_PRS;
        p_message:= @message_PRS;

        {$IFDEF MAPY} {$IFNDEF MAPY_1.0}
         {p_id_map:= @id_map_PRS;}
         p_GrOb:= @new_GP_PRS;
         typ_mapy:= map_PRSp;
        {$ENDIF} {$ENDIF}

        fn_dir:= path_A; fn_ext:= extPRS;

        tit_preactivate:= tit_PRSprea
      end;


function  TOPRS.get_flag (p: pointer; group: byte): byte;
    begin
      get_flag:= 0
    end;

procedure TOPRS.set_flag (p: pointer; group,flag: byte);
    begin
     if group = gr_map then PPRS(p)^.f_map:= flag
    end;


function TOPRS.get_poz(p: pointer): Tpoz;
   begin
     get_poz:= TPRS(p^).poz
   end;


{$IFDEF NET}
  function TOPRS.get_rec(p: pointer): Pplan_rec;
     begin
       get_rec:= @TPRS(p^).rec
     end;
{$ENDIF}


function  TOPRS.nacitanie_zo_vcera(limit_add : real): bool;
   begin
     nacitanie_zo_vcera:= inherited nacitanie_zo_vcera(limit_add)
                          {$IFDEF FUA}
                            and ((not cas_FUA_24H_EN) or (hour<cas_PRS_zac))
                          {$ENDIF}
   end;
