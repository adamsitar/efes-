{
  1. Vysle na stanicu svoje nacionaly
}
procedure _init_cfg_mess(var pkt : TIPXpkt; przn: word);
    var   typ : word;
    begin
      pkt.data[0]:= przn;
      pkt.data[1]:= lo(RTRadr);
      pkt.data[2]:= hi(RTRadr);

      typ:= ipx_nd_FDP;
      pkt.data[3]:= lo(typ);
      pkt.data[4]:= hi(typ)
    end;

procedure _IPX_cfg_mess(node: int; przn: word);
    var   pkt : TIPXpkt;
          s : string;
    begin
      _init_cfg_mess(pkt,przn);
      IPX_send_data(node,@pkt.data,5,System_socket);
      {$IFDEF ARCHIVE_NET_BIN}
       s:= 'IPX login ('+cstr(node,1)+') : '+init_str (@pkt.data,5);
       archive_data(path_NET, get_ARCHfn(0)+'.'+extNET, @s[1],length(s),archSYS,true,false);
      {$ENDIF};
    end;

procedure _IPX_cfg_mess_(adr: TNodeAdr; przn: word);
    var   pkt : TIPXpkt;
          s : string;
          i : int;
    begin
      _init_cfg_mess(pkt,przn);
      _IPX_send_packet_(0,adr,System_socket,ipxDATA,5,@pkt.data);
      {$IFDEF ARCHIVE_NET_BIN}
       s:= ''; for i:= 0 to sizeof(TEthernetAdr)-1 do s:= s+ByteToHex(adr[i]);
       s:= 'IPX login ('+'$'+delchar(s,['$'])+') : '+init_str(@pkt.data,5);
       archive_data(path_NET, get_ARCHfn(0)+'.'+extNET, @s[1],length(s),archSYS,true,false);
      {$ENDIF};
    end;

{
  2. Prijme opravu parametrov od stanice v dosledku prepnutia na inu,
     alebo vymeny za inu. Adresa RTR sa nemeni. (Ani nemoze...)
     Tyka sa to vlastne IPX adresy ROUTERa a stanic pracujucich
     v rezime RTI.
}
function _IPX_cfg_set(var pkt: TIPXpkt_nd): bool;
   var   _adr  : TRTRadr;
         _typ  : word;
         _nadr : TNETadr;
         _nd,i : int;
         p     : pointer;
         s,t   : string;
   begin
     _IPX_cfg_set:= false;

     p:= @pkt.data[1];
     move(p^,_adr,sizeof(TRTRadr)); incptr(p,sizeof(TRTRadr));
     move(p^,_typ,sizeof(_typ));

     {$IFDEF ARCHIVE_NET_BIN}
      s:= ''; for i:= 0 to sizeof(TEthernetAdr)-1 do s:= s+ByteToHex(pkt.adr[i]);
      s:= WordToHex(_typ)+', '+WordToHex(_adr)+', '+delchar(s,['$']);
      archive_data(path_NET, get_ARCHfn(0)+'.'+extNET, @s[1],length(s),archSYS,true,false);
     {$ENDIF};

     s:= '';
     if _typ<>ipx_nd_RTR then
        begin
          _nd:= 0; while (_nd<NODEpoc) and (NODEs^[_nd].desc.adrr<>_adr) do inc(_nd);
          if (_nd>=NODEpoc) then Exit;
          s:= 'Node: '+WordToHex(NODEs^[_nd].desc.adrr)+', '+NODEs^[_nd].desc.adr;

          {if (_adr<>RROUTERadr) then}
             if (NODEs^[_nd].desc.pro=RTI) then
                begin
                  _nadr:= NETadr_lan_(NODEs^[_nd].desc.adr);
                  _nd:= isIPXname(_nadr);
                  s:= s+'/'+_nadr+'/'+cstr(_nd,1);
                end
             else _nd:= -1
          {else _nd:= ROUTERnode};
        end
     else begin
            _nd:= ROUTERipx
          end;

     {$IFDEF ARCHIVE_NET_BIN}
      if s<>'' then archive_data(path_NET, get_ARCHfn(0)+'.'+extNET, @s[1],length(s),archSYS,true,false);
     {$ENDIF};

     {if IPXnodes[_nd]^.Connected then}
     if (_nd>=-1) then
        begin
          IPXnodes[_nd]^.adr:= pkt.adr;
          pkt.nd:= _nd;
          _IPX_cfg_set:= true;

         {$IFDEF ARCHIVE_NET_BIN}
          s:= s+' n.'+cstr(_nd,1);
          t:= ''; for i:= 0 to sizeof(TEthernetAdr)-1 do t:= t+ByteToHex(IPXnodes[_nd]^.adr[i]);
          s:= s + ', $' + delchar(t,['$']);
          archive_data(path_NET, get_ARCHfn(0)+'.'+extNET, @s[1],length(s),archSYS,true,false);
         {$ENDIF};
        end;
   end;


procedure IPX_check_system_mess; far;
    const semaphor: bool = false;
    var   pkt : TIPXpkt_nd;
    begin
      if (not semaphor) and (system_buff<>nil) and (system_buff^.is)  then
         begin
           semaphor:= true;
           while system_buff^.read(@pkt) do
             begin
               case pkt.data[0] of
                 ipx_sys_REQ  : if _IPX_cfg_set(pkt) then _IPX_cfg_mess(pkt.nd,ipx_sys_RES)
                                else _IPX_cfg_mess_(pkt.adr,ipx_sys_RES);
                 ipx_sys_RES  : _IPX_cfg_set(pkt)
                end
             end;
           semaphor:= false;
         end
    end;


procedure IPX_login;
    const T : real = 0;
    var   s : string;
    begin
      if (not IPX_GLOBAL_INIT) or (not (T<absTime+60)) then Exit;
    { rozoslanie adresy broadcastom }
     {$IFDEF ARCHIVE_NET_BIN}
       s:= 'IPX login';
       archive_data(path_NET, get_ARCHfn(0)+'.'+extNET, @s[1],length(s),archSYS,true,false);
     {$ENDIF};
      _IPX_cfg_mess(0,ipx_sys_REQ);
      T:= absTime
    end;

procedure IPX_read_system_mess;
    var   T: long;
    begin
      _IPX_cfg_mess(0,ipx_sys_REQ);

    { prijem adries od ostatnych    }
      T:= GetTicks;
      while not TimeOut(T,GetTicks, 3*18) do IPX_check_system_mess

      (*{$IFDEF DEBUG} {$IFDEF BROADCAST};
        IPX_close_socket(Broadcast_socket);
      {$ENDIF} {$ENDIF}*)
    end;
