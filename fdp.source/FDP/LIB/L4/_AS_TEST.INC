procedure test_fn(head: string);
    var   data : pchars;
          size,size_: long;
    begin
      if (DEV_ASOC<>nil) and ReadFile(pointer(data),size,head+'.'+extASOC) then
         begin
           size_:= size;
           if data^[size_-1] in [kbLF,kbCR] then dec(size_);
           if data^[size_-1] in [kbLF,kbCR] then dec(size_);
           {DEV_ASOC^.send_data('',head,'', data,size_, '');}
           freemem(data,size);
         end;
    end;
