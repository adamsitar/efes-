constructor O_AFTN_UA.Init(_Owner: PObject);
      begin
        inherited Init(_Owner, 'AFTN'+firExt, @hd_AFTN_UA, ord(msPPL)-ord(msALR)+1{sizeof(hd_AFTN_UA) div sizeof(Thead_ICAO)});
      end;


function O_AFTN_UA.read_cfg (_cfg_FN: string): bool;
   begin
     read_cfg := inherited read_cfg(_cfg_FN);

    {$IFDEF FPD}
     soh1_PLN := {delchar(}read_cfg_str_(_cfg_FN, cfg_soh1_PLN, _PLN.soh1_PLN){,[' '])};
     soh2_PLN := {delchar(}read_cfg_str_(_cfg_FN, cfg_soh2_PLN, _PLN.soh2_PLN){,[' '])};
     eoh_PLN  := {delchar(}read_cfg_str_(_cfg_FN, cfg_eoh_PLN,  _PLN.eoh_PLN){, [' '])};
     adr_PLN  := {delchar(}read_cfg_str_(_cfg_FN, cfg_adr_PLN,  _PLN.adr_PLN){, [' '])};
    {$ENDIF}

     txt_TEST := read_cfg_str_(_cfg_FN, cfg_txt_TEST,
                 '›››››››››››››››››››››››››››››››››'
                 );

     RUSSIAN_FPL := read_cfg_bool(_cfg_FN,cfgRUSSIAN_FPL,RUSSIAN_FPL);
     RUSSIAN_FPD := read_cfg_bool(_cfg_FN,cfgRUSSIAN_FPD,RUSSIAN_FPD);
   end;
