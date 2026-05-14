{$IFDEF KRL}

 { -----------
    KRL
   -----------
 }
  function _is_SEND_KRL (FPL: PDmFPL; s: Pstring): bool; far;
     var   nd: int;
     begin
       nd:= is_NETadr(adr_airbase(FPL^.start.kod));
       _is_SEND_KRL:= {$IFDEF AIRBASE}
                            _kridlo_pre_ine_letisko(FPL,s)
                       and (   (FPL^.stat=cnst_disk)
                            or (FPL^.rec[nd]=no_ack)
                           )
                      {$ELSE}
                       true
                      {$ENDIF}
     end;


  function _KRL_oprava(sc: PScroller; FPL: PDmFPL): bool; far;
     var   res: bool;
     begin
       res:= formular_mFPL(FPL,letvis,FPL^.stat,false,
                           msg_KRL_CHG, i_15M,
                           nil, hlp_mFPL
                          );
       _KRL_oprava:= false
     end;


  procedure KRL_oprava;
      begin
        spracuj_mFPL(false,false, true,false,false,false,
                     cnl_stat(cnst_all_valid), @_is_stata_KRL,
                     @_KRL_oprava, _TBFunc_p2,
                     true,true,
                     msg_KRL_CHG,nil,nil
                    );
      end;


  function _KRL_zrusenie(sc: PScroller; FPL: PDmFPL): bool; far;
     begin
       _CNL_FPL_(sc,FPL,ask_krl_CNL);
       _KRL_zrusenie:= false
     end;

  procedure KRL_zrusenie;
      begin
        spracuj_mFPL(false,false, true,false,false,false,
                     cnl_stat(cnst_all_valid), @_is_stata_KRL,
                     @_KRL_zrusenie, _TBFunc_p2,
                     true,true,
                     msg_KRL_CNL,nil,nil
                    );
      end;


  function _KRL_spracovanie(sc: PScroller; FPL: PDmFPL): bool; far;
     begin
       if formular_mFPL(FPL,letvis,cnst_disk,false,
                        msg_KRL_FPL, 0,
                        nil, hlp_mFPL
                       ) then
          begin
            if KRL_FPLM_CNL then
               begin
                 {FPL^.stat:= add_stat(FPL^.stat,cnst_CNL);}
                 FPL^.stat:= cnst_CNL;
                 save_mFPL(FPL)
               end
          end;
       _KRL_spracovanie:= false
     end;

  procedure KRL_spracovanie;
      begin
        spracuj_mFPL(false,false, true,false,false,false,
                     cnl_stat(cnst_all_valid), @_kridlo_pre_vlastne_letisko,
                     @_KRL_spracovanie, _TBFunc_p2,
                     true,true,
                     msg_KRL_FPL,nil,nil
                    );
      end;


  function handle__podanie_FPL_ako_KRL(sc: PScroller; FPL: PDmFPL): bool; far; forward;

  procedure podanie_FPL_ako_KRL(ppl: bool);
      begin
        spracuj_mFPL(false,false,
                     ppl,false,false,true,
                     cnst_disk+cnst_sended, @_is_stat_FPLm,
                     @handle__podanie_FPL_ako_KRL, _TBFunc_p2,
                     true,false,
                     titVIEW+' FPL'{$IFDEF AIRBASE}+' z '+this_airbase{$ENDIF},
                     nil,nil
                    )
      end;


{$ENDIF}
