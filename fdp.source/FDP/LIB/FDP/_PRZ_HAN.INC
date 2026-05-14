{$IFDEF PRZ}

  function _handle_event_PRZ (var _Event: TEvent; O: PObject; PRZ: pointer): bool;
     begin
       if _Event.what=evNothing then Exit;

       _handle_event_PRZ:= true;

       case _Event.What of

         evCommand, evBroadcast:

           case _Event.Command of

             0 : ;

             { PRZ
             }
              cmPRNview,cmPRZview      : if PRZ<>nil then info_PRZ(PRZ,'');
              cmPRNprint,cmPRZprint    : if PRZ<>nil then print_PRZ(PRZ);

              {$IFDEF PRZ_REQUEST}
               cmPRZ      : formular_PRZ (PRZ,true,true,'',tit_przPLAN);
               cmPRZsend  : if PRZ<>nil then say_data_sended(_SEND_PRZ(PRZ));
               cmPRZ_CHG  : if PRZ<>nil then _PRZ_CHG(PRZ) else PRZ_zmena;
               cmPRZ_CNL  : if PRZ<>nil then _PRZ_CNL(PRZ) else PRZ_zrusenie;
              {$ENDIF}

              {$IFDEF AIRBASE}
               cmPREHLAD_PRZ_nase      : prehlad_PRZ (false,false);
               cmPREHLAD_PRZ_PPL_nase  : prehlad_PRZ_PPL  (false);
               cmPREHLAD_PRZ_ARCH_nase : prehlad_PRZ_ARCH (false);
              {$ENDIF}

              cmPREHLAD_PRZ            : prehlad_PRZ (true,false);
              cmPREHLAD_PRZ_PPL        : prehlad_PRZ_PPL  (true);
              cmPREHLAD_PRZ_ARCH       : prehlad_PRZ_ARCH (true);


              cmPREHLAD_PRN            : prehlad_PRN(false);
              cmPREHLAD_PRN_PPL        : prehlad_PRN(true);
              cmPREHLAD_PRN_ARCH       : prehlad_PRN_ARCH;

              cmPREHLAD_VLIS           : prehlad_PRN_VLIS(false);
              cmPREHLAD_VLIS_PPL       : prehlad_PRN_VLIS(true);
              cmPREHLAD_VLIS_ARCH      : prehlad_PRN_VLIS_ARCH;

              else _handle_event_PRZ:= false
           end

         else _handle_event_PRZ:= false
       end
     end;

{$ENDIF}