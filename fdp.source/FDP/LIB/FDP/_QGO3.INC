{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ spracovanie QGO                                          €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}

{$IFDEF PROCESS_QGO}

  { -------------------------------
    CHG
  }

   function _QGO_CHG(QGO: PQGO): bool; far;
      begin
        _QGO_CHG:= false;
        formular_QGO(QGO, false,false)
      end;

   procedure QGO_oprava(ppl: bool);
       var   QGO : TQGO;
             FN  : string;
             p   : pointer;
       begin
         if ppl then FN:= get_PPL_FN(pathQGO,extQGO,tit_QGO)
         else FN:= get_dbQGOfn;
         {$IFDEF AIRBASE} p:= @_is_stat_QGO;
         {$ELSE}          p:= @_is_stata_QGO;
         {$ENDIF}
         spracuj_QGO(FN, nil,{@dbchg_QGO,}
                     cnl_stat(cnst_all_valid), p,
                     @_QGO_CHG,_TBFunc_p,
                     true,tit_QGO,nil
                    )
       end;

        {
          if read_this_QGO(@QGO,get_PPL_FN(pathQGO,extQGO, tit_QGO_CHG))<>-1 then
             begin
               _oprav_QGO(nil,@QGO);
               disp_QGO(@QGO)
             end
         }

  { -------------------------------
    CNL
  }
  function _QGO_CNL(QGO: PQGO): bool; far;
     var   s: string;
           b: bool;
     begin
       s:= ask_QGOCNL+' ('+QGO^.kod+') ';
       b:= pos(cnst_disk,QGO^.stat)=0;
       if b and _plan_pre_pracovisko(QGO) then s:= s + ask_rozoslat+' ';
       s:= s + '?';
       if (Ask2(msgVERIPHY,s, titNO,White,clBUTTON_COLOR,waitASK*18) = ansAno) then
          zarad_QGO(QGO, cnst_cnl, b, letvis);
       _QGO_CNL:= false
     end;

 procedure QGO_zrusenie;
     var   QGO : TQGO;
           FN  : string;
           p   : pointer;
     begin
       FN:= get_dbQGOfn;
       {$IFDEF AIRBASE} p:= @_is_stat_QGO;
       {$ELSE}          p:= @_is_stata_QGO;
       {$ENDIF}
       spracuj_QGO(FN, nil,{@dbchg_QGO,}
                   cnst_all_valid, p,
                   @_QGO_CNL,_TBFunc_p,
                   true,tit_QGO,nil
                  )
     end;
      {
       if (read_this_QGO(@QGO,get_dbQGOfn)<>-1) then
          begin
            _zrus_QGO(nil,@QGO);
            disp_QGO(@QGO)
          end
       else Say2(msgMESS,'Spr†va o schopnostiach na dnes nie je podan†.')}


 function _is_SEND(QGO: PQGO; s: Pstring): bool; far;
    var   cond: string;
    begin
      cond:= cnst_disk;
      _is_SEND:= (SERVERnode>-1) and (QGO^.rec[SERVERnode]=no_ack) and _is_stat_QGO(QGO,@cond)
    end;

 function _SEND_QGO(QGO: PQGO): bool; far;
    begin
      if pos(cnst_disk,QGO^.stat)<>0 then _SEND_QGO:= zarad_QGO(QGO,cnst_sended,true, letvis)
      else _SEND_QGO:= distribute_QGO(QGO,[],[]) {send_QGO(QGO,SERVERaddress,WAIT_INIT_NODE)}
    end;

  {procedure QGO_posli;
      var   QGO : TQGO;
      begin
        if read_this_QGO(@QGO,get_PPL_FN(pathQGO,extQGO, 'Odoslanie spr†vy o schopnostiach'))<>-1 then
           begin
             zarad_QGO(@QGO,cnst_sended,true, letvis);
             disp_QGO(@QGO)
           end;
      end;}
{$ENDIF}
