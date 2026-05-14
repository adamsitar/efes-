
{ -------------------------- }
{ NTM                        }
{ -------------------------- }

 function send_PRN(PRN: PPRN; adr: TNETadr; wait: bool): bool;
    var   kod  : word;
          p_code : pointer;
    begin
      kod:= spr_PRN;
      p_code:= @code_PRN;
     {$IFDEF DATA_BIN}
      case NETtype(adr) of
        FDP0,FDP0NX :
          begin
            kod := spr0_PRN;
            p_code:= @code0_PRN
          end;
      end;
     {$ENDIF}
      send_PRN:= NETres(NETsend_data
                   (adr, kod,
                    PRN, p_code,@codekey_PRN,@PRN^.rec,
                    true,inf_PRN,nil,
                    wait,false, net_flag_NIL
                   ))
    end;


 function  distribute_PRN (PRN: PPRN; sw: Tnd_sw_set; nd: Tnd_nd_set): bool;
    var    res : bool;
    begin
      {$IFDEF ARCHIVE_DAR}
       DAR_arch.save_FDP(typ, PRN, @code_PRN);
      {$ENDIF}

      res:= NETdistribute_data
                   (
                    [FDP,MON],sw,[MASTER,SLAVE],
                    spr_PRN, PRN,@code_PRN,@codekey_PRN,@PRN^.rec,
                    true,inf_PRN,nil,false,false,net_flag_NIL
                   );

      res:= NETdistribute_data
                   (
                    [FDP0,FDP0NX],sw,[MASTER,SLAVE],
                    spr0_PRN, PRN,@code0_PRN,@codekey_PRN,@PRN^.rec,
                    true,inf_PRN,nil,false,false,net_flag_NIL
                   );

      distribute_PRN:= res
    end;


 procedure _pkt_PRN (PRN: PPRN);
     begin
       format_PRN (PRN);
       save_PRN (PRN);
       distribute_PRN (PRN, [],[]);
     end;


 procedure _ack_PRN(key: string; rec: Tplan_rec; fdp: bool; nd: int);
     var   PRN : TPRN;
     begin
       if read_PRN(key, @PRN)<>-1 then
          begin
            if NET_ACK_ALL then
               begin
                 rec_copy (rec, PRN.rec);
               end
            else begin
                   rec_pkt(nd,PRN.rec,is_ack);
                 end;
            save_PRN(@PRN);
            disp_PRN(@PRN)
          end
     end;
