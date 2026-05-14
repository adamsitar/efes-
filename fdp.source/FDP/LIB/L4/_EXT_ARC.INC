{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
  zobrazenie a archivacia prijatej/odosielanej spravy,
  ak to parametre dovoluju
}
function O_EXT._scroller_enabled: bool;
   begin
    {$IFDEF DATA_WRITTEN_IN_APP}
      if (p_scroll_data<>nil) and (p_scroll_data^<>nil) and (p_scroll_data^^.state) then _scroller_enabled:= true
      else
    {$ENDIF}
       _scroller_enabled:= false
   end;

procedure O_EXT._archive_pkt(data: pchars; size: word; prompt, message: string; is___: bool);
    var   b  : bool;
    begin
      if not _scroller_enabled then
         begin
           {if p_utc<>nil then b:= bool(p_utc^) else} b:= true;
           if     (pathSTREAM<>'')
              and (   ((p_arch<>nil) and bool(p_arch^))
                    or (prompt=arch_ERR) or (prompt=arch_SYS) or (prompt=archMESS)
                  ) then
               begin
                 archivuj_data(pathSTREAM,get_ARCHfn(0)+'.'+fn_ext, pbytes(data),size, prompt+message, b,is___)
               end
         end
    end;


procedure O_EXT._writeln_pkt(data: pchars; size: word; prompt, message: string; cl: byte; is___: bool);
    var   s,t : string;
          b   : bool;
    begin
      if not _scroller_enabled then
         begin
           if p_utc<>nil then b:= bool(p_utc^) else b:= true;
           if     (MainApp<>nil)
              and (   ((p_wr<>nil) and bool(p_wr^))
                   or (prompt=arch_ERR) or (prompt=arch_SYS) or (prompt=archMESS)
                  ) then
              begin
                if message<>'' then
                   begin
                     s:= message+' ';
                     t[0]:= chr(Minimum(size,sizeof(t)-1)); Move(data^,t[1],ord(t[0]));
                     s:= NL_to_NL_ (s+t);
                     if ord(t[0])<size then s:= s+'...';
                     MainApp^.writeln(s,cl,prompt,b)
                   end
                else MainApp^.writeln_(pbytes(data),size,cl,prompt,b,write_in_nl_en)
              end
         end
    end;


procedure O_EXT.writeln_pkt(data: pchars; size: word; prompt, message: string; cl: byte; is___,is_nl: bool);
    begin
      {$IFDEF DATA_WRITTEN_IN_APP}
        if _scroller_enabled then
           begin
             if (size=0) and (prompt='') and (message='') then p_scroll_data^^.fwrite_nl
             else p_scroll_data^^.fwrite_data(data,size, prompt,message, true{is_utc},true{is_tab},is_nl)
           end
        else
      {$ENDIF}
         begin
          _archive_pkt (data,size, prompt, message, is___);
          _writeln_pkt (data,size, prompt, message, cl, is___);
         end
    end;


procedure O_EXT.print_pkt (data: pchars; size: word; title: string);
    var   i,p : int;
          s   : string;
          res : bool;
    begin
     {$IFDEF PRN}
       res:= true; i:= 1; p:= get_str_items (data,size, setNL+setNL_);
       while (i<=p) and res do
         begin
           s:= get_str(data,size,i,setNL+setNL_, sizeof(s)-1);
           res:= print_str(PortNo,s+kbNL);
           inc(i)
         end;
       if res then
          begin
            i:= 0; while (i<3) and print_str(PortNo,kbNL) do inc(i)
          end;
     {$ENDIF}
    end;


{ ulozenie pola (hlasky) zo subora,
  nema vyznam ak bola chyba medzitym
  spracovana (prepis=false)
}
function  O_EXT._save_txt_file(fn: string; ms: string; data: pchars; size: long; prepis: bool): bool;
    var   f    : file of char;
          i,t  : long;
          attr : word;
          bres : bool;
    begin
      bres:= Exists(fn)=0;
      _save_txt_file:= bres;
      if (not prepis) and (not bres) then Exit;
      Assign(f,fn);
      Reset(f);
      if bres then getftime(f,t);
      Rewrite(f);
      ms:= ms+kbNL;
      for i:= 1 to length(ms) do write(f,ms[i]);
      for i:= 1 to size do write(f,data^[i-1]);
      if bres then setftime(f,t);
      Close(f)
    end;


{
  nacitanie pola (hlasky) zo subora
}
function  O_EXT._read_txt_file(fn: string; is_msg: bool; var ms: string; var mp: pchar): bool;
    var   f : text;
          s : string;
    begin
      _read_txt_file:= false; ms:= ''; mp:= nil;
      if Exists(fn)<>0 then Exit;

      Assign(f,fn); Reset(f);
      if is_msg then readln(f,ms); { nacitanie hlavicky }
      while not Eof(f) do
        begin
          readln(f,s);
          if s='' then s:= ' ';
          s:= replchar(s,[#0],' ')+kbNL;
          mp:= StrNPCopy(mp,s,true,true)
        end;
      Close(f);
      ResetIOError;
      _read_txt_file:= true
    end;