{$IFDEF MACC}

{ --------------------------------------------------
   Formular pre spracovanie pripomienky na ziadost
   o schvalenie FPL podaneho na letisku
  --------------------------------------------------
}

{ kontrola, ci pripomienka uz bola vydana
  na inom pracovisku
}
 procedure _vydanie_pripomienky(rqst: Trqst; FPL,REQ: PDmFPL); far;
     var   T  : DmFPL;
           je : int;
     begin
       if zmeneny_mFPL(REQ,true) then Exit;

       if rqst<>dla then fillchar(REQ^.rec,sizeof(REQ^.rec),no_ack);
       case rqst of
         dla : zarad_FPLm(REQ,cnst_prop+cnst_prop,false,letvis);
         ack : zarad_FPLm(REQ,cnst_req_acc,true,letvis);  { pre istotu, aby nahodou nezmenil nieco }
         chg : zarad_FPLm(FPL,cnst_req_chg,true,letvis);
         dcl : zarad_FPLm(REQ,cnst_req_dec,true,letvis)
       end
     end;


 function  formular_pre_vydanie_pripomienky_ku_FPLM

              (REQ: PDmFPL;
               _beep: bool
              ): bool;

    const  f    : Tcentr = (x: initX; y: initY; m: 1);
    var    form : PREQ_FPL;
           E    : TEvent;
           FPL  : DmFPL;

    begin
      formular_pre_vydanie_pripomienky_ku_FPLM:= false;
      if REQ=nil then Exit;

      new_mFPL(REQ,@FPL);
      form:= New(PREQ_FPL, Init(f.x,f.y, f.m,
                 msg_FPL_REQ+' '+code_FPLM_7a(REQ)+'.',

                 @FPL, REQ,
                 nil,nil,nil,nil,
                 @_vydanie_pripomienky,
                 _beep,
                 hlp_mFPL_REQ)
                );
      p_formular_REQ_FPL:= form;
      form^.RunLocalFunc(E,REQLocalMenu);
      p_formular_REQ_FPL:= nil;
      formular_pre_vydanie_pripomienky_ku_FPLM:= form^.corr_res;
      Dispose(form,Done);
      disp_mFPL(@FPL)
    end;



{ spracovanie planov, na ktore dosla ziadost o pripomienku
}
 function handle_ziadost_o_pripomienku(p: pointer; FPL: PDmFPL): bool; far;
    var   res: bool;
    begin
      res:= _ziadost_o_pripomienku(nil,FPL);
      if res then formular_pre_vydanie_pripomienky_ku_FPLM(FPL,true);
      handle_ziadost_o_pripomienku:= res
    end;

 procedure spracuj_ziadosti_o_pripomienky_ku_FPL;
     const semaphor : bool = false;
     var   FPL      : DmFPL;
     begin
       if isFPLM_REQ and (not semaphor) and (p_formular_REQ_FPL=nil) then
          begin
            semaphor:= true;
            fillchar(FPL,sizeof(DmFPL),0);
            while DB_prehladaj (@handle_ziadost_o_pripomienku,
                                nil,@FPL, @disp_mFPL,
                                get_fn_mFPL_let, db_mFPL_RIADKOV, @decodeDB_FPLM,@codekey_FPLM,
                                true,''
                               ) <> -1
            do;
            isFPLM_REQ:= false;
            semaphor:= false
          end;
     end;

{$ENDIF}
