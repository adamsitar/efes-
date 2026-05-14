{$IFOPT R+} {$DEFINE R} {$R-} {$ENDIF}
{$IFOPT S+} {$DEFINE R} {$S-} {$ENDIF}
                        {$F+}

{ ---------------------------------------- }
{  broadcast                               }
{ ---------------------------------------- }

var   _ESb,_SIb : word;

procedure IPX_broadcast; far;
    var   ECB : PECB;
    begin
      {$IFDEF BROADCAST}
        ECB:= Ptr(_ESb,_SIb);
        ECB^.fragment_adress^.head.source_node:= BROADCAST;

        inp_brd_buff^.size:=   ((ECB^.fragment_adress^.head.len shl 8) and $FF00)
                             + ((ECB^.fragment_adress^.head.len shr 8) and $00FF)
                             ;
        inp_brd_buff^.size:= inp_brd_buff^.size-sizeof(TIPXhead);
        if inp_brd_buff^.size>sizeof(inp_brd_buff^.data) then inp_brd_buff^.size:= sizeof(inp_brd_buff^.data);
        move(ECB^.fragment_adress^.data,inp_brd_buff^.data,inp_brd_buff^.size);

        {$IFDEF ARCHIVE_DAR}
          if (save_RLI<>nil) then Tproc_pw(save_RLI)(@inp_brd_buff^.data, inp_brd_buff^.size); { -1 = 31-30 }
        {$ENDIF}

        if (isIPXbroadcast=nil) or ((TBFunc_p(isIPXbroadcast)(inp_brd_buff))) then
           begin
             if brd_buff<>nil then brd_buff^.save(inp_brd_buff)
           end;

        ECB^.listen_for_packet;
      {$ENDIF}
    end;


const adr_interrupt__IPX_broadcast: pointer = @IPX_broadcast;

procedure interrupt__IPX_broadcast; {far;}
    begin
      asm
        push AX
        push BX
        push CX
        push DX

        push SI
        push DI
        push DS
        push ES

        push BP
        mov  BP,SP
        {sub SP,LocalSize}

        mov  AX,SEG @Data
        mov  DS,AX

        mov  _ESb,ES
        mov  _SIb,SI
        call adr_interrupt__IPX_broadcast

        mov  SP,BP
        pop  BP

        pop  ES
        pop  DS
        pop  DI
        pop  SI

        pop  DX
        pop  CX
        pop  BX
        pop  AX
      end
    end;


{ ---------------------------------------- }
{  smerove vysielanie                      }
{ ---------------------------------------- }

var   _ESn,_SIn : word;

procedure IPX_node; far;
    var   ECB    : PECB;
          node   : int;
          typ    : byte;
    begin
      ECB:= Ptr(_ESn,_SIn);     { ECB *ecb = (ECB *) MK_FP (_ES,_SI); }
      node:= get_num(ECB^.fragment_adress^.head.source_node);
      if (node>-1) and (node<maxIPX_NODEs) then with IPXnodes[node]^ do
          begin
            typ:= ECB^.fragment_adress^.head.packet_type;

            if typ = ipxDATA then
               begin
                 inp_buff^.size:=   ((ECB^.fragment_adress^.head.len shl 8) and $FF00)
                                  + ((ECB^.fragment_adress^.head.len shr 8) and $00FF);

                 inp_buff^.size:= inp_buff^.size-sizeof(TIPXhead);
                 if inp_buff^.size>sizeof(inp_buff^.data) then inp_buff^.size:= sizeof(inp_buff^.data);
                 if inp_buff^.size>0 then
                    begin
                      move(ECB^.fragment_adress^.data,inp_buff^.data,inp_buff^.size);
                     {$IFDEF RTR}
                       RTRsave(inp_buff)
                     {$ELSE}
                       if (pro in [RTR,RTI]) or (ROUTERipx>-1) and (node=ROUTERipx)) then RTRsave(inp_buff)
                       else IPXsave(inp_buff)
                     {$ENDIF};
                    end
               end;

            {$IFDEF IPX0}
             if (not TrasaOK) then to_init:= 1;
             TrasaOK   := true;
             SendOK    := true;
             next_test := (sec+IPX__HEARTBEAT) mod 60;
             tested    := false;
             if (typ<>ipxPOTVRDENIE) then IPX_send_message(node,ipxPOTVRDENIE)
            {$ENDIF}
          end;
      ECB^.listen_for_packet
    end;


const  adr_interrupt__IPX_node: pointer = @IPX_node;

procedure interrupt__IPX_node; {far;}
    begin
      asm
        push AX
        push BX
        push CX
        push DX

        push SI
        push DI
        push DS
        push ES

        push BP
        mov  BP,SP
        {sub SP,LocalSize}

        mov  AX,SEG @Data
        mov  DS,AX

        mov  _ESn,ES
        mov  _SIn,SI
        call adr_interrupt__IPX_node

        mov  SP,BP
        pop  BP

        pop  ES
        pop  DS
        pop  DI
        pop  SI

        pop  DX
        pop  CX
        pop  BX
        pop  AX
      end
    end;



{ ---------------------------------------- }
{  systemove spravy                        }
{ ---------------------------------------- }

{$IFDEF IPX3}

  var   _ESs,_SIs : word;

  procedure IPX_system; far;
      var   ECB    : PECB;
            node   : int;
            typ    : byte;
      begin
        ECB:= Ptr(_ESs,_SIs);
        node:= get_num(ECB^.fragment_adress^.head.source_node);
        with system_pkt do
          begin
            typ:= ECB^.fragment_adress^.head.packet_type;
            if typ = ipxDATA then
               begin
                 nd:= node;
                 if nd<>IPXnode then
                    begin
                      adr:= ECB^.immediate_adress;
                      size:=   ((ECB^.fragment_adress^.head.len shl 8) and $FF00)
                             + ((ECB^.fragment_adress^.head.len shr 8) and $00FF);
                      size:= size-sizeof(TIPXhead);
                      if size>sizeof(data) then size:= sizeof(data);
                      if size>0 then
                         begin
                           move(ECB^.fragment_adress^.data,data,size);
                           {$IFDEF IPX3}
                             if (data[0] in[ipx_sys_REQ,ipx_sys_RES]) then SYSTEMsave(@system_pkt)
                           {$ENDIF}
                         end
                    end
               end;
            end;
        ECB^.listen_for_packet
      end;


  const adr_interrupt__IPX_system: pointer = @IPX_system;

  procedure interrupt__IPX_system; {far;}
      begin
        asm
          push AX
          push BX
          push CX
          push DX

          push SI
          push DI
          push DS
          push ES

          push BP
          mov  BP,SP
          {sub SP,LocalSize}

          mov  AX,SEG @Data
          mov  DS,AX

          mov  _ESs,ES
          mov  _SIs,SI
          call adr_interrupt__IPX_system

          mov  SP,BP
          pop  BP

          pop  ES
          pop  DS
          pop  DI
          pop  SI

          pop  DX
          pop  CX
          pop  BX
          pop  AX
        end
      end;

{$ENDIF}

{$IFDEF R} {$UNDEF R} {$R-} {$ENDIF}
{$IFDEF S} {$UNDEF S} {$S-} {$ENDIF}
