{$IFDEF PLN}

 procedure init_pln_editor (E: PEXTEd); far;
     var   ce : TEvCmnd;
           yi : int;
     begin
       if E^.viewer then ce:= cmTLG_EDIT else ce:= 0;
       _init_icao_editor_err_ (E,titSPRACUJ,true,0{cmTLG_PEND},cmTLG_DEL,ce,E^.viewer, yi);
     end;


 function check_pln_editor (E: PEXTEd; O: P_AFTN_TSGA; text_adr: pchar): bool; far;
    var   res : string;
    begin
      if (O<>nil) then
         begin
           check_pln_editor:= O^._process_PLN (src_ed, pchars(text_adr),strlen(text_adr), res) and (res='');
           if res<>'' then Err2('',res)
         end
      else check_pln_editor:= true
    end;


 function  handle_pln_editor (var Ev : TEvent;
                              E  : PEXTEd;
                              O  : P_AFTN_TSGA;
                              hd : p_type_ext_err_pkt
                             ): bool; far;

    var    msg,prty : string;
           tlg_PRTY : pbool;

           Dir: DirStr;
           Name: NameStr;
           Ext: ExtStr;

    begin
      handle_pln_editor:= true;
      if (E=nil) or (O=nil) or (hd=nil) then Exit;

      case Ev.Command of

        cmTLG_PEND : E^.ClearEvent(Ev); { potlacenie povodneho ... }

        cmTLG_DEL  : if Ask2(msgVERIPHY,ask_PLN_DEL,titNO,White,clBUTTON_COLOR,waitASK*18)=ansAno then
                        begin
                          O^.delete_pkt  (pchars(hd^.pkt),strlen(hd^.pkt), hd^.err, hd^.fn, E^.spr_del,'', true,false);
                          load_tlg_editor(Ev,E,O,hd)
                        end
                     else E^.ClearEvent(Ev);

        cmOK       : if E^.call_check_func then
                        begin
                          E^.is_chg:= false;
                          O^.delete_pkt (pchars(hd^.pkt),strlen(hd^.pkt), hd^.err,hd^.fn, E^.spr_del,'',true,false);
                          load_tlg_editor(Ev,E,O,hd)
                        end
                     else E^.ClearEvent(Ev);

        else handle_pln_editor:= handle_tlg_editor (Ev,E,O,hd)
      end
    end;

{$ENDIF}