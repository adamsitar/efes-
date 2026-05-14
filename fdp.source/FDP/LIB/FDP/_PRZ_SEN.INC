{ -------------------------- }
{ send                       }
{ -------------------------- }

 function send_PRZ(PRZ: PPRZ; adr: TNETadr; wait: bool): bool;
    var   kod  : word;
          p_code : pointer;
    begin
      kod:= spr_PRZ;
      p_code:= @code_PRZ;
     {$IFDEF DATA_BIN}
      case NETtype(adr) of
        FDP0,FDP0NX :
          begin
            kod := spr0_PRZ;
            p_code:= @code0_PRZ
          end;
      end;
     {$ENDIF}
      send_PRZ:= NETres(NETsend_data
                   (adr, kod,
                    PRZ, p_code,@codekey_PRZ,@PRZ^.rec,
                    true,inf_PRZ,nil,
                    wait,false, net_flag_NIL
                   ))
    end;


 function  distribute_PRZ (PRZ: PPRZ; sw: Tnd_sw_set; nd: Tnd_nd_set): bool;
    var    res : bool;
    begin
      {$IFDEF ARCHIVE_DAR}
       DAR_arch.save_FDP(typ, PRZ, @code_PRZ);
      {$ENDIF}

      res:= NETdistribute_data
                   (
                    [FDP,MON],sw,[MASTER,SLAVE],
                    spr_PRZ, PRZ,@code_PRZ,@codekey_PRZ,@PRZ^.rec,
                    true,inf_PRZ,nil,false,false,net_flag_NIL
                   );

      res:= NETdistribute_data
                   (
                    [FDP0,FDP0NX],sw,[MASTER,SLAVE],
                    spr0_PRZ, PRZ,@code0_PRZ,@codekey_PRZ,@PRZ^.rec,
                    true,inf_PRZ,nil,false,false,net_flag_NIL
                   );

      distribute_PRZ:= res
    end;


 function  _odosli_PRZ (PRZ: PPRZ; _src: fdp_src): bool;
     begin
      {$IFDEF PRZ_REQUEST}
       if __is_stat(PRZ^.stt,cnst_disk) then
          begin
            PRZ^.stt:= cnst_sended;
            save_PRZ(PRZ)
          end;
      {$ENDIF}
       distribute_PRZ (PRZ,[],[])
       {coordinate_PRZ (PRZ,_src,[],false,true);}
     end;

 procedure odosli_PRZ(PRZ: PPRZ);
     begin
       _odosli_PRZ(PRZ,letvis)
     end;


 procedure _pkt_PRZ(PRZ: PPRZ);
     begin
       save_PRZ (PRZ);
       distribute_PRZ (PRZ,[],[])
     end;


 procedure _ack_PRZ(key: string; rec: Tplan_rec; fdp: bool; nd: int);
     var   PRZ : TPRZ;
     begin
       if read_PRZ(key, @PRZ)<>-1 then
          begin
            if NET_ACK_ALL then
               begin
                 rec_copy (rec,PRZ.rec);
               end
            else begin
                   rec_pkt(nd,PRZ.rec,is_ack);
                 end;
            save_PRZ(@PRZ);
            disp_PRZ(@PRZ)
          end
     end;
