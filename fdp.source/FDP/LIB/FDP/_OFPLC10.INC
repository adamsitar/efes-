procedure OcFPL.plan(p: pointer);
    begin
     { Musim robit externu refenciu, lebo sa zacyklim
     }
      p_info_FPLc(p,'')
    end;


{$IFDEF MAPY}

   procedure OcFPL.get_sur(p: pointer; var sur: Tsur);
       begin
         sur:= DcFPL(p^).sur
       end;


   procedure OcFPL.set_sur(p: pointer; sur: Tsur);
       begin
         PDcFPL(p)^.sur:= sur
       end;


   function OcFPL._target_coordinates(p: pointer; cas: real; var sur: Tsur): Tpoz;
      begin
        _target_coordinates:= suradnice_cFPL(p,cas,sur)
      end;



   function OcFPL.get_mapa(p: pointer): PMapData;
      begin
        get_mapa:= DcFPL(p^).mapa
      end;

   procedure OcFPL.set_mapa(p: pointer; mapa: PMapData);
       begin
         DcFPL(p^).mapa:= mapa
       end;

   procedure OcFPL.get_mapa_par(p: pointer;
                                var Trat : POBxys; var bodov : int;
                                var Trat_: POBxys; var bodov_: int;
                                var MapNaz: string
                               );
       var   FPL : PDcFPL;
             T   : array[0..{sizeof(Tc_trat) div TOB + 2} max_bod_FPLC + 1] of TOBxy;
             i   : int;
       begin
         FPL   := PDcFPL(p);
         MapNaz:= cut_(FPL^.idn);

       { profil trate pre cFPL je uz rozpocitany od ACC,
         ujo len naplni otocne body na trase
       }
         FillChar(T,sizeof(T),0);
         bodov_:= 0;
         if get_OB_XY(FPL^.start.kod, T[0]) then { AIP }
            begin
              {$IFDEF EDD}
                T[0].kod := FPL^.start.kod;
                T[0].h   := FPL^.start.h;
                T[0].m   := FPL^.start.m;
              {$ENDIF}
              T[0].casA:= FPL^.start.cas;
              T[0].casD:= T[0].casA;
              inc(bodov_)
            end;

         for i:= 0 to FPL^.bodov do
           if get_OB_XY(FPL^.trat[i].kod, T[bodov_]) then { OB alebo NDB }
              begin
                {$IFDEF EDD}
                  T[bodov_].kod := FPL^.trat[i].kod;
                  T[bodov_].h   := FPL^.trat[i].h;
                  T[bodov_].m   := FPL^.trat[i].m;
                {$ENDIF}
                T[bodov_].casA:= FPL^.trat[i].cas;
                T[bodov_].casD:= FPL^.trat[i].cas;
                inc(bodov_)
              end;

         if get_OB_XY(FPL^.prist.kod, T[bodov_]) then { AIP }
            begin
              {$IFDEF EDD}
                T[bodov_].kod := FPL^.prist.kod;
                T[bodov_].h   := FPL^.prist.h;
                T[bodov_].m   := FPL^.prist.m;
              {$ENDIF}
              T[bodov_].casA:= FPL^.prist.cas;
              T[bodov_].casD:= T[bodov_].casA;
              inc(bodov_)
            end;

         GetMem(Trat_,sizeof(TOBxy)*bodov_);
         for i:= 0 to bodov_-1 do Trat_^[i]:= T[i]
       end;

{$ENDIF}
