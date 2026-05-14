
procedure TOPLapp.HandleEvent(var _Event: TEvent);
    begin
      inherited HandleEvent(_Event);
      if _Event.what=evNothing then Exit;

      case _Event.What of

        evKeyDown:
          case _Event.Key of

           {$IFDEF DEBUG}
            '!'       : SetCommand(Pending,cm_STATISTIKA_TEST);
            '?'       : net_pkt_test(paramstr(1),-1,-1);
           {$ENDIF}

           {$IFDEF STATUS}
            #01       : STATUS_show;
            #02       : STATUS_hide;
           {$ENDIF}

            else inherited HandleEvent(_Event)
          end;

        evCommand, evBroadcast:
          case _Event.Command of

            cmQUIT     : Exit;

            {
            cmSERVER : if Ask(_Event,cmOK, msgACCEPT,'íiadosü o inicializ°ciu serverom OPL.','',White,clBUTTON_COLOR,130)
                          = ansAno then SERVER__ziadost_o_inicializaciu;
            }


          { Prelety ---------------------------------------------- }
            cmCFG_LOADED    : begin
                                P_GUI(AppGUI)^.reorganize(false);
                                {$IFDEF FPL}
                                 load_mFPL(get_fn_mFPL_let, mFPL,oFPL);
                                {$ENDIF}
                                inherited HandleEvent(_Event)
                              end;

            cmZOZNAM_FPL    : begin
                                P_GUI(AppGUI)^.reorganize(true);
                                {$IFDEF FPL}
                                 load_mFPL(get_fn_mFPL_let, mFPL,oFPL);
                                {$ENDIF}
                              end;


            else inherited HandleEvent(_Event)
          end

        else inherited HandleEvent(_Event)

      end; { case }

      ClearEvent(_Event)
    end;
