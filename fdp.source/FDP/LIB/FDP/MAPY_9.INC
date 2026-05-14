{ ------------------------------
   Pridanie/zrusenie mapy trate
  ------------------------------
}
function  TMapa.zapni_trat(_ZozMap: PZozMap;
                           _Trat: POBxys; _bodov: int; _MapNaz: string;
                           _MapCl: byte
                          ): PMapData;
    var   Map  : PMapData;
    begin
      zapni_trat:= nil;

      Map:= new_MapOb(_MapNaz,gr_TPoly, map_FPL,0, _MapCl, true,true);
      Map^.GP:= New(PTTPoly,Init(_Trat,_bodov,_MapCl));

      _ZozMap^.PridejNaKonec(Map);
      zapni_trat:= Map
    end; { NewMapa }


procedure TMapa.vypni_trat(_ZozMap: PZozMap; _Map: PMapData);
    begin
      { Dispose(_Map^.GP,Done); -> urobi dalsi prikaz }
      _ZozMap^.ZrusPrvek(_Map)
    end;



{ ---------------------------------
  Pridanie/zrusenie mapy priestoru
  ---------------------------------
}
  function  TMapa.zapni_mapu(N: string;
                             p_GrOb,v_GrOb: pointer;
                             key: string; typ: word; mapf: TGRPfill;
                             PIS: bool
                            ): PMapData;
      var   Map : PMapData;
      begin
        zapni_mapu:= nil;

        N:= cut_(N);
        if (p_GrOb<>nil) and (p_GrOb<>nil) and (zMapy<>nil) then
           begin
           { Mapa definovana externe : }
             Map:= TPFunc_p{s}(p_GrOb)(v_GrOb{,key});
             if Map<>nil then zMapy^.PridejNaKonec(Map)
           end
        else begin
             { vyhladanie mapy v pamati : }
               Map:= najdi_mapu(zMapy, N,key, true);
               if (Map=nil) or ((Map<>nil) and (Map^.typ<>typ)) then
                  begin
                  { vyhladanie mapy na disku... }
                    if (Map=nil) then Map:= mapy_najdi_a_nacitaj_subor(N,{key,} zMapy, true);
                  end;
             end;

        if (Map<>nil) then
           begin
           { nastavenie parametrov }
             Map^.naz:= st_MapStat+N;
             StrDispose(Map^.key); Map^.key:= strpasnew(key);
             Map^.plan:= true;
             mapy_set_fill(zMapy,Map, mapf, typ,typ {Map^.prior});
             if PIS then Draw else OBNOV_MAPU:= true
           end;

        zapni_mapu:= Map
      end;


  function  TMapa.vypni_mapu(N,key: string; PIS: bool): bool;
      var   Map : PMapData;
      begin
        Map:= najdi_mapu(zMapy, N,key, true);
        vypni_mapu:= Map<>nil;
        if Map<>nil then
           begin
             zMapy^.ZrusPrvek(Map);
             if PIS then Draw else OBNOV_MAPU:= true
           end
      end;
