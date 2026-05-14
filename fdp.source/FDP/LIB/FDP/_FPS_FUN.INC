{ -------------------
  zaradenie spravy
  do statistiky,
  -------------------
}
 procedure code_FPLC_FPS(const FPC: DFPLC; var FPS: DFPS);
     var   s,t,u: string;
     begin
       fillchar(FPS,sizeof(FPS),0);
       FPS.fdr.idn := FPC.idn;

       {decode_l4_9 (FPC.typ, s,t,u);
       FPS.fdr.typ := s+t;}
       FPS.fdr.typ := FPC.typ;

       FPS.fdr.dep.kod := FPC.start.kod;
       FPS.fdr.dep.h   := FPC.start.h;
       FPS.fdr.dep.m   := FPC.start.m;

       FPS.fdr.arr.kod := FPC.prist.kod;
       FPS.fdr.arr.h   := FPC.prist.h;
       FPS.fdr.arr.m   := FPC.prist.m;

       if (FPC.bodov>0) then OB_to_OB_(FPC.trat[0],FPS.fdr.eet);
       if (FPC.bodov>1) then OB_to_OB_(FPC.trat[FPC.bodov-1],FPS.fdr.exi);

       FPS.fdr.vys:= FPC.vys;
       FPS.fdr.vys_:= vysOB;

       FPS.fdr.date:= FPC.date;
       FPS.fdr.stat:= FPC.stt;
     end;


 const _p_save_STA_FPLC : PProc_p = nil;

 procedure zarad_do_statistiky (FPL: PFPLC); far;
     var   FPS1,FPS2 : DFPS;
           FP4  : DFPL4;
           FPC  : PFPLC;
           ires : int;
           bres : bool;
           reg,opr : string;
     begin
       if not IS_STA_FPLC then Exit;

       if _p_save_STA_FPLC<>nil then TProc_p(_p_save_STA_FPLC)(FPL);

      { naplnenie sledovanych udajov statitiky
      }
       code_FPLC_FPS(FPL^,FPS1);
       FPC:= find_FPLCa(codekey_FPLC(FPL));
       if FPC<>nil then
          begin
            code_FPLC_FPS(FPC^,FPS2);
            bres:= chg_FPS(@FPS1,@FPS2);
            disp_FPS(@FPS2)
          end
       else bres:= true;

       if bres then
          begin
          { nacitanie ostatnych sledovanych udajov,
            ktore nie su drzane v prijatej sprave

           if read_FPL4(codekey_FDR(@FPS1.fdr),@FP4)>=0 then
              begin
                opr:= _item_18(FP4._18,rmk_OPR, 1);
                reg:= _item_18(FP4._18,rmk_REG, 1);
                FPS1.fdr.src:= FP4.src;
                disp_FPL4(@FP4);
              end
           else} begin
                  reg:= '';
                  opr:= ''
                end;

           FPS1.reg:= strpasnew(reg);
           FPS1.opr:= strpasnew(opr);
           FPS1.flo:= StrPasNew(flo_name(FPS1.fdr.idn));

           format_FPS(@FPS1);

           DB_oprav (@FPS1, get_DBfn(FPS1.fdr.date, pathFPS,extFPS),
                     db_FPS_RIADKOV,@codeDB_FPS,@codekey_FPS,
                     @dbchg_FPS,dbattr_FPS
                    );
          end;

       if (p_sta_dbscroller<>nil) then p_sta_dbscroller^.data_update(@FPS1);

       disp_FPS(@FPS1)
     end;
