{$IFDEF DVZ}

  function _handle_event_DVZ (var _Event: TEvent; O: PObject; DVZ: pointer): bool;
     begin
       _handle_event_DVZ:= false;
       if _Event.what=evNothing then Exit;

       _handle_event_DVZ:= true;

       case _Event.What of

         evKeyDown:
          case _Event.Key of

            {$IFDEF PROCESS_DVZ}
             kbF9      : SetCommand(Pending,O,cmDVZ);
             {kbCtrlF9  : SetCommand(Pending,O,cmDVZreq);}
            {$ENDIF}

            kbAltF9    : SetCommand(Pending,O,cmPREHLAD_DVZ);
            kbCtrlF9   : SetCommand(Pending,O,cmPREHLAD_DVZ_plan);

            else _handle_event_DVZ:= false
          end;

         evCommand, evBroadcast:

           case _Event.Command of

             0 : ;

             {$IFDEF PROCESS_DVZ}
              cmDVZ      : { Riadaici si vyziadali priame odoslanie ziadosti o diverziu
                           }
                           if posliZiadostDVZ then _DVZ_REQ(DVZ)
                           else formular_DVZ(DVZ,true,true,true,'',tit_dvz_ziadost);


              cmDVZchg   : if DVZ<>nil then _DVZ_CHG(DVZ) else DVZ_oprava;
              cmDVZcnl   : if DVZ<>nil then _DVZ_CNL(DVZ) else DVZ_zrusenie(true,true);

              cmDVZreq   : if DVZ<>nil then _DVZ_REQ(DVZ) else DVZ_poziadavka;
              cmDVZact   : if DVZ<>nil then _DVZ_ACT(DVZ) else DVZ_odosli_na_diverziu;
              cmDVZend   : if DVZ<>nil then _DVZ_CNL(DVZ) else DVZ_zrusenie(false,true);

              cmDVZacc   : if DVZ<>nil then _DVZ_ACC(DVZ) else DVZ_spracuj_ziadost;
              cmDVZalr   : if DVZ<>nil then _DVZ_ALR(DVZ) else DVZ_vystraha_pred_zrusenim;
              cmDVZcln   : if DVZ<>nil then _DVZ_CLN(DVZ) else DVZ_zrusenie_vystrahy;
              cmDVZacn   : if DVZ<>nil then _DVZ_CNL(DVZ) else DVZ_zrusenie(false,false);
             {$ENDIF}

             {$IFDEF PRN}
              cmDVZprint : if DVZ<>nil then print_DVZ(DVZ);
             {$ENDIF}

             {$IFDEF AIRBASE}
              cmPREHLAD_DVZ_nase : prehlad_DVZ(@_is_stat_DVZ_pre,false);
              cmPREHLAD_DVZ_ine  : prehlad_DVZ(@_is_stat_DVZ_kym,false);
             {$ENDIF}

             cmPREHLAD_DVZ_plan  : prehlad_DVZ(nil,false);
             cmPREHLAD_DVZ       : prehlad_DVZ_act;
             {cmPRIJATE_DVZ       : prehlad_DVZ(nil,false);}

             cmPREHLAD_DVZ_PPL   : prehlad_DVZ_PPL;
             cmPREHLAD_DVZ_ARCH  : prehlad_DVZ_ARCH;


            { ---------------
               RPL pre DVZ
              ---------------

             cm_DVZ_RPL_CHG     : if DVZ<>nil then _CHG_DVZ_RPL(PScroller(O),DVZ);
             cm_DVZ_RPL_CNL     : if DVZ<>nil then _CNL_DVZ_RPL(PScroller(O),DVZ);

             cmPREHLAD_DVZ_RPL  : prehlad_DVZ_RPL;
            }

             else _handle_event_DVZ:= false
           end

         else _handle_event_DVZ:= false
       end
     end;

{$ENDIF}