{ -------------------
  prehlad
  statistiky
  -------------------
}
 function comp_FPS (FPS1,FPS2: PFPS): bool; far;
    var   s1,s2: string;
    begin
      with FPS1^.fdr do s1:= idn+dep.kod+code_l4_utc(dep.h,dep.m);
      with FPS2^.fdr do s2:= idn+dep.kod+code_l4_utc(dep.h,dep.m);
      if not RUSSIAN_FPL then
         begin
           s1:= mtks_rus_to_lat(s1);
           s2:= mtks_rus_to_lat(s2);
         end;
      comp_FPS:= s1<s2
    end;

 procedure prehlad_FPLS (_arch: bool);
     var   FN  : string;
           tit : string;
     begin
       if _arch then
          begin
            FN:= get_ARCH_FN(pathARCH_FPS, extFPS, tit_ARCHIV);
            tit:= mnu_ARCHIV_STATISTIKY_PRELETOV;
          end
       else begin
              FN:= get_DBfn_(day,month,year, pathFPS, extFPS);
              tit:= mnu_DENNA_STATISTIKA_PRELETOV
            end;
       scroll_DB_FDP(delchar(tit,[cnst_HotKey]),
                     false,false,true,nil,
                     max_FDRs, sizeof(DFPS),
                     @new_FPS,nil,@disp_FPS,@eq_FPS,

                     '',nil,
                     nil,nil,nil,@_valid_FPS,nil,
                     true, nil, @comp_FPS,
                     _TBFunc_vEp2,@handle_FPS_list,nil,
                     @init_FPS_buttons,@handle_FPS_buttons,nil,
                     {$IFDEF PRN}@print_FPSs{$ELSE}nil{$ENDIF},nil,

                     FN, nil,nil,
                     db_FPS_RIADKOV,@decodeDB_FPS, @dbchg_FPS,

                     dx_plan_FPS, dy_plan_FPS, @plan_FPS,
                     nil, hlp_STA_FPLC,

                     @p_sta_dbscroller
                    )
     end;


