{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ Config                                                   €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
type fb = file of byte;

function read_bool(var f: fb): bool;
   var   b: byte;
   begin
     read(f, b);
     read_bool:= bool(b)
   end;

function read_byte(var f: fb): byte;
   var   b: byte;
   begin
     read(f, b);
     read_byte:= b
   end;

function read_word(var f: fb): word;
   var   b1,b2: byte;
   begin
     read(f, b1); read(f, b2);
     read_word:= b1 + b2 shl 8
   end;

procedure write_word(var f: fb; w: word);
    var   b: byte;
    begin
      b:= lo(w); write(f, b);
      b:= hi(w); write(f, b)
    end;


const  {cfg_fn                 = 'FDP.kod';}

       CFG_SIZE : word          =     1 + length(APP_CFG)
                                    + sizeof(long)
                                    + 1             { save cfg }

       {$IFNDEF EDD}                + 1             { Gr mod }
       {$ENDIF}
                                    + 29

       {$IFDEF OPL}                 + 21
       {$ENDIF}

       {$IFDEF EDD}                 + 1
         {$IFDEF LINE_STRIP}        + 1    {$ENDIF}
                                    + 6
         {$IFDEF PRN}               + 5    {$ENDIF}
                                    + 5
         {$IFDEF FIND_EQ_NDB}       + 1    {$ENDIF}
                                    + 1
                                    + ord(high(STRIP_DIR_)) - ord(low(STRIP_DIR_)) + 1
                                    + 1

         {$IFDEF TRENAZER_UDP}      + 1    {$ENDIF}
         {$IFDEF TRENAZER_IPX}      + 1    {$ENDIF}
       {$ENDIF}

                                    + 17


       {$IFDEF RPL}                 + 14  {$ENDIF}

       {$IFDEF PLN}                 + 6   {$ENDIF}

       {$IFDEF FPL4}                + 77
         {$IFDEF A36YKA}            + 1   {$ENDIF}
         {$IFDEF FDA}               + 2   {$ENDIF}
       {$ENDIF}

       {$IFDEF FPL0}                + 17
                                    + 38

         {$IFDEF SSR_MANAGEMENT}    + 5  {$ENDIF}
         {$IFDEF FLI_COORDINATION}  + 6  {$ENDIF}

                                         {$ENDIF}

       {$IFDEF ZAM}                 + 9    {$ENDIF}
       {$IFDEF QGO}                 + 2    {$ENDIF}
       {$IFDEF RTZ}                 + 2    {$ENDIF}
       {$IFDEF DVZ}                 + 4    {$ENDIF}

       {$IFDEF PRS}                 + 15   {$ENDIF}
       {$IFDEF NOTAM}               + 4    {$ENDIF}

       {$IFDEF MET}                 + 1    {$ENDIF}

       {$IFDEF SPR}                 + 6    {$ENDIF}

       {$IFDEF TLG}                 + 8
         {$IFDEF A36YKA}            + 1    {$ENDIF}
       {$ENDIF}

       {$IFDEF STATISTIKA}
         {$IFDEF STATISTIKA_PRELETY}+ 1    {$ENDIF}
       {$ENDIF}

       {$IFDEF SECTORS}             + 16   {$ENDIF}
       {$IFDEF MAPY}                + 10   {$ENDIF}
       {$IFDEF PRN}                 + 8    {$ENDIF}

       {$IFDEF EXTERNAL_NET}        +  4   {$ENDIF}
       {$IFDEF CONNECT_TO_ASTA_EXT} +  5   {$ENDIF}
       {$IFDEF CONNECT_TO_OPL_EXT}  +  22  {$ENDIF}
       {$IFDEF CONNECT_TO_CAMUS}    +  2   {$ENDIF}
       {$IFDEF CONNECT_TO_ASOC}     +  2   {$ENDIF}
       {$IFDEF CONNECT_TO_VERA}     +  2   {$ENDIF}
       {$IFDEF CONNECT_TO_AFTN}     +  6   {$ENDIF}
       {$IFDEF CONNECT_TO_BGU}      +  2   {$ENDIF}

                                    +  3
       {$IFDEF WRITELN_NET}         +  6   {$ENDIF}
       {$IFDEF ARCHIVE_DAR}         +  1   {$ENDIF}
       {$IFDEF X25}                 +  1   {$ENDIF}

  ;


function  apReadProgramCfg (cfg_fn: string; _dialog: bool): bool;
    var   f  : fb;

          uf : file;
          di : SearchRec;
          ti : long;
          na : string;
          res : word;

          b  : byte;
          i  : int;
          d  : Ts_dir;
          pomb : bool;
          _err : bool;

    begin
      _err:= false;
      apReadProgramCfg:= false;

      if (Exists(cfg_fn)<>0) or (_filesize(cfg_fn)<>CFG_SIZE) then
         begin
           _write_err_log('Uncorrect version of '+cfg_fn+'...');
           Exit;
         end;
      _write_err_log('Loading '+cfg_fn+'...');

      Assign(uf,cfg_fn);
      Reset(uf,1);
      BlockRead(uf,na[0],1+length(APP_CFG),res);
      BlockRead(uf,ti,sizeof(ti),res);
      Close(uf);

      FindFirst(path_E+exe+'.exe',Archive,di);
      if (na<>APP_CFG) or ((cfg_fn<>APP_CFG) and (ti<>di.Time)) then
         begin
           {$IFNDEF DEBUG}
            if _dialog then Err2('',msgCONFIG_IGNORE)
            else MessError(msgCONFIG_IGNORE, true,_err);
           {$ENDIF}
           Exit
         end;

      apReadProgramCfg:= true;
      Assign(f,cfg_fn);
      Reset(f);
      Seek(f,1+length(APP_CFG)+sizeof(ti));

      read(f, b);        { saveCFG = ? }
      if b=0 then begin Close(f); Exit end;

      {$IFNDEF EDD}
        GraphMode:= TGraphMode(read_byte(f));
      {$ENDIF}

      INIT_VYP   := read_bool(f);
      INIT_INT   := read_word(f);
      INIT_POCET := read_word(f);

      ZVUK            := read_bool(f);
      ALARM           := read_bool(f);
      CASOVE_ZNAMENIE := read_bool(f);
      UTC_SYNCHRONIZE := read_bool(f);

      SKRYVANIE  := read_bool(f);
      ZHASINANIE := read_bool(f);
      ZHASNI_PO  := read_word(f);
      JAS        := read_bool(f);

      mnu_mouse_scroll    := read_bool(f);
      mnu_data_opt_common := read_bool(f);

      waitINFO  := read_word(f);
      waitASK   := read_word(f);
      waitERR   := read_word(f);

      ask_zrus_item := read_bool(f);
      ask_zrus_plan := read_bool(f);

      waitSPRAVA:= read_word(f);
      waitSPRAVY:= read_word(f);

      disp_ERRCODE:= read_bool(f);


     {$IFDEF OPL}
      MENU_MACC     := read_bool(f);

      tab_mFPL      := read_bool(f);
      tab_cFPL      := read_bool(f);
      tab_oFPL      := read_bool(f);
      tab_mFPL_abc  := read_bool(f);

      _propose_dayFPLM       := read_bool(f);
      _unactive_dayFPLM      := read_bool(f);

      _preactived_FPLM       := read_bool(f);
      _preactived_FPLO       := read_bool(f);
        _preactived_FPLM_ot  := read_bool(f);
        _preactived_FPLO_ot  := read_bool(f);

      _proposed_FPLM         := read_bool(f);  { vyziadane pripomienky }
      _proposed_FPLO         := read_bool(f);
        _proposed_FPLM_ot    := read_bool(f);
        _proposed_FPLO_ot    := read_bool(f);

      _coordinated_FPLM      := read_bool(f);  { schvalene pripomienky }
      _coordinated_FPLO      := read_bool(f);
        _coordinated_FPLM_ot := read_bool(f);
        _coordinated_FPLO_ot := read_bool(f);

      _activated_FPLM_ot     := read_bool(f);
      _activated_FPLO_ot     := read_bool(f);
     {$ENDIF}


     {$IFDEF EDD}
       miniSTRIP:= T_strip(read_byte(f));
      {$IFDEF LINE_STRIP}
       lineSTRIP := read_bool(f);
      {$ENDIF}

       GraphMode_MAPA:= TGraphMode(read_byte(f));

       PROP_ACK_cFPL := read_bool(f);
       PROP_ACK_mFPL := read_bool(f);
       PROP_ACK_oFPL := read_bool(f);
       PROP_WARN     := read_bool(f);
       PROP_SCROLL   := read_bool(f);

      {$IFDEF PRN}
       REC_PROP_PRN  := read_bool(f);
       PROP_PRN      := read_bool(f);
       PRN_cFPL      := read_bool(f);
       PRN_mFPL      := read_bool(f);
       PRN_oFPL      := read_bool(f);
      {$ENDIF}

      {TABLET_CFG_SAVE := read_bool(f);}
      NDB_OTHERS    := read_bool(f);
      NDB_NULL      := read_bool(f);
      NDB_INP       := read_bool(f);
      NDB_SL        := read_bool(f);
      NDB_XY        := read_bool(f);
      {$IFDEF FIND_EQ_NDB}
       NDB_EQ        := read_bool(f);
      {$ENDIF}

      STRIP_DIR  := read_bool(f);
      for d:= dir_west to high(Ts_dir) do STRIP_DIR_[d]:= read_bool(f);
      STRIP_SORT := Tsort_strip(read_byte(f));

      {$IFDEF TRENAZER_UDP};
       SIM_UNIX := read_bool(f);
      {$ENDIF}
      {$IFDEF TRENAZER_IPX};
       get_trenazer_pos(read_byte(f));
      {$ENDIF}
     {$ENDIF}


     CNL_RPL_VYPIS  := read_bool(f);
     CNL_VYPIS  := read_bool(f);
     DEC_VYPIS  := read_bool(f);
     ARR_VYPIS  := read_bool(f);

     STAV_PLANU := read_bool(f);


     (*bminiSTRIP := read_bool(f);
     {$IFNDEF EDD}
      if bminiSTRIP then miniSTRIP:= mini_strip
      else miniSTRIP:= full_strip;
     {$ENDIF}*)
     ionSTRIP := read_bool(f);


     alt_VFR_sym    := read_bool(f);
     in_FL          := read_bool(f);
     in_km          := read_bool(f);

     pis_STRIP_10b  := read_bool(f);
     pis_STRIP_EST  := read_bool(f);
     pis_STRIP_COR  := read_bool(f);
     pis_STRIP_ACK  := read_bool(f);
     {pis_STRIP_SSN  := read_bool(f);}



     { ------------------------------------
         DATA
       ------------------------------------
     }
      casPRED  := read_word(f);
      casPRIST := read_word(f);


     {$IFDEF RPL}
      rpl_hour:= read_word(f);
      rpl_min:= read_word(f);

      rpl_PND  := read_bool(f);
      rpl_ERR  := read_bool(f);

      bminiRPL := read_bool(f);
      max_RPL_15_rm := read_word(f);
      max_RPL_18_rm := read_word(f);
      RUSSIAN_RPL := read_bool(f);

      prn_RPL_IFPS := read_bool(f);

      rpl_assign_15:= read_bool(f);
     {$ENDIF}


     {$IFDEF PLN}
      pln_PND:= read_bool(f);
      pln_ADR:= read_bool(f);
      pln_FPL:= read_bool(f);
      pln_ERR:= read_bool(f);

      RUSSIAN_PLN:= read_bool(f);

      pln_assign_15:= read_bool(f);
     {$ENDIF}


     {$IFDEF FPL4}
      dT_preactive_FPL4  := read_word(f);
      dT_propose_FPL4    := read_word(f);
      dT_coordinate_FPL4 := read_word(f);
      dT_unactive_FPL4   := read_word(f);
      {dT_deactive_FPL4   := read_word(f);}

      _FPL4_PPL_ENABLE := read_bool(f);
      _FPL4_CHG_ENABLE := read_bool(f);
      _FPL4_DLA_ENABLE := read_bool(f);
      _FPL4_CNL_ENABLE := read_bool(f);
      _FPL4_DEP_ENABLE := read_bool(f);
      _FPL4_ARR_ENABLE := read_bool(f);
      _FPL4_CPL_ENABLE := read_bool(f);

      _FPL4_MZP_ENABLE := read_bool(f);
      _FPL4_XG_ENABLE  := read_bool(f);

      _9b_CHECK_ICAO := read_bool(f);
      _9b_CHECK_TSGA := read_bool(f);
      _9b_CHECK_ZZZZ := read_bool(f);
      _9b_CHECK_MIL  := read_bool(f);
      _9c_CHECK_ICAO := read_bool(f);
      _9c_CHECK_ZZZZ := read_bool(f);

      _10a_CHECK     := read_bool(f);
      _10b_CHECK     := read_bool(f);

      _15a_RANGE := read_bool(f);
      _15b_RANGE := read_bool(f);

      _15_RxR_ENABLE:= read_bool(f);
      _15_BxR_ENABLE:= read_bool(f);
      _15_BxR_KM := read_bool(f);
      _15_XYxR := read_word(f);
      _15_BxR  := read_word(f);

      _15_DCT_POINTS:= read_bool(f);
      _15_UPLNA_TRAT:= read_bool(f);

      {_15_IO_ENABLE:= read_bool(f);
      FULL_RTE:= read_bool(f);
      UNKN_RTE:= read_bool(f);
      }

      _18_CHECK_IS:= read_bool(f);
      _18_CHECK:= read_bool(f);
      _18_TYPE_CHECK:= read_bool(f);
      _18_DAT_CHECK:= read_bool(f);
      _18_COM_NAV_CHECK:= read_bool(f);
      _18_DEP_CHECK:= read_bool(f);
      _18_DEST_CHECK:= read_bool(f);
      _18_ALTN_CHECK:= read_bool(f);
      _18_RALT_CHECK:= read_bool(f);

      _EFIL_8    := read_bool(f);
      _EFIL_9    := read_bool(f);
      _EFIL_10   := read_bool(f);
      _EFIL_15ab := read_bool(f);

      _CHG__7_13:= read_bool(f);
      _FPL_CHG__14_17:= read_bool(f);
      _ACT__FIELDS:= read_bool(f);
      _ARR__FIELDS:= read_bool(f);

      _ACT_OR_DEP:= read_bool(f);
      _ACT_AS_EST:= read_bool(f);
      _AP_EET_EXI:= read_bool(f);

      find_and_process_FPL4 := read_bool(f);
      find_and_process_FDR  := read_bool(f);
      _propose_dayFPL4  := read_bool(f);
      _unactive_dayFPL4 := read_bool(f);

      bminiFPL4 := read_bool(f);
      read(f,comp_FPL4);
      ZDROJ_PLANU:= read_bool(f);

      max_FPL4_15_rm := read_word(f);
      max_FPL4_18_rm := read_word(f);

      _FPL4_REPORT_PLAN:= read_bool(f);
      _FPL4_CHG_REPORT:= read_bool(f);
      _FPL4_DLA_REPORT:= read_bool(f);
      _FPL4_CNL_REPORT:= read_bool(f);
      _FPL4_DEP_REPORT:= read_bool(f);
      _FPL4_ARR_REPORT:= read_bool(f);

      _FPL4_APROVED_DISPLAY:= read_bool(f);
      _FPL4_APROVED_CHECK:= read_bool(f);
      _FPL4_APROVED_BY_FDA:= read_bool(f);

      prn_FPL4_ICAO := read_bool(f);

      {$IFDEF A36YKA}
       RUSSIAN_FPL:= read_bool(f);
      {$ENDIF}

      {$IFDEF FDA}
       {tab_FPL4prea := read_bool(f);}
       tab_FPL4prop := read_bool(f);
       tab_FPL4coor := read_bool(f);
      {$ENDIF}

     {$ENDIF}


     {$IFDEF FPL0}

     { FPLC
     }
      FPLC_CPL := read_bool(f);
      FPLC_CPL_SSR := read_bool(f);

      FPLC_ARR := read_bool(f);
      FPLC_CHECK_15 := read_bool(f);

      est_dT_pred := read_word(f);
      est_dT_po := read_word(f);

      dT_deactive_FPLC := read_word(f);
      dT_deactive_NOPL := read_word(f);

      prehlad_arch_fn_cFPL:= read_word(f);
      {pis_STRIP_cFPL:= } read_bool(f);
      miniSTRIP_cFPL:= T_strip(read_byte(f));

      find_and_process_FPLC:= read_bool(f);


     { FPLM
     }
      dT_propose_FPLM   := read_word(f);       {35<-13}
      dT_unactive_FPLM  := read_word(f);
      dT_arr_warn_FPLM  := read_word(f);
      dT_deactive_FPLM  := read_word(f);

      dT_propose_FPLM_REQ  := read_word(f);
      dT_deactive_FPLM_REQ := read_word(f);

      FPLM_INE    := read_bool(f);
      FPLM_INE_9  := read_bool(f);
      FPLM_INE_AP := read_bool(f);

      KRL_FPLM_CNL      := read_bool(f);

      FPLM_REQ_WARN     := read_bool(f);
      FPLM_DEP_WARN     := read_bool(f);

      FPLM_ARR_WARN     := read_bool(f);
      FPLM_ARR_WARN_ALL := read_bool(f);

      bminimFPL         := read_bool(f);
      max_mFPL_15_rm    := read_word(f);
      max_mFPL_18_rm    := read_word(f);
      pis_STRIP_mFPL    := read_bool(f);
      pis_STRIP_mFPL_15body  := read_bool(f);
      miniSTRIP_mFPL    := T_strip(read_byte(f));

      prn_FPLM_ICAO     := read_bool(f);

      hlas_vlastne_FPLM := read_bool(f);
      hlas_vsetky_FPLM  := read_bool(f);
      hlas_riadene_FPLM := read_bool(f);
      varovanie_FPLM    := read_bool(f);

      find_and_process_FPLM := read_bool(f);

      FPLM_REGULARITA_FPLM     := read_bool(f);
      FPLM_REGULARITA_FUA_PLAN := read_bool(f);
      FPLM_REGULARITA_FUA_ACT  := read_bool(f);
      FPLM_REGULARITA_FIR      := read_bool(f);

      {$IFDEF SSR_MANAGEMENT}
       FPLC_SSR:= read_bool(f);
       FPLM_SSR:= read_bool(f);

       SSR_NEXT_USE_KEEP:= read_bool(f);
       SSR_NEXT_USE:= read_word(f);

       {SSR_LIST:= read_bool(f);
       SSR_ASSIGN:= read_bool(f);
       SSR_NOT_CFG:= read_bool(f);}
      {$ENDIF}

      {$IFDEF FLI_COORDINATION}
       send_FLI := read_bool(f);
       display_FLI_ERR := read_bool(f);
       limit_FLI := read_word(f);

       update_FPLC_by_FLI:= read_bool(f);
       delete_FPLC_by_FLI:= read_bool(f);
      {$ENDIF}

     {$ENDIF}


     {$IFDEF ZAM}
      hlas_ZAM        := read_bool(f);
      varovanie_ZAM   := read_bool(f);

      bminiZAM        := read_bool(f);
      pis_STRIP_ZAM   := read_bool(f);
      miniSTRIP_ZAM   := T_strip(read_byte(f));

      dt_propose_ZAM  := read_word(f);
      dT_deactive_ZAM := read_word(f);
     {$ENDIF}


     {$IFDEF QGO}
      hlas_QGO        := read_bool(f);
      varovanie_QGO   := read_bool(f);
     {$ENDIF}

     {$IFDEF RTZ}
      hlas_RTZ        := read_bool(f);
      varovanie_RTZ   := read_bool(f);
     {$ENDIF}


     {$IFDEF DVZ}
      hlas_DVZ        := read_bool(f);
      hlas_vsetky_DVZ := read_bool(f);
      varovanie_DVZ   := read_bool(f);
      posliZiadostDVZ := read_bool(f);
     {$ENDIF}


     {$IFDEF PRS}
       PRS_CHECK_VYS_REG:= read_bool(f);

       hlas_PRS_plan   := read_bool(f);
       hlas_PRS_act    := read_bool(f);
       find_and_process_PRS:= read_bool(f);

       bminiPRS        := read_bool(f);
       max_PRS_pozn_rm := read_word(f);
       pis_STRIP_PRS   := read_bool(f);
       miniSTRIP_PRS   := T_strip(read_byte(f));

       dT_propose_PRS  := read_word(f);
       dT_unactive_PRS := read_word(f);
       dT_deactive_PRS := read_word(f);
     {$ENDIF}

     {$IFDEF NOTAM}
       max_NTM_D_rm := read_word(f);
       max_NTM_E_rm := read_word(f);
     {$ENDIF}

     {$IFDEF MET}
       pis_SYN_:= read_bool(f);
     {$ENDIF}

     {$IFDEF SPR}
       SPR_ACK_WAIT := read_bool(f);
       bminiSPR     := read_bool(f);
       max_SPR_am   := read_word(f);
       max_SPR_rm   := read_word(f);
     {$ENDIF}


     {$IFDEF TLG}
       tlg_SS:= read_bool(f);
       tlg_FF:= read_bool(f);
       tlg_KK:= read_bool(f);

       tlg_SSprint:= read_bool(f);
       tlg_FFprint:= read_bool(f);
       tlg_KKprint:= read_bool(f);

       tlg_Print:= read_bool(f);
       tlg_PrintAll:= read_bool(f);

       {$IFDEF A36YKA}
         RUSSIAN_TLG:= read_bool(f);
       {$ENDIF}
     {$ENDIF}


     {$IFDEF STATISTIKA}
       {$IFDEF STATISTIKA_PRELETY}
        prn_FPS_FLO:= read_bool(f);
       {$ENDIF}
     {$ENDIF}


    { ------------------------------------
        FUNCTIONs
      ------------------------------------
    }
     {$IFDEF SECTORS}
      S_DISPLAY        := read_bool(f);
      S_PRINT          := read_bool(f);
      S_ARCHIV         := read_bool(f);
      S_D_IN_THROUGH   := read_bool(f);
      S_P_IN_THROUGH   := read_bool(f);
      S_TOUCH          := read_bool(f);
      S_INP_POINT_TIME := read_bool(f);
      S_OUT_POINT_TIME := read_bool(f);
      S_IN_KM          := read_word(f);
      S_EST_LIMIT      := read_word(f);
      S_DEL_LIMIT      := read_word(f);
      S_ROUTE          := read_bool(f);
      S_IN             := read_bool(f);
     {$ENDIF}

     {$IFDEF MAPY}
       pomb{saveMAPY} := read_bool(f);
       cursMAPY := read_bool(f);

       draw_mFPL_en := read_bool(f);
       draw_cFPL_en := read_bool(f);
       draw_oFPL_en := read_bool(f);

       draw_SSR := read_bool(f);

       mark_typ := read_bool(f);
       mark_txt := read_bool(f);
       mark_8x8 := read_bool(f);

       HLAS_NENAJDENA_MAPA:= read_bool(f);
     {$ENDIF}

     {$IFDEF PRN}
       is_PRN        := read_bool(f);
       PRN_REC       := read_bool(f);
       PRN_CHG       := read_bool(f);
       PRINTER_COM   := read_word(f);
       PRN_TAB       := read_word(f);
       PRN_NET       := read_bool(f);
     {$ENDIF}


    (* ------------------------------------
        EXTERNAL DEVICES
       ------------------------------------
    *)

     {$IFDEF EXTERNAL_NET}
       icao_ERR_DISPLAY  := read_bool(f);
       {icao_UNKN_ERR    := read_bool(f);}
       icao_HEAD_ERR     := read_bool(f);
       icao_HEAD_ERR_TLG := read_bool(f);
       icao_REC_UPDATED  := read_bool(f);
     {$ENDIF}

     {$IFDEF CONNECT_TO_ASTA_EXT}
       power_ASTA:= read_bool(f);
       power_ASTA_FDP:= read_bool(f);
       power_ASTA_PRN:= read_bool(f);
       writeln_ASTA:= read_bool(f);
       process_ASTA_CPL:= read_bool(f);
     {$ENDIF}

     {$IFDEF CONNECT_TO_OPL_EXT}
       line_master_OPL:= read_bool(f);
       power_OPL_async:= read_bool(f);
       power_OPL_udp:= read_bool(f);

       writeln_OPL:= read_bool(f);
       writeln_OPL_HeartBeat:= read_bool(f);
       OPL__SAVE_STREAM:= read_bool(f);
       OPL__LAM_NOT_FOUND:= read_bool(f);
       OPL__UNCOMPLETE_PKT:= read_bool(f);

       aup_hour := read_word(f);
       aup_min  := read_word(f);

       OPL__PROCESS_AUP:= read_bool(f);
       OPL__REQUEST_AUP:= read_bool(f);
       OPL__REQUEST_AUPi:= read_word(f);

       OPL__PROCESS_RTZ:= read_bool(f);
       OPL__REQUEST_RTZ:= read_bool(f);
       OPL__REQUEST_RTZi:= read_word(f);

       OPL__PROCESS_ASM:= read_bool(f);
       OPL__PROCESS_ASMfda:= read_bool(f);
     {$ENDIF}

     {$IFDEF CONNECT_TO_CAMUS}
       power_CAMUS:= read_bool(f);
       writeln_CAMUS:= read_bool(f);
     {$ENDIF}

     {$IFDEF CONNECT_TO_ASOC}
       power_ASOC:= read_bool(f);
       writeln_ASOC:= read_bool(f);
     {$ENDIF}

     {$IFDEF CONNECT_TO_VERA}
       power_VERA:= read_bool(f);
       writeln_VERA:= read_bool(f);
     {$ENDIF}

     {$IFDEF CONNECT_TO_AFTN}
       power_AFTN:= read_bool(f);
       aftn_DUAL_LINE:= read_bool(f);
       aftn_MASTER_LINE:= read_bool(f);
       writeln_AFTN:= read_bool(f);
       archive_AFTN:= read_bool(f);
       writeln_AFTN_utc:= read_bool(f);
     {$ENDIF}

     {$IFDEF CONNECT_TO_BGU}
       BGU_DEL:= read_word(f);
     {$ENDIF}



    (* ------------------------------------
        ARCHIVATION
       ------------------------------------
    *)
      ArchDays := read_word(f);
      archive_COM := read_bool(f);

     {$IFDEF WRITELN_NET}
       writeln_NET_REC := read_bool(f);
       writeln_NET_SEND:= read_bool(f);
       writeln_NET_DATA:= read_bool(f);
       writeln_NET_ACK := read_bool(f);
       writeln_NET_HeartBeat:= read_bool(f);
       writeln_MEM:= read_bool(f);
     {$ENDIF}

     {$IFDEF ARCHIVE_DAR}
       {archive_DAR}b:= read_byte(f);
     {$ENDIF}

     {$IFDEF X25}
       X25_archive:= read_byte(f);
     {$ENDIF}

      Close(f);
      _write_err_log('Loaded '+cfg_fn+'...');

      if _err then writeln
    end;


procedure apSaveProgramCfg(cfg_fn: string);
    var   f   : fb;

          uf  : file;
          di  : SearchRec;
          s   : string;
          res : word;

          d   : Ts_dir;

    begin
      if not saveCFG then Exit;

      Assign(uf,cfg_fn);
      Rewrite(uf,1);
      s:= APP_CFG;
      BlockWrite(uf,s,1+length(s),res);
      FindFirst(path_E+exe+'.exe',Archive,di);
      BlockWrite(uf,di.Time,sizeof(di.Time),res);
      Close(uf);

      Assign(f,cfg_fn);
      Reset(f);

      Seek(f,1+length(s)+sizeof(di.Time));

      write(f, byte(saveCFG));

      {$IFNDEF EDD}
       write(f, byte(GraphMode));
      {$ENDIF}

      {b:= ord('*');
      write(f, b);}

      write(f, byte(INIT_VYP));
      write_word(f, INIT_INT);
      write_word(f, INIT_POCET);

      write(f, byte(ZVUK));
      write(f, byte(ALARM));
      write(f, byte(CASOVE_ZNAMENIE));
      write(f, byte(UTC_SYNCHRONIZE));

      write(f, byte(SKRYVANIE));
      write(f, byte(ZHASINANIE));
      write_word(f, ZHASNI_PO );
      write(f, byte(JAS));

      write(f, byte(mnu_mouse_scroll));
      write(f, byte(mnu_data_opt_common));

      write_word(f, waitINFO);
      write_word(f, waitASK);
      write_word(f, waitERR);

      write(f, byte(ask_zrus_item));
      write(f, byte(ask_zrus_plan));

      write_word(f, waitSPRAVA);
      write_word(f, waitSPRAVY);

      write(f, byte(disp_ERRCODE));

     {$IFDEF OPL}
      write(f, byte(MENU_MACC));

      write(f, byte(tab_mFPL));
      write(f, byte(tab_cFPL));
      write(f, byte(tab_oFPL));
      write(f, byte(tab_mFPL_abc));

      write(f, byte(_propose_dayFPLM));
      write(f, byte(_unactive_dayFPLM));

      write(f, byte(_preactived_FPLM));
      write(f, byte(_preactived_FPLO));
        write(f, byte(_preactived_FPLM_ot));
        write(f, byte(_preactived_FPLO_ot));

      write(f, byte(_proposed_FPLM));              { vyziadane pripomienky }
      write(f, byte(_proposed_FPLO));
        write(f, byte(_proposed_FPLM_ot));
        write(f, byte(_proposed_FPLO_ot));

      write(f, byte(_coordinated_FPLM));           { schvalene pripomienky }
      write(f, byte(_coordinated_FPLO));
        write(f, byte(_coordinated_FPLM_ot));
        write(f, byte(_coordinated_FPLO_ot));

      write(f, byte(_activated_FPLM_ot));
      write(f, byte(_activated_FPLO_ot));
     {$ENDIF}


     {$IFDEF EDD}
       write(f, byte(miniSTRIP));
      {$IFDEF LINE_STRIP}
       write(f, byte(lineSTRIP));
      {$ENDIF}

      write(f, byte(GraphMode_MAPA));

      write(f, byte(PROP_ACK_cFPL));
      write(f, byte(PROP_ACK_mFPL));
      write(f, byte(PROP_ACK_oFPL));
      write(f, byte(PROP_WARN));
      write(f, byte(PROP_SCROLL));

      {$IFDEF PRN}
       write(f, byte(REC_PROP_PRN));
       write(f, byte(PROP_PRN));
       write(f, byte(PRN_cFPL));
       write(f, byte(PRN_mFPL));
       write(f, byte(PRN_oFPL));
      {$ENDIF}

      {write(f, byte(TABLET_CFG_SAVE));}
       write(f, byte(NDB_OTHERS));
       write(f, byte(NDB_NULL));
       write(f, byte(NDB_INP));
       write(f, byte(NDB_SL));
       write(f, byte(NDB_XY));
       {$IFDEF FIND_EQ_NDB}
        write(f, byte(NDB_EQ));
       {$ENDIF}

       write(f, byte(STRIP_DIR));
       for d:= low(STRIP_DIR_) to high(STRIP_DIR_) do write(f,byte(STRIP_DIR_[d]));
       write(f, byte(STRIP_SORT));

      {$IFDEF TRENAZER_UDP}
       write(f, byte(SIM_UNIX));
      {$ENDIF}
      {$IFDEF TRENAZER_IPX}
       b:= get_trenazer_adr; {write(f, b);}
      {$ENDIF}
     {$ENDIF}


      write(f, byte(CNL_RPL_VYPIS));
      write(f, byte(CNL_VYPIS));
      write(f, byte(DEC_VYPIS));
      write(f, byte(ARR_VYPIS));

      write(f, byte(STAV_PLANU));

      {write(f, byte(bminiSTRIP));}
      write(f, byte(ionSTRIP));    {$IFNDEF ionSTRIP} ionSTRIP:= false; {$ENDIF}

      write(f, byte(alt_VFR_sym));
      write(f, byte(in_FL));
      write(f, byte(in_km));

      write(f, byte(pis_STRIP_10b));
      write(f, byte(pis_STRIP_EST));
      write(f, byte(pis_STRIP_COR));
      write(f, byte(pis_STRIP_ACK));
      {write(f, byte(pis_STRIP_SSN));}


     { ------------------------------------
         DATA
       ------------------------------------
     }
      write_word(f, casPRED);
      write_word(f, casPRIST);


     {$IFDEF RPL}
      write_word(f, rpl_hour);
      write_word(f, rpl_min);

      write(f, byte(rpl_PND));
      write(f, byte(rpl_ERR));

      write(f, byte(bminiRPL));
      write_word(f,max_RPL_15_rm);
      write_word(f,max_RPL_18_rm);
      write(f, byte(RUSSIAN_RPL));

      write(f, byte(prn_RPL_IFPS));

      write(f, byte(rpl_assign_15));
     {$ENDIF}


     {$IFDEF PLN}
      write(f, byte(pln_PND));
      write(f, byte(pln_ADR));
      write(f, byte(pln_FPL));
      write(f, byte(pln_ERR));

      write(f, byte(RUSSIAN_PLN));

      write(f, byte(pln_assign_15));
     {$ENDIF}


     {$IFDEF FPL4}
      write_word(f, dT_preactive_FPL4);
      write_word(f, dT_propose_FPL4);
      write_word(f, dT_coordinate_FPL4);
      write_word(f, dT_unactive_FPL4);
      {write_word(f, dT_deactive_FPL4);}

      write(f, byte(_FPL4_PPL_ENABLE));
      write(f, byte(_FPL4_CHG_ENABLE));
      write(f, byte(_FPL4_DLA_ENABLE));
      write(f, byte(_FPL4_CNL_ENABLE));
      write(f, byte(_FPL4_DEP_ENABLE));
      write(f, byte(_FPL4_ARR_ENABLE));
      write(f, byte(_FPL4_CPL_ENABLE));

      write(f, byte(_FPL4_MZP_ENABLE));
      write(f, byte(_FPL4_XG_ENABLE));

      write(f, byte(_9b_CHECK_ICAO));
      write(f, byte(_9b_CHECK_TSGA));
      write(f, byte(_9b_CHECK_ZZZZ));
      write(f, byte(_9b_CHECK_MIL));
      write(f, byte(_9c_CHECK_ICAO));
      write(f, byte(_9c_CHECK_ZZZZ));

      write(f, byte(_10a_CHECK));
      write(f, byte(_10a_CHECK));

      write(f, byte(_15a_RANGE));
      write(f, byte(_15b_RANGE));

      write(f, byte(_15_RxR_ENABLE));
      write(f, byte(_15_BxR_ENABLE));
      write(f, byte(_15_BxR_KM));
      write_word(f,_15_XYxR);
      write_word(f,_15_BxR);

      write(f, byte(_15_DCT_POINTS));
      write(f, byte(_15_UPLNA_TRAT));

      {_15_IO_ENABLE:= read_bool(f);
      FULL_RTE:= read_bool(f);
      UNKN_RTE:= read_bool(f);
      }

      write(f, byte(_18_CHECK_IS));
      write(f, byte(_18_CHECK));
      write(f, byte(_18_TYPE_CHECK));
      write(f, byte(_18_DAT_CHECK));
      write(f, byte(_18_COM_NAV_CHECK));
      write(f, byte(_18_DEP_CHECK));
      write(f, byte(_18_DEST_CHECK));
      write(f, byte(_18_ALTN_CHECK));
      write(f, byte(_18_RALT_CHECK));

      write(f, byte(_EFIL_8));
      write(f, byte(_EFIL_9));
      write(f, byte(_EFIL_10));
      write(f, byte(_EFIL_15ab));

      write(f, byte(_CHG__7_13));
      write(f, byte(_FPL_CHG__14_17));
      write(f, byte(_ACT__FIELDS));
      write(f, byte(_ARR__FIELDS));

      write(f, byte(_ACT_OR_DEP));
      write(f, byte(_ACT_AS_EST));
      write(f, byte(_AP_EET_EXI));

      write(f, byte(find_and_process_FPL4));
      write(f, byte(find_and_process_FDR));
      write(f, byte(_propose_dayFPL4));
      write(f, byte(_unactive_dayFPL4));

      write(f, byte(bminiFPL4));
      write(f, comp_FPL4);
      write(f, byte(ZDROJ_PLANU));

      write_word(f,max_FPL4_15_rm);
      write_word(f,max_FPL4_18_rm);

      write(f, byte(_FPL4_REPORT_PLAN));
      write(f, byte(_FPL4_CHG_REPORT));
      write(f, byte(_FPL4_DLA_REPORT));
      write(f, byte(_FPL4_CNL_REPORT));
      write(f, byte(_FPL4_DEP_REPORT));
      write(f, byte(_FPL4_ARR_REPORT));

      write(f, byte(_FPL4_APROVED_DISPLAY));
      write(f, byte(_FPL4_APROVED_CHECK));
      write(f, byte(_FPL4_APROVED_BY_FDA));

      write(f, byte(prn_FPL4_ICAO));

      {write(f, byte(ACT_as_EST));}

      {$IFDEF A36YKA}
       write(f, byte(RUSSIAN_FPL));
      {$ENDIF}

      {$IFDEF FDA}
       {write(f, byte(tab_FPL4prea));}
       write(f, byte(tab_FPL4prop));
       write(f, byte(tab_FPL4coor));
      {$ENDIF}
     {$ENDIF}


     {$IFDEF FPL0}

     { FPLC
     }
      write(f, byte(FPLC_CPL));
      write(f, byte(FPLC_CPL_SSR));

      write(f, byte(FPLC_ARR));
      write(f, byte(FPLC_CHECK_15));

      write_word (f,est_dT_pred);
      write_word (f,est_dT_po);

      write_word (f, dT_deactive_FPLC);
      write_word (f, dT_deactive_NOPL);

      write_word (f, prehlad_arch_fn_cFPL);
      write(f, byte(pis_STRIP_cFPL));
      write(f, byte(miniSTRIP_cFPL));

      write(f, byte(find_and_process_FPLC));

     { FPLM
     }
      write_word (f, dT_propose_FPLM);
      write_word (f, dT_unactive_FPLM);
      write_word (f, dT_arr_warn_FPLM);
      write_word (f, dT_deactive_FPLM);

      write_word (f, dT_propose_FPLM_REQ);
      write_word (f, dT_deactive_FPLM_REQ);

      write(f, byte(FPLM_INE));
      write(f, byte(FPLM_INE_9));
      write(f, byte(FPLM_INE_AP));

      write(f, byte(KRL_FPLM_CNL));

      write(f, byte(FPLM_REQ_WARN));
      write(f, byte(FPLM_DEP_WARN));

      write(f, byte(FPLM_ARR_WARN));
      write(f, byte(FPLM_ARR_WARN_ALL));

      write(f, byte(bminimFPL));
      write_word (f, max_mFPL_15_rm);
      write_word (f, max_mFPL_18_rm);
      write(f, byte(pis_STRIP_mFPL));
      write(f, byte(pis_STRIP_mFPL_15body));
      write(f, byte(miniSTRIP_mFPL));

      write(f, byte(prn_FPLM_ICAO));

      write(f, byte(hlas_vlastne_FPLM));
      write(f, byte(hlas_vsetky_FPLM));
      write(f, byte(hlas_riadene_FPLM));
      write(f, byte(varovanie_FPLM));

      write(f, byte(find_and_process_FPLM));

      write(f, byte(FPLM_REGULARITA_FPLM));
      write(f, byte(FPLM_REGULARITA_FUA_PLAN));
      write(f, byte(FPLM_REGULARITA_FUA_ACT));
      write(f, byte(FPLM_REGULARITA_FIR));


      {$IFDEF SSR_MANAGEMENT}
       write(f, byte(FPLC_SSR));
       write(f, byte(FPLM_SSR));

       write(f, byte(SSR_NEXT_USE_KEEP));
       write_word (f, SSR_NEXT_USE);

       {write(f, byte(SSR_LIST));
       write(f, byte(SSR_ASSIGN));
       write(f, byte(SSR_NOT_CFG));}
      {$ENDIF}

      {$IFDEF FLI_COORDINATION}
       write(f, byte(send_FLI));
       write(f, byte(display_FLI_ERR));
       write_word(f,limit_FLI);

       write(f, byte(update_FPLC_by_FLI));
       write(f, byte(delete_FPLC_by_FLI));
      {$ENDIF}

     {$ENDIF}

      {write(f, b);}

     {$IFDEF ZAM}
      write(f, byte(hlas_ZAM));
      write(f, byte(varovanie_ZAM));

      write (f, byte(bminiZAM));
      write (f, byte(pis_STRIP_ZAM));
      write (f, byte(miniSTRIP_ZAM));

      write_word (f,dt_propose_ZAM);
      write_word (f,dT_deactive_ZAM);
     {$ENDIF}


     {$IFDEF QGO}
      write(f, byte(hlas_QGO));
      write(f, byte(varovanie_QGO));
     {$ENDIF}

     {$IFDEF RTZ}
      write(f, byte(hlas_RTZ));
      write(f, byte(varovanie_RTZ));
     {$ENDIF}


     {$IFDEF DVZ}
      write(f, byte(hlas_DVZ));
      write(f, byte(hlas_vsetky_DVZ));
      write(f, byte(varovanie_DVZ));
      write(f, byte(posliZiadostDVZ));
     {$ENDIF}


     {$IFDEF PRS}
      write (f, byte(PRS_CHECK_VYS_REG));

      write (f, byte(hlas_PRS_plan));
      write (f, byte(hlas_PRS_act));
      write (f, byte(find_and_process_PRS));

      write (f, byte(bminiPRS));
      write_word (f,max_PRS_pozn_rm);
      write (f, byte(pis_STRIP_PRS));
      write (f, byte(miniSTRIP_PRS));

      write_word (f,dT_propose_PRS );
      write_word (f,dT_unactive_PRS);
      write_word (f,dT_deactive_PRS);
     {$ENDIF}

     {$IFDEF NOTAM}
      write_word (f,max_NTM_D_rm);
      write_word (f,max_NTM_E_rm);
     {$ENDIF}

     {$IFDEF MET}
       write (f,byte(pis_SYN_));
     {$ENDIF}


     {$IFDEF SPR}
      write (f,byte(SPR_ACK_WAIT));
      write (f,byte(bminiSPR));
      write_word (f,max_SPR_am);
      write_word (f,max_SPR_rm);
     {$ENDIF}


     {$IFDEF TLG}
      write(f, byte(tlg_SS));
      write(f, byte(tlg_FF));
      write(f, byte(tlg_KK));

      write(f, byte(tlg_SSprint));
      write(f, byte(tlg_FFprint));
      write(f, byte(tlg_KKprint));

      write(f, byte(tlg_Print));
      write(f, byte(tlg_PrintAll));

      {$IFDEF A36YKA}
        write(f, byte(RUSSIAN_TLG));
      {$ENDIF}
     {$ENDIF}

     {$IFDEF STATISTIKA}
       {$IFDEF STATISTIKA_PRELETY}
        write(f, byte(prn_FPS_FLO));
       {$ENDIF}
     {$ENDIF}


     { ------------------------------------
         FUNCTIONs
       ------------------------------------
     }
     {$IFDEF SECTORS}
      write(f, byte(S_DISPLAY));
      write(f, byte(S_PRINT));
      write(f, byte(S_ARCHIV));
      write(f, byte(S_D_IN_THROUGH));
      write(f, byte(S_P_IN_THROUGH));
      write(f, byte(S_TOUCH));
      write(f, byte(S_INP_POINT_TIME));
      write(f, byte(S_OUT_POINT_TIME));
      write_word(f, S_IN_KM);
      write_word(f, S_EST_LIMIT);
      write_word(f, S_DEL_LIMIT);
      write(f, byte(S_ROUTE));
      write(f, byte(S_IN));
     {$ENDIF}

     {$IFDEF MAPY}
      write(f, byte(saveMAPY));
      write(f, byte(cursMAPY));

      write(f, byte(draw_mFPL_en));
      write(f, byte(draw_cFPL_en));
      write(f, byte(draw_oFPL_en));

      write(f, byte(draw_SSR));

      write(f, byte(mark_typ));
      write(f, byte(mark_txt));
      write(f, byte(mark_8x8));

      write(f, byte(HLAS_NENAJDENA_MAPA));
     {$ENDIF}

     {$IFDEF PRN}
      write(f, byte(is_PRN));
      write(f, byte(PRN_REC));
      write(f, byte(PRN_CHG));
      write_word(f, PRINTER_COM);
      write_word(f, PRN_TAB);
      write(f, byte(PRN_NET));
     {$ENDIF}


     { ------------------------------------
         EXTERNAL DEVICES
       ------------------------------------
     }

     {$IFDEF EXTERNAL_NET}
      write(f, byte(icao_ERR_DISPLAY));
      {write(f, byte(icao_UNKN_ERR));}
      write(f, byte(icao_HEAD_ERR));
      write(f, byte(icao_HEAD_ERR_TLG));
      write(f, byte(icao_REC_UPDATED));
     {$ENDIF}

     {$IFDEF CONNECT_TO_ASTA_EXT}
      write(f, byte(power_ASTA));
      write(f, byte(power_ASTA_FDP));
      write(f, byte(power_ASTA_PRN));
      write(f, byte(writeln_ASTA));
      write(f, byte(process_ASTA_CPL));
     {$ENDIF}

     {$IFDEF CONNECT_TO_OPL_EXT}
      write(f, byte(line_master_OPL));
      write(f, byte(power_OPL_async));
      write(f, byte(power_OPL_udp));

      write(f, byte(writeln_OPL));
      write(f, byte(writeln_OPL_HeartBeat));
      write(f, byte(OPL__SAVE_STREAM));
      write(f, byte(OPL__LAM_NOT_FOUND));
      write(f, byte(OPL__UNCOMPLETE_PKT));

      write_word(f, aup_hour);
      write_word(f, aup_min);

      write(f, byte(OPL__PROCESS_AUP));
      write(f, byte(OPL__REQUEST_AUP));
      write_word(f,OPL__REQUEST_AUPi);

      write(f, byte(OPL__PROCESS_RTZ));
      write(f, byte(OPL__REQUEST_RTZ));
      write_word(f,OPL__REQUEST_RTZi);

      write(f, byte(OPL__PROCESS_ASM));
      write(f, byte(OPL__PROCESS_ASMfda));
     {$ENDIF}

     {$IFDEF CONNECT_TO_CAMUS}
      write(f, byte(power_CAMUS));
      write(f, byte(writeln_CAMUS));
     {$ENDIF}

     {$IFDEF CONNECT_TO_ASOC}
      write(f, byte(power_ASOC));
      write(f, byte(writeln_ASOC));
     {$ENDIF}

     {$IFDEF CONNECT_TO_VERA}
      write(f, byte(power_VERA));
      write(f, byte(writeln_VERA));
     {$ENDIF}

     {$IFDEF CONNECT_TO_AFTN}
      write(f, byte(power_AFTN));
      write(f, byte(aftn_DUAL_LINE));
      write(f, byte(aftn_MASTER_LINE));
      write(f, byte(writeln_AFTN));
      write(f, byte(archive_AFTN));
      write(f, byte(writeln_AFTN_utc));
     {$ENDIF}

     {$IFDEF CONNECT_TO_BGU}
      write_word(f,BGU_DEL);
     {$ENDIF}


     { ------------------------------------
         ARCHIVATION
       ------------------------------------
     }
      write_word(f, ArchDays);
      write(f, byte(archive_COM));

     {$IFDEF WRITELN_NET}
      write(f, byte(writeln_NET_REC));
      write(f, byte(writeln_NET_SEND));
      write(f, byte(writeln_NET_DATA));
      write(f, byte(writeln_NET_ACK));
      write(f, byte(writeln_NET_HeartBeat));
      write(f, byte(writeln_MEM));
     {$ENDIF}

     {$IFDEF ARCHIVE_DAR}
      write(f, byte(archive_DAR));
     {$ENDIF}

     {$IFDEF X25}
      write(f, byte(X25_archive));
     {$ENDIF}

      Close(f)
    end;
