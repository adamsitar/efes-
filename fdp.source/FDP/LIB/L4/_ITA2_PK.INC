{ ---------------------------
   Zostavenie spravy
  ...........................
}
{ Struktura:  hlavicka
              adresny riadok
              udaje odosielatela
              text
              koniec


  Kazda cast spravy sa oddeluje MTK_2_NL.


  Hlavicka :  prepinac abecedy
             +MTK_2_SOH
             +MTK_2_SPACE
             +napr. MKA017   // kanal (odosielatel+adresat+id_kanala) a cislo spravy
                              // - mimo áñ,çç,ó,ò,ô,ù,û, kanal v postupnosti kanalov
                              // medzi stanicami
             +MTK_2_SPACE
             +napr. 0817      // cas 08.17
             +MTK_2_INT(_R)   // interval

  Adresny riadok :

              MTK_2_NL                // koniec riadku
             +kategoria naliehavosti
             +max 9 adries do 6 znakov alebo max 7 do 8
             +MTK_2_NL

             V CCCP Existuju zvlastne pravidla, ak adresa
             nie je v ICAO, potom "úú", nema nema dvojznakovy kod "õõ"
             alebo je to vojenska "õú" adresa

  Udaje odosielatela :

              MTK_2_DIGITS
             +sest znakov den a cas podania spravy
             +prepinac abecedy
             +MTK_2_SPACE
             +sest alebo osem znakov identifikacie odosielatela
             +MTK_2_NL

  Text : podla prislusneho predpisu


  Koniec : mal by zakonceny v tvare :
             MTK_2_NMPS
            +MTK_2_EOT
            +MTK_2_NMPP       // len na neautomatizovane stanice


  Ak je od poslednej spravy viac ako 30 s, je potrebne poslat
  spustaci impluz :

  Pr.  M2_L+MTK_2_SOT+MTK_2_SPACE+'MKA'+M2_D+'017'+MTK_2_INT

       MKA ... cislo kanala
       017 ... cislo spravy


  Pr.  ZCZC VLA502 1333
       ŸFF UKBBZQZX
       ŸFF UKBBZTZX UKBBZQZX UKOOZQZX
       Ÿ031230 OJAIZPZX
       Ÿ()
       ŸNNNN

       áñáñ ÜãÄ120 0643     Ÿ
       ÑÑ ìäÅÅáêáúŸ
       ÑÑ ìäïïáêáú ìäÅÅáêáúŸ
       030638 ììÇÜáüáúŸ
       ()Ÿ
       çççç

       ZCZC VLA487 1314     Ÿ
       GG UKBBZRZXŸ
       GG UKKUZXZX UKKKZDZX UKLLBFXX UKBBZRZX UKKKZTZX UKCCZTZXŸ
       031313 UKLLZTZXŸ
       031201 UKLLZTZXŸ
       ()Ÿ
       NNNN
}

 const max_adries  = MTK_2_PAGE {_MTK_ADR_LINEs};
 type  pole_adries = array[0..max_adries-1] of pchar;

 procedure rozklad_adries_do_riadkov (priorita : string;
                                      adresati : pchar;

                                      var adresy: pole_adries;
                                      var adries: int;
                                      var adlz: word
                                     );

     var   i,j,pocet : int;
           s,a : string;

     begin
       fillchar(adresy,sizeof(adresy),0);
       adries:= 0;
       adlz:= 0;

       i:= 1; pocet:= getpstritems(adresati,[icao_NXIT]);
       while ({(adries*_MTK_ADR_hi_pocet)}i<=pocet) and (adries<max_adries) do
         begin
           adresy[adries]:= nil;
           j:= 1; a:= '';
           while (j<=_MTK_ADR_hi_pocet) and ({(adries*_MTK_ADR_hi_pocet)+}i<=pocet) do
             begin
               s:= getPstr(adresati,i,[icao_NXIT]);
               if j>1 then s:= MTK_2_SPACE + s;
               a:= a + s;
               inc(j);
               inc(i)
             end;
           a:= MTK_2_NL_+priorita+MTK_2_SPACE+a+MTK_2_NL_;
           adresy[adries]:= strpasnew(a);
           inc(adries);
           inc(adlz,length(a))
         end
     end;


 function  code_ITA2_pkt (channel : string;
                          cislo_spravy : int;
                          priorita : string;
                          adresati : pchar;
                          odosielatel : string;

                          data: pchars; size: word;

                          var pkt: pchars;  var dlz: word;

                          bin : bool;
                          ibits : byte;
                          var bpkt: pchars; var bdlz: word
                         ): bool;

    var   hlavicka,ritka,riadok : string;
          adresy : pole_adries;
          adlz, pole : word;
          adries, riadkov, i,l,k,c,p : int;


    procedure clean(data: pchars; size: int);
        var   i: int;
        begin
        { odstranenie bielych znakov
        }
          for i:= 0 to size-1 do
            begin
              if data^[i] in MTK_2_CONTROL+[' '] then data^[i]:= ' '
              else begin
                     l:= 0; k:= 0;
                     while (l<max_MTK_2_abc) and (MTK_2[l,k]<>data^[i]) do
                       begin
                         k:= 0; while (k<max_MTK_2_znk) and (MTK_2[l,k]<>data^[i]) do inc(k);
                         if (k>=max_MTK_2_znk) then inc(l)
                       end;
                     if l>=max_MTK_2_abc then data^[i]:= ' '
                   end
            end;
        end;

    begin
      pkt := nil; dlz := 0;
      bpkt:= nil; bdlz:= 0;
      code_ITA2_pkt:= false;


      { naplnenie poloziek spravy
      }
       hlavicka :=   MTK_2_LATIN + MTK_2_SOT
                   + MTK_2_SPACE + channel+inttostr(CISLO_SPRAVY,ITA2_CHANNEL_SIZE,0)
                   + MTK_2_SPACE + code_l4_utc(hour,min)
                   + MTK_2_INT_                  { obsahuje MTK_2_LATIN }
                   ;

       rozklad_adries_do_riadkov (priorita,adresati, adresy,adries,adlz);
       if (adresati<>nil) then
          odosielatel:=   MTK_2_DIGITS + code_MTK2_date(day, hour,min) {inttostr(day,2,0)+code_l4_utc(hour,min)}
                        + MTK_2_LATIN  + MTK_2_SPACE + odosielatel
                        + MTK_2_NL_
       else odosielatel:= MTK_2_NL_;

       ritka := MTK_2_EOT_;


      { vytvorenie spravy
      }
       p:= get_str_items(data,size, setNL+setNL_);
       pole:= 0;
       for i:= 1 to p do
         begin
           pole:= pole + length(get_str(data,size, i, setNL+setNL_, sizeof(string)-1));
           if (i<p) or (data^[size-1] in setNL+setNL_) then pole:= pole + length(MTK_2_NL_);
         end;

       dlz :=   length(hlavicka)
              + adlz
              + length(odosielatel)
              + pole
              + length(ritka);

       if maxavail>dlz then
          begin
            getmem(pkt,dlz); fillchar(pkt^,dlz,0); c:= 0;
            move(hlavicka[1],    pkt^[c], length(hlavicka));     inc(c,length(hlavicka));
            for i:= 0 to adries-1 do
              begin
                move(adresy[i][0],  pkt^[c], strlen(adresy[i])); inc(c,strlen(adresy[i]));
              end;
            move(odosielatel[1], pkt^[c], length(odosielatel));  inc(c,length(odosielatel));

            for i:= 1 to p do
              begin
                riadok:= get_str(data,size, i, setNL+setNL_, sizeof(riadok)-1);
                clean(@riadok[1],length(riadok));
                if (i<p) or (data^[size-1] in setNL+setNL_) then riadok:= riadok + MTK_2_NL_;
                move(riadok[1], pkt^[c], length(riadok));
                inc(c,length(riadok));
              end;

            move(ritka[1],       pkt^[c], length(ritka));        inc(c,length(ritka));
          end;

       for i:= 0 to adries-1 do strdispose(adresy[i]);

      { kodovanie spravy
      }
       if (pkt<>nil) then ascii_to_mtk2bin (pkt,dlz, false {v hlavicke je M2L}, pbytes(bpkt),bdlz, bin,ibits);

       (*{$IFDEF DEBUG} { Kontrola }
         getmem(ddata,bsize); move(adata^,ddata^,bsize);
         mtk2bin_to_ascii(pchars(ddata),bsize, ibits);
         freemem(ddata,bsize);
       {$ENDIF}*)

       code_ITA2_pkt:= (pkt<>nil)
     end;
