procedure TFDAapp.HandleEvent(var _Event: TEvent);
    var   i : int;
          p : pointer;
          is: bool;

    begin
      is:= true;

      case _Event.What of

        evKeyDown:

          case _Event.Key of

           NULL         : ;


           {$IFDEF DEMO}
            {'*'         : DEV_AFTN^.demo_file(' ',11);
                           asta_fdp_test;}
           {$ENDIF}

           {$IFDEF DD_EXE}
            {'@'         : _ack_PLN('IPR202-UKFF-990729',0);}
            '!'         : net_pkt_test('net.tst',-1,-1);
           {$IFDEF CONNECT_TO_AFTN}
            '?'          : DEV_AFTN^.test_file(paramstr(1),' ',11);
           {$ENDIF}

            {$IFDEF FPD}
             '?'        : REQ_EST('','');
            {$ENDIF}
           {$ENDIF}

           {$IFDEF MPU}
             kbF9       : SetCommand(Pending,cmPRN_TEST1);
             kbF10      : SetCommand(Pending,cmPRN_TEST)

             {$IFDEF DEBUG};
              kbF11     :   test_print_cFPL
             {$ENDIF}
           {$ENDIF}

          else is:= false
        end

        else is:= false
      end;

      if is then
         begin
           ClearEvent(_Event);
           Exit
         end
      else inherited HandleEvent(_Event);

      case _Event.What of

        evCommand, evBroadcast:
          case _Event.Command of

            cmQUIT     : EXIT;


           {----------------------------------------------------- }
           { NASTAVENIA                                           }
           { ---------------------------------------------------- }
           cmZOZNAM_FPL : if AppGUI<>nil then AppGUI^.Draw;

        end
      end; { case }

      ClearEvent(_Event)
    end;
