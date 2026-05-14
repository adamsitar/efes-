{ ------------------------------------
   f) vypis podanych a prijatych KRL
  ------------------------------------
}

{$IFDEF KRL}

  { all : 0 - nase           0 - archiv
          1 - prijate        1 - dnesne
          2 - vsetky         2 - ppl
  }
  procedure prehlad_KRL (_all: byte; _ppl: byte);
      var   title,fn,cond  : string;
            ppl,arch       : bool;
            p_filter       : pointer;
            p_handler      : pointer;
            p_handler_type : TScrollAct_handler_type;

      begin
        p_handler:= @handle_KRL;
        p_handler_type:= _TBFunc_p2;

        case _all of
          0 :   begin
                  title:= tit_KRLnase;
                  p_filter:= @_kridlo_pre_vlastne_letisko;
                end;
          1 :   begin
                  title:= tit_KRLine;
                  p_filter:= @_kridlo_pre_ine_letisko;
                end;
          else  begin
                  title:= tit_KRLvsetky;
                  p_filter:= @_is_stata_FPLm;
                end
        end;

        ppl:= false; arch:= false;
        cond:= cnl_stat(cnst_all_valid);
        if _ppl=2 then ppl:= true
        else if _ppl=1 then
        else begin
               arch:= true;
               cond:= cnst_all_valid;
             end;

        spracuj_mFPL(false,false,
                     ppl,arch,false,false,
                     cond, p_filter,
                     p_handler,p_handler_type,
                     true,_all<>0, title,
                     nil,nil{hlp_prehlad_KRL}
                    );

        if _all=0 then isKRL:= false
      end;
{$ENDIF}