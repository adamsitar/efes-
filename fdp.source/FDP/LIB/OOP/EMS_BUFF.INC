{ --------------------------
   TstreamBuffer
  --------------------------
}

{constructor TstreamBuffer.Init;
      begin
        inherited Init(1,0)
      end;
}

procedure TstreamBuffer.add_to_buffer (var buff; bdlz: word);
    begin
      if not is then Exit;

      seek(getsize);
      write(buff,bdlz)
    end;


 {w:= a.getsize;
 getmem(p,w);
 a.seek(0);
 a.read(p^,w);
 freemem(p,w);
 }

constructor TstreamBuffer.Init(MinSize, MaxSize: Longint);
      begin
        inherited Init(MinSize, MaxSize);
        if not is then _write_err_log('Failed to init EMS stream.')
      end;


function TstreamBuffer.read_buffer (var buff: pchars; var bdlz: word; buff0: bool): bool;
   begin
     read_buffer:= read_buffer_int (0,getsize, buff,bdlz, buff0)
   end;


function TstreamBuffer.read_buffer_int (pos,max: long; var buff: pchars; var bdlz: word; buff0: bool): bool;
   var   dlz : long;
   begin
     read_buffer_int:= false;
     buff:= nil;
     bdlz:= 0;
     dlz:= Minimum(N(getsize-pos),max);

     if    (MaxAvail<=MIN_NET_HEAP_SIZE)
        or (MaxAvail<=dlz)
        or (dlz=0)
        or (not is) then Exit;

     if (dlz>0) and (dlz<MaxAvail) and (MaxAvail>MIN_NET_HEAP_SIZE) then
        begin
          read_buffer_int:= true;
          bdlz:= dlz;
          if buff0 then inc(bdlz);
          getmem(buff,bdlz); fillchar(buff^,bdlz,0);
          seek(pos);
          read(buff^,dlz); { musi byt dlzka <= dlzke dat v bufferi }
          if buff0 then buff^[bdlz-1]:= NULL
        end
   end;
