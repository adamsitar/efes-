{ -------------------------
  Mapa, inicializacia
  -------------------------
}

{$IFDEF LIS}
  {$I ed_map1.inc}
{$ENDIF}

procedure MAPY_init(_Owner     : PGroup;

                    _p_mapy_en : pointer;
                    _p_ciele   : pointer; { Tproc_b  }
                    _p_handle  : pointer; { Tproc_vE }
                    _p_cursor  : pointer  { Tproc }
                    );

    var   i : int;
    begin
      {$IFDEF LIS} Set_USer_Priority; {$ENDIF}
      Mapa:= New(PMapa,Init(_Owner, _p_mapy_en,_p_ciele,_p_handle,_p_cursor));
      {$IFDEF LIS}   Mapa^.Vytvor_obmedz_lst {$ENDIF};

      adrMapaPoint:= Mapa
    end; { InitMAPs }
