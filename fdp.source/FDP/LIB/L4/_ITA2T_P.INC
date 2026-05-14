{ ---------------------------
   Zostavenie spravy
  ...........................
}
{ Struktura:  hlavicka
              adresny riadok
              udaje odosielatela
              text
              koniec

  Pr : pre citatelnost rozdeleny na riadky

       ZCZC VLA487 1314
       GG UKBBZRZX
       GG UKKUZXZX UKKKZDZX UKLLBFXX UKBBZRZX UKKKZTZX UKCCZTZX
       031313 UKLLZTZX
       031201 UKLLZTZX
       ()
       NNNN
}

function  code_ITA2T_pkt (channel : string;
                          cislo_spravy : int;
                          priorita : string;
                          adresati : pchar;
                          odosielatel : string;

                          data: pchars; size: word;

                          var pkt: pchars; var dlz: word
                         ): bool;

   var   hlavicka,ritka: string;
         c : word;

   begin
     pkt:= nil; dlz:= 0;
     code_ITA2t_pkt:= false;

     hlavicka:=               MTK_2_SOT
                + icao_NXIT + channel+inttostr(cislo_spravy,ITA2_CHANNEL_SIZE,0)
                + icao_NXIT + priorita
                + icao_NXIT;

     if adresati<>nil then
        odosielatel:=    icao_NXIT + code_MTK2_date(day, hour,min) {inttostr(day,2,0)+code_l4_utc(hour,min)}
                       + icao_NXIT + odosielatel
                       + icao_NXIT
     else odosielatel:= '';

     ritka:= icao_NXIT + MTK_2_EOT;

     dlz:=    length(hlavicka)
            + strlen(adresati)
            + length(odosielatel)
            + size
            + length(ritka);

     if maxavail<=dlz then Exit;
     getmem(pkt,dlz); fillchar(pkt^,dlz,0);
     c:= 0;

     move(hlavicka[1],    pkt^[c], length(hlavicka));     inc(c,length(hlavicka));
     move(adresati[0],    pkt^[c], strlen(adresati));     inc(c,strlen(adresati));
     move(odosielatel[1], pkt^[c], length(odosielatel));  inc(c,length(odosielatel));
     move(data^[0],       pkt^[c], size);                 inc(c,size);
     move(ritka[1],       pkt^[c], length(ritka));        inc(c,length(ritka));

     code_ITA2T_pkt:= true
   end;
