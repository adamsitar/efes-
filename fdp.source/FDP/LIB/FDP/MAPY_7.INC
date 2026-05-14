   procedure TMapa.GetEvent(var _Event: TEvent);
       begin
         inherited GetEvent(_Event);
         with _Event do
           case What of
             evKeyDown :
               case Key of
                 kbEnter         : SetCommand(_Event,cmMAPA_VYSTRED);
                 kb_mapa_CENTRUJ : SetCommand(_Event,cmMAPA_CENTRUJ);
                 kbEsc           : SetCommand(_Event,cmClose);
                 else if kbset_xy(Key) then ClearEvent(_Event)
               end;
             evMouseClick:
               if (What = evMouseClick) and (inView(M.x,M.y)) then
                  if      bool(M.bt and mbLeftButton)  then SetCommand(_Event,cmMAPA_VYSTRED)
                  else if bool(M.bt and mbRightButton) then SetCommand(_Event,cmClose)
           end
       end;


   procedure TMapa.nastav_rozsah(key: char);
       var    _FILLOVAT, _map_init: bool;
             ch: char;
       label L;
       const semaphor: bool= false;
       begin
         if semaphor then Exit;

         semaphor:= true;
         _map_init:= false;
         _FILLOVAT:= FILLOVAT;
         ch:= NULL;

         L: if ch=key then krok:= Maximum(krok - 3, max_krok) else krok:= min_krok;
            ch:= key;
            case key of
              '-'    : Rozsah:= Rozsah+Vy_r(Rozsah);
              '+'    : Rozsah:= Rozsah-Vy_r(Rozsah);
              kbLeft : Stred(Xvystred-Vy_r(Rozsah),Yvystred);
              kbRight: Stred(Xvystred+Vy_r(Rozsah),Yvystred);
              kbDown : Stred(Xvystred,Yvystred-Vy_r(Rozsah));
              kbUp   : Stred(Xvystred,Yvystred+Vy_r(Rozsah));
            end;
            kb_clear;

            Kresli(true{_map_init});

         if kbhit then
            begin
              key:= GetKey;
              if key in cnst_SCROLL_MAP then
                 begin
                   MAPSCROLL:= true;
                   if FILLOVAT=true then
                      begin
                        FILLOVAT:= false;
                        _map_init:= true
                      end
                   else _map_init:= false;
                   CheckProcesses;
                   goto L
                 end;
            end;

         if FILLOVAT<>_FILLOVAT then
            begin
              MAPSCROLL:= false;
              FILLOVAT:= _FILLOVAT;
              Kresli(true)
            end;

         krok:= min_krok;

         semaphor:= false
       end;


   procedure TMapa.handle_target(var _Event: TEvent);
       begin
         if (p_handle<>nil) then TProc_vE(p_handle)(_Event)
       end;

   procedure TMapa.HandleEvent(var _Event: TEvent);
       begin
         if not ({(p_mapy_en=nil) or (bool(p_mapy_en^))}PLANZET_MAPA or ZOBRAZ_MAPU) then Exit;

         inherited HandleEvent(_Event);
         if _Event.what=evNothing then Exit;

         case _Event.What of

           evCommand :

             case _Event.Command of
               cmMAPA_VYSTRED :
                 begin
                   with mouse_status.stat do
                     begin
                       get_xy(x,y);
                       Txx:= x; Tyy:= y
                     end;
                   InvPoint(Xvystred,Yvystred);
                   Draw
                 end;
                cmMAPA_CENTRUJ : Centruj
               else Exit
             end;

           evKeyDown :

             if (_Event.Key=kb_mapa_CENTRUJ) then
                  begin
                    SetCommand(_Event,cmMAPA_CENTRUJ);
                    HandleEvent(_Event)
                  end
             else if (Active and (_Event.Key in cnst_SCROLL_MAP)) then nastav_rozsah(_Event.Key)
                  else Exit

           else if isClicked(_Event) then
                   if active then handle_target(_Event)
                   else Mail(Owner, cm_mapa_scroll,One, nil,0)

           else Exit
         end;

         ClearEvent(_Event)
       end;
