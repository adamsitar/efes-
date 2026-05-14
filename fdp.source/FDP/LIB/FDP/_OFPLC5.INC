{
ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ
Û                                          Û
Û TcFPL                                    Û
ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ
}

 function comp_idn_cFPL(FPL1,FPL2: PDcFPL): bool;
    var   s1,s2: string;
    begin
      with FPL1^ do begin s1:= idn; if bodov>0 then with trat[0] do s1:= s1 + kod + code_l4_utc(h,m) end;
      with FPL2^ do begin s2:= idn; if bodov>0 then with trat[0] do s2:= s2 + kod + code_l4_utc(h,m) end;
      comp_idn_cFPL:= s1 < s2
    end;


 constructor OcFPL.Init(_items : word;
                        _en_net: bool;

                        var _p_PRN   : bool;

                        {$IFDEF EDD}
                         _accepted : bool;
                         _adrBOARD : PPObject;
                         _cmADD,_cmCHG,_cmDEL,_cmCLR: word;
                        {$ENDIF}

                        _p_formular : pointer;
                        _p_handler  : pointer
                       );
       begin
         inherited Init(_items,sizeof(DcFPL),
                        nil,@format_cFPL,nil,

                        @eq_cFPL, @idn_cFPL,@ssr_cFPL,@chg_cFPL,@stav_cFPL,nil,
                        @distribute_rdp_cFPL,@send_cFPL,_en_net,

                        {$IFDEF EDD} @plan_cFPL, dx_cFPLp,dy_cFPLp, nil,nil,
                        {$ELSE}      @sc_cFPL, dx_cFPLp,dy_cFPLp,
                                     @dx_sc_cFPL,@dy_sc_cFPL,
                        {$ENDIF}
                        nil,

                        {$IFDEF MAPY}
                          @zobraz_trat_cFPL,
                          @draw_cFPLtrgt,@draw_cFPL_en,
                          cl_cFPL,cl_trat_cFPL,
                        {$ENDIF}

                        {$IFDEF EDD}
                          _accepted,
                          _adrBOARD, _cmADD,_cmCHG,_cmDEL,_cmCLR,
                          @strip_cFPL,
                          fplOTHER,
                        {$ENDIF}

                        _p_PRN, {$IFDEF PRN} @print_cFPL {$ELSE} nil {$ENDIF},

                        @save_cFPL,
                        @info_cFPL,
                        _p_formular,
                        @comp_idn_cFPL,
                        _p_handler,

                        nil, @decodeDB_FPLC,
                        db_cFPL_RIADKOV,
                        @codekey_FPLC,

                        nil,@dT_deactive_NOPL,@dT_deactive_FPLC,
                        false,

                        hlp_PREHLAD_cFPL
                       );

         denny_subor:= false;
         add_pos:= poz_est_FPLC;

         p_message:= @message_cFPL;
         p_ssr0:= @ssr0_cFPL;
         p_typ := @typ_cFPL;

         {$IFDEF EDD}
           hidding:= true;
         {$ENDIF}
       end;


 procedure OcFPL.format_data_variables (p: pointer);
     var   FPL : PDcFPL;
     begin
       FPL:= p;
       {$IFDEF FLI_COORDINATION}
        FPL^.przn[p_fli]:= _najdi_FLI(FPL,0);
       {$ENDIF}
       inherited format_data_variables(p);
     end;


 function OcFPL.is_plan(p: pointer): bool;
    begin
      is_plan:= (PDcFPL(p)^.stt<>hd_CPL) or FPLC_CPL or (FPLC_CPL_SSR and (PDcFPL(p)^.ssr<>''))
    end;


 function OcFPL.Eq(ind: int; p: pointer): bool;
    var   fli,prz : byte;
    begin
     {$IFDEF FLI_COORDINATION}
      { Spravne by tu mala byt kontrola, ci sa nezmenila trat ...
      } fli:= Maximum(PDcFPL(ap^[ind])^.przn[p_fli],PDcFPL(p)^.przn[p_fli]);
        PDcFPL(p)^.przn[p_fli]:= fli;
     {$ENDIF}
      prz:= PDcFPL(ap^[ind])^.przn[p_others] or PDcFPL(p)^.przn[p_others];
      PDcFPL(p)^.przn[p_others]:= prz;
      Eq:= inherited Eq(ind, p);
     (*{$IFDEF FLI_COORDINATION}
      { FLI sa odosiela len raz, a toto moze byt sprava o tom...
      } PDcFPL(ap^[ind])^.przn[p_fli]:= fli;
     {$ENDIF}
      PDcFPL(ap^[ind])^.przn[p_others]:= prz;*)
    end;


 function OcFPL.urc_platnost(p: pointer; var zmena: bool; kresli: bool): Tpoz;
    var   z : Tpoz;
    begin
      z:= stav_planu(p,AbsTime,zmena);
      urc_platnost:= z;
      {$IFDEF MAPY}
       if kresli and (z>=poz_SEDI {in [poz_SEDI,poz_HANGAR]}) then zmaz_plan_na_mape(p,true)
      {$ENDIF}
    end;


 procedure OcFPL.plan_zruseny (p: pointer);
     var   FPL: DcFPL;
     begin
      {$IFDEF CNL_FPLC}
       new_cFPL(p,@FPL);
       _zarad_FPLc(@FPL,hd_CNL,true,[],user,'',true,true,false, p,true);
       disp_cFPL(@FPL);
      {$ENDIF}
     end;


