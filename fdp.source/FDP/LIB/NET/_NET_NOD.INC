{ ----------------------------
   Kontrola stavu uzlov ...
  ----------------------------
}

procedure TNET.initialize_node(nd: int);
    begin
      Diagnose
    end;


procedure TNET.check_nodes;

    const {RTEnode_is_initialized : bool = false;}
          m    : byte = 60;
          s           = 30;
          i    : int  = 0;
          ii   : int  = 0;

    var   d    : TDatum;
          L    : long;
          inf  : bool;
          r    : real;
          t    : string;

    begin

     {$IFDEF CAS_SERVER}
     { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
        Rozoslanie casu ...
       תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
     } if (m<>BIOS.min) and (sec>s) then
          begin
            m:= BIOS.min;
            datum_init (d, day,month,year, hour,BIOS.min,sec);
            distribute_data([FDP0,FDP],[],[], spr_CAS, @d,@code_UTC,nil,nil, true,inf_CAS,nil,true,false,net_flag_NIL)
          end;
     {$ENDIF}

     { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
        Ma sa uzol inicializovat ?
       תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
     } if (DISTRIBUTE_EN) then
          if (i < NODEpoc) then with NODEs^[i] do
             begin

               if not (desc.typ in set_nd_LETVIS) then
                  begin
                  end

               else if (not stat.semaphor) then
                  begin

                    if (stat.TrasaOK) and (stat.NodeInit) then
                       begin
                        { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
                          detekovana ziadost o inicializaciu alebo obnovenie spojenia
                          תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
                        }
                         if INITIALIZE_EN and NET_ENABLED then
                            begin

                              {$IFDEF BACKUP_ACTIVE_2_NET}

                               { zalozny server rozosiela udaje namiesto hlavneho,
                                 je povolena inicializacia :
                               }
                               {$IFDEF BACKUP}
                                 { zalozny server - vsetkych smerov
                                 }
                               {$ELSE} {$IFDEF MASTER}
                                 { hlavny server - len zalozneho servera
                                 }
                                 if BACKUPstatus and (i<>BACKUPnode) then stat.NodeInit:= false;
                               {$ELSE}
                                 { ostatne smery - okrem hlavneho servera
                                 }
                                 if (i=SERVERnode) and (BACKUPnode>-1) and BACKUPstatus then stat.NodeInit:= false;
                               {$ENDIF} {$ENDIF}

                              {$ELSE}

                               { hlavny server rozosiela udaje namiesto zalozneho,
                                 je povolena inicializacia :
                               }

                               {$IFDEF BACKUP}
                                 { zalozny server - len hlavneho servera
                                 }
                                 if SERVERstatus and (i<>SERVERnode) then stat.NodeInit:= false;
                               {$ELSE} {$IFDEF MASTER}
                                 { hlavny server - vsetkych smerov
                                 }
                               {$ELSE}
                                 { ostatne smery - mali by okrem zalozneho servera
                                 }
                                 if (i=BACKUPnode) and (SERVERnode>-1) and SERVERstatus then stat.NodeInit:= false;
                               {$ENDIF} {$ENDIF}

                              {$ENDIF}

                               if     (stat.NodeInit)
                                  and (not s_init)
                                  and (desc.nd in [SLAVE,MASTER]) then
                                  begin
                                    {RTEnode_is_initialized:= (desc.pro=RTR);}

                                    ii:= i; s_init:= true;
                                    stat.semaphor := true;
                                    stat.NodeInit := false;

                                    with NODEs^[i].stat do
                                      begin
                                        if INIT_VYP and InitEn then
                                           begin
                                             r:= INIT_INT;
                                             if (absTime<InitLast+r*60) then
                                                begin
                                                  inc(InitPoc);
                                                  if InitPoc>INIT_POCET then
                                                     begin
                                                       t:= NODEs^[i].desc.adr + tit_INIT_NOT;
                                                       Err2(msgWARNING,t);
                                                       writeln_mess0(t, true,true, cl_NODE_OFF,arch_MESS, true);
                                                       InitEn:= false;
                                                     end
                                                end
                                             else InitPoc:= 1;
                                           end;

                                        InitLast:= absTime;
                                        if InitEn then
                                           begin
                                             initialize_node(i);
                                           end
                                      end;

                                    stat.semaphor := false;
                                    i:= ii; s_init:= false;
                                    {if (desc.pro=RTR) then RTEnode_is_initialized:= false;}
                                  end
                            end
                       end

                    else if stat.Node_ON then
                      begin
                      { תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
                         uzol nie je nie inicializovany, kontroluje sa stav uzla
                        תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
                        V pripade, ze nie su odosielane ziadne data, kontroluje sa, ci
                        podriadene (slave) a nadriadene (master) stanice su zive,
                        odosiela sa heartbeat. Ak je trasa off, odosiela sa vyzva,
                        a v pripade jej nepotvrdenia sa predlzuje perioda jej
                        odoslania az na 3*tmout_HEARTBEAT
                      }

                        inf:=  (desc.nd in [MASTER]) or (StrPos(desc.inf,inf_HeartBeat)<>nil);
                        if (desc.nd in [SLAVE,MASTER]) then L:= stat.NextTest
                        else if inf then L:= tmout_HEARTBEAT
                        else L:= 0;
                        {$IFDEF BACKUP} {$IFNDEF BACKUP_ACTIVE_2_NET}
                          if (i=SERVERnode) then L:= SERVERtimeout*18;
                        {$ENDIF} {$ENDIF}
                        if L<>0 then
                           begin
                            { bol vyslany test alebo sprava -> caka na potvrdenie spravy
                            }
                             if     (not (stat.TrasaOK))
                                and (desc.nd in [SLAVE,MASTER])
                                and (TimeOut(stat.SendTick, getticks, L)) then
                                    begin
                                      NETsend_msg(desc.adr,spr_CALL, nil,0, false,net_flag_SEND);
                                      stat.NextTest:= Minimum(stat.NextTest shl 1,tmout_CALL_hi)
                                    end
                            { test. ci stanica zije...
                            }
                             else begin
                                    L:= tmout_HEARTBEAT;
                                    {$IFDEF BACKUP} {$IFNDEF BACKUP_ACTIVE_2_NET}
                                     if (i=SERVERnode) then L:= SERVERtimeout*18;
                                    {$ENDIF} {$ENDIF}
                                    if     (StrPos(desc.inf,inf_HeartBeat)<>nil)
                                       and TimeOut(stat.SendTick,getticks,L) then
                                       begin
                                         NETsend_msg(desc.adr,spr_HEARTBEAT, nil,0, true,net_flag_SEND)
                                       end
                                  end
                           end
                      end
                  end;
               Diagnose;
               inc(i)
             end
          else i:= 0
    end;

(*
procedure TNET.initialize_nodes;
    begin
    end;
*)