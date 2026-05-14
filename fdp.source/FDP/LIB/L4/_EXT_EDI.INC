 constructor TEXTEd.Init (_title: string;
                          var _x,_y, _mode: int;
                          _viewer : bool;
                          _riadkov,_znakov, _velkost_strany: int;

                          _write_txt,_read_txt : pointer;
                          _check_func : pointer;
                          _dxb,_dyb : int;

                          _init_buttons,_handle_buttons : pointer;
                          _handler_owner : PO_EXT;
                          _handler_data : p_type_ext_err_pkt; { NEMENIT ! }
                          _handle_end_state : pointer;

                          _bge,_cle, _abg,_acl, _bgv,_clv : byte;
                          _spr_ed,_spr_del : TNETtyp;
                          _hlpXXX : pchar;

                          var _pkt : pchar
                         );

       begin
         inherited Init(nil,
                        _x,_y, _mode, cmOK, _title,
                        true, _viewer,  nil, _riadkov,_znakov, _velkost_strany, '',
                        _write_txt,_read_txt,
                        pointer(_pkt), strlen(_pkt),strlen(_pkt), true,true, {,_text_repl,_text_disp,}
                        [kbCR,kbLF,#12],[icao_NXIT],kbNL,
                        _check_func,
                        _dxb,_dyb, _init_buttons,_handle_buttons,_handler_owner,_handler_data,
                        _bge,_cle, _abg,_acl, _bgv,_clv,
                        _hlpXXX
                       );

         {if (handler_owner<>nil) then handler_owner^.PushObject(@Self); -> vlozene do predchodcu 2.2 }

         spr_ed:= _spr_ed; spr_del:= _spr_del;

         handler_end_state:= _handle_end_state;
         upcas:= true;
         with win^.btTitle^ do
           begin
             cmXXXX:= cmAboutWin;
             kbAct:= kbAltF1;
             kbHot:= kbAltF1
           end
       end;


 destructor TEXTEd.Done;
      var   O : PObject;
      begin
        {if (handler_owner<>nil) then -> vlozene do predchodcu 2.2
           begin
             O:= @Self;
             handler_owner^.RemoveObject(O,false)
           end;}
        inherited Done
      end;


{ Funkcie zacinajuce s podciarovnikom maju ine parametre ako
  predpokladaju refenrencie na nich (alebo nie su odkazovatelne),
  preto musia byt volane cez sprostredkovatelske funkcie !

  Dolezita poznamka - vystupne pole editora musi mat premenlivu dlzku,
                      preto je to pchar. Predpoklada to viacero externych
                      funkcii v tomto module.
}


{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   funkcie pre spracovanie sprav
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}

{ zapisanie zmien do editovanej spravy
  chyby/tlg/... a ich rozoslanie
}
  function  _icao_editor_cancel (E  : PEXTEd;
                                 O  : PO_EXT;
                                 hd : p_type_ext_err_pkt
                                ): TAnswer;
     var    a : TAnswer;
     begin
       _icao_editor_cancel:= ansAno;
       if (E=nil) or (O=nil) or (hd=nil) then Exit;

       if E^.is_chg then
          begin
            a:= Ask2(msgVERIPHY,ask_message_changed,titNO,White,clBUTTON_COLOR,waitASK*18);
            if a=ansAno then
               begin
                 E^.read_from_editor;
                 {$IFDEF SYNCHRONIZE_EXT}
                  O^.update_pkt (pchars(E^.text_adr),strlen(E^.text_adr),hd^.err,hd^.fn, E^.spr_ed,'')
                 {$ENDIF}
               end;
            E^.is_chg:= a=ansZrus;
            _icao_editor_cancel:= a
          end
     end;


{ natiahnutie predchadzajucej/nasledujucej
  spravy do editora
}
  function  _icao_editor_load (_smer : int;
                               _novy : bool;

                               E  : PEXTEd;
                               O  : PO_EXT;
                               hd : p_type_ext_err_pkt;

                               path,mask : string
                              ): bool;

     var    D,D2 : DirStr; N,N2: NameStr; X,X2: ExtStr;
            s    : string;
            smer : int;
            nova : bool;

     begin
       _icao_editor_load:= false;
       if (E=nil) or (O=nil) or (hd=nil) then Exit;

       FSplit(hd^.fn, D,N,X);
       FSplit(mask, D2,N2,X2);
       if (X2='.') or (X2='') then mask:= N2+X;
       FSplit(path, D2,N2,X2);
       if D2='' then path:= D;
       if _smer=0 then smer:= 1
       else smer:= _smer;
       s:= dalsi_subor(D,mask, hd^.fn, smer);
       if (s='') or (_novy and (path+s=hd^.fn)) then
          begin
            if (_smer<>0) then Exit else smer:= -smer;
            s:= dalsi_subor(D,mask, hd^.fn, smer)
          end;
       if s='' then Exit;

       s:= path+s;
       if (s<>hd^.fn) then
          begin
          { Ulozenie? ak bol zmeneny obsah...
          } nova:= _novy or (_icao_editor_cancel(E,O,hd)<>ansZrus);
            strdispose(hd^.pkt);
            if nova and (O^._read_txt_file(s,true,hd^.err,hd^.pkt)) then
               begin
                 hd^.fn:= s;
                 E^._write_in_editor(hd^.pkt,strlen(hd^.pkt));
                 E^.new_title(hd^.err);
                 E^.pos_prev:= -1;
                 E^.List;
                 _icao_editor_load:= true
               end;
          end
       else begin
              if smer=-1 then s:= edi_queue_start else s:= edi_queue_end;
              if _smer<>0 then Say2(msgMESS,s)
            end
     end;


{ Je v editore sprava, ktorej oprava bola prijata ?
}
  function  _is_icao_editor_refresh (var Ev : TEvent;

                                     E : PEXTEd;
                                     O : PO_EXT;

                                     const hd : type_ext_err_pkt;
                                     var data : TSYNC_EXTpkt
                                    ): bool;
     var    key1,key2: string;
            D1,D2 : DirStr;
            N1,N2 : NameStr;
            E1,E2 : ExtStr;
            is    : bool;

     begin
       _is_icao_editor_refresh:= false;
       if not ((E<>nil) and (O<>nil) and (Ev.from=O) and (Ev.Box<>nil) and (Ev.Size=sizeof(data))) then Exit;

       Move(Ev.Box^,data,sizeof(data));
       if (data.data<>nil) and (data.size<>0) then
          begin
            key1:= O^._key_data(pchars(hd.pkt),strlen(hd.pkt));
            key2:= O^._key_data(data.data,data.size);
            is:= key1=key2
          end
       else if data.fn<>'' then
          begin
            FSplit(hd.fn,D1,N1,E1);
            FSplit(data.fn,D2,N2,E2);
            is:= D1+N1=D2+N2
          end
       else is:= false;
       _is_icao_editor_refresh:= is
     end;


{ Prepisanie obsahu formulara prijatou spravou
}
  function  _icao_editor_reload (E : PEXTEd;
                                 O : PO_EXT;

                                 var   hd   : type_ext_err_pkt;
                                 const data : TSYNC_EXTpkt
                                ): bool;

     var   i : int;
     begin
       _icao_editor_reload:= false;
       if (E=nil) or (O=nil) then Exit;

       Say2(msgMESS,say_message_changed_+is_NODEname(data.from)+'.');

       strdispose(hd.pkt);
       if data.size>0 then
          begin
            getmem(hd.pkt,data.size+1);
            move(data.data^,hd.pkt^,data.size);
            for i:= 0 to data.size-1 do if hd.pkt[i]=NULL then hd.pkt[i]:= ' ';
            hd.pkt[data.size]:= NULL
          end;
       hd.err:= data.tit;

       E^._write_in_editor(hd.pkt,strlen(hd.pkt));
       E^.new_title(hd.err);
       E^.pos_prev:= -1;
       E^.List;

       _icao_editor_reload:= true
     end;


{ odmazanie  obsahu formulara
}
  {function  _icao_editor_clear (E : PEXTEd;
                                O : PO_EXT;

                                var   hd   : type_ext_err_pkt;
                                const data : TSYNC_EXTpkt
                               ): bool;

     begin
       _icao_editor_clear:= false;
       if (E=nil) or (O=nil) then Exit;

       Say2(msgMESS,'Edited message has been processed by '+is_NODEname(data.from)+'.');
       E^.is_chg:= false;

       _icao_editor_clear:= _icao_editor_load(0,false, E,O, path,mask, @hd)
     end;}



  function  _icao_editor_handle (var Ev : TEvent;

                                 E : PEXTEd;
                                 O : PO_EXT;

                                 path,mask : string;
                                 hd : p_type_ext_err_pkt;

                                 load : bool
                                ): bool;

     var    data : TSYNC_EXTpkt;
            smer : int;
            pkt  : pchar;

     begin
       _icao_editor_handle:= true;

       {$IFDEF DEBUG}
        if isKey (Ev, #250) then net_pkt_test('net.tst',-1,-1);
       {$ENDIF}

       if (E=nil) or (O=nil) or (hd=nil) or (not ((Ev.What=evCommand) or (Ev.What=evBroadcast))) then Exit;

       case Ev.command of

         cmCancel      : if _icao_editor_cancel(E,O,hd)=ansZrus then E^.ClearEvent(Ev)
                         else Exit;

         cmEditRefresh : if _is_icao_editor_refresh(Ev, E,O, hd^,data) then
                            begin
                              _icao_editor_reload (E,O,hd^,data);
                            end;

         cmEditDelete  : if _is_icao_editor_refresh(Ev, E,O, hd^,data) then
                            begin
                              Say2(msgMESS,say_message_processed_+is_NODEname(data.from)+'.');
                              E^.is_chg:= false;
                              if _icao_editor_load(0,true, E,O,hd, path,mask) then
                              else SetCommand(Pending,E,cmCancel)
                            end;

         cmPrev,cmNext : begin
                           if Ev.command=cmPrev then smer:= -1 else smer:= 1;
                           _icao_editor_load(smer,false, E,O,hd, path,mask)
                         end;

         cmPrint       : begin
                          {$IFDEF PRN}
                            E^.read_from_editor;
                            pkt:= E^.text_adr;
                            O^.print_pkt(pchars(pkt),strlen(pkt),'')
                          {$ENDIF}
                         end

         else Exit
       end;

       ClearEvent(Ev,E)
     end;


  function _icao_editor_check (E : PEXTEd;
                               O : PO_EXT;

                               text_adr : pchar;

                               path,mask : string  { parameter navyse }
                              ): bool;

     var   head,resh,resd : string;
           bres : bool;
           hd : p_type_ext_err_pkt;

     begin
       _icao_editor_check:= false;
       if (E=nil) or (O=nil) then Exit;
       hd:= p_type_ext_err_pkt(E^.handler_data);
       if (hd=nil) then Exit;

       resh:= ''; resd:= ''; bres:= false;
       InfoCakaj (msgWAITING,say_checking_message);
       { priznak "src_ed" sposobi, ze sprava sa spracovava,
         i ked stanica nie je v mode "MASTER"
       }
       O^.process_data (src_ed, pointer(text_adr),strlen(text_adr),head, resh,resd);
       InfoCakaj_zatvor;
       if resd<>'' then
          begin
          { sprava o neuspesnom spracovani sa nerozosiela (ani v process_pkt),
            az pri zatvoreni spravy/editora, ako sprava src_ed
          } E^.new_title(resd);
            Err2('',resd)
          end
       else begin
            { spravu o spracovani distribuoval process_pkt...
              ako vysledok dekodovania,
              teraz je potrebne odmazat paket z radu
              pre spracovanie
            }
              O^.delete_pkt (pchars(text_adr),strlen(text_adr), hd^.err,hd^.fn, E^.spr_del, '', true,false);
              hd:= E^.handler_data;
              bres:= _icao_editor_load (0,true, E,O,hd, path,mask)
            end;
       _icao_editor_check:= (resd='') and (not bres) { uz nie je dalsia oprava...}
     end;


  function  _icao_editor(_title: string;
                         var _x,_y, _mode: int;
                         _viewer : bool;
                         _riadkov,_znakov, _velkost_strany: int;

                         _write_txt,_read_txt : pointer;
                         _check_func : pointer;
                         _dxb,_dyb : int;

                         _init_buttons,_handle_buttons : pointer;
                         _handler_owner : PO_EXT;
                         _handler_data : p_type_ext_err_pkt;
                         _handle_end_state : pointer;

                         _bge,_cle, _abg,_acl, _bgv,_clv : byte;
                         _spr_ed,_spr_del : TNETtyp;
                         _hlpXXX : Pchar;

                         var _pkt : pchar
                        ): bool;

     var    E  : PEXTEd;
            Ev : TEvent;
     begin
       E:= New(PEXTEd,Init(_title, _x,_y,_mode,
               _viewer, _riadkov,_znakov, _velkost_strany,
               _write_txt,_read_txt,
               _check_func,
               _dxb,_dyb,
               _init_buttons,_handle_buttons,_handler_owner,_handler_data,nil,
               _bge,_cle, _abg,_acl, _bgv,_clv,
               _spr_ed,_spr_del,
               _hlpXXX,
               _pkt)
              );
       E^.Run{LocalFunc}(Ev{,nil});
       _icao_editor:= E^.corr_res;
       Dispose(E,Done)
     end;
