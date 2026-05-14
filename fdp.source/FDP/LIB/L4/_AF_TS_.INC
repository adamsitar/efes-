 function O_AFTN_TSGA.read_cfg (_cfg_FN: string): bool;
    begin
      read_cfg := inherited read_cfg(_cfg_FN);

      {$IFDEF PLN}
       soh1_PLN := {delchar(}read_cfg_str_(_cfg_FN, cfg_soh1_PLN, _PLN.soh1_PLN){,[' '])};
       soh2_PLN := {delchar(}read_cfg_str_(_cfg_FN, cfg_soh2_PLN, _PLN.soh2_PLN){,[' '])};
       eoh_PLN  := {delchar(}read_cfg_str_(_cfg_FN, cfg_eoh_PLN,  _PLN.eoh_PLN){, [' '])};
       adr_PLN  := {delchar(}read_cfg_str_(_cfg_FN, cfg_adr_PLN,  _PLN.adr_PLN){, [' '])};
      {$ENDIF}

      test_AFTN_TSGA:= read_cfg_str_(_cfg_FN, cfg_TEST,test_AFTN_TSGA);
    end;


 constructor O_AFTN_TSGA.Init;
       begin
         semaphor_pln:= false;
         is_PLN:= false;
         inherited Init('', nil,nil, @hd_AF_TSGA, sizeof(hd_AF_TSGA) div sizeof(Thead_ICAO));
       end;


 procedure O_AFTN_TSGA.HandleEvent(var _Event: TEvent);

     begin
       inherited HandleEvent(_Event);

       if isCommand (_Event,cm_PLNpended) then
          begin
            {$IFDEF PLN}
             _read_PLN;
            {$ENDIF}
            ClearEvent(_Event)
          end
     end;


 procedure O_AFTN_TSGA.check;
     begin
       inherited check;
       {$IFDEF PLN}
        manage_PLN
       {$ENDIF}
     end;


 procedure O_AFTN_TSGA.initialize_STATUS(_draw: bool);
     begin
       {$IFDEF PLN}
        is_PLN:= najstarsi_subor(pathTLG,'*.'+extPLN)<>'';
       {$ENDIF}
       inherited initialize_STATUS(_draw);
     end;

