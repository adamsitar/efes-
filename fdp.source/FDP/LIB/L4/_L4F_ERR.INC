procedure O_L4_FDP.process_ERR_DATA (src: TPKT_SRC;
                                     data: pchars; size: word; res: string;
                                     err_save,err_show,distribute: bool
                                    );
    begin
      inherited process_ERR_DATA (src, data,size,res, err_save,err_show,distribute);
      if _error_FDA and (FDAaddress<>'') then
         begin
           if (data<>nil) then NETsend_err (FDAaddress,level_DATA,false,data,size);
           NETsend_err (FDAaddress,level_USER,true,@res[1],length(res))
         end;
    end;
