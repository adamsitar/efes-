(*-------------------------------------------------------------------*)
(* LETVIS FDP - EDD_func                                             *)
(* (c) Ales Kosice 1995  (ab)                                        *)
(*-------------------------------------------------------------------*)
{$I comp.h}


unit EDD_func;


interface


     uses   TypeDef,
            _L4_def, _FDP_def
            {$IFDEF FPL}
             , _FPL_def, _FPL, _FPL4, _FPLc, _FPLm
            {$ENDIF}
            ;


     {$IFDEF FPL}
      procedure search_SSR;
      procedure search_SSR_;

      procedure search_CODE;
      procedure search_CODE_;
     {$ENDIF}


implementation

{$IFDEF FPL}

uses  bios, str0, sets,
     {$I unit_gr.h},
     {$I unit_net.h},
      Scroll, Dialog, Lists, Edit, Msg,
      Body,
      FDP_msg,
      _FPLms,
      FDP_NET;


 function  _search_SSR(ssr: string; iFPL: P_OFPL): bool;
     var   i : int;
           b : bool;
     begin
       i:= 0; b:= false;
       while (i<=iFPL^.top) do
         begin
           if iFPL^.is_ssr(i,ssr) then begin iFPL^.zobraz(iFPL^.ap^[i]); b:= true end;
           inc(i)
         end;
       _search_SSR:= b
     end;

 procedure search_SSR;
     const s: string[kod_7a]='';
     var   b: bool;
     begin
       if (not formular_s(s,kod_7c, 'SSR code',@fn_7b,1,@set_7c,@setNil,0, nil,false,true,true,nil)) or (s='') then Exit;
       b:= false;
      {$IFDEF EDD}
       b:= _search_SSR(s,PROP_cFPL) or b;
       b:= _search_SSR(s,PROP_mFPL) or b;
       {$IFDEF FPLO}
        b:= _search_SSR(s,PROP_oFPL) or b;
       {$ENDIF}
      {$ENDIF}
       b:= _search_SSR(s,cFPL) or b;
       {$IFNDEF FPLM_DISABLED}
        b:= _search_SSR(s,mFPL) or b;
        {$IFDEF FPLO}
         b:= _search_SSR(s,oFPL) or b;
        {$ENDIF}
       {$ENDIF}
       if not b then Say2(msgSEARCH, s+' - '+msgDATA_NOT_FOUND)
     end;


 function filter_search_SSR_(FPL: PDcFPL; ssr: pstring): bool; far;
    begin
      filter_search_SSR_:= (FPL^.ssr=ssr^) or (FPL^.ssr0=ssr^)
    end;

 procedure search_SSR_;
     const s: string[kod_7a]='';
     begin
       if (not formular_s(s,kod_7c, 'SSR CODE',@fn_7b,1,@set_7c,@setNil,0, nil,false,true,true,nil)) or (s='') then Exit;
       spracuj_cFPL('',false, @_arch_fn_cFPL, nil, @s, @filter_search_SSR_,
                    @handle__spracuj_ukoncene_cFPL, _TBFunc_p,
                    tit_arch_cFPL, nil,nil
                   )
     end;


 function _search_CODE(code: string; iFPL: P_OFPL): int;
    var   ind: int;
    begin
      ind:= iFPL^.find_id(code);
      if ind>=0 then iFPL^.zobraz(iFPL^.ap^[ind]);
      _search_CODE:= ind
    end;

 procedure search_CODE;
     const s : string[kod_7a]='';
     var   b : bool;
     begin
       if (not formular_s(s,kod_7a, 'CALLSIGN',nil,1,@setABC,@setNil,0, nil,false,true,true,nil)) or (s='') then Exit;
      {$IFDEF EDD}
       b:= (_search_CODE(s,PROP_cFPL)>-1) or b;
       b:= (_search_CODE(s,PROP_mFPL)>-1) or b;
       {$IFDEF FPLO}
        b:= (_search_CODE(s,PROP_oFPL)>-1) or b;
       {$ENDIF}
      {$ENDIF}
       b:= (_search_CODE(s,cFPL)>-1) or b;
      {$IFNDEF FPLM_DISABLED}
       b:= (_search_CODE(s,mFPL)>-1) or b;
       {$IFDEF FPLO}
        b:= (_search_CODE(s,oFPL)>-1) or b;
       {$ENDIF}
      {$ENDIF}
       if not b then Say2(msgSEARCH, s+' - '+msgDATA_NOT_FOUND)
     end;


 function filter_search_CODE_(FPL: PDcFPL; idn: pstring): bool; far;
    begin
      filter_search_CODE_:= eq_str(FPL^.idn,idn^)
    end;

 procedure search_CODE_;
     const s: string[kod_7a]='';
     begin
       if (not formular_s(s,kod_7a, 'CALLSIGN',nil,1,@setABC,@setNil,0, nil,false,true,true,nil)) or (s='') then Exit;
       spracuj_cFPL('', false, @_arch_fn_cFPL, nil, @s, @filter_search_CODE_,
                    @handle__spracuj_ukoncene_cFPL, _TBFunc_p,
                    tit_arch_cFPL, nil,nil
                   )
     end;

{$ENDIF}

end.
