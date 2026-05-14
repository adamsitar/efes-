{ vyhladanie, ci existuje zaznam o aktualnom pouziti daneho
  kodu (pridelenie inemu letu/nevyprsaniu timeoutu)...

}
 function _is_ssr_used (last: real): int;
    var   r : real;
    begin
      r:= SSR_NEXT_USE; r:= r*60;
      if absTime <= last then _is_ssr_used:= err_ssr_is_used
      else if absTime < last + r then _is_ssr_used:= err_ssr_time_out
      else _is_ssr_used:= -1
    end;


 function  _ssr_in_use (flight1,flight2: string; last1: real): int;
    var    ires : int;
    begin
      if eq_str(flight1,flight2) then ires:= -1
      else ires:= _is_ssr_used(last1);
      _ssr_in_use:= ires
    end;


 function  ssr_in_use (code: string; flight: string): int;
    var    ires : int;
    begin
      ssr_in_use:= -1;
      {$IFNDEF BN_MANAGEMENT}
       if (length(code)=kod_uvd_BN) then Exit;
      {$ENDIF}
      ires:= SSRs^.najdi(code);
      if ires>-1 then ires:= _ssr_in_use (strpas(SSRs^.ssr_a^[ires]^.flight),flight, SSRs^.ssr_a^[ires]^.last);
      ssr_in_use:= ires
    end;



 function _ssr_configured (mil: pbool; ssr: p_ssr_record): bool; far;
    begin
      _ssr_configured:=      (_is_ssr_used(ssr^.last)=-1)
                         and (   ((not mil^) and (ssr^.user in [ssr_atca{,uvd_atca}]))
                              or (mil^ and (ssr^.user in [ssr_mil{,uvd_mil}]))
                             )
    end;

 function  ssr_configured (code: string; mil: bool{; var res: string}): int;
    var    ires : int;
    begin
      ssr_configured:= 0;
      {$IFNDEF BN_MANAGEMENT}
        if (length(code)=kod_uvd_BN) then Exit;
      {$ENDIF}
      ires:= -1;
      {$IFDEF SSR_MANAGEMENT}
       ires:= SSRs^.najdi (code);
       if    (ires<0)
          or ((not mil) and (not (SSRs^.ssr_a^[ires]^.user in [ssr_atca,uvd_atca])))
          or (mil and (not (SSRs^.ssr_a^[ires]^.user in [ssr_mil,uvd_mil])))
          then {l4_err(a_ssr,code,0,err_ssr_not_cfg, res)};
      {$ENDIF}
      ssr_configured:= ires
    end;
