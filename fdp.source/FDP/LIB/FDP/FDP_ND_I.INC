{ Pozn: kontrola na to, ci data neboli odoslane, a nechaka sa na ich
        potvrdenie- (not NETack^.is_for_ack(nd^,codekey_mFPL(p))) )
}

 function nd_init_res(nd: int): byte; far;
    begin
      if NODEs^[nd].stat.TrasaOK then nd_init_res:= do_item__NEXT
      else nd_init_res:= do_item__BREAK
    end;



{$IFDEF PLN}
  function nd_init_PLN(p: PPLN; nd: pint): byte; far;
     begin
       if     ( (p^.rec[nd^]=no_ack) )
          {and ( NET_ACK_DELETE_ALL_ACK or (not NETack^.is_for_ack(nd^,code_key_PLN(p))) )}
              then send_PLN(p,NODEs^[nd^].desc.adr,WAIT_INIT_NODE);
       nd_init_PLN:= nd_init_res(nd^)
     end;
{$ENDIF}


{$IFDEF FPL4}
  function nd_init_FPL4(p: PFPL4; nd: pint): byte; far;
     begin
       if     ( (p^.rec[nd^]=no_ack) )
          {and ( NET_ACK_DELETE_ALL_ACK or (not NETack^.is_for_ack(nd^,code_key_PLN(p))) )}
              then send_FPL4(p,NODEs^[nd^].desc.adr,WAIT_INIT_NODE);
       nd_init_FPL4:= nd_init_res(nd^)
     end;
{$ENDIF}


{$IFDEF FPL0}
  { TBfunc_pi(filter)(data,nd))
  }
  function is_cFPL_to_nd(FPL: PDcFPL; nd: int): bool; far;
     begin
       is_cFPL_to_nd:= true
     end;

  {function is_EST_to_nd(FPL: PDcFPL; nd: int): bool; far;
     begin
       is_EST_to_nd:= FPL^.stt<>hd_CPL
     end;

  function is_CPL_to_nd(FPL: PDcFPL; nd: int): bool; far;
     begin
       is_CPL_to_nd:= FPL^.stt=hd_CPL
     end;}


 {$IFNDEF FPLM_DISABLED}
  function is_mFPL_to_nd(FPL: PDmFPL; nd: int): bool; far;
     begin
       is_mFPL_to_nd:= send2node_mFPL(FPL,nd)
     end;

  function nd_init_mFPL(p: PDmFPL; nd: pint): byte; far;
     begin
       if     ( p^.rec[nd^]=no_ack  )
          and ( pos(cnst_disk,p^.stat) = 0 )
          {and ( NET_ACK_DELETE_ALL_ACK or (not NETack^.is_for_ack(nd^,codekey_FPLM(p))) )}
          and send2node_mFPL (p,nd^)
              then send_mFPL(p,NODEs^[nd^].desc.adr,WAIT_INIT_NODE);
       nd_init_mFPL:= nd_init_res(nd^)
     end;

 {$IFDEF KRL}
  function nd_init_KRL(p: PDmFPL; nd: pint): byte; far;
     begin
       if     ( p^.rec[nd^]=no_ack )
          and ( pos(cnst_disk,p^.stat) = 0 )
          {and ( NET_ACK_DELETE_ALL_ACK or (not NETack^.is_for_ack(nd^,codekey_FPLM(p))) )}
          and send2node_KRL (p,nd^)
              then send_mFPL(p,NODEs^[nd^].desc.adr,WAIT_INIT_NODE);
       nd_init_KRL:= nd_init_res(nd^)
     end;
 {$ENDIF}
 {$ENDIF}

{$ENDIF}


