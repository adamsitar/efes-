{$IFDEF PRS}

  function _handle_event_PRS (var _Event: TEvent; O: PObject; PRS: pointer): bool;
     begin
       _handle_event_PRS:= false;
       if _Event.what=evNothing then Exit;

       _handle_event_PRS:= true;

       case _Event.What of

         evKeyDown:
          case _Event.Key of

            {$IFDEF PROCESS_PRS}
             kbF7      : SetCommand(Pending,O,cmPRS);
            {$ENDIF}

            kbAltF7    : SetCommand(Pending,O,cmPREHLAD_PRS);
            kbCtrlF7   : SetCommand(Pending,O,cmPREHLAD_PRS_all);

            else _handle_event_PRS:= false
          end;

         evCommand, evBroadcast:

           case _Event.Command of

             0 : ;

             {$IFDEF PROCESS_PRS}
               cmPRS      : formular_PRS(PRS, true,true, letvis,'', tit_formPRS);

               cmPRSsend  : if PRS<>nil then say_data_sended(_SEND_PRS(PRS));
               cmPRSchg   : if PRS<>nil then _PRS_CHG(PRS) else PRS_zmena_(@_is_CHG,@_PRS_CHG,tit_prsCHG);
               cmPRScnl   : if PRS<>nil then _PRS_CNL(PRS) else PRS_zrusenie;

               {$IFDEF AMC}
                cmPRSreq  : if PRS<>nil then _PRS_REQ(PRS,nil) else PRS_ziadost;
                cmPRSacc  : if PRS<>nil then _PRS_ACC(PRS) else PRS_schvalenie;
                cmPRSdec  : if PRS<>nil then _PRS_DEC(PRS) else PRS_zamietnutie;
               {$ENDIF}

               cmPRSdep   : if PRS<>nil then _PRS_DEP(PRS) else PRS_zaciatok;
               cmPRSact   : if PRS<>nil then _PRS_ACT(PRS) else PRS_zmena_(@_is_ACT,@_PRS_ACT,tit_prsACT);
               cmPRSbrk   : if PRS<>nil then _PRS_BRK(PRS) else PRS_prerusenie;
               cmPRScnt   : if PRS<>nil then _PRS_CNT(PRS) else PRS_pokracovanie;
               cmPRSarr   : if PRS<>nil then _PRS_ARR(PScroller(O),PRS) else PRS_koniec;

               cm_PRS_RPL_CHG     : if PRS<>nil then _CHG_PRS_RPL(PScroller(O),PRS);
               cm_PRS_RPL_CNL     : if PRS<>nil then _CNL_PRS_RPL(PScroller(O),PRS);

               cmPREHLAD_PRS_RPL  : prehlad_PRS_RPL;
             {$ENDIF}

             cmPRSview    : if PRS<>nil then info_PRS(PRS,'');
             cmPRSprint   : if PRS<>nil then print_PRS(PRS);


             cmPREHLAD_PRS_nase      : prehlad_PRS (false,false);
             cmPREHLAD_PRS_sicke     : prehlad_PRS (true,false);
             {cmPREHLAD_PRS_plan      : prehlad_PRS_plan;}
             cmPREHLAD_PRS_acc       : prehlad_PRS_acc;
             cmPREHLAD_PRS           : PRSs^.Vypis(tit_prsACT_L+' (T=-'+cstr(dt_propose_PRS,2)+' min)');
             cmPREHLAD_PRS_act       : prehlad_PRS_act;
             cmPREHLAD_PRS_arr       : prehlad_PRS_arr;
             cmPREHLAD_PRS_all       : prehlad_PRS_all;

             cmPREHLAD_PRS_PPL_nase  : prehlad_PRS(false,true);
             cmPREHLAD_PRS_PPL       : prehlad_PRS(true,true);

             cmPREHLAD_PRS_ARCH_nase : prehlad_PRS_ARCH(false);
             cmPREHLAD_PRS_ARCH      : prehlad_PRS_ARCH(true);

             else _handle_event_PRS:= false;

           end

         else _handle_event_PRS:= false
       end
     end;

{$ENDIF}