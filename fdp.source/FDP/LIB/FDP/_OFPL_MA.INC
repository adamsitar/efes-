{$IFDEF MAPY}

   function O_FPL.sur_eq(p,ip: pointer): bool;
      var   sur1,sur2: Tsur;
      begin
        get_sur(p,sur1); get_sur(ip,sur2);
        sur_eq:= (sur1.xl_=sur2.xl_) and (sur2.yl_=sur2.yl_)
      end;

   procedure O_FPL.get_sur(p: pointer; var sur: Tsur);
       begin
         fillchar(sur,sizeof(sur),0)
       end;

   procedure O_FPL.set_sur(p: pointer; sur: Tsur);
       begin
       end;

   procedure O_FPL.init_sur(p: pointer; clear: bool);
       var   sur: Tsur;
       begin
         get_sur(p, sur);
         if clear then fillchar(sur,sizeof(sur),0)
         else begin
                sur.is:= false; sur.xl_:= 0; sur.Lp:= 0
              end;
         set_sur(p, sur)
       end;



  { ----------------------------
    VYKRESLENIE CIELOV
    ---------------------------- }
   {
     prepocet historie do aktualnej mierky, sur je kopia
   }
   procedure O_FPL._target_history(p: pointer; var sur: Tsur);
       var   i: int;
       begin
         i:= 0;
         while (i<max_his) do
           begin
             if (sur.his[i].x<>0) then
                begin
                  Mapa^.Point(sur.his[i].x,sur.his[i].y);
                  sur.his[i].x:= Mapa^.Txx;
                  sur.his[i].y:= Mapa^.Tyy
                end;
             inc(i)
           end;
       end;

   {
    rozhodne, ci ciel sa ma kreslit
   }
   function O_FPL._target_coordinates(p: pointer; cas: real; var sur: Tsur): Tpoz;
      begin
        _target_coordinates:= poz_STOJI
      end;


   {
    vypocet suradnic ciela a jeho vykreslenie
   }
   procedure O_FPL._target(p,ip: pointer; mapa_init: bool);
       var   ViewPort : ViewPortType;
             sur,_sur : Tsur;
             poz      : Tpoz;
             bp : bool; xlm,ylm : int;
             i, xl,yl : int;
             xl_,yl_,xh_,yh_ : real;
       begin
         poz:= _target_coordinates(p, absTime, sur);

         if    (sur.is) and ((poz in [poz_SEDI,poz_HANGAR])
            or ((not draw_MZP) and (poz=poz_MZP)))
            or ((not draw_PATRAT) and (poz=poz_PATRAT))
               then zmaz_plan_na_mape(p,true);
         if not (poz in pozACT) then Exit;

         if mapa_init then sur.is:= false
         else if not sur.is then mapa_init:= true;

         if not (bool(ciele_en^)) then
            begin
            { zmaze ciel na suradniciach xl,yl s pl_ }
              zmaz_plan_na_mape(p, not draw_trgt_rte)
            end;

         Mapa^.Point(sur.x ,sur.y );  sur.xl_:= Mapa^.Txx; sur.yl_:= Mapa^.Tyy;
         Mapa^.Point(sur.xl,sur.yl);  xl:= Mapa^.Txx;      yl:= Mapa^.Tyy;
         if (sur.is) and (xl=sur.xl_) and (yl=sur.yl_) then Exit;

         m_off (bp, xlm,ylm);

         GetViewSettings(ViewPort); with Mapa^ do SetViewPort(x0+1,y0+1,x1-1,y1-1,true);

       { A) trat letu ------------------------ }

         xl_:= sur.xl; yl_:= sur.yl;

         if bool(ciele_en^) then
            begin
            { a) odmazanie starej polohy }
              if (sur.is) and (draw_trgt<>nil) then Tdraw_trgt(draw_trgt)(p, xl,yl, sur, true);  { Vymaz }

            { b) vykreslenie novej polohy }
              sur.is:= true;
              sur.Lp:= 0;
              if ip<>nil then for i:= 0 to int(ip^)-1 do
                 begin
                   get_sur(ap^[i],_sur);
                   if (sur.xl_=_sur.xl_) and (sur.yl_=_sur.yl_) then inc(sur.Lp)
                 end;
              if (draw_trgt<>nil) then Tdraw_trgt(draw_trgt)(p, sur.xl_,sur.yl_, sur, false);  { Poloz }
            end;

         sur.xl:= sur.x; sur.yl:= sur.y;


       { B) historia letu -------------------- }

       { a) ak sa ciel vykresluje opat, polozi sa i historia }
         if (mapa_init or draw_trgt_his or (poz=poz_MZP)) and (bool(ciele_en^)) then
            begin
              _sur:= sur;
              _target_history(p, _sur);
              draw_trgt_history(_sur, false, cl_ciel);
              _sur:= _sur
            end;

         if (sur.xl<>0) and (xl_<>0) then
            begin
              if (not (inRadius(sur.xl,sur.yl, sur.xh,sur.yh, ds_HISTORY))) then
                 begin  {((sec div 5) * 5 = sec) (not (inRadius(sur.xl,sur.yl, sur.xh,sur.yh, 5))) }
                 { b) odmazanie posledneho bodu historie }
                   if (sur.is) and (sur.his[max_his-1].x<>0) then
                      begin
                        Mapa^.Point(sur.his[max_his-1].x,sur.his[max_his-1].y);
                        if (bool(ciele_en^)) then draw_trgt_history_point(Mapa^.Txx,Mapa^.Tyy,false,cl_ciel)
                      end;
                   Move(sur.his[0],sur.his[1],sizeof(THis_xy)*(max_his-1));
                   sur.his[0].x:= 0; sur.his[0].y:= 0;

                 { c) zaradenie posledneho bodu na trati ako prveho v historii }
                   sur.his[0].x:= sur.xh; sur.his[0].y:= sur.yh;
                   if (sur.is) and (bool(ciele_en^)) then
                       begin
                         Mapa^.Point(sur.his[0].x,sur.his[0].y);
                         draw_trgt_history_point(Mapa^.Txx,Mapa^.Tyy,false,cl_ciel)
                       end;

                   sur.xh:= sur.xl; sur.yh:= sur.yl
                 end
            end;

         with ViewPort do SetViewPort(x1,y1,x2,y2,clip);
         m_on(bp, xlm,ylm);
         set_sur(p,sur)
       end;


   {
    vypocet suradnic cielov a ich vykreslenie
   }
   procedure O_FPL.targets(mapa_init: bool);
       var   i: int;
       begin
         if PLANZET_MAPA then
            begin
              i:= 0;
              while i<=top do
                begin
                  _target(ap^[i],@i, mapa_init);
                  CheckProcesses0;
                  inc(i)
                end
            end
       end;

   procedure O_FPL.init_targets;
       var   i  : int;
       begin
         for i:= 0 to top do init_sur(ap^[i],false)
       end;

   procedure O_FPL.hide_targets;
       begin
         bool(ciele_en^):= false;
         targets(true)
       end;

   procedure O_FPL.show_targets;
       begin
         bool(ciele_en^):= true;
         targets(false)
       end;



  { ----------------------------
    VYKRESLENIE TRATE
    ---------------------------- }


   procedure O_FPL.zobraz_plan_na_mape(p: pointer);
       begin
        { mozem polozit ciel, namiesto obnovy cielov }
         OBNOV_CIELE:= true
       end;

   procedure O_FPL.zmaz_plan_na_mape(p: pointer; _del: bool);
       var   sur, _sur : Tsur;
             ViewPort  : ViewPortType;
             bp : bool; xlm,ylm: int;
       label X;
       begin
         get_sur(p, sur);
         if (not sur.is) then goto X;
         if (not PLANZET_MAPA) or (OpenWins>0) then begin OBNOV_MAPU:= true; goto X end;

         if (draw_trgt<>nil) then
            begin
              m_off (bp, xlm,ylm);
              GetViewSettings(ViewPort); with Mapa^ do SetViewPort(x0+1,y0+1,x1-1,y1-1,true);

              _sur:= sur;
              _target_history(p, _sur);
              draw_trgt_history(_sur, false, cl_ciel);

              Mapa^.Point(sur.xl,sur.yl);
              Tdraw_trgt(draw_trgt)(p, Mapa^.Txx,Mapa^.Tyy,sur, true);

              with ViewPort do SetViewPort(x1,y1,x2,y2,clip);
              m_on (bp, xlm,ylm);
            end;

         X: init_sur(p,false);
            if _del then del_mapa(p)
       end;


   {
     vrati adresu mapy p^.m z planu p^
   }
   function  O_FPL.get_mapa(p: pointer): PMapData;
      begin
        get_mapa:= nil
      end;

   {
     nastavi adresu mapy p^.m do planu p^
   }
   procedure O_FPL.set_mapa(p: pointer; mapa: PMapData);
       begin
       end;



   procedure O_FPL.get_mapa_par(p: pointer;
                               var Trat: POBxys; var bodov: int;
                               var Trat_: POBxys; var bodov_: int;
                               var MapNaz: string
                              );
       begin
       end;


   procedure O_FPL.put_mapa(M: PMapData);
       var   ViewPort: ViewPortType;
             bp: bool; xlm,ylm: int;
       begin
         m_off (bp, xlm,ylm);
         with Mapa^ do
           begin
             GetViewSettings(ViewPort);
             SetViewPort(x0{+1},y0{+1},x1{-1},y1{-1},true);
             Mapa(M);
             if FILLOVAT then SetWritemode(8) else SetWritemode(XORput);
             with ViewPort do SetViewPort(x1,y1,x2,y2,clip)
           end;
         m_on (bp, xlm,ylm);
       end;

   {
     vykreslenie trate letu
   }
   procedure O_FPL.draw_mapa(M: PMapData);
       var   ViewPort: ViewPortType;
       begin
         Mapa^.Pracuj_s_pamatou;
         put_mapa(M)
       end;

   {
     zmazanie trate letu
   }
   procedure O_FPL.hide_mapa(M: PMapData);
       begin
         put_mapa(M)
       end;

   {
     - vyrobi mapa, alokuje, prida ju a nakresli.
     - premenna Trat_ sa pouzije pre naplnenie Mapy,
       ak premenna Trat nie je sucastnou zaznamu iFPL.
       Rusi sa v tejto procedure. Usetrim tym nadbytocnu
       virtualnu fciu.
   }
   procedure O_FPL.add_mapa(p: pointer);
       var   M             : PMapData;
             Trat, Trat_   : POBxys;
             bodov, bodov_ : int;
             MapNaz        : string;
       begin
         Trat:= nil; Trat_:= nil; M:= nil;
         get_mapa_par(p, Trat,bodov, Trat_,bodov_, MapNaz);
         if (Trat<>nil) then M:= Mapa^.zapni_trat(Mapa^.zTrate, Trat, bodov, MapNaz, cl_trat)
         else if (Trat_<>nil) then
                 begin
                   M:= Mapa^.zapni_trat(Mapa^.zTrate, Trat_, bodov_, MapNaz, cl_trat);
                   FreeMem(Trat_, sizeof(TOBxy)*bodov_)
                 end;
         if (M<>nil) then
            begin
              set_mapa(p,M);
              if (PLANZET_MAPA) and (OpenWins=0) then draw_mapa(M)
              else OBNOV_MAPU:= true
            end
       end;

   {
     odmaze a odalokuje mapa
   }
   procedure O_FPL.del_mapa(p: pointer);
       var   M: PMapData;
       begin
         M:= get_mapa(p);
         if M<>nil then
            begin
              if (not PLANZET_MAPA) or FILLOVAT or (OpenWins>0) then OBNOV_MAPU:= true
              else hide_mapa(M);
              Mapa^.vypni_trat(Mapa^.zTrate,M)
            end;
         set_mapa(p,nil)
       end;



  { ----------------------------
     HandleEvent: Plan,Trasa
    ---------------------------- }

   {
     kontrola, ci suhlasia suradnice
   }
   function  O_FPL._handle_target(var _Event: TEvent; p: pointer): bool;
      var    TRGmenu: PWinMenu;
             x,y: int;
      var    poz: Tpoz; sur: Tsur;
      begin
        _handle_target:= false;
        if not ((_Event.What = evMouseClick) and bool(_Event.M.bt and mbLeftButton)) then Exit;

        x:= _Event.m.x + (-Moff[_Event.m.curs].x) - Mapa^.x0;   { xl+Mapa^.x0 = m_x + (-Moff[KRIZ].x) }
        y:= _Event.m.y + (-Moff[_Event.m.curs].y) - Mapa^.y0;
        get_sur(p, sur);
        if inRadius(sur.xl_,sur.yl_, x,y, RADIUS) then
           begin
             poz:= get_poz(p);
             if not (poz in [poz_START,poz_LETI,poz_MZP,poz_STOJI,poz_DALSI,poz_PRIST,poz_PATRAT]) then Exit;

             TRGmenu:= WinMenu(' '+get_id(p)+' ',nil,
                          Item(tit_VIEW,  cm_PLAN_VIEW,
                          Item(tit_DRAW,  cm_PLAN_DRAW,
                          nil ) )
                       );
             TRGMenu^.MoveRel(x+10-TRGMenu^.x0,y+20-TRGMenu^.y0);
             TRGMenu^.Run(_Event);
             if ((_Event.What and evMessage) <> 0) then
                case _Event.Command of
                  cm_PLAN_VIEW  : zobraz(p);
                  cm_PLAN_DRAW  : if get_mapa(p)=nil then add_mapa(p)
                                  else del_mapa(p);
                end;
             Dispose(TRGmenu, Done);
             ClearEvent(_Event,@Self);
             _handle_target:= true;
           end
      end;

   function  O_FPL.handle_target(var _Event: TEvent): bool;
      var    i: int;
      begin
        i:= 0;
        while (i<=top) and (not _handle_target(_Event, ap^[i])) do inc(i);
        handle_target:= i<=top
      end;

{$ENDIF}