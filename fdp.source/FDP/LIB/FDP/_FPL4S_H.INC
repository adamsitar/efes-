
{ ---------------------
   handler pre App
  ---------------------
}
 function _handle_event_FPL4_sc (var _Event: TEvent; O: PObject; FPL: PFPL4; sc: PScroller): bool;
    var   ires : int;
          res  : string;
          b : bool;

    begin
      _handle_event_FPL4_sc:= false;
      if _Event.what=evNothing then Exit;
      _handle_event_FPL4_sc:= true;

      case _Event.What of

        evKeyDown:
         case _Event.Key of

            NULL : ;

            {$IFDEF PROCESS_FPL4}
             kbF3      : SetCommand(Pending,O,cm_FPL);
            {$ENDIF}

            {$IFDEF FPL4_ACT}
             kbCtrlF3  : SetCommand(Pending,O,cm_ACT);
             kbAltF3   : SetCommand(Pending,O,cmPREHLAD_FPL4);
            {$ENDIF}

           else _handle_event_FPL4_sc:= false
         end;


        evCommand, evBroadcast:

          case _Event.Command of

            0 : ;

            {$IFDEF PROCESS_FPL4}
             cm_FPL        :                  _FRM_FPL4(FPL);
             cm_CHG        : if FPL<>nil then _CHG_FPL4(FPL) else CHG_FPL4i;
             cm_DLA        : if FPL<>nil then _DLA_FPL4(FPL) else DLA_FPL4i;
             cm_CNL        : if FPL<>nil then _CNL_FPL4(FPL) else CNL_FPL4i;

             cm_DEP        : if FPL<>nil then _DEP_FPL4(FPL) else DEP_FPL4i;
             cm_ARR        : if FPL<>nil then _ARR_FPL4(FPL) else ARR_FPL4i;
            {$ENDIF}

            {$IFDEF FPL4_ACT}
             cm_ACT        : if FPL<>nil then _ACT_FPL4(FPL) else ACT_FPL4i;
            {$ENDIF}

            {$IFDEF PROCESS_FPL4}
             {$IFDEF TLG}
              cm_ALR        : if FPL<>nil then _ALR_FPL4(FPL) else ALR_FPL4i;
              cm_RCF        : if FPL<>nil then _RCF_FPL4(FPL) else RCF_FPL4i;
              {$IFDEF TSGA}
               cm_ANP       : if FPL<>nil then _ANP_FPL4(FPL) else ANP_FPL4i;
               cm_FLA       : if FPL<>nil then _FLA_FPL4(FPL) else FLA_FPL4i;
              {$ENDIF}
            {$ENDIF}

            {$ENDIF}

            {$IFDEF FLI_COORDINATION}
             cm_FLI       : if cFPL^.top>=0 then
                               begin
                                 if formular_idn_i(cFPL,'FLI of',ires) then
                                    if (ires>=0) and (ires<=cFPL^.top) then p_formular_FLI(cFPL^.ap^[ires])
                                    else p_formular_FLI(nil)
                               end
                            else p_formular_FLI(nil);

             cmICAO_FLI   : begin
                              b:= true;
                              cFPL^.coordinate_FLI_ERR(b)
                            end;
            {$ENDIF}

             cmPREHLAD_FPL4               : prehlad_FPL(false);
             cmPREHLAD_FPL4_PPL           : prehlad_FPL(true);
             cmPREHLAD_FPL4_ARCH          : prehlad_FPL_ARCH;

             cmPREHLAD_FPL4D_INACTIVATED  : prehlad_FPL_INACTIVATED;
             cmPREHLAD_FPL4D_PREACTIVATED : prehlad_FPL_PREACTIVATED;
             cmPREHLAD_FPL4D_PROPOSED     : prehlad_FPL_PROPOSED;
             cmPREHLAD_FPL4D_COORDINATED  : prehlad_FPL_COORDINATED;
             {cmPREHLAD_FPL4D_ACTIVED     : prehlad_FPL_ACTIVED;}
             cmPREHLAD_FPL4D_NOTACTIVED   : prehlad_FPL_NOTACTIVED;
             cmPREHLAD_FPL4D_REALISED     : prehlad_FPL_REALISED;
             cmPREHLAD_FPL4D_ALL          : prehlad_FPL_ALL;

             cmPREHLAD_FPL4D_PPL          : prehlad_FPL_ALL_PPL;
             cmPREHLAD_FPL4D_ARCH         : prehlad_FPL_ALL_ARCH;


            cmFPL4view     : if FPL<>nil then info_FPL4(FPL,'');
            {$IFDEF PROCESS_FPL4}
             cmFPL4view_strip  : if FPL<>nil then _display_decoded_FPL4 (FPL,false,res,ires);
            {$ENDIF}


            {$IFDEF MAPY}
             cmFPL4draw    : if FPL<>nil then zobraz_trat_FPL4(FPL);
            {$ENDIF}

            {$IFDEF PRN}
             cmFPL4print   : if FPL<>nil then print_FPL4(FPL);
            {$ENDIF}

            else _handle_event_FPL4_sc:= false
          end

        else _handle_event_FPL4_sc:= false

      end;

    end;

 function  _handle_event_FPL4 (var _Event: TEvent; O: PObject; FPL: PFPL4): bool;
    begin
      _handle_event_FPL4:= _handle_event_FPL4_sc (_Event,O,FPL,nil)
    end;
