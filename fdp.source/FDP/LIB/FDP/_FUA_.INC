 type  TFUAprs = string[kod_PRS];

 const max_FUAprs = MAX_ARRAY_SIZE div sizeof(TFUAprs);

 type  PFUAprss = ^TFUAprss;
       TFUAprss = array[0..max_FUAprs-1] of TFUAprs;

 const FUAprss : PFUAprss = nil;
       poc_FUAprs : word = 0;


 procedure init_FUA_;
     var   s : string;
           i : int;
     begin
       cas_FUA_24H_EN:= read_cfg_bool(cfg_FUA, cfg_FUA_24H_EN, cas_FUA_24H_EN);
       cas_FUA_1H_EN:= read_cfg_bool(cfg_FUA, cfg_FUA_1H_EN, cas_FUA_1H_EN);
       cas_FUA_1H:= read_cfg_word(cfg_FUA, cfg_LIMIT_FUA_1H, cas_FUA_1H);

       s:= ''; while (poc_FUAprs<max_FUAprs) and (__read_cfg_line(cfg_FUA,cfg_FUA_1H,poc_FUAprs+1,2)<>'') do inc(poc_FUAprs);
       if (poc_FUAprs>0) and AllocMem(pointer(FUAprss),poc_FUAprs*sizeof(TFUAprs)) then
          begin
            i:= 0; while (i<poc_FUAprs) do
              begin
                s:= getstr(__read_cfg_line(cfg_FUA,cfg_FUA_1H,i+1,2),2,odd_cfg);
                FUAprss^[i]:= _unique_area_code(s);
                inc(i);
              end;
          end;
     end;

 procedure done_FUA_;
     begin
       if FUAprss<>nil then
          begin
            DeallocMem(pointer(FUAprss),poc_FUAprs*sizeof(TFUAprs));
            poc_FUAprs:= 0;
          end
     end;


 function neschvalovany_PRS(kod: string): bool;
    var   i : int;
    begin
     {$IFDEF AMC}
      i:= 0; while (i<poc_FUAprs) and (kod<>FUAprss^[i]) and (not in_TSA(kod,FUAprss^[i])) do inc(i);
      neschvalovany_PRS:= i<poc_FUAprs
     {$ELSE}
      neschvalovany_PRS:= false
     {$ENDIF}
    end;
