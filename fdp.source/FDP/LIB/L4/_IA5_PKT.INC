function  code_IA5_pkt  (channel : string;
                         cislo_spravy : int;
                         priorita : string;
                         adresati : pchar;
                         odosielatel : string;

                         data: pchars; size: word;

                         var pkt: pchars;  var dlz: word
                        ): bool;

   var   heading,address,origin,ending: string;
         i,c : word;

   begin
     pkt:= nil; dlz:= 0;
     code_IA5_pkt:= false;

     heading:=   IA5_SOH + channel + inttostr(cislo_spravy,IA5_CHANNEL_SIZE,0);

     address:=   IA5_NL + priorita;
     c:= getPstritems(adresati,[icao_NXIT]);
     for i:= 1 to c do address:= address + IA5_SPACE + getPstr(adresati,i,[icao_NXIT]);
     address:= address + priorita + IA5_NL;

     origin:=                 inttostr(day,2,0)+code_l4_utc(hour,min)
               + IA5_SPACE  + odosielatel
               + IA5_NL
               + IA5_STX;


     ending:=    IA5_NL + IA5_VT + IA5_ETX;

     dlz:=    length(heading)
            + length(address)
            + length(origin)
            + size
            + length(ending);

     if maxavail<=dlz then Exit;
     getmem(pkt,dlz); fillchar(pkt^,dlz,0);
     c:= 0;

     move(heading[1],    pkt^[c], length(heading));     inc(c,length(heading));
     move(address[1],    pkt^[c], length(address));     inc(c,length(address));
     move(origin[1],     pkt^[c], length(origin));      inc(c,length(origin));
     move(data^[0],      pkt^[c], size);                inc(c,size);
     move(ending[1],     pkt^[c], length(ending));      inc(c,length(ending));

     code_IA5_pkt:= true
   end;
