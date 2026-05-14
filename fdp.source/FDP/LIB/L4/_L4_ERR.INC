
{ usetrenie pamate a sprehladnenie chyb
}
 function l4_err (arrpos,arrspec: string; errpos,errspec: word; var errs: string): word;
    begin
      l4_err:= _get_err(fnERR_L4, arrpos,arrspec, errpos,errspec, errs)
    end;

 function l4_errs (arrpos,arrspec: string; errspec: word): string;
    var   errs: string;
    begin
      _get_err (fnERR_L4, arrpos,arrspec, 0,errspec, errs);
      l4_errs:= errs
    end;

