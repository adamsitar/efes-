constructor TTxtFileEditor.Init
                         (_Owner : PGroup;
                          var _x,_y, _mode: int; _cmXXXX: word; _title : string;

                          _win_en : bool;
                          _viewer : bool;

                          _strana: pointer; _riadkov,_znakov, _velkost_strany: int;

                          _fn,_tmp,_ini : string;

                          _odd_rdk,_odd_slv : TCharSet; _odd_rdkr: string;

                          _check_func : pointer;    { TBFunc_p3(@Self,handler_owner,text_adr) }

                          _dxb,_dyb       : int;
                          _init_buttons,

                          _handle_buttons : pointer;
                          _handler_owner  : PObject;
                          _handler_data   : pointer;

                          _bge,_cle, _bga,_cla, _bgv,_clv : byte;
                          _hlpXXX : Pchar
                         );
      begin
        fn := strpasnew(_fn);
        tmp:= _tmp;
        ini:= strpasnew(_ini);
        if FExists(_fn)=0 then copyfile(_fn,_tmp)
        else if FExists(_tmp)<>0 then copyfile(_ini,_tmp);
        TxtFile:= New(PTxtFileBuffer,Init(_tmp));
        TxtFile^.ReadFile;

        inherited Init (_Owner, _x,_y,_mode, _cmXXXX, _title,
                        _win_en,_viewer,
                        _strana,_riadkov,_znakov,_velkost_strany,
                        _tmp,
                        nil,nil,pointer(TxtFile),0,0,false,false,
                        _odd_rdk,_odd_slv, _odd_rdkr,
                        _check_func,
                        _dxb,_dyb,
                        _init_buttons,
                        _handle_buttons,
                        _handler_owner,
                        _handler_data,
                        _bge,_cle, _bga,_cla, _bgv,_clv,
                        _hlpXXX
                       )
      end;

destructor TTxtFileEditor.Done;
     begin
       inherited Done;
       dispose(TxtFile,Done);
       strdispose(ini);
       strdispose(fn);
     end;


procedure TTxtFileEditor.__write_in_editor(_text_adr : pointer;
                                           _text_len : word
                                          );
    var   i : int;
    begin
      i:= 0; while (i<TxtFile^.items) and (i<riadkov) do
        begin
          _write_line_in_editor (i, TxtFile^.read(i));
          inc(i)
        end;
    end;

procedure  TTxtFileEditor.__read_from_editor;
    var    i,k : word;
    begin
      TxtFile^.truncate(0);
     { najde posledny neprazdny riadok }
      k:= TxtFile^.items;
      while (k>0) and (cut_(_read_line_from_editor(k))='') do dec(k);
      i:= 0; while (i<k) and (i<riadkov) do
        begin
          TxtFile^.add(_read_line_from_editor(i));
          inc(i)
        end;
    end;


procedure TTxtFileEditor.handle_buttons(var _Event: TEvent);
   begin
     inherited handle_buttons(_Event);
     if _Event.what=evNothing then Exit;

     case _Event.command of

       cmCancel       : Exit;

       {cmEditRefresh : if _is_icao_editor_refresh(Ev, E,O, hd^,data) then
                              _icao_editor_reload (E,O,hd^,data);
       }

       {cmVLOZ_VZOR    : begin
                         clear_items;
                         delfile(tmp);
                         copyfile(strpas(ini),tmp);
                         read_editor;
                         pos_prev:= -1;
                         List
                       end;}


       else Exit
     end;

     ClearEvent(_Event)
   end;



{procedure TTxtFileEditor.make_message;
    begin
    end;}