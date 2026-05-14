     type PFileBuffer = ^TFileBuffer;
          TFileBuffer = object(TstreamBuffer)
            fn : string;

            constructor Init(_fn: string);
            destructor  Done; virtual;

            procedure   ReadFile;
            procedure   SaveFile;
          end;

     type PCopyFileBuffer = ^TCopyFileBuffer;
          TCopyFileBuffer = object(TFileBuffer)
            fn0 : string;

            constructor Init(_fn,_fn0: string);
          end;


constructor TFileBuffer.Init(_fn: string);
      begin
        fn:= _fn;
        inherited Init(_filesize(fn),0);
        ReadFile
      end;


destructor  TFileBuffer.Done;
     begin
       SaveFile;
       inherited Done;
     end;


const buff_size = 1024;

procedure TFileBuffer.ReadFile;
    var   f    : file;
          buff : pchars;
          numi,numc : word;
          numr,numm : long;
    begin
      if FExists(fn)<>0 then Exit;
      seek(0); truncate;                { odmazanie povodnych dat, ak boli }
      numr:= 0; numm:= _filesize(fn);
      getmem(buff,buff_size);
      system.Assign(f,fn); system.Reset(f,1);
      repeat
        fillchar(buff^,buff_size,0);
        system.blockread (f,buff^,buff_size,numi);
        add_to_buffer (buff^,numi);
        inc (numr,numi)
      until (numi=0) or (numr<numm);
      freemem(buff,buff_size);
      system.Close(f)
    end;


procedure TFileBuffer.SaveFile;
    var   f    : file;
          buff : pchars;
          numi,numc : word;
          numr,numm : long;
    begin
      system.Assign(f,fn); system.Rewrite(f,1);
      numr:= 0; numm:= getsize;
      while (numr<numm) and read_buffer_int(numr,buff_size, buff,numi, false) do
        begin
          system.blockwrite(f, buff^,numi,numc);
          inc(numr,numi);
          freemem(buff,numi)
        end;
      system.Close(f)
    end;


constructor TCopyFileBuffer.Init(_fn,_fn0: string);
      begin
        if FExists(_fn)=2 then CopyFile(_fn0,_fn,0,false,true);
        inherited Init(_fn)
      end;
