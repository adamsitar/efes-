{ -------------------
   NET - distribucia
  -------------------
}

 function send2node_PRS(PRS: PPRS; nd: int): bool;
    begin
      send2node_PRS:=   true
                       {$IFDEF SEND_2_NODE_PRS}
                        {$IFDEF LK}
                          and (   (strpos(NODEs^[nd].desc.inf,nd_PVO)<>nil)
                               or (_decode_stav(PRS^.stat) in [_aktivovany.._zruseny])
                              )
                        {$ENDIF}
                       {$ENDIF}
    end;

 function send_PRS(PRS: PPRS; adr: TNETadr; wait: bool): bool;
    var   kod  : word;
          p_code : pointer;
    begin
      kod:= spr_PRS;
      p_code:= @code_PRS;
     {$IFDEF DATA_BIN}
      case NETtype(adr) of
        FDP0 : begin
                 kod := spr0_PRS;
                 p_code:= @code0_PRS
               end;
       {$IFDEF RDP}
        RDP0 : begin
                 kod := spr0_RDP_PRS;
                 p_code:= @code0_PRS_RDP
               end;
        FDP0NX,RDP0NX :
               begin
                 kod := spr0_RDPNX_PRS;
                 p_code:= @code0NX_PRS_RDP
               end
       {$ENDIF}
      end;
     {$ENDIF}
      send_PRS:= NETres(NETsend_data
                   (adr, kod,
                    PRS,p_code,@codekey_PRS,@PRS^.rec,
                    true,inf_PRS,{nil}@send2node_PRS,
                    wait,false,net_flag_NIL)
                   )
    end;


 function  distribute_PRS (PRS: PPRS; sw: Tnd_sw_set; nd: Tnd_nd_set): bool;
    var    res : bool;
    begin
      res:= true;
      {$IFDEF DATA_BIN}
       res:= NETdistribute_data
                    (
                     [FDP0],sw,[MASTER,SLAVE],
                     spr0_PRS, PRS,@code0_PRS,@codekey_PRS,@PRS^.rec,
                     true,inf_PRS,{nil}@send2node_PRS,false,false,net_flag_NIL
                    );
      {$ENDIF}
      {$IFDEF RDP}
       res:= NETdistribute_data
                    (
                     [FDP0NX],[],[MASTER,SLAVE],
                     spr0_RDPNX_PRS, PRS,@code0NX_PRS_RDP,@codekey_PRS,@PRS^.rec,
                     true,inf_PRS,{nil}@send2node_PRS,false,false,net_flag_NIL
                    ) and res;
      {$ENDIF}
      res:= NETdistribute_data
                   (
                    [FDP],sw,[MASTER,SLAVE],
                    spr_PRS, PRS,@code_PRS,@codekey_PRS,@PRS^.rec,
                    true,inf_PRS,{nil}@send2node_PRS,false,false,net_flag_NIL
                   ) and res;

      distribute_PRS:= res
    end;


 function  distribute_rdp_PRS (PRS: PPRS; add: pbool): bool;
    var    res, est : bool;
           stt : string;
    begin
      res:= true;

      if add<>nil then est:= add^
      else est:= est_PRS(PRS);

      {$IFDEF RDP}
       if est then
         begin
          {$IFDEF ARCHIVE_DAR}
            DAR_arch.save_FDP(spr_PRS,PRS, @code_PRS);
          {$ENDIF}

          {$IFDEF DATA_BIN}
            res:= NETdistribute_data
                         (
                          [RDP0],[],[SLAVE],
                          spr0_RDP_PRS, PRS,@code0_PRS_RDP,@codekey_PRS,@PRS^.rec,
                          true,inf_PRS,{nil}@send2node_PRS,false,false,net_flag_NIL
                         ) and res;
            res:= NETdistribute_data
                         (
                          [RDP0NX],[],[SLAVE],
                          spr0_RDPNX_PRS, PRS,@code0NX_PRS_RDP,@codekey_PRS,@PRS^.rec,
                          true,inf_PRS,{nil}@send2node_PRS,false,false,net_flag_NIL
                         ) and res;
          {$ENDIF}

           res:= NETdistribute_data
                        (
                         [RDP,MON],[],[MASTER,SLAVE],
                         spr_PRS, PRS,@code_PRS,@codekey_PRS,@PRS^.rec,
                         true,inf_PRS,{nil}@send2node_PRS,false,false,net_flag_NIL
                        ) and res;

         end
       else begin
              stt:= PRS^.stat; PRS^.stat:= cnst_cnl;
              res:= NETdistribute_data
                        ([RDP0],[],[],
                         spr0_RDP_PRS_DEL, PRS,@code0_PRS_mess,@codekey_PRS,nil,
                         true,inf_PRS,{nil}@send2node_PRS,false,false,net_flag_SEND
                        );
              res:= NETdistribute_data
                           (
                            [RDP0NX],[],[SLAVE],
                            spr0_RDPNX_PRS, PRS,@code0NX_PRS_RDP,@codekey_PRS,@PRS^.rec,
                            true,inf_PRS,{nil}@send2node_PRS,false,false,net_flag_NIL
                           ) and res;
              res:= NETdistribute_data
                        ([RDP,MON],[],[],
                         spr_PRS_CNL, PRS,@code_PRS_mess,@codekey_PRS,nil,
                         true,inf_PRS,{nil}@send2node_PRS,false,false,net_flag_SEND
                        ) and res;
              PRS^.stat:= stt;
            end;
      {$ENDIF}

      distribute_rdp_PRS:= res;
    end;


 procedure message_PRS (PRS: PPRS; kod: word; adr: TNETadr);
     var   p_code : pointer;
           pkod   : word;
     begin
       pkod:= kod;
       p_code:= @code_PRS_mess;
       {$IFDEF DATA_BIN} {$IFDEF RDP}
         if NETtype(adr) in [RDP0] then
            begin
              pkod:= code_0type(kod);
              p_code:= @code0_PRS_mess
            end;
       {$ENDIF} {$ENDIF}

       {$IFDEF ARCHIVE_DAR}
         DAR_arch.save_FDP(pkod,PRS, p_code);
       {$ENDIF}

       if cut_(adr)<>'' then
          begin
            NETsend_data(adr,
                         pkod, PRS,p_code,@codekey_PRS,nil,
                         true,inf_PRS,{nil}@send2node_PRS, false,false, net_flag_SEND
                        )
          end
       else begin
             {$IFDEF RDP}
              NETdistribute_data
                     ([RDP0],[],[],
                      code_0type(kod), PRS,@code0_PRS_mess,@codekey_PRS,nil,
                      true,inf_PRS,{nil}@send2node_PRS,false,false,net_flag_SEND
                     );
             {$ENDIF}
              NETdistribute_data
                     ([FDP,FDP0,FDP0NX,RDP,RDP0NX],[],[],
                      kod, PRS,@code_PRS_mess,@codekey_PRS,nil,
                      true,inf_PRS,{nil}@send2node_PRS,false,false,net_flag_SEND
                     );
            end;
     end;


