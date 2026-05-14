procedure O_EXT._send_test(head,fn: string);
    var   data : pchars;
          size,size_: long;
    begin
      if ReadFile(pointer(data),size,fn+'.'+fn_ext) then
         begin
           size_:= size;
           if data^[size_-1] in [kbLF,kbCR] then dec(size_);
           if data^[size_-1] in [kbLF,kbCR] then dec(size_);
           send_data('',head,'','', data,size_, '',0);
           freemem(data,size);
         end;
    end;


{ nacitanie dat z textoveho subora, ked velkost riadku presiahne string
}
procedure O_EXT._process_char (soc: char);
    begin
    end;


procedure O_EXT._process_data(data: pchars; size: word);
   var    res : string;
   begin
     receive_pkt(src_ext,'', data,size, res, true);
     if (res<>'') then writeln_pkt (@res[1],length(res), arch_ERR,'', cl_r,false,false);
   end;


procedure O_EXT._process_test (data: pbytes; dlz: int);
    begin
      _process_data(pchars(data),dlz);
    end;


function  O_EXT._process_file (src: TPKT_SRC;
                               var fn: string;
                               demo : bool;
                               soc: char; off: int;
                               one_msg: bool; var last_pos: long
                              ): bool;
    var   f : file of byte;
          p : pointer;
          b : byte;
          z,k,i,j, l,dlz : long;
          is,bres  : bool;
          res,s,_fn : string;

    begin
      if demo then
         begin
           _fn:= get_icao_streamFN(pathSTREAM,fn_ext, day,month,year, hour,min);
           if (fn='') or (fn<>_fn) then
              begin
                fn:= _fn;
                last_pos:= 0
              end
         end;

      if Exists(fn)<>0 then Exit;

      Assign(f,fn); Reset(f);
      if one_msg then Seek(f,last_pos);
      z:= FilePos(f);
      while not Eof(f) do
        begin
          read(f,b);
          if b=ord(kbLF) then
             begin
               k:= FilePos(f)-1; Seek(f,z);
               GetMem(p,k-z+1);
               i:= 0; while i<=k-z do
                 begin
                   read(f,pbytes(p)^[i]);
                   _process_char(pchars(p)^[i]);
                   inc(i)
                 end;
               i:= 0;
               if soc<>' ' then
                  begin
                    while (i<=k-z) and (pchars(p)^[i]<>soc) do inc(i);
                  end;
               inc(i,off);
               for j:= 0 to strlen(p)-1 do
                 begin
                   if pchars(p)^[j]=kbLF_ then pchars(p)^[j]:= kbLF;
                   if pchars(p)^[j]=kbCR_ then pchars(p)^[j]:= kbCR
                 end;
               is:=     (k-z-i+1>2)             { eliminovanie prazdneho riadku }
                    and (pchars(p)^[0]<>';');   { - // - poznamky }

               if is then
                  begin
                    if pchars(p)^[i] in [kbLF,kbCR] then inc(i);
                    if pchars(p)^[i] in [kbLF,kbCR] then inc(i);

                    {dlz:= k-z-i+1-2;
                    pNL__to_NL (@pchars(p)^[i],dlz);
                    _process_test(@(pchars(p)^[i]),dlz);}

                    {check_pkt_frame(@(pchars(p)^[i]),k-z-i+1-2, s);}
                    if src=src_ext then receive_pkt(src_ext,'', @(pchars(p)^[i]),k-z-i+1-2,res,true)
                    else process_pkt(src,@(pchars(p)^[i]),k-z-i+1-2,res,res,bres)

                    {save_pkt0(@(pchars(p)^[i]),k-z-i+1-2)}
                    {s:= 'H@@@@D@01';}
                    {save_pkt0(@s[1],length(s));}
                    {check;}
                  end;

               FreeMem(p,k-z+1);
               z:= k+1;
               Seek(f,z);
               last_pos:= z;
               if is and one_msg then break;

               Check
             end
        end;

      bres:= Eof(f);
      if bres then last_pos:= 0;

      _process_file:= bres;
      Close(f);
      ResetIOError
    end;


procedure O_EXT.test_file(fn: string; soc: char; off: int);
    var   p: pstring;
    begin
      {s:= '‹€   – UKWZ  € 16/10/97 4€‘’œ  2'
          +#10#13+' … ‰ ‘  ’ˆ  ‚›‹…’    ‚•„      ‚›•„     ‘€„Š€  Œ… €‡'#10#13'…ƒ9206  ’“54 ‹ƒ’‘1715 '
          +'Š…”ˆ1824 ƒ’‚  1833 ““……2000 ”Œ“09300000'+#10#13+'Š…–  2 4€‘’ˆ'+#10#13+'';
      process_pkt(src_ext,@s[1],length(s),res,res);
      }
      testing_txt_file:= true;
      _process_file(src_ext,fn,false,soc,off,testing_one_msg,test_last_pos);
      testing_txt_file:= false;
    end;


procedure O_EXT.demo_file(soc: char; off: int);
    var   p: pstring;
    begin
      {s:= '‹€   – UKWZ  € 16/10/97 4€‘’œ  2'
          +#10#13+' … ‰ ‘  ’ˆ  ‚›‹…’    ‚•„      ‚›•„     ‘€„Š€  Œ… €‡'#10#13'…ƒ9206  ’“54 ‹ƒ’‘1715 '
          +'Š…”ˆ1824 ƒ’‚  1833 ““……2000 ”Œ“09300000'+#10#13+'Š…–  2 4€‘’ˆ'+#10#13+'';
      process_pkt(src_ext,@s[1],length(s),res,res);
      }
      testing_txt_file:= true;
      _process_file(src_ext,testing_fn,true,soc,off,testing_one_msg,test_last_pos);
      testing_txt_file:= false;
    end;