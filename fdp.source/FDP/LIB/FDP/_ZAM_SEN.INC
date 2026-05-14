{ -------------------
   NET - distribucia
  -------------------
}

 function send2node_ZAM(ZAM: PZAM; nd: int): bool; far;
    begin
      send2node_ZAM:= send2node(ZAM^.stat,nd)
    end;


 function send_ZAM(ZAM: PZAM; adr: TNETadr; wait: bool): bool;
    var   kod  : word;
          p_code : pointer;
    begin
      kod:= spr_ZAM;
      p_code:= @code_ZAM;
     {$IFDEF DATA_BIN}
      if NETtype(adr)=FDP0 then
         begin
           kod:= spr0_ZAM;
           p_code:= @code0_ZAM
         end;
     {$ENDIF}
      send_ZAM:= NETres(NETsend_data
                   (adr, kod,
                    ZAM,p_code,@codekey_ZAM,@ZAM^.rec,
                    true,inf_ZAM,@send2node_ZAM,
                    wait,false,net_flag_NIL)
                   )
    end;


 function  distribute_ZAM(ZAM: PZAM; sw: Tnd_sw_set; nd: Tnd_nd_set): bool;
    var    res : bool;
    begin
     {$IFDEF DATA_BIN}
      res:= NETdistribute_data
                   (
                    [FDP0],sw,[MASTER,SLAVE],
                    spr0_ZAM, ZAM,@code0_ZAM,@codekey_ZAM,@ZAM^.rec,
                    true,inf_ZAM,@send2node_ZAM,false,false,net_flag_NIL
                   );
     {$ENDIF}

      res:= NETdistribute_data
                   (
                    [FDP],sw,[MASTER,SLAVE],
                    spr_ZAM, ZAM,@code_ZAM,@codekey_ZAM,@ZAM^.rec,
                    true,inf_ZAM,@send2node_ZAM,false,false,net_flag_NIL
                   ) and res;

      distribute_ZAM:= res
    end;


 function  distribute_rdp_ZAM (ZAM: PZAM; add: pbool): bool;
    var    res, est : bool;
           stt : string;
    begin
      res:= true;

      if add<>nil then est:= add^
      else est:= est_ZAM(ZAM);

      {$IFDEF RDP}
       if est then
         begin
          {$IFDEF ARCHIVE_DAR}
            DAR_arch.save_FDP(spr_ZAM,ZAM, @code_ZAM);
          {$ENDIF}

           res:= NETdistribute_data
                        (
                         [RDP,MON],[],[MASTER,SLAVE],
                         spr_ZAM, ZAM,@code_ZAM,@codekey_ZAM,@ZAM^.rec,
                         true,inf_ZAM,@send2node_ZAM,false,false,net_flag_NIL
                        ) and res;

         end
       else begin
              stt:= ZAM^.stat; ZAM^.stat:= cnst_cnl;
              res:= NETdistribute_data
                        ([RDP,MON],[],[],
                         spr_ZAM_CNL, ZAM,@code_ZAM_mess,@codekey_ZAM,nil,
                         true,inf_ZAM,nil,false,false,net_flag_SEND
                        ) and res;
              ZAM^.stat:= stt
            end;
      {$ENDIF}

      distribute_rdp_ZAM:= res;
    end;


   procedure message_ZAM (ZAM: PZAM; kod: word; adr: TNETadr);
       begin
         {$IFDEF ARCHIVE_DAR}
           DAR_arch.save_FDP(kod, ZAM, @code_ZAM);
         {$ENDIF}

         if cut_(adr)<>'' then
            NETsend_data(adr,
                         kod, ZAM,@code_ZAM_mess,@codekey_ZAM,nil,
                         true,inf_ZAM,nil, false,false, net_flag_SEND
                        )
         else NETdistribute_data
                        ([RDP],[],[],
                         kod, ZAM,@code_ZAM_mess,@codekey_ZAM,nil,
                         true,inf_ZAM,nil, false,false,net_flag_SEND
                        )
       end;


{ -------------------
   EXT - koordinacia
  -------------------
}
 procedure coordinate_ZAM (ZAM: PZAM;
                           src: fdp_src; dst: set_fdp_src;
                           zmena, zmeneny: bool
                          );
     var   head: Thead_ICAO;
     begin
      {$IFDEF EXTERNAL_NET}
       {if zmena then zmeneny:= zmeneny_ZAM(ZAM,false);
       head:= hd_ZAM;
       fdp_co_ordinate_procedure (src,dst, spr_ZAM, head, zmeneny,ZAM^);}
      {$ENDIF}
     end;



{ --------------
   NET+EXT
  --------------
}
 function _odosli_ZAM(ZAM: PZAM; _src: fdp_src): bool;
    begin
      {$IFDEF PROCESS_ZAM}
       if __is_stat(ZAM^.stat,cnst_disk) then with ZAM^ do
          begin
            stat:= cnst_sended;
            save_ZAM(ZAM);
            add_ZAM(ZAM)
          end;
      {$ENDIF}
      _odosli_ZAM:= distribute_ZAM(ZAM,[],[]);
      coordinate_ZAM (ZAM, _src,[],false,true);
    end;

 procedure odosli_ZAM(ZAM: PZAM);
     begin
       _odosli_ZAM(ZAM,letvis)
     end;


