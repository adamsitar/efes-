{ Test sa nepotrebuje ukladat. Staci, ak sa zobrazuje.
}
 function O_AFTN_TSGA._process_TLG_TEST (data: pchars; size: word): bool;
    var   i,p : int;
          s : string;
    begin
      i:= 1; p:= get_str_items (data,size, setNL);
      while (i<=p) do
        begin
          s:= get_str(data,size, i, setNL, sizeof(string)-1);
          if s=txt_TEST then break;
          inc(i)
        end;
      _process_TLG_TEST:= i<=p
    end;


 function O_AFTN_TSGA.process_data_TLG (src: TPKT_SRC; data: pchars; size: word; var res: string): bool;
    var   i,pi : int;
    begin
      process_data_TLG:= true;
      res:= '';
      if _process_TLG_TEST(data,size) then
      {$IFDEF PLN}
       else if _process_PLN(src,data,size, res) then
      {$ENDIF}
      else process_data_TLG:= inherited process_data_TLG (src,data,size,res)
    end;