procedure TPLAN.posli(p: pointer; adr: TNETadr; wait: bool);
    begin
      if (p_send<>nil) then TNET_send_pkt(p_send)(p,adr,wait)
    end;


procedure TPLAN.rozosli (p: pointer; p_add: pbool);
    begin
      if not rozoslat then Exit;
      if (p_distribute<>nil) then TNET_distribute_rdp_pkt(p_distribute)(p,p_add)
    end;


procedure TPLAN.sprava(p: pointer; typ: TNETtyp; adr: TNETadr);
    begin
      if find(p)<0 then Exit;
      if (p_message<>nil) and (typ<>0) then TNET_message_pkt(p_message)(p,typ,adr)
    end;


{$IFDEF DEBUG} { I sec0.inc} {$ENDIF}

function odosli_plan(PLAN: PPLAN; p: pointer): bool;
   begin
   end;


function  TPLAN.Inicializacia (nd      : int;      { cislo uzla }
                               info    : string;   { typ informacie odosielanej na uzol }
                               filter  : pointer   { @TBfunc_pi - poslat plan na tento smer ? (sektor) }
                              ): bool;
    var   rec : Pplan_rec;
          bres, is_ini : bool;
          i : int;

    begin
     {$IFDEF NET}
      with NODEs^[nd] do
        begin
          is_ini:=      stat.Node_ON
                   and (   (desc.typ in [RDP0,RDP0NX,RDP,MON])
                        or (strpos(desc.inf,ndp_INITALL)<>nil)
                       );
          i:= 0; while (stat.TrasaOK) and (i<=top) do
            begin
              rec:= get_rec(ap^[i]);
              if is_ini and (rec<>nil) then rec^[nd]:= no_ack;
              if     (is_ini or ((rec<>nil) and (rec^[nd]=no_ack)))
                 and is_to_nd(nd,info,filter,ap^[i],nil)
                 (*and (     is_rdp
                        or (   (p_codekey=nil)                { neposielat znova spravu, na potvrdenie ktorej sa este caka }
                            or ((p_codekey<>nil) and (not NETack^.is_for_ack(nd,get_key(ap^[i]))))
                           )
                     )*)
                 then begin
                        posli(ap^[i],desc.adr, WAIT_INIT_NODE);
                        {if (not WAIT_INIT_NODE) then Wait(1,CheckProcesses)} CheckProcesses
                      end;
              CheckProcesses;
              inc(i)
            end;

          bres:= (not WAIT_INIT_NODE) or ((stat.TrasaOK) and (i>top));

          {if bres and is_rdp and (EN_RDP_ZO_SUBORA>0) and (nodesRDP < EN_RDP_ZO_SUBORA) then
             begin
               if (FN='') and (p_nameDB<>nil) then FN:= TSFunc(p_nameDB);
               DB_prehladaj(p_load, @Self, p, disp_item, FN, riadkovDB, p_decodeDB, false);
               function preaktivuj_plan(PLAN: PPLAN; p: pointer): bool;
             end;}

          Inicializacia:= bres
        end;
     {$ELSE}
      Inicializacia:= true;
     {$ENDIF}
    end;

