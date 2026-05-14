 function O_L4_FDP._decode_LAM  (data: pchars; size: word;
                                 var header: string;
                                 var lam,ods,key: string;
                                 var typ: TNETtyp;
                                 var res: string
                                ): bool;
     var   bres: bool;
     var   head,adr,cislo,header_data : string;
           ires : int;
     begin
       _decode_LAM:= false; lam:= ''; ods:= ''; key:= ''; typ:= 0;
       ires:= _icao_head_type(header,res);
       if (ires>=0) and (p_heads_EXT^[ires]=hd_LAM) then
          if _decode_header (header, head,adr,ods,cislo, header_data, @res) then
             if (NODE_THIS='') or (adr=NODE_THIS) then
                begin
                  prijaty_LAM (header_data,ods, key,typ);
                  _decode_LAM:= true
                end
             else res:= err_ext_received_address
          else res:= err_ext_lam_data
      {bres:= inherited _decode_LAM (data,size, header,lam,ods,key,typ, res);
      _decode_LAM:= bres;
      if not bres then Exit;}
    end;

 procedure O_L4_FDP.neprijaty_LAM(id,adr,head,key: string; var res: string);
     begin
       inherited neprijaty_LAM(id,adr,head,key,res);
       if (not _nolam_fda) or (FDAaddress='') then Exit;
       if res<>'' then
          begin
            if res[length(res)]<>NULL then res:= res+NULL;
            NETsend_err (FDAaddress,level_USER,false,@res[1],length(res));
          end;
       res:=   rmk_NOLAM+icao_NXT+adr
             + icao_ARR+head+id
             + icao_ARR+key+NULL;
       NETsend_msg (FDAaddress,spr_NOLAM,@res[1],length(res),false,net_flag_SEND)
     end;
