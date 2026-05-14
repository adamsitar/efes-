{$IFDEF SPR}

  function _handle_event_SPR (var _Event: TEvent; O: PObject; SPR: pointer): bool;
     begin
       _handle_event_SPR:= false;
       if _Event.what=evNothing then Exit;
       _handle_event_SPR:= true;

       case _Event.What of

         evKeyDown:
          case _Event.Key of

            kbF10      : SetCommand(Pending,O,cmSPR);

            kbAltF10   : SetCommand(Pending,O,cmPREHLAD_SPR_dor);
            kbCtrlF10  : SetCommand(Pending,O,cmPREHLAD_SPR_odo);
            kbShiftF10 : SetCommand(Pending,O,cmPREHLAD_SPR);

            else _handle_event_SPR:= false
          end;

         evCommand, evBroadcast:

           case _Event.Command of

             0 : ;

             cmSPR                  : formular_SPR(SPR);
             cmTLG                  : _formular_SPR(SPR,tit_TLG,hd_TLG,size_SPRtlg);

             cmSPRlam               : if SPR<>nil then info_SPRlam(SPR);
             cmSPRview              : if SPR<>nil then info_SPRr (SPR,'',false,0);
             {$IFDEF PRN}
              cmSPRprint            : if SPR<>nil then print_SPR(SPR);
             {$ENDIF}

             cmPREHLAD_SPR          : prehlad_SPR;
             cmPREHLAD_SPR_dor      : prehlad_SPR_dor;
             cmPREHLAD_SPR_odo      : prehlad_SPR_odo;

             cmPREHLAD_SPR_ARCH     : prehlad_SPR_ARCH;
             cmPREHLAD_SPR_dor_ARCH : prehlad_SPR_ARCH_dor;
             cmPREHLAD_SPR_odo_ARCH : prehlad_SPR_ARCH_odo;

             else _handle_event_SPR:= false
           end

         else _handle_event_SPR:= false
       end
     end;

{$ENDIF}