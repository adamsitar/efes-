{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                          €
€ TFDR                                     €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
{ kvoli vypoctu a alokovaniue trate
}

 procedure TOFDR.format_data_variables (p: pointer);
     begin
       dealloc_FDRrte(PFDR(p)^.rte,PFDR(p)^.bodov);
     end;


 constructor TOFDR.Init (_items : word);
       begin
         inherited Init (_items,sizeof(DFDR),
                     @new_FDR,nil,@disp_FDR,

                     @eq_FDR, @idn_FDR,@ssr_FDR,@chg_FDR,@stav_FDR,nil,
                     nil,nil{send...az ked budu FPL4 v pamati},false,

                     @plan_FDR, dx_FDR_plan,dy_FDR_plan,nil,nil,nil,
                     {$IFDEF MAPY} nil,nil,nil,0,0, {$ENDIF}
                     {$IFDEF EDD} false,nil,0,0,0,0,nil,'', {$ENDIF}
                     c_false, nil,

                     nil{@save_FDR},@info_FDR,
                     nil{_p_formular},
                     @comp_xxx_FDR,
                     @handle_plan_FDR,
                     @get_fn_FPL4, @decodeDB_FDR,
                     db_FPL4_RIADKOV,
                     @codekey_FDR,

                     @dT_preactive_FPL4,@dT_unactive_FPL4,@dT_deactive_FPLC, true,

                     hlp_PREHLAD_FPL4
                    );

         denny_subor:= true;
         add_pos:= poz_est_FDR;

         fn_dir:= path_A;
         fn_ext:= extFPL;

         item_medzera:= 2; item_dxi:= 2; item_dyi:= 2; item_bg:= __bg;

         {is_to_ACTivate:= false;
         s_ACT:= false; s_PREACT:= false;}
         tit_preactivate:= tit_FPL4prea
       end;


 function TOFDR.get_poz(p: pointer): Tpoz;
    begin
      get_poz:= PFDR(p)^.poz
    end;


 function is_FDRprop (FDR: PFDR; p: pointer): bool;
    begin
      is_FDRprop:= FDR^.poz = poz_PREACTIVE
    end;

 function is_FDRcoor (FDR: PFDR; p: pointer): bool;
    begin
      is_FDRcoor:=  FDR^.poz = poz_PROPOSED
    end;


 function TOFDR.zmena_platnosti(z0,z1: Tpoz): bool;
    begin
      zmena_platnosti:= ((z0=poz_PREACTIVE) or (z0=poz_PROPOSED)) and (z0<>z1)
    end;
