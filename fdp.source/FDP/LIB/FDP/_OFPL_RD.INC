{ Predpokladam, ze si pamatam stav ack/noack (i na disku).
  Moze sa zmenit :
    - ack/noack  od seba (EDD) a sector (RDP)
    - oprava planu => musi si zistit stav ack alebo ho nesmie prepisat
    - prijem dat zo siete => ak
}

{$IFDEF RDP}

  procedure O_FPL.message_to_RDP_sector(p: pointer; kod: TNETtyp);
      begin
        { for i:= 0 to NODEpoc-1 do if strpos(NODEs^[i].desc.inf,nd_SECTOR)<>nil then }
        if find(p)<0 then Exit;

        if (sector_RDPnd<>-1) and (p_message<>nil) then
          begin
           {$IFDEF DATA_BIN}
            if NODEs^[sector_RDPnd].desc.typ = RDP0 then
               case kod of
                 spr_EST_CNL    : kod:= spr0_RDP_EST_DEL;

                 spr_ACCEPT     : kod:= spr0_RDP_A;
                 spr_UNACCEPT   : kod:= spr0_RDP_UA;
                 spr_HANDOVER   : kod:= spr0_RDP_H;
                 spr_UNHANDOVER : kod:= spr0_RDP_UH
               end;
           {$ENDIF}
            sprava(p,kod,NODEs^[sector_RDPnd].desc.adr)
          end
      end;


 {$IFDEF RDP_ACCEPT}

  function  O_FPL.get_accept(p: pointer; var ACPT: TTRG_stat; var RDP: TRTRadr): TTRG_stat;
     begin
       ACPT:= _cor; RDP:= 0;
       get_accept:= _cor
     end;

  procedure O_FPL.set_accept(p: pointer; TRG: TTRG_stat; RDP: TRTRadr);
     begin
     end;

  function  O_FPL.is_rdp_sector(RDP: TRTRadr): int;
     var    i : int;
     begin
       {i:= 0; while (i<NODEpoc) and (RDP<>NODEs^[i].desc.adrr) do inc(i);
       if (i>=NODEpoc) or (strpos(NODEs^[i].desc.inf,nd_SECTOR)=nil) then i:= -1;
       is_rdp_sector:= i}
       if RDP=sector_RDP then is_rdp_sector:= sector_RDPnd
       else is_rdp_sector:= -1
     end;


  procedure O_FPL.RDP_accept(idn: string; TRG: TTRG_stat; RDP: TRTRadr; send: bool);
      var   ind: int;
            is_acpt: TTRG_stat; is_rdp: TRTRadr;
      begin
        ind:= find_id(idn); if ind<0 then Exit;
        get_accept(ap^[ind], is_acpt,is_rdp);
        if (is_acpt=TRG) and (is_rdp=RDP) then Exit;

        set_accept(ap^[ind], TRG, RDP);
        vypis_plan(ind, false, false);
        uloz(ap^[ind]);
       { posli_spravu_na_server, zacyklil by sa ?
       }
      end;

  procedure O_FPL.EDD_accept(p: pointer; TRG: TTRG_stat; RDP: TRTRadr; send: bool);
      var   ind,i : int;
            is_acpt: TTRG_stat; is_rdp: TRTRadr;
            kod   : word;
      begin
        ind:= find(p); if ind<0 then Exit;
        get_accept(ap^[ind], is_acpt,is_rdp);
        if (is_acpt=TRG) and (is_rdp=RDP) then Exit;

        set_accept(ap^[ind], TRG, RDP);
        vypis_plan(ind, false, false);
        uloz(ap^[ind]);

        if send then
          begin
           if TRG=_acc then kod:= spr_ACCEPT else kod:= spr_UNACCEPT;
           {$IFDEF RDP}
             message_to_RDP_sector(p, kod)
           {$ENDIF}
           { posli_spravu_na_server, zacyklil by sa ?
           }
          end
      end;


  { ----------------------------------
     riadenie FPL na RDP
    ----------------------------------
  }

  procedure O_FPL.FL_accept(idn: string; RDP: TRTRadr);
      begin
        RDP_accept(idn,_acc,RDP,true)
      end;

  procedure O_FPL.FL_unaccept(idn: string; RDP: TRTRadr);
      begin
        RDP_accept(idn,_cor,0,true)
      end;

  procedure O_FPL.FL_handover(idn: string; RDP: TRTRadr);
      begin
        RDP_accept(idn,_acc,RDP,false)
      end;

  procedure O_FPL.FL_unhandover(idn: string; RDP: TRTRadr);
      begin
        RDP_accept(idn,_cor,0,false)
      end;


  { ----------------------------------
     riadenie FPL na EDD
    ----------------------------------
  }

  procedure O_FPL.FPL_accept(p: pointer);
      begin
        EDD_accept(p, _acc,sector_RDP, true)
      end;

  procedure O_FPL.FPL_unaccept(p: pointer);
      begin
        EDD_accept(p, _cor,0, true)
      end;


  procedure init_RDP_SECTOR;
      var   i,c: int;
            _err: bool;
      begin
        _err:= false;
        {$IFDEF RDP_ACCEPT}
        { Urcenie adresy RDP, ktory je s nim na sektore
        }
          for i:= 0 to NODEpoc-1 do with NODEs^[i].desc do
            begin
              if (strpos(inf,nd_SECTOR)<>nil) then
                 if (sector_RDPnd<>-1) then RunError('Too many RDP sectors.')
                 else begin
                        {val(NETadr_wan(adr),RDP_SECTOR_nd,c);}
                        sector_RDP:= NODEs^[i].desc.adrr;
                        sector_RDPnd:= i
                      end;
            end;
          if (sector_RDPnd=-1) then MessError('There is not defined RDP sector.',true,_err)
          else if (sector_RDP=0) then MessError('There is not defined RDP sector address.',true,_err);
        {$ENDIF}
        if _err then writeln;
      end;

 {$ENDIF}

{$ENDIF}
