{$IFDEF AIRBASE}

{ --------------------------------------------------
   Formular pre spracovanie spracovanych pripomienok
   o schvaleni/zamietnuti/pripomienkovani FPL
   na ACC
  --------------------------------------------------
}

 function  formular_pre_vyziadanie_pripomienky_ku_FPLM(FPL: PDmFPL): bool;
    begin
      formular_pre_vyziadanie_pripomienky_ku_FPLM:=
        formular_mFPL(FPL,letvis,cnst_prop,false,
                      msg_FPL_REQ,i_15M,
                      nil,hlp_mFPL_REQ
                     );
    end;


 function  formular_pre_spracovanie_pripomienky_ku_FPLM

              (REQ: PDmFPL;
               _stat,_title: string;
               _p_dla,_p_ack,_p_dcl,_p_chg : pointer;
               _hlpXXX: Pchar
              ): bool;

    const  f    : Tcentr = (x: initX; y: initY; m: 1);

    var    form : PREQ_FPL;
           E    : TEvent;
           FPL  : DmFPL;

    begin
      formular_pre_spracovanie_pripomienky_ku_FPLM:= false;
      if REQ=nil then Exit;

      new_mFPL(REQ,@FPL);
      if _stat<>'' then FPL.stat:= _stat;
      form:= New(PREQ_FPL, Init(f.x,f.y, f.m, _title,
                 @FPL,REQ,
                 _p_dla,_p_ack,_p_dcl,_p_chg, nil,
                 true, _hlpXXX)
                );
      form^.RunLocalFunc(E,REQLocalMenu);
      formular_pre_spracovanie_pripomienky_ku_FPLM:= form^.corr_res;
      Dispose(form,Done);
      disp_mFPL(@FPL)
    end;


  { -------------------------------------------
    Oprava ziadosti o pripomienkuna ACC
  }

  procedure CHG_is_acc(FPL,REQ: PDmFPL); far;
      begin
        fillchar(REQ^.rec,sizeof(REQ^.rec),0);
        zarad_FPLm (REQ, del_stat(REQ^.stat,cnst_str_chg),true,letvis)
      end;

  procedure CHG_is_dec(FPL,REQ: PDmFPL); far;
      begin
        fillchar(REQ^.rec,sizeof(REQ^.rec),0);
        zarad_FPLm (REQ, del_stat(REQ^.stat,cnst_str_chg)+cnst_cnl,true,letvis)
      end;

  procedure CHG_is_chg(FPL,REQ: PDmFPL); far;
      begin
        fillchar(FPL^.rec,sizeof(FPL^.rec),0);
        zarad_FPLm (FPL, cnst_prop,true,letvis)
      end;


  { -------------------------------------------
    Zobrazenie spracovanej ziadosti
    o pripomienku
  }

  procedure REQ_is_acc(FPL,REQ: PDmFPL); far;
      begin
        CHG_is_acc(REQ,REQ);
        info_mFPL(REQ,msg_req+' '+code_FPLM_7a(REQ)+' '+msg_req_acc)
      end;

  procedure REQ_is_dec(FPL,REQ: PDmFPL); far;
      begin
        CHG_is_dec(REQ,REQ);
        info_mFPL(FPL,msg_req+' '+code_FPLM_7a(FPL)+' '+msq_req_dec)
      end;

  procedure REQ_is_chg(FPL,REQ: PDmFPL); far;
      begin
        formular_pre_spracovanie_pripomienky_ku_FPLM
           (REQ,'',msg_plan_pre+' '+code_FPLM_7a(REQ)+' '+msg_opraveny,
            nil, @CHG_is_acc,@CHG_is_dec,@CHG_is_chg,
            hlp_mFPL_CHG
           )
      end;


 { --------------------------------------------
    Spracovanie planov, na ktore dosla
    pripomienka alebo oprava
 }
  function spracuj_pripomienku (p: pointer; REQ: PDmFPL): bool; far;
     var   res : bool;
     begin
       res:= _spracovanie_na_ACC(nil, REQ);
       if res then
          begin
            if pos(cnst_req_chg,REQ^.stat)<>0 then       REQ_is_chg (REQ,REQ)
            else if pos(cnst_req_acc, REQ^.stat)<>0 then REQ_is_acc (REQ,REQ)
            else if pos(cnst_req_dec, REQ^.stat)<>0 then REQ_is_dec (REQ,REQ)
            else zarad_FPLm(REQ,del_stat(REQ^.stat,cnst_str_chg),true,letvis)
          end;
       spracuj_pripomienku:= res
     end;

  procedure spracuj_pripomienky_ku_FPL;
      const semaphor : bool = false;
      var   FPL      : DmFPL;
      begin
        if isFPLM_ACC and (not semaphor) then
           begin
           { bol prijaty FPL zo StrRLP opraveny alebo pripomienkovany
           } semaphor:= true;
             fillchar(FPL,sizeof(DmFPL),0);
             while DB_prehladaj (@spracuj_pripomienku, nil,@FPL, @disp_mFPL,
                                 get_fn_mFPL_let, db_mFPL_RIADKOV, @decodeDB_FPLM,@codekey_FPLM,
                                 true,''
                                ) <> -1
             do;
             isFPLM_ACC:= false;
             semaphor:= false
           end;
      end;

{$ENDIF}