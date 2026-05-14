function O_AFTN_TSGA.decode_data (data: pchars; size: word;
                                  header: string;
                                  var head: string;
                                  var res: string
                                 ): bool;

   var   FPL : DFPL4;
         i : int;
   begin
     decode_data:= false;
     i:= _icao_head_type(head,res);
     if res<>'' then Exit;

    {$IFDEF FPL4}
     new_FPL4(nil,@FPL);
     case msAF_TSGAdata(i) of
     { msALR   : decode_data:= decode_ALR(data,size, FPL^, res);
       msRCF   : decode_data:= decode_RCF(data,size, FPL^, res);
     }
       msPPL,
       msFPL   : decode_data:= decode_FPL(data,size, FPL, res);

       msCHG   : decode_data:= decode_CHG(data,size, FPL, res);
       msDLA   : decode_data:= decode_DLA(data,size, FPL, res);
       msCNL   : decode_data:= decode_CNL(data,size, FPL, res);

       msDEP   : decode_data:= decode_DEP(data,size, FPL, res);
       msARR   : decode_data:= decode_ARR(data,size, FPL, res);

     end;

     disp_FPL4(@FPL);
    {$ENDIF}

     if res<>'' then decode_data:= false
   end;
