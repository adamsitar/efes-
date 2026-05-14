procedure TFDAapp.get_app_config (typ : Tnd_typ; sw : Tnd_sw; nd : Tnd_nd;
                                  var data: pchars; var size: word
                                 );
    var   s: string;
    begin
      s:= ''; data:= nil; size:= 0;
      if sw=BSERVER then
         begin
           s:= chr(ord(BSERVER))+chr(ord(FDA))+chr(ord(SLAVE));
               {spravne by sa mala kontrolovat i dlzka spravy}

           {$IFDEF CONNECT_TO_AFTN}
            s:= s + bool_to_char(aftn_DUAL_LINE)
                  + bool_to_char(aftn_MASTER_LINE);
           {$ENDIF}

           {$IFDEF EXTERNAL_NET}
            {s:= s + bool_to_char(EXTERNAL_NET_DISPLAY);}
            s:= s + bool_to_char(icao_HEAD_ERR);
            s:= s + bool_to_char(icao_HEAD_ERR_TLG);
           {$ENDIF}

           {$IFDEF FPL4}
            s:= s + bool_to_char(_propose_dayFPL4);
            s:= s + word_to_str (dT_preactive_FPL4);
            s:= s + word_to_str (dT_propose_FPL4);
            s:= s + word_to_str (dT_coordinate_FPL4);
            s:= s + word_to_str (dT_deactive_FPLC);
            s:= s + word_to_str (dT_unactive_FPL4);

            s:= s + bool_to_char(_FPL4_PPL_ENABLE);
            s:= s + bool_to_char(_FPL4_XG_ENABLE);
            s:= s + bool_to_char(_ACT_OR_DEP);

            s:= s + bool_to_char(_9b_CHECK_ICAO);
            s:= s + bool_to_char(_9b_CHECK_ZZZZ);
            s:= s + bool_to_char(_9b_CHECK_TSGA);
            s:= s + bool_to_char(_9b_CHECK_MIL);
            s:= s + bool_to_char(_9c_CHECK_ICAO);
            s:= s + bool_to_char(_9c_CHECK_ZZZZ);

            s:= s + bool_to_char(_15a_RANGE);
            s:= s + bool_to_char(_15b_RANGE);
            s:= s + bool_to_char(_15_IO_ENABLE);
            s:= s + bool_to_char(_15_RxR_ENABLE);
            s:= s + bool_to_char(_15_BxR_ENABLE);
            s:= s + word_to_str(_15_XYxR);
            s:= s + word_to_str(_15_BxR);
            s:= s + bool_to_char(_FPL4_MZP_ENABLE);
            s:= s + bool_to_char(_15_DCT_POINTS);
            s:= s + bool_to_char(_15_UPLNA_TRAT);
            s:= s + bool_to_char(_15_ALL_ENABLE);
            s:= s + bool_to_char(_15_CHECK_FDA);

            s:= s + bool_to_char(_18_CHECK_IS);
            s:= s + bool_to_char(_18_CHECK);
            s:= s + bool_to_char(_18_TYPE_CHECK);
            s:= s + bool_to_char(_18_DAT_CHECK);
            s:= s + bool_to_char(_18_COM_NAV_CHECK);
            s:= s + bool_to_char(_18_DEP_CHECK);
            s:= s + bool_to_char(_18_DEST_CHECK);
            s:= s + bool_to_char(_18_ALTN_CHECK);
           {$ENDIF}

           {$IFDEF PLN}
            s:= s + bool_to_char(pln_PND);
            s:= s + bool_to_char(pln_ADR);
            s:= s + bool_to_char(pln_FPL);
            s:= s + bool_to_char(pln_ERR);
           {$ENDIF}

           {$IFDEF FPL0}
            s:= s + bool_to_char(FPLC_ARR);
            s:= s + bool_to_char(FPLC_CHECK_15);

            s:= s + word_to_str(dT_deactive_FPLC);
            s:= s + word_to_str(dT_deactive_NOPL);

            {$IFDEF SSR_MANAGEMENT}
             s:= s + bool_to_char(FPLC_SSR);
             s:= s + bool_to_char(FPLM_SSR);
            {$ENDIF}

           {$ENDIF}
         end;
      size:= length(s);
      if size>0 then
         begin
           getmem(data,size);
           move(s[1],data^,size)
         end
    end;


