procedure show_targets;
    begin
    end;

procedure hide_targets;
    begin
    end;


function _handle_event_MAPY (var _Event: TEvent; O: PObject; FPL: pointer): bool;
   var   cfg_fn : string;
         res : bool;

   begin
     _handle_event_MAPY:= false;

     if _Event.what=evNothing then Exit;
     if (not PLANZET_MAPA) or (OpenWins>0) then Exit;

     res:= true;

     case _Event.What of

       evKeyDown:

        case _Event.Key of

          kb_mapa_ROZSAH   : SetCommand(Pending,O,cmMAPA_ROZSAH);
          kb_mapa_PRIESTOR : SetCommand(Pending,O,cmMAPA_PRIESTOR);
          kb_mapa_STRED    : SetCommand(Pending,O,cmMAPA_STRED);
          kb_mapa_CENTRUJ  : SetCommand(Pending,O,cmMAPA_CENTRUJ);

          kbAltF    : SetCommand(Pending,O,cmMAPA_FONT);
          kbAltH    : SetCommand(Pending,O,cmMAPA_HISTORY);

          kbAltS    : begin draw_SSR:= not draw_SSR; SetCommand(Pending,O,cmMAPA_init); end;

          kbAltM    : begin OBNOV_CIELE:= true; draw_mFPL_en:= not draw_mFPL_en end;
          kbAltC    : begin OBNOV_CIELE:= true; draw_cFPL_en:= not draw_cFPL_en end;
          {$IFDEF FPLO}
           kbAltO   : begin OBNOV_CIELE:= true; draw_oFPL_en:= not draw_oFPL_en end;
          {$ENDIF}

          else res:= false
        end;

       evCommand, evBroadcast:

         case _Event.Command of

           0 : ;


           cmCFG_SAVED      : if Mapa<>nil then
                                 begin
                                   if not read_mail_s (_Event,cfg_fn) then cfg_fn:= USER_MAPS_CFG;
                                   Mapa^.save_user_cfg (cfg_fn);
                                   res:= false
                                 end;

           cmCFG_LOADED     : if Mapa<>nil then with Mapa^ do
                                 begin
                                   if read_mail_s (_Event,cfg_fn) then load_user_cfg (cfg_fn){ then Draw;};
                                   res:= false
                                 end;

           cmMAPA_INIT,
           cmMAPA_PREKRESLI : if Mapa<>nil then Mapa^.Draw;

           cmMAPA_CENTRUJ   : if Mapa<>nil then Mapa^.Centruj;
           cmMAPA_STRED     : if Mapa<>nil then Mapa^.Vystred;

           cmMAPA_ROZSAH    : formular_Rozsah;
           cmMAPA_PRIESTOR  : formular_Priestor;

           cmMAPA_FONT      : begin
                                draw_trgt_rte:= true;
                                p_hide_targets;
                                draw_FONT:= (draw_FONT + 1) mod 2;
                                p_show_targets;
                                draw_trgt_rte:= false
                              end;

           cmMAPA_HISTORY   : begin
                                draw_trgt_rte:= true;
                                p_hide_targets;
                                draw_HISTORY:= not draw_HISTORY;
                                if draw_HISTORY then draw_trgt_his:= true;
                                p_show_targets;
                                draw_trgt_his:= false;
                                draw_trgt_rte:= false
                              end;
           else res:= false
         end

       else res:= false
     end;

     {if res and saveMAPY and (Mapa<>nil) then Mapa^.save_cfg_fn(USER_MAPS_CFG);}
     _handle_event_MAPY:= res
   end;
