{ -------------------
   NET - distribucia
  -------------------
}

 function send_cFPL(FPL: PDcFPL; adr: TNETadr; wait: bool): bool;
    var   kod    : TNETtyp;
          p_code : pointer;
    begin
      send_cFPL:= true;
      if     ((NETtype(adr) in [RDP0,RDP0NX,RDP]))
         and (FPL^.stt=hd_CPL)
         and (not FPLC_CPL) then Exit;

      kod:= spr_FPLC;
      p_code:= @code_FPLC;
     {$IFDEF DATA_BIN}
      case NETtype(adr) of
        FDP0,FDP0NX :
               begin
                 kod:= spr0_cFPL;
                 p_code:= @code0_cFPL
               end;
        RDP0,RDP0NX :
               begin
                 kod:= spr0_RDP_cFPL;
                 p_code:= @code0_cFPL_RDP
               end
      end;
     {$ENDIF}
      send_cFPL:= NETres(NETsend_data
                     (adr,
                      kod, FPL,p_code,@codekey_FPLC,@FPL^.rec,
                      true,inf_FPLC,nil, wait,false, net_flag_NIL
                     ))
    end;



 function  distribute_cFPL(FPL: PDcFPL; sw: Tnd_sw_set; nd: Tnd_nd_set): bool;
    var    res : bool;
    begin
     distribute_cFPL:= false;

     res:= true;
     {$IFDEF DATA_BIN}
      res:= NETdistribute_data
                   (
                    [FDP0,FDP0NX],sw,[MASTER,SLAVE],
                    spr0_cFPL, FPL,@code0_cFPL,@codekey_FPLC,@FPL^.rec,
                    true,inf_FPLC,nil,false,false,net_flag_NIL
                   );
     {$ENDIF}
     res:= NETdistribute_data
                  (
                   [FDP],sw,[MASTER,SLAVE],
                   spr_FPLC, FPL,@code_FPLC,@codekey_FPLC,@FPL^.rec,
                   true,inf_FPLC,nil,false,false,net_flag_NIL
                  ) and res;

     distribute_cFPL:= res
   end;


 function  distribute_rdp_cFPL (FPL: PDcFPL; add: pbool): bool;
    var    res, est : bool;
           stt : string;
    begin
      res:= true;

      {if (FPL^.stt=hd_CPL) and (not FPLC_CPL) then Exit; }

      if add<>nil then est:= add^
      else est:= est_cFPL(FPL);

      {$IFDEF RDP}
       if est then
         begin
          {$IFDEF ARCHIVE_DAR}
           {$IFDEF DATA_BIN} DAR_arch.save_FDP(spr0_RDP_cFPL, FPL, @code0_cFPL_RDP);
           {$ENDIF}          DAR_arch.save_FDP(spr_FPLC, FPL, @code_FPLC);
          {$ENDIF}

          {$IFDEF DATA_BIN}
            res:= NETdistribute_data
                         (
                          [RDP0,RDP0NX],[],[SLAVE],
                          spr0_RDP_cFPL, FPL,@code0_cFPL_RDP,@codekey_FPLC,@FPL^.rec,
                          true,inf_FPLC,nil,false,false,net_flag_NIL
                         ) and res;
          {$ENDIF}
           res:= NETdistribute_data
                        (
                         [RDP],[],[SLAVE],
                         spr_FPLC, FPL,@code_FPLC,@codekey_FPLC,@FPL^.rec,
                         true,inf_FPLC,nil,false,false,net_flag_NIL
                        ) and res;
         end
       else begin
              stt:= FPL^.stt; FPL^.stt:= cnst_cnl;
              res:= NETdistribute_data
                        ([RDP0,RDP0NX],[],[],
                         spr0_RDP_EST_DEL, FPL,@code0_cFPL_mess,@codekey_FPLC,nil,
                         true,inf_FPLC,nil,false,false,net_flag_SEND
                        );
              res:= NETdistribute_data
                        ([RDP,MON],[],[],
                         spr_EST_CNL, FPL,@code_FPLC_mess,@codekey_FPLC,nil,
                         true,inf_FPLC,nil,false,false,net_flag_SEND
                        ) and res;
              FPL^.stt:= stt
            end;
      {$ENDIF}

      distribute_rdp_cFPL:= res;
    end;


 procedure message_cFPL (FPL: PDcFPL; kod: word; adr: TNETadr);
     var   p_code : pointer;
           pkod   : word;
     begin
        pkod:= kod;
        p_code:= @code_FPLC_mess;
        {$IFDEF DATA_BIN}
          if NETtype(adr) in [FDP0,FDP0NX,RDP0,RDP0NX] then
             begin
               pkod:= code_0type(kod);
               p_code:= @code0_cFPL_mess
             end;
        {$ENDIF}

        {$IFDEF ARCHIVE_DAR}
          DAR_arch.save_FDP(pkod,FPL, p_code);
        {$ENDIF}

        if cut_(adr)<>'' then
           begin
             NETsend_data(adr,
                          pkod, FPL,p_code,@codekey_FPLC,nil,
                          true,inf_FPLC,nil, false,false, net_flag_SEND
                         )
           end
        else begin
              {$IFDEF DATA_BIN}
               NETdistribute_data
                      ([RDP0,RDP0NX],[],[],
                       code_0type(kod), FPL,@code0_cFPL_mess,@codekey_FPLC,nil,
                       true,inf_FPLC,nil,false,false,net_flag_SEND
                      );
              {$ENDIF}
               NETdistribute_data
                      ([RDP],[],[],
                       kod, FPL,@code_FPLC_mess,@codekey_FPLC,nil,
                       true,inf_FPLC,nil,false,false,net_flag_SEND
                      );
             end;
     end;


{ -------------------
   EXT - koordinacia
  -------------------
}
 procedure coordinate_FPLc(FPL: PDcFPL;
                           src: fdp_src; dst: set_fdp_src;
                           zmena, zmeneny: bool
                          );
     var   head: Thead_ICAO;
           stat: string;
     begin
      {$IFDEF EXTERNAL_NET}
       {if zmena then zmeneny:= zmeneny_FPLc(FPL,false);}
       head:= FPL^.stt;
       fdp_co_ordinate_procedure (src,dst, spr_FPLc, head, zmeneny, FPL^);
      {$ENDIF}
     end;


{ --------------
   NET+EXT
  --------------
}
 function _odosli_FPLc (FPL: PDcFPL; _src: fdp_src; _nd: Tnd_nd_set): bool;
    begin
      _odosli_FPLc:= distribute_cFPL(FPL,[],_nd);
      coordinate_FPLc (FPL, _src,[],false,true);
    end;

 procedure odosli_FPL(FPL: PDcFPL);
     begin
       _odosli_FPLc(FPL,letvis,[])
     end;
