procedure Sprava_o_zapnuti;
    var   i : int;
    begin
      for i:= 0 to NODEpoc-1 do NETsend_msg (NODEs^[i].desc.adr, spr_ON, nil,0, true,net_flag_SEND)
    end;

procedure Sprava_o_vypnuti;
    var   i : int;
    begin
      for i:= 0 to NODEpoc-1 do NETsend_msg (NODEs^[i].desc.adr, spr_OFF, nil,0, false,net_flag_SEND)
    end;
