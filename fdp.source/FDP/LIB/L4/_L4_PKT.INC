function  code_ICAO_pkt (soh, eot, header: string;
                         data: pchars; size: word;
                         var pkt: pchars; var dlz: word
                        ): bool;
    var   c : word;
    begin
      pkt:= nil; dlz:= 0;
      code_ICAO_pkt:= false;

      header:= soh+icao_STD+header;
      eot:= icao_END+eot;

      dlz:= length(header) + size + length(eot);
      if MaxAvail <= dlz then Exit;
      GetMem(pkt,dlz); FillChar(pkt^[0],dlz,0);

      c:= length(header); Move(header[1],pkt^[0],c);
      {k:= Minimum(size,p-c-length(eot)-1);}

      if data<>nil then begin Move(data^,pkt^[c],size); inc(c,size) end;
      Move(eot[1],pkt^[c],length(eot)); {inc(c,length(eot));}

      code_ICAO_pkt:= true
    end;

