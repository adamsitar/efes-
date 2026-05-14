{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   Init
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

   Pred inicializaciou musi byt X25_init !
}

{const SaveMain: TProc = nil;

procedure _check_OLDI_status; far;
    begin
      if @SaveMain<>nil then SaveMain;
      if DEV_OLDI<>nil then DEV_OLDI^.check0
    end;}

constructor O_OLDI.Init(_p_power : pbool;
                        _cfg_FN, _cfg_OB : string;
                        _lam: int;
                        _pkt_size, _buff_size: word; _is_buff0: bool;
                        _sync_info,_coor_info : pchar;

                        _p_heads_ICAO : Pheads_ICAO; _heads_ICAO : word;
                        _p_heads_LAM : Pheads_ICAO; _heads_LAM : word;

                        _p_wr, _p_arch, _p_utc : pointer;
                        _cl_s, _cl_r : byte;
                        _path, _ext : string
                       );
      begin
        inherited Init(nil,
                       _p_power,
                       _cfg_FN,_cfg_OB,
                       _lam,false,
                       _pkt_size, _buff_size, _is_buff0, _buff_size,
                       0,0,0,0,0,0,0,0,0,0,
                       _sync_info,_coor_info,
                       _p_heads_ICAO, _heads_ICAO,
                       _p_heads_LAM,  _heads_LAM,
                       _p_wr,_p_arch,_p_utc, _cl_s,_cl_r,
                       _path,_path+spath_ERR,_ext
                      );


       {$IFDEF OLDI}
        {SaveMain:= ACheck;
        ACheck:= _check_OLDI_status;}

        writeln_pkt(nil,0,arch_SYS,'OLDI init.',cl_SYS,false,false);
       { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }
         chng_OLDI_status(IDLE_STATE,false);
       { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }

       { X.25 sa otvara pre odposluch a caka na inicializaciu vzdialenym uzlom }
        OLDI_X25nodeA:= -1; OLDI_X25nodeB:= -1;
        OLDI_X25node_:= -1;
        {$IFDEF _X25}
         if X25_net<>nil then
            begin
            { registracia uzla X.25 }
              OLDI_X25nodeA:= X25nodes^.AddNode('OLDI-A',X25adr_MASTER,X25adr_MASTER, false,false);
              {$IFDEF OLDI_BACKUP}
               if X25adr_BACKUP<>'' then OLDI_X25nodeB:= X25nodes^.AddNode('OLDI-B',X25adr_BACKUP,X25adr_BACKUP, false,false);
              {$ENDIF}
              X25_net^.p_enabled_SVC := @_enabled_SVC;
              X25_net^.p_receive_pkt := @_receive_pkt;
              X25_net^.p_archive_operation := @_archive_operation;
            end
         else writeln_pkt(nil,0, arch_ERR,'Xת25 not alive, protocol OLDI will be death bug.', cl_ERR, false,false);
        {$ENDIF}
       {$ENDIF}
      end;


destructor  O_OLDI.Done;
    begin
     {$IFDEF OLDI}
      { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }
         handle_OLDI_event(VC_Clear,nil);
      { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת }
       writeln_pkt(nil,0,arch_SYS,'OLDI done.',cl_SYS,false,false);

      {$IFDEF _X25}
       if X25_net<>nil then
          begin
            X25_net^.p_enabled_SVC:= nil;
            X25_net^.p_receive_pkt:= nil;
            X25_net^.p_archive_operation:= nil;
          end;
      {$ENDIF}
     {$ENDIF}
      inherited Done
    end;


