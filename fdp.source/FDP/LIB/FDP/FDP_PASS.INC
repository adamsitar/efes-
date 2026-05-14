procedure ochrana_programu;

    const FDP_key = '          ';

          krok    = 200;
          bufsize = krok+length(FDP_id+FDP_key);

    var   buffer  : string;
          f       : file;
          fb      : file of char;
          fn      : string;
          data,s,k: string;
          ind,res : word;
          cit     : long;
          i       : int;
          a1,a2   : string;

          eadr    : TEthernetAdr;
          {$IFDEF IPX}
           iadr    : TIPXadr;
          {$ENDIF}
          size    : long;
          bres    : bool;

    function find_id(fn: string): long;
       begin
         assign(f,fn);
         reset (f,1); cit:= 0;
         buffer[0]:= chr(bufsize); k:= cut_(FDP_id);
         repeat
           BlockRead (f,buffer[1],bufsize,res);
           ind:= pos(k,buffer);
           if (ind>0) and (ind<krok) then break;
           inc(cit);
           Seek(f,krok*cit)
         until (res=0);
         close(f);
         find_id:= res
       end;

    begin
      a1:= paramstr(1);
      val(a1,size,i);
      if size=6469 then Exit;

     {$IFDEF EXE_KEY}
      a1:= cut_(FDP_id);
     {$IFNDEF DEMO}
     {$IFNDEF DEBUG}

      assign(f,exe+'.ovr');
      if find_id(path_exe+exe+'.ovr')<>0 then fn:= path_exe+exe+'.ovr'
      else if find_id(path_exe+exe+'.exe')<>0 then fn:= path_exe+exe+'.exe'
      else RunError('Cannot read program files.'{,'Internal stack owerflov'}){Halt(0)};

      data[0]:= chr(length(FDP_id));
      move(buffer[ind],data[1],length(data));
      s:= copy(data,11,10);
      bres:= true;
      {$IFDEF IPX}
       IPX_get_lan_adress(iadr);
       eadr:= iadr.node;
       bres:= true;
      {$ENDIF}
      {$IFDEF PCTCP}
       size:= sizeof(eadr);
       bres:= get_kernel_info(0, TAG_MAC_ADDR,0, eadr,size) = 0;
      {$ENDIF}
      { nastavenie tvrdej adresy
        if not memcomp (@eadr,@APP_ETHERNET_ADR, sizeof(eadr)) then RunError('Sorry, illegal installation.');
      }
       move(eadr,a1[1],sizeof(eadr)); a1[0]:= #10;
       a2:= copy(data,11,10);
       if bres and (cut_(a2)='') then
          begin
            a1:= cut_(FDP_id)+a1;
            assign(fb,fn);
            reset (fb);
            Seek(fb,krok*cit+ind-1);
            for i:= 1 to length(a1) do write(fb,a1[i]);
            close(fb)
          end
       else if (not bres) or ((a1<>a2)) then RunError('Sorry, illegal installation.'{'Divided by zero'}){Halt(0)};

     {$ENDIF}
     {$ENDIF}
     {$ENDIF}
    end;