{$IFDEF INIT_PLANY_ZO_SUBORA}

  {
    TByFunc_p2 = function(buff: pointer; param: pointer): byte;

    Prvu filtraciu urobi
     * node_initialize_DB - na povolene smery (vysiela sa len ku
       SERVERu alebo SLAVE, vynimkou su diverzie a kridla),
     * druhu nd_init - ci uz boli data dorucene...
  }


  {$IFDEF ZAM}
    function nd_init_ZAM(p: PZAM; nd: pint): byte; far;
       begin
         if     ( p^.rec[nd^]=no_ack )
            and ( pos(cnst_disk,p^.stat) = 0 )
          {and ( NET_ACK_DELETE_ALL_ACK or (not NETack^.is_for_ack(nd^,code_key_PLN(p))) )}
                then send_ZAM(p,NODEs^[nd^].desc.adr,WAIT_INIT_NODE);
         nd_init_ZAM:= nd_init_res(nd^)
       end;
  {$ENDIF}


  {$IFDEF DVZ}
    function nd_init_DVZ(p: PDVZ; nd: pint): byte; far;
       begin
         if     (p^.rec[nd^]=no_ack)
            and ( pos(cnst_disk,p^.stat) = 0 )
            {and (    (adr_airbase(p^.let_) = NODEs^[nd^].desc.adr)
                  or (adr_airbase(p^.let)  = NODEs^[nd^].desc.adr)
                )
            }
          {and ( NET_ACK_DELETE_ALL_ACK or (not NETack^.is_for_ack(nd^,code_key_PLN(p))) )}
            then send_DVZ(p,NODEs^[nd^].desc.adr,WAIT_INIT_NODE);
         nd_init_DVZ:= nd_init_res(nd^)
       end;
  {$ENDIF}


  {$IFDEF QGO}
    function nd_init_QGO(p: PQGO; nd: pint): byte; far;
       begin
         if     (p^.rec[nd^]=no_ack)
            and ( pos(cnst_disk,p^.stat) = 0 )
          {and ( NET_ACK_DELETE_ALL_ACK or (not NETack^.is_for_ack(nd^,code_key_PLN(p))) )}
            then send_QGO(p,NODEs^[nd^].desc.adr,WAIT_INIT_NODE);
         nd_init_QGO:= nd_init_res(nd^)
       end;
  {$ENDIF}


  {$IFDEF RTZ}
    function nd_init_RTZ(p: PRTZ; nd: pint): byte; far;
       begin
         if     (p^.rec[nd^]=no_ack)
          { and ( pos(cnst_disk,p^.stat) = 0 )}
          {and ( NET_ACK_DELETE_ALL_ACK or (not NETack^.is_for_ack(nd^,code_key_PLN(p))) )}
            then send_RTZ(p,NODEs^[nd^].desc.adr,WAIT_INIT_NODE);
         nd_init_RTZ:= nd_init_res(nd^)
       end;
  {$ENDIF}


  {$IFDEF PRZ}
    function nd_init_PRZ(p: PPRZ; nd: pint): byte; far;
       begin
         if     (p^.rec[nd^]=no_ack)
            and (pos(cnst_disk,p^.stt) = 0)
          {and ( NET_ACK_DELETE_ALL_ACK or (not NETack^.is_for_ack(nd^,code_key_PLN(p))) )}
                then send_PRZ(p,NODEs^[nd^].desc.adr,WAIT_INIT_NODE);
         nd_init_PRZ:= nd_init_res(nd^)
       end;

    function nd_init_PRN(p: PPRN; nd: pint): byte; far;
       begin
         if     (p^.rec[nd^]=no_ack)
            and (pos(cnst_disk,p^.stt) = 0)
          {and ( NET_ACK_DELETE_ALL_ACK or (not NETack^.is_for_ack(nd^,code_key_PLN(p))) )}
                then send_PRN(p,NODEs^[nd^].desc.adr,WAIT_INIT_NODE);
         nd_init_PRN:= nd_init_res(nd^)
       end;
  {$ENDIF}


  {$IFDEF PRS}
    function nd_init_PRS(p: PPRS; nd: pint): byte; far;
       begin
         if     (p^.rec[nd^]=no_ack)
            and (pos(cnst_disk,p^.stat) = 0)
          {and ( NET_ACK_DELETE_ALL_ACK or (not NETack^.is_for_ack(nd^,code_key_PLN(p))) )}
                then send_PRS(p,NODEs^[nd^].desc.adr,WAIT_INIT_NODE);
         nd_init_PRS:= nd_init_res(nd^)
       end;
  {$ENDIF}


  {$IFDEF MET}
    function nd_init_SYN(p: PSYN; nd: pint): byte; far;
       begin
         if     (p^.rec[nd^]=no_ack)
          {and ( NET_ACK_DELETE_ALL_ACK or (not NETack^.is_for_ack(nd^,code_key_PLN(p))) )}
                 then send_SYN(p,NODEs^[nd^].desc.adr,WAIT_INIT_NODE);
         nd_init_SYN:= nd_init_res(nd^)
       end;
  {$ENDIF}

{$ENDIF}