 procedure new_SSR (ssr1, ssr2: p_ssr_record); far;
     begin
       FillChar(ssr2^,SizeOf(ssr2^),0);
       if ssr1<>nil then
          begin
            ssr2^:= ssr1^;
            ssr2^.flight:= StrNew(ssr1^.flight);
          end
     end;

 procedure  disp_SSR (ssr: p_ssr_record); far;
     begin
       if ssr=nil then Exit;
       with ssr^ do
         begin
           StrDispose(flight);
         end;
     end;

 function eq_SSR (SSR1, SSR2: p_ssr_record): bool; far;
    begin
      eq_SSR:=      ((SSR1<>nil) and (SSR2<>nil))
                and (codekey_SSR(SSR1) = codekey_SSR(SSR2))
    end;


{ ulozenie spravy o pouziti ssr kodu
}
 procedure ssr_save (code: string; flight: string; last: real; stat: string);
    var    ssr  : t_ssr_record;
           db   : PDB;
           ires : int;
    begin
      {$IFNDEF BN_MANAGEMENT}
        if (length(code)=kod_uvd_BN) then Exit;
      {$ENDIF}

      fillchar(ssr,sizeof(ssr),0);
      ssr.code:= code;
      ires:= SSRs^.najdi(code);
      if ires>-1 then new_SSR(SSRs^.ssr_a^[ires],@ssr)
      else ssr.user:= ssr_user;

      strdispose(ssr.flight);
      if stat<>cnst_CNL then
         begin
           ssr.last:= last;
           ssr.flight:= strpasnew(flight)
         end
      else ssr.last:= 0;

      SSRs^.add(@ssr);

      db:= New(PDB, Init(fn_db__ssr,false,db_SSR_RIADKOV,@codeDB_SSR,@decodeDB_SSR,@codekey_SSR,nil,dbattr_SSR));
      ires:= db^.najdi(@ssr,false,nil); { kvoli zisteniu, ci ssr je konfigurovany }
      db^.zapis(@ssr,ires,false);
      Dispose(db,Done);
      disp_SSR(@ssr);
    end;


 procedure ssr_zrus (code: string);
    var    i : int;
    begin
      {$IFNDEF BN_MANAGEMENT}
        if (length(code)=kod_uvd_BN) then Exit;
      {$ENDIF}
      ssr_save (code,'',0,hd_CNL);
      i:= SSRs^.najdi(code);
      if (i>-1) and (SSRs^.ssr_a^[i]^.user=ssr_user) then SSRs^.del(i)
    end;