procedure TFDAapp.set_app_config (const data: pchars; size: word);
    var   s : string;
          p : word;
    begin
      (*
      size:= minimum(size,sizeof(s)-1);
      s[0]:= char(size);
      move(data^,s[1],size);

      if copy(s,1,3) = chr(ord(BSERVER))+chr(ord(FDA))+chr(ord(SLAVE)) then
         begin
           p:= 4;

           {$IFDEF CONNECT_TO_AFTN}
            aftn_DUAL_LINE:= bool(s[p]);
            {$IFDEF BACKUP}
             aftn_MASTER_LINE:= bool(s[p+1]);
            {$ENDIF}
            inc(p,2);
           {$ENDIF}

           {$IFDEF EXTERNAL_NET}
            {EXTERNAL_NET_DISPLAY:= bool(s[p]);}
             icao_HEAD_ERR:= bool(s[p]);
             icao_HEAD_ERR_TLG := bool(s[p+1]);
             inc(p,2);
           {$ENDIF}

           {$IFDEF FPL4}
            _propose_dayFPL4:= bool(s[p]); inc(p);
            dT_preactive_FPL4:= str_to_word(copy(s,p,sizeof(word))); inc(p,sizeof(word));
            dT_propose_FPL4:= str_to_word(copy(s,p,sizeof(word))); inc(p,sizeof(word));
            dT_coordinate_FPL4:= str_to_word(copy(s,p,sizeof(word))); inc(p,sizeof(word));
            dT_deactive_FPLC:= str_to_word(copy(s,p,sizeof(word))); inc(p,sizeof(word));
            dT_unactive_FPL4:= str_to_word(copy(s,p,sizeof(word))); inc(p,sizeof(word));

            _FPL4_PPL_ENABLE:= bool(s[p]); inc(p);
            _FPL4_XG_ENABLE:= bool(s[p]); inc(p);
            _ACT_OR_DEP:= bool(s[p]); inc(p);

            _9b_CHECK_ICAO:= bool(s[p]); inc(p);
            _9b_CHECK_ZZZZ:= bool(s[p]); inc(p);
            _9b_CHECK_TSGA:= bool(s[p]); inc(p);
            _9b_CHECK_MIL:= bool(s[p]); inc(p);
            _9c_CHECK_ICAO:= bool(s[p]); inc(p);
            _9c_CHECK_ZZZZ:= bool(s[p]); inc(p);

            _15a_RANGE:= bool(s[p]); inc(p);
            _15b_RANGE:= bool(s[p]); inc(p);
            _15_IO_ENABLE:= bool(s[p]); inc(p);
            _15_RxR_ENABLE:= bool(s[p]); inc(p);
            _15_BxR_ENABLE:= bool(s[p]); inc(p);
            _15_XYxR:= str_to_word(copy(s,p,sizeof(word))); inc(p,sizeof(word));
            _15_BxR:= str_to_word(copy(s,p,sizeof(word))); inc(p,sizeof(word));
            _FPL4_MZP_ENABLE:= bool(s[p]); inc(p);
            _15_DCT_POINTS:= bool(s[p]); inc(p);
            _15_UPLNA_TRAT:= bool(s[p]); inc(p);
            _15_ALL_ENABLE:= bool(s[p]); inc(p);
            _15_CHECK_FDA:= bool(s[p]); inc(p);

            _18_CHECK_IS:= bool(s[p]); inc(p);
            _18_CHECK:= bool(s[p]); inc(p);
            _18_TYPE_CHECK:= bool(s[p]); inc(p);
            _18_DAT_CHECK:= bool(s[p]); inc(p);
            _18_COM_NAV_CHECK:= bool(s[p]); inc(p);
            _18_DEP_CHECK:= bool(s[p]); inc(p);
            _18_DEST_CHECK:= bool(s[p]); inc(p);
            _18_ALTN_CHECK:= bool(s[p]); inc(p);
           {$ENDIF}

           {$IFDEF PLN}
            pln_PND:= bool(s[p]); inc(p);
            pln_ADR:= bool(s[p]); inc(p);
            pln_FPL:= bool(s[p]); inc(p);
            pln_ERR:= bool(s[p]); inc(p);
           {$ENDIF}

           {$IFDEF FPL0}
            FPLC_ARR:= bool(s[p]); inc(p);
            FPLC_CHECK_15:= bool(s[p]); inc(p);

            dT_deactive_FPLC := str_to_word(copy(s,p,sizeof(word))); inc(p,sizeof(word));
            dT_deactive_NOPL := str_to_word(copy(s,p,sizeof(word))); inc(p,sizeof(word));

            {$IFDEF SSR_MANAGEMENT}
             FPLC_SSR:= bool(s[p]); inc(p);
             FPLM_SSR:= bool(s[p]); inc(p);
            {$ENDIF}

           {$ENDIF}
         end;

      inherited set_app_config (data,size)
      *)
    end;
