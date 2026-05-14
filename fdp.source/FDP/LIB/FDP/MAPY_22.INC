{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TNextMapa                                                €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

constructor TNextMapa.Init(_Owner: PGroup;
                           x,y,dx,dy: int; _title: string;
                           _OMapa: PMapa; _cfg: string
                          );
      begin
        inherited Init(_Owner, x,y, dx,dy, kbEnter, cmClose, _title, true);
        CM:= New(PCopyMapa,Init(@Self, x0+11,y0+31,dx-22,dy-8, _OMapa,_cfg))
      end;

procedure TNextMapa.Image;
    begin
      on_off(x0+10,y0+30,x1-10,y1-10, clBUTTON_COLOR+clBUTTON_DARK,clBUTTON_COLOR+clBUTTON_LIGHT, btSmall, btOFF)
    end;



procedure zobraz_trat(tit: string; _OBs: POBxys; _bodov : int; dx,dy: int; cl: byte);
    const f  : Tcentr = (x: initX; y: initY; m: 1);
    var   NM : PNextMapa;
          M  : PMapData;
          E  : TEvent;

          W  : PWindow;
    begin
      if Mapa=nil then Exit;

      NM:= New(PNextMapa,Init(nil, f.x,f.y, dx,dy, tit, Mapa, 'FPL'));
      NM^.MoveWin(f.x,f.y, f.m);
      M := NM^.CM^.zapni_trat(NM^.CM^.zTrat, _OBs, _bodov, tit, cl);
      ZOBRAZ_MAPU:= true;
      NM^.Run(E);
      ZOBRAZ_MAPU:= false;
      NM^.CM^.vypni_trat(NM^.CM^.zTrat,M);
      Dispose(NM,Done)
    end;
