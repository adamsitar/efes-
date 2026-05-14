{ -----------
   ACT
  -----------
}

{ Act z vonku
}
 function _filter_FPL_ACT(FPL: PFPL4; pitem: PFPL4_item_filter): bool; far;
    var   kod: string; h,m: byte;
          B: TsBod;
    begin
      _filter_FPL_ACT:=     _ACT_OR_DEP
                         or (not decode_l4_13(FPL^._13, kod,h,m,h,m))
                         or (not (is_OB(kod,B,true) and B.ine.podriadene))
    end;

 function _ACT_FPL4(FPL: PFPL4): bool; far;
    var   res  : string;
          ires : int;
          err  : string;
    begin
      _ACT_FPL4:= false;
      if FPL=nil then Exit;

      if not fpl_approved(FPL^.src,_FPL4_APROVED_CHECK) then
         begin
           if _find_err (fnERR_L4,a_FPL4,idn_FPL4(FPL),0,err_FPL4notapproved,err) then
           else err:= tit_FPL4notapproved;
           if Ask2(msgWARNING,err,titNo,clGRe,Red,waitASK*18)<>ansAno then Exit;
         end;

      if _ACT_AS_EST then
         begin
           res:= ''; ires:= -1;
           InfoCakaj(msgWAITING,tit_dekoduje_plan);
           _fpl4_date_all:= true;
           ires:= _decode_FPL4(FPL^,false,res);
           InfoCakaj_zatvor;
           if (FPL^.data=nil) or (FPL^.data^.fdr=nil) and (FPL^.data^.fdr^.fpl=nil) then Exit;
           FPL^.data^.fdr^.fpl^.stt:= hd_ACT;
           formular_cFPL_(FPL^.data^.fdr^.fpl,msg_FPLc_ACT);
         end
      else formular_FPL4(FPL,user,hd_ACT,false,tit_fpl_act,nil,nil);
    end;

 procedure ACT_FPL4i;
     var   finded_data : int;
           key : string;
     begin
       if      (not _spracuj_FPL (true,true,false,false, true,false,
                                  @key,@finded_data,
                                  @_filter_FPL_ACT,ms_ICAOplan+ms_ICAOact,'',
                                  _TBFunc_p,@_ACT_FPL4,
                                  tit_fpl_act,hlpmnuFPL4
                                 )
                )
          {$IFDEF FPL4_ACT} {$IFDEF EDD}
           and (key<>'')
           and (finded_data<=0)
          {$ENDIF} {$ENDIF}
            then
          begin
           {$IFDEF FPL4_ACT} {$IFDEF EDD}
             {NETdistribute_msg([SERVER,BSERVER],[],[], spr_FPL4_REQ, @key[1],length(key),true, net_flag_SEND);}
           {$ENDIF} {$ENDIF}
         end
     end;