{ -------------------
   EXT - koordinacia
  -------------------
}
 procedure coordinate_PRS (PRS: PPRS;
                           src: fdp_src; dst: set_fdp_src;
                           zmena, zmeneny: bool
                          );
     var   head: Thead_ICAO;
     begin
      {$IFDEF EXTERNAL_NET}
      { Toto spomali if zmena then zmeneny:= zmeneny_PRS(PRS,false);}
       head:= hd_PRS;
       fdp_co_ordinate_procedure (src,dst, spr_PRS, head, zmeneny,PRS^);
      {$ENDIF}
     end;


{ --------------
   NET+EXT
  --------------
}
 function _odosli_PRS (PRS: PPRS; _src: fdp_src{; db: PDB; pos: int}): bool;
    begin
      {$IFDEF PROCESS_PRS}
        if __is_stat(PRS^.stat,cnst_disk{+cnst_prop}) then with PRS^ do
           begin
             {$IFDEF FUA} {$IFNDEF AMC}
              { kontrola na limit casu odoslania...
                if not plan_pred_poslednym_schvalenim (PRS) then Exit;
              }
             {$ENDIF} {$ENDIF}

             stat:= cnst_sended;
             {save_PRS(PRS);
             add_PRS(PRS)}
           end;
      {$ENDIF}

      coordinate_PRS (PRS, _src,[],true,true);
      _odosli_PRS:= distribute_PRS(PRS,[],[]);
    end;

{
 procedure odosli_PRS(PRS: PPRS);
     begin
       _odosli_PRS(PRS,letvis)
     end;
}