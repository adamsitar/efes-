{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   Funkcie pre vypis/prehlad/editovanie sprav prijatych
   z AFTN.
   Prehladove funkcie pouzivaju ine buttony a handler.
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

 procedure init_tlg_editor (E: PEXTEd); far;
     var   yi : int;
           ce : TEvCmnd;
     begin
       if E^.viewer then ce:= cmTLG_EDIT else ce:= 0;
       _init_icao_editor_err_ (E,titPOTVRD,true,cmTLG_PEND,0,ce,E^.viewer,yi);
       if E^.viewer then
          begin
          end;
     end;


 {
   TBFunc_vEp3(handle_buttons)(_Event,@Self,handler_owner,handler_data)
 }
 function  load_tlg_editor (var Ev : TEvent;
                            E  : PEXTEd;
                            O  : PO_EXT;
                            hd : p_type_ext_err_pkt
                           ): bool;

    var    Dir: DirStr; Name: NameStr; Ext: ExtStr;

    begin
      load_tlg_editor:= false;
      if (E=nil) or (O=nil) or (hd=nil) then Exit;

      SetCommand(Ev,E,cmCancel);
      E^.corr_res:= true;

      FSplit(hd^.fn,Dir,Name,Ext);
      hd^.fn:= najmladsi_subor(Dir, '*'+Ext);
      if (hd^.fn<>'') then
         begin
           hd^.fn:= Dir+hd^.fn;
           strdispose(hd^.pkt);
           if O^._read_txt_file(hd^.fn,true,hd^.err,hd^.pkt) then
              begin
                E^._write_in_editor(hd^.pkt,strlen(hd^.pkt));
                E^.new_title(hd^.err);
                E^.pos_prev:= -1;
                E^.List;
                E^.ClearEvent(Ev);
                E^.corr_res:= false;
                load_tlg_editor:= true
              end
         end
    end;


 function  handle_tlg_editor (var Ev : TEvent;
                              E  : PEXTEd;
                              O  : PO_EXT;
                              hd : p_type_ext_err_pkt
                             ): bool;

    var    msg,prty : string;
           tlg_PRTY : pbool;
           Dir: DirStr; Name: NameStr; Ext: ExtStr;

    begin
      handle_tlg_editor:= true;
      if (E=nil) or (O=nil) or (hd=nil) then Exit;

      FSplit(hd^.fn,Dir,Name,Ext);
      _icao_editor_handle (Ev, E,O, P_AFTN(O)^.pathTLG,P_AFTN(O)^._fn_TLGmask(Ext), hd, true);
      if (not ((Ev.What=evCommand) or (Ev.What=evBroadcast))) then Exit;

      case Ev.Command of

        cmTLG_PEND  : if hd<>nil then
                        begin
                          prty:= getstr(hd^.err,1,[' ']);
                          if prty=tlgSS then tlg_PRTY:= @tlg_SS
                          else if prty=tlgFF then tlg_PRTY:= @tlg_FF
                          else tlg_PRTY:= @tlg_KK;
                          tlg_PRTY^:= false;
                          SetCommand (Ev,O,CmCancel)
                        end;

        cmTLG_EDIT  : begin
                        E^.functionality(not E^.viewer);
                        ClearEvent(Ev,E)
                      end;

        cmA36YKA    : begin
                       is_kblayout:= not is_kblayout;
                       ClearEvent(Ev,E)
                      end;

        cmOK        : begin
                       if E^.call_check_func then
                          begin
                          { Spracovanie TLG a odmazanie zaznamu o nom
                          }
                            {P_AFTN(O)^.save_TLG(pchars(hd^.pkt),strlen(hd^.pkt),hd^.err,prty);}
                            O^.delete_pkt (pchars(hd^.pkt),strlen(hd^.pkt), hd^.err,hd^.fn, E^.spr_del,'',true,false);

                          { Natiahnutie dalsieho TLG
                          }
                            if not load_tlg_editor(Ev,E,O,hd) then
                               begin
                                 SetCommand(Ev,E,cmCancel);
                                 E^.corr_res:= true;
                                 Exit
                               end
                          end;
                       ClearEvent(Ev,E)
                     end
      end
    end;


 function check_tlg_editor (E: PEXTEd; O: PO_EXT; text_adr: pchar): bool;
    var   head,resh,resd : string;
          bres : bool;
    begin
      check_tlg_editor:= false;
      if ((O<>nil) and (not E^.viewer)) then
         if (Ask2(msgVERIPHY,ask_NEW_MESSAGE,titNO,White,clBUTTON_COLOR,waitASK*18)=ansAno) then
            begin
              resd:= '';
              P_AFTN(O)^.process_data (src_ed, pchars(text_adr),strlen(text_adr), head, resh,resd);
              if resd<>'' then Err2('',resd);
              check_tlg_editor:= bres and (resd='')
            end
         else check_tlg_editor:= false
      else check_tlg_editor:= true
    end;
