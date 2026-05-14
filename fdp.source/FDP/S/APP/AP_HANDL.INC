procedure TSERVERapp.HandleEvent(var _Event: TEvent);
    var   i : int;
          p : pointer;
          is: bool;

    begin
      is:= true;

      case _Event.What of

        evKeyDown:

          case _Event.Key of

           #0           : ;

           {$IFDEF DEMO}
            {'*'         : DEV_AFTN^.demo_file(' ',11);
                           asta_fdp_test;}
           {$ENDIF}

           {$IFDEF DD_EXE}
            '!'         : net_pkt_test(paramstr(1),-1,-1);
            '?'         : {DEV_AFTN^.test_file(paramstr(1),' ',11)}
                          {DEV_OPL^.test_file(paramstr(1),' ',11)}
                          {DEV_CAMUS^.test_file(paramstr(1),'',0)}
                          {LKPR - DEV_CAMUS^.test_file(paramstr(1),'',0)}
                          {LZIB -  DEV_CAMUS^.test_file(paramstr(1),'ù',2)
                          {asta_prn_test}
                          {testFDAnodes}
                          ;
            {$IFDEF STATUS}
             #01        : STATUS_show;
             #02        : STATUS_hide;
             #03        : ;
            {$ENDIF}
            {$IFDEF FPD}
             '?'        : REQ_EST('','');
            {$ENDIF}
           {$ENDIF}

           {$IFDEF AFTN}
             kbF10      : SetCommand(Pending,cm_TLG);
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

        end
      end; { case }

      ClearEvent(_Event)
    end;
