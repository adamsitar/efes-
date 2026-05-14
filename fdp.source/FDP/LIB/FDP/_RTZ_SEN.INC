{ -------------------------- }
{ send                       }
{ -------------------------- }

function send2node_RTZ(RTZ: PRTZ; nd: int): bool; far;
   begin
     send2node_RTZ:= true
   end;

function send_RTZ(RTZ: PRTZ; adr: TNETadr; wait: bool): bool;
   var   kod  : word;
         p_code : pointer;
   begin
     kod:= spr_RTZ;
     p_code:= @code_RTZ;
     send_RTZ:= NETres(NETsend_data
                  (adr, kod,
                   RTZ,p_code,@codekey_RTZ,@RTZ^.rec,
                   true,inf_RTZ,@send2node_RTZ,
                   wait,false,net_flag_NIL)
                  )
   end;


function  distribute_RTZ(RTZ: PRTZ; sw: Tnd_sw_set; nd: Tnd_nd_set): bool;
   var    res : bool;
   begin
     res:= NETdistribute_data
                  (
                   [FDP,RDP,MON],sw,[MASTER,SLAVE],
                   spr_RTZ, RTZ,@code_RTZ,@codekey_RTZ,@RTZ^.rec,
                   true,inf_RTZ,@send2node_RTZ,false,false,net_flag_NIL
                  );
   end;


function _odosli_RTZ(RTZ: PRTZ; _src: fdp_src): bool;
   begin
     {$IFDEF PROCESS_RTZ}
      if __is_stat(RTZ^.stat,cnst_disk) then with RTZ^ do
         begin
           stat:= cnst_sended;
           save_RTZ(RTZ);
           add_RTZ(RTZ)
         end;
     {$ENDIF}
     _odosli_RTZ:= distribute_RTZ(RTZ,[],[])
     {coordinate_RTZ (RTZ, _src,[],false,true);}
   end;

procedure odosli_RTZ(RTZ: PRTZ);
    begin
      _odosli_RTZ(RTZ,letvis)
    end;