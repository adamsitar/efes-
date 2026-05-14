{$IFDEF SECTORS}

{ ps_SECTORS = 'SEC-ALT';
  prev_SECTORS : bool = false;
}

{$I sec_reg.inc}

procedure SECTOR_nastav(var S: TSECTOR; is: bool);
    var   naz: string; was: bool;
    begin
      was:= S.is; naz:= S.nazov;
     {$IFDEF MAPY}
      if (not is) and was and (Mapa<>nil) then Mapa^.vypni_mapu(naz,'%'+naz+'%',false);
     {$ENDIF}
      S.is:= is;
     {$IFDEF MAPY}
      if is and (Mapa<>nil) then Mapa^.zapni_mapu(naz,nil,nil,'%'+naz+'%',map_ACCsecf,_fill_,false);
     {$ENDIF}
    end;

procedure SECTOR_chg(nS: mask_SECTORs; _draw: bool);
    var   i  : int;
          s  : string;
          was,nis, dis : bool;
    begin
      dis:= nS=0;
      if (nS=0) then
         begin
           s:= 'Sectors are not assumed. There is used a standard sectorization.';
           if _draw and (nS<>SECTORm) then Say2(msgWARNING,s);
           nS:= SECTORm
         end;

      was:= false;
      for i:= 0 to nsec-1 do
        begin
          nis:= (nS and (1 shl i))<>0;
          was:= was or (SECTORs^[i]^.is<>nis);
          SECTOR_nastav(SECTORs^[i]^,nis)
        end;

      if was then
         begin
           S_UPDATE:= absTime;
           if not dis then
              begin
                s:= 'Sectorization has been changed.';
                if _draw then Say2(msgMESS,s);
                {archivuj_cmny(s+' ('+cstr(nS,1)+')')}
              end;
           send_mail(MainApp,MainApp,cmSECTOR_CHG, one, nil,0)
         end
    end;

{ nesmie prepustit program dalej, a nenajde mapu sektora
}

procedure nacitanie_sektorov_riadenia;
    var   f     : text;
          i,k   : int;
          s,t,u : string;
          v,v2  : word;
          v_,v2_: char;
          _err,b : bool;
    begin
      _err:= false;
      if Exists(SECcfg)<>0 then RunError('Can not read '+SECcfg+'.');

      {write('Reading '+SECcfg+'...  ');}

      {read_cfg_str (SECcfg,cfg_SEC, SECTOR_adr);
      if Exists(PathToSEC+SECTOR_adr+ext_MAP)<>0 then MessError('Sector file '+SECTOR_adr+' not found.',true,true);
      PathToSEC:= uni_str(read_cfg_str_(SECcfg, cfg_SECTORs, PathToSEC));
      if PathToSEC[length(PathToSEC)]<>'\' then PathToSEC:= PathToSEC+'\';
      }

      nsec:= 0;
      GetMem(SECTORs, max_SECTORs*sizeof(PSECTOR));
      fillchar(SECTORs^, max_SECTORs*sizeof(PSECTOR), 0);

      Assign(f,SECcfg); Reset(f);
      while (not Eof(f)) and (nsec<max_SECTORs-1) do
         begin
           Readln(f,s); s:= uni_str(s);
           if (s='') or (s[1]=';') then continue;

         { nazov mapy sektora
         } t:= getstr(s,2,[';']);
           u:= getstr(t,1,['=']); u:= cut_(u);
           if u<>cfg_SEC then continue;

           New(SECTORs^[nsec]);
           fillchar(SECTORs^[nsec]^,sizeof(SECTORs^[nsec]^),0);

           u:= getstr(t,2,['=']); u:= cut_(u);
           SECTORs^[nsec]^.nazov:= u;

         { nacitanie mapy
         } with SECTORs^[nsec]^ do
             begin
               mapa:= New(PMapy,Init);
               if (mapa^.najdi_a_nacitaj_subor(PathToSEC+nazov+ext_MAP)=nil) then
                  RunError(SECcfg+' -> Can not read file of sector '+SECTORs^[nsec]^.nazov+'.')
             end;

         { nazov sektora
         } t:= getstr(s,1,[';']); t:= cut_(t);
           SECTORs^[nsec]^.meno:= strpasnew(t);

         { rozsah vysok
         } t:= getstr(s,3,[';']);
           u:= getstr(t,1,['=']); u:= cut_(u);
           if u=cfg_ALT then
              begin
                u:= getstr(t,2,['=']); u:= cut_(u);
              { vyskove obmedzenie
              } if (u<>'') then
                   begin
                     b:= decode_l4_vys(getstr(u,1,[icao_ARR,icao_NXT]), v,v_);
                     SECTORs^[nsec]^.vys_0:= get_altM(v_,v) div m_S;
                     b:= decode_l4_vys(getstr(u,2,[icao_ARR,icao_NXT]), v,v_) and b;
                     SECTORs^[nsec]^.vys_1:= get_altM(v_,v) div m_S;
                     if ((u<>'0') and (not b)) or (SECTORs^[nsec]^.vys_1<SECTORs^[nsec]^.vys_0) then
                        begin
                          error_vys (SECcfg,u);
                          _err:= true
                        end;
                   end;
              end;

           {$IFDEF EDD}
             SECTORs^[nsec]^.tablet:= copy(cut_(getstr(s,4,[';'])),1,sizeof(SECTORs^[nsec]^.tablet)-1);
           {$ENDIF}
           inc(nsec)
         end;
      Close(f);

      if nsec=0 then RunError(SECcfg+' -> There is no sector defined.');


    { Priradenie riadenych sektorov ku pracovisku
    }
      s:= uni_str(read_cfg_str_(SECcfg, cfg_SECTOR, ''));
      if s='' then MessError(SECcfg+' -> There is no assumed sector.',true,_err);
      for i:= 1 to getstritems(s,[';',',',' ']) do
         begin
           t:= getstr(s,i,[';',',',' ']);
           k:= 0; while (k<nsec) and (t<>strpas(SECTORs^[k]^.meno)) do inc(k);
           if k>=nsec then RunError('Assumed sector '+t+' is unknown.');
           SECTORs^[k]^.is:= true
         end;

      SECTORm:= 0;
      for i:= 0 to nsec-1 do
        begin
          if SECTORs^[i]^.is then SECTORm:= SECTORm or (1 shl i)
        end;

      if _err then writeln;
    end;

procedure odalokovanie_sektorov_riadenia;
    var   i: int;
    begin
      if SECTORs<>nil then
         begin
           for i:= 0 to nsec-1 do
             begin
               if SECTORs^[i]^.mapa<>nil then Dispose(SECTORs^[i]^.mapa,Done);
               strdispose(SECTORs^[i]^.meno);
               dispose(SECTORs^[i]);
             end;
           FreeMem(SECTORs, max_SECTORs*sizeof(PSECTOR));  {dispose(SECTORs);}
           nsec:= 0
         end;
      SECTORs:= nil
    end;

{$ENDIF}

