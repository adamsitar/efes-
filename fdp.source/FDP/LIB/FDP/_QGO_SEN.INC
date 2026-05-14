{ -------------------------- }
{ send                       }
{ -------------------------- }

function send2node_QGO(QGO: PQGO; nd: int): bool; far;
   begin
     {IFDEF FDP_OPL
       send2node_QGO:= NODEs^[nd].desc.sw in set_nd_OPL
     ELSE}
       send2node_QGO:= true
     {ENDIF}
   end;

function send_QGO(QGO: PQGO; adr: TNETadr; wait: bool): bool;
   var   kod  : word;
         p_code : pointer;
   begin
     kod:= spr_QGO;
     p_code:= @code_QGO;
    {$IFDEF DATA_BIN}
     if NETtype(adr)=FDP0 then
        begin
          kod:= spr0_QGO;
          p_code:= @code0_QGO
        end;
    {$ENDIF}
     send_QGO:= NETres(NETsend_data
                  (adr, kod,
                   QGO,p_code,@codekey_QGO,@QGO^.rec,
                   true,inf_QGO,@send2node_QGO,
                   wait,false,net_flag_NIL)
                  )
   end;


function  distribute_QGO(QGO: PQGO; sw: Tnd_sw_set; nd: Tnd_nd_set): bool;
   var    res : bool;
   begin
    {$IFDEF ARCHIVE_DAR}
      DAR_arch.save_FDP(spr_QGO, QGO, @code_QGO);
    {$ENDIF}

    {$IFDEF DATA_BIN}
     res:= NETdistribute_data
                  (
                   [FDP0],sw,[MASTER,SLAVE],
                   spr0_QGO, QGO,@code0_QGO,@codekey_QGO,@QGO^.rec,
                   true,inf_QGO,@send2node_QGO,false,false,net_flag_NIL
                  );
    {$ENDIF}

     res:= NETdistribute_data
                  (
                   [FDP,RDP,MON],sw,[MASTER,SLAVE],
                   spr_QGO, QGO,@code_QGO,@codekey_QGO,@QGO^.rec,
                   true,inf_QGO,@send2node_QGO,false,false,net_flag_NIL
                  ) and res;

     distribute_QGO:= res
   end;


function _odosli_QGO(QGO: PQGO; _src: fdp_src): bool;
   begin
     {$IFDEF PROCESS_QGO}
      if __is_stat(QGO^.stat,cnst_disk) then with QGO^ do
         begin
           stat:= cnst_sended;
           save_QGO(QGO);
           add_QGO(QGO)
         end;
     {$ENDIF}
     _odosli_QGO:= distribute_QGO(QGO,[],[])
     {coordinate_PRS (PRS, _src,[],false,true);}
   end;

procedure odosli_QGO(QGO: PQGO);
    begin
      _odosli_QGO(QGO,letvis)
    end;