 const is_temp_PLN : bool = false;

 procedure pozri_spracovanie_PLN;
     const h : byte = 24;
           d : byte = 0;
     begin
       if (h<>hour) or (d<>day) then
          begin
            if d=0 then is_temp_PLN:= najstarsi_subor(path_TLG,'*.'+extPLN)<>'';

            if (hour>=23) or ((d<>0) and (day>=d)) then
               begin
                 process_pended_PLN (true);
               end;

            h:= hour;
            d:= day;

            is_temp_PLN:= najstarsi_subor(path_TLG,'*.'+extPLN)<>'';
            {$IFDEF PLN}
             btPLN^.visibility(is_temp_PLN)
            {$ENDIF}
          end;
     end;


 procedure save_pend_PLN (data: pchars; size: word);
     var   fn: string;
           D : DirStr;
           N : NameStr;
           E : ExtStr;
     begin
       if DEV_ICAO=nil then Exit;

       with DEV_ICAO^ do
         begin
           fn:= _fn_data(data,size);
           FSplit(fn,D,N,E);
           fn:= N+'.'+extPLN
         end;
       archivuj_data(path_TLG,fn, pbytes(data),size, '',false,false);
       is_temp_PLN:= true;
       {$IFDEF PLN}
        btPLN^.visibility(is_temp_PLN)
       {$ENDIF}
     end;


 function  _process_pnd_PLN (fn: string; all: bool): bool;
    var    last_pos: long;
    begin
      last_pos:= 0;
      if DEV_ICAO<>nil then with DEV_ICAO^ do
         begin
           _process_file (src_file,fn,' ',0,false,last_pos);
           delete_pkt (nil,0, '',fn, spr_del, '', true,false)
         end;
      _process_pnd_PLN:= true or all
    end;


 procedure process_pended_PLN (all: bool);
     var   fn   : string;
           bres : bool;
     begin
       fn:= najstarsi_subor(path_TLG,'*.'+extPLN); bres:= fn<>'';
       while (fn<>'') and bres do
         begin
           bres:= p_process_pnd_PLN(path_TLG+fn,all);
           if bres then {DelFile(path_TLG+fn)}
           else break;
           fn:= najstarsi_subor(path_TLG,'*.'+extPLN);
           if (all) and (fn<>'') then bres:= Ask2(msgVERIPHY,'Process the next PLN message ?',titNo,clGRe,clGR7,180)<>ansNie
         end;

       is_temp_PLN:= najstarsi_subor(path_TLG,'*.'+extPLN)<>'';
       {$IFDEF PLN}
        btPLN^.visibility(is_temp_PLN);
       {$ENDIF}
     end;

