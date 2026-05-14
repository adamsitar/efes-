procedure TFDPapp.HandleEvent(var _Event: TEvent);
    var   i : int;
    begin
      inherited HandleEvent(_Event);

      if _Event.what=evNothing then Exit;


      if        _handle_event_FDP  (_Event, @Self, nil) then


      {$IFDEF RPL}
        else if _handle_event_RPL (_Event, @Self, nil) then
      {$ENDIF}

      {$IFDEF PLN}
        else if _handle_event_PLN (_Event, @Self, nil) then
      {$ENDIF}

      {$IFDEF FPL4}
        else if _handle_event_FPL4 (_Event, @Self, nil) then
      {$ENDIF}

      {$IFDEF FPL0}
        else if _handle_event_FPL (_Event, @Self, nil) then
      {$ENDIF}


      {$IFDEF ZAM}
        else if _handle_event_ZAM (_Event, @Self, nil) then
      {$ENDIF}


      {$IFDEF QGO}
        else if _handle_event_QGO (_Event, @Self, nil) then
      {$ENDIF}

      {$IFDEF RTZ}
        else if _handle_event_RTZ (_Event, @Self, nil) then
      {$ENDIF}

      {$IFDEF DVZ}
        else if _handle_event_DVZ (_Event, @Self, nil) then
      {$ENDIF}


      {$IFDEF PRZ}
        else if _handle_event_PRZ (_Event, @Self, nil) then
      {$ENDIF}

      {$IFDEF PRS}
        else if _handle_event_PRS (_Event, @Self, nil) then
      {$ENDIF}

      {$IFDEF FUA}
        else if _handle_event_FUA (_Event, @Self, nil) then
      {$ENDIF}


      {$IFDEF MET}
        else if _handle_event_MET (_Event, @Self, nil) then
      {$ENDIF}


      {$IFDEF SPR}
        else if _handle_event_SPR (_Event, @Self, nil) then
      {$ENDIF}

      {$IFDEF TLG}
       else if _handle_event_TLG (_Event, @Self, nil) then
      {$ENDIF}


      {$IFDEF STATISTIKA}
        else if _handle_event_STATISTIKA (_Event, @Self, nil) then
      {$ENDIF}


      {$IFDEF MAPY}
        else if _handle_event_MAPY (_Event, @Self, nil) then
      {$ENDIF}


      else   if _handle_AIP_list   (_Event, @Self) then


      else case _Event.What of

        evKeyDown:
          case _Event.Key of

           { -----------------------------
              Systemove horuce klavesy
             תתתתתתתתתתתתתתתתתתתתתתתתתתתתת
           }

            kbShiftF1 : SetCommand(Pending,cmHelpIndex);

            kbAltX    : SetCommand(Pending,cmQuit);


           {$IFDEF DEBUG}
            {$IFDEF STATUS}
             #01        : STATUS_show;
             #02        : STATUS_hide;
            {$ENDIF}
           {$ENDIF}

           {$IFDEF BGI} {$IFDEF DISPLAY_PREPNI}
             {$IFDEF IDD} kbAlt4
             {$ELSE}
              {$IFDEF VGA}
                kbAlt1
              {$ELSE}
                kbAlt2
              {$ENDIF}
             {$ENDIF}
               ..
             {$IFDEF _1280x1024}   kbAlt5
             {$ELSE} {$IFDEF SVGA} kbAlt4
                     {$ELSE}       kbAlt3
                     {$ENDIF}
             {$ENDIF} : begin
                          if EN_GRAPH_MODE_SWITCH then
                             begin
                               GraphMode:= TGraphMode((ord(_Event.Key)-(ord(kbAlt1)-ord('1'))-ord('0'))-1);
                               SetCommand(Pending,cmGraphModeChanged)
                             end
                        end;
           {$ENDIF} {$ENDIF}

            kbF12     , #253 : SetCommand(Pending,cmTRASY0);
            kbShiftF12, #254 : SetCommand(Pending,cmTRASY1);


           { -----------------------------
              Horuce klavesy FDP
             תתתתתתתתתתתתתתתתתתתתתתתתתתתתת
           }

           {$IFNDEF NO_PLAN}

           {$ENDIF}

             kbCtrlF8   : SetCommand(Pending,cmSEARCH_SSR);
             kbCtrlF9   : SetCommand(Pending,cmSEARCH_CODE);

            { prehlad
            }

             {$IFDEF PLN}
              kbAltF2   : SetCommand(Pending,cmPREHLAD_PLN);
             {$ENDIF}

            else Exit

          end;

        evCommand, evBroadcast:
          case _Event.Command of

          { -------------------
             Systemove prikazy
            תתתתתתתתתתתתתתתתתתת
          }

            cmQUIT        : Exit;

            cmHelpIndex   : _help_index;

            cmNASTAV_SPRACOVANIE,
            cmNASTAV_ZOBRAZENIE : begin
                                    {if bminiSTRIP then miniSTRIP:= mini_strip else miniSTRIP:= full_strip;}
                                    Draw;
                                  end;

            cmAbout        : begin
                               i:= 155; {$IFNDEF SK} {$IFNDEF CZ} inc(i,35); {$ENDIF} {$ENDIF}
                               Info(msgABOUT, @_about,nil,300,i,nil,0);
                             end;
            cmAboutUpgrade : _help(hlp_UPG);

            cmTRASY0 : NODEs_info(false);
            cmTRASY1 : NODEs_info(true);


            cmPRN_TEST   : {$IFDEF PRN} printer_test(PortNo) {$ENDIF};

            cmSTATUS_CHG : begin
                            {$IFDEF STATUS}
                              STATUS_reinit;
                              distribute_app_config;
                            {$ENDIF}
                           end;


            cmCFG_SAVE_ACT     : SaveProgramCfg(USER_CFG);
            cmCFG_SAVE_OTH     : SaveUserCfg;

            cmCFG_LOADED       : begin
                                   change_gm(GraphMode,false,false);
                                   Exit
                                 end;

            cmCFG_DEFAULT,
            cmCFG_USER_lo..cmCFG_USER_hi :
                                 begin
                                   ReadUserCfg(_Event);
                                   Draw;
                                 end;


            cmGraphModeChanged : change_gm(GraphMode,false,true);

            cmSYSTEM_VOLBY     : begin
                                   JasBGI(ord(JAS) and 1);
                                   Rozsviet;
                                 end;

          { Cas
          }
            cmTIMEset   : formular_Hodiny;
            cmCLOCK     : Clock^.reinit(0,0,MaxX,MaxY);


          { -------------------
             FDP
            תתתתתתתתתתתתתתתתתתת
          }
            cmFPLm_ARR_PATRAT : {pozri_nevydane_spravy};


          { --------------------
            PRIPOJENE ZARIADENIA
            תתתתתתתתתתתתתתתתתתתת
          }

           {$IFDEF BACKUP}
            cmSERVER_BCK : Say2(msgWARNING,'Master server connection timeout.');
           {$ENDIF}
           {$IFDEF MASTER}
            cmSERVER_BCK : Say2(msgWARNING,'Slave server connection timeout.');
           {$ENDIF}

           { SEARCH ----------------------------
           }
           {$IFDEF FPL}
            cmSEARCH_SSR  : search_SSR;
            cmSEARCH_SSR_ : search_SSR_;
            cmSEARCH_CODE : search_CODE;
            cmSEARCH_CODE_: search_CODE_;
           {$ENDIF}


          { -------------------
            ARCHIV
            תתתתתתתתתתתתתתתתתתת
          }

          cmARCHIV_COM    : zalohuj_archiv(path_COM,'*.'+extCOM,msgBCK,msgCOPY,nil);

          {$IFDEF ARCHIVE_NET}
           cmARCHIV_NET  : zalohuj_archiv(path_NET,'*.'+extNET,msgBCK,msgCOPY,nil);
          {$ENDIF}

          {$IFDEF ARCHIVE_DAR}
           cmARCHIV_DAR  : zalohuj_archiv(path_DAR,'*.*',msgBCK,msgCOPY,@backup_DAR_file);
          {$ENDIF}

          {$IFDEF ARCHIVE_ASTA}
           cmARCHIV_ASTA : zalohuj_archiv(path_ASTA,'*.*',msgBCK,msgCOPY,nil);
          {$ENDIF}

          else Exit

        end;

        else Exit

      end; { case }

      ClearEvent(_Event)

    end;
