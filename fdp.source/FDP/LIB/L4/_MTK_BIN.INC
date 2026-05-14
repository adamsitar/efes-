{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
  - dekovanie z kodu MTK_2, slovo pride odzadu
}

function inv_byte(b, bits: byte): byte;
   var   z,k: byte;
   begin
     z:= 0; for k:= 1 to bits do z:= z or (((b shr (k-1)) and 1) shl (bits-k));
     inv_byte:= z
   end;


procedure mtk2bin_to_ascii(data: pchars; size: word; bits: byte);
    var   i,j,k   : int;
          b,z,r   : byte;
          p       : pchars;
          zac,kon : word;
          s, sot,eot : string;
    begin
    { a) dekodovanie poslupnosti inverznych indexov v tabulke MTK_2
    } r:= rdk_MTK_2_LAT;    { predpokladame zaciatok kodovania v LATIN }
      j:= 0;
      for i:= 0 to size-1 do
        begin
         { a.a) bity znakov prichadzaju v obratenom poradi:
         } z:= inv_byte(ord(data^[i]), bits);

         { a.b) dostali sme index jedneho mozneho znaku z troch v MTK-2,
                transformacia na kod ASCII LATIN a AZBUKA podla tabulky MTK_2,
                vypustenie prazdnych riadkov, ktore zvycajne chodia :
         }
           case MTK_2[rdk_MTK_2_DIG,z] of
           { prepnutie na ziadanu abecedu }

             MTK_2_LATIN  : begin r:= rdk_MTK_2_LAT; continue end;
             MTK_2_DIGITS : begin r:= rdk_MTK_2_DIG; continue end;
             MTK_2_A36UKA : begin r:= rdk_MTK_2_A36; continue end;

             MTK_2_SPACE  : data^[j]:= ' ';
             MTK_2_CR     : begin
                              if (j>0) and (data^[j-1]<>kbCR) and (data^[j-1]<>kbLF) then data^[j]:= kbCR
                              else continue;
                            end;
             MTK_2_LF     : begin
                              if (j>0) and (data^[j-1]<>kbLF) then data^[j]:= kbLF
                              else continue;
                            end

             else begin
                  { cast textu :
                  } data^[j]:= MTK_2[r,z];
                  { Poznamka: "4" sluzi ako "—", lebo sa v azbuke podobaju.
                              "" nie je vyuzite
                  }
                  end;
           end;
          inc(j);
        end;

     { c) odmazanie nepotrebnych znakov na konci, ktore vznikli tym,
          ze v dekodovanom texte boli vypustene riadiace znaky;
          inak by chaosili
     } for i:= j to size-1 do data^[i]:= ' ';

     { d) moze sa stat, ze chybaju oddelovace riadkov,
          musime ich vsunut, aby mi neprepisovalo obrazovku
          (pocita sa s maximalnou dlzkou riadku)
     } p:= nil;
       i:= 1; while i<=get_str_items(data,size,[kbCR,kbLF]) do
         begin
           get_ind(data,size,i,[kbCR,kbLF], zac,kon);
           if kon-zac>MTK_2_LINE then
              begin
                { problem, dlhsi riadok, ako je vhodne }
                j:= zac+MTK_2_LINE-1; while (j>zac) and (data^[j]<>icao_ARR) do dec(j);
                if j=zac then
                   begin
                     j:= zac+MTK_2_LINE-1; while (j>zac) and (data^[j]<>icao_NXIT) do dec(j);
                   end;
                if j=zac then j:= Minimum(zac+MTK_2_LINE-1,size-1);
                if zac<j then
                   begin
                     getmem(p,size-j+1);
                     move(data^[j+1],p^,size-j+1);
                     data^[j]:= kbCR;
                     if j+1<size then data^[j+1]:= kbLF;
                     if j+2<size then move(p^,data^[j+2],size-j+1-2);
                     freemem(p,size-j+1)
                   end;
              end;
           inc(i)
         end;
    end;


procedure ascii_to_mtk2bin(data: pchars; size: word;
                           _1st_switch: bool;
                           var bdata: pbytes; var bsize: word;
                           bin : bool;
                           ibits : byte
                          );

    const iM2_abc: array[0..max_MTK_2_abc-1] of byte = (iM2_A,iM2_L,iM2_D);

    var   abc: int; i,j,k,l,r,z : word;

    function r_ind(ch: char; var r,z: word): word;
       begin
         r:= 0; z:= 0;
         while (r<max_MTK_2_abc) and (MTK_2[r,z]<>ch) do
           begin
             z:= 0; while (z<max_MTK_2_znk) and (MTK_2[r,z]<>ch) do inc(z);
             if (z>=max_MTK_2_znk) then inc(r)
           end;
         if      ch=M2_L then r:= 1
         else if ch=M2_D then r:= 2
         else if ch=M2_A then r:= 0;
         r_ind:= r
       end;

    function add_abc(var abc : int; r : word; i : int): bool;
       begin
         add_abc:= false;
         if (r<>abc) and (r<max_MTK_2_abc) then
            begin
              add_abc:= ((abc<>-1) or _1st_switch) and (not (data^[i] in [M2_C,M2_F,M2_S, M2_A,M2_L,M2_D]));
              abc:= r   { kvoli pociatocnej -1 }
            end
       end;


    begin
    { a) Vyhladanie indexu v MTK_2 (1-32: najde riadok a stlpec)
         zodpovedajucemu danemu znaku.
      b) Index sa zakoduje do inverzneho kodu.
      c) Pretoze sa musia vsuvat prepinace medzi riadkami (abecedy),
         zvysi sa pocet znakov.
    }

    { Zistenie poctu pridanych znakov
    }
      bsize:= size;
      abc:= -1 ;              {rdk_MTK_2_LAT; riadok sa ma zacinat latinkou }
      for i:= 0 to size-1 do
        begin
          if data^[i]='—' then data^[i]:= '4';

          case data^[i] of

            kbCR,M2_C : ;
            kbLF,M2_F : ;
            ' ' ,M2_S : ;

            else begin
                   r_ind(data^[i], r,z);
                   if add_abc(abc, r,i) then inc(bsize);
                   {$IFDEF DEBUG}
                    if (r>=max_MTK_2_abc) or (z>=max_MTK_2_znk) then
                       begin
                         {RunError('Cannot code message into MTK-2.')}
                       end
                   {$ENDIF}
                 end
          end
        end;

    { alokovanie, naplnenie a zakodovanie noveho pola dat
    } getmem(bdata,bsize); fillchar(bdata^,bsize,0);
      abc:= -1; i:= 0; j:= 0;
      while (i<size) and (j<bsize) do
        begin
          case data^[i] of

            kbCR,M2_C : bdata^[j]:= iM2_C;
            kbLF,M2_F : bdata^[j]:= iM2_F;
            ' ' ,M2_S : bdata^[j]:= iM2_S;

            else begin
                   r_ind(data^[i], r,z);
                   if add_abc(abc, r,i) then
                      begin
                        bdata^[j]:= iM2_abc[r];
                        inc(j)
                      end;
                  if (r<max_MTK_2_abc) and (z<max_MTK_2_znk) then bdata^[j]:= z
                  else bdata^[j]:= iM2_S
                end
          end;
         inc(j);
         inc(i)
        end;

      if bin then for j:= 0 to bsize-1 do bdata^[j]:= inv_byte(bdata^[j],ibits)
    end;
