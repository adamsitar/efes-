 function O_AFTN._is_to_LAM (data: pchars; size: word; header: string): bool;
    begin
      _is_to_LAM:= false;
    end;


{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   - dekovanie z kodu MTK_2
   - eliminovanie prazdnych riadkov za pseudoznaky keyb
}

 function O_AFTN.decode_pkt(data: pchars; size: word; var res: string): bool;
    var   i,j,k   : int;
          b,z,r   : byte;
          p       : pchars;
          zac,kon : word;
          s, sot,eot : string;
    begin
      res:= '';

      if {$IFDEF DEBUG} false {$ELSE} archive_AFTN_bin {$ENDIF} then
         begin
         { Ulozenie binarnej spravy
         } archivuj_data(pathSTREAM,get_ARCHfn(0)+'.'+extAFTNb, pbytes(data),size, arch_PKT_REC, writeln_AFTN_utc,false);

         { Ulozenie textovej spravy dekodovanej len do kodu LATIN
         } getmem(p,size);
           for i:= 1 to size do p^[i-1]:= MTK_2[rdk_MTK_2_LAT,inv_byte(ord(data^[i-1]), asyncBITs)];
           archivuj_data(pathSTREAM,get_ARCHfn(0)+'.'+extAFTNb, pbytes(p),size, arch_PKT_REC, writeln_AFTN_utc,false);
           freemem(p,size);
         end;

      mtk2bin_to_ascii(data,size, asyncBITs);

     { e) korektna sprava AFTN musi zacinat "ZCZC" a koncit "NNNN"
     }{
       i:= length(MTK_2_SOH);
       while (i<size) do
          begin
          end
       sot:= get_str(data,size,2,setNL+setNL_,sizeof(s)-1); sot:= cut_(sot);
       system_pkt:= (copy(s,1,length(MTK_2_CH_R))=MTK_2_CH_R) or (copy(s,1,length(MTK_2_CH))=MTK_2_CH)
      }

      decode_pkt:= res=''
    end;


{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
  Vracia true, ak sa paket potvrdzuje; chyby detekuje vo vnutri a vyhodnocuje
  ich s popisom.
  Kvoli jednoduchsiemu spracovaniu pchar-u konverzia pchars na pchar
}

 function O_AFTN.process_data (src: TPKT_SRC;
                               data: pchars; size: word;
                               var header: string;
                               var resh,resd: string
                              ): bool;
    var   zac,kon : word;
          bres : bool;
    begin
      if     decode_frame  (data,size, zac,kon, resh)
         and decode_header (data,size, zac,kon, header, resh,false)
         and (_icao_head_type(header,resh)>=0) then
         begin
           {process_data_FPL (src, @data^[zac],(kon-zac)+1, header,res)}
           process_data:= process_data_FPL (src, data,size, header,resh,resd)
         end
      else begin
             resh:= '';
             process_data_TLG (src, data,size, resd);
             process_data:= false { TLG sa nepotvrdzuje }
           end
    end;


 function O_AFTN.process_data_FPL (src: TPKT_SRC;
                                   data: pchars; size: word;
                                   var header: string;
                                   var resh,resd: string
                                  ): bool;
    var   p,i,zac,kon : word;
          d : pchars;
    begin
      if (src<>src_net) {$IFDEF SYNCHRONIZE_EXT} or is_distribute_pkt {$ENDIF} then
         begin
         { v poli data sa nachadzaju oddelovace riadkov a nesmiem ich prepisat,
           pretoze v pripadne neuspesneho spracovnania sa paket spracovava a nahrava;
         }
           {p:= size-1; while (p>0) and (data^[p] in[' ',NULL]) do dec(p);
           getmem(d,p+1); move(data^,d^,p+1);
           for i:= 0 to p-1 do d^[i]:= cNL_to_NL_(d^[i]);
           d^[p]:= NULL;
           process_data_FPL:= decode_data (data,size,header,header,res);
           freemem(d,p+1)
           }
           process_data_FPL:= inherited process_data (src, data,size, header, resh,resd);
         end
      else process_data_FPL:= false
    end;


function O_AFTN.decode_data (data: pchars; size: word;
                             header: string;
                             var head: string;
                             var res: string
                            ): bool;
   var   FPL : DFPL4;
         i   : int;
   begin
     decode_data:= false;
     i:= _icao_head_type(head,res);
     if i<0 then Exit;

    {$IFDEF FPL4}
     new_FPL4(nil,@FPL);
     case msAFTNdata(i) of
       msFPL   : decode_data:= decode_FPL(data,size, FPL, res);
       msCHG   : decode_data:= decode_CHG(data,size, FPL, res);
       msDLA   : decode_data:= decode_DLA(data,size, FPL, res);
       msCNL   : decode_data:= decode_CNL(data,size, FPL, res);

       msDEP   : decode_data:= decode_DEP(data,size, FPL, res);
       msARR   : decode_data:= decode_ARR(data,size, FPL, res);
     end;
     disp_FPL4(@FPL)
    {$ENDIF}
   end;
