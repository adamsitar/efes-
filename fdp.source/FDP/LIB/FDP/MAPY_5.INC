{---------------------------------------}
{ Vykreslenie:                          }
{---------------------------------------}

procedure TMapa.Mapa(_Data : PMapData);
    var   FillInfo      : FillSettingsType;
          _adrMapaPoint : PMapa;
    begin
      _adrMapaPoint:= adrMapaPoint; adrMapaPoint:= @Self; { nesmie obsahovat Main }
      if (not _Data^.kr) or (_Data^.GP=nil) then Exit;
      GetFillSettings(FillInfo);
      SetFillStyle(SolidFill,_Data^.cl);
      SetColor(_Data^.cl);
      _Data^.GP^.kresli;
      with FillInfo do SetFillStyle(Pattern, Color);
      adrMapaPoint:= _adrMapaPoint
    end; { Mapa }


procedure TMapa.Symbol(_Data : PMapData);
    begin
    end; { Symbol }


procedure TMapa.kresli_mapy(_ZozMap: PZozMap);
    var   PData : PMapData;
    begin
      if (_ZozMap<>nil) and (_ZozMap^.DejPocet>0) then
         begin
           _ZozMap^.JdiNaZacatek;
           repeat
             Mapa(_ZozMap^.DejAktPrvek)
           until _ZozMap^.JdiNaDalsi_
         end
    end;


procedure TMapa.uvolni_data(PData: PMapData);
    begin
      with PData^ do
      if not kr and (GP <> nil) then
         begin
           Dispose(GP,Done);
           GP:= nil
         end
    end;


procedure TMapa.nacitaj_data(PData: PMapData);
    begin
      if PData^.kr and (PData^.GP = nil) then mapy_najdi_a_nacitaj_data(PData)
    end;


procedure TMapa.pracuj_s_pamatou;
    var   PData : PMapData;
    begin
      zMapy^.JdiNaZacatek;
      repeat
        PData:= zMapy^.DejAktPrvek;
        if PData=nil then break;
        uvolni_data(PData)
      until zMapy^.JdiNaDalsi_;

      zMapy^.JdiNaZacatek;
      repeat
        PData := zMapy^.DejAktPrvek;
        if PData=nil then break;
        nacitaj_data(PData)
      until zMapy^.JdiNaDalsi_
    end; { Pracuj_s_pamatou; }


procedure TMapa.kresli(_map_init: bool);
    var   ViewPort : ViewPortType;
          bp: bool; xlm,ylm: int;
    begin
      reinit_(GraphMode);
      if not MAPY_DRAW_en then Exit;
      map_init:= _map_init;
      m_off (bp, xlm,ylm);

      if map_init or FILLOVAT then
         begin
           if map_init then Pracuj_s_pamatou;
           FillWin(x0,y0,x1,y1,MAPsBACKGROUND)
         end;
      if active then ActiveOn else ActiveOff;
      GetViewSettings(ViewPort);
      SetViewPort(x0{+1},y0{+1},x1{-1},y1{-1},true);
      kresli_mapy(zMapy);
      kresli_mapy(zTrate);
      kresli_mapy(zTrat);
      SetWritemode(0);
      with ViewPort do SetViewPort(x1,y1,x2,y2,clip);
      if (not MAPSCROLL) and (p_ciele<>nil) {and (su_mapy)} then TProc_b(p_ciele)(map_init or FILLOVAT);

      m_on (bp, xlm,ylm);
      map_init:= false
    end; { kresli }


procedure TMapa.Draw;
    begin
      if ({(p_mapy_en=nil) or (bool(p_mapy_en^))}PLANZET_MAPA or ZOBRAZ_MAPU) then Kresli(true)
    end;