function   O_OLDI.read_cfg(_cfg_FN: string): bool;
    var    res, s : string;

    procedure get_NSAP(var s: string; var NSAP_: NSAP);
        var   i: int;
              l: long;
        begin
          {s:= delchar(s,[' ','.',',']);}
          for i:= 1 to sizeof(NSAP_) do
            begin
              if not is_scish_(getstr(s,i,[' ',',',';']),l,false) then RunError(_cfg_FN+' -> Invalid NSAP.');
              NSAP_[i-1]:= trunc(l)
            end
          {scis_(s,1+(i-1)*2,2,false)}
        end;

    var   _err: bool;
    begin
      _err:= false;
      read_cfg:= false;
      if not inherited read_cfg(_cfg_FN) then Exit;
      res:= '';

      { Maxiamlna Velkost paketu }
{28?} ipkt_size:= Limit(read_cfg_word(_cfg_FN, cfg_PKT_SIZE, OLDI_pkt_size),OLDI_pkt_size_lo,OLDI_pkt_size_hi+28,0);
      {$IFDEF _X25}
        { nastavenie maximalnej hodnoty do cfg suborov Xת25 }

        EXCEPTION_CALL_DESC:= read_cfg_bool(_cfg_FN, cfg_EXCEPTION_CALL_DESC, EXCEPTION_CALL_DESC);
      {$ENDIF}

     { Nazov uzla }
      NODE_THIS:= _read_cfg(_cfg_FN,cfg_NODE_THIS,true);
      if NODE_THIS='' then res:= cfg_NODE_THIS;

      NODE_REMOTE:= _read_cfg(_cfg_FN,cfg_NODE_REMOTE,true);
      if NODE_REMOTE='' then res:= cfg_NODE_REMOTE;

     {$IFDEF OLDI}

      { Adresy X25
      }
       X25adr_THIS:= delchar(_read_cfg(_cfg_FN,cfg_X25adr_THIS,true),[' ','.',',']);
       if X25adr_THIS='' then res:= cfg_X25adr_THIS;

       X25adr_MASTER:= delchar(_read_cfg(_cfg_FN,cfg_X25adr_MASTER,true),[' ','.',',']);
       if X25adr_MASTER='' then MessError('Not assigned master address for protocol OLDI/X25...',true,_err);
       {$IFDEF OLDI_BACKUP}
        X25adr_BACKUP:= delchar(_read_cfg(_cfg_FN,cfg_X25adr_BACKUP,true),[' ','.',',']);
        if X25adr_BACKUP='' then MessError('Not assigned backup address for protocol OLDI/X25...',true,_err);
       {$ENDIF}

       X25adr_REMOTE_:= '';


      { NSAP
      }
       s:= _read_cfg(_cfg_FN,cfg_NSAP_THIS,true);
       get_NSAP(s,NSAP_THIS);
       if s='' then res:= cfg_NSAP_THIS;

       s:= _read_cfg(_cfg_FN,cfg_NSAP_REMOTE,true);
       get_NSAP(s,NSAP_REMOTE);
       if s='' then res:= cfg_NSAP_REMOTE;

       _make_UDF(NSAP_THIS,NSAP_REMOTE, UDF);


      { OLDI
      }
       send_StartUp:= read_cfg_bool(_cfg_FN, cfg_Send_StartUp, true);
       switch_Remote:= read_cfg_bool(_cfg_FN, cfg_switch_Remote, false);

     {$ENDIF}

      if res<>'' then RunError(_cfg_FN+' -> item "'+res+'" is missing.');

      if _err then writeln;
      read_cfg:= true
    end;


{$IFDEF OLDI}

 function O_OLDI.is_pkt_for_node (from: string; data: pchars; size: word): bool;
    begin
      is_pkt_for_node:= (from = '') or (from = X25adr_REMOTE_) or (from = NODE_PROMISCUITE)
    end;


 procedure O_OLDI.HandleEvent(var _Event: TEvent);
     begin
       inherited HandleEvent(_Event);

       if (_Event.What<>evNothing) then
         case _Event.Command of

           cmOLDI_INFO           : Dialog.Info(cfg_FN, @_info_OLDI,@Self,550,180,nil,0);

           cmOLDI_TEST_TrTimeout : Tr_:= 0;
           cmOLDI_disable_SVC    : disable_SVC;

           else Exit
         end
       else Exit;

       ClearEvent(_Event)
     end;

{$ENDIF}

{function O_OLDI._key_data (data: pchars; size: word): string;
   var   s: string;
   begin
     _key_data:= ''
   end;
}
