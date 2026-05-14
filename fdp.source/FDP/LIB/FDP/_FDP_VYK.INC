{$IFDEF MAPY}

  const xp: int = 0;
        yp: int = 0;

  procedure mapa_cursor_shape;
      var   x,y, i : int;
            res    : bool;
      begin
        if (abs(mouse_status.stat.x-xp)>RADIUS) or (abs(mouse_status.stat.y-xp)>RADIUS) then
           begin
             x:= mouse_status.stat.x + (-Moff[mouse_status.curs].x) - Mapa^.x0;   { xl+Mapa^.x0 = m_x + (-Moff[KRIZ].x) }
             y:= mouse_status.stat.y + (-Moff[mouse_status.curs].y) - Mapa^.y0;
           { obchadzam virtualne metody, aby to bolo rychlejsie... }
             res:= false;
            {$IFDEF FPL0}
             i:= 0; while (not res) and (i<=cFPL^.top) do
               begin
                 res:= inRadius(PDcFPL(cFPL^.ap^[i])^.sur.xl_,PDcFPL(cFPL^.ap^[i])^.sur.yl_, x,y,RADIUS);
                 inc(i)
               end;
             i:= 0; while (not res) and (i<=mFPL^.top) do
               begin
                 res:= inRadius(PDmFPL(mFPL^.ap^[i])^.sur.xl_,PDmFPL(mFPL^.ap^[i])^.sur.yl_, x,y,RADIUS);
                 inc(i)
               end;
            {$IFDEF FPLO}
             i:= 0; while (not res) and (i<=oFPL^.top) do
               begin
                 res:= inRadius(PDmFPL(oFPL^.ap^[i])^.sur.xl_,PDmFPL(oFPL^.ap^[i])^.sur.yl_, x,y,RADIUS);
                 inc(i)
               end;
            {$ENDIF}
             if res then
                begin
                  m_cursor(CIEL);
                 {if cursBEEP then beep(300,100)}
                end
             else m_cursor(Mapa^.MCursor);
            {$ENDIF}
             xp:= mouse_status.stat.x; yp:= mouse_status.stat.y
           end
      end;

  procedure mapa_handle_target(var _Event: TEvent);
      var   i, x,y: int;
            res   : bool;
      begin
       {$IFDEF FPL0}
        if not cFPL^.handle_target(_Event) then
           if not mFPL^.handle_target(_Event) then
             {$IFDEF FPLO}
               oFPL^.handle_target(_Event)
             {$ENDIF}
       {$ENDIF}
      end;


  procedure imit_targets(mapa_init: bool);
      begin
        if (not PLANZET_MAPA) or (OpenWins>0) {or (not su_mapy)} then Exit;

        OBNOV_CIELE:= false;
        if mapa_init then
           begin
            {$IFDEF FPL0}
             cFPL^.init_targets;
             mFPL^.init_targets;
             {$IFDEF FPLO}
              oFPL^.init_targets
             {$ENDIF}
            {$ENDIF}
           end;

        {$IFDEF FPL0}
          cFPL^.targets(mapa_init);
          mFPL^.targets(mapa_init);
          {$IFDEF FPLO}
           oFPL^.targets(mapa_init)
          {$ENDIF}
        {$ENDIF}
      end;

  procedure show_targets;
      begin
        if (not PLANZET_MAPA) or (OpenWins>0) then Exit;
       {$IFDEF FPL0}
        cFPL^.show_targets;
        mFPL^.show_targets;
        {$IFDEF FPLO}
         oFPL^.show_targets
        {$ENDIF}
       {$ENDIF}
      end;

  procedure hide_targets;
      begin
        if (not PLANZET_MAPA) or (OpenWins>0) then Exit;
       {$IFDEF FPL0}
        cFPL^.hide_targets;
        mFPL^.hide_targets;
        {$IFDEF FPLO}
         oFPL^.hide_targets
        {$ENDIF}
       {$ENDIF}
      end;


  {procedure targets_font;
      begin
        draw_trgt_rte:= true;
        hide_targets;
        draw_FONT:= (draw_FONT + 1) mod 1;
        show_targets;
        draw_trgt_rte:= false
      end;

  procedure targets_history;
      begin
        draw_trgt_rte:= true;
        hide_targets;
        draw_HISTORY:= not draw_HISTORY;
        if draw_HISTORY then draw_trgt_his:= true;
        show_targets;
        draw_trgt_his:= false;
        draw_trgt_rte:= false
      end;}


 procedure pozri_vykreslenie; far;
     const semaphor : bool = false;
           T        : real = 0;
     begin

      { ---------------------------------------------
         vykreslenie cielov na trati
        תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
      } {$IFDEF MAPY}
         if       (PLANZET_MAPA)
              and (OpenWins=0)
              and (not semaphor)
              and (   OBNOV_CIELE or OBNOV_MAPU
                   or (    (T<>absTime)
                       and (   (OBNOVENIE_CIELOV=0)
                            or ((sec mod OBNOVENIE_CIELOV)=0)
                           )
                      )
                  ) then
              begin
                semaphor:= true;
                T:= absTime;
                if OBNOV_MAPU then
                   begin                   { nastavene pri odmazani ciela z obrazovky }
                     OBNOV_MAPU:= false;
                     Mapa^.Draw
                   end
                else imit_targets(false);  { prepocet poloh a ich zobrazenie }
                semaphor:= false
              end;
        {$ENDIF}

       { --------------------------------------------
          zmena polohy vo vypise planov
         תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
       } {$IFDEF FPL0}
          {if (PREPIS__VYPIS_PLANOV) and (OpenWins=1) then
             begin
               PREPIS__VYPIS_PLANOV:= false;

               if (cFPL^.viewer<>nil) and (cFPL^.viewer^.visible) then cFPL^.viewer^.List;
               if (mFPL^.viewer<>nil) and (mFPL^.viewer^.visible) then mFPL^.viewer^.List;
               if (oFPL^.viewer<>nil) and (oFPL^.viewer^.visible) then oFPL^.viewer^.List;
             end;}
        {$ENDIF}
     end;

{$ENDIF}