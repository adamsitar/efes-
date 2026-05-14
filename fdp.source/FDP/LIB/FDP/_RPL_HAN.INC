 function _handle_event_RPL_sc (var _Event: TEvent; O: PObject; RPL: PRPL; sc: PScroller): bool;
    var    res: string;
    begin
      _handle_event_RPL_sc:= false;
      if _Event.what=evNothing then Exit;
      _handle_event_RPL_sc:= true;

      case _Event.What of

        evKeyDown:
         case _Event.Key of

           NULL : ;

           {$IFDEF PROCESS_RPL}
            kbF2 : SetCommand(Pending,O,cm_RPL);
           {$ENDIF}

           else _handle_event_RPL_sc:= false
         end;


        evCommand, evBroadcast:

          case _Event.Command of

            0 : ;

            {$IFDEF PROCESS_RPL}
             cm_RPL        : _FRM_RPL(RPL);

             cm_RPLchg     : if RPL<>nil then _CHG_RPL(RPL) else CHG_RPLi;
             cm_RPLbrk     : if RPL<>nil then _BRK_RPL(RPL) else BRK_RPLi;
             cm_RPLcnt     : if RPL<>nil then _CNT_RPL(RPL) else CNT_RPLi;
             {cm_RPLcnl    : if RPL<>nil then _CNL_RPL(RPL) else CHG_RPLi;}

             cm_RPLdokonci : finish_RPLs;
             cm_RPLadd     : add_RPLs;
             cm_RPLreplace : replace_RPLs(false);
             cm_RPLcorrect : replace_RPLs(true);
             cm_RPLrestore : restore_RPLs;

             cm_RPLchyby   : zobraz_chyby_txt_rpl;
            {$ENDIF}


            cm_RPLview     : info_RPL(RPL,'');

            {$IFDEF MAPY}
             cm_RPLdraw    : draw_RPL(RPL);
            {$ENDIF}

            {$IFDEF PROCESS_RPL}
             {cm_RPL4Cview : display_decoded_RPL (RPL,s);}
             cm_RPLspracuj : if RPL<>nil then _FPL_RPL(RPL) else FPL_RPLi;
            {$ENDIF}

            {$IFDEF PRN}
             cm_RPLprint   : print_RPL(RPL);
            {$ENDIF}

            cmPREHLAD_RPL : prehlad_RPL;

            cm_RPLmake    : begin
                              if (datetosec(lastRPL.date.r,lastRPL.date.m,lastRPL.date.d)>datetosec(year,month,day)) then
                                 begin
                                   l4_err(a_RPL,'',0,ask_rpl_make,res);
                                   if (res<>'') and (Ask2(msgVERIPHY,res,titNO,White,clBUTTON_COLOR,waitASK*18)<>ansAno) then
                                      Exit
                                 end;
                              make_FPL(true);
                            end;

            cm_RPLpended  : make_FPL(true);


            else _handle_event_RPL_sc:= false
          end

        else _handle_event_RPL_sc:= false

      end
    end;


 function  _handle_event_RPL (var _Event: TEvent; O: PObject; RPL: PRPL): bool;
    begin
      _handle_event_RPL:= _handle_event_RPL_sc (_Event,O,RPL,nil)
    end;

