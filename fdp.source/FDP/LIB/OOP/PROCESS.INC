constructor TProcess.Init (_title,_btOKtitle: string;
                           _info,_key: string;
                           _do_it: pointer; _data: pointer;
                           {_items: int; _pitem: pint;}
                           var _is_done: bool
                          );
      var   pch: pchar;
      begin
        info:= _info; key:= _key;
        sprava:= info+key+'...';
        p_is_done:= @_is_done;
        p_is_done^:= false;
        {$IFDEF ARCHIVE_PROGRAM_ERR}
         if archive_info_mess then _write_err_log(sprava+'  ('+WordToHex(Seg(Self))+':'+WordToHex(Ofs(Self))+')');
        {$ENDIF}
        sprava:= sprava+NULL; pch:= @sprava[1];
        {items:= _items; pitem:= _pitem;}
        inherited Init(_title,_btOKtitle,
                       nil,nil,0,0,
                       @pch,1,
                       clGRe,clBUTTON_COLOR-2,
                       nil,nil,
                       -1,nil,nil,GetTicks,
                       nil,nil
                      );
        do_it:= _do_it; data:= _data;
        lmain:= false;
      end;

procedure TProcess.Idle(var _Event: TEvent);
    var   bres: bool;
    begin
      if (do_it<>nil) then
         begin
           bres:= t_proc_ext_process(do_it)(data,{pitem,items,}@Self);
           if bres then
              begin
                SetCommand(_Event,cmOK);
                p_is_done^:= true
              end;
         end
    end;

procedure TProcess.new_item(_key: string);
    var   pch : pchar;
          dx,dy,i : int;
    begin
      sprava:= info+copy(_key,1,length(key))+'...'; { orezanie na inicializovanu dlzku }
      {$IFDEF ARCHIVE_PROGRAM_ERR}
       if archive_info_mess then _write_err_log(sprava);
      {$ENDIF}
      sprava:= sprava+NULL; pch:= @sprava[1];
      for i:= 0 to ms-1 do strdispose(mp[i]);
      message_split(@pch,1, 0,0, strpas(btTitle^.title), mp,ms, dx,dy);
      draw_
    end;

destructor TProcess.Done;
     var   s: string;
     begin
        {$IFDEF ARCHIVE_PROGRAM_ERR}
         if archive_info_mess and (p_is_done<>nil) then
            begin
              if p_is_done<>nil then s:= 'Done.' else s:= 'Pended...';
              _write_err_log(s+'  ('+WordToHex(Seg(Self))+':'+WordToHex(Ofs(Self))+')');
            end;
        {$ENDIF}
       inherited Done
     end;

