function icao_head_type (head: string; var res: string;
                         p_heads : Pheads_ICAO; heads : word
                        ): int;
   var   i : int;
   begin
     res:= '';
     icao_head_type:= -1;
     if (p_heads=nil) or (heads=0) then Exit;
     head:= mtks_rus_to_lat(copy(head,1,kod_HEAD));
     i:= 0; while (i < heads) and (head <> p_heads^[i]) do inc(i);
     if i < heads then icao_head_type:= i
     else l4_err(a_ICAO,'',0,err_ICAO_neznama_sprava, res)
   end;

function in_icao_head (head: string; iset: set_msICAO; var unkn: bool): bool;
   var   i : int;
         r : string;
   begin
     head:= copy(head,1,kod_HEAD);
     i:= icao_head_type(head, r, @hd_ICAO,sizeof(hd_ICAO) div sizeof(Thead_ICAO));
     unkn:= i<0;
     in_icao_head:= (not unkn) and (ms_ICAO(i) in iset);
   end;
