{ Kontrola adresy...
}
 function O_EXT.is_pkt_for_node (from: string; data: pchars; size: word): bool;
    begin
      is_pkt_for_node:= (from = '') or (from = NODE_REMOTE) or (NODE_REMOTE = NODE_PROMISCUITE)
    end;

{ Zabezpecovaci/servisny paket ?
}
 function O_EXT.is_system_pkt (data: pchars; size: word; res: string): bool;
    begin
      is_system_pkt:= false;
    end;

{ Index hlavicky
}
 function O_EXT._icao_head_type (head: string; var res: string): int;
    begin
      _icao_head_type:= icao_head_type (head,res, p_heads_EXT,heads_EXT)
    end;


{ תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
   implementacia de/kodovania paketu
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת
}
{ Niektore aplikacie maju paket zakodovany inak ako ASCII
}
 function O_EXT.decode_pkt (data: pchars; size: word; var res: string): bool;
    begin
      decode_pkt:= true
    end;


{ Hlavicka spravy sa nachadza sa icao_STD ("(") na prvej pozicii,
  ak tam nic nenajdem, alebo to nie je znama hlavicka, odoslanie
  sprav do chyboveho radu
}
 function O_EXT.decode_frame (data: pchars; size: word;
                              var zac,kon: word;
                              var res: string
                             ): bool;
    begin
      res:= '';
      if not get_ind_(data,size, icao_STD, zac) then res:= err_ext_frame_begin
      else if not get_ind_(data,size, icao_END, kon) then
              begin
                if not uncomplete_pkt_en then res:= err_ext_frame_end;
                kon:= size-1
              end;
      decode_frame:= res=''
    end;


 function O_EXT.decode_HeartBeat (data: pchars; size: word): bool;
    begin
      decode_HeartBeat:= (HeartBeat<>'') and (cut_(init_str(data,size))=HeartBeat)
    end;


{ ASMMI/PR120
}
 function O_EXT._code_header (head,adr,ods,cislo: string; header_data: string; data: pchars; var header: string): string;
    begin
      if cislo='' then
         begin
           INC_CISLO_SPRAVY(CISLO_SPRAVY,CISLO_SPRAVYcfg);
           cislo:= IntToStr(CISLO_SPRAVY,kod_SQN,0)
         end;
      header:= head;
      if EXT_HEADER_ADR then
         begin
           if adr='' then adr:= NODE_THIS;
           if ods='' then ods:= NODE_REMOTE;

         { kontrola na spravnu dlzku
         } header:= InsChar(header,kod_HEAD,' ',1);
           adr   := InsChar(adr,kod_ID,' ',1);
           ods   := InsChar(ods,kod_ID,' ',1);
           cislo := InsChar(cislo,kod_SQN,' ',1);
           header:= header+adr+icao_NXT+ods+cislo;

           if header_data<>'' then header:= header + header_data;
         end;
      if data<>nil then header:= header+icao_ARR;
      _code_header:= header
    end;


 function O_EXT._decode_header (header: string;
                                var head,adr,ods,cislo: string;
                                var header_data: string;
                                res: pstring
                               ): bool;
    var   s: string;
          p: int;
    begin
      header:= getstr(header,1,odd_L4); { mtks_rus_to_lat uz je... }
      s:= getstr(header,1,[icao_NXT]);
      head:= copy(s,1,kod_HEAD);
      ods := copy(s,kod_HEAD+1,kod_ID);
      p:= length(s)+1;
      s:= getstr(header,2,[icao_NXT]);
      adr := copy(s,1,kod_ID);
      cislo := copy(s,kod_ID+1,kod_SQN);
      inc(p,length(adr)+length(cislo));
      header_data:= copy(header,p+1,length(header)-p);
      if res<>nil then
         begin
           res^:= '';
           if head='' then res^:= err_ext_undecoded_message_type
           else if ods='' then res^:= err_ext_undecoded_message_sender
           else if adr=''then res^:= err_ext_undecoded_message_address
           else if cislo='' then res^:= err_ext_undecoded_message_number
         end;
      _decode_header:= (res=nil) or (res^='');
    end;


 function O_EXT.decode_header (data: pchars; size: word;
                               zac,kon: word;
                               var header: string;
                               var res: string;
                               decode: bool
                              ): bool;
    var   bres  : bool;
    begin
      res:= ''; header:= '';
      if zac<size then header:= mtks_rus_to_lat(get_str_(@data^[zac],size-zac,1,odd_L4, bres, sizeof(header)-1));
      if (header='') then res:= err_ext_undecoded_message_header;
      decode_header:= res=''
    end;


 function O_EXT.decode_head (header: string;
                             var head: string;
                             var res: string
                            ): bool;
    begin
      res:= '';
      head:= getstr(header,1,[icao_NXT]+odd_L4);
      head:= copy(head,1,kod_head);
      if head='' then res:= err_ext_undecoded_message_type;
      decode_head:= res=''
    end;


 function O_EXT.enabled_head (src: TPKT_SRC;
                              data: pchars; size: word;
                              head: string;
                              var res: string
                             ): bool;
    begin
      res:= '';
      enabled_head:= _icao_head_type(head,res) >= 0
    end;


