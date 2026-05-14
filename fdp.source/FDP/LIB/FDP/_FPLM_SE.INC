{ -------------------
   NET - distribucia
  -------------------
}

{ plan sa posiela na EDD,SRD ako EST,
  na IDD ako schvalena pripomienka,
  vid sourcecode...
}
 function send2node_mFPL(FPL: PDmFPL; nd: int): bool;
    begin
      send2node_mFPL:=        true {send2node(FPL^.stat, nd)}
                       {$IFDEF AIRBASE}
                         and (    (not (NODEs^[nd].desc.sw in set_nd_OPL))
                               or _FPLM._plan_pre_pracovisko (FPL)
                             )
                       {$ENDIF}
    end;

 function send2node_KRL(FPL: PDmFPL; nd: int): bool;
    var   adr: string;
    begin
      adr:= adr_airbase(FPL^.start.kod);
      send2node_KRL:= adr<>''
    end;


 function send_mFPL(FPL: PDmFPL; adr: TNETadr; wait: bool): bool;
    var   kod    : TNETtyp;
          p_code : pointer;
    begin
      send_mFPL:= false;
      kod:= spr_FPLM;
      p_code:= @code_FPLM;
      if not is_KRL(FPL) then
         begin
          {$IFDEF DATA_BIN}
           case NETtype(adr) of
             FDP0,FDP0NX :
                    begin
                      kod:= spr0_mFPL;
                      p_code:= @code0_mFPL
                    end;
             RDP0,RDP0NX :
                    begin
                      kod:= spr0_RDP_mFPL;
                      p_code:= @code0_mFPL_RDP
                    end
           end;
          {$ENDIF}
           send_mFPL:= NETres(NETsend_data
                         (adr, kod,
                          FPL, p_code,@codekey_FPLM,@FPL^.rec,
                          true,inf_FPLM,@send2node_mFPL,
                          wait,false, net_flag_NIL
                         ))
         end
      else begin
            {$IFDEF KRL}
              send_mFPL:= _odosli_KRL(FPL)
            {$ENDIF}
           end
    end;


 {$IFDEF KRL}

   function _odosli_KRL (FPL: PDmFPL): bool;
      var   b   : bool;
            adr : TNETadr;
      begin
        b:= pos(cnst_disk,FPL^.stat)<>0;
        if b then FPL^.stat:= cnst_sended;

        adr:= adr_airbase(FPL^.start.kod);
        if (adr<>'') and (adr<>NETaddress) then
           begin
             _odosli_KRL:= NETres(NETsend_data
                            (adr, spr_FPLM,
                             FPL, @code_FPLM,@codekey_KRL,@FPL^.rec,
                             true,inf_KRL,@send2node_mFPL,
                             false,false, net_flag_SEND
                            ))
           end
        else _odosli_KRL:= false
      end;
 {$ENDIF}


 function  distribute_mFPL(FPL: PDmFPL; sw: Tnd_sw_set; nd: Tnd_nd_set): bool;
    var    res : bool;
    begin
      distribute_mFPL:= false;
      if is_KRL(FPL) then Exit;

      res:= true;
      {$IFDEF DATA_BIN}
       res:= NETdistribute_data
                    (
                     [FDP0,FDP0NX],sw,[MASTER,SLAVE],
                     spr0_mFPL, FPL,@code0_mFPL,@codekey_FPLM,@FPL^.rec,
                     true,inf_FPLM,@send2node_mFPL,false,false,net_flag_NIL
                    );
      {$ENDIF}
      res:= NETdistribute_data
                   (
                    [FDP],sw,[MASTER,SLAVE],
                    spr_FPLM, FPL,@code_FPLM,@codekey_FPLM,@FPL^.rec,
                    true,inf_FPLM,@send2node_mFPL,false,false,net_flag_NIL
                   ) and res;

      distribute_mFPL:= res
    end;


 function  distribute_rdp_mFPL (FPL: PDmFPL; add: pbool): bool;
    var    res, est : bool;
           stt : string;
    begin
      res:= true;

      if add<>nil then est:= add^
      else est:= est_mFPL(FPL);

      {$IFDEF RDP}
       if est then
         begin
          {$IFDEF ARCHIVE_DAR}
           {$IFDEF DATA_BIN} DAR_arch.save_FDP(spr0_RDP_mFPL, FPL, @code0_mFPL_RDP);
           {$ENDIF}          DAR_arch.save_FDP(spr_FPLM, FPL, @code_FPLM);
          {$ENDIF}

          {$IFDEF DATA_BIN}
            res:= NETdistribute_data
                         (
                          [RDP0,RDP0NX],[],[SLAVE],
                          spr0_RDP_mFPL, FPL,@code0_mFPL_RDP,@codekey_FPLM,@FPL^.rec,
                          true,inf_FPLM,@send2node_mFPL,false,false,net_flag_NIL
                         ) and res;
          {$ENDIF}
           res:= NETdistribute_data
                        (
                         [RDP],[],[SLAVE],
                         spr_FPLM, FPL,@code_FPLM,@codekey_FPLM,@FPL^.rec,
                         true,inf_FPLM,@send2node_mFPL,false,false,net_flag_NIL
                        ) and res;
         end
       else begin
              stt:= FPL^.stat; FPL^.stat:= cnst_cnl;
             {$IFDEF DATA_BIN}
              res:= NETdistribute_data
                        ([RDP0,RDP0NX],[],[],
                         spr0_RDP_EST_DEL, FPL,@code0_mFPL_mess,@codekey_FPLM,nil,
                         true,inf_FPLM,nil,false,false,net_flag_SEND
                        );
             {$ELSE}
               res:= true;
             {$ENDIF}
              res:= NETdistribute_data
                        ([RDP,MON],[],[],
                         spr_EST_CNL, FPL,@code_FPLM_mess,@codekey_FPLM,nil,
                         true,inf_FPLM,nil,false,false,net_flag_SEND
                        ) and res;
              FPL^.stat:= stt
            end;
      {$ENDIF}

      distribute_rdp_mFPL:= res;
    end;


 procedure message_mFPL (FPL: PDmFPL; kod: word; adr: TNETadr);
     var   p_code : pointer;
           pkod   : word;
     begin
        pkod:= kod;
        p_code:= @code_FPLM_mess;
        {$IFDEF DATA_BIN}
          if NETtype(adr) in [FDP0,FDP0NX,RDP0,RDP0NX] then
             begin
               pkod:= code_0type(kod);
               p_code:= @code0_mFPL_mess
             end;
        {$ENDIF}

        {$IFDEF ARCHIVE_DAR}
          DAR_arch.save_FDP(pkod,FPL, p_code);
        {$ENDIF}

        if cut_(adr)<>'' then
           begin
             NETsend_data(adr,
                          pkod, FPL,p_code,@codekey_FPLM,nil,
                          true,inf_FPLM,nil, false,false, net_flag_SEND
                         )
           end
        else begin
              {$IFDEF DATA_BIN}
               NETdistribute_data
                      ([RDP0,RDP0NX],[],[],
                       code_0type(kod), FPL,@code0_mFPL_mess,@codekey_FPLM,nil,
                       true,inf_FPLM,nil,false,false,net_flag_SEND
                      );
              {$ENDIF}
               NETdistribute_data
                      ([RDP],[],[],
                       kod, FPL,@code_FPLM_mess,@codekey_FPLM,nil,
                       true,inf_FPLM,nil,false,false,net_flag_SEND
                      );
             end;
     end;


