constructor TTxtFileBuffer.Init(_fn: string);
      begin
        fn:= _fn;
        inherited Init;
        {is_init_read:= false;
        is_done_save:= false;
        if is_init_read then ReadFile}
      end;

destructor  TTxtFileBuffer.Done;
     begin
       {if not is_done_save then SaveFile;}
       inherited Done;
     end;


{const buff_size = 1024;}

procedure TTxtFileBuffer.ReadFile;
    var   f : text;
          s : string;
    begin
      if FExists(fn)<>0 then Exit;
      truncate(0);                  { vynuluje obsah buffera v pamati }
      system.Assign(f,fn);          { nacita obsah subora do buffera  }
      system.Reset(f);
      while not Eof(f) do
        begin
          readln(f,s);
          add(s)
        end;
      system.Close(f)
    end;

procedure TTxtFileBuffer.SaveFile;
    var   f : text;
          s : string;
          i : long;
    begin
      vytvor_novy_subor(fn);
      if FExists(fn)<>0 then Exit;
      system.Assign(f,fn);
      system.Rewrite(f);
      for i:= 0 to items-1 do writeln(f,read(i));
      system.Close(f)
    end;



constructor TCopyTxtFileBuffer.Init(_fn,_fn0: string);
      begin
        fn0:= _fn0;
        if (FExists(fn)<>0) and (FExists(_fn0)=0) then CopyFile(_fn0,_fn);
        inherited Init(_fn)
      end;
