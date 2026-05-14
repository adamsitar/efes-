procedure TFDAapp.writeln_(pb: pbytes; size: int; cl: byte; ident: string; is_utc, is_NL: bool);
    begin
      inherited writeln_ (pb,size, cl,ident, is_utc,is_NL);
    end;
