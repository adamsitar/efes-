 { -----------
    CHG
   -----------
   - ak bola na plan odoslana poziadavka na acc, musi byt znova odoslana
   - ak bol plan odoslany, musi byt zmena znova odoslana
 }
 function _is_CHG(FPL: PDmFPL; s: Pstring): bool; far;
    var   cond: string;
    begin
      cond:= cnl_stat(cnst_FPL_CHG);
      _is_CHG:= _is_plan_FPLm{_is_stat_FPLm}(FPL,@cond)
    end;

 function _CHG_FPL(sc: PScroller; FPL: PDmFPL): bool; far;
    var   send, res: bool;
    begin
      (*
      {$IFDEF AIRBASE}
      if _is_stat_(FPL, cnst_prop+cnst_acc) then FPL^.stat:= cnst_prop;
      {$ENDIF}
      send:= _is_stat_(FPL, cnst_sended+cnst_prop+cnst_acc+cnst_ACT_plan);
      formular_mFPL(FPL, not send, false, '', 'Oprava pl nu letu', hlp_mFPL)
      *)
      res:= formular_mFPL(FPL,letvis,
                          {add_stat(}del_cnl_stat(FPL^.stat){,cnst_chg)},
                          false,
                          msg_FPLm_CHG,i_15M,nil,hlp_mFPL
                         );
      _CHG_FPL:= false
    end;

 procedure mFPL_CHG;
     begin
       spracuj_mFPL(find_and_process_FPLM,find_and_process_FPLM,true,false,false,true,
                    '', @_is_CHG,
                    @_CHG_FPL,_TBFunc_p2,
                    true,true,
                    msg_FPLm_CHG,nil,
                    hlp_mFPL_CHG
                   )
     end;


 { -----------
    CNL
   -----------
 }
 function _CNL_FPL_(sc: PScroller; FPL: PDmFPL; tit: string): bool;
    var   s : string;
          b : bool;
    begin
      _CNL_FPL_:= false;
      s:= tit+' '+code_FPLM_7a(FPL)+' ';
      b:= pos(cnst_disk,FPL^.stat)=0;
      if b then s:= s+ask_rozoslat+' ';
      s:= s + '?';
      if (Ask2(msgVERIPHY,s,titNO,White,clBUTTON_COLOR,waitASK*18)=ansAno) then
          zarad_FPLm(FPL,{add_stat(FPL^.stat,}cnst_cnl{)},b,letvis)
    end;


 function _is_CNL(FPL: PDmFPL; s: Pstring): bool; far;
    var   cond: string;
    begin
      cond:= cnst_planned;
      _is_CNL:= _is_plan_FPLm{_is_stat_FPLm}(FPL,@cond)
    end;

 function _CNL_FPL(sc: PScroller; FPL: PDmFPL): bool; far;
    begin
      _CNL_FPL_(sc,FPL,ask_fpl_CNL);
      _CNL_FPL:= false;
    end;

 procedure mFPL_CNL;
     begin
       spracuj_mFPL(find_and_process_FPLM,false,
                    true,false,false,true,
                    '', @_is_CNL,
                    @_CNL_FPL, _TBFunc_p2,
                    false,false,
                    msg_FPLm_CNL,nil,hlp_mFPL_CNL
                   )
     end;


 {
 procedure mFPL_DLA;
     begin
       spracuj_mFPL(get_fnFPL_let,@dbchg_mFPL,
                    cnst_ACT_plan, @_is_stat,
                    @DLA_FPL,_TBFunc_p2,
                    false,false,false,
                    'OPRAVA POLOHY NA BODE',nil,hlp_mFPL_DLA
                   )
     end;
 }



 function _is_SEND(FPL: PDmFPL; s: Pstring): bool; far;
    var   cond: string;
    begin
      cond:= cnst_disk;
      _is_SEND:=     (SERVERnode>-1)
                 and _plan_pre(FPL^.let)
                 and (FPL^.rec[SERVERnode]=no_ack)
    end;

 function _SEND_FPL(FPL: PDmFPL): bool; far;
    begin
      if pos(cnst_disk,FPL^.stat)<>0 then zarad_FPLm(FPL,cnst_sended,true,letvis)
      else distribute_mFPL(FPL,[],[]);
      _SEND_FPL:= true
    end;


 procedure send_FPLs(FPLs: PmFPLs; top: pointer);
     var   i : int;
           b : bool;
     begin
       if int(top^)<0 then Exit;

       i:= 0; b:= true;
       while b and (i<=int(top^)) do
         begin
           if _is_SEND(FPLs^[i],nil) then
              begin
                b:= _SEND_FPL(FPLs^[i]);
                {if not WAIT_INIT_NODE then} Wait(3,CheckProcesses)
              end;
           inc(i)
         end;
       say_data_sended(b)
     end;


 {$IFDEF KRL}
  procedure send_KRLs  (FPLs: PmFPLs; top: pointer);
      var   i,j,p : int;
            res,b,b2 : bool;
      var   M   : PWinMenu;
            Mi  : array[0..maxNODEs] of PItem;
            AP  : array[0..maxNODEs] of string[KOD_AP];
            E   : TEvent;
      begin
        if int(top^)<0 then Exit;

        M:= WinMenu(' Kr¡dla pre: ', nil,nil);
        p:= 0;
        for i:= 0 to NODEpoc-1 do
         if (strpos(NODEs^[i].desc.inf,nd_AP)<>nil) and (strpos(NODEs^[i].desc.inf,inf_KRL)<>nil) then with NODEs^[i] do
            begin
              AP[p]:= NETadr_wan(strpas(NODEs^[i].desc.name));
              Mi[p]:= Item(' ~'+AP[p][1]+'~'+copy(AP[p],2,length(AP[p])-1),cmOTHER+p,nil);
              inc(p)
            end;

        if p=0 then
           begin
             Dispose(M, Done);
             Exit
           end;

        for i:= 0 to p-1 do M^.AddItem(Mi[i]);
        M^.Centre;
        M^.Run(E);
        Dispose(M, Done);
        i:= 0; while (i<p) do
          begin
            if isCommand(E,cmOTHER+i) then break;
            inc(i)
          end;
        if not (i<p) then Exit;

        j:= 0; b:= true; b2:= false;
        while j<=int(top^) do
          begin
            if    { (not is_this_airbase(FPLs^[j]^.start.kod))
              and}(   (FPLs^[j]^.start.kod = NETadr_wan(AP[i]))
                  {or (FPLs^[j]^.prist.kod = NETadr_wan(AP[i]))}
                  )
              then begin
                     b2:= true;
                     b:= _SEND_FPL(FPLs^[j]);
                     Wait(3,CheckProcesses)
                   end;
            inc(j)
          end;
        if b2 then say_data_sended(b)
      end;
 {$ENDIF}