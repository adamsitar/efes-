procedure decode_SECTOR_PASSWORD(const pkt: TNETpkt); far;
    var   s : string;
          m : mask_SECTORs;
          p : pchars;
    begin
      move(pkt.pkt.data^[0],m,sizeof(m));

      {$IFDEF SECTORS} {IFNDEF DEBUG}
       proc_SECTOR_chg(m,true);
      {$ENDIF} {ENDIF}

      {$IFDEF EXIT_PASSWORD}
       if MainApp<>nil then
          begin
            s:= strpas(pchar(pkt.pkt.data^[sizeof(m)]));
            MainApp^.set_password(cut_(s))
          end
      {$ENDIF}
    end;