{ Spracovanie dat paketu;
  Abstraktna funkcia
}
 function O_EXT.decode_data  (data: pchars; size: word;
                              header: string;
                              var head: string;
                              var res: string
                             ): bool;
    begin
      decode_data:= decode_LAM (data,size,header, res) {(_icao_head_type(head,res)>=0)};
    end;


 function O_EXT.decode_adr (header: string; var res: string): bool;
    var   head,adr,ods,cislo,header_data : string;
    begin
      if (not process_all_adr) and _decode_header (header, head,adr,ods,cislo,header_data, @res) then
         begin
           if (adr<>NODE_THIS) and (NODE_THIS<>NODE_PROMISCUITE) then res:= err_ext_received_address
           else if (ods<>NODE_REMOTE) and (NODE_REMOTE<>NODE_PROMISCUITE) then res:= err_ext_sender_address
         end;
      decode_adr:= res= '';
    end;


{ ----------------------------------------------
   Funkcia spracovania paketu, moze sa pretazit
   pre odlisenie typu paketov a ich rozneho
   spracovania, napriklad (FPL,TLG,PLN...),
   pripadne zahrnut spracovanie NET sprav
  תתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתתת

   Vracia true, ak sa paket potvrdzuje; chyby detekuje
   vo vnutri a vyhodnocuje ich s popisom.
   Kvoli jednoduchsiemu spracovaniu pchar-u konverzia
   pchars na pchar
}

 function O_EXT.process_data (src: TPKT_SRC;
                              data: pchars; size: word;
                              var header: string;
                              var resh,resd: string
                             ): bool;
    var   zac,kon : word;
          head : string;
          hb,bres : bool;
    begin
      resh:= ''; resd:= '';
      process_data:= true;
      if decode_HeartBeat (data,size) then Exit;

      bres:=      decode_frame  (data,size, zac,kon, resh)
              and decode_header (data,size, zac,kon, header, resh, true)
              and decode_head   (header, head, resh)
              and enabled_head  (src, data,size, head, resh)
              and decode_adr    (header, resh)
              and decode_data   (@data^[zac],kon-zac+1, header,head, resd);

      process_data:= bres
    end;


 function O_EXT.process_pkt (src: TPKT_SRC;
                             data: pchars; size: word;
                             var header: string;
                             var res: string;
                             res_send: bool
                            ): bool;
    var   resd,resh: string;
    begin
      process_pkt:= false;
      res:= '';
      if (data=nil) or (size=0) then Exit;

      if (process_data(src, data,size,header, resh,resd)) then
         begin
         { Vykonane dekodovanie, spracovanie, rozoslanie
           a spracovanie potvrdeni funkciou process_data
         }
           process_pkt:= true;

         { ma sa sprava potvrdit ?
         }
           if (    (src=src_ext)
               and (not lam_pred_spracovanim)
               and _is_to_LAM (data,size,header)
              )
               then send_LAM(data,size,header);

         { rozoslanie spravy na ostatne (backup) pracoviska
         }
          {$IFDEF SYNCHRONIZE_EXT}
           if (res='') and res_send then distribute_pkt(data,size,'','',spr_prd,'',false);
          {$ENDIF}
         end;

      if (resh<>'') then
         begin
           process_ERR_HEAD (src, data,size,resh);
           res:= resh
         end
      else if (resd<>'') and (src<>src_net) then
         begin
         { Sprava o chybe sa distribuuje len pri jej prvom spracovani
         } process_ERR_DATA (src, data,size,resd, true,true,true);
           res:= resd
         end
    end;