{ -------------------
   EXT - koordinacia
  -------------------
}
 procedure coordinate_FPLM (FPL: PDmFPL;
                            src: fdp_src; dst: set_fdp_src;
                            zmena, zmeneny: bool
                           );
     var   head: Thead_ICAO;
           stat: string;
     begin
      {$IFDEF EXTERNAL_NET}
       if is_KRL(FPL) then Exit;

       {if zmena then zmeneny:= zmeneny_mFPL(FPL,false);}

       stat:= FPL^.stat;
       {if __is_stat(stat,cnst_acc) then head:= hd_ABI
       else} if __is_stat(stat,cnst_stat_dep) then head:= hd_ACT
       else if pos(cnst_stat_arr,stat)>0 then head:= hd_ARR
       else if get_poz(stat)<=poz_COORDINATED then
            begin
              if         (cnst_cnl=stat)        then head:= hd_CNL
              else if pos(cnst_dla,stat)>0      then head:= hd_DLA
              {este nie je - else if _zmeneny or (pos(cnst_chg,stat)>0) then head:= hd_CHG}
              else if pos(cnst_sended,stat)>0   then head:= hd_FPL
            end;

       fdp_co_ordinate_procedure (src,dst, spr_FPLM,head, zmeneny,FPL^);
      {$ENDIF}
     end;


{ --------------
   NET+EXT
  --------------
}
 function _odosli_mFPL_ (FPL: PDmFPL): bool;
    var   krl: bool;
    begin
      _odosli_mFPL_:= false;

      krl:= is_KRL(FPL);

      {$IFDEF PROCESS_FPLM}
        if pos(cnst_disk,FPL^.stat)<>0 then
           begin
             FPL^.stat:= cnst_sended;
             save_mFPL(FPL);
             if not krl then add_FPLm(FPL)
           end;
      {$ENDIF}

      if krl then
         begin
          {$IFDEF KRL} _odosli_mFPL_:= _odosli_KRL(FPL); {$ENDIF}
         end
      else begin
             _odosli_mFPL_:= distribute_mFPL(FPL,[],[]);
           end;
    end;

 function _odosli_mFPL (FPL: PDmFPL; _src: fdp_src): bool;
    begin
      _odosli_mFPL:= false;
      _odosli_mFPL_ (FPL);
      if not is_KRL(FPL) then coordinate_FPLM (FPL,_src,[],false,true);
    end;

 procedure odosli_mFPL (FPL: PDmFPL);
    begin
      _odosli_mFPL(FPL,letvis);
    end;
