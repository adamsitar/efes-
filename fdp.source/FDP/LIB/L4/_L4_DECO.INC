(*function O_L4444.decode_header (data: pchars; size: word;
                                zac,kon: word;
                                var header: string;
                                var res: string;
                                decode: bool
                               ): bool;
   var   bres : bool;
         head, s : string;
   begin
     decode_header:= false;
     if     inherited decode_header (data,size,zac,kon,header,res, decode)
        and decode_head (header, head, res) then
        begin
         (*{$IFDEF FPL4}
          if decode then
             begin
               if (head=hd_PPL) and (not _FPL4_PPL_ENABLE) then
                  begin
                    l4_err(a_ICAO,hd_PPL, 0,1, s);
                    if icao_DIS_ERR then res:= s
                    else writeln_pkt(nil,0,arch_SYS,s,cl_SYS,false,true)
                  end;
             end;
         {$ENDIF}
          decode_header:= res=''
        end
   end;
*)

function O_L4444.enabled_head (src: TPKT_SRC;
                               data: pchars; size: word;
                               head: string;
                               var res: string
                              ): bool;
   var   bres: bool;
   begin
     bres:= inherited enabled_head (src, data,size, head,res);
     {$IFDEF PROCESS_FPL4}
       if bres then
          begin
            if (head=hd_PPL) and (not _FPL4_PPL_ENABLE) then res:= hd_PPL
            else if (head=hd_CHG) and (not _FPL4_CHG_ENABLE) then res:= hd_CHG
            else if (head=hd_DLA) and (not _FPL4_DLA_ENABLE) then res:= hd_DLA
            else if (head=hd_DEP) and (not _FPL4_DEP_ENABLE) then res:= hd_DEP
            else if (head=hd_ARR) and (not _FPL4_ARR_ENABLE) then res:= hd_ARR;
            bres:= res='';
            if not bres then l4_err(a_ICAO,res,0,err_ICAO_neznama_sprava, res)
          end;
     {$ENDIF}
     enabled_head:= bres
   end;

