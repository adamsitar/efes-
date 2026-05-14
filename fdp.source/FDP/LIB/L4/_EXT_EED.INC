{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   funkcie pre spracovanie chyb
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
  function check_icao_editor_err (E : PEXTEd;
                                  O : PO_EXT;

                                  text_adr: pchar
                                 ): bool; far;

     begin
       check_icao_editor_err:= false;
       if (E=nil) or (O=nil) or (text_adr=nil) then Exit;

       check_icao_editor_err:= _icao_editor_check (E,O, text_adr, O^.pathERR,O^._fn_ERRmask(''))
     end;


{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   funkcie pre okamzite spracovanie prijatych chyb
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
  procedure _init_icao_editor_err_
                    (E: PEXTEd;
                     _titOK: string;
                     _ine : bool;
                     _pend,_del,_edit : TEvCmnd;
                     _a36yka : bool;
                     var yi: int
                    );

      var   bt1 : PTextIcon;
            bt2 : PbtTCancel;
            bt3 : PDialogButton;
            xt,yt,xi, c : int;
            _kbHot : char;

      begin
        yi:= 0;
        with E^ do
          begin
            Win^.get_btXY(1,yi, xt,yt);
            bt1:= New(PTextIcon, Init(Win, xt,yt, 62,5,
                      GetAltCode(get_HotKey(_kbHot,_titOK)),
                      cmOk,_titOK,@icYes)
                     );
            bt1^.kbAltHot:= kbCtrlEnter;
            inc(yi);

            if _ine then
               begin
                 Win^.get_btXY(1,yi, xt,yt);
                 bt3:= New(PDialogButton, Init(Win, xt,yt, '<'{kbAltP}, cmPrev, titPREV, icKey,icText));
                 { IFNDEF A36YKA} bt3^.kbAltHot:= kbAltLeft { ENDIF};
                  inc(yi);

                 Win^.get_btXY(1,yi, xt,yt);
                 bt3:= New(PDialogButton, Init(Win, xt,yt, '>'{kbAltN}, cmNext, titNEXT, icKey,icText));
                 { IFNDEF A36YKA} bt3^.kbAltHot:= kbAltRight { ENDIF};
                 inc(yi);
               end;

            if _del<>0 then
               begin
                 Win^.get_btXY(1,yi, xt,yt);
                 bt2:= New(PbtTCancel,Init(Win,xt,yt, 56,_del,titIGNORE{'~I~gnore '}));
                 inc(yi);
               end;

            if _pend<>0 then
               begin
                 Win^.get_btXY(1,yi, xt,yt);
                 bt3:= New(PDialogButton,Init(Win, xt,yt,
                           GetAltCode(get_HotKey(_kbHot,titDLA)),
                           _pend,titDLA{'~P~end '},icKey,icText)
                          );
                 inc(yi);
               end;

            {$IFDEF PRN}
             {if _prn then}
                begin
                  Win^.get_btXY(1,yi, xt,yt);
                  bt3:= New(PDialogButton,Init(Win, xt,yt,
                            GetAltCode(get_HotKey(_kbHot,titPRINT)),
                            cmPrint,titPRINT{'P~r~int'},icKey,icText)
                           );
                  inc(yi);
                end;
            {$ENDIF}

            if _edit<>0 then
                begin
                  Win^.get_btXY(1,1, xt,yt);
                  xi:= Win^.x1-dbtWIDTH-(xt-Win^.x0);
                  _kbHot:= GetAltCode(get_HotKey(_kbHot,titEDIT));
                  bt3:= New(PDialogButton,Init(Win, xi,yt,
                            _kbHot, _edit,titEDIT,icKey,icText)
                           );
                  bt3^.kbAct:= _kbHot;
                  bt3^.kbHot:= _kbHot;
                  bt3^.kbAltHot:= _kbHot;
                  bt3^.click:= ord(false);
                end;

            {$IFDEF A36YKA}
             if _a36yka then
                begin
                  Win^.get_btXY(1,0, xt,yt);
                  xi:= Win^.x1-dbtWIDTH-(xt-Win^.x0);
                  btA36:= New(PDialogButton,Init(Win,xi,yt,
                            kbAltA,cmA36YKA,titA36,icKey,icText)
                           );
                  {inc(yi);}
                end;
            {$ENDIF}
          end
      end;

  procedure init_icao_editor_err (E: PEXTEd); far;
      var   yi: int;
      begin
        _init_icao_editor_err_ (E,titPOTVRD,false,cmERR_SAVE,cmERR_DEL,0,true,yi);
      end;


  function  _handle_icao_editor_err (var Ev : TEvent;

                                     E : PEXTEd;
                                     O : PO_EXT;

                                     hd : p_type_ext_err_pkt;

                                     load : bool
                                    ): bool;
     var    msg,path,mask : string;
            bres : bool;

     begin
       _handle_icao_editor_err:= true;
       if (E=nil) or (O=nil) or (hd=nil) or (not ((Ev.What=evCommand) or (Ev.What=evBroadcast))) then Exit;

       path:= O^.pathERR; mask:= O^._fn_ERRmask('');
       _handle_icao_editor_err:= _icao_editor_handle(Ev, E,O, path,mask, hd,false);
       if not ((Ev.What=evCommand) or (Ev.What=evBroadcast)) then Exit;

       case Ev.command of

         cmERR_DEL     : if  (Ask2(msgVERIPHY,ask_message_deleted,titNO,White,clBUTTON_COLOR,waitASK*18)=ansAno) then
                            begin
                              {msg:= 'Ignored and deleted pkt : ';
                              O^.writeln_pkt (pchars(hd^.pkt),Minimum(strlen(hd^.pkt),30),arch_SYS,msg,cl_SYS,true,true);}
                              O^.delete_pkt  (pchars(hd^.pkt),strlen(hd^.pkt), hd^.err, hd^.fn, E^.spr_del,'', true,false);
                              bres:= load and _icao_editor_load(0,true, E,O,hd, path,mask);
                              if not bres then
                                 begin
                                   SetCommand(Ev,E,cmCancel);
                                   E^.corr_res:= true;
                                   Exit
                                 end
                            end;

         cmERR_SAVE    : with hd^ do
                            begin
                              {msg:= 'Pended pkt : ';
                              O^.writeln_pkt(pchars(hd^.pkt),Minimum(strlen(hd^.pkt),30),arch_SYS,msg,cl_SYS,true,true);}
                              E^.read_from_editor;
                              O^._save_ERR(pchars(E^.text_adr),strlen(E^.text_adr),err,
                                           ext_ERS,{O^.cis_ERS,}O^.is_ERS,
                                           true,false
                                          );
                              SetCommand(Ev,E,cmCancel);
                              E^.corr_res:= true;
                              Exit
                            end

         else Exit
       end;

       ClearEvent(Ev,E)
     end;


  function  handle_icao_editor_err (var Ev : TEvent;
                                    E  : PEXTEd;
                                    O  : PO_EXT;
                                    hd : p_type_ext_err_pkt
                                   ): bool;  far;
     begin
       handle_icao_editor_err:= _handle_icao_editor_err (Ev ,E,O, hd,false)
     end;


{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   funkcie pre spracovanie odlozenych chybovych sprav
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
  procedure init_icao_editor_ers (E: PEXTEd); far;
      var   yi: int;
      begin
        _init_icao_editor_err_ (E,titPOTVRD,true,0,cmERR_DEL,0,true,yi);
      end;

  function  handle_icao_editor_ers (var Ev : TEvent;
                                    E  : PEXTEd;
                                    O  : PO_EXT;
                                    hd : p_type_ext_err_pkt
                                   ): bool; far;

     begin
       handle_icao_editor_ers:= _handle_icao_editor_err (Ev, E,O, hd,true)
     end;
