{$IFDEF ZAM}

  function _handle_event_ZAM (var _Event: TEvent; O: PObject; ZAM: pointer): bool;
     begin
       _handle_event_ZAM:= false;
       if _Event.what=evNothing then Exit;

       _handle_event_ZAM:= true;

       case _Event.What of

         evKeyDown:
          case _Event.Key of

            {$IFDEF PROCESS_ZAM}
              kbF6    : SetCommand(Pending,O,cmZAM);
            {$ENDIF}

             kbAltF6    : SetCommand(Pending,O,cmPREHLAD_ZAM);
             kbCtrlF6   : SetCommand(Pending,O,cmPREHLAD_ZAM_all);

            else _handle_event_ZAM:= false
          end;

         evCommand, evBroadcast:

           case _Event.Command of

             0 : ;

             {$IFDEF PROCESS_ZAM}
               cmZAM     : formular_ZAM(ZAM,true,true,'',tit_formZAM);

               cmZAMsend : if ZAM<>nil then say_data_sended(_SEND_ZAM(ZAM));
               cmZAMzme  : if ZAM<>nil then _ZAM_CHG(ZAM) else ZAM_zmena;
               cmZAMzru  : if ZAM<>nil then _ZAM_CNL(ZAM) else ZAM_zrusenie;

               cmZAMzac  : if ZAM<>nil then _ZAM_DEP(ZAM) else ZAM_zaciatok;
               cmZAMpre  : if ZAM<>nil then _ZAM_BRK(ZAM) else ZAM_prerusenie;
               cmZAMpok  : if ZAM<>nil then _ZAM_CNT(ZAM) else ZAM_pokracovanie;
               cmZAMkon  : if ZAM<>nil then _ZAM_ARR(nil,ZAM) else ZAM_koniec;
               cmZAMlet  : if ZAM<>nil then _ZAM_LETOV(ZAM) else ZAM_letov;

               cm_ZAM_RPL_CHG     : if ZAM<>nil then _CHG_ZAM_RPL(PScroller(O),ZAM);
               cm_ZAM_RPL_CNL     : if ZAM<>nil then _CNL_ZAM_RPL(PScroller(O),ZAM);

               cmPREHLAD_ZAM_RPL  : prehlad_ZAM_RPL;
             {$ENDIF}


             cmZAMview  : if ZAM<>nil then info_ZAM (ZAM,'');
             cmZAMprint : if ZAM<>nil then print_ZAM (ZAM);

             cmPRIJATE_ZAM           : prehlad_ZAM(true,false);

             cmPREHLAD_ZAM_nase      : prehlad_ZAM(false,false);
             cmPREHLAD_ZAM_sicke     : prehlad_ZAM(true,false);

             cmPREHLAD_ZAM_plan_nase : prehlad_ZAM_plan_nase;
             cmPREHLAD_ZAM_plan      : prehlad_ZAM_plan;
             cmPREHLAD_ZAM_act       : prehlad_ZAM_act;
             cmPREHLAD_ZAM           : ZAMs^.Vypis(tit_actZAM+' (T=-'+cstr(dt_propose_ZAM,2)+'min)');
             cmPREHLAD_ZAM_arr       : prehlad_ZAM_arr;
             cmPREHLAD_ZAM_all       : prehlad_ZAM_all;

             cmPREHLAD_ZAM_PPL       : prehlad_ZAM(true,true);
             cmPREHLAD_ZAM_PPL_nase  : prehlad_ZAM(false,true);
             cmPREHLAD_ZAM_ARCH      : prehlad_ZAM_ARCH(true);
             cmPREHLAD_ZAM_ARCH_nase : prehlad_ZAM_ARCH(false);



             else _handle_event_ZAM:= false
           end

         else _handle_event_ZAM := false
       end
     end;

{$ENDIF}