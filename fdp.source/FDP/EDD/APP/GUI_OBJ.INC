constructor T_GUI.Init(_Owner: PGroup);
      begin
        inherited Init(_Owner, 0,0,MaxX,MaxY);
        winACC := New(PwinACC,Init(_Owner, miniSTRIP));
       {$IFDEF MAPY}
         MAPY_init(_Owner, @PLANZET_MAPA, @imit_targets, @mapa_handle_target, {nil}@mapa_cursor_shape);
         set_region(0,dMapaY0,0, dMapaY0, btMapydXY);
       {$ENDIF}
        HODINY_init(_Owner, MaxX-150,y0_winPROP+dy_PROP); { musi by pred, lebo sa vykresluje na }
        winPROP:= New(PwinPROP,Init(_Owner));

        last_active:= winPROP;
        hlpXXX:= hlp_GUI;
        hlp_dy0:= winPROP^.reg.y1+10;
        hlp_dy1:= 0;
        sc_dy  := 100;

        appGui:= @Self
      end;

procedure T_GUI.Draw;
    begin
      inherited Draw;
      edd_status;
    end;

procedure T_GUI.Prekreslenie;
    begin
      if ma_sa_prekreslit then
         begin
           edd_status;
           Clock^.Draw;
           PREPIS:= 0;
           PREPISANE:= absTime;
         end;
    end;

