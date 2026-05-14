procedure T_GUI.HandleEvent(var _Event: TEvent);
    begin
      inherited HandleEvent(_Event);

      case _Event.What of

        evKeyDown:
          case _Event.Key of
            kbTab      : winACC^.dalsi;
            kbShiftTab : winACC^.predch;

            else Exit
          end;

        evCommand, evBroadcast:

          case _Event.Command of

            cmSECTOR_CHG,
            cmEDD_STATUS   : edd_status;

            hl_vyp_winPROP : winACC^.zapni;   { sprava pre GUI, ze PROP sa vypina => zapne ACC   }
            hl_zap_winPROP : winACC^.vypni;   { sprava pre GUI, ze PROP sa zapina => vypne ACC   }

            hl_vyp_winACC  : winPROP^.zapni;  { sprava pre GUI, ze ACC sa vypina => zapne PROP   }
            hl_zap_winACC  : winPROP^.vypni;  { sprava pre GUI, ze ACC sa zapina => vypne PROP   }

            cmACC_DEFAULT,
            cmACC_DEFAULT_lo..cmACC_DEFAULT_hi

                           : mnuGROUPs_done(@Self,_Event)

            else Exit
          end;

        else Exit
      end;

      ClearEvent(_Event)
    end;

