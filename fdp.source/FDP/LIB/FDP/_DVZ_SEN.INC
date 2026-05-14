{ -------------------------- }
{ send                       }
{ -------------------------- }

 function send2node_DVZ(DVZ: PDVZ; nd: int): bool; far;
    begin
      (*{$IFDEF FDP_OPL}
         send2node_DVZ:=    {(     (NODEs^[nd].desc.sw in set_nd_EST)
                               and _is_stat(DVZ^.stat,cnst_ACT_plan,false)
                             )
                          or} (NODEs^[nd].desc.sw in set_nd_FDP)
      {$ELSE}*)
      send2node_DVZ:= true
    end;

 function sendw_DVZ(DVZ: PDVZ; adr: TNETadr; wait,msg: bool): bool;
    var   kod  : word;
          p_code : pointer;
    begin
      if NETtype(adr)=FDP0 then
         begin
           kod:= spr0_DVZ;
           p_code:= @code0_DVZ
         end
      else begin
             kod:= spr_DVZ;
             p_code:= @code_DVZ
           end;
      sendw_DVZ:= NETres(NETsend_data
                   (adr, kod,
                    DVZ,p_code,@codekey_DVZ,@DVZ^.rec,
                    true,inf_DVZ,@send2node_DVZ,
                    wait,msg,net_flag_NIL)
                   )
    end;

 function send_DVZ(DVZ: PDVZ; adr: TNETadr; wait: bool): bool;
    begin
      send_DVZ:= sendw_DVZ(DVZ,adr, wait,false)
    end;


 function  distribute_DVZ(DVZ: PDVZ; sw: Tnd_sw_set; nd: Tnd_nd_set): bool;
    var    res : bool;
    begin
     {$IFDEF ARCHIVE_DAR}
       {DAR_arch.save_FDP(spr_DVZ, DVZ, @code_DVZ);}
     {$ENDIF}

     {$IFDEF DATA_BIN}
      res:= NETdistribute_data
                   (
                    [FDP0],sw,[MASTER,SLAVE],
                    spr0_DVZ, DVZ,@code0_DVZ,@codekey_DVZ,@DVZ^.rec,
                    true,inf_DVZ,@send2node_DVZ,false,false,net_flag_NIL
                   );
     {$ENDIF}

      res:= NETdistribute_data
                   (
                    [FDP,RDP,MON],sw,[MASTER,SLAVE],
                    spr_DVZ, DVZ,@code_DVZ,@codekey_DVZ,@DVZ^.rec,
                    true,inf_DVZ,@send2node_DVZ,false,false,net_flag_NIL
                   ) and res;

      distribute_DVZ:= res
    end;



 function _odosli_DVZ (DVZ: PDVZ; _src: fdp_src): bool; far;
    var   adr : TNETadr;
          r   : TPlanRec;
          nd  : int;
          res : bool;
    begin
      {$IFDEF PROCESS_DVZ}
        if _plan_pre(DVZ^.pre) then
           begin
             adr:= adr_airbase(DVZ^.kym);
             if (pos(cnst_disk,DVZ^.stat)<>0) then
                begin
                  DVZ^.stat:= cnst_prop;
                  save_DVZ(DVZ)
                end
           end
        else adr:= adr_airbase(DVZ^.pre);
        _INFO_NET_RES:= true;
        res:= sendw_DVZ(DVZ,adr,true,true);
        nd:= is_NETadr(adr);
        if nd>-1 then begin r:= DVZ^.rec[nd]; DVZ^.rec[nd]:= no_send end;
      {$ELSE}
        nd:= -1; res:= true;
      {$ENDIF}

      _odosli_DVZ:= distribute_DVZ(DVZ,[],[]) and res;
      if (nd>-1) and (DVZ^.rec[nd]=no_send) then DVZ^.rec[nd]:= r;
      {coordinate_DVZ (DVZ, _src,[],false,true);}
    end;


 procedure odosli_DVZ(DVZ: PDVZ); far;
     begin
       _odosli_DVZ(DVZ,letvis)
     end;

