{$IFDEF MAPY}

  procedure OmFPL.get_sur(p: pointer; var sur: Tsur);
      begin
        sur:= DmFPL(p^).sur
      end;

  procedure OmFPL.set_sur(p: pointer; sur: Tsur);
      begin
        PDmFPL(p)^.sur:= sur
      end;



  function OmFPL._target_coordinates(p: pointer; cas: real; var sur: Tsur): Tpoz;
     var   zmena : bool;
     begin
       if (absTime >= PDmFPL(p)^.prist.cas) and (PDmFPL(p)^.poz <> poz_PATRAT) then
          { cas je pocitany na sec, poloha len po min, ciel by zostal vysiet az do celej
          } stav_mFPL(p,absTime,zmena);
       _target_coordinates:= suradnice_mFPL(p,cas,sur)
     end;


  function OmFPL.get_mapa(p: pointer): PMapData;
     begin
       get_mapa:= DmFPL(p^).mapa
     end;


  procedure OmFPL.set_mapa(p: pointer; mapa: PMapData);
      begin
        DmFPL(p^).mapa:= mapa
      end;


  procedure OmFPL.get_mapa_par(p: pointer;
                               var Trat : POBxys; var bodov : int;
                               var Trat_: POBxys; var bodov_: int;
                               var MapNaz: string
                              );
      var   FPL: PDmFPL;
      begin
        FPL   := PDmFPL(p);
        Trat  := FPL^.trat_;
        bodov := FPL^.bodov;
        MapNaz:= get_id(FPL)
      end;

{$ENDIF}