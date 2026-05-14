{ -------------------------------------------
   Testovanie
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
procedure O_OPL.check_stream_file;
    const shour: byte = 24;
    begin
     {$IFDEF OPL__SAVE_STREAM}
      if OPL__SAVE_STREAM and (hour<>shour) then
         begin
           shour:= hour;
           if stream_open then close(stream_file);
           stream_open:= false;
           stream_fn:= path_OPL + get_ARCHfn(min)+'.'+extOPS;
           vytvor_novy_subor(stream_fn);
           assign(stream_file,stream_fn);
           reset(stream_file);
           stream_open:= true;
        end;
     {$ENDIF}
    end;

procedure O_OPL.save_stream_char (soc: char);
    begin
     {$IFDEF OPL__SAVE_STREAM}
       if OPL__SAVE_STREAM and stream_open then
         begin
           write(stream_file,soc);
           if (soc=EOT) then
              begin
                soc:= kbCR; write(stream_file,soc);
                soc:= kbLF; write(stream_file,soc);
              end;
         end;
     {$ENDIF}
    end;


procedure O_OPL._process_char (soc: char);
    begin
     {$IFDEF OPL__SAVE_STREAM}
       save_stream_char(soc)
     {$ENDIF}
    end;

procedure O_OPL._process_data(data: pchars; size: word);

   procedure int_inp(b: char);
       begin
         if ((b=SOH) and (OPLpkt^.poc>1)) or (OPLpkt^.poc>=sizeof(OPLpkt^.buf)) then {ipkt_size-sizeof(OPLpkt^.p) then }
            begin
              ibuff^.save(OPLpkt);    {[#]}
              OPLpkt^.poc:= 0;
            end;

         OPLpkt^.buf[OPLpkt^.poc]:= b;
         inc(OPLpkt^.poc);

         if (b=EOT) then
            begin
              {if (OPLpkt^.b[0]=SOH) then} {[#]}
              ibuff^.save(OPLpkt);
              OPLpkt^.poc:= 0
            end
       end;

   var    res : string;
          i   : int;
   begin
     if test_int then for i:= 0 to size-1 do int_inp(data^[i])
     else inherited _process_data(data,size)
   end;
