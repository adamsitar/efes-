 procedure _help_(key,title: string);
     var   h: PHelp;
     begin
       h:= New(PHelp,Init(fn_hlp_exe,false,nil));
       {$IFDEF PRN}
        h^.dyb:= btHEIGHT+10;
        h^.init_buttons:= @scroll.init_sc_butt1;
       {$ENDIF}
       h^.is_help:= true;
       h^.empty_en:= false;
       h^.help(key,title);
       Dispose(h);
     end;

 procedure _help(key: pchar);
     begin
       _help_(strpas(key),'');
     end;


 procedure _info__ (fn,tit: string;
                    _dxm,_dym : int;
                    _dxb,_dyb : int;
                    _init_buttons,_handle_buttons,_handler_owner : pointer;
                    _SOH,_EOT,_EOH: char;
                    _hlpXXX: pchar
                   );
     var   h: PHelp;
     begin
       h:= New(PHelp,Init(fn,true,_hlpXXX));
       h^.dxm:= _dxm; h^.dym:= _dym;
       h^.SOH:= _SOH; h^.EOT:= _EOT; h^.EOH:= _EOH;
       h^.is_comment:= true{false};
       h^.comment_en:= true{false};
       h^.dxb:= _dxb; h^.dyb:= _dyb;
       h^.init_buttons:= _init_buttons;
       h^.handler_buttons:= _handle_buttons;
       h^.handler_owner:= _handler_owner;
       h^.help('',tit);
       Dispose(h)
     end;

 procedure _infoh (fn,tit: string;
                   _dxm,_dym : int;
                   _dxb,_dyb : int;
                   _init_buttons,_handle_buttons,_handler_owner : pointer;
                   _hlpXXX: pchar
                  );
     begin
       _info__(fn,tit, _dxm,_dym,
               _dxb,_dyb, _init_buttons,_handle_buttons,_handler_owner,
               hlp_SOH,hlp_EOT,hlp_EOH,
               _hlpXXX
              )
     end;

 procedure _info(fn,tit: string);
     begin
       _infoh (fn,tit, 0,0, 0,0, nil,nil,nil,nil)
     end;


 { TBFunc_vEp3(handle_buttons)(_Event,@Self,handler_owner,handler_data)
 }
 function  _handle_info_p (var Ev : TEvent;
                           H : PHelp;
                           O : pointer;
                           P : pointer
                          ): bool;
    var    i: int;
    begin
      _handle_info_p:= true;
     {$IFDEF PRN}
      if isCommand(Ev,cmPrint) then
         begin
           if print_head(PortNo,strpas(H^.win^.btTitle^.title)) then
              begin
                i:= 0; while (i<H^.items) and print_str(PortNo,_PRN_TAB+H^.get(i)+kbNL) do inc(i);
              end
         end
      else
      {$ENDIF}
      if isCommand(Ev,cmSend) then
         begin
         end
      else Exit;
      ClearEvent(Ev,H)
    end;

 procedure _infop(fn,tit: string;
                  _dxm,_dym : int;
                  print,send: bool;
                  _hlpXXX: pchar
                 );
     var   _dy: int;
           _init_buttons,
           _handle_buttons,
           _handler_owner   : pointer;
     begin
       _handler_owner:= nil;
       _handle_buttons:= nil;

       if print and send then _init_buttons:= @scroll.init_sc_butt2
       else if print then _init_buttons:= @scroll.init_sc_butt1
       else _init_buttons:= nil;
       if _init_buttons<>nil then
          begin
            _dy:= btHEIGHT+10;
            _handle_buttons:= @_handle_info_p
          end
       else _dy:= 0;

       _infoh(fn,tit, _dxm,_dym, 0,_dy, _init_buttons,_handle_buttons,_handler_owner, _hlpXXX)
     end;
