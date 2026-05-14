
{ ----------------------------
  Init, Done
  ----------------------------
}

procedure MAPsubmenu_init(MMenu: PSubmenu); far; forward;


constructor TMapa.Init(_Owner : PGroup;
                       _p_mapy_en : pointer;
                       _p_ciele   : pointer; { Tproc_b  }
                       _p_handle  : pointer; { Tproc_vE }
                       _p_cursor  : pointer  { Tproc    }
                      );
      begin
        inherited Init(_Owner,0,0,0,0);
        MCursor:= KRIZ; Active:= true;

        p_mapy_en:= _p_mapy_en;
        p_ciele  := _p_ciele;
        p_handle := _p_handle;
        p_cursor := _p_cursor;

        zMapy := New( PZozMap, {PListMan,} Init {(SizeOf(TMapData))} );
        zTrate:= New( PZozMap, {PListMan,} Init {(SizeOf(TMapData))} );
        zTrat := New( PZozMap, {PListMan,} Init {(SizeOf(TMapData))} );

        {$IFDEF LIS} CO_ROBIT:= cmNil; cmXXXX := cmOK; {$ENDIF}

        read_cfg_fn(APP_MAPS_CFG);

        dcXvystred:= 0;
        dcYvystred:= 0;
      end; { Init }


destructor TMapa.Done;
     begin
       done_maps(zTrat);
       done_maps(zTrate);
       done_maps(zMapy)
     end; { Done }


{ ----------------------------
  inView, Active..., ReInit
  ----------------------------
}

function TMapa.inView(x,y: int): bool;
   begin
     inView:= ({(MAPY_EN=nil) or (bool(MAPY_EN^))}PLANZET_MAPA or ZOBRAZ_MAPU) and inherited inView(x,y)
   end;

procedure TMapa.m_shape;
    begin
      if (p_cursor<>nil) and (cursMAPY) then Tproc(p_cursor)
      else m_cursor(MCursor)
    end;


procedure TMapa.ActiveOn;
    begin
      active:= true;
      SetColor(clGR5);
      Rectangle(x0,y0,x1,y1)
    end;

procedure TMapa.ActiveOff;
    begin
      active:= false;
      SetColor(clGR3);
      Rectangle(x0,y0,x1,y1)
    end;

{
  _dx>0 -> posun zlava
  _dx<0 ->       zprava
}
procedure TMapa.reinit_(_mode: TGraphMode);
    const _dk1 : array[Low(TGraphMode)..High(TGraphMode)] of int = (640,640,800,1024,1280); {(600,670,830,1162,1400);}
          _dk2 : array[Low(TGraphMode)..High(TGraphMode)] of int = (640,640,800,1024,1280);
          _dTyy: array[Low(TGraphMode)..High(TGraphMode)] of int = (100,120,100,180 ,160 );
    begin
      if Rozsah < 2000 then Rozsah:= 2000;

      dK1 := _dK1[_mode];
      dK2 := _dK2[_mode];
      dTyy:= _dTyy[_mode];

      Xs1 := Xvystred+Rozsah/2;
      Xs2 := Xvystred-Rozsah/2;
      Ys1 := Yvystred+Rozsah/2;
      Ys2 := Yvystred-Rozsah/2;
      Kon1:= dK1/Rozsah;
      Kon2:= dK2/Rozsah;

      XY(0,btMapydXY.y0, MaxX - btMapydXY.x1, MaxY - btMapydXY.y1-btMapydXY.y0)
    end;



procedure Nevojde(s: string);
    begin
      Say(msgWARNING,msgMEMORY+s+'.',white,red, nil,nil, 3, 0,nil,nil)
    end;


procedure  TMapa.done_maps(var _ZozMap: PZozMap);
    var    PData : PMapData;
    begin
      if _ZozMap=nil then Exit;
      Dispose(_ZozMap,Done);
      _ZozMap:= nil
    end;


{ Definuje sa jednoznacny kluc pre indentifikaciu planu medzi mapami,
  lebo nazov mapy (napr. priestor) moze byt pouzity viacnasobne...
  Mapy sa hladaju podla kluca, ak je='', az potom podla nazvu.
}
function najdi_mapu(ZozMap: PZozMap; naz,key: string; _stMapStat: bool): PMapData;
   var   Map, PMap : PMapData;
         is_k,is_n : bool;
   begin
     PMap:= nil;
     if (ZozMap<>nil) and ((naz<>'') or (key<>'')) then
        begin
          if _stMapStat and (naz<>'') then if naz[1]<>st_MapStat then naz:= st_MapStat+naz;
          ZozMap^.JdiNaZacatek;
          repeat
            Map:= ZozMap^.DejAktPrvek;
            if (Map<>nil) then
               begin
                 is_n:= eq_str(naz,Map^.naz);
                 is_k:= eq_str(key,strpas(Map^.key));
                 if    ((key<>'') and (is_k and (is_n or (naz=''))))
                    or ((key='')  and (is_k and (is_n and (naz<>'')))) then
                     begin
                       PMap:= Map;
                       break
                     end
               end;
          until ZozMap^.JdiNaDalsi_
        end;
     najdi_mapu:= PMap
   end;


